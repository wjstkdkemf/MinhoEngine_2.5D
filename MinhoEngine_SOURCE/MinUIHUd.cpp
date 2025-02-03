#include "MinUIHUd.h"
#include "MinResources.h"

namespace min
{
	UIHUd::UIHUd()
		:UIBase(enums::eUIType::HPBAR)
	{
	}
	UIHUd::~UIHUd()
	{
	}
	void UIHUd::OnInit()
	{
		
		mTexture = Resources::Find<graphics::Texture>(L"HPBAR");
	}
	void UIHUd::OnActive()
	{
	}
	void UIHUd::OnInActive()
	{
	}
	void UIHUd::OnUpdate()
	{
	}
	void UIHUd::OnLateUpdate()
	{
	}
	void UIHUd::OnRender(HDC hdc)
	{
		TransparentBlt(hdc
			, 0, 0
			, mTexture->GetWidth()
			, mTexture->GetHeight()
			, mTexture->GetHdc()
			, 0, 0
			, mTexture->GetWidth()
			, mTexture->GetHeight()
			, RGB(255, 0, 255));
	}
	void UIHUd::OnClear()
	{
	}
}