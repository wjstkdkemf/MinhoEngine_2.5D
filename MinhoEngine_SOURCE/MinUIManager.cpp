#include "MinUIManager.h"

namespace min
{
	std::unordered_map<eUIType, UIBase*> UIManager::mUIs = {};
	std::stack<UIBase*> UIManager::mUIBases = {};
	std::queue<eUIType>UIManager::mRequestUIQueue = {};
	UIBase* UIManager::mActiveUI = nullptr;

	void UIManager::Initialize()
	{
	}
	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UIBase*>::iterator iter
			= mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
		
	}
	void UIManager::Update()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->Update();
				uiBases.pop();
			}
		}

		if (mRequestUIQueue.size() > 0)
		{
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();
			OnLoad(requestUI);
		}
	}
	void UIManager::LateUpdate()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->LateUpdate();
				uiBases.pop();
			}
		}
	}
	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->Render(hdc);
				uiBases.pop();
			}
		}
	}
	void UIManager::OnComplete(UIBase* addUI)
	{
		if (addUI == nullptr)
			return;

		addUI->Initialize();
		addUI->Active();
		addUI->Update();

		if (addUI->IsFullScreen())
		{
			std::stack<UIBase*> uiBases = mUIBases;
			while (uiBases.empty())
			{
				UIBase* uiBase = uiBases.top();
				uiBases.pop();
				if (uiBase)
				{
					uiBase->InActive();
				}
			}
		}
		mUIBases.push(addUI);
		mActiveUI = nullptr;
	}
	void UIManager::OnFail()
	{
		mActiveUI = nullptr;
	}
	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}
	void UIManager::Pop(eUIType type)
	{
		if (mUIBases.size() <= 0)
			return;

		UIBase* uibase = nullptr;

		while (mUIBases.size() > 0)
		{

		}
	}
}