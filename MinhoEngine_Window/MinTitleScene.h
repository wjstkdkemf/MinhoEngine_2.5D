#pragma once
#include "..\\MinhoEngine_SOURCE\\\MinScene.h"

namespace min {
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander() override;

		void OnEnter() override;
		void OnExit() override;

	private:
		class Player* bg;
		class Player* fg;
	};
}

