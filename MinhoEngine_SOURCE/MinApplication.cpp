#include "MinApplication.h"


namespace min {
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mSpeed(0.0f)
		, mX(0.0f) 
		, mY(0.0f) 
	{
	}
	Application::~Application()
	{
		
	}
	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);
	}
	void Application::Run()
	{
		Update();
		LateUpdate();
		Rander();
	}
	void Application::Update()
	{
		mSpeed += 0.01f;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			mX -= 0.01f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			mX += 0.01f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			mY -= 0.01f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			mY += 0.01f;
		}
	}
	void Application::LateUpdate()
	{
	}
	void Application::Rander()
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));// 파랑배경 브러쉬 생성
		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, brush); // 파랑 브러쉬 DC에 선택 후 기존 흰색 브러쉬 반환

		HPEN redpen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldpen = (HPEN)SelectObject(mHdc, redpen);

		SelectObject(mHdc, oldpen);

		Rectangle(mHdc, 100 + mX, 100 + mY, 200 + mX , 200 +mY);

	}
}
