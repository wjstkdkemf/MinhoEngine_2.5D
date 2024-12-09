#pragma once
#include "..\\MinhoEngine_SOURCE\\MinScript.h"

namespace min
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Rander(HDC hdc) override;

	private:

	};
}

