#pragma once
#include "minScene.h"

namespace min {
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name) {
			T* scene = new T();
			mScene.insert(std::make_pair(name, scene));

			scene->SetName(name);
			scene->Initialize();

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name);
		//static Scene* LoadScene(const std::wstring& name , bool Loading);


		static bool SetActiveScene(const std::wstring& name);
		static std::wstring GetSceneName() { return mActiveScene->GetName(); }
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetDontDestroyOnLoad() { return mDontDestroyOnLoad; }
		static std::vector<GameObject*> GetGameObjects(eLayerType layer);


		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Destory();
		static void Release();

	//	static SceneManager& GetInst()
	//	{
	//		static SceneManager sceneManager;
	//		return sceneManager;
	//	}

	//private:
	//	SceneManager();
	//	~SceneManager();

	private:
		//static std::vector<Scene*> mScene;
		static std::map<std::wstring, Scene*> mScene;
		static Scene* mActiveScene;
		static Scene* mDontDestroyOnLoad;

	};
}

