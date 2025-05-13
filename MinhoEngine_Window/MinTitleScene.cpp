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
#include "MinShadow.h"
#include "MinEffect.h"
#include "MinBoxCollider2D.h"
#include "MinUIManager.h"

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
		mCameraVector.push_back(camera);
		renderer::mainCamera = cameraComp;
#pragma endregion
#pragma region BG
		GameObject* BG = object::Instantiate<GameObject>
			(enums::eLayerType::BackGround, Vector3(0.0f, 0.0f, 0.0f));
		BG->GetComponent<Transform>()->SetScale(Vector3(8.0f, 8.0f, 0.0f));

		SpriteRenderer* sr = BG->AddComponent<SpriteRenderer>();//
		sr->SetSprite(Resources::Find<graphics::Texture>(L"Floor_2"));//TitleMenu
#pragma endregion

#pragma region TitleName
		GameObject* TitleName = object::Instantiate<GameObject>
			(enums::eLayerType::BackGround, Vector3(0.0f, 1.0f, 0.0f));
		TitleName->GetComponent<Transform>()->SetScale(Vector3(2.0f, 1.0f, 0.0f));

		SpriteRenderer* tnsr = TitleName->AddComponent<SpriteRenderer>();//
		
		tnsr->SetSprite(Resources::Find<graphics::Texture>(L"TitleName"));//TitleMenu
#pragma endregion
		//cameraScript->SetPlayer(mPlayer);// 카메라가 따라다닐 오브젝트 지정
		//cameraScript->SetFieldSize(mFloor->GetComponent<Transform>()->GetScale());

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
		UIManager::Push(eUIType::TitleButton);
		renderer::mainCamera = mCameraVector[0]->GetComponent<Camera>();

		Player* mPlayer = (Player*)object::GetDontDestoryOnLoadLayer(eLayerType::Player);
		mPlayer->SetActive(false);

		Effect* mShadow = (Effect*)object::GetDontDestoryOnLoadLayer(eLayerType::Shadow);
		mShadow->SetActive(false);

		Scene::OnEnter();
	}
	void TitleScene::OnExit(){
		UIManager::Pop(eUIType::TitleButton);

		Player* mPlayer = (Player*)object::GetDontDestoryOnLoadLayer(eLayerType::Player);
		mPlayer->SetActive(true);
		Shadow* mShadow = (Shadow*)object::GetDontDestoryOnLoadLayer(eLayerType::Shadow);
		mShadow->GetShadow()->SetActive(true);

		Scene::OnExit();
	}
}