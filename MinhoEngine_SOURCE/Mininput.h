#pragma once
#include "commoninclude.h"

namespace min {
	enum class eKeyState {
		Down,
		Pressed,
		Up,
		None,
	};

	enum class eKeyCode {
		Q = 0x51, W = 0x57, E = 0x45, R = 0x52, T = 0x54,
		Y = 0x59, U = 0x55, I = 0x49, O = 0x4F, P = 0x50,
		A = 0x41, S = 0x53, D = 0x44, F = 0x46, G = 0x47,
		H = 0x48, J = 0x4A, K = 0x4B, L = 0x4C,
		Z = 0x5A, X = 0x58, C = 0x43, V = 0x56, B = 0x42,
		N = 0x4E, M = 0x4D,

		Left = VK_LEFT, Right = VK_RIGHT, Down = VK_DOWN, Up = VK_UP,
		LButton = VK_LBUTTON, MButton = VK_MBUTTON, RButton = VK_RBUTTON,

		LeftShift = VK_LSHIFT, Leftcontrol = VK_LCONTROL, LeftAlt = VK_LMENU,
		RightShift = VK_RSHIFT, RightControl = VK_RCONTROL, RightAlt = VK_RMENU,

		End = VK_END
	};

	enum class eMouseCode
	{
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	};

	class input
	{
	public:
		struct Key {
			eKeyCode keyCode;
			eKeyState state;
			int VK_KeyCode;
			bool bPressed;
		};

		static void Initailize();
		static void Update();


		__forceinline static bool GetKeyDown(eKeyCode code) { return mKeys[(UINT)code].state == eKeyState::Down; };
		__forceinline static bool GetKeyUp(eKeyCode code) { return mKeys[(UINT)code].state == eKeyState::Up; };
		__forceinline static bool GetKey(eKeyCode code) { return mKeys[(UINT)code].state == eKeyState::Pressed; };
		static math::Vector2 GetMousePosition() { return mMousePosition; }

	private:
		static void createKeys();
		static void updateKeys();
		static void updateKey(input::Key& key);
		static bool isKeyDown(eKeyCode code);
		static void updateKeyDown(input::Key& key);
		static void updateKeyUp(input::Key& key);
		static void getMousePositionByWindow();
		static void claerKey();
		

	private:
		//eKeyState mState = eKeyState::Up;
		static std::vector<Key> mKeys;	//static -> 정적변수(전역변수와 같이 사용하도록 하기위함)
										//but, 하나의 클라스 안에서만 전역변수와 같이 사용할 수 있다.
										//그리고 전역변수와 같기때문에 초기화를 해주어야한다.
										//즉 여러개의 클래스를 만들어도 static으로 선언된 변수는 하나의 주소를 참조하기때문에
										//모두 같은 값을 참조할 수 있게된다.
		static math::Vector2 mMousePosition;
	};
}

