#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "commoninclude.h"

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 

#define CBSLOT_TRANSFORM		0
#define CBSLOT_ANIMATION		1
#define CBSLOT_UI				2


namespace min::graphics
{
	struct Vertex
	{
		math::Vector3 pos;
		math::Vector4 color;
		math::Vector2 uv;
	};

	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		All,
		End,
	};

	enum class eCBType
	{
		Transform,
		Animation,
		None,
		End,
	};

	enum class eSamplerType
	{
		Point,
		Linear,
		Anisotropic,
		PostProcess,
		End,
	};

	enum class eRenderingMode
	{
		Opaque,
		CutOut,
		Transparent,
		PostProcess,
		End,
	};

	enum class eTextureType
	{
		Albedo,
		Normal,
		Specular,
		Smoothness,
		Metallic,
		Sprite,
		Animation,
		End,
	};

	enum class eRasterizerState
	{
		SolidBack,
		SolidFront,
		SolidNone,
		Wireframe,
		End,
	};
	enum class eBlendState
	{
		AlphaBlend,
		OneOne,
		ColorZero,
		End,
	};

	enum class eDepthStencilState
	{
		DepthNone,
		LessEqual,
		End,
	};
	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer = nullptr;
		D3D11_BUFFER_DESC desc = {};

		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		math::Matrix world;
		math::Matrix view;
		math::Matrix projection;
	};

	CBUFFER(AnimationCB, CBSLOT_ANIMATION)
	{
		float offsetX;
		float offsetY;
		float sizeX;
		float sizeY;
		float textureSizeX;
		float textureSizeY;
		float useAni;
		float DataPadding;
	};

	CBUFFER(UICB, CBSLOT_UI)
	{
		math::Matrix view;
		math::Matrix projection;
	};
}

