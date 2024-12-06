#pragma once
#include "MinResource.h"
namespace min::graphcis
{
	class Texture : public Resource
	{
	public:
		enum class eTextureType 
		{
			Bmp,
			Png,
			None,
		};

		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring path) override;

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }
		eTextureType GetTextureType() { return mType; }
		Gdiplus::Image* GetImage() { return mImage; }

	private:
		eTextureType mType;
		Gdiplus::Image* mImage;//png파일
		HBITMAP mBitmap;//bmp 파일
		HDC mHdc;

		UINT mWidth;
		UINT mHeight;
	};
}

