#include "ThirdPersonCamera.h"
#include "../GID.h"

//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
ThirdPersonCamera::ThirdPersonCamera(Base* target):m_dist(200) {
	mp_target = target;

}
//�J��������
void ThirdPersonCamera::UpdateCamera(Camera* c) {

	CVector3D at = mp_target->GetPos();
	//�����_�@��Ɏ��_���ړ�����
	CVector3D cam_at = at + CVector3D(0, 80, 0);
	//�}�E�X���삩��J��������]----
	//�}�E�X�ړ���
	CVector2D mouse_vec = CInput::GetMouseVec();
	m_cam_rot.y += mouse_vec.x * -0.01f;
	m_cam_rot.x += mouse_vec.y * 0.01f;
	m_cam_rot.x = min(DtoR(45), max(DtoR(-10), m_cam_rot.x));

	//�J�����̋�����ύX
	m_dist += CInput::GetMouseWheel() * 5.0f;
	//�J�����̈ʒu���v�Z
	CVector3D dir = CMatrix::MRotation(m_cam_rot).GetFront();
	//CVector3D dir(sin(cam_rot.y),0,cos(cam_rot.y));
	m_cam_pos = cam_at + dir * -m_dist;
	//�J�����{�̂փf�[�^��n��
	c->SetParam(m_cam_pos, at, CVector3D(0, 1, 0));
}

/*
//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
ThirdPersonCamera::ThirdPersonCamera(Base* target) :Base(eId_Camera),m_dist(200) {
	mp_target = target;

}
//�J��������
void ThirdPersonCamera::Update() {
	//�������
	CVector3D at = mp_target->GetPos();
	//�����_�@��Ɏ��_���ړ�����
	CVector3D cam_at = at + CVector3D(0, 80, 0);
	//�}�E�X���삩��J��������]----
	//�}�E�X�ړ���
	CVector2D mouse_vec = CInput::GetMouseVec();
	m_cam_rot.y += mouse_vec.x * -0.01f;
	m_cam_rot.x += mouse_vec.y * 0.01f;
	//if���ɂ�鐧��
	//if (cam_rot.x > DtoR(45)) cam_rot.x = DtoR(45);
	//if (cam_rot.x < DtoR(-10)) cam_rot.x = DtoR(-10);
	//min,max�֐��ɂ�鐧��
	//cam_rot.x = min(DtoR(45), cam_rot.x);
	//cam_rot.x = max(DtoR(-10), cam_rot.x);
	//clamp�֐��Ɠ����̏���
	m_cam_rot.x = min(DtoR(45), max(DtoR(-10), m_cam_rot.x));

	//�J�����̋�����ύX
	m_dist += CInput::GetMouseWheel() * 5.0f;
	//�J�����̈ʒu���v�Z
	CVector3D dir = CMatrix::MRotation(m_cam_rot).GetFront();
	//CVector3D dir(sin(cam_rot.y),0,cos(cam_rot.y));
	m_cam_pos = cam_at + dir * -m_dist;
	//�ʒu�ƒ����_��ݒ肵�ăJ�������X�V
	CCamera::GetCurrent()->LookAt(m_cam_pos, cam_at, CVector3D(0, 1, 0));
}
*/