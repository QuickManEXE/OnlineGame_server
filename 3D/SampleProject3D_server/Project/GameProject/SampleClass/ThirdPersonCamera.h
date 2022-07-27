#pragma once

#include "CameraBase.h"
class ThirdPersonCamera:public CameraBase {
	//�J�����̈ʒu
	CVector3D m_cam_pos;
	//�J�����̉�]�l
	CVector3D m_cam_rot;
	//�J�����̋���
	float m_dist;
	//��������I�u�W�F�N�g
	Base* mp_target;
public:
	//�R���X�g���N�^
	ThirdPersonCamera(Base* target);
	//�J�����X�V
	void UpdateCamera(Camera* c);

};

/*
#include "../Base/Base.h"

class ThirdPersonCamera :public Base {
	//�J�����̈ʒu
	CVector3D m_cam_pos;
	//�J�����̉�]�l
	CVector3D m_cam_rot;
	//�J�����̋���
	float m_dist;
	//��������I�u�W�F�N�g
	Base* mp_target;
public:
	//�R���X�g���N�^
	ThirdPersonCamera(Base* target);
	//�J�����X�V
	void Update();

};
*/