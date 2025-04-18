#pragma once
#include "commoninclude.h"

namespace min
{
	class SkillInformation
	{
	public:
		struct Skill_information
		{
			std::wstring SkillName;
		};

	public:
		SkillInformation();
		~SkillInformation();

		static void CreateSkillInformation();
		static void CreateSkillInformationByOnes(std::wstring name);

		static std::vector<Skill_information*> GetSkillInformation() { return Skill_Informations; }

	private:
		static std::vector<Skill_information*> Skill_Informations;
	};
}

