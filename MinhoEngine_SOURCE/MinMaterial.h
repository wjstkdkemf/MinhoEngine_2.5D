#pragma once
#include "MinResource.h"
#include "MinTexture.h"
#include "MinShader.h"

namespace min
{
	class Material : public Resource
	{
	public:
		struct Data
		{
			std::wstring albedo;
		};

		Material();
		virtual ~Material();

		virtual HRESULT Save(const std::wstring path) override;
		virtual HRESULT Load(const std::wstring path) override;

		void Bind();
		void BindShader();
		void BindTextures();

		void SetShader(graphics::Shader* shader) { mShader = shader; }

	private:
		graphics::eRenderingMode mMode;
		Material::Data mData;

		graphics::Texture* mAlbedoTexture;
		graphics::Shader* mShader;
	};
}
