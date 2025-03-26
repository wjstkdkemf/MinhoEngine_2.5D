#include "MinFirstSkillScript.h"
#include "MinTime.h"
#include "MinObject.h"
#include "MinAnimator.h"
#include "MinTransform.h"
namespace min
{
    FirstSkillScript::FirstSkillScript()
        : mAnimator(nullptr)
        , mState(min::FirstSkillScript::eState::Run)
        , mTime(0.0f)
        , mDuration(0.0f)
    {
    }
    FirstSkillScript::~FirstSkillScript()
    {
    }
    void FirstSkillScript::Initialize()
    {
    }
    void FirstSkillScript::Update()
    {
        mTime += Time::DeltaTime();
        Transform* tr = GetOwner()->GetComponent<Transform>();

        if (mTime > mDuration)
            object::Destory(GetOwner());
        if (mAnimator == nullptr)
            mAnimator = GetOwner()->GetComponent<Animator>();

        switch (mState)
        {
        case min::FirstSkillScript::eState::Run:
            SkillPlayAnimation();
            break;
        case min::FirstSkillScript::eState::idle:
            Move(tr);
            break;
        case min::FirstSkillScript::eState::Hit:
            break;
        default:
            break;
        }
    }
    void FirstSkillScript::LateUpdate()
    {
    }
    void FirstSkillScript::Render()
    {
    }
    void FirstSkillScript::SkillPlayAnimation()
    {
        mAnimator->PlayAnimation(L"FirstSkill", false);
        mState = eState::idle;
    }
    void FirstSkillScript::Move(Transform* tr)
    {
        Vector3 pos = tr->GetPosition();

        pos.x += 10.0f * Time::DeltaTime();
        //tr->SetPosition(pos.x , pos.y, pos.z);
    }
    void FirstSkillScript::OnCollisionEnter(Collider* other)
    {
    }
    void FirstSkillScript::OnCollisionStay(Collider* other)
    {
    }
    void FirstSkillScript::OnCollisionExit(Collider* other)
    {
    }
}