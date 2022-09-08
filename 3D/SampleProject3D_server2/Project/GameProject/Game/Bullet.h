#pragma once
#include "../Base/Base.h"
#include"../NetWorkObjectBase/NetWorkObjectBase.h"

class Bullet : public NetWorkObjectBase {
	float m_speed;
	int m_cnt;
public:
	//�R���X�g���N�^
	//�����@:���ˈʒu
	Bullet(const CVector3D& pos, float rot,float speed,int bullet_type, NetWorkObjectManager::ObjectDataForSocket* od);
	//�ړ��̏���
	void Update();
	void UpdateByOwner()override;
	//�`��̏���
	void Draw();

	//�����蔻�茟��
	void HitCheck(Base* b);
};