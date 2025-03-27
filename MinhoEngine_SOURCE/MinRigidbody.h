#pragma once
#include "MinComponent.h"

namespace min
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();
	
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector3 force) { mForce += force; }
		void ResetForce() { mForce = Vector3::Zero; }
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }

		Vector3 GetVelocity() const {return mVelocity; }
		bool GetGround() { return mbGround; }

	private:
		bool mbGround;
		float mMass;
		float mFriction;
		
		Vector3 mForce;
		Vector3 mAccelation;
		Vector3 mVelocity;
		Vector3 mLimitmVelocity;
		Vector3 mGravity;
	};
}

