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
		static std::vector<Key> mKeys;	//static -> ��������(���������� ���� ����ϵ��� �ϱ�����)
										//but, �ϳ��� Ŭ�� �ȿ����� ���������� ���� ����� �� �ִ�.
										//�׸��� ���������� ���⶧���� �ʱ�ȭ�� ���־���Ѵ�.
										//�� �������� Ŭ������ ���� static���� ����� ������ �ϳ��� �ּҸ� �����ϱ⶧����
										//��� ���� ���� ������ �� �ְԵȴ�.
	};
}

