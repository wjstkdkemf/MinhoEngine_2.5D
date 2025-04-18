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
#include "MinEffect.h"
#include "MinBoxCollider2D.h"
#include "MinCollisionManager.h"
#include "MinDontDestroyOnLoad.h"
#include "MinRigidbody.h"
#include "MinFloor.h"
#include "MinUIManager.h"
#include "MinAudioClip.h"
#include "MinAudioListener.h"
#include "MiNAudioSource.h"
#include "MinGraphicDevice_DX11.h"
#include "MinSpriteRenderer.h"
#include "MinMaterial.h"
#include "MinCameraScript.h"
#include "MinEnemyScript.h"
#include "MinSkillManager.h"
#include "MinShadow.h"

namespace min {
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{	
		Scene::Initialize();
#pragma region Camera
		GameObject* camera = object::Instantiate<GameObject>
			(enums::eLayerType::None, Vector3(0.0f, 0.0f, -5.0f));

		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->SetSize(200.0f);

		CameraScript* cameraScript = camera->AddComponent<CameraScript>();

		mCameraVector.push_back(camera);
		renderer::mainCamera = cameraComp;
#pragma endregion
#pragma region BG
			
		GameObject* BG = object::Instantiate<GameObject>
			(enums::eLayerType::BackGround, Vector3(0.0f , 0.0f , 10.0f));
		BG->GetComponent<Transform>()->SetScale(Vector3(15.0f , 15.0f , 0.0f));

		SpriteRenderer* sr = BG->AddComponent<SpriteRenderer>();
		sr->SetSprite(Resources::Find<graphics::Texture>(L"BG"));

		//BoxCollider2D* mBGBoxCollidder = BG->AddComponent<BoxCollider2D>();
		//mBGBoxCollidder->GetBoxCollider2D().Extents = XMFLOAT3(1.0f, 1.0f, 1.0f); // Vector3(1.0f);
			
#pragma endregion
#pragma region Floor
		Floor* mFloor = object::Instantiate<Floor>(eLayerType::Floor, Vector3(0.0f, -8.0f, 0.0f));
		mFloor->GetComponent<Transform>()->SetScale(15.0f, 15.0f, 0.0f);
		SpriteRenderer* flsr = mFloor->AddComponent<SpriteRenderer>();
		flsr->SetSprite(Resources::Find<graphics::Texture>(L"Floor_1"));
		flsr->SetName(L"Floor_1");

		BoxCollider2D* mBGBoxCollidder = mFloor->AddComponent<BoxCollider2D>();
		mBGBoxCollidder->SetName(L"Floor");
		//mBGBoxCollidder->GetBoxCollider2D().Extents = XMFLOAT3(1.0f, 1.0f, 1.0f); // Vector3(1.0f);
#pragma endregion
#pragma region Player
		Player* mPlayer = object::Instantiate<Player>
			(enums::eLayerType::Player, Vector3(0.0f, 0.0f, 0.0f));//카메라에 가까울수록 depth버퍼가 크다
		mPlayer->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 0.0f);
		mPlayer->SetName(L"Player");
		PlayerScript* prsc = mPlayer->AddComponent<PlayerScript>();
		//SpriteRenderer* prsr = Player->AddComponent<SpriteRenderer>();
		//prsr->SetSprite(Resources::Find<graphics::Texture>(L"Player"));
		Animator* playerAnimator = mPlayer->AddComponent<Animator>();

		playerAnimator->CreateAnimation(L"PlayerWalk_Right", Resources::Find<graphics::Texture>(L"Player")
			,Vector2(0.0f , 0.0f), Vector2(250.0f, 250.0f) , Vector2::Zero , 6 , 0.5f);
		playerAnimator->CreateAnimation(L"PlayerWalk_Left", Resources::Find<graphics::Texture>(L"Player")
			, Vector2(1500.0f, 0.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 6, 0.5f);
		playerAnimator->CreateAnimation(L"Player_Idle", Resources::Find<graphics::Texture>(L"Player")
			, Vector2(0.0f, 500.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 3, 0.3f);
			
		playerAnimator->PlayAnimation(L"Player_Idle",true);

		mPlayer->AddComponent<Rigidbody>();
		mPlayer->AddComponent<Shadow>();

		BoxCollider2D* mPlayerBoxCollidder = mPlayer->AddComponent<BoxCollider2D>();

		SkillManager* prsm = mPlayer->AddComponent<SkillManager>();

		object::DontDestoryOnLoad(mPlayer);
		object::DontDestoryOnLoad(mPlayer->GetComponent<Shadow>()->GetShadow());

		//playerAnimator->CreateAnimationByFolder(L"PlayerWalk", FolderPath, Vector2::Zero, 1.0f);
#pragma endregion
#pragma region Enemy
		GameObject* Enemy = object::Instantiate<GameObject>
			(enums::eLayerType::Enemy, Vector3(-4.0f, 0.0f, 0.0f));//카메라에 가까울수록 depth버퍼가 크다
		Enemy->GetComponent<Transform>()->SetScale(1.0f, 1.0f, 0.0f);
		EnemyScript* Enemysc = Enemy->AddComponent<EnemyScript>();
		//SpriteRenderer* prsr = Player->AddComponent<SpriteRenderer>();
		//prsr->SetSprite(Resources::Find<graphics::Texture>(L"Player"));
		Animator* EnemyAnimator = Enemy->AddComponent<Animator>();

		EnemyAnimator->CreateAnimation(L"PlayerWalk", Resources::Find<graphics::Texture>(L"Player")
			, Vector2(0.0f, 0.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 3, 0.5f);

		EnemyAnimator->CreateAnimation(L"FirstSkill", Resources::Find<graphics::Texture>(L"FirstSkill")
			, Vector2(0.0f, 0.0f), Vector2(386.0f, 246.0f), Vector2::Zero, 8, 2.0f / 8);

		EnemyAnimator->PlayAnimation(L"PlayerWalk", true);

		BoxCollider2D* mEnemyBoxCollidder = Enemy->AddComponent<BoxCollider2D>();
#pragma endregion
		
		cameraScript->SetPlayer(mPlayer);// 카메라가 따라다닐 오브젝트 지정
		cameraScript->SetFieldSize(mFloor->GetComponent<Transform>()->GetScale());//카메라 위치 최대치
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
	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::OnEnter()
	{
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Shadow, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::SkillEffect, eLayerType::Enemy, true);

		UIManager::Push(eUIType::HPBAR);
		//UIManager::Push(eUIType::SkillInventory);
		renderer::mainCamera = mCameraVector[0]->GetComponent<Camera>();

		Scene::OnEnter();
	}
	void PlayScene::OnExit()
	{
		//Transform* tr = mPlayer->GetComponent<Transform>();
		UIManager::Pop(eUIType::HPBAR);
		//tr->SetPosition(Vector2(0, 0));
		Scene::OnExit();
	}
}