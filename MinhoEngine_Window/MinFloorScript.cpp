#include "MinFloorScript.h"
#include "MinCatScript.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"
#include "minGameObject.h"
#include "MinAnimator.h"
#include "MinObject.h"
#include "MinCollider.h"
#include "MinRigidbody.h"

namespace min
{
	FloorScript::FloorScript()
	{
	}
	FloorScript::~FloorScript()
	{
	}
	void FloorScript::Initialize()
	{

	}
	void FloorScript::Update()
	{
	}
	void FloorScript::LateUpdate()
	{
	}
	void FloorScript::Render(HDC hdc)
	{
	}
	void FloorScript::OnCollisionEnter(Collider* other)
	{
		Rigidbody* playerRb = other->GetOwner()->GetComponent<Rigidbody>();
		Transform* playerTr = other->GetOwner()->GetComponent<Transform>();
		Collider* PlayerCol = other->GetOwner()->GetComponent<Collider>();

		Rigidbody* floorRb = this->GetOwner()->GetComponent<Rigidbody>();
		Transform* floorTr = this->GetOwner()->GetComponent<Transform>();
		Collider* floorCol = this->GetOwner()->GetComponent<Collider>();
		float len = fabs(playerTr->GetPosition().y - floorTr->GetPosition().y);
		float scale = fabs(PlayerCol->GetSize().y * 100 / 2.0f - floorCol->GetSize().y * 100 / 2.0f);

		if (len <= scale)
		{
			Vector2 playerPos = playerTr->GetPosition();
			playerPos.y -= (scale - len) - 1.0f;

			playerTr->SetPosition(playerPos);
		}

		playerRb->SetGround(true);
	}
	void FloorScript::OnCollisionStay(Collider* other)
	{
	}
	void FloorScript::OnCollisionExit(Collider* other)
	{
	}
}
