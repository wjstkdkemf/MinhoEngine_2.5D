#pragma once
#include "..\\MinhoEngine_SOURCE\minGameObject.h"

namespace min
{
	class Floor : public GameObject
	{
	public:
		Floor();
		~Floor();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander(HDC hdc) override;


	private:
	};
}

