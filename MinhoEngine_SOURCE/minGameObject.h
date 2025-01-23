#pragma once
#include "commoninclude.h"
#include "MinComponent.h"

namespace min::object
{
	void Destroy(GameObject* gameObject);
}

namespace min {
	class GameObject : public Entity
	{
	public:
		//friend void object::Destory(GameObject* obj);

		enum class eState
		{
			Active,
			Paused,
			Dead,
			End
		};


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

		void SetActive(bool power)
		{
			if (power)
				mState = eState::Active;
			else
				mState = eState::Paused;
		}
		eState GetState() { return mState; }
		bool IsActive() { return mState == eState::Active; }
		bool IsDead() { return mState == eState::Dead; }

		void death() { mState = eState::Dead; }
		void SetLayerType(eLayerType layer) { mLayerType = layer; }
		eLayerType GetLayerType() { return mLayerType; }

		

	private:
		void initializeTransform();
		

	private:
		std::vector<Component*> mComponents;
		eState mState;
		eLayerType mLayerType;
	};
}

