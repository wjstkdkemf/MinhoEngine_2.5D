#include "MinRigidbody.h"
#include "MinTime.h"
#include "MinTransform.h"
#include "minGameObject.h"

namespace min
{
	Rigidbody::Rigidbody()
		: Component(enums::eComponentType::Rigidbody)
		, mbGround(true)
		, mMass(1.0f)
		, mFriction(5.0f)
		, mForce(Vector3::Zero)
		, mJumpingForce(Vector3::Zero)
		, mAccelation(Vector3::Zero)
		, mVelocity(Vector3::Zero)
		, mJumpVelocity(Vector3::Zero)
		, mLimitmVelocity(Vector3(10.0f , 100.0f, 0.0f))
		, mGravity(Vector3(0.0f, -25.0f , 0.0f))
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
		mAccelation = mForce / mMass;
		mVelocity += mAccelation * Time::DeltaTime();
		mForce = Vector3::Zero;

		if(mbGround)//땅에서 돌아다닐때 속도.
		{
			NormalVelocityCalculate(eRigidBody::Ground);
		}
		else// 점프를 했을 때 속도
		{
			JumpVelocityCalculate();
			NormalVelocityCalculate(eRigidBody::Jump);
		}
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();


		pos = pos + mVelocity * Time::DeltaTime();

		tr->SetPosition(pos + mJumpVelocity * Time::DeltaTime());
		tr->SetPlusZvalue(mJumpVelocity.y * Time::DeltaTime());

		if (tr->GetZvalue() <= 0.0f)
		{
			float mZval = tr->GetZvalue();

			tr->SetPlusZvalue(-mZval);
			tr->SetPosition(pos.x ,pos.y - tr->GetZvalue() , pos.z);

			mJumpVelocity = Vector3::Zero;
			mbGround = true;
		}
	}
	void Rigidbody::LateUpdate()
	{
	}
	void Rigidbody::Render()
	{
	}
	void Rigidbody::JumpVelocityCalculate()
	{
		if (mJumpingForce != Vector3::Zero)
		{
			mJumpVelocity += mJumpingForce / mMass;
			mJumpingForce = Vector3::Zero;
		}

		mJumpVelocity += mGravity * Time::DeltaTime();

		//최대 속도 제한
		Vector3 gravity = mGravity;
		gravity.Normalize();
		Vector3 gravityVel = gravity * mJumpVelocity.Dot(gravity);

		Vector3 sideVelocity = mJumpVelocity - gravityVel;
		if (mLimitmVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitmVelocity.y;
		}
		if (mLimitmVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitmVelocity.x;
		}

		mJumpVelocity = gravityVel + sideVelocity;
	}

	void Rigidbody::NormalVelocityCalculate(eRigidBody Version)
	{
		if (mLimitmVelocity.x < mVelocity.Length())
		{
  			mVelocity.Normalize();
			mVelocity *= mLimitmVelocity.x;
		}

		if (mVelocity.Length() > 0.0f)
		{
			Vector3 friction = -mVelocity; // 힘의 반대방향
			friction.Normalize();
			friction = friction * mFriction * mMass * Time::DeltaTime();

			if (mVelocity.Length() <= friction.Length())
			{
				mVelocity = Vector3::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}
	}
}
