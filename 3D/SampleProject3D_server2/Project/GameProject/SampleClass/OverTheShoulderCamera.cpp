#include "OverTheShoulderCamera.h"
#include "../GID.h"

//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
OverTheShoulderCamera::OverTheShoulderCamera(Base* target) {
	mp_target = target;

}
//�J��������
void OverTheShoulderCamera::UpdateCamera(Camera* c) {
	CVector3D pos = mp_target->GetPos();
	CVector3D rot = mp_target->GetRot();


	CMatrix m = CMatrix::MTranselate(pos) * CMatrix::MTranselate(CVector3D(0, 80, 0)) * CMatrix::MRotation(rot) * CMatrix::MTranselate(CVector3D(-40, 0, -100));

	//�J�����{�̂փf�[�^��n��
	c->SetParam(m.GetPosition(), m.GetPosition() + m.GetFront(), m.GetUp());
}
/*
//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
OverTheShoulderCamera::OverTheShoulderCamera(Base* target) :Base(eId_Camera) {
	mp_target = target;

}
//�J��������
void OverTheShoulderCamera::Update() {
	CVector3D pos = mp_target->GetPos();
	CVector3D rot = mp_target->GetRot();


	CMatrix m = CMatrix::MTranselate(pos) * CMatrix::MTranselate(CVector3D(0, 80, 0)) * CMatrix::MRotation(rot) * CMatrix::MTranselate(CVector3D(-40, 0, -100));

	//���_�A�����_�ւƕϊ�
	CCamera::GetCurrent()->LookAt(m.GetPosition(), m.GetPosition() + m.GetFront(), m.GetUp());

}
*/
