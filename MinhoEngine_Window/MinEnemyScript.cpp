#include "MinEnemyScript.h"
#include "minGameObject.h"
#include "MinCollider.h"
#include "MinSkillGameObject.h"
namespace min
{
	EnemyScript::EnemyScript()
		:mState(EnemyScript::eState::idle)
		, mAnimator(nullptr)
		, HP(100.0f)
	{
	}
	EnemyScript::~EnemyScript()
	{
	}
	void EnemyScript::Initialize()
	{
	}
	void EnemyScript::Update()
	{
	}
	void EnemyScript::LateUpdate()
	{
		if (HP <= 0.0f)
			GetOwner()->death();
	}
	void EnemyScript::Render()
	{
	}
	void EnemyScript::OnCollisionEnter(Collider* other)
	{
		HP -= ((SkillGameObject*)(other->GetOwner()))->GetDamage();
	}
	void EnemyScript::OnCollisionStay(Collider* other)
	{
	}
	void EnemyScript::OnCollisionExit(Collider* other)
	{
	}
}