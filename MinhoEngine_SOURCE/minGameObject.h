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

		void Update_2();
		void LateUpdate_2();
		void Rander_2(HDC mHdc);


	private:
		float mX;
		float mY;
	};
}

