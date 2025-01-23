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

		void Initialize(); // 초기화 함수
		void Active(); // 활성화시 호출
		void InActive(); // 비활성화시 호출

		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		void UIClear();//UI삭제시 메모리 정리

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

