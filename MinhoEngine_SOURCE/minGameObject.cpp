#include "minGameObject.h"
#include "mininput.h"
#include "MinTime.h"

namespace min {
	//bool GameObject::shot = false;

	GameObject::GameObject()
	{
	}
	GameObject::~GameObject()
	{
		for (Component* comp : mComponents) {
			delete comp;
			comp = nullptr;
		}
	}
	
	void GameObject::Initialize()
	{
		for (Component* comp : mComponents) {
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents) {
			for (Component* comp : mComponents) {
				comp->Update();
			}
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
			for (Component* comp : mComponents) {
				comp->LateUpdate();
			}
		}
	}
	void GameObject::Rander(HDC hdc)
	{
		for (Component* comp : mComponents) {
			for (Component* comp : mComponents) {
				comp->Rander(hdc);
			}
		}
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