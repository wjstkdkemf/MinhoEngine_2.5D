#include "minGameObject.h"
#include "mininput.h"

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
		if (input::GetKey(eKeyCode::A)) {
			mX -= 0.01f;
		}
		if (input::GetKey(eKeyCode::D)) {
			mX += 0.01f;
		}
		if (input::GetKey(eKeyCode::W)) {
			mY -= 0.01f;
		}
		if (input::GetKey(eKeyCode::S)) {
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

		/*HPEN redpen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldpen = (HPEN)SelectObject(mHdc, redpen);

		SelectObject(mHdc, oldpen);*/

		Rectangle(mHdc, 100 + mX, 100 + mY, 200 + mX, 200 + mY);

		SelectObject(mHdc, oldBrush);
		DeleteObject(brush);
	}

	void GameObject::Update_2()
	{
		if (input::GetKey(eKeyCode::Left)) {
			mX -= 0.01f;
		}
		if (input::GetKey(eKeyCode::Right)) {
			mX += 0.01f;
		}
		if (input::GetKey(eKeyCode::Up)) {
			mY -= 0.01f;
		}
		if (input::GetKey(eKeyCode::Down)) {
			mY += 0.01f;
		}
	}
	void GameObject::LateUpdate_2()
	{
	}
	void GameObject::Rander_2(HDC mHdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, brush); // 파랑 브러쉬 DC에 선택 후 기존 흰색 브러쉬 반환

		/*HPEN redpen_2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldpen = (HPEN)SelectObject(mHdc, redpen_2);*/

		Ellipse(mHdc, 1500 + mX, 800 + mY, 1600 + mX, 900 + mY);

		SelectObject(mHdc, oldBrush);
		DeleteObject(brush);
	}
}