#pragma once
#include "minGameObject.h"

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

		GameObject mPlayer[2];
	};
}

