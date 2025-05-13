#include "MinUIManager.h"
#include "MinUIHUd.h"
#include "MinUIButton.h"
#include "MinTitleButton.h"
#include "MinSkillInventory.h"
#include "MinApplication.h"

extern min::Application application;

namespace min
{
	std::unordered_map<eUIType, UIBase*> UIManager::mUIs = {};
	std::stack<UIBase*> UIManager::mUIBases = {};
	std::queue<eUIType>UIManager::mRequestUIQueue = {};
	UIBase* UIManager::mActiveUI = nullptr;

	Matrix UIManager::mUIMatrix = Matrix::Identity;
	Matrix UIManager::mUIViewMatrix = Matrix::Identity;

	UIManager::UIManager()
	{
	}

	UIManager::~UIManager()
	{
	}

	void UIManager::Initialize()
	{
		UIHUd* hud = new UIHUd();
		mUIs.insert(std::make_pair(eUIType::HPBAR, hud));

		UIButton* button = new UIButton();
		mUIs.insert(std::make_pair(eUIType::Button, button));

		SkillInventory* skillinven = new SkillInventory();
		mUIs.insert(std::make_pair(eUIType::SkillInventory, skillinven));

		TitleButton* titleButton = new TitleButton();
		mUIs.insert(std::make_pair(eUIType::TitleButton, titleButton));

		RECT winRect;
		GetClientRect(application.GetWindow().GetHwnd(), &winRect);

		mUIMatrix = Matrix::CreateOrthographicOffCenterLH(
			0.0f, (float)application.GetWindow().GetWidth(),       // Left to Right
			(float)application.GetWindow().GetHeight(), 0.0f,      // Bottom to Top (Y축 아래로 증가)
			0.0f, 1.0f                // nearZ, farZ
		);
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

		while (!uiBases.empty())
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
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->LateUpdate();
				uiBases.pop();
			}
		}
	}
	void UIManager::Render()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (uiBase)
			{
				uiBase->Render();
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
	void UIManager::Release()
	{
		for (auto iter : mUIs)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}
	void UIManager::Pop(eUIType type)
	{
		if (mUIBases.size() <= 0)
			return;

		std::stack<UIBase*> tempStack;

		UIBase* uibase = nullptr;

		while (mUIBases.size() > 0)
		{
			uibase = mUIBases.top();
			mUIBases.pop();

			if (uibase->GetType() != type)
			{
				tempStack.push(uibase);
				continue;
			}

			if (uibase->IsFullScreen())
			{
				std::stack<UIBase*> uiBases = mUIBases;
				while (!uiBases.empty())
				{
					UIBase* uiBase = uiBases.top();
					uiBases.pop();
					if (uiBase)
					{
						uiBase->Active();
						break;
					}
				}
			}
			uibase->UIClear();
		}

		while (tempStack.size() > 0)
		{
			uibase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uibase);
		}
	}
}