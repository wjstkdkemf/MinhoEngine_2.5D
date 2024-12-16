#include "MinPlayScene.h"
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
#include "MinCamera.h"
#include "MinRenderer.h"
#include "MinAnimator.h"

namespace min {
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		{
			//bg = new Player();
			//Transform* tr = bg->AddComponent<Transform>();
			//tr->SetPosition(Vector2(0, 0));

			//tr->SetName(L"TR");

			//SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
			//sr->SetName(L"SR");
			//sr->ImageLoad(L"C:\\Users\\wjstk\\source\\repos\\MinhoEngine\\MinhoEngine_SOURCE\\Resources\\CloudOcean.png");
			//AddGameObject(bg, enums::eLayerType::BackGround);
			GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None,Vector2(344.0f,445.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::mainCamera = cameraComp;
			//camera->AddComponent<PlayerScript>();

			mPlayer = object::Instantiate<Player>
				(enums::eLayerType::Particle, Vector2(0.0f, 0.0f));
			/*SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
			sr->SetSize(Vector2(2.0f, 2.0f));*/
			mPlayer->AddComponent<PlayerScript>();

			//graphcis::Texture* PacTex = Resources::Find<graphcis::Texture>(L"MappleEffect");
		 //	Animator* animator = mPlayer->AddComponent<Animator>();
			//animator->CreateAnimation(L"CatFrontMove", PacTex
			//	, Vector2(0.0f, 0.0f), Vector2(386.0f, 246.0f), Vector2::Zero, 8, 0.1f);//32.0f, 32.0f


			graphcis::Texture* PacTex = Resources::Find<graphcis::Texture>(L"Cat");
			Animator* animator = mPlayer->AddComponent<Animator>();
			animator->CreateAnimation(L"CatDownWalk", PacTex
				, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);//32.0f, 32.0f
			animator->CreateAnimation(L"CatRightWalk", PacTex
				, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			animator->CreateAnimation(L"CatUpWalk", PacTex
				, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			animator->CreateAnimation(L"CatLeftWalk", PacTex
				, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			animator->CreateAnimation(L"CatSitDown", PacTex
				, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			animator->CreateAnimation(L"CatGrooming", PacTex
				, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

			animator->PlayAnimation(L"CatSitDown", false);
			//sr->SetTexture(ChickenAlpha);

			mPlayer->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 100.0f));
			mPlayer->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));
			mPlayer->GetComponent<Transform>()->SetRotation(30.0f);

			GameObject* bg = object::Instantiate<GameObject>
				(enums::eLayerType::Player, Vector2(0.0f, 0.0f));
			SpriteRenderer* BGsr = bg->AddComponent<SpriteRenderer>();
			//BGsr->SetSize(Vector2(2.0f, 2.0f));

			graphcis::Texture* BgTex = Resources::Find<graphcis::Texture>(L"Bubble");
			BGsr->SetTexture(BgTex);



			/*graphcis::Texture* tex = new graphcis::Texture();
			tex->Load(L"C:\\Users\\wjstk\\source\\repos\\MinhoEngine\\MinhoEngine_SOURCE\\Resources\\CloudOcean.png");*/
			Scene::Initialize();
		}
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (input::GetKey(eKeyCode::N)) {
			SceneManager::LoadScene(L"TitleScene");
		}
	}
	void PlayScene::Rander(HDC hdc)
	{
		Scene::Rander(hdc);
		wchar_t str[50] = L"Play Scene";
		TextOut(hdc, 0, 0, str, 10);
	}
	void PlayScene::OnEnter()
	{
	}
	void PlayScene::OnExit()
	{
		Transform* tr = mPlayer->GetComponent<Transform>();
		//tr->SetPosition(Vector2(0, 0));
	}
}