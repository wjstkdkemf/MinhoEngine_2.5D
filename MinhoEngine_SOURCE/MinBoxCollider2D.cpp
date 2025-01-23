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
	void BoxCollider2D::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (renderer::mainCamera)
			pos = renderer::mainCamera->CalculatePosition(pos);

		Vector2 offset = GetOffset();

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc,transparentBrush);

		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

		Rectangle(hdc
			, pos.x + offset.x
			, pos.y + offset.y
			, pos.x + offset.x + 100 * GetSize().x
			, pos.y + offset.y + 100 * GetSize().y);

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		//DeleteObject(transparentBrush); -> stockobject 이기때문에 삭제하지 않아도 된다.
		DeleteObject(greenPen);
	}
}