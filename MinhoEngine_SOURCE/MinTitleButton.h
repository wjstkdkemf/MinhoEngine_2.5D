#pragma once
#include "MinUIBase.h"
#include "MinTexture.h"
#include "MinMesh.h"
#include "MinMaterial.h"
#include "MinSkillInformation.h"


namespace min
{
	class TitleButton : public UIBase
	{
	public:
		struct ButtonInfo
		{
			std::wstring ButtonName;
			Vector2 offset;
			Vector2 TitlePos;

			bool mTouch;
		};

		TitleButton();
		~TitleButton();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender() override;
		virtual void OnClear() override;


		void PrintButton();
		void PrintBGTitle();

		void CreateButtonInfomation();

		void mOnClick(std::wstring name);

		void ConstantBufferSetting(UINT Num);
		void ResizeButtonPosition();

	private:
		graphics::Texture* mSprite;
		graphics::Texture* mMainTitleSprite;

		Material* mMaterial;
		Material* mMainTitleMaterial;

		Mesh* mMesh;
		Mesh* mMainTitleMesh;

		float mBeforeResolutionX;
		float mBeforeResolutionY;

		std::vector<ButtonInfo> mTitlenfo;
	};
}

