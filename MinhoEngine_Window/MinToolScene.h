#pragma once
#include "..\\MinhoEngine_SOURCE\\\MinScene.h"


namespace min
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		~ToolScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

	private:
	};
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);