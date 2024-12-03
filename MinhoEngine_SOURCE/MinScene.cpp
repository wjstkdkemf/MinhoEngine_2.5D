#include "MinScene.h"


namespace min {
	Scene::Scene()
		: mLayer {}
	{
		mLayer.resize((UINT)eLayerType::Max);
		for (size_t i = 0; i < (UINT)eLayerType::Max; i++) {
			mLayer[i] = new Layer();
		}
	}
	Scene::~Scene()
	{
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
	void Scene::AddGameObject(GameObject* gameObj,const eLayerType type)
	{
		mLayer[(UINT)type]->AddGameObject(gameObj);
	}

	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
}