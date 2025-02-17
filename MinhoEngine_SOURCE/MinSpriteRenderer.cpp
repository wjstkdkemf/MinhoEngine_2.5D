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
	void SpriteRenderer::Render()
	{
		if (mTexture == nullptr)
			assert(false);

		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRoation();
		Vector2 scale = tr->GetScale();*/

		//	pos = renderer::mainCamera->CalculatePosition(pos);

		//	if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
		//	{
		//		if (mTexture->IsAlpha())
		//		{
		//			BLENDFUNCTION func = {};
		//			func.BlendOp = AC_SRC_OVER;
		//			func.BlendFlags = 0;
		//			func.AlphaFormat = AC_SRC_ALPHA;
		//			func.SourceConstantAlpha = 255;//0(완전투명) ~ 255(불투명)

		//			AlphaBlend(hdc
		//				, pos.x
		//				, pos.y
		//				, mTexture->GetWidth() * mSize.x * scale.x
		//				, mTexture->GetHeight() * mSize.y * scale.y
		//				, mTexture->GetHdc()
		//				, 0, 0
		//				, mTexture->GetWidth()
		//				, mTexture->GetHeight()
		//				, func);
		//		}
		//		else
		//		{
		//			TransparentBlt(hdc, pos.x, pos.y
		//				, mTexture->GetWidth() * mSize.x * scale.x, mTexture->GetHeight() * mSize.y * scale.y
		//				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight()
		//				, RGB(255, 0, 255));
		//		}
		//	}
		//	else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png)
		//	{
		//		Gdiplus::ImageAttributes imgAtt = {};

		//		imgAtt.SetColorKey(Gdiplus::Color(100, 100, 100), Gdiplus::Color(255, 255, 255));//투명화 시킬 픽셀의 색 범위


		//		Gdiplus::Graphics graphcis(hdc);

		//		graphcis.TranslateTransform(pos.x, pos.y);
		//		graphcis.RotateTransform(rot);
		//		graphcis.TranslateTransform(-pos.x, -pos.y);

		//		graphcis.DrawImage(mTexture->GetImage()
		//			, Gdiplus::Rect
		//			(
		//				pos.x, pos.y
		//				, mTexture->GetWidth() * mSize.x * scale.x, mTexture->GetHeight() * mSize.y * scale.y
		//			)
		//			, 0, 0
		//			, mTexture->GetWidth(), mTexture->GetHeight()
		//			, Gdiplus::UnitPixel
		//			, nullptr//&imgAtt
		//		);
		//	}
		//
	}

}
