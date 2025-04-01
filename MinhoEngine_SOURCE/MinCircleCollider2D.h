#pragma once
#include "MinCollider.h"

namespace min
{
	class CircleCollider2D : public Collider
	{
	public:
		CircleCollider2D();
		~CircleCollider2D();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual bool Intersects(Collider* other) override;
		virtual ContainmentType Contain(Collider* other) override;
		BoundingSphere& GetCircleCollider2D() { return mCircleCollider2D; }

	private:
		float mRadian;
		BoundingSphere mCircleCollider2D;
	};
}

