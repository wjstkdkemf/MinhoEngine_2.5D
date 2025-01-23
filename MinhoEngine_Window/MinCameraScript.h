#pragma once
#include "..\\MinhoEngine_SOURCE\\MinScript.h"
#include "..\\MinhoEngine_SOURCE\\MinTransform.h"

namespace min
{
	class CameraScript :public Script
	{
	public:
		CameraScript();
		~CameraScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
	};
}

