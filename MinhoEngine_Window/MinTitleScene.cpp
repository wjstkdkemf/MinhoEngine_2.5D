#include "MinTitleScene.h"
#include "..\\MinhoEngine_SOURCE\\minGameObject.h"
#include "MinPlayer.h"
#include "MinTransform.h"
#include "MinSpriteRenderer.h"
#include "Mininput.h"
#include "MinSceneManager.h"
#include "MinObject.h"
#include "MinTexture.h"
#include "MinResources.h"
#include "MinPlayerScript.h"
#include "MinRenderer.h"

namespace min {
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		{
			//Player* bg = new Player();
			//Transform* tr = bg->AddComponent<Transform>();
			//tr->SetPosition(Vector2(0, 0));

			//tr->SetName(L"TR");

			//SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
			//sr->SetName(L"SR");
			//sr->ImageLoad(L"C:\\Users\\wjstk\\source\\repos\\MinhoEngine\\MinhoEngine_SOURCE\\Resources\\background.png");
			//AddGameObject(bg, enums::eLayerType::BackGround);

			fg = object::Instantiate<Player>(enums::eLayerType::FrontGround, Vector2(300.0f, 300.0f));
			SpriteRenderer* sr = fg->AddComponent<SpriteRenderer>();
			//sr->ImageLoad(L"..\\MinhoEngine_SOURCE\\Resources\\TitleName.png");

			graphcis::Texture* bgTex = Resources::Find<graphcis::Texture>(L"BG_2");
			sr->SetTexture(bgTex);

			bg = object::Instantiate<Player>(enums::eLayerType::BackGround, Vector2(0.0f, 0.0f));
			sr = bg->AddComponent<SpriteRenderer>();
			//sr->ImageLoad(L"..\\MinhoEngine_SOURCE\\Resources\\background.png");

			bgTex = Resources::Find<graphcis::Texture>(L"TN");
			sr->SetTexture(bgTex);

			bg->AddComponent<PlayerScript>();

			Scene::Initialize();
		}
	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (input::GetKey(eKeyCode::M)) {
			SceneManager::LoadScene(L"TitleScene");
		}
	}
	void TitleScene::Rander(HDC hdc)
	{
		Scene::Rander(hdc);
		wchar_t str[50] = L"Title Scene";
		TextOut(hdc, 0, 0, str, 11);
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}