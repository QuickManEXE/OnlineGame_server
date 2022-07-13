#ifndef CHARA_BASE_H_
#define CHARA_BASE_H_

#include <vector>

// キャラ基底
class CharaBase
{
public:
	CharaBase(float max_hp, float max_mp, float attack, float deffence) :
		m_Hp(max_hp),
		m_MaxHp(max_hp),
		m_Mp(max_mp),
		m_MaxMp(max_mp),
		m_Attack(attack),
		m_Deffence(deffence)
	{
	}

	// HPゲッター
	float GetHp()
	{
		return m_Hp;
	}

	// MPゲッター
	float GetMp()
	{
		return m_Mp;
	}

	// 攻撃力ゲッター
	float GetAttack()
	{
		return m_Attack;
	}

	// 防御力ゲッター
	float GetDeffence()
	{
		return m_Deffence;
	}

	// スキルを所持しているか
	bool HasSkill()
	{
		if (m_SkillList.size() > 0)
		{
			return true;
		}
		return false;
	}

	// 魔法を所持しているか
	bool HasMagic()
	{
		if (m_MagicList.size() > 0)
		{
			return true;
		}
		return false;
	}

	// HPオーバー判定
	bool IsHpPercentOver(float check_percent);

	// MPオーバー判定
	bool IsMpPercentOver(float check_percent);

	// 死亡判定
	bool IsDie();

protected:
	std::vector<int> m_SkillList;	// スキルリスト
	std::vector<int> m_MagicList;	// 魔法リスト

	float m_Hp;			// HP
	float m_MaxHp;		// 最大HP
	float m_Mp;			// MP
	float m_MaxMp;		// 最大MP
	float m_Attack;		// 攻撃力
	float m_Deffence;	// 防御力
};

#endif
