#pragma once
#include "..\\MinhoEngine_SOURCE\\MinScript.h"

namespace min
{
	class EnemyScript : public Script
	{
	public:
		enum class eState
		{
			idle,
			Walk,
			Jump,
			GiveWater,
			Attack,
			Max = 16,
		};

		EnemyScript();
		~EnemyScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:

	private:
		eState mState;
		class Animator* mAnimator;

		float HP;
		//void (*StartEvent)();
		//void (*CompleteEvent)();
		//void (*EndEvent)();
	};
}

