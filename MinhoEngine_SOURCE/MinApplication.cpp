#include "MinApplication.h"
#include "Mininput.h"
#include "MinTime.h"
#include "MinSceneManager.h"


namespace min {
	//std::vector<GameObject> Application::Bullet = {};

	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mWidth(0)
		, mHeight(0)
		, mBackHdc(NULL)
		, mBackBitmap(NULL)
		, Bullet{}
	{
	}
	Application::~Application()
	{
		
	}
	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		adjustWindowRect(hwnd, width, height);
		createBuffer(width, height);
		initializeEtc();

		SceneManager::Initialize();
	}
	void Application::Run()
	{
		Update();
		LateUpdate();
		Rander();
	}
	void Application::Update()
	{
		input::Update();
		Time::Update();
		SceneManager::Update();//mPlayer[0].Update(); 대체

		mPlayer[0].Update();
		//	mPlayer[1].Update_2();
		if (mPlayer->GetShot()) {
			GameObject* gameobj = new GameObject(mPlayer[0]);
			Bullet.push_back(gameobj);
			mPlayer->SetShot(false);
		}
	}
	void Application::LateUpdate()
	{
	}
	void Application::Rander()
	{
		clearRenderTarget();

		Time::Render(mBackHdc);
		SceneManager::Rander(mBackHdc);// 아래 대체할예정
		mPlayer[0].Rander(mBackHdc);
		
		for(size_t i=0; i< Bullet.size(); i++){
			Bullet[i]->ShotRander(mBackHdc);
		}
		/*std::for_each(bullet.begin(), bullet.end(), [&](gameobject bullets)
		{
			bullets.shotrander(mbackhdc);
		});*/
	//	mPlayer[1].Rander_2(mBackHdc);

		copyRenderTarget(mBackHdc, mHdc);
	}
	void Application::clearRenderTarget()
	{
		Rectangle(mBackHdc, -1, -1, 1921, 1081);
	}
	void Application::copyRenderTarget(HDC source, HDC dest)
	{
		BitBlt(dest, 0, 0, mWidth, mHeight
			, source, 0, 0, SRCCOPY);
	}
	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(hwnd, nullptr, 0, 0
			, mWidth
			, mHeight, 0);
		ShowWindow(hwnd, true);
	}
	void Application::createBuffer(UINT width, UINT height)
	{
		mBackBitmap = CreateCompatibleBitmap(mHdc
			, width
			, height);

		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);
	}
	void Application::initializeEtc()
	{
		input::Initailize();
		Time::Initailize();
	}
}
