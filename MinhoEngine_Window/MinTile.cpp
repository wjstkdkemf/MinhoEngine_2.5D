#include "MinTile.h"
#include "Mininput.h"
#include "MinTransform.h"
#include "MinTime.h"
#include "MinTilemapRender.h"

namespace min
{

	void Tile::Initialize()
	{
		GameObject::Initialize();
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Tile::Rander(HDC hdc)
	{
		GameObject::Rander(hdc);
	}

	void Tile::SetIndexPosition(int x, int y)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos;
		pos.x = x * TilemapRender::TileSize.x;
		pos.y = y * TilemapRender::TileSize.y;
		tr->SetPosition(pos);
	}
}
