#pragma once
#include "..\\MinhoEngine_SOURCE\\MinScript.h"
#include "MinTransform.h"

namespace min
{
	class SecondSkillScript :public Script
	{
	public:
		enum class eState
		{
			idle,
			Run,
			Hit,
		};

		struct VectorSkill {
			float x, y;

			VectorSkill() : x(0), y(0) {}
			VectorSkill(float x, float y) : x(x), y(y) {}

			// 벡터 회전 변환 (pivot 기준)
			VectorSkill Rotate(float angle, VectorSkill pivot) const {
				float rad = angle * (3.1415926535f / 180.0f);
				float s = sin(rad);
				float c = cos(rad);

				// 중심을 원점으로 이동
				float localX = x - pivot.x;
				float localY = y - pivot.y;

				// 회전 변환
				float rotatedX = localX * c - localY * s;
				float rotatedY = localX * s + localY * c;

				// 다시 원래 위치로 이동
				return VectorSkill(rotatedX + pivot.x, rotatedY + pivot.y);
			}
		};

		SecondSkillScript();
		~SecondSkillScript();

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
		void SetSetting(Vector3 pivot, Vector3 Start);
		void SetDirection(bool dir) { mDirection = dir; }
		void UpdateSetting();

	private:
		eState mState;
		class Animator* mAnimator;

		VectorSkill mPivot; // 캐릭터 위치
		VectorSkill mStart; // 스킬 시작지점

		float mAngle;

		bool mDirection;

		float mTime;
		float mDuration;
		float mDeltaAngle;
	};
}