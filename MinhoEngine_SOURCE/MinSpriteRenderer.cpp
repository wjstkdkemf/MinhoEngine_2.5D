#include "MinSpriteRenderer.h"
#include "MinGameObject.h"
#include "MinTransform.h"


namespace min {
	SpriteRenderer::SpriteRenderer()
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::LateUpdate()
	{
	}
	void SpriteRenderer::Rander(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));// 파랑배경 브러쉬 생성
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush); // 파랑 브러쉬 DC에 선택 후 기존 흰색 브러쉬 반환

		/*HPEN redpen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldpen = (HPEN)SelectObject(mHdc, redpen);

		SelectObject(mHdc, oldpen);*/

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Rectangle(hdc, 100 + tr->GetX(), 100 + tr->GetY(), 200 + tr->GetX(), 200 + tr->GetY());

		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
		//for (size_t i = 0; i < Bullet.size(); i++) {
		//	Bullet[i]->ShotRander(mHdc);
		//}
	}
}
