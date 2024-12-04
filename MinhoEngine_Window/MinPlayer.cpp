#include "MinPlayer.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"

namespace min {
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
		if (input::GetKey(eKeyCode::Right)) {
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x += 100.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
	void Player::Rander(HDC hdc)
	{
		GameObject::Rander(hdc);
	}
}
