#pragma once
#include "..\\MinhoEngine_SOURCE\\MinSceneManager.h"
#include "MinPlayScene.h"
#include "MinTitleScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\MinhoEngine_Window.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\MinhoEngine_Window.lib")
#endif

namespace min {
	void LoadScenes() {
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<TitleScene>(L"TitleScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}