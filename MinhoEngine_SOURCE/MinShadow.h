#pragma once
#include "MinComponent.h"

namespace min
{
	class Shadow : public Component
	{
	public:
		Shadow();
		~Shadow();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetGroundMaterial();
		std::wstring& GetGroundMaterial() { return mGroundMaterial; }
		
		class Effect* GetShadow() { return mShadow; }

	private:
		class Effect* mShadow;
		std::wstring mGroundMaterial;

	};
}

