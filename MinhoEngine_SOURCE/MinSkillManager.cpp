#include "MinSkillManager.h"
#include "minGameObject.h"
#include "MinFirstSkill.h"
#include "MinSecondSkill.h"

namespace min
{
	SkillManager::SkillManager()
		:Component(enums::eComponentType::Skill)
		, mSkillAnimator(nullptr)
	{
	}
	SkillManager::~SkillManager()
	{
	}
	void SkillManager::Initialize()
	{
		//mSkillAnimator = GetOwner()->GetComponent<Animator>();
		CreateSkillinfo();
	}
	void SkillManager::Update()
	{
	}
	void SkillManager::LateUpdate()
	{
		if (mActive)
		{
			if (mSkill[mActiveName]->GetFinish())
			{
				mActive = false;
				mSkill[mActiveName]->SetFinish(false);
			}

			mSkill[mActiveName]->Active();
		}
		
	}
	void SkillManager::Render()
	{
	}
	void SkillManager::UseSkill(std::wstring KeyValue)
	{
		if (mSkill.find(KeyValue) != mSkill.end())
		{
			mSkill[KeyValue]->Active();
			mActiveName = KeyValue;
			mActive = true;
		}
	}
	void SkillManager::CreateSkillinfo()//std::wstring name, Vector3 Range, UINT Damage, XMFLOAT3 Extent
	{
		std::unique_ptr<FirstSkill> F_skill = std::make_unique<FirstSkill>() ;
		F_skill->SetSkillManager(this);
		std::unique_ptr<SecondSkill> S_skill = std::make_unique<SecondSkill>();
		S_skill->SetSkillManager(this);
		
		F_skill->SetSkillManager(this);

		mSkill[L"FirstSkill"] = std::move(F_skill);
		mSkill[L"SecondSkill"] = std::move(S_skill);

	//	mSkill.push_back(mSkillMake);
	}
}