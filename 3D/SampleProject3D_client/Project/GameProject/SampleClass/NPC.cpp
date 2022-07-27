#include "NPC.h"
#include "../GID.h"
#include "Stage.h"
//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
//�@�@�@�@�@������pos(���W)��rot(��]�l)���󂯎��
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���N���X�iBase�j�֎�ނ̏���n��
NPC::NPC(const CVector3D& pos, float rot):Base(eId_Enemy) {
	//���W�̐ݒ�
	m_pos = pos;
	//��]�l�̐ݒ�
	m_rot.y = rot;
	//���a�̐ݒ�
	m_rad = 20.0f;
	//���f���̕���
	m_model_a3m = COPY_RESOURCE("Antman", CModelA3M);
	m_vec = CVector3D(0, 0, 0);
}
//�X�V����
//Base::UpdateALL�֐����ŌĂ΂�Ă���
void NPC::Update() {
	Base* p = Base::FindObject(eId_Player);

	const float speed = 2.0f;
	const float view_length = 400;
	const float view_ang = DtoR(45);

	CVector3D vec = p->GetPos() - m_pos;
	CVector3D dirNP = vec.GetNormalize();
	float length = vec.Length();

	CVector3D dir(sin(m_rot.y),0,cos(m_rot.y));
	float d = CVector3D::Dot(dir, dirNP);
	d = max(-1.0f, min(1.0, d));
	float a = acos(d);
	if (a < view_ang && length < view_length) {

		m_rot.y = atan2(vec.x, vec.z);
		m_pos += dir * speed;
		m_model_a3m.ChangeAnimation(1);
	}
	else {
		m_model_a3m.ChangeAnimation(0);
	}

	//������
	m_vec.y -= GRAVITY;
	m_pos += m_vec;

	m_model_a3m.UpdateAnimation();

	//���J�v�Z��
	m_lineS = m_pos + CVector3D(0, 80, 0);
	m_lineE = m_pos + CVector3D(0, m_rad, 0);


}
//�`�揈��
//Base::DrawALL�֐����ŌĂ΂�Ă���
void NPC::Draw() {
	//���̕\��
	//Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 1, 1));
	m_model_a3m.SetPos(m_pos);
	m_model_a3m.SetRot(m_rot);
	m_model_a3m.SetScale(0.5f, 0.5f, 0.5f);
	m_model_a3m.Render();
}
//�����蔻�菈��
//Base::CollisionALL�֐����őS�ẴI�u�W�F�N�g���m�̑g�ݍ��킹�ŌĂ΂�Ă���
//               �����ɏՓˌ��ؑΏۂ̃I�u�W�F�N�g(b)���󂯎��
void NPC::HitCheck(Base* b) {
	//�Փˌ��ؑΏۂ̃I�u�W�F�N�g�̎�ނŕ���
	switch (int t = b->GetType()) {
	//
	case eId_Charactor:

		break;
	//���e�Ƃ̔���
	case eId_Player_Bullet:
		if (CollisionCapsule(b)) {
			SetKill();
		}
		break;
	case eId_Field:
		//��
		if (Stage* s = dynamic_cast<Stage*>(b)) {
			Base::CollisionModel(&m_pos, &m_vec, m_rad, s->GetCollisionModel());
		}
		break;

	}
}

