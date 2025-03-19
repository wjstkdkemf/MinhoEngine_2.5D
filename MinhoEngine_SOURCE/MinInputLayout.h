#pragma once
#include "MinGraphicDevice_DX11.h"

namespace min::graphics
{
	class InputLayout
	{
	public:
		InputLayout();
		~InputLayout();

		void CreateInputLayout(UINT vertexCount, D3D11_INPUT_ELEMENT_DESC* layout, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength);
		void CreateInputLayout_Const(UINT vertexCount,const D3D11_INPUT_ELEMENT_DESC* layout, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength);
		ID3D11InputLayout* GetInputLayout() { return mInputLayout.Get(); }
		
		void Bind();

	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

	};
}

