#pragma once

namespace min::enums 
{
	enum class eComponentType
	{
		Transform,
		Collider,
		Rigidbody,
		Script,
		SpriteRenderer,
		Animator,
		Camera,
		AudioListener,
		AudioSource,
		End,
	};


	enum class eLayerType
	{
		None,
		BackGround,
		Tile,
		FrontGround,
		Animal,
		Player,
		Floor,
		Particle,
		Max = 16,
	};

	enum class eResourceType 
	{
		Texture,
		Mesh,
		AudioClip,
		Animation,
		Shader,
		Material,
		Prefab,
		End,
	};

	enum class eColliderType
	{
		Circle2D,
		Rect2D,
		End,
	};

	enum class eUIType
	{
		HPBAR,
		Button,
		End,
	};
}
