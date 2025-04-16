#pragma once
#include "MinGraphicDevice_DX11.h"

namespace min::graphics
{
	class VertexBuffer : public GpuBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		bool Create(const std::vector<Vertex>& vertexes);
		void Bind();
		void BindWithIncetancing(eIBType eType);

	private:
	};
}

