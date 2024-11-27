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
		Q,W,E,R,T,Y,U,I,O,P,
		A,S,D,F,G,H,J,K,L,
		Z,X,C,V,B,N,M,
		Left,Right,Down,Up,
		End,
	};

	class input
	{
	public:
		struct Key {
			eKeyCode keyCode;
			eKeyState state;
			bool bPressed;
		};

		static void Initailize();
		static void Update();


		static bool GetKeyDown(eKeyCode code) { return mKeys[(UINT)code].state == eKeyState::Down; };
		static bool GetKeyUp(eKeyCode code) { return mKeys[(UINT)code].state == eKeyState::Up; };
		static bool GetKey(eKeyCode code) { return mKeys[(UINT)code].state == eKeyState::Pressed; };

	private:
		static void createKeys();
		static void updateKeys();
		static void updateKey(input::Key& key);
		static bool isKeyDown(eKeyCode code);
		static void updateKeyDown(input::Key& key);
		static void updateKeyUp(input::Key& key);

	private:
		//eKeyState mState = eKeyState::Up;
		static std::vector<Key> mKeys;	//static -> 정적변수(전역변수와 같이 사용하도록 하기위함)
										//but, 하나의 클라스 안에서만 전역변수와 같이 사용할 수 있다.
										//그리고 전역변수와 같기때문에 초기화를 해주어야한다.
										//즉 여러개의 클래스를 만들어도 static으로 선언된 변수는 하나의 주소를 참조하기때문에
										//모두 같은 값을 참조할 수 있게된다.
	};
}

