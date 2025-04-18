#pragma once

namespace min::enums 
{
	enum class eComponentType
	{
		Transform,
		Camera,
		Rigidbody,
		Collider,
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
		Shadow,
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
		Rect2DAABB,
		Rect2DOBB,
		Circle2D,
		End,
	};

	enum class eUIType
	{
		SkillInventory,
		HPBAR,
		Button,
		End,
	};
}
