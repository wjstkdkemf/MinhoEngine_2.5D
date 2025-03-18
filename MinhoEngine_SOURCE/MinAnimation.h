#pragma once
#include "MinTexture.h"
#include "MinResource.h"
#include "MinMaterial.h"
#include "MinMesh.h"

namespace min 
{
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			//float frameWidth;      // �� �������� �ʺ�
			//float frameHeight;     // �� �������� ����
			Vector2 size;
			Vector2 offset;
			int totalFrames;       // �� ������ ����
			int currentFrame;      // ���� ������
			float animationSpeed;  // ������ ���� �ӵ� (��)
			float elapsedTime;     // ��� �ð�
			float duration;
		};

		struct AnimationBuffer
		{
			Vector2 Offset;
			Vector2 Size;
			Vector2 TextureSize;
			float useAni;
			float padding;
		};

		Animation();
		virtual ~Animation();

		virtual HRESULT Save(const std::wstring path) override;
		virtual HRESULT Load(const std::wstring path) override;

		void Update();
		void Render();

		void CreateAnimation(const std::wstring& name
			, graphics::Texture* spriteSheet//ScratchImage* spriteSheet
			, Vector2 leftTop
			, Vector2 size
			, Vector2 offset
			, UINT spriteLength
			, float duration);
		void ResetAnimationConstant();
		void Reset();

		bool IsComplete() const { return mbComplete; }
		void SetAnimator(class Animator* animator) { mAnimator = animator;}
		void SetTexture(graphics::Texture* tex) { mSprite = tex; }

	private:
		class Animator* mAnimator;
		//graphics::Texture* mTexture;
		std::vector<Sprite> mAnimationSheet;
		graphics::Texture* mSprite;
		Material* mMaterial;
		Mesh* mMesh;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}

