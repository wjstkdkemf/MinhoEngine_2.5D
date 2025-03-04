#pragma once
#include "minEntity.h"
#include "minGameObject.h"
#include "MinLayer.h"

namespace min {
	class Scene : public Entity
	{
	public :
		Scene();
		~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destory();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObj,const enums::eLayerType type);
		void EraseGameObject(GameObject* gameObj);
		Layer* GetLayer(const enums::eLayerType type) { return mLayer[(UINT)type]; }

	private :
		void CreateLayers();

	private :
		std::vector<Layer*> mLayer;
	};
}

