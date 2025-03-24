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

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void UseSkill(std::wstring KeyValue);

		void CreateSkillinfo();//std::wstring name, Vector3 Range, UINT Damage, XMFLOAT3 Extent

		Animator* GetAnimator() { return mSkillAnimator; }

	private:
		Animator* mSkillAnimator;
		std::unordered_map<std::wstring, std::unique_ptr<Skill>> mSkill;
		bool mActive;
		std::wstring mActiveName;
	};
}