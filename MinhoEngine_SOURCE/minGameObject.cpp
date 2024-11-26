#include "minGameObject.h"
namespace min {
	GameObject::GameObject()
		:mX(0.0f)
		,mY(0.0f)
	{

	}
	GameObject::~GameObject()
	{

	}

	void GameObject::Update()
	{
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
	void GameObject::LateUpdate()
	{
	}
	void GameObject::Rander(HDC mHdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));// 파랑배경 브러쉬 생성
		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, brush); // 파랑 브러쉬 DC에 선택 후 기존 흰색 브러쉬 반환

		HPEN redpen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldpen = (HPEN)SelectObject(mHdc, redpen);

		SelectObject(mHdc, oldpen);

		Rectangle(mHdc, 100 + mX, 100 + mY, 200 + mX, 200 + mY);
	}

	void GameObject::Update_2()
	{
		if (GetAsyncKeyState('A') & 0x8000) {
			mX -= 0.01f;
		}
		if (GetAsyncKeyState('D') & 0x8000) {
			mX += 0.01f;
		}
		if (GetAsyncKeyState('W') & 0x8000) {
			mY -= 0.01f;
		}
		if (GetAsyncKeyState('S') & 0x8000) {
			mY += 0.01f;
		}
	}
	void GameObject::LateUpdate_2()
	{
	}
	void GameObject::Rander_2(HDC mHdc)
	{
		HBRUSH brush_2 = CreateSolidBrush(RGB(255, 0, 000));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, brush_2); // 파랑 브러쉬 DC에 선택 후 기존 흰색 브러쉬 반환

		HPEN redpen_2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldpen = (HPEN)SelectObject(mHdc, redpen_2);

		SelectObject(mHdc, oldpen);

		Ellipse(mHdc, 1500 + mX, 800 + mY, 1600 + mX, 900 + mY);
	}
}