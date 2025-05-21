#pragma once
#include "..\\MinhoEngine_SOURCE\\MinScript.h"
#include "..\\MinhoEngine_SOURCE\MinSkillInventory.h"

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

		void CoolTimeCheck();
		void CheakPosition();

		void SetFieldSize(Vector3 Size) { mFieldSize = Size; }

	public :
		static bool exChangeSkill;


	private:
		void Idle();
		void move();
		void SkillActive();
		void Jumping();
		void MakeSkill_Info();

	private:
		eState mState;
		class Animator* mAnimator;

		Vector3 mFieldSize;
		//class Effect* Shadow;

		float mDelayTime;
		float mGravity;
		float mSpeed;

		std::vector<float> mCoolTime;

		bool mMoveLock;
		bool isJump;
		bool mFront; // true 면 오른쪽 , false 면 왼쪽

		float mJumpingTime;


		std::vector<SkillInventory::InventoryInfo> mSkillInfo;
		//void (*StartEvent)();
		//void (*CompleteEvent)();
		//void (*EndEvent)();
	};
}

