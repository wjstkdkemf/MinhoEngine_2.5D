#pragma once
#include "MinSkill.h"


namespace min
{
	class FirstSkill : public Skill
	{
	public:
		FirstSkill();
		~FirstSkill();

		void Active() override;

	private:
		float mTime;
	};
}

