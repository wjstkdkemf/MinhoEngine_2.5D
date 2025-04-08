#pragma once
#include "..\\MinhoEngine_SOURCE\minGameObject.h"

namespace min
{
	class SkillGameObject :public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander() override;

		void SetDamage(float damage) { Damage = damage; }
		float GetDamage() { return Damage; }
	private:
		float Damage;
	};
}

