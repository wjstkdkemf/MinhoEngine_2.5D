#include "MinApplication.h"
#include "Mininput.h"
#include "MinTime.h"
#include "MinSceneManager.h"
#include "MinResources.h"


namespace min {
	//std::vector<GameObject> Application::Bullet = {};

	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mWidth(0)
		, mHeight(0)
		, mBackHdc(NULL)
		, mBackBitmap(NULL)
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
		Destory();
	}
	void Application::Update()
	{
		input::Update();
		Time::Update();
		SceneManager::Update();
	}
	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}
	void Application::Rander()
	{
		clearRenderTarget();

		Time::Render(mBackHdc);
		SceneManager::Rander(mBackHdc);

		copyRenderTarget(mBackHdc, mHdc);
	}
	void Application::Destory()
	{
		SceneManager::Destory();
	}
	void Application::Release()
	{
		SceneManager::Release();
		Resources::Release();
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
