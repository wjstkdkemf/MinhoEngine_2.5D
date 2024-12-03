#include "MinSceneManager.h"
#include "Mininput.h"

namespace min {
	std::map<std::wstring, Scene*> SceneManager::mScene = {{}};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
	}
	void SceneManager::Update()
	{
		if (input::GetKey(eKeyCode::N)) {
			SceneManager::LoadScene(L"TitleScene");
		}
		if (input::GetKey(eKeyCode::M)) {
			SceneManager::LoadScene(L"PlayScene");
		}
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