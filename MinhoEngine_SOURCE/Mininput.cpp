#include "Mininput.h"
#include "MinApplication.h"

extern min::Application application;

namespace min {
	std::vector<input::Key> input::mKeys = {};
	math::Vector2 input::mMousePosition = math::Vector2::One;

	void input::Initailize()
	{
		//mKeys.resize((UINT)eKeyCode::End);
		createKeys();
	}

	void input::Update()
	{
		updateKeys();
	}
	void input::createKeys()
	{
		for (int vk = 0; vk <= 0xFF; ++vk) {
			eKeyCode keyCode = static_cast<eKeyCode>(vk);

			Key key = {};
			key.bPressed = false;
			key.state = eKeyState::None;
			key.keyCode = keyCode;
			key.VK_KeyCode = vk;

			mKeys.push_back(key);
		}
	}
	void input::updateKeys()
	{
		std::for_each(mKeys.begin(), mKeys.end(),
			[](Key & key) -> void
			{
				updateKey(key);
			});
	}
	void input::updateKey(input::Key& key)
	{
		if (GetFocus())
		{
			if (isKeyDown(key.keyCode)) {
				updateKeyDown(key);
			}
			else {
				updateKeyUp(key);
			}
			getMousePositionByWindow();
		}
		else
		{
			claerKey();
		}
	}
	bool input::isKeyDown(eKeyCode code)
	{
		return GetAsyncKeyState(static_cast<int>(code)) & 0x8000;
	}
	void input::updateKeyDown(input::Key& key)
	{
		if (key.bPressed == true) 
			key.state = eKeyState::Pressed;
		else 
			key.state = eKeyState::Down;

		key.bPressed = true;
	}
	void input::updateKeyUp(input::Key& key)
	{
		if (key.bPressed == true)
			key.state = eKeyState::Up;
		else
			key.state = eKeyState::None;

		key.bPressed = false;
	}
	void input::getMousePositionByWindow()
	{
		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ScreenToClient(application.GetWindow().GetHwnd(), &mousePos);

		UINT width = application.GetWindow().GetWidth();
		UINT height = application.GetWindow().GetHeight();

		mMousePosition.x = -1.0f;
		mMousePosition.y = -1.0f;

		if ((UINT)mousePos.x > 0 && (UINT)mousePos.x < width)
		{
			mMousePosition.x = (float)mousePos.x;
		}
		if ((UINT)mousePos.y > 0 && (UINT)mousePos.y < height)
		{
			mMousePosition.y = (float)mousePos.y;
		}
	}
	void input::claerKey()
	{
		for (Key& key : mKeys)
		{
			if (key.state == eKeyState::Down || key.state == eKeyState::Pressed)
				key.state = eKeyState::Up;
			else if (key.state == eKeyState::Up)
				key.state = eKeyState::None;

			key.bPressed = false;
		}
	}
}
