#include "MinSkillInventory.h"
#include "MinResources.h"
#include "MinTransform.h"
#include "MinRenderer.h"
#include "minGameObject.h"
#include "MinUIManager.h"
#include "MinGraphics.h"
#include "Mininput.h"
#include "MinTime.h"
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
		, mInstanceSize(0) // instancebuffer에서 들고있는게 나을수도? -> 자주 바꾸지 않아도 되니까 일단은 임시로 고정값을 instancebuffer에 부여, 추후 필요시 오버할로케이션 전략등 고려
		, mInventoryRow(2)
		, mInventoryCol(4)
		, mMinValue(1800.0f)
		, mTouchDelay(0.3f)
		, mSkillInfo{}
		, mSelectSkillInfo(nullptr)
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
		mNormal.offset.y = 80.0f;
		mNormal.color.x = 0.0f;
		mNormal.color.y = 0.0f;
		mNormal.color.z = 0.0f;

		mInstanceSize = mInventoryCol * mInventoryRow;

		mInstanceDatas.resize(mInstanceSize);
		mSkillInfo.resize(mInstanceSize);
		CreateIntanceData();

		CreateSkillInformation();
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
		mTouchDelay += Time::DeltaTime();

		if (input::GetKeyDown(eKeyCode::LButton))
		{
			Vector2 mousePos = input::GetMousePosition();
			float minDist = mMinValue;
			InventoryInfo* closest = nullptr;

			for (InventoryInfo& slot : mSkillInfo)
			{
				float dx = mousePos.x - slot.SkillPos.x;
				float dy = mousePos.y - slot.SkillPos.y;

				float dist = dx * dx + dy * dy;

				if (dist < minDist)
				{
					minDist = dist;
					closest = &slot;
				}
			}
			if (minDist != mMinValue && mTouchDelay >= 1.0f)
			{
				if (mSelectSkillInfo != nullptr)
				{
					if(mSelectSkillInfo != closest)
						std::swap(mSelectSkillInfo->SkillName, closest->SkillName);

					mSelectSkillInfo->mTouch = false;
					mSelectSkillInfo = nullptr;
					mTouchDelay = 0.0f;
				}
				else
				{
					closest->mTouch = true;
					mSelectSkillInfo = closest;
					mTouchDelay = 0.0f;
				}
			}
		}
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
			graphics::GetDevice()->DrawIndexedInstanced(mMesh->GetIndexCount(), mInstanceSize, 0, 0);

		PrintItem();
	}
	void SkillInventory::OnClear()
	{
	}
	void SkillInventory::PrintItem()
	{
		for (int i = 0; i < mSkillInfo.size(); i++)
		{
			if (mSkillInfo[i].mTouch)
			{
				int a = 0;
				mSkillInfo[i].mTouch = false;
			}

			if (mSkillInfo[i].SkillName == L"")
				continue;

			mSkillSprite = Resources::Find<graphics::Texture>(mSkillInfo[i].SkillName);
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
		//for (UINT i = 0; i < mInstanceSize; ++i)
		//{
		//	mInstanceDatas[i].offset.x = mNormal.offset.x * i;
		//	mInstanceDatas[i].offset.y = mNormal.offset.y * i;

		//	mInstanceDatas[i].color.x = mNormal.color.x;
		//	mInstanceDatas[i].color.y = mNormal.color.y;
		//	mInstanceDatas[i].color.z = mNormal.color.z;
		//}
		UINT index = 0;
		for (UINT j = 1; j < mInventoryRow + 1; ++j)
		{
			for (UINT i = 0; i < mInventoryCol; ++i)
			{
				mInstanceDatas[index].offset.x = mNormal.offset.x * i;
				mInstanceDatas[index].offset.y = mNormal.offset.y * (j - 1);

				mInstanceDatas[index].color.x = mNormal.color.x;
				mInstanceDatas[index].color.y = mNormal.color.y;
				mInstanceDatas[index].color.z = mNormal.color.z;

				mSkillInfo[index].SkillPos = Vector2(925.0f + mInstanceDatas[index].offset.x, 125.0f + mInstanceDatas[index].offset.y);//925 와 125는 mesh구현 과정에서 설정한 초기 중앙위치.
				index++;
			}
		}
	}
	void SkillInventory::CreateSkillInformation()
	{
		for (int i = 0; i < SkillInformation::GetSkillInformation().size(); i++)
		{
			mSkillInfo[i].SkillName = SkillInformation::GetSkillInformation()[i]->SkillName;
		}
	}
	void SkillInventory::UpdateSkillInformation()
	{
		//for (int i = 0; i < SkillInformation::GetSkillInformation().size(); i++)
		//{
		//	mSkillName[i] = SkillInformation::GetSkillInformation()[i]->SkillName;
		//}
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