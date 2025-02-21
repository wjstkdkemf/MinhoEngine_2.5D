#pragma once
#include <DirectXTex.h>
#include <DirectXTex.inl>
#include <DirectXTexEXR.h>

#include "minGameObject.h"
#include "MinGraphicDevice_DX11.h"

namespace min{
	class Application
	{
	public:
		Application();
		~Application();
		void Initialize(HWND hwnd, UINT width, UINT height);
		void AdjustWindowRect(HWND hwnd, UINT width, UINT height);
		void InitializeEtc();
		void Run();

		void Update();
		void LateUpdate();
		void Render();
		void Destory();
		void Release();

		HWND GetHwnd() const { return mHwnd; }
		HDC GetHdc() const { return mHdc; }
		UINT GetWidth() const { return mWidth; }
		UINT GetHeight() const { return mHeight; }

		bool IsLoaded() const { return mbLoaded; }
		void IsLoaded(bool load) { mbLoaded = load; }

	private:
		bool mbLoaded;
		std::unique_ptr<graphics::GraphicDevice_DX11> mGraphicDevice;
		HWND mHwnd;
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;

		GameObject mPlayer[2];
		//std::vector<GameObject*> Bullet;
		//std::vector<Scene*> mScenes;
	};
}

