#include "MinSpriteRenderer.h"
#include "MinGameObject.h"
#include "MinTransform.h"
#include "MinMath.h"
#include "MinSceneManager.h"
#include "MinTexture.h"
#include "MinRenderer.h"

namespace min {
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::SpriteRenderer)
		, mTexture(nullptr)
		, mSize(Vector2::One)
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
		if (mTexture ==nullptr)
			assert(false);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos = renderer::mainCamera->CalculatePosition(pos);

		if (mTexture->GetTextureType() == graphcis::Texture::eTextureType::Bmp)
		{
			TransparentBlt(hdc, pos.x, pos.y
				, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y
				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight()
				, RGB(255, 0, 255));
		}
		else if (mTexture->GetTextureType() == graphcis::Texture::eTextureType::Png)
		{
			Gdiplus::Graphics graphcis(hdc);
			graphcis.DrawImage(mTexture->GetImage()
				, Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y));
		}
		//HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));// 파랑배경 브러쉬 생성
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush); // 파랑 브러쉬 DC에 선택 후 기존 흰색 브러쉬 반환

		///*HPEN redpen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		//HPEN oldpen = (HPEN)SelectObject(mHdc, redpen);

		//SelectObject(mHdc, oldpen);*/

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

		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Gdiplus::Graphics graphcis(hdc);
		graphcis.DrawImage(mImage, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));*/
	}

}
