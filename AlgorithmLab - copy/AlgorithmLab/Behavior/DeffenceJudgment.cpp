#include "DeffenceJudgment.h"
#include "Enemy.h"

bool DeffenceJudgment::Judgment(Enemy *enemy)
{
	if (enemy->IsHpPercentOver(50.0f) == false)
	{
		int random = rand() % 100;

		if (random <= 40)
		{
			return true;
		}
	}

	return false;
}
