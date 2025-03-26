#include "MinShadow.h"
#include "MinTransform.h"
#include "MinObject.h"
#include "MinSpriteRenderer.h"
#include "MinResources.h"
#include "..\\MinhoEngine_Window\MinPlayerScript.h"
#include "..\\MinhoEngine_Window\\MinEffect.h"

namespace min
{
	Shadow::Shadow()
		: Component(eComponentType::Shadow)
		, mShadow(nullptr)
	{
	}
	Shadow::~Shadow()
	{
	}
	void Shadow::Initialize()
	{
		mShadow = object::Instantiate<Effect>(eLayerType::SkillEffect
			, Vector3(0.0f , 0.0f , 0.0f));

		SpriteRenderer* sdsr = mShadow->AddComponent<SpriteRenderer>();
		sdsr->SetSprite(Resources::Find<graphics::Texture>(L"Shadow"));
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		////Shadow = object::Instantiate<Effect>(eLayerType::SkillEffect,
		////	Vector3(tr->GetPosition().x, tr->GetPosition().y - (tr->GetScale().y / 2.0f), tr->GetPosition().z));
		//Shadow = object::Instantiate<Effect>(eLayerType::SkillEffect,
		//	Vector3(0.0f, 0.0f, 0.0f));
		//Transform* sdtr = Shadow->GetComponent<Transform>();
		//sdtr->SetScale((tr->GetScale()) * 0.5f);
		//SpriteRenderer* sdsr = Shadow->AddComponent<SpriteRenderer>();
		//sdsr->SetSprite(Resources::Find<graphics::Texture>(L"Shadow"));
		////Shadow->AddComponent<BoxCollider2D>();
		////BoxCollider2D* mShadowBoxCollidder = Shadow->GetComponent<BoxCollider2D>();
		////mShadowBoxCollidder->GetBoxCollider2D().Extents = XMFLOAT3(0.75f, 1.1f, 0.0f);
		int a = 0;
	}
	void Shadow::Update()
	{
		Transform* sdtr = mShadow->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		sdtr->SetScale((tr->GetScale()) * 0.5f);
		sdtr->SetPosition(Vector3(tr->GetPosition().x, tr->GetPosition().y - (tr->GetScale().y / 2.0f) - GetOwner()->GetComponent<PlayerScript>()->GetZvalue(), tr->GetPosition().z));
	}
	void Shadow::LateUpdate()
	{
	}
	void Shadow::Render()
	{
	}
}