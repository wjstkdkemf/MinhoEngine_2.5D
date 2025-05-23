#include "MinShadow.h"
#include "MinTransform.h"
#include "MinObject.h"
#include "MinSpriteRenderer.h"
#include "MinResources.h"
#include "MinRigidbody.h"
#include "MinBoxCollider2D.h"
#include "minGameObject.h"
#include "..\\MinhoEngine_Window\MinPlayerScript.h"
#include "..\\MinhoEngine_Window\\MinEffect.h"

namespace min
{
	Shadow::Shadow()
		: Component(eComponentType::Shadow)
		, mShadow(nullptr)
		, mGroundMaterial(L"")
	{
	}
	Shadow::~Shadow()
	{
	}
	void Shadow::Initialize()
	{
		mShadow = object::Instantiate<Effect>(eLayerType::Shadow
			, Vector3(0.0f , 0.0f , 0.0f));

		SpriteRenderer* sdsr = mShadow->AddComponent<SpriteRenderer>();
		sdsr->SetSprite(Resources::Find<graphics::Texture>(L"Shadow"));
		BoxCollider2D* shbc = mShadow->AddComponent<BoxCollider2D>();
		shbc->SetName(L"Shadow");
	}
	void Shadow::Update()
	{
		Transform* sdtr = mShadow->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		
		sdtr->SetScale((tr->GetScale().x) / 6.0f, (tr->GetScale().y) / 8.0f, (tr->GetScale().z) / 2.0f);
		sdtr->SetPosition(Vector3(tr->GetPosition().x, tr->GetPosition().y - tr->GetZvalue() - (tr->GetScale().y / 4.0f), tr->GetPosition().z));

		if (GetOwner()->GetState() == GameObject::eState::Paused)
		{
			mShadow->SetActive(false);
		}
		else if (GetOwner()->GetState() == GameObject::eState::Active)
		{
			mShadow->SetActive(true);
		}

		//if (!(GetOwner()->GetComponent<Rigidbody>()->GetGround()))
	}
	void Shadow::LateUpdate()
	{
		SetGroundMaterial();
	}
	void Shadow::Render()
	{
	}
	void Shadow::SetGroundMaterial()
	{
		mGroundMaterial = mShadow->GetName();
	}
}