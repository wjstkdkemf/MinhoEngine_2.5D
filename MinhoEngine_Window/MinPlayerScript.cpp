#include "MinPlayerScript.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"
#include "minGameObject.h"
#include "MinAnimator.h"
#include "MinCat.h"
#include "MinObject.h"
#include "MinResources.h"
#include "MinBoxCollider2D.h"
#include "MinCollider.h"
#include "MinRigidbody.h"
#include "MinUIManager.h"

namespace min
{
	PlayerScript::PlayerScript()
		:mState(PlayerScript::eState::idle)
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
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}
	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}
	void PlayerScript::OnCollisionStay(Collider* other)
	{
		
	}
	void PlayerScript::OnCollisionExit(Collider* other)
	{
	}
	void PlayerScript::PlayerEffect()
	{

	}
	void PlayerScript::Idle()
	{
	}
	void PlayerScript::move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		if (input::GetKey(eKeyCode::D)) {
			//pos.x += 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(200.0f, 0.0f));
		}
		if (input::GetKey(eKeyCode::A)) {
			rb->AddForce(Vector2(-200.0f, 0.0f));
			//pos.x -= 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::W)) {
			rb->AddForce(Vector2(0.0f, -200.0f));
			//pos.y -= 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::S)) {
			rb->AddForce(Vector2(0.0f, 200.0f));
			//pos.y += 100.0f * Time::DeltaTime();
		}
		

		tr->SetPosition(pos);
	}
	void PlayerScript::giveWater()
	{
		/*if (mAnimator->IsCompleteAnimation()) 
		{
			mState = PlayerScript::eState::idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}*/
	}
}
