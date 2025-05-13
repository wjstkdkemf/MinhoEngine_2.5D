#pragma once
#include "MinEntity.h"
#include "MinComponent.h"
#include "MinTexture.h"
#include "MinMaterial.h"
#include "MinResources.h"
#include "MinMesh.h"

namespace min {
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void SetSprite(graphics::Texture* sprite) { mSprite = sprite; }
		void SetMaterial(Material* material) { mMaterial = material; }
		void SetMesh(std::wstring name) {mMesh = Resources::Find<Mesh>(name);}

		graphics::Texture* GetSprite() { return mSprite; }

	private:
		graphics::Texture* mSprite;
		Material* mMaterial;
		Mesh* mMesh;
	};
}

