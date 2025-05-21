#include "MinSceneManager.h"
#include "Mininput.h"
#include "MinDontDestroyOnLoad.h"

namespace min {
	std::map<std::wstring, Scene*> SceneManager::mScene = {{}};
	Scene* SceneManager::mActiveScene = nullptr;
	Scene* SceneManager::mDontDestroyOnLoad = nullptr;

	bool SceneManager::SetActiveScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScene.find(name);

		if (iter == mScene.end())
			return false;


		mActiveScene = iter->second;
		return true;
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		if (mActiveScene) {
			mActiveScene->OnExit();
		}

		if(!SetActiveScene(name))
			return nullptr;

		mActiveScene->OnEnter();

		return mActiveScene;
	}

	//Scene* SceneManager::LoadScene(const std::wstring& name, bool Loading)
	//{
	//	if (mActiveScene) {
	//		mActiveScene->OnExit();
	//	}

	//	if (!SetActiveScene(name))
	//		return nullptr;

	//	mActiveScene->OnEnter();

	//	return mActiveScene;
	//}

	std::vector<GameObject*> SceneManager::GetGameObjects(eLayerType layer)
	{
		std::vector<GameObject*> gameObjects
			= mActiveScene->GetLayer(layer)->GetGameObjects();
		std::vector<GameObject*> dontDestroyOnload
			= mDontDestroyOnLoad->GetLayer(layer)->GetGameObjects();

		gameObjects.insert(gameObjects.end(), dontDestroyOnload.begin(), dontDestroyOnload.end());

		return gameObjects;
	}

	void SceneManager::Initialize()
	{
		mDontDestroyOnLoad = CreateScene<DontDestroyOnLoad>(L"DontDestroyOnLoad");
	}

	void SceneManager::Update()
	{/*
		if (input::GetKey(eKeyCode::N)) {
			SceneManager::LoadScene(L"TitleScene");
		}
		if (input::GetKey(eKeyCode::M)) {
			SceneManager::LoadScene(L"PlayScene");
		}
		if (input::GetKey(eKeyCode::B)) {
			SceneManager::LoadScene(L"ToolScene");
		}*/
		mActiveScene->Update();
		mDontDestroyOnLoad->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
		mDontDestroyOnLoad->LateUpdate();
	}
	void SceneManager::Render()
	{
		mActiveScene->Render();
		mDontDestroyOnLoad->Render();
	}
	void SceneManager::Destory()
	{
		mActiveScene->Destory();
		mDontDestroyOnLoad->Destory();
	}
	void SceneManager::Release()
	{
		for (auto& iter : mScene)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
}