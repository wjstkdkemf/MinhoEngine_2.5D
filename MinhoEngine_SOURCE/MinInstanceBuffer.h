#pragma once
#include "MinGraphicDevice_DX11.h"

namespace min::graphics
{
	class InstanceBuffer : public GpuBuffer
	{
	public:
		InstanceBuffer(eIBType type);
		~InstanceBuffer();

		bool Create(UINT size, void* data = NULL);
		void SetData(void* data) const;
		void Bind();

	private:
		UINT mSize;
		UINT mInventorySize;
		eIBType mType;
	};
}

