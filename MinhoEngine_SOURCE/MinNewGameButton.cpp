#include "MinNewGameButton.h"
#include "Mininput.h"
#include "MinResources.h"
#include "MinUIManager.h"
#include "MinGraphics.h"
#include "MinRenderer.h"
#include "MinApplication.h"

extern min::Application application;

namespace min
{
	NewGameButton::NewGameButton()
	{
	}
	NewGameButton::~NewGameButton()
	{
	}
	void NewGameButton::OnInit()
	{
		mMesh = Resources::Find<Mesh>(L"UIButtonMesh"); //추후 수정 예정
		mSprite = Resources::Find<graphics::Texture>(L"HPBAR");
		mMaterial = Resources::Find<Material>(L"UIMaterial");

		mOnClick = std::bind(&UIButton::ButtonClick, this);

		float PosX = (float)application.GetWindow().GetWidth();
		float PosY = (float)application.GetWindow().GetHeight();

		SetPos(Vector3(PosX/2, PosY/2 + PosY/6, 0.0f));
		SetSize(Vector3(100.0f, 50.0f, 0.0f));
	}
	void NewGameButton::OnActive()
	{
	}
	void NewGameButton::OnInActive()
	{
	}
	void NewGameButton::OnUpdate()
	{
	}
	void NewGameButton::OnLateUpdate()
	{
	}
	void NewGameButton::OnRender()
	{
	}
	void NewGameButton::OnClear()
	{
	}
	void NewGameButton::ButtonClick()
	{
	}
}