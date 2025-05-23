#pragma once
#include "MinUIBase.h"
#include "MinTexture.h"
#include "MinMaterial.h"
#include "MinMesh.h"

namespace min
{
	class UIButton : public UIBase
	{
	public:
		UIButton();
		~UIButton();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender() override;
		virtual void OnClear() override;

		virtual void ButtonClick();

	protected:
		graphics::Texture* mSprite;
		Material* mMaterial;
		Mesh* mMesh;
		Event mOnClick;
	};
}

