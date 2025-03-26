#include "MinTransform.h"
#include "MinGraphics.h"
#include "MinCamera.h"
#include "MinConstantBuffer.h"
#include "MinRenderer.h"

#include "DirectXMath.h"

namespace min {

	Transform::Transform()
		: Component(enums::eComponentType::Transform)
		, mWorldMatrix(Matrix::Identity)
		, mScale(Vector3::One)
		, mRotation(Vector3::Zero)
		, mPosition(Vector3::Zero)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::LateUpdate()
	{
		Matrix scale = Matrix::CreateScale(mScale.x, mScale.y, mScale.z);
		Matrix rotation = Matrix::CreateRotationX(math::Radian(mRotation.x));
		rotation *= Matrix::CreateRotationY(math::Radian(mRotation.y));
		rotation *= Matrix::CreateRotationZ(math::Radian(mRotation.z));
		Matrix translation = Matrix::CreateTranslation(mPosition);

		mWorldMatrix = scale * rotation * translation;

		mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
	}

	void Transform::Render()
	{
	}

	void Transform::Bind()
	{
		graphics::TransformCB cbData = {};
		cbData.world = GetWorldMatrix();
		cbData.view = Camera::GetGpuViewMatrix();
		cbData.projection = Camera::GetGpuProjectionMatrix();

		graphics::ConstantBuffer* cb = renderer::constantBuffers[CBSLOT_TRANSFORM];

		cb->SetData(&cbData);
		cb->Bind(eShaderStage::All);
	}

	XMFLOAT4 Transform::TransformToClipSpace(XMFLOAT3 pos) {
		// 1. 원래 좌표를 float4로 확장 (w=1.0f)
		XMVECTOR position = XMVectorSet(pos.x, pos.y, pos.z, 1.0f);

		// 2. 월드 변환
		position = XMVector4Transform(position, GetWorldMatrix());

		Matrix ViewMatrix_t = Camera::GetGpuViewMatrix();
		// 3. 뷰 변환
		position = XMVector4Transform(position, ViewMatrix_t.Invert());
		// 4. 투영 변환
		position = XMVector4Transform(position, Camera::GetGpuProjectionMatrix().Invert());

		// 결과 저장
		XMFLOAT4 clipPos;
		XMStoreFloat4(&clipPos, position);
		return clipPos;
	}
}