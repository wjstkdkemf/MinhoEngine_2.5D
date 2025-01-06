#include "MinScene.h"


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
		for (Layer* layer : mLayer) {
			if (layer == nullptr)
				continue;

			layer->Initialize();
		}
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
	void Scene::Rander(HDC hdc)
	{
		for (Layer* layer : mLayer) {
			if (layer == nullptr)
				continue;

			layer->Rander(hdc);
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
	}
}