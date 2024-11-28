#include "MinScene.h"


namespace min {
	Scene::Scene()
		: mGameObjects {}
	{
	}
	Scene::~Scene()
	{
	}
	void Scene::initialize()
	{
	}
	void Scene::Update()
	{
		/*for (size_t i = 0; i < mGameObjects.size(); i++) {
			mGameObjects[i]->Update();
		}*/
		for (GameObject* gameObj : mGameObjects) {
			gameObj->Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects) {
			gameObj->LateUpdate();
		}
	}
	void Scene::Rander(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects) {
			gameObj->Rander(hdc);
		}
	}
	void Scene::AddGameObject(GameObject* gameObject)
	{
		mGameObjects.push_back(gameObject);
	}
}