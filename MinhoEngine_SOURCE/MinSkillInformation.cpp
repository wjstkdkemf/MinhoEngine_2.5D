#include "MinSkillInformation.h"


namespace min
{
	std::vector<SkillInformation::Skill_information*> SkillInformation::Skill_Informations = {};

	SkillInformation::SkillInformation()
	{
	}
	SkillInformation::~SkillInformation()
	{
	}
	void SkillInformation::CreateSkillInformation()
	{
		CreateSkillInformationByOnes(L"FirstSkill");
		CreateSkillInformationByOnes(L"SecondSkill");
		CreateSkillInformationByOnes(L"Skill_3");
	}
	void SkillInformation::CreateSkillInformationByOnes(std::wstring name)
	{
		Skill_information* Sin = new Skill_information;
		Sin->SkillName = name;
		Skill_Informations.push_back(Sin);
	}
}