#include "guiEditorApplication.h"

#include "guiInspectorWindow.h"
#include "..\\MinhoEngine_SOURCE\\MinApplication.h"
#include "..\\MinhoEngine_SOURCE\\MinRenderer.h"
#include "..\\MinhoEngine_SOURCE\\MinGameObject.h"
#include "..\\MinhoEngine_SOURCE\\MinTransform.h"
#include "..\\MinhoEngine_SOURCE\\Mininput.h"

extern min::Application application;

namespace gui
{
	ImguiEditor* EditorApplication::mImguiEditor = nullptr;
	std::map<std::wstring, EditorWindow*> EditorApplication::mEditorWindows;
	ImGuiWindowFlags EditorApplication::mFlag = ImGuiWindowFlags_None;
	ImGuiDockNodeFlags EditorApplication::mDockspaceFlags = ImGuiDockNodeFlags_None;
	EditorApplication::eState EditorApplication::mState = EditorApplication::eState::Active;
	bool EditorApplication::mFullScreen = true;
	bool EditorApplication::mPadding = false;
	min::math::Vector2 EditorApplication::mViewportBounds[2] = {};
	min::math::Vector2 EditorApplication::mViewportSize;
	bool EditorApplication::mViewportFocused = false;
	bool EditorApplication::mViewportHovered = false;
	min::graphics::RenderTarget* EditorApplication::mFrameBuffer = nullptr;
	int EditorApplication::mGuizmoType = -1;
	min::EventCallbackFn EditorApplication::mEventCallback = nullptr;

	bool EditorApplication::Initialize()
	{
		mImguiEditor = new ImguiEditor();
		mFrameBuffer = min::renderer::FrameBuffer;

		mImguiEditor->Initialize();
		InspectorWindow* inspector = new InspectorWindow();
		mEditorWindows.insert(std::make_pair(L"InspectorWindow", inspector));
		mEventCallback = &EditorApplication::OnEvent;

		return true;
	}

	void EditorApplication::Update()
	{
	}

	void EditorApplication::OnGUI()
	{
		mImguiEditor->Begin();
		OnImguiRender();
		mImguiEditor->End();
	}

	void EditorApplication::Run()
	{
		Update();
		OnGUI();
	}

	void EditorApplication::Release()
	{
		for (auto iter : mEditorWindows)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		// Cleanup
		delete mImguiEditor;
		mImguiEditor = nullptr;
	}

	void EditorApplication::OnEvent(min::Event& e)
	{
		min::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<min::KeyPressedEvent>([](min::KeyPressedEvent& e) -> bool
		{
			// Todo : KeyPressedEvent
			if (OnKeyPressed(e))
				return true;

			return false;
		});

		dispatcher.Dispatch<min::KeyReleasedEvent>([](min::KeyReleasedEvent& e) -> bool
		{
			// Todo : KeyReleasedEvent
			//if (OnKeyPressed(e))
				//return true;

			return false;
		});

		dispatcher.Dispatch<min::MouseMovedEvent>([](min::MouseMovedEvent& e) -> bool
		{
			// Todo : MouseMovedEvent

			return true;
		});
		if (!e.Handled)
		{
			mImguiEditor->OnEvent(e);
		}
	}

	void EditorApplication::OpenProject()
	{

	}

	void EditorApplication::NewScene()
	{

	}

	void EditorApplication::SaveScene()
	{

	}

	void EditorApplication::SaveSceneAs()
	{

	}
	void EditorApplication::OpenScene(const std::filesystem::path& path)
	{

	}

	void EditorApplication::OnImguiRender()
	{
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		mFlag = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (mFullScreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			mFlag |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			mFlag |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (mDockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
			mFlag |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		bool Active = static_cast<bool>(mState);
		ImGui::Begin("EditorApplication", &Active, mFlag);
		ImGui::PopStyleVar();

		if (mFullScreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), mDockspaceFlags);
		}

		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open Project...", "Ctrl+O"))
					OpenProject();

				ImGui::Separator();

				if (ImGui::MenuItem("New Scene", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
					SaveScene();

				if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
					SaveSceneAs();

				ImGui::Separator();

				if (ImGui::MenuItem("Exit"))
					application.Close();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Script"))
			{
				if (ImGui::MenuItem("Reload assembly", "Ctrl+R"))
				{
					//ScriptEngine::ReloadAssembly(); ÃßÈÄ C#½ºÅ©¸³Æ® Ãß°¡±â´ÉÀÌ »ý±â¸é Ãß°¡ÇÒ ¿¹Á¤
				}

				ImGui::EndMenu();
			}


			ImGui::EndMenuBar();
		}

		for (auto& iter : mEditorWindows)
			iter.second->Run();

		// viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Scene");

		const auto viewportMinRegion = ImGui::GetWindowContentRegionMin(); // ¾ÀºäÀÇ ÃÖ¼Ò ÁÂÇ¥
		const auto viewportMaxRegion = ImGui::GetWindowContentRegionMax(); // ¾ÀºäÀÇ ÃÖ´ë ÁÂÇ¥
		const auto viewportOffset = ImGui::GetWindowPos(); // ¾ÀºäÀÇ À§Ä¡

		constexpr int letTop = 0;
		constexpr int rightBottom = 1;
		mViewportBounds[letTop] = Vector2{ viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		mViewportBounds[rightBottom] = Vector2{ viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		// check if the mouse,keyboard is on the Sceneview
		mViewportFocused = ImGui::IsWindowFocused();
		mViewportHovered = ImGui::IsWindowHovered();

		mImguiEditor->BlockEvent(!mViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		mViewportSize = Vector2{ viewportPanelSize.x, viewportPanelSize.y };
		min::graphics::Texture* texture = mFrameBuffer->GetAttachmentTexture(0);
		ImGui::Image((ImTextureID)texture->GetSRV().Get(), ImVec2{ mViewportSize.x, mViewportSize.y }
		, ImVec2{ 0, 0 }, ImVec2{ 1, 1 });

		// Open Scene by drag and drop
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PROJECT_ITEM"))
			{
				const auto path = static_cast<const wchar_t*>(payload->Data);
				OpenScene(path);
			}
			ImGui::EndDragDropTarget();
		}

		// To do : guizmo
		min::GameObject* selectedObject = min::renderer::selectedObject;
		if (selectedObject && mGuizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			ImGuizmo::SetGizmoSizeClipSpace(0.15f);
			ImGuizmo::SetRect(mViewportBounds[0].x, mViewportBounds[0].y
				, mViewportBounds[1].x - mViewportBounds[0].x, mViewportBounds[1].y - mViewportBounds[0].y);

			// To do : guizmo...
			// game view camera setting

			// Scene Camera
			const min::math::Matrix& viewMatrix = min::renderer::mainCamera->GetViewMatrix();
			const min::math::Matrix& projectionMatrix = min::renderer::mainCamera->GetProjectionMatrix();

			// Object Transform
			min::Transform* transform = selectedObject->GetComponent<min::Transform>();
			min::math::Matrix worldMatrix = transform->GetWorldMatrix();

			// snapping
			bool snap = min::input::GetKey(min::eKeyCode::Leftcontrol);
			float snapValue = 0.5f;

			// snap to 45 degrees for rotation
			if (mGuizmoType == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(*viewMatrix.m, *projectionMatrix.m, static_cast<ImGuizmo::OPERATION>(mGuizmoType)
				, ImGuizmo::WORLD, *worldMatrix.m, nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				// Decompose matrix to translation, rotation and scale
				float translation[3];
				float rotation[3];
				float scale[3];
				ImGuizmo::DecomposeMatrixToComponents(*worldMatrix.m, translation, rotation, scale);

				// delta rotation from the current rotation
				min::math::Vector3 deltaRotation = Vector3(rotation) - transform->GetRotation();
				deltaRotation = transform->GetRotation() + deltaRotation;

				// set the new transform
				transform->SetScale(Vector3(scale));
				transform->SetRotation(Vector3(deltaRotation));
				transform->SetPosition(Vector3(translation));
			}
		}

		ImGui::End();	// Scene end
		ImGui::PopStyleVar();

		ImGui::End(); // dockspace end
	}

	void EditorApplication::SetKeyPressed(int keyCode, int scancode, int action, int mods)
	{
		constexpr int RELEASE = 0;
		constexpr int PRESS = 1;
		constexpr int REPEAT = 2;

		//To do : repeat check
		//if (action == PRESS)
			//action = REPEAT;
		//static std::unordered_map<key, >

		// unordered map key setting



		switch (action)
		{
		case RELEASE:
		{
			min::KeyReleasedEvent event(static_cast<min::eKeyCode>(keyCode));

			if (mEventCallback)
				mEventCallback(event);
		}
		break;
		case PRESS:
		{
			min::KeyPressedEvent event(static_cast<min::eKeyCode>(keyCode), false);

			if (mEventCallback)
				mEventCallback(event);
		}
		break;
		case REPEAT:
		{
			min::KeyPressedEvent event(static_cast<min::eKeyCode>(keyCode), true);

			if (mEventCallback)
				mEventCallback(event);
		}
		break;
		}
	}

	bool EditorApplication::OnKeyPressed(min::KeyPressedEvent& e)
	{
		if (e.IsRepeat())
			return false;

		bool control = min::input::GetKey(min::eKeyCode::Leftcontrol) || min::input::GetKey(min::eKeyCode::RightControl);
		bool shift = min::input::GetKey(min::eKeyCode::LeftShift) || min::input::GetKey(min::eKeyCode::RightShift);

		switch (e.GetKeyCode())
		{
			// Gizmos
		case min::eKeyCode::Q:
		{
			if (!ImGuizmo::IsUsing())
				SetGuizmoType(-1);
			break;
		}
		case min::eKeyCode::W:
		{
			if (!ImGuizmo::IsUsing())
				SetGuizmoType(ImGuizmo::OPERATION::TRANSLATE);
			break;
		}
		case min::eKeyCode::E:
		{
			if (!ImGuizmo::IsUsing())
				SetGuizmoType(ImGuizmo::OPERATION::ROTATE);
			break;
		}
		case min::eKeyCode::R:
		{
			if (control)
			{
				//ScriptEngine::ReloadAssembly();
			}
			else
			{
				if (!ImGuizmo::IsUsing())
					SetGuizmoType(ImGuizmo::OPERATION::SCALE);
			}
			break;
		}
		}

		return true;
	}

	void EditorApplication::SetCursorPos(double x, double y)
	{
		min::MouseMovedEvent event(x, y);

		if (mEventCallback)
			mEventCallback(event);
	}
}