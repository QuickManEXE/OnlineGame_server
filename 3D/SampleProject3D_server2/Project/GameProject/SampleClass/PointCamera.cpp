#include "PointCamera.h"
#include "../GID.h"
//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
PointCamera::PointCamera(const CVector3D& eye, const CVector3D& at, const CVector3D& up):
m_eye(eye),m_at(at),m_up(up){


}
//�J��������
void PointCamera::UpdateCamera(Camera* c) {

	//�J�����{�̂փf�[�^��n��
	c->SetParam(m_eye, m_at, m_up);
}