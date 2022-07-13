#ifndef CHARA_BASE_H_
#define CHARA_BASE_H_

#include <vector>

// �L�������
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

	// HP�Q�b�^�[
	float GetHp()
	{
		return m_Hp;
	}

	// MP�Q�b�^�[
	float GetMp()
	{
		return m_Mp;
	}

	// �U���̓Q�b�^�[
	float GetAttack()
	{
		return m_Attack;
	}

	// �h��̓Q�b�^�[
	float GetDeffence()
	{
		return m_Deffence;
	}

	// �X�L�����������Ă��邩
	bool HasSkill()
	{
		if (m_SkillList.size() > 0)
		{
			return true;
		}
		return false;
	}

	// ���@���������Ă��邩
	bool HasMagic()
	{
		if (m_MagicList.size() > 0)
		{
			return true;
		}
		return false;
	}

	// HP�I�[�o�[����
	bool IsHpPercentOver(float check_percent);

	// MP�I�[�o�[����
	bool IsMpPercentOver(float check_percent);

	// ���S����
	bool IsDie();

protected:
	std::vector<int> m_SkillList;	// �X�L�����X�g
	std::vector<int> m_MagicList;	// ���@���X�g

	float m_Hp;			// HP
	float m_MaxHp;		// �ő�HP
	float m_Mp;			// MP
	float m_MaxMp;		// �ő�MP
	float m_Attack;		// �U����
	float m_Deffence;	// �h���
};

#endif
