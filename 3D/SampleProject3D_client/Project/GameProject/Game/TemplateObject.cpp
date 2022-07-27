#include "TemplateObject.h"
#include "../GID.h"
//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
//�@�@�@�@�@������pos(���W)��rot(��]�l)���󂯎��
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���N���X�iBase�j�֎�ނ̏���n��
TemplateObject::TemplateObject(const CVector3D& pos, float rot):Base(eId_Charactor) {
	//���W�̐ݒ�
	m_pos = pos;
	//��]�l�̐ݒ�
	m_rot.y = rot;
	//���a�̐ݒ�
	m_rad = 1.0f;

}
//�X�V����
//Base::UpdateALL�֐����ŌĂ΂�Ă���
void TemplateObject::Update() {
	
	//��]
	m_rot.y += DtoR(1.0f);

	//�O���������߂�
	CVector3D dir(sin(m_rot.y), 0,cos(m_rot.y));
	
	//�O�Ɉړ�
	m_pos += dir * 0.1f;

	//�{�^���T�i�X�y�[�X�L�[�j��������
	if (PUSH(CInput::eButton5)) {
		//�I�u�W�F�N�g�폜
		SetKill();
	}
}
//�`�揈��
//Base::DrawALL�֐����ŌĂ΂�Ă���
void TemplateObject::Draw() {
	//���̕\��
	Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 1, 1));
}
//�����蔻�菈��
//Base::CollisionALL�֐����őS�ẴI�u�W�F�N�g���m�̑g�ݍ��킹�ŌĂ΂�Ă���
//               �����ɏՓˌ��ؑΏۂ̃I�u�W�F�N�g(b)���󂯎��
void TemplateObject::HitCheck(Base* b) {
	//�Փˌ��ؑΏۂ̃I�u�W�F�N�g�̎�ނŕ���
	switch (int t = b->GetType()) {
	//
	case eId_Charactor:
		//���ł̏Փˌ���
		//if (CollisionSphere(b)) {
			//���g���폜
			//SetKill();
		//}
		break;
	}
}

