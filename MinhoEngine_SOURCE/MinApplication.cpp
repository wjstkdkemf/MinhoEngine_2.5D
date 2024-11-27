#include "MinApplication.h"
#include "Mininput.h"


namespace min {
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
	{
	}
	Application::~Application()
	{
		
	}
	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);

		input::Initailize();
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

		mPlayer[0].Update();
		mPlayer[1].Update_2();
	}
	void Application::LateUpdate()
	{
	}
	void Application::Rander()
	{
		mPlayer[0].Rander(mHdc);
		mPlayer[1].Rander_2(mHdc);
	}
}
