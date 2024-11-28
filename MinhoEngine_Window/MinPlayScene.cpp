#include "MinPlayScene.h"
#include "..\\MinhoEngine_SOURCE\\minGameObject.h"


namespace min {
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::initialize()
	{
		GameObject* objc = new GameObject();
		AddGameObject(objc);
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Rander(HDC hdc)
	{
		Scene::Rander(hdc);
	}
}