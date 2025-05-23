#pragma once
#include "MinComponent.h"
#include "minGameObject.h"
#include "MinLayer.h"
#include "MinScene.h"
#include "MinSceneManager.h"
#include "MinTransform.h"

namespace min::object
{
	template <typename T>
	static T* Instantiate(min::enums::eLayerType type)
	{
		T* gameobject = new T();
		gameobject->SetLayerType(type);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);

		layer->AddGameObject(gameobject);

		return gameobject;
	}

	template <typename T>
	static T* Instantiate(min::enums::eLayerType type, math::Vector3 position)
	{
		T* gameobject = new T();
		gameobject->SetLayerType(type);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);

		layer->AddGameObject(gameobject);

		Transform* tr = gameobject->GetComponent<Transform>();
		tr->SetPosition(position);

		return gameobject;
	}


	static void Destory(GameObject* obj)
	{
		obj->death();
	}

	static void DontDestoryOnLoad(GameObject* gameobject)
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		activeScene->EraseGameObject(gameobject);

		Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
		dontDestroyOnLoad->AddGameObject(gameobject, gameobject->GetLayerType());
	}

	static GameObject* GetDontDestoryOnLoadLayer(const enums::eLayerType type)
	{
		Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();

		return (dontDestroyOnLoad->GetLayer(type)->GetGameObjects())[0];
	}
}