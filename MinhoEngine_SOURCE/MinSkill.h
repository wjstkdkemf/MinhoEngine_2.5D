#pragma once
#include "MinResource.h"
#include "MinAnimation.h"
#include "MinBoxCollider2D.h"
#include "MinAnimator.h"
#include "MinComponent.h"

namespace min
{
	class Skill
	{
	public:
		Skill();
		virtual ~Skill();

		virtual void Active(bool Direction) = 0;

		void SetSkillAnimation(std::wstring name) { mSkillAnimation = name; }
		void SetSkillPosition(Vector3 Position) { mSkillPosition = Position; }
		void SetSkillDamage(float Damage) { mSkillDamage = Damage; }
		void SetSkillColType(enums::eColliderType Type) { mSkillColType = Type; }
		void SetSkillManager(class SkillManager* skillmanager) { mSkillManager = skillmanager; }
		void SetSkillDuration(float Time) { SkillDuration = Time; }
		void SetFinish(bool fin) { mFinish = fin; }

		std::wstring GetSkillAnimation() { return mSkillAnimation; }
		float GetSkillDuration() {return SkillDuration; }
		float GetSkillDamage() { return mSkillDamage; }
		Vector3 GetSkillPosition() { return mSkillPosition; }
		bool GetFinish() { return mFinish; }
		XMFLOAT3 GetmSkillCollider() { return ColliderExtent; }


		class SkillManager* GetSkillManager() { return mSkillManager; }

		void SetmSkillCollider(XMFLOAT3 Extent) { ColliderExtent = Extent; }//mSkillCollider.GetBoxCollider2D().Extents


	private:
		XMFLOAT3 ColliderExtent;
		class SkillManager* mSkillManager;
		enums::eColliderType mSkillColType; // ��ų�� collider ����
		std::wstring mSkillAnimation; // ��ų�� �ִϸ��̼� �̸� -> �̸� �ִϸ����Ϳ� load �س�����.

		Vector3 mSkillPosition;// ��� �������� ������ �Ҳ���
		float mSkillDamage; // ��ų�� ��������
		float SkillDuration; // ��ų ���ӽð�

		bool mFinish;
	};
}

