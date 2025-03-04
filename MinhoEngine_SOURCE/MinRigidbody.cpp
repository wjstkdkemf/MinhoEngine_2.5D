#include "MinRigidbody.h"
#include "MinTime.h"
#include "MinTransform.h"
#include "minGameObject.h"

namespace min
{
	Rigidbody::Rigidbody()
		: Component(enums::eComponentType::Rigidbody)
		, mbGround(false)
		, mMass(1.0f)
		, mFriction(10.0f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, mLimitmVelocity(Vector2(200.0f , 1000.0f))
		, mGravity(Vector2(0.0f, 400.0f))
	{

	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}
	void Rigidbody::Update()
	{
		//mAccelation = mForce / mMass;
		//mVelocity += mAccelation * Time::DeltaTime();

		//if (mbGround)
		//{
		//	Vector2 gravity = mGravity;
		//	gravity.Normalize();
		//	float dot = mVelocity.Dot(gravity);
		//	// Vector2::Dot(mVelocity, gravity);
		//	mVelocity -= gravity * dot;
		//}
		//else
		//{
		//	mVelocity += mGravity * Time::DeltaTime();
		//}

		////최대 속도 제한
		//Vector2 gravity = mGravity;
		//gravity.Normalize();
		////float dot = Vector2::Dot(mVelocity, gravity);
		//float dot = mVelocity.Dot(gravity);
		//gravity = gravity * dot;

		//Vector2 sideVelocity = mVelocity - gravity;
		//if (mLimitmVelocity.y < gravity.Length())
		//{
		//	gravity.Normalize();
		//	gravity *= mLimitmVelocity.y;
		//}
		//if (mLimitmVelocity.x < sideVelocity.Length())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= mLimitmVelocity.x;
		//}

		//mVelocity = gravity + sideVelocity;

		//if (!(mVelocity == Vector2::Zero))
		//{
		//	Vector2 friction = -mVelocity; // 힘의 반대방향
		//	friction.Normalize();
		//	friction = friction * mFriction * mMass * Time::DeltaTime();

		//	if (mVelocity.Length() <= friction.Length())
		//	{
		//		mVelocity = Vector2::Zero;
		//	}
		//	else
		//	{
		//		mVelocity += friction;
		//	}
		//}

		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector2 pos = tr->GetPosition();
		//pos = pos + mVelocity * Time::DeltaTime();
		//tr->SetPosition(pos);

		//mForce = Vector2::One;
	}
	void Rigidbody::LateUpdate()
	{
	}
	void Rigidbody::Render()
	{
	}
}
