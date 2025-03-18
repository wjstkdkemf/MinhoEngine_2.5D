#include "MinEnemyScript.h"

namespace min
{
	EnemyScript::EnemyScript()
		:mState(EnemyScript::eState::idle)
		, mAnimator(nullptr)
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
	}
	void EnemyScript::Render()
	{
	}
	void EnemyScript::OnCollisionEnter(Collider* other)
	{
	}
	void EnemyScript::OnCollisionStay(Collider* other)
	{
	}
	void EnemyScript::OnCollisionExit(Collider* other)
	{
	}
}