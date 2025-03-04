#include "MinCircleCollider2D.h"
#include "MinTransform.h"
#include "minGameObject.h"
#include "MinRenderer.h"
#include "MinCamera.h"

namespace min
{
	CircleCollider2D::CircleCollider2D()
		:Collider(eColliderType::Circle2D)
		, mRadian(0.0f)
	{
	}
	CircleCollider2D::~CircleCollider2D()
	{
	}
	void CircleCollider2D::Initialize()
	{
	}
	void CircleCollider2D::Update()
	{
	}
	void CircleCollider2D::LateUpdate()
	{
	}
	void CircleCollider2D::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
	}
}