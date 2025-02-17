#pragma once
#include "MinResource.h"
#include "MinVertexBuffer.h"
#include "MinIndexBuffer.h"

namespace min
{
	class Mesh : public Resource
	{
	public:
		struct Data
		{
			Data();
			~Data();

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
		void Bind();

	private:
		graphics::VertexBuffer mVB;
		graphics::IndexBuffer mIB;

		Data mData;
	};
}
