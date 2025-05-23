#include "MinCamera.h"
#include "minGameObject.h"
#include "MinTransform.h"
#include "MinApplication.h"
#include "..\\MinhoEngine_Window\MinCameraScript.h"

extern min::Application application;

namespace min
{
	Matrix Camera::ViewMatrix = Matrix::Identity;
	Matrix Camera::ProjectionMatrix = Matrix::Identity;
	Vector3 Camera::mCameraPosition = Vector3::Zero;

	Camera::Camera()
		:Component(enums::eComponentType::Camera)
		, mProjectionType(eProjectionType::Orthographic)
		, mViewMatrix(Matrix::Identity)
		, mProjectionMatrix(Matrix::Identity)
		, mAspectRatio(0.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mSize(1.0f)

	{
	}
	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
	}
	void Camera::Update()
	{
	}
	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(mProjectionType);

		ViewMatrix = mViewMatrix;
		ProjectionMatrix = mProjectionMatrix;
	}
	void Camera::Render()
	{
	}
	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mCameraPosition = tr->GetPosition();

		const Vector3 pos = tr->GetPosition();
		const Vector3 up = tr->Up();
		const Vector3 forward = tr->Foward();

		mViewMatrix = Matrix::CreateLookToLH(pos, forward, up);

		//XMMATRIX mViewMatrix = Matrix::CreateLookToLH(pos, forward, up);
	}
	void Camera::CreateProjectionMatrix(eProjectionType type)
	{
		RECT winRect;
		GetClientRect(application.GetWindow().GetHwnd(), &winRect);
		float width = (winRect.right - winRect.left);
		float height = (winRect.bottom - winRect.top);

		GetOwner()->GetComponent<CameraScript>()->SetFieldMaxSize(width / mSize, height / mSize);
		mAspectRatio = width / height;
		switch (type)
		{
		case eProjectionType::Perspective:
			mProjectionMatrix = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
			break;
		case eProjectionType::Orthographic:
			mProjectionMatrix = Matrix::CreateOrthographicLH(width / mSize, height / mSize, mNear, mFar);
			break;
		}
	}
}