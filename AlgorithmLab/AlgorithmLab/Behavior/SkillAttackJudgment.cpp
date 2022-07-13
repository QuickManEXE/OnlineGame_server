#include "SkillAttackJudgment.h"
#include "Enemy.h"

bool SkillAttackJudgment::Judgment(Enemy *enemy)
{
	if (enemy->HasSkill())
	{
		return true;
	}

	return false;
}