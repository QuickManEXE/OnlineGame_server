#include "AntMan.h"
#include "../GID.h"
//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
//�@�@�@�@�@������pos(���W)��rot(��]�l)���󂯎��
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���N���X�iBase�j�֎�ނ̏���n��
AntMan::AntMan(const CVector3D& pos, float rot):Base(eId_Player) {
	//���W�̐ݒ�
	m_pos = pos;
	//��]�l�̐ݒ�
	m_rot.y = rot;
	//���a�̐ݒ�
	m_rad = 1.0f;
	//���f���̕���
	m_model_a3m = COPY_RESOURCE("Antman", CModelA3M);

}
//�X�V����
//Base::UpdateALL�֐����ŌĂ΂�Ă���
void AntMan::Update() {
	
	//�����L�[�̓��͕����x�N�g��
	CVector3D key_dir(0, 0, 0);

	//�J�����̕����x�N�g��
	CVector3D cam_dir = CCamera::GetCurrent()->GetDir();

	//���͉�]�l
	float key_ang = 0;
	//�J�����̉�]�l
	float cam_ang = atan2(cam_dir.x, cam_dir.z);


	const float move_speed = 1.0f;

	//�����L�[������͕����x�N�g����ݒ�
	if (CInput::GetState(0, CInput::eHold, CInput::eUp)) {
		key_dir.z = 1;
	}
	if (CInput::GetState(0, CInput::eHold, CInput::eDown)) {
		key_dir.z = -1;
	}
	if (CInput::GetState(0, CInput::eHold, CInput::eLeft)) {
		key_dir.x = 1;
	}
	if (CInput::GetState(0, CInput::eHold, CInput::eRight)) {
		key_dir.x = -1;
	}

	//�L�[���͂������
	if (key_dir.LengthSq() > 0) {
		//���͕���������͉�]�l���v�Z
		key_ang = atan2(key_dir.x, key_dir.z);
		//�J�����̉�]�l�Ɠ��͉�]�l����L�����N�^�[�̉�]�l������
		m_rot.y = cam_ang + key_ang;

		//�ړ�����
		CVector3D dir(sin(m_rot.y), 0, cos(m_rot.y));
		m_pos += dir * move_speed;

		m_model_a3m.ChangeAnimation(1);
	}
	else {
		m_model_a3m.ChangeAnimation(0);
	}
	//���[�V�����̍X�V
	m_model_a3m.UpdateAnimation();
}
//�`�揈��
//Base::DrawALL�֐����ŌĂ΂�Ă���
void AntMan::Draw() {
	//���̕\��
	//Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 1, 1));
	m_model_a3m.SetPos(m_pos);
	m_model_a3m.SetRot(m_rot);
	m_model_a3m.SetScale(0.25f, 0.25f, 0.25f);
	m_model_a3m.Render();
}
//�����蔻�菈��
//Base::CollisionALL�֐����őS�ẴI�u�W�F�N�g���m�̑g�ݍ��킹�ŌĂ΂�Ă���
//               �����ɏՓˌ��ؑΏۂ̃I�u�W�F�N�g(b)���󂯎��
void AntMan::HitCheck(Base* b) {
	//�Փˌ��ؑΏۂ̃I�u�W�F�N�g�̎�ނŕ���
	switch (int t = b->GetType()) {
	//
	case eId_Charactor:

		break;
	}
}

