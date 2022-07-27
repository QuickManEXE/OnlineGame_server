#pragma once
#include "../Base/Base.h"
class Player : public Base{
private:
	CVector3D m_vec;
public:
	Player(const CVector3D& pos);
	void Update();
	void Draw();
	void HitCheck(Base* b);
};