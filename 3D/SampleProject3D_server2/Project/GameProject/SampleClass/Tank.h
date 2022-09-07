#pragma once
#include "../Base/Base.h"
#include "CameraBase.h"

class Tank : public Base,public CameraBase {
private:
	enum {
		eBottom,	//�ԗ�����
		eTop,		//�C������
		eCannon,	//��C����
		ePartsMax,
	};
	//�X�^�e�B�b�N���b�V�����f��
	CModelObj m_model[ePartsMax];

	//��Ԃ̊e�p�[�c�̍s��
	CMatrix m_matrix[ePartsMax];

	//�ړ���
	CVector3D m_move_vec;
	//��]��
	CVector3D m_rot_vec;

	//��Ԃ̊e�p�[�c�̍��W
	CVector3D m_tank_pos[ePartsMax] = {
		CVector3D(0, 0, 0),
		CVector3D(0, 2.95f, 0),
		CVector3D(0, 0.66f, 0)
	};
	//��Ԃ̊e�p�[�c�̉�]�l
	CVector3D m_tank_rot[ePartsMax] = {
		CVector3D(0, 0, 0),
		CVector3D(0, 0, 0),
		CVector3D(0, 0, 0)
	};

public:
	//�R���X�g���N�^
	//�����@:���ˈʒu
	Tank(const CVector3D& pos, float rot);
	//�ړ��̏���
	void Update();
	//�`��̏���
	void Draw();

	//�����蔻�茟��
	void HitCheck(Base* b);


	//CameraBase���
	void UpdateCamera(Camera* c);
};