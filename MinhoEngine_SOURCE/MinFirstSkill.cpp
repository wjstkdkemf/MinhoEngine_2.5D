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
#include "..\\MinhoEngine_Window\\MinSkillGameObject.h"



namespace min
{
    FirstSkill::FirstSkill()
        : mTime(0.0f)
    {
        SetSkillColType(eColliderType::Rect2DAABB);
        SetSkillDamage(100.0f);
        SetSkillPosition(Vector3(1.5f, 0.0f , 0.0f));
        SetSkillAnimation(L"FirstSkill");
        SetSkillDuration(2.0f);
    }
    FirstSkill::~FirstSkill()
    {
    }
    void FirstSkill::Active(bool Direction)
    {
        SkillGameObject* fsgo = object::Instantiate<SkillGameObject>(eLayerType::SkillEffect, this->GetSkillManager()->GetOwner()->GetComponent<Transform>()->GetPosition());

#pragma region 기초설정
        Transform* fstr = fsgo->GetComponent<Transform>();
        fstr->SetScale(0.5f, 0.3f, 0.0f);
        Vector3 pos = fstr->GetPosition();

        if (Direction)
            pos.x += GetSkillPosition().x;
        else
            pos.x -= GetSkillPosition().x;

        fstr->SetPosition(pos);
        //fsgo->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 2.0f);
        FirstSkillScript* fssc = fsgo->AddComponent<FirstSkillScript>();

        fssc->SetDirection(Direction);

        fsgo->SetDamage(GetSkillDamage());
        fssc->SetDuration(GetSkillDuration());

        Animator* fsAnimator = fsgo->AddComponent<Animator>();
        fsAnimator->CreateAnimation(GetSkillAnimation(), Resources::Find<graphics::Texture>(L"FirstSkill")
            , Vector2(0.0f, 0.0f), Vector2(386.0f, 246.0f), Vector2::Zero, 8, GetSkillDuration() / 8.0f); // duration / 프레임 갯수

#pragma endregion

        BoxCollider2D* fsCollider = fsgo->AddComponent<BoxCollider2D>();
        Matrix fsmatrix = fstr->GetWorldMatrix();
        fsCollider->GetBoxCollider2D().Extents = XMFLOAT3(fsmatrix._11, fsmatrix._22 , 0);


    }
}