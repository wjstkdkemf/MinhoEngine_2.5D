#pragma once
#include "MinUIBase.h"
#include "MinTexture.h"

namespace min
{
	class UIHUd : public UIBase
	{
	public:
		UIHUd();
		~UIHUd();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

	private:
		graphics::Texture* mTexture;
	};
}

