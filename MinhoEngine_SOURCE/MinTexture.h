#pragma once
#include "MinResource.h"
namespace min::graphics
{
	class Texture : public Resource
	{
	public:
		enum class eTextureType 
		{
			Bmp,
			Png,
			None,
		};

		static Texture* Create(const std::wstring& name,UINT width, UINT height);

		Texture();
		~Texture();

		virtual HRESULT Save(const std::wstring path) override;
		virtual HRESULT Load(const std::wstring path) override;

		UINT GetWidth() { return mWidth; }
		void SetWidth(UINT width) { mWidth = width; }
		UINT GetHeight() { return mHeight; }
		void SetHeight(UINT height) { mHeight = height; }
		eTextureType GetTextureType() const { return mType; }
		bool IsAlpha() const { return mbAlpha; }

	private:
		bool mbAlpha;
		eTextureType mType;

		UINT mWidth;
		UINT mHeight;
	};
}

