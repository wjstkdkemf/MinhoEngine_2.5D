#include "MinFirstSkill.h"
#include "MinObject.h"
#include "MinTransform.h"
#include "MinSkillManager.h"
#include "MinTime.h"
#include "MinBoxCollider2D.h"
#include "MinAnimator.h"
#include "MinResources.h"
#include <DirectXMath.h>

#include "..\\MinhoEngine_Window\\MinFirstSkillScript.h"
#include "..\\MinhoEngine_Window\\MinFirstSkillGameObject.h"



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
    void FirstSkill::Active(bool Direction)
    {
        FirstSkillGameObject* fsgo = object::Instantiate<FirstSkillGameObject>(eLayerType::SkillEffect, this->GetSkillManager()->GetOwner()->GetComponent<Transform>()->GetPosition());
        Transform* fstr = fsgo->GetComponent<Transform>();
        fstr->SetScale(0.5f, 0.3f, 0.0f);
        Vector3 pos = fstr->GetPosition();
        pos.x += 1.5f;
        fstr->SetPosition(pos);
        //fsgo->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 2.0f);
        FirstSkillScript* fssc = fsgo->AddComponent<FirstSkillScript>();

        Animator* fsAnimator = fsgo->AddComponent<Animator>();

        fsAnimator->CreateAnimation(GetSkillAnimation(), Resources::Find<graphics::Texture>(L"FirstSkill")
            , Vector2(0.0f, 0.0f), Vector2(386.0f, 246.0f), Vector2::Zero, 8, GetSkillDuration() / 8.0f); // duration / ÇÁ·¹ÀÓ °¹¼ö

        fssc->SetDuration(GetSkillDuration());

        BoxCollider2D* fsCollider = fsgo->AddComponent<BoxCollider2D>();
        Matrix fsmatrix = fstr->GetWorldMatrix();
        fsCollider->GetBoxCollider2D().Extents = XMFLOAT3(fsmatrix._11, fsmatrix._22 , 0);//GetmSkillCollider()

        
        /*if (mTime == 0.0f)
        {
            mSkillGameObject = object::Instantiate<Cat>(eLayerType::SkillEffect, this->GetSkillManager()->GetOwner()->GetComponent<Transform>()->GetPosition());
        }

        mTime += Time::DeltaTime();
        if (mTime < this->GetSkillDuration())
        {
            int a = 0;
        }
        else
        {
            this->SetFinish(true);
            mTime = 0;
            mSkillGameObject->death();
        }*/

    }
}