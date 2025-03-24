#include "MinFirstSkill.h"
#include "MinObject.h"
#include "MinTransform.h"
#include "MinSkillManager.h"
#include "MinTime.h"
#include "..\\MinhoEngine_Window\MinCat.h"


namespace min
{
    FirstSkill::FirstSkill()
        : mTime(0.0f)
    {
        this->SetSkillColType(eColliderType::Rect2D);
        this->SetSkillDamage(100.0f);
        this->SetSkillPosition(Vector3::Zero);
        this->SetSkillAnimation(L"FirstSkill");
        this->SetSkillDuration(2.0f);
    }
    FirstSkill::~FirstSkill()
    {
    }
    void FirstSkill::Active()
    {
        Cat* FirstSkillObj = object::Instantiate<Cat>(eLayerType::SkillEffect, this->GetSkillManager()->GetOwner()->GetComponent<Transform>()->GetPosition());

        mTime += Time::DeltaTime();
        if (mTime < this->GetSkillDuration())
        {
            int a = 0;
        }
        else
            this->SetFinish(true);
    }
}