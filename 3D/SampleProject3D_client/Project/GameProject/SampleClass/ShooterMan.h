#pragma once
#include "../Base/Base.h"


class ShooterMan : public Base {
private:
	CModelA3M m_model_a3m;
	CMatrix m_wepon_matrix;
	CModelObj m_wepon_model;
	//��
	CVector3D m_vec;
public:
	//�R���X�g���N�^
	//�����@:���ˈʒu
	ShooterMan(const CVector3D& pos, float rot);
	//�ړ��̏���
	void Update();
	//�`��̏���
	void Draw();

	//�����蔻�茟��
	void HitCheck(Base* b);
};