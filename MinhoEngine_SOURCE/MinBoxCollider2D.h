#pragma once
#include "MinCollider.h"
#include "MinInputLayout.h"

namespace min
{
	class BoxCollider2D : public Collider
	{
	public:
		BoxCollider2D();
		~BoxCollider2D();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual bool Intersects(Collider* other) override;
		BoundingBox& GetBoxCollider2D() { return mBoxCollider2D; }
		void DrawCube(CXMMATRIX mWorld, FXMVECTOR color);
		void DrawAabb(BoundingBox box, FXMVECTOR color);

	private:
		BoundingBox mBoxCollider2D;
		graphics::InputLayout mInputLayout;
	};
}
