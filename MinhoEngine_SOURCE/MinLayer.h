#pragma once
#include "MinEntity.h"
#include "commoninclude.h"
#include "minGameObject.h"

namespace min {
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Rander(HDC hdc);
		virtual void Destroy();

		void AddGameObject(GameObject* gameObject);

	private:
		//eLayerType mType;
		std::vector<GameObject*> mGameObjects;
	};

	typedef std::vector<GameObject*>::iterator GameObjectIter;
}

