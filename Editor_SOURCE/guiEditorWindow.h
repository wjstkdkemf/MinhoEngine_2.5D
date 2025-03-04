#pragma once
#include "guiEntity.h"

namespace gui
{
	class EditorWindow : public Entity
	{
	public:
		EditorWindow();
		virtual ~EditorWindow();

		virtual void Initialize();
		virtual void Update();
		virtual void OnGUI();
		virtual void OnEnable();
		virtual void OnDisable();
		virtual void OnDestroy();

	private:
	};
}

