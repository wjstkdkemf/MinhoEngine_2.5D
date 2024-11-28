#pragma once
#include "minEntity.h"
#include "minGameObject.h"

namespace min {
	class Scene : public Entity
	{
	public :
		Scene();
		~Scene();

		virtual void initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Rander(HDC hdc);

		void AddGameObject(GameObject* gameObject);

	private :
		std::vector<GameObject*> mGameObjects;
	};
}

