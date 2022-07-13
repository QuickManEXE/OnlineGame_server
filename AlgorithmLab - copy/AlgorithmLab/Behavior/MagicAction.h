#ifndef MAGIC_ACTION_H_
#define MAGIC_ACTION_H_

#include "ActionBase.h"

// ñÇñ@çsìÆ
class MagicAction : public ActionBase
{
public:
	static MagicAction *GetInstance()
	{
		static MagicAction instance;
		return &instance;
	}

	virtual STATE Run(Enemy *enemy);
};

#endif
