#pragma once
#include "MinComponent.h"

namespace min
{
	using namespace min::math;
	class Camera : public Component
	{
	public:
		Vector2 CalculatePosition(Vector2 pos) { return pos - mDistance; };
		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Rander(HDC hdc) override;

		void SetTarget(GameObject* target) { mTarget = target; }

	private:
		//std::vector<GameObject*> mGameObjects;
		class GameObject* mTarget;

		Vector2 mDistance;
		Vector2 mResolution;
		Vector2 mLookPosition;

	};
}

