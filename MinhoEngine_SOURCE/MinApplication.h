#pragma once
#include <DirectXTex.h>
#include <DirectXTex.inl>
#include <DirectXTexEXR.h>

#include "minGameObject.h"
#include "MinGraphicDevice_DX11.h"
#include "SpriteFont.h"

#include "MinEvent.h"
#include "MinWindow.h"
#include "MinApplicationEvent.h"
#include "MinMoushEvent.h"
#include "MinKeyEvent.h"

namespace min{
	class Application
	{
	public:
		Application();
		~Application();
		void Initialize(HWND hwnd, int width, int height);
		void InitializeWindow(HWND hwnd);
		void AdjustWindowRect(HWND hwnd, int width, int height);
		void ReszieGraphicDevice(WindowResizeEvent& e);
		void InitializeEtc();

		void OnEvent(Event& e);

		void Run();
		void Close();

		void Update();
		void LateUpdate();
		void Render();
		void Present();
		void Destory();
		void Release();

		Window GetWindow() { return mWindow; }
		bool IsLoaded() const { return mbLoaded; }
		void IsLoaded(bool load) { mbLoaded = load; }
		bool IsRunning() const { return mbRunning; }
		//std::unique_ptr<graphics::GraphicDevice_DX11> GetDevice() { return mGraphicDevice; };


	private:
		bool mbLoaded;
		bool mbRunning;
		std::unique_ptr<graphics::GraphicDevice_DX11> mGraphicDevice;
		//std::unique_ptr<DirectX::SpriteFont> mFont;


		Window mWindow;
		//std::vector<GameObject*> Bullet;
		//std::vector<Scene*> mScenes;
	};
}

