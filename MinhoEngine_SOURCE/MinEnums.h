#pragma once

namespace min::enums 
{
	enum class eComponentType
	{
		Transform,
		Camera,
		Collider,
		Rigidbody,
		Script,
		SpriteRenderer,
		Animator,
		Skill,
		Shadow,
		AudioListener,
		AudioSource,
		End,
	};


	enum class eLayerType
	{
		None,
		BackGround,
		Floor,
		FrontGround,
		Enemy,
		Player,
		SkillEffect,
		Particle,
		Skill_info,
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
		Rect2D,
		Circle2D,
		End,
	};

	enum class eUIType
	{
		HPBAR,
		Button,
		End,
	};
}
