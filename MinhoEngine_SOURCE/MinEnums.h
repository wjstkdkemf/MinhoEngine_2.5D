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
		FrontGround,
		Enemy,
		Player,
		Floor,
		Particle,
		Max = 16,
	};

	enum class eResourceType 
	{
		Texture,
		Mesh,
		Material,
		AudioClip,
		Animation,
		Shader,
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
