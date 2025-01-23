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
#include "MinCat.h"
#include "MinCatScript.h"
#include "MinBoxCollider2D.h"
#include "MinCollisionManager.h"
#include "MinDontDestroyOnLoad.h"
#include "MinRigidbody.h"
#include "MinFloor.h"
#include "MinFloorScript.h"

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
			CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);

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
				(enums::eLayerType::Player);
			mPlayer->SetName(L"player");
			BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
			//CircleCollider2D* collider = mPlayer->AddComponent<CircleCollider2D>();

			collider->SetOffset(Vector2(-50.0f, -50.0f));
			/*SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
			sr->SetSize(Vector2(2.0f, 2.0f));*/
			PlayerScript* plScriptmPlayer = mPlayer->AddComponent<PlayerScript>();
	

			//cameraComp->SetTarget(mPlayer);

			//graphcis::Texture* PacTex = Resources::Find<graphcis::Texture>(L"MappleEffect");
		 //	Animator* animator = mPlayer->AddComponent<Animator>();
			//animator->CreateAnimation(L"CatFrontMove", PacTex
			//	, Vector2(0.0f, 0.0f), Vector2(386.0f, 246.0f), Vector2::Zero, 8, 0.1f);//32.0f, 32.0f


			graphcis::Texture* PlayerTex = Resources::Find<graphcis::Texture>(L"Player");
			Animator* animator = mPlayer->AddComponent<Animator>();
			animator->CreateAnimation(L"Idle", PlayerTex
				, Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 4, 0.1f);//32.0f, 32.0f
			animator->CreateAnimation(L"PlayerFronttGiveWater", PlayerTex
				, Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.1f);
			/*animator->CreateAnimation(L"PlayerRightWalk", PlayerTex
				, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			animator->CreateAnimation(L"PlayerUpWalk", PlayerTex
				, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			animator->CreateAnimation(L"PlayerLeftWalk", PlayerTex
				, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			animator->CreateAnimation(L"PlayerSitDown", PlayerTex
				, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);*/
			
			animator->PlayAnimation(L"Idle", false);
			
			animator->GetCompleteEvent(L"PlayerFronttGiveWater") = std::bind(&PlayerScript::PlayerEffect, plScriptmPlayer);

			mPlayer->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 100.0f));
			//mPlayer->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));
			mPlayer->GetComponent<Transform>()->SetRotation(30.0f);

			mPlayer->AddComponent<Rigidbody>();

			Floor* floor = object::Instantiate<Floor>(eLayerType::Floor, Vector2(0.0f, 600.0f));
			floor->SetName(L"Floor");
			BoxCollider2D* floorCol = floor->AddComponent<BoxCollider2D>();
			floorCol->SetSize(Vector2(3.0f, 1.0f));
			floor->AddComponent<FloorScript>();
			
			

			//배경화면

			//GameObject* bg = object::Instantiate<GameObject>
			//	(enums::eLayerType::Player, Vector2(0.0f, 0.0f));
			//SpriteRenderer* BGsr = bg->AddComponent<SpriteRenderer>();
			////BGsr->SetSize(Vector2(2.0f, 2.0f));

			//graphcis::Texture* BgTex = Resources::Find<graphcis::Texture>(L"Bubble");
			//BGsr->SetTexture(BgTex);


			//Cat

			/*Cat* cat = object::Instantiate<Cat>
				(enums::eLayerType::Animal);
			CatScript* catScript = cat->AddComponent<CatScript>();
			//BoxCollider2D* catCol = cat->AddComponent<BoxCollider2D>();
			CircleCollider2D* catCol = cat->AddComponent<CircleCollider2D>();

			catScript->setPlayer(mPlayer);
			catCol->SetOffset(Vector2(-50.0f, -50.0f));
			//cat->SetActive(false);

			graphcis::Texture* CatTex = Resources::Find<graphcis::Texture>(L"Cat");
			Animator* catAnimator = cat->AddComponent<Animator>();
			catAnimator->CreateAnimation(L"CatDownWalk", CatTex
				, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"CatRightWalk", CatTex
				, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"CatUpWalk", CatTex
				, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"CatLeftWalk", CatTex
				, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"CatSitDown", CatTex
				, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"CatGrooming", CatTex
				, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"CatLayDown", CatTex
				, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

			catAnimator->PlayAnimation(L"CatSitDown", false);
			cat->GetComponent<Transform>()->SetPosition(Vector2(400.0f, 300.0f));
			cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));
			cat->GetComponent<Transform>()->SetRotation(30.0f);
			*/


			//GameObject* sheet = object::Instantiate<GameObject>
			//	(enums::eLayerType::Particle);
			//SpriteRenderer* plScriptsheet = sheet->AddComponent<SpriteRenderer>();

			//graphcis::Texture* mrIdle = Resources::Find<graphcis::Texture>(L"MushroomIdle");
			//plScriptsheet->SetTexture(mrIdle);

			/*graphcis::Texture* tex = new graphcis::Texture();
			tex->Load(L"C:\\Users\\wjstk\\source\\repos\\MinhoEngine\\MinhoEngine_SOURCE\\Resources\\CloudOcean.png");*/
			
			//object::DontDestoryOnLoad(mPlayer);

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
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
	}
	void PlayScene::OnExit()
	{
		Transform* tr = mPlayer->GetComponent<Transform>();
		//tr->SetPosition(Vector2(0, 0));
	}
}