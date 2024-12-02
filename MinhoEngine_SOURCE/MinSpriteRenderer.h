#pragma once
#include "MinEntity.h"
#include "minComponent.h"

namespace min {
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander(HDC hdc) override;
	private:
	};
}

