#include "MinSpriteRenderer.h"
#include "MinGameObject.h"
#include "MinTransform.h"
#include "MinMath.h"
#include "MinSceneManager.h"


namespace min {
	SpriteRenderer::SpriteRenderer()
		:mImage(nullptr)
		,mWidth(0)
		,mHeight(0)
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
		//HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));// 파랑배경 브러쉬 생성
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush); // 파랑 브러쉬 DC에 선택 후 기존 흰색 브러쉬 반환

		///*HPEN redpen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		//HPEN oldpen = (HPEN)SelectObject(mHdc, redpen);

		//SelectObject(mHdc, oldpen);*/

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Gdiplus::Graphics graphcis(hdc);
		graphcis.DrawImage(mImage, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));

		//std::wstring SceneName = SceneManager::GetSceneName();
		//wchar_t str[50] = L"";
		//swprintf_s(str, 50, L"Scene Name : %s", SceneName.c_str());//swprintf_s(str,50,L"Time : %f", time)
		//int len = wcsnlen_s(str, 50);

		//TextOut(hdc, 0, 0, str, len);

		//Rectangle(hdc, 100 + tr->GetX(), 100 + tr->GetY(), 200 + tr->GetX(), 200 + tr->GetY());

		//SelectObject(hdc, oldBrush);
		//DeleteObject(brush);
		////for (size_t i = 0; i < Bullet.size(); i++) {
		////	Bullet[i]->ShotRander(mHdc);
		////}
	}
	void SpriteRenderer::ImageLoad(const std::wstring& path)
	{
		mImage = Gdiplus::Image::FromFile(path.c_str());
		mWidth = mImage->GetWidth();
		mHeight = mImage->GetHeight();
	}
}
