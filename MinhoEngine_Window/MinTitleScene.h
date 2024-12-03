#pragma once
#include "..\\MinhoEngine_SOURCE\\\MinScene.h"

namespace min {
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		void initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander(HDC hdc) override;

	private:

	};
}

