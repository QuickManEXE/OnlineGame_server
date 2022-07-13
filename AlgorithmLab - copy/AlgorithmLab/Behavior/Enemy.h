#ifndef ENEMY_H_
#define ENMEY_H_

#include <vector>
#include "CharaBase.h"

class BehaviorTree;
class BehaviorData;
class NodeBase;

// 敵クラス
class Enemy : public CharaBase
{
public:
	Enemy(BehaviorTree *ai_tree, float max_hp, float max_mp, float attack, float deffence);

	// 実行
	void Run();
	// スキル使用
	void UseSkill();
	// 魔法使用
	void UseMagic();
	// 物理攻撃
	void PhysicsAttack();
	// 守備
	void Deffence();
	// ダメージ反映(デバッグ用)
	void ReceiveDamage(float damage);

private:
	BehaviorTree *m_AiTree;			// ビヘイビアツリー
	BehaviorData *m_BehaviorData;	// ビヘイビアデータ
	NodeBase *m_ActiveNode;			// 実行中ノード
};

#endif
