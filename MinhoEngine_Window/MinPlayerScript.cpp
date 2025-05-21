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
#include "MinShadow.h"

namespace min
{
	bool PlayerScript::exChangeSkill = false;

	PlayerScript::PlayerScript()
		: mState(PlayerScript::eState::idle)
		, mAnimator(nullptr)
		, mDelayTime(2.0f)
		, mGravity(0.05f)
		, isJump(false)
		, mJumpingTime(0.0f)
		, mFront(true)
		, mSpeed(15.0f)
		, mMoveLock(false)
		, mCoolTime(4, 3.0f)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		exChangeSkill = false;
		mSkillInfo.resize(4);
	}
	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if(exChangeSkill)
		{
			MakeSkill_Info();
			exChangeSkill = false;
		}

		if (mAnimator == nullptr)
			mAnimator = GetOwner()->GetComponent<Animator>();

		Jumping();
		CoolTimeCheck();
		CheakPosition();


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
		if(GetOwner()->GetState() == GameObject::eState::Active)
		{
			if (GetOwner()->GetComponent<Shadow>()->GetGroundMaterial() == L"Floor_1")//땅의 재질을 읽어들일 수 있으므로 이에 맞는 사운드 출력을 구현하면됨
				int a = 0;
		}
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
	void PlayerScript::CoolTimeCheck()
	{
		if (mCoolTime[0] < 2.0f) 
		{
			mCoolTime[0] += Time::DeltaTime();

			if (mCoolTime[0] >= 1.0f)
				mMoveLock = false;
		}

		if (mCoolTime[1] < 1.0f)
		{
			mCoolTime[1] += Time::DeltaTime();

			if (mCoolTime[1] >= 0.5f)
				mMoveLock = false;
		}
	}
	void PlayerScript::CheakPosition()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		float lx = mFieldSize.x / 2;
		float clampX = std::clamp(pos.x, -lx, lx); // 추후lx 부분을 ground의 position으로 조정해줘야함 

		float ly = mFieldSize.y / 2;

		float clampY = 0.0f;

		if(rb->GetGround())
			clampY = std::clamp(pos.y, -ly + 0.5f, 0.0f);
		else
		{
			clampY = std::clamp(pos.y, -ly + 0.5f, 999999.0f);
			Vector3 vel = rb->GetVelocity();
			rb->SetVelocity(Vector3(vel.x, 0.0f, vel.z));
		}

		tr->SetPosition(clampX, clampY, pos.z);
	}
	void PlayerScript::Idle()
	{
#pragma region 이동관련 구현(WASD)
		if(!mMoveLock)
		{
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
			if (input::GetKey(eKeyCode::R)) {
				//sm->SetSkillDamage(L"FirstSkill");
				UIManager::Push(eUIType::SkillInventory);
			}
			if (input::GetKey(eKeyCode::T)) {
				//sm->SetSkillDamage(L"FirstSkill");
				UIManager::Pop(eUIType::SkillInventory);//eUIType::SkillInventory
			}
			if (input::GetKey(eKeyCode::P))
			{
				input::GetMousePosition();
			}
			if (input::GetKey(eKeyCode::SpaceVar))
			{
				if (!isJump)
					isJump = true;
			}
		}
#pragma endregion
#pragma region Skill
		if (input::GetKey(eKeyCode::Q)) {
			mState = eState::Walk;

			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
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
			rd->AddForce(Vector3(mSpeed, 0.0f, 0.0f));
		}
		if (input::GetKey(eKeyCode::A)) {
			rd->AddForce(Vector3(-mSpeed, 0.0f, 0.0f));
			mFront = false;
		}
		if (input::GetKey(eKeyCode::W)) {
			rd->AddForce(Vector3(0.0f, mSpeed, 0.0f));
		}
		if (input::GetKey(eKeyCode::S)) {
			rd->AddForce(Vector3(0.0f, -mSpeed, 0.0f));
		}
		if (input::GetKey(eKeyCode::P))
		{
			input::GetMousePosition();
		}
#pragma endregion
#pragma region Skill
		if (input::GetKey(eKeyCode::Q)) {
			if (mCoolTime[0] >= 2.0f)
			{
				sm->UseSkill(mSkillInfo[0].SkillName, mFront);
				rd->SetVelocity(Vector3::Zero);
				mMoveLock = true;
				mCoolTime[0] = 0.0f;
			}
		}
		if (input::GetKey(eKeyCode::E)) {
			if (mCoolTime[1] >= 1.0f)
			{
				sm->UseSkill(mSkillInfo[1].SkillName, mFront);
				rd->SetVelocity(Vector3::Zero);
				mMoveLock = true;
				mCoolTime[1] = 0.0f;
			}
		}
		if (input::GetKey(eKeyCode::R)) {
			//sm->SetSkillDamage(L"FirstSkill");
			UIManager::Push(eUIType::SkillInventory);
		}
		if (input::GetKey(eKeyCode::T)) {
			//sm->SetSkillDamage(L"FirstSkill");
			UIManager::Pop(eUIType::SkillInventory);
		}
		if (input::GetKey(eKeyCode::SpaceVar))
		{
			if (!isJump)
				isJump = true;
		}
#pragma endregion
#pragma endregion

		if (input::GetKeyUp(eKeyCode::D) || input::GetKeyUp(eKeyCode::A) || input::GetKeyUp(eKeyCode::W) || input::GetKeyUp(eKeyCode::S)
			|| input::GetKeyUp(eKeyCode::Q) || input::GetKeyUp(eKeyCode::E) || input::GetKeyUp(eKeyCode::R) || input::GetKeyUp(eKeyCode::T))
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
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		if (isJump)
		{
			if(rb->GetGround())
			{
				rb->SetGround(false);
				rb->AddJumpingForce(Vector3(0.0f, 10.0f, 0.0f));
				isJump = false;
			}
			else
			{
				isJump = false;
			}
		}
	}
	void PlayerScript::MakeSkill_Info()
	{
		SkillInventory* skillinven = (SkillInventory*)UIManager::UIGet(eUIType::SkillInventory);
		std::vector<SkillInventory::InventoryInfo> skillinfo = skillinven->GetSkillInfo();

		for (int i = 0; i < 4; i++)
		{
			mSkillInfo[i] = skillinfo[i];
		}
	}
}
