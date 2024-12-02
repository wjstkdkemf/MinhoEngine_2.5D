#pragma once
#include "MinEntity.h"

namespace min {
	class GameObject;
	class Component : public Entity
	{
	public:
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Rander(HDC hdc);

		void SetOwner(GameObject* owner) { mOwner = owner; };
		GameObject* GetOwner() { return mOwner; };
	private:
		GameObject* mOwner;
		// 전방선언을 해야함.
	};
}

