#pragma once
#include "..\\MinhoEngine_SOURCE\\MinScript.h"
#include "..\\MinhoEngine_SOURCE\\MinTransform.h"

namespace min
{
	class CatScript : public Script
	{
	public:
		enum class eState
		{
			SitDown,
			Walk,
			Sleep,
			LayDown,
			Attack,
			Max = 16,
		};

		enum class eDirection
		{
			Left,
			Right,
			Up,
			Down,
			End,
		};

		CatScript();
		~CatScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void setPlayer(GameObject* player) { mPlayer = player; }



		Vector2 mDest;

	private:
		void sitDown();
		void move();
		void layDown();
		void playWalkAnimationByDirection(eDirection dir);
		void trnaslate(Transform* tr);

		

	private:
		eState mState;
		class Animator* mAnimator;
		float mTime;
		float mDeathTime;
		eDirection mDirection;

		GameObject* mPlayer;
		float mRadian;
	};
}



