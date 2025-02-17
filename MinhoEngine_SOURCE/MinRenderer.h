#pragma once
#include "MinCamera.h"
#include "MinGraphicDevice_DX11.h"

#include "MinVertexBuffer.h"
#include "MinConstantBuffer.h"
#include "MinIndexBuffer.h"

using namespace min::graphics;
using namespace min::math;

namespace min::renderer
{
	extern Camera* mainCamera;

	extern std::vector<graphics::Vertex> vertexes;
	extern std::vector<UINT> indices;

	extern graphics::VertexBuffer vertexBuffer;
	extern graphics::IndexBuffer indexBuffer;
	extern graphics::ConstantBuffer constantBuffers[(UINT)eCBType::End];
	extern ID3D11Buffer* constantBuffer;

	extern ID3D11InputLayout* inputLayouts;


	void Initialize();
	void Release();
}

