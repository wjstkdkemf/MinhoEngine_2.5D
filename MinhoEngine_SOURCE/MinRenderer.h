#pragma once
#include "MinCamera.h"
#include "MinGraphicDevice_DX11.h"

#include "MinConstantBuffer.h"
#include "MinRenderTarget.h"

using namespace min::graphics;
using namespace min::math;

namespace min::renderer
{
	extern Camera* mainCamera;

	extern GameObject* selectedObject;

	extern graphics::ConstantBuffer* constantBuffers[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRasterizerState::End];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBlendState::End];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDepthStencilState::End];

	extern RenderTarget* FrameBuffer;

	void Initialize();
	void Release();
}

