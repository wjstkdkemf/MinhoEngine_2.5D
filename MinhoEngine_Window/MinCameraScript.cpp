#include "MinCameraScript.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"
#include "minGameObject.h"
#include "MinAnimator.h"
#include "MinCat.h"
#include "MinCatScript.h"
#include "MinObject.h"
#include "MinResources.h"
#include "MinBoxCollider2D.h"
#include "MinCollider.h"


namespace min
{
	CameraScript::CameraScript()
	{
	}
	CameraScript::~CameraScript()
	{
	}
	void CameraScript::Initialize()
	{
	}
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (input::GetKey(eKeyCode::Right)) {
			pos.x += 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Left)) {
			pos.x -= 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Up)) {
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Down)) {
			pos.y += 100.0f * Time::DeltaTime();
		}
		tr->SetPosition(pos);

		if (input::GetKeyUp(eKeyCode::Right)
			|| input::GetKeyUp(eKeyCode::Left)
			|| input::GetKeyUp(eKeyCode::Up)
			|| input::GetKeyUp(eKeyCode::Down)) 
		{

		}
	}
	void CameraScript::LateUpdate()
	{
	}
	void CameraScript::Render()
	{
	}
}
