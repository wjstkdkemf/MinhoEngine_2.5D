#include "MinScript.h"
#include "MinCollider.h"

namespace min
{
	Script::Script()
		: Component(enums::eComponentType::Script)
	{

	}
	Script::~Script()
	{
	}
	void Script::Initialize()
	{
	}
	void Script::Update()
	{
	}
	void Script::LateUpdate()
	{
	}
	void Script::Render(HDC hdc)
	{
	}
	void Script::OnCollisionEnter(Collider* other)
	{
	}
	void Script::OnCollisionStay(Collider* other)
	{
	}
	void Script::OnCollisionExit(Collider* other)
	{
	}
}
