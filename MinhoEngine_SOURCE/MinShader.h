#pragma once
#include "MinResource.h"
#include "MinGraphicDevice_DX11.h"

namespace min::graphics
{
	class Shader : public Resource
	{
	public:
		Shader();
		virtual ~Shader();

		virtual HRESULT Save(const std::wstring path) override;
		virtual HRESULT Load(const std::wstring path) override;
		bool Create(const eShaderStage stage, const std::wstring& fileName);
		bool CreateVertexShader(const std::wstring& fileName);
		bool CreatePixelShader(const std::wstring& fileName);

		void Bind();

		[[nodiscard]] Microsoft::WRL::ComPtr<ID3DBlob> GetVSBlob() { return mVSBlob; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID3DBlob> GetHSBlob() { return mHSBlob; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID3DBlob> GetDSBlob() { return mDSBlob; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID3DBlob> GetGSBlob() { return mGSBlob; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID3DBlob> GetPSBlob() { return mPSBlob; }

		[[nodiscard]] Microsoft::WRL::ComPtr<ID3D11VertexShader> GetVS() const { return mVS; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID3D11HullShader> GetHS() const { return mHS; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID3D11DomainShader> GetDS() const { return mDS; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID3D11GeometryShader> GetGS() const { return mGS; }
		[[nodiscard]] Microsoft::WRL::ComPtr<ID3D11PixelShader> GetPS() const { return mPS; }

		void SetRasterizerState(const eRasterizerState state) { mRasterizerState = state; }
		void SetBlendState(const eBlendState state) { mBlendState = state; }
		void SetDepthStencilState(const eDepthStencilState state) { mDepthStencilState = state; }

		void SetBlendFactor(float Factors[4])
		{
			for (int i = 0; i < 4; i++)
			{
				mBlendFactor[i] = Factors[i];
			}
			isBlendFactor = true;
		}

	private:
		static bool bWireframe;

		Microsoft::WRL::ComPtr<ID3DBlob> mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;

		graphics::eRasterizerState mRasterizerState;
		graphics::eBlendState mBlendState;
		graphics::eDepthStencilState mDepthStencilState;

		bool isBlendFactor = false;
		float mBlendFactor[4];
	};
}

