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
			Scene::Initialize();
#pragma region Camera
			GameObject* camera = object::Instantiate<GameObject>
				(enums::eLayerType::None, Vector3(0.0f, 0.0f, -10.0f));

			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
			cameraComp->SetSize(200.0f);

			CameraScript* cameraScript = camera->AddComponent<CameraScript>();
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

			//BG->AddComponent<PlayerScript>();
			
#pragma endregion
#pragma region Player
			Player* mPlayer = object::Instantiate<Player>
				(enums::eLayerType::Player, Vector3(5.0f, 0.0f, 0.0f));//카메라에 가까울수록 depth버퍼가 크다
			mPlayer->GetComponent<Transform>()->SetScale(5.0f, 5.0f, 0.0f);
			PlayerScript* prsc = mPlayer->AddComponent<PlayerScript>();
			//SpriteRenderer* prsr = Player->AddComponent<SpriteRenderer>();
			//prsr->SetSprite(Resources::Find<graphics::Texture>(L"Player"));

			object::DontDestoryOnLoad(mPlayer);
			Animator* playerAnimator = mPlayer->AddComponent<Animator>();

			playerAnimator->CreateAnimation(L"PlayerWalk", Resources::Find<graphics::Texture>(L"Player")
				,Vector2(0.0f , 0.0f), Vector2(250.0f, 250.0f) , Vector2::Zero , 3 , 0.5f);

			playerAnimator->PlayAnimation(L"PlayerWalk",true);

			BoxCollider2D* mPlayerBoxCollidder = mPlayer->AddComponent<BoxCollider2D>();
			mPlayerBoxCollidder->GetBoxCollider2D().Extents = XMFLOAT3(0.75f, 1.1f, 0.0f); // Vector3(1.0f);

			SkillManager* prsm = mPlayer->AddComponent<SkillManager>();


			//std::vector<std::wstring> FolderPath;
			//FolderPath.push_back(L"..\\Resources\\char_2\\01_Ninja\\legs\\0.png");
			//FolderPath.push_back(L"..\\Resources\\char_2\\01_Ninja\\legs\\1.png");
			//FolderPath.push_back(L"..\\Resources\\char_2\\01_Ninja\\legs\\2.png");
			//FolderPath.push_back(L"..\\Resources\\char_2\\01_Ninja\\legs\\3.png");
			//FolderPath.push_back(L"..\\Resources\\char_2\\01_Ninja\\legs\\4.png");
			//FolderPath.push_back(L"..\\Resources\\char_2\\01_Ninja\\legs\\5.png");

			//playerAnimator->CreateAnimationByFolder(L"PlayerWalk", FolderPath, Vector2::Zero, 1.0f);
#pragma endregion

#pragma region Enemy
			GameObject* Enemy = object::Instantiate<GameObject>
				(enums::eLayerType::Enemy, Vector3(-5.0f, 0.0f, 0.0f));//카메라에 가까울수록 depth버퍼가 크다
			Enemy->GetComponent<Transform>()->SetScale(5.0f, 5.0f, 0.0f);
			EnemyScript* Enemysc = Enemy->AddComponent<EnemyScript>();
			//SpriteRenderer* prsr = Player->AddComponent<SpriteRenderer>();
			//prsr->SetSprite(Resources::Find<graphics::Texture>(L"Player"));
			Animator* EnemyAnimator = Enemy->AddComponent<Animator>();

			EnemyAnimator->CreateAnimation(L"PlayerWalk", Resources::Find<graphics::Texture>(L"Player")
				, Vector2(0.0f, 0.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 3, 0.5f);

			EnemyAnimator->PlayAnimation(L"PlayerWalk", true);

			BoxCollider2D* mEnemyBoxCollidder = Enemy->AddComponent<BoxCollider2D>();
			mEnemyBoxCollidder->GetBoxCollider2D().Extents = XMFLOAT3(0.75f, 1.1f, 0.0f); // Vector3(1.0f);
#pragma endregion
			//Animation* ani = 

			//renderer::selectedObject = BG;
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
	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::OnEnter()
	{
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);
		/*CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);

		UIManager::Push(eUIType::Button);*/
		Scene::OnEnter();
	}
	void PlayScene::OnExit()
	{
		//Transform* tr = mPlayer->GetComponent<Transform>();
		//UIManager::Pop(eUIType::Button);
		//tr->SetPosition(Vector2(0, 0));
		Scene::OnExit();
	}
}