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
			//만약 메인쓰레드가 종료되는데 자식쓰레드가 남아있다면
			//자식쓰레드를 메인쓰레드에 편입시켜 메인쓰레드가 종료되기전까지 block
			mResourcesLoad->join();
			//메인쓰레드와 완전 분리 시켜 독립적인 쓰레드 운영가능
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
			Resources::Load<graphics::Texture>(L"Floor_2", L"..\\Resources\\//CloudOcean.png");//CloudOcean.png
			Resources::Load<graphics::Texture>(L"HPBAR", L"..\\Resources\\HPBAR.bmp");
			//Resources::Load<graphics::Texture>(L"NoneSkill", L"..\\Resources\\char_2\\Background\\00_Icon\\Fase1.png");
			Resources::Load<graphics::Texture>(L"Skill_1", L"..\\Resources\\char_2\\Background\\00_Icon\\Fase2.png");
			Resources::Load<graphics::Texture>(L"Skill_2", L"..\\Resources\\char_2\\Background\\00_Icon\\Fase3.png");
			Resources::Load<graphics::Texture>(L"Skill_3", L"..\\Resources\\char_2\\Background\\00_Icon\\Fase4.png");

			Resources::Load<graphics::Texture>(L"NoneSkill", L"..\\Resources\\UI\\PNG\\Extra\\Default\\button_square_depth_line.png");
			Resources::Load<graphics::Texture>(L"SkillBG", L"..\\Resources\\UI\\PNG\\Extra\\Default\\button_rectangle_depth_line.png");

			//renderer::Initialize();
			
			SceneManager::CreateScene<PlayScene>(L"PlayScene");
			SceneManager::CreateScene<TitleScene>(L"TitleScene");
			
		}
		m.unlock();

		SceneManager::SetActiveScene(L"LoadingScene");

		mbLoadCompleted = true;
	}
}
