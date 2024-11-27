#pragma once
#include "commoninclude.h"

namespace min {
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void Update();
		void LateUpdate();
		void Rander(HDC mHdc);
		void ShotRander(HDC mHdc);

		void Update_2();
		void LateUpdate_2();
		void Rander_2(HDC mHdc);

		bool GetShot() { return shot; };
		void SetShot(bool button);

	private:
		float mX;
		float mY;
		float speed;
		static bool shot;
	};
}

