#pragma once
#include "MinEntity.h"
#include "MinComponent.h"

namespace min {
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Rander(HDC hdc) override;
	
		void ImageLoad(const std::wstring& path);

	private:
		Gdiplus::Image* mImage;
		UINT mWidth;
		UINT mHeight;
	};
}

