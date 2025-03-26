#pragma once
#include "MinSkill.h"
#include "..\\MinhoEngine_Window\MinEffect.h"

namespace min
{
	class FirstSkill : public Skill
	{
	public:
		FirstSkill();
		~FirstSkill();

		void Active(bool Direction) override;

	private:
		float mTime;
	};
}

