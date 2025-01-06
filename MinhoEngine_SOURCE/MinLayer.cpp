#include "MinLayer.h"


namespace min {
	Layer::Layer()
		: mGameObjects{}
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
	}
	void Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;

			gameObj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;
			GameObject::eState state = gameObj->GetActive();
			if (state == GameObject::eState::Paused
				|| state == GameObject::eState::Dead)
				continue;

				gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;

			gameObj->LateUpdate();
		}
	}
	void Layer::Rander(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;

			GameObject::eState state = gameObj->GetActive();
			if (state == GameObject::eState::Paused
				|| state == GameObject::eState::Dead)
				continue;

			gameObj->Rander(hdc);
		}
	}
	void Layer::Destroy()
	{
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			GameObject::eState active = (*iter)->GetActive();

			if (active == GameObject::eState::Dead)
			{
				GameObject* deathObj = (*iter);

				iter = mGameObjects.erase(iter);

				delete deathObj;
				deathObj = nullptr;
				continue;
			}

			iter++;
		}
	}


	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		mGameObjects.push_back(gameObject);
	}
}