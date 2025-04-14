#pragma once
#include "MinComponent.h"
#include "MinSkill.h"
#include "MinAnimator.h"

namespace min
{
	class SkillManager : public Component
	{
	public:
		SkillManager();
		~SkillManager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void UseSkill(std::wstring KeyValue, bool Direction);
		void SetSkillDamage(std::wstring KeyValue);

		void CreateSkillinfo();//std::wstring name, Vector3 Range, UINT Damage, XMFLOAT3 Extent

		Animator* GetAnimator() { return mSkillAnimator; }

	private:
		Animator* mSkillAnimator;
		std::unordered_map<std::wstring, std::unique_ptr<Skill>> mSkill;
		bool mActive;
		std::wstring mActiveName;
	};
}