#include "MinPlayerScript.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"
#include "minGameObject.h"
#include "MinAnimator.h"
#include "MinEffect.h"
#include "MinObject.h"
#include "MinResources.h"
#include "MinBoxCollider2D.h"
#include "MinCollider.h"
#include "MinRigidbody.h"
#include "MinUIManager.h"
#include "MinSkillManager.h"
#include "MinSpriteRenderer.h"
#include "MinCamera.h"

namespace min
{
	PlayerScript::PlayerScript()
		: mState(PlayerScript::eState::idle)
		, mAnimator(nullptr)
		, Skill_info(nullptr)
		, mDelayTime(2.0f)
		, mGravity(0.05f)
		, isJump(false)
		, mJumpingTime(0.0f)
		, mFront(true)
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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if(Skill_info == nullptr)
		{
			Skill_info = object::Instantiate<GameObject>(enums::eLayerType::Skill_info, Vector3(Camera::GetCameraPosition().x, Camera::GetCameraPosition().y - 2.0f, Camera::GetCameraPosition().z + 1.0f));
			Skill_info->GetComponent<Transform>()->SetScale(0.3f, 0.3f, 0);
			SpriteRenderer* sksr = Skill_info->AddComponent<SpriteRenderer>();
			sksr->SetSprite(Resources::Find<graphics::Texture>(L"Bubble"));
		}

		if (mAnimator == nullptr)
			mAnimator = GetOwner()->GetComponent<Animator>();

		if (mDelayTime < 2.0f)
			mDelayTime += Time::DeltaTime();

		Jumping();

		switch (mState)
		{
		case min::PlayerScript::eState::idle:
			Idle();
			break;
		case min::PlayerScript::eState::Walk:
			move();
			break;
		case min::PlayerScript::eState::Jump:
			//Jumping();
			break;
		case min::PlayerScript::eState::Skill:
			SkillActive();
			break;
		case min::PlayerScript::eState::Attack:
			break;
		case min::PlayerScript::eState::Max:
			break;
		default:
			break;
		}
	}
	void PlayerScript::LateUpdate()
	{
		//Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		//Skill_info->GetComponent<Transform>()->SetPosition(Camera::GetCameraPosition().x, Camera::GetCameraPosition().y - 2.0f, Camera::GetCameraPosition().z + 1.0f);
	}
	void PlayerScript::Render()
	{
	}
	void PlayerScript::OnCollisionEnter(Collider* other)
	{
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
#pragma region 이동관련 구현(WASD)
		if (input::GetKey(eKeyCode::D)) {
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"PlayerWalk_Right");
			mFront = true;
		}
		if (input::GetKey(eKeyCode::A)) {
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"PlayerWalk_Left");
			mFront = false;
		}
		if (input::GetKey(eKeyCode::W)) {
			mState = eState::Walk;
		}
		if (input::GetKey(eKeyCode::S)) {
			mState = eState::Walk;
		}
#pragma region Jump and Gravity
		if (input::GetKey(eKeyCode::SpaceVar))
		{
			if (!isJump)
				isJump = true;
		}
#pragma endregion
#pragma endregion
#pragma region Skill
		if (input::GetKey(eKeyCode::Q)) {
			mState = eState::Walk;
		}
		if (input::GetKey(eKeyCode::E)) {
			mState = eState::Walk;
		}
#pragma endregion
	}
	void PlayerScript::move()
	{
		Rigidbody* rd = GetOwner()->GetComponent<Rigidbody>();
		SkillManager* sm = GetOwner()->GetComponent<SkillManager>();

#pragma region 이동관련 구현(WASD)
		if (input::GetKey(eKeyCode::D)) {
			rd->AddForce(Vector3(300.0f, 0.0f, 0.0f));
		}
		if (input::GetKey(eKeyCode::A)) {
			rd->AddForce(Vector3(-300.0f, 0.0f, 0.0f));
			mFront = false;
		}
		if (input::GetKey(eKeyCode::W)) {
			rd->AddForce(Vector3(0.0f, 300.0f, 0.0f));
		}
		if (input::GetKey(eKeyCode::S)) {
			rd->AddForce(Vector3(0.0f, -300.0f, 0.0f));
		}
#pragma endregion
#pragma region Skill
		if (input::GetKey(eKeyCode::Q)) {
			if (mDelayTime >= 2.0f)
			{
				sm->UseSkill(L"FirstSkill", mFront);
				mDelayTime = 0.0f;
			}
		}
		if (input::GetKey(eKeyCode::E)) {
			sm->UseSkill(L"SecondSkill", mFront);
		}
		if (input::GetKey(eKeyCode::SpaceVar))
		{
			if (!isJump)
				isJump = true;
		}
#pragma endregion
#pragma endregion

		if (input::GetKeyUp(eKeyCode::D) || input::GetKeyUp(eKeyCode::A) || input::GetKeyUp(eKeyCode::W) || input::GetKeyUp(eKeyCode::S)
			|| input::GetKeyUp(eKeyCode::Q) || input::GetKeyUp(eKeyCode::E))
		{
			rd->ResetForce();
			mState = eState::idle;
			mAnimator->PlayAnimation(L"Player_Idle");
		}
	}
	void PlayerScript::SkillActive()
	{
		/*if (mAnimator->IsCompleteAnimation()) 
		{
			mState = PlayerScript::eState::idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}*/
	}
	void PlayerScript::Jumping()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (isJump)
		{
			GetOwner()->GetComponent<Rigidbody>()->SetGround(false);
			GetOwner()->GetComponent<Rigidbody>()->AddForce(Vector3(0.0f, 100.0f, 0.0f));
			isJump = false;
			//if (mJumpingTime < 0.5f) // 추후 중력 계수로 해서 수정 가능
			//{
			//	Vector3 pos = tr->GetPosition();
			//	tr->SetPosition(pos.x, pos.y + 0.1f, pos.z);
			//	tr->SetPlusZvalue(0.1f);


			//	mJumpingTime += Time::DeltaTime();
			//}
			//else
			//{
			//	isJump = false;
			//	mJumpingTime = 0.0f;
			//}
		}
		else if (tr->GetZvalue() <= 0.0f)
		{
			//Vector3 pos = tr->GetPosition();
			//tr->SetPosition(pos.x, pos.y - mGravity, pos.z);
			//tr->SetPlusZvalue(-mGravity);
			GetOwner()->GetComponent<Rigidbody>()->SetGround(true);
			GetOwner()->GetComponent<Rigidbody>()->SetVelocity(Vector3::Zero);

			tr->SetPlusZvalue(-tr->GetZvalue());
		}
	}
	void PlayerScript::makeShadow()
	{
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		////Shadow = object::Instantiate<Effect>(eLayerType::SkillEffect,
		////	Vector3(tr->GetPosition().x, tr->GetPosition().y - (tr->GetScale().y / 2.0f), tr->GetPosition().z));
		//Shadow = object::Instantiate<Effect>(eLayerType::SkillEffect,
		//	Vector3(0.0f, 0.0f, 0.0f));
		//Transform* sdtr = Shadow->GetComponent<Transform>();
		//sdtr->SetScale((tr->GetScale()) * 0.5f);
		//SpriteRenderer* sdsr = Shadow->AddComponent<SpriteRenderer>();
		//sdsr->SetSprite(Resources::Find<graphics::Texture>(L"Shadow"));
		////Shadow->AddComponent<BoxCollider2D>();
		////BoxCollider2D* mShadowBoxCollidder = Shadow->GetComponent<BoxCollider2D>();
		////mShadowBoxCollidder->GetBoxCollider2D().Extents = XMFLOAT3(0.75f, 1.1f, 0.0f);
	}
}
