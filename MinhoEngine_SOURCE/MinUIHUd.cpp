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
		, mHptr(nullptr)
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
		mHptr = new Transform();
		mSprite = Resources::Find<graphics::Texture>(L"HPBAR");
		mHptr->Initialize();
		mMesh = Resources::Find<Mesh>(L"RectMesh"); //추후 수정 예정
		//mMaterial = Resources::Find<Material>(L"SpriteDefaultMaterial");
	}
	void UIHUd::OnActive()
	{
	}
	void UIHUd::OnInActive()
	{
	}
	void UIHUd::OnUpdate()
	{
		mHptr->Update();
	}
	void UIHUd::OnLateUpdate()
	{
		Transform* tr = renderer::mainCamera->GetOwner()->GetComponent<Transform>();
		Vector3 trpos = tr->GetPosition();
		mHptr->SetPosition(trpos.x, trpos.y - (renderer::mainCamera->GetOwner()->GetComponent<CameraScript>()->GetMaxHeight() / 2), trpos.z + 3.0f);

		if (renderer::mainCamera->GetOwner()->GetComponent<CameraScript>()->GetMaxHeight() != 0.0f)
		{
			renderer::mainCamera->GetOwner()->GetComponent<CameraScript>()->GetMaxHeight();
			int a = 0;
		}
		mHptr->LateUpdate();
	}
	void UIHUd::OnRender()
	{
		//if(mHptr)
			//mHptr->Bind();
		graphics::UICB cbData = {};
		cbData.view = XMMatrixTranspose(UIManager::mUIViewMatrix);
		cbData.projection = XMMatrixTranspose(UIManager::mUIMatrix);

		graphics::ConstantBuffer* cb = renderer::constantBuffers[CBSLOT_UI];

		cb->SetData(&cbData);
		cb->Bind(eShaderStage::All);

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