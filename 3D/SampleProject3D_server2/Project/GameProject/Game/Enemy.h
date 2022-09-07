#pragma once
#include "../Base/Base.h"
class Enemy :public Base {
private:
	int m_cnt;
public:
	Enemy(const CVector3D& pos, float rot);
	//ˆÚ“®‚Ìˆ—
	void Update();
	//•`‰æ‚Ìˆ—
	void Draw();
	//“–‚½‚è”»’èŒŸØ
	void HitCheck(Base* b);
};