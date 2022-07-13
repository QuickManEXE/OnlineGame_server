#ifndef SKILL_ATTACK_JUDGMENT_H_
#define SKILL_ATTACK_JUDGMENT_H_

#include "ExecJudgmentBase.h"

class Enemy;

// ƒXƒLƒ‹”»’è
class SkillAttackJudgment : public ExecJudgmentBase
{
public:
	static SkillAttackJudgment *GetInstance()
	{
		static SkillAttackJudgment m_Instance;
		return &m_Instance;
	}

	virtual bool Judgment(Enemy *enemy);
};

#endif
