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

			GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.0f, 445.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::mainCamera = cameraComp;

			fg = object::Instantiate<Player>(enums::eLayerType::FrontGround, Vector2(300.0f, 300.0f));
			SpriteRenderer* sr = fg->AddComponent<SpriteRenderer>();
			//sr->ImageLoad(L"..\\MinhoEngine_SOURCE\\Resources\\TitleName.png");

			graphics::Texture* fgTex = Resources::Find<graphics::Texture>(L"BG_2");
			sr->SetTexture(fgTex);

			bg = object::Instantiate<Player>(enums::eLayerType::BackGround, Vector2(0.0f, 0.0f));
			sr = bg->AddComponent<SpriteRenderer>();
			//sr->ImageLoad(L"..\\MinhoEngine_SOURCE\\Resources\\background.png");

			graphics::Texture* bgTex = Resources::Find<graphics::Texture>(L"TN");
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
	void TitleScene::Rander()
	{
		Scene::Rander();
	}
	void TitleScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void TitleScene::OnExit()
	{
		Scene::OnExit();
	}
}