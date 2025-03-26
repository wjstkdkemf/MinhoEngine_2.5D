#include "MinSkill.h"

namespace min
{
    Skill::Skill()
        : mSkillPosition(Vector3::Zero)
        , mSkillDamage(0)
        , mSkillManager(nullptr)
        , mFinish(false)
        , ColliderExtent(1.0f,1.0f,0.0f)
    {
    }
    Skill::~Skill()
    {
        
    }
    void Skill::Active(bool Direction)
    {
    }
}