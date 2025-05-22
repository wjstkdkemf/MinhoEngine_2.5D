#pragma once
#include "MinGraphics.h"

namespace min::graphics
{
	class GraphicDevice_DX11
	{
	public:
		GraphicDevice_DX11();
		~GraphicDevice_DX11();

		bool CreateDevice();
		bool CreateSwapchain(DXGI_SWAP_CHAIN_DESC desc);
		bool GetBuffer(UINT Buffer, REFIID riid, void** ppSurface);
		bool CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView);
		bool CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView);
		bool CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D);
		bool CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);
		bool CreateVertexShader(const std::wstring& fileName, ID3DBlob** ppCode, ID3D11VertexShader** ppVertexShader);
		bool CreatePixelShader(const std::wstring& fileName, ID3DBlob** ppCode, ID3D11PixelShader** ppPixelShader);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements
			, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer);
		bool CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView);
		bool CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState);
		bool CreateBlendState(const D3D11_BLEND_DESC* pBlendState, ID3D11BlendState** ppBlendState);
		bool CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState);

		void InitializeD2D(ID3D11Device* d3d11Device, IDXGISwapChain* swapChain);

		void BindInputLayout(ID3D11InputLayout* pInputLayout);
		void BindPrimitiveTopology(const D3D11_PRIMITIVE_TOPOLOGY topology);
		void BindVS(ID3D11VertexShader* pVertexShader);
		void BindPS(ID3D11PixelShader* pPixelShader);
		void SetDataGpuBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void SetShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset);
		void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindVertexBuffer(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void BindVertexBufferWithInstanceBuffer(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const ppVertexBuffers[], const UINT pStrides[], const UINT pOffsets[]);
		void BindSampler(eShaderStage stage, UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers);
		void BindSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers);
		bool CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView);
		void BindRasterizerState(ID3D11RasterizerState* pRasterizerState);
		void BindBlendState(ID3D11BlendState* pBlendState, const FLOAT BlendFactor[4], UINT SampleMask);
		void BindDepthStencilState(ID3D11DepthStencilState* pDepthStencilState, UINT StencilRef);
		bool Resize(D3D11_VIEWPORT viewport);

		void BindViewPort();
		void BindRenderTargets(UINT NumViews = 1, ID3D11RenderTargetView* const* ppRenderTargetViews = nullptr, ID3D11DepthStencilView* pDepthStencilView = nullptr);
		void BindDefaultRenderTarget();

		void CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource);

		void ClearRenderTargetView();
		void ClearDepthStencilView();

		void Initialize();
		void Draw(UINT VertexCount, UINT StartVertexLocation);
		void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
		void DrawIndexedInstanced(UINT IndexCount, UINT slotSize, UINT StartIndexLocation, INT BaseVertexLocation);
		void Present();

	public:
		[[nodiscard]]Microsoft::WRL::ComPtr<ID3D11Device> GetID3D11Device() { return mDevice; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetID3D11DeviceContext() { return mContext; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetFrameBuffer() { return mFrameBuffer; }

		[[nodiscard]] Microsoft::WRL::ComPtr<ID2D1Factory1> GetID2D1Factory1() { return g_d2dFactory; }
		[[nodiscard]] Microsoft::WRL::ComPtr<IDWriteFactory> GetIDWriteFactory() { return g_dwriteFactory; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID2D1RenderTarget> GetID2D1RenderTarget() { return g_d2dRenderTarget; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> GetID2D1SolidColorBrush() { return g_brush; }
		[[nodiscard]] Microsoft::WRL::ComPtr<IDWriteTextFormat> GetIDWriteTextFormat() { return g_textFormat; }


	private:
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mFrameBuffer;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mFrameBufferView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencil;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> mSamplers;//[(UINT)Filter::MAXIMUM_ANISOTROPIC]

		Microsoft::WRL::ComPtr<ID2D1Factory1> g_d2dFactory;
		Microsoft::WRL::ComPtr<IDWriteFactory> g_dwriteFactory;
		Microsoft::WRL::ComPtr<ID2D1RenderTarget> g_d2dRenderTarget; // Direct3D 백버퍼와 연동될 렌더 타겟
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> g_brush;
		Microsoft::WRL::ComPtr<IDWriteTextFormat> g_textFormat;
	};

	inline GraphicDevice_DX11*& GetDevice()
	{
		static GraphicDevice_DX11* device = nullptr;
		return device;
	}
}

