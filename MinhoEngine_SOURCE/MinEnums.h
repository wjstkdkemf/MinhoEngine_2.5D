#pragma once

namespace min::enums 
{
	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animator,
		Script,
		Camera,
		End,
	};


	enum class eLayerType
	{
		None,
		BackGround,
		FrontGround,
		Animal,
		Player,
		Particle,
		Max = 16,
	};

	enum class eResourceType 
	{
		Texture,
		AudioClip,
		Animation,
		Prefab,
		End,
	};
}
