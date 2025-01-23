#include "Mininput.h"
#include "MinApplication.h"

extern min::Application application;

namespace min {
	std::vector<input::Key> input::mKeys = {};
	math::Vector2 input::mMousePosition = math::Vector2::One;

	int ASCII[(UINT)eKeyCode::End] {
		'Q','W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT,VK_RIGHT,VK_DOWN,VK_UP,VK_SPACE,
		VK_LBUTTON,VK_MBUTTON, VK_RBUTTON,
	};

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
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++) {
			Key key = {};
			key.bPressed = false;
			key.state = eKeyState::None;
			key.keyCode = (eKeyCode)i;

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
		return GetAsyncKeyState(ASCII[(UINT)code]) & 0x8000;
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
		ScreenToClient(application.GetHwnd(), &mousePos);

		UINT width = application.GetWidth();
		UINT height = application.GetHeight();

		mMousePosition.x = -1.0f;
		mMousePosition.y = -1.0f;

		if (mousePos.x > 0 && mousePos.x < width)
		{
			mMousePosition.x = mousePos.x;
		}
		if (mousePos.y > 0 && mousePos.y < height)
		{
			mMousePosition.y = mousePos.y;
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
