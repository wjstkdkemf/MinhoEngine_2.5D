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

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		bool Intersects(Collider* other) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;
		
		BoundingBox& GetBoxCollider2D() { return mBoxCollider2D; }
		void DrawAabb(BoundingBox box, FXMVECTOR color);
		void DrawCube(CXMMATRIX mWorld, FXMVECTOR color);

	private:
		BoundingBox mBoxCollider2D;
		graphics::InputLayout mInputLayout;
	};
}
