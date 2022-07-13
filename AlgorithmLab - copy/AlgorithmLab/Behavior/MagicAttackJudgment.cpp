#include "MagicAttackJudgment.h"
#include "Enemy.h"

bool MagicAttackJudgment::Judgment(Enemy *enemy)
{
	if (enemy->HasMagic() &&
		enemy->IsMpPercentOver(50.0f))
	{
		return true;
	}

	return false;
}