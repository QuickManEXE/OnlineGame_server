#pragma once
#include "../Base/Base.h"
class Enemy :public Base {
private:
	int m_cnt;
public:
	Enemy(const CVector3D& pos, float rot);
	//�ړ��̏���
	void Update();
	//�`��̏���
	void Draw();
	//�����蔻�茟��
	void HitCheck(Base* b);
};