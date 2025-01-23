#pragma once
#include "commoninclude.h"
#include "MinUIBase.h"

namespace min
{
	using namespace enums;
	class UIManager
	{
	public:
		static void Initialize();
		static void OnLoad(eUIType type);
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		static void OnComplete(UIBase* addUI);
		static void OnFail();

		static void Push(eUIType type);
		static void Pop(eUIType type);

	private:
		static std::unordered_map<eUIType, UIBase*> mUIs;
		static std::stack<UIBase*> mUIBases;
		static std::queue<eUIType> mRequestUIQueue;
		static UIBase* mActiveUI;
	};
}

