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
			Player* bg = new Player();
			Transform* tr = bg->AddComponent<Transform>();
			tr->SetPos(Vector2(0, 0));

			tr->SetName(L"TR");

			SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");
			sr->ImageLoad(L"C:\\Users\\wjstk\\source\\repos\\MinhoEngine\\MinhoEngine_SOURCE\\Resources\\CloudOcean.png");
			AddGameObject(bg);
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