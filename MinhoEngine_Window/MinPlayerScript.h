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
		virtual void Render() override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

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

