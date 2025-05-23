#include "MinRenderer.h"
#include "MinGraphicDevice_DX11.h"
#include "MinResources.h"
#include "MinShader.h"
#include "MinMesh.h"
#include "MinMaterial.h"
#include "MinApplication.h"
#include "MinRenderTarget.h"

extern min::Application application;

namespace min::renderer
{
	Camera* mainCamera = nullptr;
	GameObject* selectedObject = nullptr;

	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	InstanceBuffer* InstanceBuffers[(UINT)eIBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRasterizerState::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBlendState::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDepthStencilState::End] = {};
	std::unique_ptr<PrimitiveBatch<VertexPositionColor>> primitiveBatch = {};
	std::unique_ptr<BasicEffect> batchEffect = {};

	RenderTarget* FrameBuffer = nullptr;

	void LoadTriangleMesh()
	{
		Mesh* mesh = new Mesh();

		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(3);
		vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[2] = {};
		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		graphics::Shader* triangleShader = Resources::Find<graphics::Shader>(L"TriangleShader");
		mesh->SetVertexBufferParams(2, inputLayoutDesces, triangleShader->GetVSBlob()->GetBufferPointer(), triangleShader->GetVSBlob()->GetBufferSize());

		mesh->CreateIB(indices);
		mesh->CreateVB(vertexes);

		min::Resources::Insert(L"TriangleMesh", mesh);
	}

	void LoadFrameBuffer()
	{
		RenderTargetSpecification spec;
		spec.Attachments = { eRenderTargetFormat::RGBA8, eRenderTargetFormat::Depth };
		spec.Width = application.GetWindow().GetWidth();
		spec.Height = application.GetWindow().GetHeight();

		FrameBuffer = RenderTarget::Create(spec);
	}

	void LoadRectMesh()
	{
		Mesh* mesh = new Mesh();
		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);

		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[3] = {};
		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		inputLayoutDesces[2].AlignedByteOffset = 28;
		inputLayoutDesces[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[2].InputSlot = 0;
		inputLayoutDesces[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[2].SemanticName = "TEXCOORD";
		inputLayoutDesces[2].SemanticIndex = 0;

		graphics::Shader* spriteShader = Resources::Find<graphics::Shader>(L"SpriteDefaultShader");
		mesh->SetVertexBufferParams(3, inputLayoutDesces, spriteShader->GetVSBlob()->GetBufferPointer(), spriteShader->GetVSBlob()->GetBufferSize());



		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		min::Resources::Insert(L"RectMesh", mesh);
	}

	void LoadPlayerMesh()
	{
		Mesh* mesh = new Mesh();
		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);

		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[3] = {};
		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		inputLayoutDesces[2].AlignedByteOffset = 28;
		inputLayoutDesces[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[2].InputSlot = 0;
		inputLayoutDesces[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[2].SemanticName = "TEXCOORD";
		inputLayoutDesces[2].SemanticIndex = 0;

		graphics::Shader* spriteShader = Resources::Find<graphics::Shader>(L"AnimationShader");
		mesh->SetVertexBufferParams(3, inputLayoutDesces, spriteShader->GetVSBlob()->GetBufferPointer(), spriteShader->GetVSBlob()->GetBufferSize());


		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		min::Resources::Insert(L"PlayerMesh", mesh);
	}

	void LoadUIMesh()
	{
		Mesh* mesh = new Mesh();
		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);

		vertexes[0].pos = Vector3(200.0f, 100.0f, 0.5f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(300.0f, 100.0f, 0.5f);
		vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(300.0f, 150.0f, 0.5f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(200.0f, 150.0f, 0.5f);
		vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);


		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[3] = {};
		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		inputLayoutDesces[2].AlignedByteOffset = 28;
		inputLayoutDesces[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[2].InputSlot = 0;
		inputLayoutDesces[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[2].SemanticName = "TEXCOORD";
		inputLayoutDesces[2].SemanticIndex = 0;

		graphics::Shader* UIShader = Resources::Find<graphics::Shader>(L"UIShader");
		mesh->SetVertexBufferParams(3, inputLayoutDesces, UIShader->GetVSBlob()->GetBufferPointer(), UIShader->GetVSBlob()->GetBufferSize());


		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		min::Resources::Insert(L"UIMesh", mesh);
	}

	void LoadUIButtonMesh()
	{
		Mesh* mesh = new Mesh();
		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);

		vertexes[0].pos = Vector3(600.0f, 100.0f, 0.5f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(700.0f, 100.0f, 0.5f);
		vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(700.0f, 150.0f, 0.5f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(600.0f, 150.0f, 0.5f);
		vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[3] = {};
		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		inputLayoutDesces[2].AlignedByteOffset = 28;
		inputLayoutDesces[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[2].InputSlot = 0;
		inputLayoutDesces[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[2].SemanticName = "TEXCOORD";
		inputLayoutDesces[2].SemanticIndex = 0;

		graphics::Shader* UIShader = Resources::Find<graphics::Shader>(L"UIShader");
		mesh->SetVertexBufferParams(3, inputLayoutDesces, UIShader->GetVSBlob()->GetBufferPointer(), UIShader->GetVSBlob()->GetBufferSize());


		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		min::Resources::Insert(L"UIButtonMesh", mesh);
	}

	void LoadInventoryMesh()
	{
		Mesh* mesh = new Mesh();
		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);

		vertexes[0].pos = Vector3(900.0f, 100.0f, 0.5f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(950.0f, 100.0f, 0.5f);
		vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(950.0f, 150.0f, 0.5f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(900.0f, 150.0f, 0.5f);
		vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[5] = {};
		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		inputLayoutDesces[2].AlignedByteOffset = 28;
		inputLayoutDesces[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[2].InputSlot = 0;
		inputLayoutDesces[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[2].SemanticName = "TEXCOORD";
		inputLayoutDesces[2].SemanticIndex = 0;

		inputLayoutDesces[3].AlignedByteOffset = 0;		
		inputLayoutDesces[3].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[3].InputSlot = 1;
		inputLayoutDesces[3].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
		inputLayoutDesces[3].InstanceDataStepRate = 1;
		inputLayoutDesces[3].SemanticName = "OFFSET";
		inputLayoutDesces[3].SemanticIndex = 0;

		inputLayoutDesces[4].AlignedByteOffset = 8;
		inputLayoutDesces[4].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[4].InputSlot = 1;
		inputLayoutDesces[4].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
		inputLayoutDesces[4].InstanceDataStepRate = 1;
		inputLayoutDesces[4].SemanticName = "COLOR";
		inputLayoutDesces[4].SemanticIndex = 1;

		graphics::Shader* UIShader = Resources::Find<graphics::Shader>(L"InventoryShader");
		mesh->SetVertexBufferParams(5, inputLayoutDesces, UIShader->GetVSBlob()->GetBufferPointer(), UIShader->GetVSBlob()->GetBufferSize());


		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		min::Resources::Insert(L"SkillInventoryMesh", mesh);
	}

	void LoadSkillInventoryMesh()
	{
		Mesh* mesh = new Mesh();
		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);

		vertexes[0].pos = Vector3(900.0f, 100.0f, 0.5f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(950.0f, 100.0f, 0.5f);
		vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(950.0f, 150.0f, 0.5f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(900.0f, 150.0f, 0.5f);
		vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[3] = {};
		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		inputLayoutDesces[2].AlignedByteOffset = 28;
		inputLayoutDesces[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[2].InputSlot = 0;
		inputLayoutDesces[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[2].SemanticName = "TEXCOORD";
		inputLayoutDesces[2].SemanticIndex = 0;

		graphics::Shader* UIShader = Resources::Find<graphics::Shader>(L"SkillInventoryIconShader");
		mesh->SetVertexBufferParams(3, inputLayoutDesces, UIShader->GetVSBlob()->GetBufferPointer(), UIShader->GetVSBlob()->GetBufferSize());


		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		min::Resources::Insert(L"SkillItemInventoryMesh", mesh);
	}

	void LoadSkillInventoryBGMesh()
	{
		Mesh* mesh = new Mesh();
		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);

		vertexes[0].pos = Vector3(850.0f, 50.0f, 0.5f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(1240.0f, 50.0f, 0.5f);
		vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(1240.0f, 280.0f, 0.5f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(850.0f, 280.0f, 0.5f);
		vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[3] = {};
		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		inputLayoutDesces[2].AlignedByteOffset = 28;
		inputLayoutDesces[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[2].InputSlot = 0;
		inputLayoutDesces[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[2].SemanticName = "TEXCOORD";
		inputLayoutDesces[2].SemanticIndex = 0;

		graphics::Shader* UIShader = Resources::Find<graphics::Shader>(L"UIShader");
		mesh->SetVertexBufferParams(3, inputLayoutDesces, UIShader->GetVSBlob()->GetBufferPointer(), UIShader->GetVSBlob()->GetBufferSize());


		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		min::Resources::Insert(L"SkillItemInventoryBGMesh", mesh);
	}

	void LoadTitleUIMesh()
	{
		Mesh* mesh = new Mesh();
		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);

		vertexes[0].pos = Vector3(700.0f, 500.0f, 0.5f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(900.0f, 500.0f, 0.5f);
		vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(900.0f, 800.0f, 0.5f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(700.0f, 800.0f, 0.5f);
		vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);


		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[3] = {};
		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		inputLayoutDesces[2].AlignedByteOffset = 28;
		inputLayoutDesces[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[2].InputSlot = 0;
		inputLayoutDesces[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[2].SemanticName = "TEXCOORD";
		inputLayoutDesces[2].SemanticIndex = 0;

		graphics::Shader* UIShader = Resources::Find<graphics::Shader>(L"UIShader");
		mesh->SetVertexBufferParams(3, inputLayoutDesces, UIShader->GetVSBlob()->GetBufferPointer(), UIShader->GetVSBlob()->GetBufferSize());


		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		min::Resources::Insert(L"TitleUIMesh", mesh);
	}

	void LoadTitleButtonMesh()
	{
		Mesh* mesh = new Mesh();
		std::vector<graphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);

		vertexes[0].pos = Vector3(750.0f, 590.0f, 0.5f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(850.0f, 590.0f, 0.5f);
		vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(850.0f, 640.0f, 0.5f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(750.0f, 640.0f, 0.5f);
		vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[3] = {};
		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		inputLayoutDesces[2].AlignedByteOffset = 28;
		inputLayoutDesces[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[2].InputSlot = 0;
		inputLayoutDesces[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[2].SemanticName = "TEXCOORD";
		inputLayoutDesces[2].SemanticIndex = 0;

		graphics::Shader* UIShader = Resources::Find<graphics::Shader>(L"TitleShader");
		mesh->SetVertexBufferParams(3, inputLayoutDesces, UIShader->GetVSBlob()->GetBufferPointer(), UIShader->GetVSBlob()->GetBufferSize());


		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		min::Resources::Insert(L"TitleButtonMesh", mesh);
	}

	void LoadMeterails()
	{
		Material* triangleMaterial = new Material();
		triangleMaterial->SetShader(min::Resources::Find<graphics::Shader>(L"TriangleShader"));
		min::Resources::Insert(L"TriangleMaterial", triangleMaterial);

		Material* spriteMaterial = new Material();
		spriteMaterial->SetShader(min::Resources::Find<graphics::Shader>(L"SpriteDefaultShader"));
		min::Resources::Insert(L"SpriteDefaultMaterial", spriteMaterial);

		Material* AnimationMaterial = new Material();
		AnimationMaterial->SetShader(min::Resources::Find<graphics::Shader>(L"AnimationShader"));
		min::Resources::Insert(L"AnimationMaterial", AnimationMaterial);

		Material* UIMaterial = new Material();
		UIMaterial->SetShader(min::Resources::Find<graphics::Shader>(L"UIShader"));
		min::Resources::Insert(L"UIMaterial", UIMaterial);

		Material* InventoryMaterial = new Material();
		InventoryMaterial->SetShader(min::Resources::Find<graphics::Shader>(L"InventoryShader"));
		min::Resources::Insert(L"SkillInventoryMaterial", InventoryMaterial);

		Material* SkillInventoryMaterial = new Material();
		SkillInventoryMaterial->SetShader(min::Resources::Find<graphics::Shader>(L"SkillInventoryIconShader"));
		min::Resources::Insert(L"SkillItemInventoryMaterial", SkillInventoryMaterial);

		Material* TitleMaterial = new Material();
		TitleMaterial->SetShader(min::Resources::Find<graphics::Shader>(L"TitleShader"));
		min::Resources::Insert(L"TitleMaterial", TitleMaterial);
	}

	void LoadMeshes()
	{
		LoadTriangleMesh();
		LoadRectMesh();
		LoadPlayerMesh();
		LoadUIMesh();
		LoadUIButtonMesh();
		LoadInventoryMesh();
		LoadSkillInventoryMesh();
		LoadSkillInventoryBGMesh();
		LoadTitleUIMesh();
		LoadTitleButtonMesh();
	}
	void LoadShaders()
	{
		min::Resources::Load<graphics::Shader>(L"TriangleShader", L"..\\Shaders_SOURCE\\Triangle");
		min::Resources::Load<graphics::Shader>(L"SpriteDefaultShader", L"..\\Shaders_SOURCE\\SpriteDefault");
		min::Resources::Load<graphics::Shader>(L"WireframeShader", L"..\\Shaders_SOURCE\\Wireframe");
		min::Resources::Load<graphics::Shader>(L"AnimationShader", L"..\\Shaders_SOURCE\\Animation");
		min::Resources::Load<graphics::Shader>(L"UIShader", L"..\\Shaders_SOURCE\\UI");
		min::Resources::Load<graphics::Shader>(L"InventoryShader", L"..\\Shaders_SOURCE\\inventory");
		min::Resources::Load<graphics::Shader>(L"SkillInventoryIconShader", L"..\\Shaders_SOURCE\\SkillInventoryIcon");
		min::Resources::Load<graphics::Shader>(L"TitleShader", L"..\\Shaders_SOURCE\\Title");
	}

	void LoadConstantBuffers()
	{

		constantBuffers[CBSLOT_TRANSFORM] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[CBSLOT_TRANSFORM]->Create(sizeof(TransformCB));

		constantBuffers[CBSLOT_ANIMATION] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[CBSLOT_ANIMATION]->Create(sizeof(AnimationCB));

		constantBuffers[CBSLOT_UI] = new ConstantBuffer(eCBType::UI);
		constantBuffers[CBSLOT_UI]->Create(sizeof(UICB));

		constantBuffers[CBSLOT_Skill] = new ConstantBuffer(eCBType::Skill);
		constantBuffers[CBSLOT_Skill]->Create(sizeof(SkillCB));

		constantBuffers[CBSLOT_Title] = new ConstantBuffer(eCBType::Title);
		constantBuffers[CBSLOT_Title]->Create(sizeof(TitleCB));
	}
	void LoadInstanceBuffers()
	{
		InstanceBuffers[IBSLOT_INVENTORY] = new InstanceBuffer(eIBType::Inventory);
		InstanceBuffers[IBSLOT_INVENTORY]->Create(sizeof(InstanceData));
	}

	void LoadStates()
	{
#pragma region sampler state
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());

		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::PostProcess].GetAddressOf());

		GetDevice()->BindSamplers((UINT)eSamplerType::Point, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSamplers((UINT)eSamplerType::Linear, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());
		GetDevice()->BindSamplers((UINT)eSamplerType::Anisotropic, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSamplers((UINT)eSamplerType::PostProcess, 1, samplerStates[(UINT)eSamplerType::PostProcess].GetAddressOf());
#pragma endregion
#pragma region rasterize state
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.AntialiasedLineEnable = false;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		rsDesc.DepthBias = 0;
		rsDesc.DepthBiasClamp = 0.0f;
		rsDesc.DepthClipEnable = true;
		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.FrontCounterClockwise = false;
		rsDesc.MultisampleEnable = false;
		rsDesc.ScissorEnable = false;
		rsDesc.SlopeScaledDepthBias = 0.0f;
		GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRasterizerState::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRasterizerState::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRasterizerState::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRasterizerState::Wireframe].GetAddressOf());
#pragma endregion
#pragma region blend state
		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBlendState::AlphaBlend].GetAddressOf());

		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBlendState::OneOne].GetAddressOf());

		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_DEST_COLOR;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ZERO;
		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBlendState::ColorZero].GetAddressOf());

#pragma endregion
#pragma region depthstencil state
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, depthStencilStates[(UINT)eDepthStencilState::LessEqual].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, depthStencilStates[(UINT)eDepthStencilState::DepthNone].GetAddressOf());


#pragma endregion
	}
	void LoadFrimitiveBatch()
	{
		primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(GetDevice()->GetID3D11DeviceContext().Get());
		batchEffect = std::make_unique<BasicEffect>(GetDevice()->GetID3D11Device().Get());
		batchEffect->SetVertexColorEnabled(true);
	}

	void Initialize()
	{
		LoadStates();
		LoadShaders();
		LoadMeshes();
		LoadMeterails();
		LoadConstantBuffers();
		LoadInstanceBuffers();
		LoadFrameBuffer();
		LoadFrimitiveBatch();
	}
	void Release()
	{
		//inputLayouts->Release();
		//delete mesh;
		delete FrameBuffer;
		FrameBuffer = nullptr;

		for (UINT i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}
	}
}
