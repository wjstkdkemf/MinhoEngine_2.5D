#pragma once
#include "MinScene.h"

namespace min 
{
	class DontDestroyOnLoad : public Scene
	{
	public:
		DontDestroyOnLoad();
		~DontDestroyOnLoad();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander() override;

		void OnEnter() override;
		void OnExit() override;
	};
}

