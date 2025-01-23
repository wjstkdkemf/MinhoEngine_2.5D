#include "MinCollider.h"
#include "MinScript.h"
#include "minGameObject.h"

namespace min
{
	UINT32 Collider::mCollisionID = 1;
	Collider::Collider(eColliderType type)
		: Component(enums::eComponentType::Collider)
		, mType(type)
		, mID(mCollisionID)
		, mSize(Vector2::One)
	{

	}
	Collider::~Collider()
	{
	}
	void Collider::Initialize()
	{
	}
	void Collider::Update()
	{
	}
	void Collider::LateUpdate()
	{
	}
	void Collider::Render(HDC hdc)
	{
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionExit(other);
	}
}
