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

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			comp->Initialize();
			comp->SetOwner(this);
			mComponents[(UINT)comp->GetType()] = comp;
			//mComponents.push_back(comp);

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
		std::vector<Component*> mComponents;
	};
}

