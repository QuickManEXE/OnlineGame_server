#pragma once
#include "../Base/Base.h"


class TemplateObject : public Base {

public:
	//�R���X�g���N�^
	//�����@:���ˈʒu
	TemplateObject(const CVector3D& pos, float rot);
	//�ړ��̏���
	void Update();
	//�`��̏���
	void Draw();

	//�����蔻�茟��
	void HitCheck(Base* b);
};