#pragma once
#include "commoninclude.h"
#include "MinUIBase.h"

namespace min
{
	using namespace enums;
	class UIManager
	{
	public:
		UIManager();
		~UIManager();

		static void Initialize();
		static void OnLoad(eUIType type);
		static void Update();
		static void LateUpdate();
		static void Render();
		static void OnComplete(UIBase* addUI);
		static void OnFail();
		static void Release();

		static void Push(eUIType type);
		static void Pop(eUIType type);

		static UIBase* UIGet(eUIType type)
		{
			auto iter = mUIs.find(type);
			return iter->second;
		}

	public:
		static Matrix mUIMatrix;
		static Matrix mUIViewMatrix;

	private:
		static std::unordered_map<eUIType, UIBase*> mUIs;
		static std::stack<UIBase*> mUIBases;
		static std::queue<eUIType> mRequestUIQueue;
		static UIBase* mActiveUI;
	};
}

