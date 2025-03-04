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

			GameObject* camera = object::Instantiate<GameObject>
				(enums::eLayerType::None, Vector3(00.0f, 0.0f, -10.0f));

			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
			cameraComp->SetSize(200.0f);

			CameraScript* cameraScript = camera->AddComponent<CameraScript>();
			renderer::mainCamera = cameraComp;

			GameObject* player = object::Instantiate<Player>
				(enums::eLayerType::Player);

			object::DontDestoryOnLoad(player);

			SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
			sr->SetSprite(Resources::Find<graphics::Texture>(L"Player"));

			renderer::selectedObject = player;
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
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
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