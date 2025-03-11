#include "MinSpriteRenderer.h"
#include "MinGameObject.h"
#include "MinTransform.h"
#include "MinMath.h"
#include "MinSceneManager.h"
#include "MinTexture.h"
#include "MinRenderer.h"
#include "MinResources.h"
#include "MinTransform.h"

namespace min {
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::SpriteRenderer)
		, mSprite(nullptr)
		, mMaterial(nullptr)
		, mMesh(nullptr)
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
		GetOwner()->GetName();

		mMesh = Resources::Find<Mesh>(L"RectMesh");
		//mMesh = Resources::Find<Mesh>(L"TriangleMesh");

		mMaterial = Resources::Find<Material>(L"SpriteDefaultMaterial");
		//mMaterial = Resources::Find<Material>(L"TriangleMaterial");
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::LateUpdate()
	{
	}
	void SpriteRenderer::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

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
	}

}
