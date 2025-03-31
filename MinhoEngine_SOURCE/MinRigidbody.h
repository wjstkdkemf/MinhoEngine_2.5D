#pragma once
#include "MinComponent.h"

namespace min
{
	class Rigidbody : public Component
	{
	public:
		enum class eRigidBody
		{
			None,
			Ground,
			Jump,
			End,
		};

		Rigidbody();
		~Rigidbody();
	
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector3 force) { mForce += force; }
		void AddJumpingForce(Vector3 force) { mJumpingForce += force; }
		void ResetForce() { mForce = Vector3::Zero; }
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }

		void JumpVelocityCalculate();
		void NormalVelocityCalculate(eRigidBody Version);

		Vector3 GetVelocity() const {return mVelocity; }
		bool GetGround() { return mbGround; }

	private:
		bool mbGround;
		float mMass;
		float mFriction;
		
		Vector3 mJumpingForce;
		Vector3 mForce;
		Vector3 mAccelation;
		Vector3 mVelocity;
		Vector3 mJumpVelocity;
		Vector3 mLimitmVelocity;
		Vector3 mGravity;
	};
}

