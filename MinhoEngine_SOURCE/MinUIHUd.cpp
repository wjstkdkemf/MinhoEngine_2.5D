#include "MinUIHUd.h"
#include "MinResources.h"
#include "MinTransform.h"
#include "MinRenderer.h"
#include "minGameObject.h"
#include "MinUIManager.h"
#include "..\\MinhoEngine_Window\MinCameraScript.h"

namespace min
{
	UIHUd::UIHUd()
		:UIBase(enums::eUIType::HPBAR)
		, mSprite(nullptr)
		, mMaterial(nullptr)
		, mMesh(nullptr)
	{
	}
	UIHUd::~UIHUd()
	{
	}
	void UIHUd::OnInit()
	{
		mMesh = Resources::Find<Mesh>(L"UIMesh"); //추후 수정 예정
		mSprite = Resources::Find<graphics::Texture>(L"NoneSkill");//HPBAR
		mMaterial = Resources::Find<Material>(L"UIMaterial");
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
	void UIHUd::OnRender()
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
	void UIHUd::OnClear()
	{
	}
}