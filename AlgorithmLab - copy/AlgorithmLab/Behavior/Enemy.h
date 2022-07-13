#ifndef ENEMY_H_
#define ENMEY_H_

#include <vector>
#include "CharaBase.h"

class BehaviorTree;
class BehaviorData;
class NodeBase;

// �G�N���X
class Enemy : public CharaBase
{
public:
	Enemy(BehaviorTree *ai_tree, float max_hp, float max_mp, float attack, float deffence);

	// ���s
	void Run();
	// �X�L���g�p
	void UseSkill();
	// ���@�g�p
	void UseMagic();
	// �����U��
	void PhysicsAttack();
	// ���
	void Deffence();
	// �_���[�W���f(�f�o�b�O�p)
	void ReceiveDamage(float damage);

private:
	BehaviorTree *m_AiTree;			// �r�w�C�r�A�c���[
	BehaviorData *m_BehaviorData;	// �r�w�C�r�A�f�[�^
	NodeBase *m_ActiveNode;			// ���s���m�[�h
};

#endif
