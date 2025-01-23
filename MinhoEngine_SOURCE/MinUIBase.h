#pragma once
#include "MinEntity.h"

namespace min
{
	using namespace enums;
	class UIBase : public Entity
	{
	public:
		UIBase();
		~UIBase();

		void Initialize(); // �ʱ�ȭ �Լ�
		void Active(); // Ȱ��ȭ�� ȣ��
		void InActive(); // ��Ȱ��ȭ�� ȣ��

		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		void UIClear();//UI������ �޸� ����

		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnClear();

		eUIType GetType() { return mType; }
		void SetFullScreen(bool enable) { mbFullScreen = enable; }
		bool IsFullScreen() {return mbFullScreen; }

	private:
		eUIType mType;
		bool mbFullScreen;
		bool mbEnabled;
	};
}

