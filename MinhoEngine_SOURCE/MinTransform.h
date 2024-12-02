#pragma once
#include "MinEntity.h"
#include"MinComponent.h"

namespace min {
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander(HDC hdc) override;

		void SetPos(int x, int y) { mX = x; mY = y; }
		int GetX() { return mX; };
		int GetY() { return mY; };
	private:
		int mX;
		int mY;
	};
}

