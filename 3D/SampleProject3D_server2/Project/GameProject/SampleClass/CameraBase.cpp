#include "CameraBase.h"
#include "PointCamera.h"
#include "ThirdPersonCamera.h"
#include "OverTheShoulderCamera.h"
#include "../GID.h"


//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
//�@�@�@�@�@������pos(���W)��rot(��]�l)���󂯎��
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���N���X�iBase�j�֎�ނ̏���n��
Camera::Camera():Base(eId_Camera),m_t(1.0f){
	//�������̎�ނ̃J�����𐶐�
	mp_camera[0] = new OverTheShoulderCamera(Base::FindObject(eId_Player));
	mp_camera[1] = new ThirdPersonCamera(Base::FindObject(eId_Player));
	//�؂�ւ��e�X�g�p��_�J����
	mp_camera[2] = new PointCamera(CVector3D(0,200,200),CVector3D(100,0,0),CVector3D(0,1,0));
	mp_curret = mp_camera[0];

}

void Camera::SetParam(const CVector3D& eye, const CVector3D& at, const CVector3D& up)
{
	m_new_eye = eye;
	m_new_at = at;
	m_new_up = up;
}

void Camera::Update()
{
	//�J�����؂�ւ��e�X�g
	if (PUSH(CInput::eMouseR)) {
		static int idx = 0;
		idx = (idx + 1) % 3;
		ChangeCamera(idx);
	}
	//��ԌW�����ő�1.0f�܂ő���
	m_t = min(1.0f, m_t + 0.01f);
	//��Ԃ��Ȃ���X�V
	m_eye = m_eye * (1 - m_t) + m_new_eye * m_t;
	m_at = m_at * (1 - m_t) + m_new_at * m_t;
	m_up = m_up * (1 - m_t) + m_new_up * m_t;
	//���ݎg�p���̃J�����ōX�V
	if (mp_curret) mp_curret->UpdateCamera(this);

}
void Camera::Draw()
{

	//�ʒu�ƒ����_��ݒ肵�ăJ�������X�V
	CCamera::GetCurrent()->LookAt(m_eye, m_at, m_up);
}
void Camera::ChangeCamera(CameraBase* c)
{
	mp_curret = c;
	//�؂�ւ����ɂ͕�ԌW����0����X�^�[�g
	m_t = 0.0f;
}
void Camera::ChangeCamera(int i)
{
	mp_curret = mp_camera[i];
	//�؂�ւ����ɂ͕�ԌW����0����X�^�[�g
	m_t = 0.0f;
}
