#ifndef SKILL_ACTION_H_
#define SKILL_ACTION_H_

#include "ActionBase.h"

// ÉXÉLÉãçsìÆ
class SkillAction : public ActionBase
{
public:
	static SkillAction *GetInstance()
	{
		static SkillAction instance;
		return &instance;
	}

	virtual STATE Run(Enemy *enemy);
};

#endif
