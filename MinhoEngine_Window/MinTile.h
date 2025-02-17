#pragma once
#include "..\\MinhoEngine_SOURCE\minGameObject.h"

namespace min
{
	class Tile : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander() override;

		void SetIndexPosition(int x, int y);

	private:
	};
}

