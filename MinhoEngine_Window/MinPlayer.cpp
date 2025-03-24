#include "MinPlayer.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"

namespace min {
	Player::Player()
	{
	}
	Player::~Player()
	{
	}
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
	}
	void Player::Rander()
	{
		GameObject::Rander();
	}
}
