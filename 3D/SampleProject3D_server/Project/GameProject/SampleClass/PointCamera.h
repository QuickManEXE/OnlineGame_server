#pragma once
#include "CameraBase.h"

//�e�X�g�p��_�J����
class PointCamera:public CameraBase {
	CVector3D m_eye;
	CVector3D m_at;
	CVector3D m_up;
public:
	//�R���X�g���N�^
	//���_�A�����_,Up�x�N�g����ݒ肵�Ē�_�J�������쐬
	PointCamera(const CVector3D& eye, const CVector3D& at, const CVector3D& up);
	//�J�����X�V
	void UpdateCamera(Camera* c);

};