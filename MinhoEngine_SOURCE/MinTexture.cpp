#include "MinTexture.h"
#include "MinApplication.h"
#include "MinResources.h"

extern min::Application application;

namespace min::graphics
{
	Texture::Texture()
		: Resource(enums::eResourceType::Texture)
		, mDesc{}
	{
	}

	Texture::~Texture()
	{
	}

	HRESULT Texture::Save(const std::wstring path)
	{
		return E_NOTIMPL;
	}
	HRESULT Texture::Load(const std::wstring path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);
		//bmp �϶�
		/*if (ext == L"bmp")
		{
			mType = eTextureType::Bmp;
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP
				, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			if (mBitmap == nullptr)
				return S_FALSE;

			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;
			
			if (info.bmBitsPixel == 32)
				mbAlpha = true;
			else if (info.bmBitsPixel == 24)
				mbAlpha = false;

			HDC mainDC = application.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(oldBitmap);
		}
		else if (ext == L"png")
		{
			mType = eTextureType::Png;
			mImage = Gdiplus::Image::FromFile(path.c_str());
			if (mImage == nullptr)
				return S_FALSE;
			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}*/

		if (ext == L".dds" || ext == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (ext == L".tga" || ext == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}

		HRESULT hr = CreateShaderResourceView
		(
			graphics::GetDevice()->GetID3D11Device().Get()
			, mImage.GetImages()
			, mImage.GetImageCount()
			, mImage.GetMetadata()
			, mSRV.GetAddressOf()
		);

		if (hr == S_FALSE)
			assert(false/*"Textrue load fail!!"*/);

		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		return S_OK;
	}

	HRESULT Texture::CreateByScratchImage(ScratchImage mScratchImage)
	{
		HRESULT hr = CreateShaderResourceView
		(
			graphics::GetDevice()->GetID3D11Device().Get()
			, mScratchImage.GetImages()
			, mScratchImage.GetImageCount()
			, mScratchImage.GetMetadata()
			, mSRV.GetAddressOf()
		);

		if (hr == S_FALSE)
			assert(false/*"Textrue load fail!!"*/);

		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		return S_OK;
	}

	bool Texture::Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag)
	{
		mDesc.BindFlags = bindFlag;
		mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mDesc.CPUAccessFlags = 0;
		mDesc.Format = format;
		mDesc.Width = width;
		mDesc.Height = height;
		mDesc.ArraySize = 1;
		mDesc.SampleDesc.Count = 1;
		mDesc.SampleDesc.Quality = 0;
		mDesc.MipLevels = 1;
		mDesc.MiscFlags = 0;

		if (!GetDevice()->CreateTexture2D(&mDesc, nullptr, mTexture.GetAddressOf()))
			return false;

		if (!CreateGpuView(mDesc.BindFlags))
			return false;

		return true;
	}

	bool Texture::CreateSRV()
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = mDesc.Format;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

		if (!GetDevice()->CreateShaderResourceView(mTexture.Get(), &srvDesc, mSRV.GetAddressOf()))
			return false;

		return true;
	}

	bool Texture::CreateUAV()
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.Format = mDesc.Format;
		uavDesc.Texture2D.MipSlice = 0;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;

		if (!GetDevice()->CreateUnorderedAccessView(mTexture.Get(), &uavDesc, mUAV.GetAddressOf()))
			return false;

		return true;
	}

	bool Texture::CreateRTV()
	{
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = mDesc.Format;
		rtvDesc.Texture2D.MipSlice = 0;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;


		if (!GetDevice()->CreateRenderTargetView(mTexture.Get(), &rtvDesc, mRTV.GetAddressOf()))
			return false;

		return true;
	}

	bool Texture::CreateDSV()
	{
		if (!GetDevice()->CreateDepthStencilView(mTexture.Get(), nullptr, mDSV.GetAddressOf()))
			return false;

		return true;
	}

	bool Texture::CreateGpuView(UINT flag)
	{
		if (flag & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			if (!CreateRTV())
				return false;
		}
		if (flag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
		{
			if (!CreateDSV())
				return false;
		}
		if (flag & D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			if (!CreateSRV())
				return false;
		}
		if (flag & D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			if (!CreateUAV())
				return false;
		}

		return true;
	}

	void Texture::Bind(eShaderStage stage, UINT startSlot)
	{
		graphics::GetDevice()->SetShaderResource(stage, startSlot, mSRV.GetAddressOf());
	}
}