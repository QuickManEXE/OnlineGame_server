#pragma once
#include "../Base/Base.h"


class AntMan : public Base {
private:
	CModelA3M m_model_a3m;
public:
	//�R���X�g���N�^
	//�����@:���ˈʒu
	AntMan(const CVector3D& pos, float rot);
	//�ړ��̏���
	void Update();
	//�`��̏���
	void Draw();

	//�����蔻�茟��
	void HitCheck(Base* b);
};