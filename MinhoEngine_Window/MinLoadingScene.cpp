#include "MinLoadingScene.h"
#include "MinRenderer.h"
#include "MinSceneManager.h"
#include "MinResources.h"
#include "MinTexture.h"

min::LoadingScene::LoadingScene()
	: mbLoadCompleted(false)
{
}

min::LoadingScene::~LoadingScene()
{
	delete mResourcesLoad;
	mResourcesLoad = nullptr;
}

void min::LoadingScene::Initialize()
{
	mResourcesLoad = new std::thread(&LoadingScene::resourcesLoad, this, std::ref(mMutex));
}

void min::LoadingScene::Update()
{
	if (mbLoadCompleted)
	{
		mResourcesLoad->join();

		SceneManager::LoadScene(L"PlayScene");
	}
}

void min::LoadingScene::LateUpdate()
{
}

void min::LoadingScene::Rander(HDC hdc)
{
}

void min::LoadingScene::OnEnter()
{
}

void min::LoadingScene::OnExit()
{
}

void min::LoadingScene::resourcesLoad(std::mutex& m)
{
	m.lock();
	{
		Resources::Load<graphics::Texture>(L"BG", L"C:\\Users\\wjstk\\source\\repos\\MinhoEngine\\Resources\\CloudOcean.png");
		Resources::Load<graphics::Texture>(L"BG_2", L"..\\Resources\\TitleName.png");
		Resources::Load<graphics::Texture>(L"TN", L"..\\Resources\\background.png");
		Resources::Load<graphics::Texture>(L"PackMan", L"..\\Resources\\3.png");
		Resources::Load<graphics::Texture>(L"Chicken", L"..\\Resources\\chicken.bmp");
		Resources::Load<graphics::Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<graphics::Texture>(L"Bubble", L"..\\Resources\\Bubble.png");
		Resources::Load<graphics::Texture>(L"MappleEffect", L"..\\Resources\\ezgif.com-gif-maker.png");
		Resources::Load<graphics::Texture>(L"Player", L"..\\Resources\\Player.bmp");
		Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");
		Resources::Load<graphics::Texture>(L"HPBAR", L"..\\Resources\\HPBAR.bmp");
	}
	m.unlock();

	mbLoadCompleted = true;
}
