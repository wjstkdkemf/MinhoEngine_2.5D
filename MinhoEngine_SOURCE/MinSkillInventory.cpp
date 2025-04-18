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
		:UIBase(enums::eUIType::SkillInventory)
		, mSprite(nullptr)
		, mSkillSprite(nullptr)
		, mMaterial(nullptr)
		, mMesh(nullptr)
		, mSkillMesh(nullptr)
		, mSkillMaterial(nullptr)
		, mNormal()
		, mInstanceDatas{}
		, mInstanceSize(4) // instancebuffer에서 들고있는게 나을수도?
		, mSkillName{}
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
		mSkillMesh = Resources::Find<Mesh>(L"SkillItemInventoryMesh");
		mSkillMaterial = Resources::Find<Material>(L"SkillItemInventoryMaterial");
		mNormal.offset.x = 80.0f;
		mNormal.offset.y = 0.0f;
		mNormal.color.x = 0.0f;
		mNormal.color.y = 0.0f;
		mNormal.color.z = 0.0f;

		mInstanceDatas.resize(mInstanceSize);
		CreateIntanceData();

		UpdateSkillInformation();
	}
	void SkillInventory::OnActive()
	{
		UpdateSkillInformation();
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

		PrintItem();
	}
	void SkillInventory::OnClear()
	{
	}
	void SkillInventory::PrintItem()
	{
		for (int i = 0; i < mSkillName.size(); i++)
		{
			mSkillSprite = Resources::Find<graphics::Texture>(mSkillName[i]);
			SkillConstantBufferSetting(i);

			if (mSkillMesh)
				mSkillMesh->Bind();

			if (mSkillMaterial)
				mSkillMaterial->BindShader();

			if (mSkillSprite)
				mSkillSprite->Bind(eShaderStage::PS, (UINT)eTextureType::Sprite);

			if (mSkillMesh)
				graphics::GetDevice()->DrawIndexed(mSkillMesh->GetIndexCount(), 0, 0);
		}
	}
	void SkillInventory::CreateUIIndexBuffer()
	{
		mInstanceData.clear();

		for (int i = 0; i < mInstanceSize; ++i) {
			InstanceData data;
			data.offset = XMFLOAT2(mInstanceDatas[i].offset.x, mInstanceDatas[i].offset.y);  // 슬롯 위치
			data.color = XMFLOAT4(mInstanceDatas[i].color.x, mInstanceDatas[i].color.y, mInstanceDatas[i].color.z, 1.0f);  // 슬롯 색상
			mInstanceData.push_back(data);
		}
		
		renderer::InstanceBuffers[IBSLOT_INVENTORY]->SetData(mInstanceData.data());
		
		//deviceContext->UpdateSubresource(instanceBuffer, 0, NULL, mInstanceData.data(), 0, 0);
	}
	void SkillInventory::CreateIntanceData()
	{
		for (UINT i = 0; i < mInstanceSize; ++i)
		{
			mInstanceDatas[i].offset.x = mNormal.offset.x * i;
			mInstanceDatas[i].offset.y = mNormal.offset.y * i;

			mInstanceDatas[i].color.x = mNormal.color.x;
			mInstanceDatas[i].color.y = mNormal.color.y;
			mInstanceDatas[i].color.z = mNormal.color.z;
		}
	}
	void SkillInventory::UpdateSkillInformation()
	{
		mSkillName.clear();

		for (int i = 0; i < SkillInformation::GetSkillInformation().size(); i++)
		{
			mSkillName.push_back(SkillInformation::GetSkillInformation()[i]->SkillName);
		}
	}
	void SkillInventory::SkillConstantBufferSetting(UINT Num)
	{
		graphics::SkillCB cbData = {};
		cbData.offsetX = mInstanceDatas[Num].offset.x;
		cbData.offsetY = mInstanceDatas[Num].offset.y;

		graphics::ConstantBuffer* cb = renderer::constantBuffers[CBSLOT_Skill];

		cb->SetData(&cbData);
		cb->Bind(eShaderStage::All);
	}
}