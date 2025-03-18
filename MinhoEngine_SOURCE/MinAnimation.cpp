#include "MinAnimation.h"
#include "MinTime.h"
#include "MinTransform.h"
#include "minGameObject.h"
#include "MinAnimator.h"
#include "MinRenderer.h"
#include "MinSpriteRenderer.h"
#include "MinComponent.h"
#include "MinResources.h"


namespace min
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, mAnimator(nullptr)
		, mAnimationSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
		, mSprite(nullptr)
		, mMaterial(nullptr)
		, mMesh(nullptr)
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
		mAnimationSheet[mIndex].elapsedTime = mTime;
		if (mAnimationSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;
			if (mIndex < mAnimationSheet[mIndex].totalFrames - 1)
				mIndex++;
			else 
			{
				mbComplete = true;
				ResetAnimationConstant();
			}
		}
	}
	void Animation::Render()
	{
		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		graphics::AnimationCB cbData = {};
		cbData.offsetX = mAnimationSheet[mIndex].offset.x;
		cbData.offsetY = mAnimationSheet[mIndex].offset.y;
		cbData.sizeX = mAnimationSheet[mIndex].size.x;
		cbData.sizeY = mAnimationSheet[mIndex].size.y;
		cbData.textureSizeX = mSprite->GetSizeX();
		cbData.textureSizeY = mSprite->GetSizeY();
		cbData.useAni = 1.0f;
		graphics::ConstantBuffer* cb = renderer::constantBuffers[CBSLOT_ANIMATION];

		cb->SetData(&cbData);
		cb->Bind(eShaderStage::All);

		if (tr)
			tr->Bind();

		if (mMesh)
			mMesh->Bind();

		if (mMaterial)
			mMaterial->BindShader();

		if (mSprite)
			mSprite->Bind(eShaderStage::PS, (UINT)eTextureType::Sprite);

		if (mMesh)
			graphics::GetDevice()->DrawIndexed(mMesh->GetIndexCount(), 0, 0);

		ResetAnimationConstant();
	}
	void Animation::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		SetName(name);
		//mScratchImage.InitializeFromImage(*spriteSheet);
		//mAnimationSprite.frameWidth = leftTop.x;      // 한 프레임의 너비
		//.frameHeight = leftTop.y;     // 한 프레임의 높이
		//mAnimationSprite.totalFrames = spriteLength;       // 총 프레임 개수
		//mAnimationSprite.currentFrame = ;      // 현재 프레임
		//mAnimationSprite.animationSpeed = 1;  // 프레임 변경 속도 (초)
		//mAnimationSprite.elapsedTime = ;     // 경과 시간
		//mAnimationSprite.duration = duration;
		mSprite = spriteSheet;
		mMesh = Resources::Find<Mesh>(L"PlayerMesh"); //추후 수정 예정 -> 몬스터 , 플레이어 와 같은 구분을 위해
		mMaterial = Resources::Find<Material>(L"AnimationMaterial");
		//mMaterial = Resources::Find<Material>(L"SpriteDefaultMaterial");
		
		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};
			sprite.size = size;
			sprite.offset.x = offset.x + size.x * i;
			sprite.offset.y = offset.y;
			sprite.duration = duration;
			sprite.totalFrames = spriteLength;
		//	sprite.mScratch.InitializeFromImage(*spriteSheet);
			mAnimationSheet.push_back(sprite);
		}
		int a = 0;
	}
	void Animation::ResetAnimationConstant()
	{
		graphics::AnimationCB cbData = {};
		cbData.offsetX = 0.0f;
		cbData.offsetY = 0.0f;
		cbData.sizeX = 0.0f;
		cbData.sizeY = 0.0f;
		cbData.textureSizeX = 0.0f;
		cbData.textureSizeY = 0.0f;
		cbData.useAni = 0.0f;
		graphics::ConstantBuffer* cb = renderer::constantBuffers[CBSLOT_ANIMATION];

		cb->SetData(&cbData);
		cb->Bind(eShaderStage::All);
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}
