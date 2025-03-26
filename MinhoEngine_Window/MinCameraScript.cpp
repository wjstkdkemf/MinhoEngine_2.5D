#include "MinCameraScript.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"
#include "minGameObject.h"
#include "MinAnimator.h"
#include "MinEffect.h"
#include "MinObject.h"
#include "MinResources.h"
#include "MinBoxCollider2D.h"
#include "MinCollider.h"
#include "MinCamera.h"

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
		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		if (input::GetKey(eKeyCode::Right)) {
			pos += 20.0f * tr->Right() * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Left)) {
			pos += 20.0f * -tr->Right() * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Up)) {
			pos += 20.0f * tr->Up() * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Down)) {
			pos += 20.0f * -tr->Up() * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::E)) {
			pos += 20.0f * tr->Foward() * Time::DeltaTime();
		}
		if (input::GetKey(eKeyCode::Q)) {
			pos += 20.0f * -tr->Foward() * Time::DeltaTime();
		}
		tr->SetPosition(pos);

		if (input::GetKeyUp(eKeyCode::Right)
			|| input::GetKeyUp(eKeyCode::Left)
			|| input::GetKeyUp(eKeyCode::Up)
			|| input::GetKeyUp(eKeyCode::Down)) 
		{
		}*/
	}
	void CameraScript::LateUpdate()
	{
	}
	void CameraScript::Render()
	{
	}
}
