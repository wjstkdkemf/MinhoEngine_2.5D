#pragma once
#include "..\\MinhoEngine_SOURCE\\\MinScene.h"

namespace min {
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnEnter() override;
		void OnExit() override;

	private:
		std::vector<GameObject*> mCameraVector;
	};
}

