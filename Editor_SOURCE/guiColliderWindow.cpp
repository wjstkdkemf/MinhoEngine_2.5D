#include "guiColliderWindow.h"


namespace gui
{
	ColliderWindow::ColliderWindow()
	{
		SetName("Collider");
		SetSize(ImVec2(300, 600));
	}

	ColliderWindow::~ColliderWindow()
	{
	}

	void ColliderWindow::Initialize()
	{
	}

	void ColliderWindow::Update()
	{
		for (Editor* editor : mEditors)
		{
			editor->Update();
		}
	}

	void ColliderWindow::OnGUI()
	{

		for (Editor* editor : mEditors)
		{
			editor->OnGUI();
		}
	}

	void ColliderWindow::Run()
	{
		bool Active = (bool)GetState();
		ImGui::Begin(GetName().c_str(), &Active, GetFlag());

		Update();
		OnGUI();

		ImGui::End();
	}

	void ColliderWindow::OnEnable()
	{
	}

	void ColliderWindow::OnDisable()
	{
	}

	void ColliderWindow::OnDestroy()
	{
	}

}
