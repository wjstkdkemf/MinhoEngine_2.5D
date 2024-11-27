#pragma once
#include "minGameObject.h"

namespace min{
	class Application
	{
	public:
		Application();
		~Application();
		void Initialize(HWND hwnd, UINT width, UINT height);
		void Run();

		void Update();
		void LateUpdate();

		void Rander();

	private:
		HWND mHwnd;
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;

		GameObject mPlayer[2];
		static std::vector<GameObject>Bullet;
	};
}

