#pragma once
#include "commoninclude.h"

namespace min{
	class Application
	{
	public:
		Application();
		~Application();
		void Initialize(HWND hwnd);
		void Run();

		void Update();
		void LateUpdate();

		void Rander();

	private:
		HWND mHwnd;
		HDC mHdc;

		float mSpeed;
		float mX;
		float mY;
	};
}

