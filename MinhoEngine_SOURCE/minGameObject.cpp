#include "minGameObject.h"
#include "mininput.h"
#include "MinTime.h"
#include "MinTransform.h"

namespace min {
	//bool GameObject::shot = false;

	GameObject::GameObject()
		: mState(eState::Active)
		, mLayerType(eLayerType::None)
	{
		mComponents.resize((UINT)enums::eComponentType::End);
		initializeTransform();
	}
	GameObject::~GameObject()
	{
		for (Component* comp : mComponents) {
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}
	}
	
	void GameObject::Initialize()
	{
		for (Component* comp : mComponents) {
			if (comp == nullptr)
				continue;

			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents) {
			if (comp == nullptr)
				continue;

				comp->Update();
		}
		//if (input::GetKey(eKeyCode::A)) {
		//	mX -= speed * Time::DeltaTime();
		//}
		//if (input::GetKey(eKeyCode::D)) {
		//	mX += speed * Time::DeltaTime();
		//}
		//if (input::GetKey(eKeyCode::W)) {
		//	mY -= speed * Time::DeltaTime();
		//}
		//if (input::GetKey(eKeyCode::S)) {
		//	mY += speed * Time::DeltaTime();
		//}
		//if (input::GetKey(eKeyCode::Space)) {
		//	shot = true;
		//}
		//if (GetShot()) {
		//	GameObject* gameobj = new GameObject();
		//	gameobj->mX = mX;
		//	gameobj->mY = mY;
		//	Bullet.push_back(gameobj);
		//	SetShot(false);
		//}
	}
	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents) {
			if (comp == nullptr)
				continue;

			comp->LateUpdate();
		}
	}
	void GameObject::Rander(HDC hdc)
	{
		for (Component* comp : mComponents) {
			if (comp == nullptr)
				continue;

			comp->Render(hdc);
		}
	}
	void GameObject::initializeTransform()
	{
		AddComponent<Transform>();
	}
	/*void GameObject::ShotRander(HDC mHdc)
	{
		mY -= speed * Time::DeltaTime();
		Ellipse(mHdc, 145 + mX, 90 + mY, 155 + mX, 100 + mY);

	}*/


	/*void GameObject::SetShot(bool button)
	{
		shot = button;
	}*/
}