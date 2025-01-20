#pragma once
#include "MinComponent.h"
#include "MinEntity.h"
#include "MinTexture.h"

namespace min
{
	class TilemapRender : public Component
	{
	public:
		TilemapRender();
		~TilemapRender();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetTexture(graphcis::Texture* texture) { mTexture = texture; }
		void SetSize(math::Vector2 size) { mSize = size; }
		void SetIndex(Vector2 Index) { mIndex = Index; }


	public:
		static Vector2 TileSize;
		static Vector2 OriginTileSize;
		static Vector2 SelectedIndex;
			
	private:
		Vector2 mTileSize;
		graphcis::Texture* mTexture;
		Vector2 mSize;
		Vector2 mIndex;
	};
}

