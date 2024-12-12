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
		Player,
		Max = 6,
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
