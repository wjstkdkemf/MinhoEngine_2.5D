#pragma once
#include "..\\MinhoEngine_SOURCE\minGameObject.h"


namespace min {
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander() override;
	private:
	};
}

