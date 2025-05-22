#include "MinGraphicDevice_DX11.h"
#include "MinApplication.h"
#include "MinRenderer.h"
#include "MinShader.h"
#include "MinTexture.h"
#include "MinResources.h"
#include "MinMesh.h"
#include "MinMaterial.h"

extern min::Application application;

namespace min::graphics
{
	GraphicDevice_DX11::GraphicDevice_DX11()
	{
		min::graphics::GetDevice() = this;
		if (!(CreateDevice()))
			assert(NULL && "Create Device Failed!");
	}

	GraphicDevice_DX11::~GraphicDevice_DX11()
	{
	}

	bool GraphicDevice_DX11::CreateDevice()
	{
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		if (FAILED(D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
			0, creationFlags,
			featureLevels, ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION, mDevice.GetAddressOf(),
			0, mContext.GetAddressOf())))
			return false;

		return true;
	}

	void GraphicDevice_DX11::InitializeD2D(ID3D11Device* d3d11Device, IDXGISwapChain* swapChain)
	{
		HRESULT hr = S_OK;
		// Direct2D ���丮 ����
		D2D1_FACTORY_OPTIONS options = {};
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &options, &g_d2dFactory);

		if (FAILED(hr))
		{
			int a = 0;
		}

		// DirectWrite ���丮 ����
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &g_dwriteFactory);

		if (FAILED(hr))
		{
			int a = 0;
		}

		// DXGI ����ۿ��� Direct2D ���� Ÿ�� ����
		Microsoft::WRL::ComPtr<IDXGISurface> dxgiBackBuffer;

		hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));

		if (FAILED(hr))
		{
			int a = 0;
		}

		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_HARDWARE,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
		hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));;

		if (FAILED(hr))
		{
			int a = 0;
		}

		hr = g_d2dFactory->CreateDxgiSurfaceRenderTarget(dxgiBackBuffer.Get(), &props, &g_d2dRenderTarget);

		if (FAILED(hr))
		{
			int a = 0;
		}

		// �귯�� �� �ؽ�Ʈ ���� ���� (����)
		g_d2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &g_brush);
		g_dwriteFactory->CreateTextFormat(
			L"Arial",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			24.0f,
			L"ko-kr", // �Ǵ� �ٸ� ������
			&g_textFormat
		);
	}

	bool GraphicDevice_DX11::CreateSwapchain(DXGI_SWAP_CHAIN_DESC desc)
	{
		Microsoft::WRL::ComPtr<IDXGIDevice>     pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter>    pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory>    pFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
			return false;

		if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
			return false;

		if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &desc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::GetBuffer(UINT Buffer, REFIID riid, void** ppSurface)
	{
		if (FAILED(mSwapChain->GetBuffer(Buffer, riid, ppSurface)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
	{
		if (FAILED(mDevice->CreateRenderTargetView(pResource, pDesc, ppRTView)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
	{
		if (FAILED(mDevice->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D)
	{
		if (FAILED(mDevice->CreateTexture2D(pDesc, pInitialData, ppTexture2D)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
	{
		if (FAILED(mDevice->CreateSamplerState(pSamplerDesc, ppSamplerState)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateVertexShader(const std::wstring& fileName, ID3DBlob** ppCode, ID3D11VertexShader** ppVertexShader)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

		ID3DBlob* errorBlob = nullptr;
		const std::wstring shaderFilePath = L"..\\Shaders_SOURCE\\";
		D3DCompileFromFile((shaderFilePath + fileName + L"VS.hlsl").c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "main", "vs_5_0", shaderFlags, 0, ppCode, &errorBlob);

		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
			assert(NULL && "hlsl file have problem check message!");
			return false;
		}

		if (FAILED(mDevice->CreateVertexShader((*ppCode)->GetBufferPointer(), (*ppCode)->GetBufferSize(), nullptr, ppVertexShader)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreatePixelShader(const std::wstring& fileName, ID3DBlob** ppCode, ID3D11PixelShader** ppPixelShader)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

		ID3DBlob* errorBlob = nullptr;
		const std::wstring shaderFilePath = L"..\\Shaders_SOURCE\\";
		D3DCompileFromFile((shaderFilePath + fileName + L"PS.hlsl").c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "main", "ps_5_0", shaderFlags, 0, ppCode, &errorBlob);

		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
			assert(NULL && "hlsl file have problem check message!");
			return false;
		}

		if (FAILED(mDevice->CreatePixelShader((*ppCode)->GetBufferPointer(), (*ppCode)->GetBufferSize(), nullptr, ppPixelShader)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements
		, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout)
	{
		if (FAILED(mDevice->CreateInputLayout(pInputElementDescs, NumElements
			, pShaderBytecodeWithInputSignature
			, BytecodeLength
			, ppInputLayout)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
	{
		if (FAILED(mDevice->CreateBuffer(pDesc, pInitialData, ppBuffer)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
	{

		if (FAILED(mDevice->CreateShaderResourceView(pResource, pDesc, ppSRView)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView)
	{
		if (FAILED(mDevice->CreateUnorderedAccessView(pResource, pDesc, ppUAView)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
	{
		if (FAILED(mDevice->CreateRasterizerState(pRasterizerDesc, ppRasterizerState)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateBlendState(const D3D11_BLEND_DESC* pBlendState, ID3D11BlendState** ppBlendState)
	{
		if (FAILED(mDevice->CreateBlendState(pBlendState, ppBlendState)))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState)
	{
		if (FAILED(mDevice->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState)))
			return false;

		return true;
	}

	void GraphicDevice_DX11::BindInputLayout(ID3D11InputLayout* pInputLayout)
	{
		mContext->IASetInputLayout(pInputLayout);
	}

	void GraphicDevice_DX11::BindPrimitiveTopology(const D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		mContext->IASetPrimitiveTopology(topology);
	}

	void GraphicDevice_DX11::BindVS(ID3D11VertexShader* pVertexShader)
	{
		mContext->VSSetShader(pVertexShader, 0, 0);
	}

	void GraphicDevice_DX11::BindPS(ID3D11PixelShader* pPixelShader)
	{
		mContext->PSSetShader(pPixelShader, 0, 0);
	}
	void GraphicDevice_DX11::SetDataGpuBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, size);
		mContext->Unmap(buffer, 0);
	}

	void GraphicDevice_DX11::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
	{
		mContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
	}

	void GraphicDevice_DX11::SetShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV)
	{
		if ((UINT)eShaderStage::VS & (UINT)stage)
			mContext->VSSetShaderResources(startSlot, 1, ppSRV);
		if ((UINT)eShaderStage::HS & (UINT)stage)
			mContext->HSSetShaderResources(startSlot, 1, ppSRV);
		if ((UINT)eShaderStage::DS & (UINT)stage)
			mContext->DSSetShaderResources(startSlot, 1, ppSRV);
		if ((UINT)eShaderStage::GS & (UINT)stage)
			mContext->GSSetShaderResources(startSlot, 1, ppSRV);
		if ((UINT)eShaderStage::PS & (UINT)stage)
			mContext->PSSetShaderResources(startSlot, 1, ppSRV);
		if ((UINT)eShaderStage::CS & (UINT)stage)
			mContext->CSSetShaderResources(startSlot, 1, ppSRV);
	}

	void GraphicDevice_DX11::BindSampler(eShaderStage stage, UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		if (eShaderStage::VS == stage)
			mContext->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);

		if (eShaderStage::HS == stage)
			mContext->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);

		if (eShaderStage::DS == stage)
			mContext->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);

		if (eShaderStage::GS == stage)
			mContext->GSSetSamplers(StartSlot, NumSamplers, ppSamplers);

		if (eShaderStage::PS == stage)
			mContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
	}

	void GraphicDevice_DX11::BindSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		BindSampler(eShaderStage::VS, StartSlot, NumSamplers, ppSamplers);
		BindSampler(eShaderStage::HS, StartSlot, NumSamplers, ppSamplers);
		BindSampler(eShaderStage::DS, StartSlot, NumSamplers, ppSamplers);
		BindSampler(eShaderStage::GS, StartSlot, NumSamplers, ppSamplers);
		BindSampler(eShaderStage::PS, StartSlot, NumSamplers, ppSamplers);
	}
	void GraphicDevice_DX11::BindViewPort()
	{
		D3D11_VIEWPORT viewPort =
		{
			0, 0,
			(float)application.GetWindow().GetWidth(), (float)application.GetWindow().GetHeight(),
			0.0f, 1.0f
		};

		mContext->RSSetViewports(1, &viewPort);
	}

	void GraphicDevice_DX11::BindRenderTargets(UINT NumViews
		, ID3D11RenderTargetView* const* ppRenderTargetViews
		, ID3D11DepthStencilView* pDepthStencilView)
	{
		mContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
	}

	void GraphicDevice_DX11::BindDefaultRenderTarget()
	{
		mContext->OMSetRenderTargets(1, mFrameBufferView.GetAddressOf(), mDepthStencilView.Get());
	}

	void GraphicDevice_DX11::CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource)
	{
		mContext->CopyResource(pDstResource, pSrcResource);
	}

	void GraphicDevice_DX11::BindRasterizerState(ID3D11RasterizerState* pRasterizerState)
	{
		mContext->RSSetState(pRasterizerState);
	}
	void GraphicDevice_DX11::BindBlendState(ID3D11BlendState* pBlendState, const FLOAT BlendFactor[4], UINT SampleMask)
	{
		mContext->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
	}
	void GraphicDevice_DX11::BindDepthStencilState(ID3D11DepthStencilState* pDepthStencilState, UINT StencilRef)
	{
		mContext->OMSetDepthStencilState(pDepthStencilState, StencilRef);
	}

	bool GraphicDevice_DX11::Resize(D3D11_VIEWPORT viewport)
	{
		mFrameBufferView.Reset();
		mFrameBuffer.Reset();

		mDepthStencilView.Reset();
		mDepthStencil.Reset();

		HRESULT hr = mSwapChain->ResizeBuffers(0, // ���� ���� ����
			(UINT)viewport.Width, // �ػ� ����
			(UINT)viewport.Height,
			DXGI_FORMAT_UNKNOWN, // ���� ���� ����
			0);

		// Get render target by Swapchain
		Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTarget = nullptr;
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)(renderTarget.GetAddressOf()));

		D3D11_TEXTURE2D_DESC desc = {};
		renderTarget->GetDesc(&desc);
		mFrameBuffer = renderTarget;

		// Create RenderTargetView
		hr = mDevice->CreateRenderTargetView(mFrameBuffer.Get(), nullptr, mFrameBufferView.GetAddressOf());

		// Create DepthStencil
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.Width = (UINT)viewport.Width;
		depthStencilDesc.Height = (UINT)viewport.Height;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.MiscFlags = 0;

		hr = mDevice->CreateTexture2D(&depthStencilDesc, nullptr, mDepthStencil.GetAddressOf());

		// Create DepthStencilView
		hr = mDevice->CreateDepthStencilView(mDepthStencil.Get(), nullptr, mDepthStencilView.GetAddressOf());

		// Set Viewport
		BindViewPort();

		// Bind RenderTarget
		BindRenderTargets(1, mFrameBufferView.GetAddressOf(), mDepthStencilView.Get());

		return true;
	}

	void GraphicDevice_DX11::ClearRenderTargetView()
	{
		FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mFrameBufferView.Get(), backgroundColor);
	}

	void GraphicDevice_DX11::ClearDepthStencilView()
	{
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void GraphicDevice_DX11::Initialize()
	{
#pragma region swapchain desc

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		swapChainDesc.OutputWindow = application.GetWindow().GetHwnd();
		swapChainDesc.Windowed = true;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Width = application.GetWindow().GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetWindow().GetHeight();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

#pragma region 4X MSAA surported check
		UINT quility = 0;
		mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &quility);

		/*
		* if(quility > 0)
		* {
		*	swapChainDesc.SampleDesc.Count = 4; // how many multisamples
			swapChainDesc.SampleDesc.Quality = quility - 1;
		* }
		*/

#pragma endregion
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
#pragma endregion
		if (!(CreateSwapchain(swapChainDesc)))
			assert(NULL && "Create Swapchain Failed!");
		if (!(GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mFrameBuffer.GetAddressOf())))
			assert(NULL && "Couldn't bring rendertarget!");
		if (!(CreateRenderTargetView(mFrameBuffer.Get(), nullptr, mFrameBufferView.GetAddressOf())))
			assert(NULL && "Create RenderTargetView Failed!");
#pragma region depthstencil desc

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthStencilDesc.Width = application.GetWindow().GetWidth();
		depthStencilDesc.Height = application.GetWindow().GetHeight();
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
#pragma endregion
		if (!(CreateTexture2D(&depthStencilDesc, nullptr, mDepthStencil.GetAddressOf())))
			assert(NULL && "Create depthstencil texture failed!");
		if (!(CreateDepthStencilView(mDepthStencil.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			assert(NULL && "Create depthstencilview failed!");

		//renderer::vertexBuffer.Create(renderer::vertexes);
		//renderer::indexBuffer.Create(renderer::indices);
		InitializeD2D(mDevice.Get(), mSwapChain.Get());
	}

	void GraphicDevice_DX11::Draw(UINT VertexCount, UINT StartVertexLocation)
	{
		//Mesh* mesh = Resources::Find<Mesh>(L"RectMesh");
		//mesh->Bind();

		//Vector4 pos(-0.2f, 0.0f, 0.0f, 1.0f);
		//renderer::constantBuffers[(UINT)eCBType::Transform].SetData(&pos);
		//renderer::constantBuffers[(UINT)eCBType::Transform].Bind(eShaderStage::VS);

		//Material* material = min::Resources::Find<Material>(L"SpriteMaterial");
		//material->Bind();

		//mContext->DrawIndexed(6, 0, 0);

		//// Draw Triangle
		//mesh = Resources::Find<Mesh>(L"TriangleMesh");
		//mesh->Bind();

		//pos = Vector4(0.2f, 0.0f, 0.0f, 1.0f);
		//renderer::constantBuffers[(UINT)eCBType::Transform].SetData(&pos);
		//renderer::constantBuffers[(UINT)eCBType::Transform].Bind(eShaderStage::VS);

		//material = min::Resources::Find<Material>(L"TriangleMaterial");
		//material->Bind();

		//mContext->DrawIndexed(3, 0, 0);
		mContext->Draw(VertexCount, StartVertexLocation);
	}
	void GraphicDevice_DX11::BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		UINT slot = (UINT)type;
		switch (stage)
		{
		case min::graphics::eShaderStage::VS:
			mContext->VSSetConstantBuffers(slot, 1, &buffer);
			break;
		case min::graphics::eShaderStage::HS:
			mContext->HSSetConstantBuffers(slot, 1, &buffer);
			break;
		case min::graphics::eShaderStage::DS:
			mContext->DSSetConstantBuffers(slot, 1, &buffer);
			break;
		case min::graphics::eShaderStage::GS:
			mContext->GSSetConstantBuffers(slot, 1, &buffer);
			break;
		case min::graphics::eShaderStage::PS:
			mContext->PSSetConstantBuffers(slot, 1, &buffer);
			break;
		case min::graphics::eShaderStage::CS:
			mContext->CSSetConstantBuffers(slot, 1, &buffer);
			break;
		case min::graphics::eShaderStage::All:
			mContext->VSSetConstantBuffers(slot, 1, &buffer);
			mContext->HSSetConstantBuffers(slot, 1, &buffer);
			mContext->DSSetConstantBuffers(slot, 1, &buffer);
			mContext->GSSetConstantBuffers(slot, 1, &buffer);
			mContext->PSSetConstantBuffers(slot, 1, &buffer);
			mContext->CSSetConstantBuffers(slot, 1, &buffer);
			break;
		default:
			break;
		}
	}
	void GraphicDevice_DX11::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		mContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
	}
	void GraphicDevice_DX11::DrawIndexedInstanced(UINT IndexCount,UINT slotSize, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		mContext->DrawIndexedInstanced(IndexCount, slotSize, 0, 0, 0);// �ε��� ������ ������ġ, ���� ������ ������ġ, �ν��Ͻ� ���� ��ġ
	}
	void GraphicDevice_DX11::Present()
	{
		mSwapChain->Present(1, 0);
	}
	void GraphicDevice_DX11::BindVertexBuffer(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
	{
		mContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
	}
	void GraphicDevice_DX11::BindVertexBufferWithInstanceBuffer(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const ppVertexBuffers[], const UINT pStrides[], const UINT pOffsets[])
	{
		mContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
	}
}
