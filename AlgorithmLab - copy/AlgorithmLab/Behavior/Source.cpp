#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BehaviorTree.h"
#include "AttackJudgment.h"
#include "MagicAttackJudgment.h"
#include "SkillAttackJudgment.h"
#include "DeffenceJudgment.h"
#include "PhysicsAction.h"
#include "DeffenceAction.h"
#include "MagicAction.h"
#include "SkillAction.h"
#include "Enemy.h"

void main(void)
{
	srand((unsigned)time(NULL));

	BehaviorTree behavior;
	behavior.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	behavior.AddNode("Root", "Attack", 1, BehaviorTree::SELECT_RULE::SEQUENTIAL_LOOPING, AttackJudgment::GetInstance(), NULL);
	behavior.AddNode("Root", "Deffence", 2, BehaviorTree::SELECT_RULE::NON, DeffenceJudgment::GetInstance(), DeffenceAction::GetInstance());
	behavior.AddNode("Attack", "PhysicsAttack", 1, BehaviorTree::SELECT_RULE::NON, NULL, PhysicsAction::GetInstance());
	behavior.AddNode("Attack", "MagicAttack", 2, BehaviorTree::SELECT_RULE::NON, MagicAttackJudgment::GetInstance(), MagicAction::GetInstance());
	behavior.AddNode("Attack", "SkillAttack", 3, BehaviorTree::SELECT_RULE::NON, SkillAttackJudgment::GetInstance(), SkillAction::GetInstance());

	behavior.PrintTree();

	Enemy enemy(&behavior, 100.0f, 100.0f, 30.0f, 10.0f);

	for (int i = 0; i < 100; i++)
	{
		if (enemy.IsDie() == false)
		{
			enemy.Run();
			enemy.ReceiveDamage(2.0f);
		}
	}

	getchar();
}
