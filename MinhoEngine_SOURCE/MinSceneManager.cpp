#include "MinSceneManager.h"

namespace min {
	std::map<std::wstring, Scene*> SceneManager::mScene = {{}};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void SceneManager::Rander(HDC hdc)
	{
		mActiveScene->Rander(hdc);
	}
}