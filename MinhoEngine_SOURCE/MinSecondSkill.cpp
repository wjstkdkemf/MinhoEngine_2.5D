#include "MinSecondSkill.h"
#include "MinObject.h"
#include "MinTransform.h"
#include "MinSkillManager.h"
#include "MinTime.h"
#include "..\\MinhoEngine_Window\MinEffect.h"
#include "..\\MinhoEngine_Window\MinSkillGameObject.h"
#include "..\\MinhoEngine_Window\MinSecondSkillScript.h"
#include "MinBoxCollider2DOBB.h"

namespace min
{
	SecondSkill::SecondSkill()
		: mTime(0.0f)
	{
		this->SetSkillColType(eColliderType::Rect2DOBB);
		this->SetSkillDamage(50.0f);
		this->SetSkillPosition(Vector3(0.5f, 0.2f, 0.0f));
		this->SetSkillAnimation(L"SecondSkill");
		this->SetSkillDuration(0.1f);//스킬 지속 시간
	}
	SecondSkill::~SecondSkill()
	{
	}
	void SecondSkill::Active(bool Direction)
	{
        SkillGameObject* ssgo = object::Instantiate<SkillGameObject>(eLayerType::SkillEffect, this->GetSkillManager()->GetOwner()->GetComponent<Transform>()->GetPosition());
#pragma region 기초설정
        Transform* sstr = ssgo->GetComponent<Transform>();
        sstr->SetScale(0.1f, 0.5f, 0.0f);
        Vector3 pos = sstr->GetPosition();
        Vector3 Rot = sstr->GetRotation();

        if (Direction)
        {
            pos.x += GetSkillPosition().x;
            sstr->SetRotation(Rot.x, Rot.y, Rot.z -35.0f);
        }
        else
        {
            pos.x -= GetSkillPosition().x;
            sstr->SetRotation(Rot.x, Rot.y, Rot.z + 35.0f);
        }

        pos.y += GetSkillPosition().y;

        sstr->SetPosition(pos);
        ssgo->SetDamage(GetSkillDamage());

        SecondSkillScript* sssc = ssgo->AddComponent<SecondSkillScript>();

        sssc->SetSetting(this->GetSkillManager()->GetOwner()->GetComponent<Transform>()->GetPosition(), sstr->GetPosition());
        sssc->SetDirection(Direction);

        Animator* fsAnimator = ssgo->AddComponent<Animator>();

        //fsAnimator->CreateAnimation(GetSkillAnimation(), Resources::Find<graphics::Texture>(L"FirstSkill")
        //    , Vector2(0.0f, 0.0f), Vector2(386.0f, 246.0f), Vector2::Zero, 8, GetSkillDuration() / 8.0f); // duration / 프레임 갯수

        sssc->SetDuration(GetSkillDuration());
#pragma endregion
        BoxCollider2DOBB* fsCollider = ssgo->AddComponent<BoxCollider2DOBB>();
        Matrix fsmatrix = sstr->GetWorldMatrix();
        fsCollider->GetBoxCollider2D().Extents = XMFLOAT3(fsmatrix._11, fsmatrix._22, 0);
	}
}
