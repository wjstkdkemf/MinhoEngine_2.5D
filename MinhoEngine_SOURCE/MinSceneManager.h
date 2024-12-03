#pragma once
#include "minScene.h"

namespace min {
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name) {
			T* scene = new T();
			scene->SetName(name);
			scene->Initialize();

			mScene.insert(std::make_pair(name, scene));

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name) {
			if(mActiveScene){
				mActiveScene->OnExit();
			}
			
			std::map<std::wstring, Scene*>::iterator iter = mScene.find(name);

			if (iter == mScene.end()) {
				return nullptr;
			}
			mActiveScene = iter->second;
			mActiveScene->OnEnter();

			return iter->second;
		}
		static std::wstring GetSceneName() { return mActiveScene->GetName(); }

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Rander(HDC hdc);

	private:
		//static std::vector<Scene*> mScene;
		static std::map<std::wstring, Scene*> mScene;
		static Scene* mActiveScene;
	};
}

