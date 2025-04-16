#pragma once
#include "MinResource.h"
#include "MinVertexBuffer.h"
#include "MinInputLayout.h"
#include "MinIndexBuffer.h"

namespace min
{
	class Mesh : public Resource
	{
	public:
		struct MeshData
		{
			MeshData();
			~MeshData();

			D3D11_PRIMITIVE_TOPOLOGY mTopology;
			std::vector<graphics::Vertex> vertices;
			std::vector<UINT> indices;
		};

		Mesh();
		virtual ~Mesh();

		virtual HRESULT	Save(const std::wstring path) override;
		virtual HRESULT Load(const std::wstring path) override;

		bool CreateVB(const std::vector<graphics::Vertex>& vertices);
		bool CreateIB(const std::vector<UINT>& indices);
		void SetVertexBufferParams(UINT vertexCount, D3D11_INPUT_ELEMENT_DESC* layout, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength);
		UINT GetIndexCount() const { return mIB.GetIndexCount(); }
		void Bind();
		void BindWithInstancing(graphics::eIBType eType);

	private:
		graphics::InputLayout mInputLayout;
		graphics::VertexBuffer mVB;
		graphics::IndexBuffer mIB;

		MeshData mData;
	};
}
