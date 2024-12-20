#include "MinAnimation.h"
#include "MinTime.h"
#include "MinTransform.h"
#include "minGameObject.h"
#include "MinAnimator.h"
#include "MinRenderer.h"

namespace min
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, mAnimator(nullptr)
		, mTexture(nullptr)
		, mAnimationSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}
	Animation::~Animation()
	{
		/*mAnimationSheet.clear();
		std::vector<Sprite>().swap(mAnimationSheet);*/
	}
	HRESULT Animation::Load(const std::wstring path)
	{
		return E_NOTIMPL;
	}
	void Animation::Update()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		if (mAnimationSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;
			if (mIndex < mAnimationSheet.size() - 1)
				mIndex++;
			else
				mbComplete = true;
		}
	}
	void Animation::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			return;

		GameObject* gameobj = mAnimator->GetOwner();
		Transform* tr = gameobj->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRoation();
		Vector2 scale = tr->GetScale();

		if (renderer::mainCamera)
			pos = renderer::mainCamera->CalculatePosition(pos);

		Sprite sprite = mAnimationSheet[mIndex];
		graphcis::Texture::eTextureType type = mTexture->GetTextureType();

		if (type == graphcis::Texture::eTextureType::Bmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;//0(완전투명) ~ 255(불투명)

			
			HDC imgHdc = mTexture->GetHdc();

			AlphaBlend(hdc
				, pos.x - (sprite.size.x / 2.0f), pos.y - (sprite.size.y / 2.0f)
				, sprite.size.x * scale.x, sprite.size.y * scale.y
				, imgHdc
				, sprite.leftTop.x, sprite.leftTop.y
				, sprite.size.x, sprite.size.y
				, func);
		}
		else if (type == graphcis::Texture::eTextureType::Png)
		{
			Gdiplus::ImageAttributes imgAtt = {};

			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));//투명화 시킬 픽셀의 색 범위
			Gdiplus::Graphics graphcis(hdc);

			graphcis.TranslateTransform(pos.x, pos.y);
			graphcis.RotateTransform(rot);
			graphcis.TranslateTransform(-pos.x, -pos.y);

			graphcis.DrawImage(mTexture->GetImage()
				,Gdiplus::Rect
				(
						pos.x - (sprite.size.x / 2.0f), pos.y - (sprite.size.y / 2.0f)
					,	sprite.size.x * scale.x, sprite.size.y * scale.y
				)
				, sprite.leftTop.x,	 sprite.leftTop.y
				, sprite.size.x,	 sprite.size.y
				, Gdiplus::UnitPixel
				, &imgAtt
			);
		}
		//AlphaBlend() 사용조건 : 해당이미지의 알파채널이 존재해야한다.
	}
	void Animation::CreateAnimation(const std::wstring& name, graphcis::Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		mTexture = spriteSheet;
		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			sprite.offset = offset;
			sprite.duration = duration;
			sprite.size = size;

			mAnimationSheet.push_back(sprite);
		}
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}
