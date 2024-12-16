#include "MinCatScript.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"
#include "minGameObject.h"
#include "MinAnimator.h"


namespace min
{
	CatScript::CatScript()
		:mState(CatScript::eState::SitDown)
		, mAnimator(nullptr)
		, mTime(0.0f)
		, mDirection(CatScript::eDirection::Down)
	{
	}
	CatScript::~CatScript()
	{
	}
	void CatScript::Initialize()
	{

	}
	void CatScript::Update()
	{
		if (mAnimator == nullptr)
			mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mState)
		{
		case min::CatScript::eState::SitDown:
			sitDown();
			break;
		case min::CatScript::eState::Walk:
			move();
			break;
		case min::CatScript::eState::Sleep:
			break;
		case min::CatScript::eState::LayDown:
			break;
		case min::CatScript::eState::Attack:
			break;
		case min::CatScript::eState::Max:
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
	void CatScript::LateUpdate()
	{
	}
	void CatScript::Rander(HDC hdc)
	{
	}
	void CatScript::sitDown()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f)
		{
			mState = CatScript::eState::Walk;
			int direction = rand() % 4;
			mDirection = (eDirection)direction;
			playWalkAnimationByDirection(mDirection);
			mTime = 0.0f;
			
		}
	}
	void CatScript::move()
	{
		mTime += Time::DeltaTime();
		if (mTime > 2.0f)
		{
			int isLayDown = rand() % 2;
			if (isLayDown)
			{
				mState = CatScript::eState::LayDown;
				mAnimator->PlayAnimation(L"CatLayDown", false);
			}
			else
			{
				mState = CatScript::eState::SitDown;
				mAnimator->PlayAnimation(L"CatSitDown", false);
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		trnaslate(tr);
	}
	void CatScript::layDown()
	{
	}
	void CatScript::playWalkAnimationByDirection(eDirection dir)
	{
		switch (dir)
		{
		case min::CatScript::eDirection::Left:
			mAnimator->PlayAnimation(L"CatLeftWalk", true);
			break;
		case min::CatScript::eDirection::Right:
			mAnimator->PlayAnimation(L"CatRightWalk", true);
			break;
		case min::CatScript::eDirection::Up:
			mAnimator->PlayAnimation(L"CatUpWalk", true);
			break;
		case min::CatScript::eDirection::Down:
			mAnimator->PlayAnimation(L"CatDownWalk", true);
			break;
		case min::CatScript::eDirection::End:
			break;
		default:
			assert(false);
			break;
		}
	}
	void CatScript::trnaslate(Transform* tr)
	{
		Vector2 pos = tr->GetPosition();

		switch (mDirection)
		{
		case min::CatScript::eDirection::Left:
			pos.x -= 100.0f * Time::DeltaTime();
			break;
		case min::CatScript::eDirection::Right:
			pos.x += 100.0f * Time::DeltaTime();
			break;
		case min::CatScript::eDirection::Up:
			pos.y -= 100.0f * Time::DeltaTime();
			break;
		case min::CatScript::eDirection::Down:
			pos.y += 100.0f * Time::DeltaTime();
			break;
		case min::CatScript::eDirection::End:
			break;
		default:
			break;
		}
		tr->SetPosition(pos);
	}
}
