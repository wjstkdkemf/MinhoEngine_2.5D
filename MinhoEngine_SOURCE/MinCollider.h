#pragma once
#include "MinComponent.h"
#include "commoninclude.h"

namespace min 
{
	class Collider : public Component
	{
	public:
		Collider(eColliderType type);
		~Collider();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		virtual bool Intersects(Collider* other) = 0;
		eColliderType GetColType() const { return mType; }


		Vector2 GetOffset() const { return mOffset; }
		void SetOffset(Vector2 offset) { mOffset = offset; }
		UINT32 GetID() const { return mID; }
		Vector2 GetSize() const { return mSize; }
		void SetSize(Vector2 Size) { mSize = Size; }
		


	private:
		static UINT32 mCollisionID;
		UINT32 mID;
		Vector2 mOffset;
		Vector2 mSize;

		eColliderType mType;
	};
}
