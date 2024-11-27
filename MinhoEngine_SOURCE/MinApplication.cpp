#include "MinApplication.h"
#include "Mininput.h"
#include "MinTime.h"


namespace min {
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mWidth(0)
		, mHeight(0)
		, mBackHdc(NULL)
		, mBackBitmap(NULL)
	{
	}
	Application::~Application()
	{
		
	}
	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);


		RECT rect = {0, 0, width, height};
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(mHwnd, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top, 0);
		ShowWindow(mHwnd, true);

		mBackBitmap = CreateCompatibleBitmap(mHdc
			, mWidth
			, mHeight);

		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);

		input::Initailize();
		Time::Initailize();
	}
	void Application::Run()
	{
		Update();
		LateUpdate();
		Rander();
	}
	void Application::Update()
	{
		input::Update();
		Time::Update();

		mPlayer[0].Update();
		mPlayer[1].Update_2();
	}
	void Application::LateUpdate()
	{
	}
	void Application::Rander()
	{
		Rectangle(mBackHdc, 0, 0, 1920, 1080);

		Time::Render(mBackHdc);
		mPlayer[0].Rander(mBackHdc);
		mPlayer[1].Rander_2(mBackHdc);

		BitBlt(mHdc, 0, 0, mWidth, mHeight
		, mBackHdc, 0, 0, SRCCOPY);
	}
}
