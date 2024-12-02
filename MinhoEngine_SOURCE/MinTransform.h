#pragma once

#include "MinEntity.h"
#include "MinComponent.h"



namespace min {
	using namespace math;
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander(HDC hdc) override;

		void SetPos(Vector2 pos) { mPosition.x = pos.x; mPosition.y = pos.y; }
		Vector2 GetPosition() { return mPosition; }
	private:
		Vector2 mPosition;
	};
}

