#include <stdio.h>
#include "SkillAction.h"
#include "Enemy.h"

ActionBase::STATE SkillAction::Run(Enemy *enemy)
{
	enemy->UseSkill();

	return ActionBase::STATE::COMPLETE;
}