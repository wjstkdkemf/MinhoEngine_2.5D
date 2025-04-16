#include "MinSkillInventory.h"
#include "MinResources.h"
#include "MinTransform.h"
#include "MinRenderer.h"
#include "minGameObject.h"
#include "MinUIManager.h"
#include "MinGraphics.h"
#include "..\\MinhoEngine_Window\MinCameraScript.h"

namespace min
{
	SkillInventory::SkillInventory()
		:UIBase(enums::eUIType::HPBAR)
		, mSprite(nullptr)
		, mMaterial(nullptr)
		, mMesh(nullptr)
		, mNormal()
		, mInstanceSize(4) // instancebuffer에서 들고있는게 나을수도?
	{
	}
	SkillInventory::~SkillInventory()
	{
	}
	void SkillInventory::OnInit()
	{
		mMesh = Resources::Find<Mesh>(L"SkillInventoryMesh"); //추후 수정 예정
		mSprite = Resources::Find<graphics::Texture>(L"NoneSkill");
		mMaterial = Resources::Find<Material>(L"SkillInventoryMaterial");

		mNormal.offset.x = 80.0f;
		mNormal.offset.y = 0.0f;
		mNormal.color.x = 0.0f;
		mNormal.color.y = 0.0f;
		mNormal.color.z = 0.0f;
	}
	void SkillInventory::OnActive()
	{
	}
	void SkillInventory::OnInActive()
	{
	}
	void SkillInventory::OnUpdate()
	{
	}
	void SkillInventory::OnLateUpdate()
	{
	}
	void SkillInventory::OnRender()
	{
		CreateUIConstantBuffer();
		CreateUIIndexBuffer();

		if (mMesh)
			mMesh->BindWithInstancing(eIBType::Inventory);

		if (mMaterial)
			mMaterial->BindShader();

		if (mSprite)
			mSprite->Bind(eShaderStage::PS, (UINT)eTextureType::Sprite);

		if (mMesh)
			graphics::GetDevice()->DrawIndexedInstanced(mMesh->GetIndexCount(), 4, 0, 0);


	}
	void SkillInventory::OnClear()
	{
	}
	void SkillInventory::CreateUIIndexBuffer()
	{
		for (int i = 0; i < mInstanceSize; ++i) {
			InstanceData data;
			data.offset = XMFLOAT2(mNormal.offset.x * i, 0.0f);  // 슬롯 위치
			data.color = XMFLOAT4(mNormal.color.x, mNormal.color.y, mNormal.color.z, 1.0f);  // 슬롯 색상
			mInstanceData.push_back(data);
		}
		
		renderer::InstanceBuffers[IBSLOT_INVENTORY]->SetData(mInstanceData.data());
		
		//deviceContext->UpdateSubresource(instanceBuffer, 0, NULL, mInstanceData.data(), 0, 0);
	}
}