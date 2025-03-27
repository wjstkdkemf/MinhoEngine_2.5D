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
		, mFriction(1.0f)
		, mForce(Vector3::Zero)
		, mAccelation(Vector3::Zero)
		, mVelocity(Vector3::Zero)
		, mLimitmVelocity(Vector3(20.0f , 100.0f, 0.0f))
		, mGravity(Vector3(0.0f, -15.0f , 0.0f))
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
		if(GetOwner()->GetComponent<Transform>()->GetZvalue() <= 0.0f)
		{
			//최대 속도 제한
			Vector3 gravity = mGravity;
			gravity.Normalize();
			//float dot = Vector2::Dot(mVelocity, gravity);
			Vector3 gravityVel = gravity * mVelocity.Dot(gravity);//float dot = mVelocity.Dot(gravity);
			//if (mbGround && gravityVel.y < 0.0f)
			//	gravityVel = Vector3::Zero;

			if (mLimitmVelocity.x < mVelocity.Length())
			{
				mVelocity.Normalize();
				mVelocity *= mLimitmVelocity.x;
			}
		}
		else
		{
			if (mbGround)
			{
				Vector3 gravityDir = mGravity;
				gravityDir.Normalize();
				float dot = mVelocity.Dot(gravityDir);
				if (dot < 0)
					mVelocity -= gravityDir * dot;
			}
			else
			{
				mVelocity += mGravity * Time::DeltaTime();
			}

			//최대 속도 제한
			Vector3 gravity = mGravity;
			gravity.Normalize();
			//float dot = Vector2::Dot(mVelocity, gravity);
			Vector3 gravityVel = gravity * mVelocity.Dot(gravity);//float dot = mVelocity.Dot(gravity);
			//if (mbGround && gravityVel.y < 0.0f)
			//	gravityVel = Vector3::Zero;

			Vector3 sideVelocity = mVelocity - gravityVel;
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

			mVelocity = gravityVel + sideVelocity;

			if (mbGround && mVelocity.Length() > 0.0f)
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

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();

		if (!mbGround)
		{
			tr->SetPosition(pos);
			tr->SetPlusZvalue(pos.y);
		}
		else 
		{
			tr->SetPosition(pos);
		}
	}
	void Rigidbody::LateUpdate()
	{
	}
	void Rigidbody::Render()
	{
	}
}
