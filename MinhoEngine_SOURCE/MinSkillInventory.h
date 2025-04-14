#pragma once
#include "MinUIBase.h"
#include "MinTexture.h"
#include "MinMesh.h"
#include "MinMaterial.h"

namespace min
{
	class SkillInventory : public UIBase
	{
	public:
		SkillInventory();
		~SkillInventory();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender() override;
		virtual void OnClear() override;

		void CreateUIIndexBuffer();

	private:
		graphics::Texture* mSprite;
		Material* mMaterial;
		Mesh* mMesh;

		std::vector<graphics::InstanceData> mInstanceData;

		graphics::InstanceData mNormal;
	};
}

