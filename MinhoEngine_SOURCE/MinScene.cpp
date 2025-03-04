#include "MinScene.h"
#include "MinCollisionManager.h"
#include "MinSceneManager.h"

namespace min {
	Scene::Scene()
		: mLayer {}
	{
		CreateLayers();
	}
	Scene::~Scene()
	{
		for (Layer* layer : mLayer)
		{
			delete layer;
			layer = nullptr;
		}
	}
	void Scene::Initialize()
	{
		const std::wstring& sceneName = GetName();
		SceneManager::SetActiveScene(sceneName);
	}
	void Scene::Update()
	{
		/*for (size_t i = 0; i < mGameObjects.size(); i++) {
			mGameObjects[i]->Update();
		}*/
		for (Layer* layer : mLayer) {
			if (layer == nullptr)
				continue;

			layer->Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (Layer* layer : mLayer) {
			if (layer == nullptr)
				continue;

			layer->LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer* layer : mLayer) {
			if (layer == nullptr)
				continue;

			layer->Rander();
		}
	}
	void Scene::Destory()
	{
		for (Layer* layer : mLayer) {
			if (layer == nullptr)
				continue;

			layer->Destroy();
		}
	}
	void Scene::AddGameObject(GameObject* gameObj,const enums::eLayerType type)
	{
		mLayer[(UINT)type]->AddGameObject(gameObj);
	}

	void Scene::EraseGameObject(GameObject* gameObj)
	{
		eLayerType layerType = gameObj->GetLayerType();
		mLayer[(UINT)layerType]->EraseGameObjects(gameObj);
	}

	void Scene::CreateLayers()
	{
		mLayer.resize((UINT)enums::eLayerType::Max);
		for (size_t i = 0; i < (UINT)enums::eLayerType::Max; i++) {
			mLayer[i] = new Layer();
		}
	}

	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
		CollisionManager::clear();
	}
}