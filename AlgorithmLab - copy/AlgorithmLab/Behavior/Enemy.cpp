#include <stdio.h>
#include "Enemy.h"
#include "BehaviorData.h"
#include "NodeBase.h"

Enemy::Enemy(BehaviorTree *ai_tree, float max_hp, float max_mp, float attack, float deffence) :
		m_AiTree(ai_tree),
		m_BehaviorData(NULL),
		m_ActiveNode(NULL),
		CharaBase(max_hp, max_mp, attack, deffence)
{
	m_BehaviorData = new BehaviorData();

	m_SkillList.push_back(1);
	m_MagicList.push_back(1);
}

void Enemy::Run()
{
	if (m_ActiveNode == NULL)
	{
		m_ActiveNode = m_AiTree->Inference(this, m_BehaviorData);
	}

	if (m_ActiveNode != NULL)
	{
		m_ActiveNode = m_AiTree->Run(this, m_ActiveNode, m_BehaviorData);
	}
}

void Enemy::ReceiveDamage(float damage)
{
	m_Hp -= damage;
}

void Enemy::PhysicsAttack()
{
	printf("�����U��\n");
}

void Enemy::Deffence()
{
	printf("���\n");
}

void Enemy::UseSkill()
{
	printf("�X�L���g�p\n");
}

void Enemy::UseMagic()
{
	printf("���@�g�p\n");
}
