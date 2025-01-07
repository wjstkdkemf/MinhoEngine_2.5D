#pragma once
#include "..\\MinhoEngine_SOURCE\\MinScript.h"

namespace min
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			idle,
			Walk,
			Sleep,
			GiveWater,
			Attack,
			Max = 16,
		};

		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

		void PlayerEffect();

	private:
		void Idle();
		void move();
		void giveWater();

	private:
		eState mState;
		class Animator* mAnimator;



		//void (*StartEvent)();
		//void (*CompleteEvent)();
		//void (*EndEvent)();
	};
}

