#pragma once
#include "../Base/Base.h"
#include "CameraBase.h"

class Stage : public Base {
private:
	//�X�^�e�B�b�N���b�V�����f��
	//CModelObj m_model;
	//�t�B�[���h���f��
	//CModelField* m_field;
	//�����蔻��p���f��
	CModelObj m_model_collision;



public:
	//�R���X�g���N�^
	//�����@:���ˈʒu
	Stage();
	//�ړ��̏���
	void Update();
	//�`��̏���
	void Draw();
	//�Փ˔���p���f���̎擾
	CModel* GetCollisionModel();
};