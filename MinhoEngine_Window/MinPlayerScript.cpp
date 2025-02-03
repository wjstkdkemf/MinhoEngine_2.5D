#include "MinPlayerScript.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"
#include "minGameObject.h"
#include "MinAnimator.h"
#include "MinCat.h"
#include "MinCatScript.h"
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
		if (mAnimator == nullptr)
			mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mState)
		{
		case min::PlayerScript::eState::idle:
			Idle();
			break;
		case min::PlayerScript::eState::Walk:
			move();
			break;
		case min::PlayerScript::eState::Sleep:
			break;
		case min::PlayerScript::eState::GiveWater:
			giveWater();
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
	void PlayerScript::Render(HDC hdc)
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
		Cat* cat = object::Instantiate<Cat>
			(enums::eLayerType::Animal);
		CatScript* catSrc = cat->AddComponent<CatScript>();

		catSrc->setPlayer(GetOwner());

		graphics::Texture* CatTex = Resources::Find<graphics::Texture>(L"Cat");
		Animator* catAnimator = cat->AddComponent<Animator>();
		catAnimator->CreateAnimation(L"CatDownWalk", CatTex
			, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"CatRightWalk", CatTex
			, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"CatUpWalk", CatTex
			, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"CatLeftWalk", CatTex
			, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"CatSitDown", CatTex
			, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"CatGrooming", CatTex
			, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"CatLayDown", CatTex
			, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

		Transform* tr = GetOwner()->GetComponent<Transform>();

		BoxCollider2D* catCollider = cat->AddComponent<BoxCollider2D>();
		catCollider->SetOffset(Vector2(-50.0f, -50.0f));

		catAnimator->PlayAnimation(L"CatSitDown", false);


		cat->GetComponent<Transform>()->SetPosition(tr->GetPosition());
		cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

		Vector2 mousePos = input::GetMousePosition();
		catSrc->mDest = mousePos;

	}
	void PlayerScript::Idle()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		if (input::GetKey(eKeyCode::Right)) {
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"PlayerRightWalk", true);
		}
		if (input::GetKey(eKeyCode::Left)) {
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"PlayerLeftWalk", true);
		}
		if (input::GetKey(eKeyCode::Up)) {
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"PlayerUpWalk", true);
		}
		if (input::GetKey(eKeyCode::Down)) {
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"PlayerDownWalk", true);
		}
		if (input::GetKey(eKeyCode::Lbutton)) {
			mState = PlayerScript::eState::GiveWater;
			mAnimator->PlayAnimation(L"PlayerFronttGiveWater", false);

			Vector2 mousePos = input::GetMousePosition();
		}
		if (input::GetKey(eKeyCode::Space)) {
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			//pos.y += 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::I)) {
			UIManager::Push(eUIType::HPBAR);
		}
		if (input::GetKey(eKeyCode::O)) {
			UIManager::Pop(eUIType::HPBAR);
		}
	}
	void PlayerScript::move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		if (input::GetKey(eKeyCode::Right)) {
			//pos.x += 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(200.0f, 0.0f));
		}
		if (input::GetKey(eKeyCode::Left)) {
			rb->AddForce(Vector2(-200.0f, 0.0f));
			//pos.x -= 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Up)) {
			rb->AddForce(Vector2(0.0f, -200.0f));
			//pos.y -= 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Down)) {
			rb->AddForce(Vector2(0.0f, 200.0f));
			//pos.y += 100.0f * Time::DeltaTime();
		}
		

		tr->SetPosition(pos);

		if (input::GetKeyUp(eKeyCode::Right) 
			|| input::GetKeyUp(eKeyCode::Left)
			|| input::GetKeyUp(eKeyCode::Up)
			|| input::GetKeyUp(eKeyCode::Down)) {
			mState = PlayerScript::eState::idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}
	}
	void PlayerScript::giveWater()
	{
		if (mAnimator->IsCompleteAnimation()) 
		{
			mState = PlayerScript::eState::idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}
	}
}
