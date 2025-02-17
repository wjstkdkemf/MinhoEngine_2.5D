#pragma once
#include "MinResource.h"

namespace min
{
	class Mesh : public Resource
	{
	public:
		struct Data
		{

		};

		Mesh();
		virtual ~Mesh();

		virtual HRESULT Load(const std::wstring path) override;
	};
}
