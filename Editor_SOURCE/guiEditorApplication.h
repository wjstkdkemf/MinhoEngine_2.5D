#pragma once
#include "guiEditor.h"
#include "guiEditorWindow.h"

namespace gui
{
	class EditorApplication
	{
	public:
		///<summary>
		///에디터를 초기화합니다.
		///</summary>
		static bool Initialize();

		/// <summary>
		/// 에디터를 로직을 업데이트합니다.
		/// </summary>
		static void Update();

		/// <summary>
		/// 에디터 렌더링을 업데이트합니다.
		/// </summary>
		static void OnGUI();

		/// <summary>
		/// 에디터 업데이트
		/// </summary>
		static void Run();

		/// <summary>
		/// 에디터를 종료합니다.
		/// </summary>
		static void Release();

	private:
		static bool imGguiInitialize();
		static void imGuiRender();
	};
};


