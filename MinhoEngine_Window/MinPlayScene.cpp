#include "MinPlayScene.h"
#include "..\\MinhoEngine_SOURCE\\minGameObject.h"
#include "MinPlayer.h"
#include "MinTransform.h"
#include "MinSpriteRenderer.h"

namespace min {
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::initialize()
	{
		{
			Player* p1 = new Player();
			Transform* tr = p1->AddComponent<Transform>();
			tr->SetPos(800, 450);

			tr->SetName(L"TR");

			SpriteRenderer* sr = p1->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");

			AddGameObject(p1);
		}
		{
			Player* p1 = new Player();
			Transform* tr = p1->AddComponent<Transform>();
			tr->SetPos(300, 450);

			tr->SetName(L"TR");

			SpriteRenderer* sr = p1->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");

			AddGameObject(p1);
		}
		{
			Player* p1 = new Player();
			Transform* tr = p1->AddComponent<Transform>();
			tr->SetPos(100, 650);

			tr->SetName(L"TR");

			SpriteRenderer* sr = p1->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");

			AddGameObject(p1);
		}
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