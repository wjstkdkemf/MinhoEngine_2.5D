#pragma once
#include "..\\MinhoEngine_SOURCE\\MinScript.h"
#include "MinTransform.h"

namespace min
{
	class FirstSkillScript :public Script
	{
	public:
		enum class eState
		{
			idle,
			Run,
			Hit,
		};

		FirstSkillScript();
		~FirstSkillScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SkillPlayAnimation();
		void Move(Transform* tr);

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void SetDuration(float Duration) { mDuration = Duration; }
		void SetDirection(bool dir) { mDirection = dir; }

	private:

	private:
		eState mState;
		class Animator* mAnimator;

		float mTime;
		float mDuration;

		bool mDirection;
	};
}

