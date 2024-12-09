#pragma once
#include "MinComponent.h"

namespace min
{
	class Script : public Component
	{
	public:
		Script();
		~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Rander(HDC hdc) override;

	private:

	};
}

