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
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);

		layer->AddGameObject(gameobject);

		return gameobject;
	}

	template <typename T>
	static T* Instantiate(min::enums::eLayerType type, math::Vector2 position)
	{
		T* gameobject = new T();
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
}