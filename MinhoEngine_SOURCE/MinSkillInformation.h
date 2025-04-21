#pragma once
#include "commoninclude.h"
#include "MinMath.h"

namespace min
{
	class SkillInformation// 나중에 저장, 불러오기를 위해서 형태만 구현
	{
	public:
		struct Skill_information
		{
			std::wstring SkillName;
			math::Vector2 Pos;
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

