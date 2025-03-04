#include "MinApplication.h"
#include "Mininput.h"
#include "MinTime.h"
#include "MinSceneManager.h"
#include "MinResources.h"
#include "MinCollisionManager.h"
#include "MinUIManager.h"
#include "MinFmod.h"
#include "MinGraphicDevice_DX11.h"
#include "MinRenderer.h"


namespace min {
	//std::vector<GameObject> Application::Bullet = {};

	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mWidth(0)
		, mHeight(0)
		, mBackHdc(NULL)
		, mBackBitmap(NULL)
		, mbLoaded(false)
	{
	}
	Application::~Application()
	{
		
	}
	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		AdjustWindowRect(hwnd, width, height);
		InitializeEtc();

		mGraphicDevice = std::make_unique<graphics::GraphicDevice_DX11>();
		renderer::Initialize();
		mGraphicDevice->Initialize();

		Fmod::Initialize();
		CollisionManager::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();
	}
	void Application::Run()
	{
		if (mbLoaded == false)
			mbLoaded = true;

		Update();
		LateUpdate();
		Render();
		Destory();
	}
	void Application::Update()
	{
		input::Update();
		Time::Update();

		CollisionManager::Update();
		UIManager::Update();
		SceneManager::Update();
	}
	void Application::LateUpdate()
	{
		CollisionManager::LateUpdate();
		UIManager::LateUpdate();
		SceneManager::LateUpdate();
	}
	void Application::Render()
	{
		//clearRenderTarget();
		graphics::GetDevice()->ClearRenderTargetView();
		graphics::GetDevice()->ClearDepthStencilView();
		graphics::GetDevice()->BindViewPort();
		graphics::GetDevice()->BindDefaultRenderTarget();

		Time::Render();
		CollisionManager::Render();
		UIManager::Render();
		SceneManager::Render();
	}
	void Application::Present()
	{
		GetDevice()->Present();
	}
	void Application::Destory()
	{
		SceneManager::Destory();
	}
	void Application::Release()
	{
		SceneManager::Release();
		UIManager::Release();
		Resources::Release();

		renderer::Release();
	}

	void Application::AdjustWindowRect(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);

		RECT rect = { 0, 0, (LONG)width, (LONG)height };
		::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(hwnd, nullptr, 0, 0
			, mWidth
			, mHeight, 0);
		ShowWindow(hwnd, true);
	}
	
	void Application::InitializeEtc()
	{
		input::Initailize();
		Time::Initailize();
	}
}
