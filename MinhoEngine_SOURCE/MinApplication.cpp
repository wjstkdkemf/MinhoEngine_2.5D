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
#include "MinApplicationEvent.h"
#include "MinMoushEvent.h"
#include "MinSkillInformation.h"

namespace min {
	Application::Application()
		: mbLoaded(false)
		, mbRunning(false)
		, mWindow()
	{
		mWindow.SetEventCallBack(MIN_BIND_EVENT_FN(Application::OnEvent));
	}
	Application::~Application()
	{
		
	}
	void Application::Initialize(HWND hwnd, int width, int height)
	{
		mWindow.SetHwnd(hwnd);

		AdjustWindowRect(hwnd, width, height);
		InitializeEtc();

		mGraphicDevice = std::make_unique<graphics::GraphicDevice_DX11>();
		mGraphicDevice->Initialize();

		GetDevice()->GetID3D11Device().Get();

		// = std::make_unique<SpriteFont>(GetDevice()->GetID3D11Device().Get(), L"myfile.spritefont"); //mGraphicDevice.get()->GetID3D11Device().Get()

		renderer::Initialize();

		Fmod::Initialize();
		CollisionManager::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();
		SkillInformation::CreateSkillInformation(); //추후 업데이트 데이터에 대한 스킬 로드도 만들어줘야함

		mbRunning = true;
	}
	void Application::InitializeWindow(HWND hwnd)
	{
		SetWindowPos(hwnd, nullptr,
			mWindow.GetXPos(), mWindow.GetYPos(),
			mWindow.GetWindowWidth(), mWindow.GetWindowHeight(),
			0);
		ShowWindow(hwnd, SW_SHOWDEFAULT);
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
		SceneManager::Update();
		UIManager::Update();
	}
	void Application::LateUpdate()
	{
		CollisionManager::LateUpdate();
		SceneManager::LateUpdate();
		UIManager::LateUpdate();
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
		SceneManager::Render();
		UIManager::Render();

		Microsoft::WRL::ComPtr<ID3D11Texture2D> src = GetDevice()->GetFrameBuffer();
		Microsoft::WRL::ComPtr<ID3D11Texture2D> dst = renderer::FrameBuffer->GetAttachmentTexture(0)->GetTexture();

		GetDevice()->CopyResource(dst.Get(), src.Get());
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

	void Application::AdjustWindowRect(HWND hwnd, int width, int height)
	{
		RECT rect = { 0, 0, (LONG)width, (LONG)height };
		::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		RECT winRect;
		::GetWindowRect(mWindow.GetHwnd(), &winRect);

		//window position
		mWindow.SetPos(winRect.left, winRect.top);

		mWindow.SetWindowWidth(rect.right - rect.left);
		mWindow.SetWindowHeight(rect.bottom - rect.top);

		// window size

		mWindow.SetWidth(width);
		mWindow.SetHeight(height);

		InitializeWindow(hwnd);
	}

	void Application::ReszieGraphicDevice(WindowResizeEvent& e)
	{
		if (mGraphicDevice == nullptr)
			return;

		D3D11_VIEWPORT viewport = {};
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(e.GetWidth());
		viewport.Height = static_cast<float>(e.GetHeight());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		mWindow.SetWidth(viewport.Width);
		mWindow.SetHeight(viewport.Height);

		mGraphicDevice->Resize(viewport);
		renderer::FrameBuffer->Resize(viewport.Width, viewport.Height);
	}

	void Application::Close()
	{
		mbRunning = false;
	}
	
	void Application::InitializeEtc()
	{
		input::Initailize();
		Time::Initailize();
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e) -> bool
		{
			ReszieGraphicDevice(e);
			return true;
		});

		//dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& e) -> bool
		//{
		//	// Todo : MouseMovedEvent
		//	return true;
		//});
	}
}
