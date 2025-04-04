#include "MinSecondSkill.h"
#include "MinObject.h"
#include "MinTransform.h"
#include "MinSkillManager.h"
#include "MinTime.h"
#include "..\\MinhoEngine_Window\MinEffect.h"
#include "..\\MinhoEngine_Window\MinSkillGameObject.h"
#include "..\\MinhoEngine_Window\MinSecondSkillScript.h"

namespace min
{
	SecondSkill::SecondSkill()
		: mTime(0.0f)
	{
		this->SetSkillColType(eColliderType::Rect2D);
		this->SetSkillDamage(100.0f);
		this->SetSkillPosition(Vector3::Zero);
		this->SetSkillAnimation(L"SecondSkill");
		this->SetSkillDuration(0.3f);
	}
	SecondSkill::~SecondSkill()
	{
	}
	void SecondSkill::Active(bool Direction)
	{
        SkillGameObject* ssgo = object::Instantiate<SkillGameObject>(eLayerType::SkillEffect, this->GetSkillManager()->GetOwner()->GetComponent<Transform>()->GetPosition());
        Transform* sstr = ssgo->GetComponent<Transform>();
        sstr->SetScale(0.5f, 0.3f, 0.0f);
        Vector3 pos = sstr->GetPosition();

        if (Direction)
            pos.x += 0.5f;
        else
            pos.x -= 0.5f;



        sstr->SetPosition(pos);
        
        SecondSkillScript* sssc = ssgo->AddComponent<SecondSkillScript>();

        sssc->SetSetting(this->GetSkillManager()->GetOwner()->GetComponent<Transform>()->GetPosition(), sstr->GetPosition());
        sssc->SetDirection(Direction);

        Animator* fsAnimator = ssgo->AddComponent<Animator>();

        //fsAnimator->CreateAnimation(GetSkillAnimation(), Resources::Find<graphics::Texture>(L"FirstSkill")
        //    , Vector2(0.0f, 0.0f), Vector2(386.0f, 246.0f), Vector2::Zero, 8, GetSkillDuration() / 8.0f); // duration / ÇÁ·¹ÀÓ °¹¼ö

        sssc->SetDuration(GetSkillDuration());

        BoxCollider2D* fsCollider = ssgo->AddComponent<BoxCollider2D>();
        Matrix fsmatrix = sstr->GetWorldMatrix();
        fsCollider->GetBoxCollider2D().Extents = XMFLOAT3(fsmatrix._11, fsmatrix._22, 0);
	}
}
