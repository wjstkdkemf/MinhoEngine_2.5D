#pragma once

namespace min::graphics
{
	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		All,
		End,
	};

	enum class eCBType
	{
		Transform,
		End,
	};
}

