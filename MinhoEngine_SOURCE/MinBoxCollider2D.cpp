#include "MinBoxCollider2D.h"
#include "MinTransform.h"
#include "minGameObject.h"
#include "MinRenderer.h"
#include "MinCamera.h"

namespace min
{
	BoxCollider2D::BoxCollider2D()
		:Collider(eColliderType::Rect2D)
	{
	}
	BoxCollider2D::~BoxCollider2D()
	{
	}
	void BoxCollider2D::Initialize()
	{
	}
	void BoxCollider2D::Update()
	{
	}
	void BoxCollider2D::LateUpdate()
	{
	}
	void BoxCollider2D::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
	}
}