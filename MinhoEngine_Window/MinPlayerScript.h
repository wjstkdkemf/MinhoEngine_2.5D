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
			Jump,
			Skill,
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
		void SkillActive();
		void Jumping();
		void makeShadow();

	private:
		eState mState;
		class Animator* mAnimator;
		class GameObject* Skill_info;
		//class Effect* Shadow;

		float mDelayTime;
		float mGravity;

		bool isJump;

		bool mFront; // true 면 오른쪽 , false 면 왼쪽

		float mJumpingTime;
		//void (*StartEvent)();
		//void (*CompleteEvent)();
		//void (*EndEvent)();
	};
}

