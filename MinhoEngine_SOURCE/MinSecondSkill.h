#pragma once
#include "MinSkill.h"


namespace min
{
	class SecondSkill : public Skill
	{
	public:
		SecondSkill();
		~SecondSkill();

		 void Active(bool Direction) override;

	private:
		float mTime;
	};
}

