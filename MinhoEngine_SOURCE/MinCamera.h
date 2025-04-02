#pragma once
#include "MinComponent.h"

namespace min
{
	using namespace min::math;
	class Camera : public Component
	{
	public:
		enum class eProjectionType
		{
			Perspective,
			Orthographic
		};

		static Matrix GetGpuViewMatrix() { return ViewMatrix; }
		static Matrix GetGpuProjectionMatrix() { return ProjectionMatrix; }

		static Vector3 GetCameraPosition() { return mCameraPosition; }
		static void SetGpuViewMatrix(Matrix matrix) { ViewMatrix = matrix; }
		static void SetGpuProjectionMatrix(Matrix matrix) { ProjectionMatrix = matrix; }

		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix(eProjectionType type);

		void SetProjectionType(eProjectionType type) { mProjectionType = type; }
		void SetSize(float size) { mSize = size; }

		const Matrix& GetViewMatrix() { return mViewMatrix; }
		const Matrix& GetProjectionMatrix() { return mProjectionMatrix; }


	private:
		static Matrix ViewMatrix;
		static Matrix ProjectionMatrix;
		static Vector3 mCameraPosition;

		eProjectionType mProjectionType;

		Matrix mViewMatrix;
		Matrix mProjectionMatrix;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;


	};
}

