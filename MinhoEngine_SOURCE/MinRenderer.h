#pragma once
#include "MinCamera.h"
#include "MinGraphicDevice_DX11.h"

#include "MinConstantBuffer.h"
#include "MinMesh.h"

using namespace min::graphics;
using namespace min::math;

namespace min::renderer
{
	extern Camera* mainCamera;

	extern Mesh* mesh;
	extern graphics::ConstantBuffer constantBuffers[(UINT)eCBType::End];
	extern ID3D11Buffer* constantBuffer;

	extern ID3D11InputLayout* inputLayouts;


	void Initialize();
	void Release();
}

