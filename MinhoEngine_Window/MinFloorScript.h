#pragma once
#include "..\\MinhoEngine_SOURCE\\MinScript.h"

namespace min
{
	class FloorScript : public Script
	{
	public:

		FloorScript();
		~FloorScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
	};
}


