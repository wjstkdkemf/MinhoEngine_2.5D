#pragma once
#include "MinCollider.h"
#include "MinInputLayout.h"

namespace min
{
	class BoxCollider2DOBB : public Collider
	{
	public:
		BoxCollider2DOBB();
		~BoxCollider2DOBB();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual bool Intersects(Collider* other) override;
		virtual ContainmentType Contain(Collider* other) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		BoundingOrientedBox& GetBoxCollider2D() { return mBoxCollider2D; }
		void DrawObb(BoundingOrientedBox box, FXMVECTOR color);
		void DrawCube(CXMMATRIX mWorld, FXMVECTOR color);

	private:
		BoundingOrientedBox mBoxCollider2D;//BoundingBox
		graphics::InputLayout mInputLayout;
	};
}