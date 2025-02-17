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
	HRESULT Animation::Save(const std::wstring path)
	{
		return E_NOTIMPL;
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
	void Animation::Render()
	{
		if (mTexture == nullptr)
			return;
	}
	void Animation::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		SetName(name);
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
