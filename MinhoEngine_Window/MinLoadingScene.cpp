#include "MinLoadingScene.h"
#include "MinSceneManager.h"
#include "MinTitleScene.h"
#include "MinPlayScene.h"
#include "MinRenderer.h"
#include "MinSceneManager.h"
#include "MinResources.h"
#include "MinTexture.h"
#include "MinApplication.h"

extern min::Application application;


namespace min
{
	LoadingScene::LoadingScene()
		: mbLoadCompleted(false)
		, mMutex()
		, mResourcesLoad()
	{
	}

	LoadingScene::~LoadingScene()
	{
		delete mResourcesLoad;
		mResourcesLoad = nullptr;
	}

	void LoadingScene::Initialize()
	{
		mResourcesLoad = new std::thread(&LoadingScene::resourcesLoad, this, std::ref(mMutex));
	}

	void LoadingScene::Update()
	{
		//if (mbLoadCompleted)
		//{
		//	mResourcesLoad->join();

		//	SceneManager::LoadScene(L"PlayScene");
		//}
	}

	void LoadingScene::LateUpdate()
	{
	}

	void LoadingScene::Render()
	{
		if (mbLoadCompleted /*&& application.IsLoaded()*/)
		{
			int a = 0;
			//���� ���ξ����尡 ����Ǵµ� �ڽľ����尡 �����ִٸ�
			//�ڽľ����带 ���ξ����忡 ���Խ��� ���ξ����尡 ����Ǳ������� block
			mResourcesLoad->join();
			//���ξ������ ���� �и� ���� �������� ������ �����
			//mResourcesLoadThread->detach();
			SceneManager::LoadScene(L"PlayScene");//TitleScenePlayScene
		}
	}

	void LoadingScene::OnEnter()
	{
	}

	void LoadingScene::OnExit()
	{
	}

	void LoadingScene::resourcesLoad(std::mutex& m)
	{
		while (true)
		{
			if (application.IsLoaded() == true)
				break;
		}

		m.lock();
		{
			/*	Resources::Load<graphics::Texture>(L"BG", L"C:\\Users\\wjstk\\source\\repos\\MinhoEngine\\Resources\\CloudOcean.png");
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
				*/
				//Resources::Load<graphics::Texture>(L"BG", L"C:\\Users\\wjstk\\source\\repos\\MinhoEngine\\Resources\\CloudOcean.png");
			Resources::Load<graphics::Texture>(L"Player", L"..\\Resources\\Player.bmp");
			Resources::Load<graphics::Texture>(L"BG", L"..\\Resources\\background.png");
			Resources::Load<graphics::Texture>(L"FirstSkill", L"..\\Resources\\FirstSkill.png");
			Resources::Load<graphics::Texture>(L"Shadow", L"..\\Resources\\shadow.png");
			Resources::Load<graphics::Texture>(L"Bubble", L"..\\Resources\\Bubble.png");
			Resources::Load<graphics::Texture>(L"Floor_1", L"..\\Resources\\Char\\BG\\Bg_Beach.png");


			//renderer::Initialize();

			SceneManager::CreateScene<TitleScene>(L"TitleScene");
			SceneManager::CreateScene<PlayScene>(L"PlayScene");
		}
		m.unlock();

		SceneManager::SetActiveScene(L"LoadingScene");

		mbLoadCompleted = true;
	}
}
