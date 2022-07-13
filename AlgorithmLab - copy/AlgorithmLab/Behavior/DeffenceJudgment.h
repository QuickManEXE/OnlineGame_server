#ifndef DEFFENCE_JUDGMENT_H_
#define DEFFENCE_JUDGMENT_H_

#include "ExecJudgmentBase.h"

// ç”õÀs”»’è
class DeffenceJudgment : public ExecJudgmentBase
{
public:
	static DeffenceJudgment *GetInstance()
	{
		static DeffenceJudgment instance;
		return &instance;
	}

	virtual bool Judgment(Enemy *enemy);
};

#endif
