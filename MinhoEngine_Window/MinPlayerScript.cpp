#include "MinPlayerScript.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"
#include "minGameObject.h"
#include "MinAnimator.h"


namespace min
{
	PlayerScript::PlayerScript()
		:mState(PlayerScript::eState::SitDown)
		,mAnimator(nullptr)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{

	}
	void PlayerScript::Update()
	{
		if (mAnimator == nullptr)
			mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mState)
		{
		case min::PlayerScript::eState::SitDown:
			sitDown();
			break;
		case min::PlayerScript::eState::Walk:
			move();
			break;
		case min::PlayerScript::eState::Sleep:
			break;
		case min::PlayerScript::eState::Attack:
			break;
		case min::PlayerScript::eState::Max:
			break;
		default:
			break;
		}

		//if (input::GetKey(eKeyCode::Right)) {
		//	Transform* tr = GetOwner()->GetComponent<Transform>();
		//	Vector2 pos = tr->GetPosition();
		//	pos.x += 100.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//if (input::GetKey(eKeyCode::Left)) {
		//	Transform* tr = GetOwner()->GetComponent<Transform>();
		//	Vector2 pos = tr->GetPosition();
		//	pos.x -= 100.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//if (input::GetKey(eKeyCode::Up)) {
		//	Transform* tr = GetOwner()->GetComponent<Transform>();
		//	Vector2 pos = tr->GetPosition();
		//	pos.y -= 100.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//if (input::GetKey(eKeyCode::Down)) {
		//	Transform* tr = GetOwner()->GetComponent<Transform>();
		//	Vector2 pos = tr->GetPosition();
		//	pos.y += 100.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Rander(HDC hdc)
	{
	}
	void PlayerScript::sitDown()
	{
		if (input::GetKey(eKeyCode::Right)) {
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"CatRightWalk", true);
		}
		if (input::GetKey(eKeyCode::Left)) {
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"CatLeftWalk", true);
		}
		if (input::GetKey(eKeyCode::Up)) {
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"CatUpWalk", true);
		}
		if (input::GetKey(eKeyCode::Down)) {
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"CatDownWalk", true);
		}
	}
	void PlayerScript::move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (input::GetKey(eKeyCode::Right)) {
			pos.x += 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Left)) {
			pos.x -= 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Up)) {
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Down)) {
			pos.y += 100.0f * Time::DeltaTime();
		}
		tr->SetPosition(pos);

		if (input::GetKeyUp(eKeyCode::Right) 
			|| input::GetKeyUp(eKeyCode::Left)
			|| input::GetKeyUp(eKeyCode::Up)
			|| input::GetKeyUp(eKeyCode::Down)) {
			mState = PlayerScript::eState::SitDown;
			mAnimator->PlayAnimation(L"CatSitDown", false);
		}
	}
}
