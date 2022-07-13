#include <stdio.h>
#include "DeffenceAction.h"
#include "Enemy.h"

ActionBase::STATE DeffenceAction::Run(Enemy *enemy)
{
	enemy->Deffence();

	return ActionBase::STATE::COMPLETE;
}