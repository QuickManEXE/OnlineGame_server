#pragma once
#include "../Base/Base.h"
#include"../NetWorkObjectBase/NetWorkObjectBase.h"

class Bullet : public Base {
	float m_speed;
	int m_cnt;
public:
	//�R���X�g���N�^
	//�����@:���ˈʒu
	Bullet(const CVector3D& pos, float rot,float speed,int bullet_type);
	//�ړ��̏���
	void Update();
	//�`��̏���
	void Draw();

	//�����蔻�茟��
	void HitCheck(Base* b);
};