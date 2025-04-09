#pragma once
#include "..\\MinhoEngine_SOURCE\\MinScript.h"
#include "..\\MinhoEngine_SOURCE\\MinTransform.h"
#include "MinPlayer.h"


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
		void Render() override;

		void SetPlayer(Player* player) { mPlayer = player; }
		void SetFieldSize(Vector3 Size) { mFieldSize = Size; }

		void SetFieldMaxSize(float X , float Y)
		{
			mMaxWidthInOrgan = X;
			mMaxHeightInOrgan = Y;
		}
		float GetMaxWidth() { return mMaxWidthInOrgan; }
		float GetMaxHeight() { return mMaxHeightInOrgan; }


	private:
		Player* mPlayer;
		Vector3 mFieldSize;

		float mMaxWidthInOrgan;
		float mMaxHeightInOrgan;
	};
}

