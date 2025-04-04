#include "MinSecondSkillScript.h"
#include "MinTime.h"
#include "MinObject.h"
#include "MinAnimator.h"
#include "MinTransform.h"
namespace min
{
    SecondSkillScript::SecondSkillScript()
        : mAnimator(nullptr)
        , mState(min::SecondSkillScript::eState::Run)
        , mTime(0.0f)
        , mDuration(0.0f)
        , mPivot()
        , mStart() 
        , mAngle(0.0f)
        , mDeltaAngle(-5.0f)
    {
    }
    SecondSkillScript::~SecondSkillScript()
    {
    }
    void SecondSkillScript::Initialize()
    {
    }
    void SecondSkillScript::Update()
    {
        mTime += Time::DeltaTime();
        Transform* tr = GetOwner()->GetComponent<Transform>();

        if (mTime > mDuration)
            object::Destory(GetOwner());
        if (mAnimator == nullptr)
            mAnimator = GetOwner()->GetComponent<Animator>();

        switch (mState)
        {
        case min::SecondSkillScript::eState::Run:
            SkillPlayAnimation();
            break;
        case min::SecondSkillScript::eState::idle:
            Move(tr);
            break;
        case min::SecondSkillScript::eState::Hit:
            break;
        default:
            break;
        }
    }
    void SecondSkillScript::LateUpdate()
    {
    }
    void SecondSkillScript::Render()
    {
    }
    void SecondSkillScript::SkillPlayAnimation()
    {
        //mAnimator->PlayAnimation(L"FirstSkill", false);
        mState = eState::idle;
    }
    void SecondSkillScript::Move(Transform* tr)
    {
        Vector3 pos = tr->GetPosition();

        UpdateSetting();

        if (mDeltaAngle == -5.0f && !mDirection)
            mDeltaAngle = 5.0f;

        tr->SetPosition(mStart.x, mStart.y, pos.z);
    }
    void SecondSkillScript::OnCollisionEnter(Collider* other)
    {
    }
    void SecondSkillScript::OnCollisionStay(Collider* other)
    {
    }
    void SecondSkillScript::OnCollisionExit(Collider* other)
    {
    }
    void SecondSkillScript::SetSetting(Vector3 pivot, Vector3 Start)
    {
        mPivot.x = pivot.x;
        mPivot.y = pivot.y;

        mStart.x = Start.x;
        mStart.y = Start.y;
    }
    void SecondSkillScript::UpdateSetting()
    {
        mAngle += mDeltaAngle;  // 회전각 변화
        mStart = mStart.Rotate(mDeltaAngle, mPivot);
    }
}