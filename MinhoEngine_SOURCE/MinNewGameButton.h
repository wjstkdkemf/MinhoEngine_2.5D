#pragma once
#include "MinUIButton.h"
#include "MinTexture.h"
#include "MinMaterial.h"
#include "MinMesh.h"


namespace min
{
	class NewGameButton : public UIButton
	{
	public:
		NewGameButton();
		~NewGameButton();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender() override;
		virtual void OnClear() override;

		virtual void ButtonClick();

	private:
	};
}

