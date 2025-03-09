#pragma once
#include "guiEditor.h"
#include "guiEditorWindow.h"
#include "guiImguiEditor.h"

#include "..\\MinhoEngine_SOURCE\\MinRenderTarget.h"
#include "..\\MinhoEngine_SOURCE\\MinEvent.h"
#include "..\\MinhoEngine_SOURCE\MinKeyEvent.h"
#include "..\\MinhoEngine_SOURCE\\MinMoushEvent.h"


namespace min
{
	class KeyPressEvent;
}

namespace gui
{
	class EditorApplication
	{
	public:
		enum class eState
		{
			Disable,
			Active,
			Destroy,
		};

		template <typename T>
		T* GetWindow(const std::wstring& name)
		{
			auto iter = mEditorWindows.find(name);
			if (iter == mEditorWindows.end())
				return nullptr;

			return dynamic_cast<T*>(iter->second);
		}
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

		static void OnEvent(min::Event& e);

		static void OpenProject();
		static void NewScene();
		static void SaveScene();
		static void SaveSceneAs();
		static void OpenScene(const std::filesystem::path& path);

		static void OnImguiRender();
		
		static void SetKeyPressed(int keyCode, int scancode, int action, int mods);
		static bool OnKeyPressed(min::KeyPressedEvent& e);


		static void SetGuizmoType(int type) { mGuizmoType = type; }

		static void SetCursorPos(double x, double y);

	private:
		static ImguiEditor* mImguiEditor;

		static std::map<std::wstring, EditorWindow*> mEditorWindows;
		static ImGuiWindowFlags mFlag;
		static ImGuiDockNodeFlags mDockspaceFlags;
		static eState mState;
		static bool mFullScreen;
		static bool mPadding;
		static min::math::Vector2 mViewportBounds[2];
		static min::math::Vector2 mViewportSize;
		static bool mViewportFocused;
		static bool mViewportHovered;
		static int mGuizmoType;

		static min::graphics::RenderTarget* mFrameBuffer;
		static min::EventCallbackFn mEventCallback;
	};
};


