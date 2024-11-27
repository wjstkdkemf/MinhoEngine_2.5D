#include "Mininput.h"


namespace min {
	std::vector<input::Key> input::mKeys = {};

	int ASCII[(UINT)eKeyCode::End] {
		'Q','W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT,VK_RIGHT,VK_DOWN,VK_UP,
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
		if (isKeyDown(key.keyCode)){
			updateKeyDown(key);
		}
		else {
			updateKeyUp(key);
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
}
