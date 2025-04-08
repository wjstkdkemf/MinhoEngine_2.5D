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
		: mMaxWidthInOrgan(0.0f)
		, mMaxHeightInOrgan(0.0f)
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
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();
		//if (input::GetKey(eKeyCode::Right)) {
		//	pos += 20.0f * tr->Right() * Time::DeltaTime();
		//}
		//if (input::GetKey(eKeyCode::Left)) {
		//	pos += 20.0f * -tr->Right() * Time::DeltaTime();
		//}
		//if (input::GetKey(eKeyCode::Up)) {
		//	pos += 20.0f * tr->Up() * Time::DeltaTime();
		//}
		//if (input::GetKey(eKeyCode::Down)) {
		//	pos += 20.0f * -tr->Up() * Time::DeltaTime();
		//}
		//if (input::GetKey(eKeyCode::E)) {
		//	pos += 20.0f * tr->Foward() * Time::DeltaTime();
		//}
		//if (input::GetKey(eKeyCode::Q)) {
		//	pos += 20.0f * -tr->Foward() * Time::DeltaTime();
		//}
		//tr->SetPosition(pos);

		//if (input::GetKeyUp(eKeyCode::Right)
		//	|| input::GetKeyUp(eKeyCode::Left)
		//	|| input::GetKeyUp(eKeyCode::Up)
		//	|| input::GetKeyUp(eKeyCode::Down)) 
		//{
		//}
	}
	void CameraScript::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (mPlayer == nullptr)
			return ;

		Transform* prtr = mPlayer->GetComponent<Transform>();
		Vector3 pos = prtr->GetPosition();

		float lx = (mFieldSize.x - mMaxWidthInOrgan) / 2;
		float clampX = std::clamp(pos.x, -lx, lx ); // 추후lx 부분을 ground의 position으로 조정해줘야함 

		//float ly = (mFieldSize.y - mMaxHeightInOrgan) / 2;
		//float clampY = std::clamp(pos.y, -ly, ly);


		tr->SetPosition(clampX, pos.y, pos.z - 5.0f);
	}
	void CameraScript::Render()
	{
	}
}
