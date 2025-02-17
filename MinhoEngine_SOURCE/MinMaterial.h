#pragma once
#include "MinResource.h"

namespace min
{
	class Material : public Resource
	{
	public:
		struct Data
		{

		};

		Material();
		virtual ~Material();

		virtual HRESULT Load(const std::wstring path) override;
	};
}
