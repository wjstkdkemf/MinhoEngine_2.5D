#include "MinUIButton.h"
#include "Mininput.h"

namespace min
{
	UIButton::UIButton()
		: UIBase(enums::eUIType::Button)
	{
	}
	UIButton::~UIButton()
	{
	}
	void UIButton::OnInit()
	{
		SetPos(Vector2(200.0f, 200.0f));
		SetSize(Vector2(200.0f, 200.0f));

		mOnClick = std::bind(&UIButton::ButtonClick, this);
	}
	void UIButton::OnActive()
	{
	}
	void UIButton::OnInActive()
	{
	}
	void UIButton::OnUpdate()
	{
		Vector2 mousePos = input::GetMousePosition();
		
		if (mPosition.x <= mousePos.x && mousePos.x <= mPosition.x + mSize.x
			&& mPosition.y <= mousePos.y && mousePos.y <= mPosition.y + mSize.y)
		{
			mbMouseOn = true;
		}
		else
		{
			mbMouseOn = false;
		}

		if (input::GetKeyDown(eKeyCode::Lbutton))
		{
			if (mbMouseOn)
			{
				mOnClick();
			}
		}
	}
	void UIButton::OnLateUpdate()
	{
	}
	void UIButton::OnRender(HDC hdc)
	{
		::Rectangle(hdc
			, mPosition.x, mPosition.y
			, mPosition.x + mSize.x, mPosition.y + mSize.y);
	}
	void UIButton::OnClear()
	{
	}
	void UIButton::ButtonClick()
	{
	}
}