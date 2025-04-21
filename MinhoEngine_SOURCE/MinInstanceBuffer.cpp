#include "MinInstanceBuffer.h"


namespace min::graphics
{
	InstanceBuffer::InstanceBuffer(eIBType type)
		: mType(type)
		, mSize(0)
		, mInventorySize(30)
	{
	}
	InstanceBuffer::~InstanceBuffer()
	{
	}
	bool InstanceBuffer::Create(UINT size, void* data)
	{
		mSize = size;
		desc.ByteWidth = size * mInventorySize;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = data;

		bool succes = false;
		if (data == NULL)
			succes = GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf());
		else
			succes = GetDevice()->CreateBuffer(&desc, &sub, buffer.GetAddressOf());

		if (!succes)
			assert(NULL);

		return true;
	}
	void InstanceBuffer::SetData(void* data) const
	{
		GetDevice()->SetDataGpuBuffer(buffer.Get(), data, mSize * mInventorySize); //mSize * mInventorySize
	}
	void InstanceBuffer::Bind()
	{
		UINT offset = 0;
		UINT vectexSize = sizeof(Vertex);
		
		GetDevice()->BindVertexBuffer(0, 1, buffer.GetAddressOf(), &vectexSize, &offset);
	}
}