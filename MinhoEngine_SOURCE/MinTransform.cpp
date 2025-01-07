#include "MinTransform.h"

min::Transform::Transform()
	: Component(enums::eComponentType::Transform)
	, mScale(Vector2::One)
	, mRotation(0.0f)
{
}

min::Transform::~Transform()
{
}

void min::Transform::Initialize()
{
}

void min::Transform::Update()
{
}

void min::Transform::LateUpdate()
{
}

void min::Transform::Render(HDC hdc)
{
}
