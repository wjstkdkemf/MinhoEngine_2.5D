#include "MinVertexBuffer.h"
#include "MinRenderer.h"

namespace min::graphics
{
	VertexBuffer::VertexBuffer()
	{
	}
	VertexBuffer::~VertexBuffer()
	{
	}
	bool VertexBuffer::Create(const std::vector<Vertex>& vertexes)
	{
#pragma region vertex buffer desc
		desc.ByteWidth = sizeof(Vertex) * (UINT)vertexes.size();
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sub = { };
		sub.pSysMem = vertexes.data();

#pragma endregion
		if (!(GetDevice()->CreateBuffer(&desc, &sub, buffer.GetAddressOf())))
			assert(NULL);

		return true;
	}
	void VertexBuffer::Bind()
	{
		UINT offset = 0;
		UINT vectexSize = sizeof(Vertex);
		GetDevice()->BindVertexBuffer(0, 1, buffer.GetAddressOf(), &vectexSize, &offset);
	}
	void VertexBuffer::BindWithIncetancing(eIBType eType)
	{
		graphics::InstanceBuffer* ib = renderer::InstanceBuffers[IBSLOT_INVENTORY];

		ID3D11Buffer* Buffers[2] = { buffer.Get() , ib->buffer.Get() };
		UINT offset[2] = { 0, 0 };
		UINT vertexSize[2] = { sizeof(Vertex), sizeof(InstanceData) };

		//GetDevice()->GetID3D11DeviceContext()->IASetVertexBuffers(0, 2, Buffers, vertexSize, offset);
		GetDevice()->BindVertexBuffer(0, 2, Buffers, vertexSize, offset);
		//GetDevice()->BindVertexBufferWithInstanceBuffer(0, 2, Buffers, vertexSize, offset);
	}
}