#include "CharaBase.h"

bool CharaBase::IsHpPercentOver(float check_percent)
{
	float percent = m_Hp / m_MaxHp;

	if (percent * 100.0f >= check_percent)
	{
		return true;
	}

	return false;
}

bool CharaBase::IsMpPercentOver(float check_percent)
{
	float percent = m_Mp / m_MaxMp;

	if (percent * 100.0f >= check_percent)
	{
		return true;
	}

	return false;
}

bool CharaBase::IsDie()
{
	return m_Hp <= 0.0f ? true : false;
}

