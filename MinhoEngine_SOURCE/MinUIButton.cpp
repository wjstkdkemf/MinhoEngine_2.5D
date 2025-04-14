#include "MinUIButton.h"
#include "Mininput.h"
#include "MinResources.h"
#include "MinUIManager.h"
#include "MinGraphics.h"
#include "MinRenderer.h"

namespace min
{
	UIButton::UIButton()
		: UIBase(enums::eUIType::Button)
		, mSprite(nullptr)
		, mMaterial(nullptr)
		, mMesh(nullptr)
	{
	}
	UIButton::~UIButton()
	{
	}
	void UIButton::OnInit()
	{
		mMesh = Resources::Find<Mesh>(L"UIButtonMesh"); //추후 수정 예정
		mSprite = Resources::Find<graphics::Texture>(L"HPBAR");
		mMaterial = Resources::Find<Material>(L"UIMaterial");

		mOnClick = std::bind(&UIButton::ButtonClick, this);

		SetPos(Vector3(600.0f, 100.0f, 0.0f));
		SetSize(Vector3(100.0f, 50.0f, 0.0f));
	}
	void UIButton::OnActive()
	{
	}
	void UIButton::OnInActive()
	{
	}
	void UIButton::OnUpdate()
	{
		Vector2 mousePos = input::GetMousePosition();
		
		if (mPosition.x <= mousePos.x && mousePos.x <= mPosition.x + mSize.x
			&& mPosition.y <= mousePos.y && mousePos.y <= mPosition.y + mSize.y)
		{
			mbMouseOn = true;
		}
		else
		{
			mbMouseOn = false;
		}

		if (input::GetKeyDown(eKeyCode::LButton))
		{
			if (mbMouseOn)
			{
				mOnClick();
			}
		}
	}
	void UIButton::OnLateUpdate()
	{
	}
	void UIButton::OnRender()
	{
		CreateUIConstantBuffer();

		if (mMesh)
			mMesh->Bind();

		if (mMaterial)
			mMaterial->BindShader();

		if (mSprite)
			mSprite->Bind(eShaderStage::PS, (UINT)eTextureType::Sprite);

		if (mMesh)
			graphics::GetDevice()->DrawIndexed(mMesh->GetIndexCount(), 0, 0);

	}
	void UIButton::OnClear()
	{
	}
	void UIButton::ButtonClick()
	{
		int a = 0;
	}
}