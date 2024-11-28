#pragma once
#include "..\\MinhoEngine_SOURCE\\\MinScene.h"

namespace min {
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		void initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander(HDC hdc) override;

	private:

	};
}

