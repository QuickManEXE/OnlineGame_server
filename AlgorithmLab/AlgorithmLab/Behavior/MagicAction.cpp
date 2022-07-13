#include "MagicAction.h"
#include "Enemy.h"

ActionBase::STATE MagicAction::Run(Enemy *enemy)
{
	enemy->UseMagic();

	return ActionBase::STATE::COMPLETE;
}