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
#include "MinCamera.h"
#include "MinCameraScript.h"
#include "MinFloor.h"
#include "MinBoxCollider2D.h"

namespace min {
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Scene::Initialize();
#pragma region Camera
		GameObject* camera = object::Instantiate<GameObject>
			(enums::eLayerType::None, Vector3(0.0f, 0.0f, -5.0f));

		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->SetSize(200.0f);

		CameraScript* cameraScript = camera->AddComponent<CameraScript>();
		renderer::mainCamera = cameraComp;
#pragma endregion
#pragma region Floor
		Floor* mFloor = object::Instantiate<Floor>(eLayerType::Floor, Vector3(0.0f, -8.0f, 0.0f));
		mFloor->GetComponent<Transform>()->SetScale(15.0f, 15.0f, 0.0f);
		SpriteRenderer* flsr = mFloor->AddComponent<SpriteRenderer>();
		flsr->SetSprite(Resources::Find<graphics::Texture>(L"Floor_2"));
		flsr->SetName(L"Floor_2");

		BoxCollider2D* mBGBoxCollidder = mFloor->AddComponent<BoxCollider2D>();
		mBGBoxCollidder->SetName(L"Floor");
		//mBGBoxCollidder->GetBoxCollider2D().Extents = XMFLOAT3(1.0f, 1.0f, 1.0f); // Vector3(1.0f);
#pragma endregion

		Player* mPlayer = (Player*)object::GetDontDestoryOnLoadLayer(eLayerType::Player);

		cameraScript->SetPlayer(mPlayer);// 카메라가 따라다닐 오브젝트 지정
		cameraScript->SetFieldSize(mFloor->GetComponent<Transform>()->GetScale());
	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (input::GetKey(eKeyCode::M)) {
			SceneManager::LoadScene(L"PlayScene");
		}
	}
	void TitleScene::Render()
	{
		Scene::Render();
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