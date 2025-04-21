#pragma once
#include "MinUIBase.h"
#include "MinTexture.h"
#include "MinMesh.h"
#include "MinMaterial.h"
#include "MinSkillInformation.h"

namespace min
{
	class SkillInventory : public UIBase
	{
	public:
		struct InventoryInfo
		{
			std::wstring SkillName;
			Vector2 SkillPos;

			bool mTouch;
		};

		SkillInventory();
		~SkillInventory();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender() override;
		virtual void OnClear() override;

		void PrintItem();

		void CreateUIIndexBuffer();
		void CreateIntanceData();
		void CreateSkillInformation();

		UINT GetInstanceSize() { return mInstanceSize; }

		void UpdateSkillInformation();
		void SkillConstantBufferSetting(UINT Num);

	private:
		graphics::Texture* mSprite;
		graphics::Texture* mSkillSprite;
		Material* mMaterial;
		Material* mSkillMaterial;
		Mesh* mMesh;
		Mesh* mSkillMesh;

		UINT mInstanceSize;
		UINT mInventoryRow;
		UINT mInventoryCol;

		graphics::InstanceData mNormal;
		std::vector<graphics::InstanceData> mInstanceData;
		std::vector<graphics::InstanceData> mInstanceDatas;
		std::vector<InventoryInfo> mSkillInfo;

		InventoryInfo* mSelectSkillInfo;

		float mMinValue;
		float mTouchDelay;
	};
}

