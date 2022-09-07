#pragma once
#include "../Base/Base.h"


class NPC : public Base {
private:
	CModelA3M m_model_a3m;
	CVector3D m_vec;
public:
	//�R���X�g���N�^
	//�����@:���ˈʒu
	NPC(const CVector3D& pos, float rot);
	//�ړ��̏���
	void Update();
	//�`��̏���
	void Draw();

	//�����蔻�茟��
	void HitCheck(Base* b);
};