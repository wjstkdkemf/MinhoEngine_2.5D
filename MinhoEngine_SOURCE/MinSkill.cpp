#include "MinSkill.h"

namespace min
{
    Skill::Skill()
        : mSkillPosition(Vector3::Zero)
        , mSkillDamage(0)
        , mSkillManager(nullptr)
        , mFinish(false)
    {
    }
    Skill::~Skill()
    {
        
    }
    void Skill::Active()
    {
    }
}