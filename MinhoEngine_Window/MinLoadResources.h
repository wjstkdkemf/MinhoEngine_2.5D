#pragma once
#include "..\\MinhoEngine_SOURCE\\MinResources.h"
#include "..\\MinhoEngine_SOURCE\\MinTexture.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\MinhoEngine_Window.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\MinhoEngine_Window.lib")
#endif

namespace min {
	void LoadResources() {
		Resources::Load<graphcis::Texture>(L"BG", L"C:\\Users\\wjstk\\source\\repos\\MinhoEngine\\MinhoEngine_SOURCE\\Resources\\CloudOcean.png");
		Resources::Load<graphcis::Texture>(L"BG_2", L"..\\MinhoEngine_SOURCE\\Resources\\TitleName.png");
		Resources::Load<graphcis::Texture>(L"TN", L"..\\MinhoEngine_SOURCE\\Resources\\background.png");
		Resources::Load<graphcis::Texture>(L"PackMan", L"..\\MinhoEngine_SOURCE\\Resources\\3.png");

	}
}