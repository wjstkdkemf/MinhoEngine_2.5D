#pragma once
#include "commoninclude.h"
#include "MinComponent.h"

namespace min {
	class GameObject
	{
	public:
		GameObject();
		~GameObject();
		
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Rander(HDC hdc);
		//virtual void ShotRander(HDC mHdc);

		/*bool GetShot() { return shot; };
		void SetShot(bool button);*/

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			comp->Initialize();
			comp->SetOwner(this);
			mComponents.push_back(comp);

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			T* component = nullptr;
			for (Component* comp : mComponents) {
				component = dynamic_cast<T*>(comp);
				if (component)
					break;
			}

			return component;
		}

	private:
		void initializeTransform();

	private:
		//static bool shot;
		std::vector<Component*> mComponents;
		//std::vector<GameObject*> Bullet;
	};
}

