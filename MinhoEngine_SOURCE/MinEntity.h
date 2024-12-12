#pragma once
#include "commoninclude.h"

using namespace min::math;

namespace min {
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; };
		std::wstring& GetName() { return mName; };

	private:
		std::wstring mName;
	};
}

 