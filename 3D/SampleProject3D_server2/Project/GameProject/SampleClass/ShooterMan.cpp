#include "ShooterMan.h"
#include "../GID.h"
#include "CannonBall.h"
#include "Stage.h"
//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
//�@�@�@�@�@������pos(���W)��rot(��]�l)���󂯎��
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���N���X�iBase�j�֎�ނ̏���n��
ShooterMan::ShooterMan(const CVector3D& pos, float rot):Base(eId_Player) {
	//���W�̐ݒ�
	m_pos = pos;
	//��]�l�̐ݒ�
	m_rot.y = rot;
	//���a�̐ݒ�
	m_rad = 20.0f;
	//���f���̕���
	m_model_a3m = COPY_RESOURCE("Antman", CModelA3M);

	m_wepon_model = COPY_RESOURCE("Scar", CModelObj);

	m_vec = CVector3D(0, 0, 0);
}
//�X�V����
//Base::UpdateALL�֐����ŌĂ΂�Ă���
void ShooterMan::Update() {
	//�}�E�X����ŃL�����N�^�[����]----
	CVector2D mouse_vec = CInput::GetMouseVec();
	m_rot.y += mouse_vec.x * -0.01f;
	m_rot.x += mouse_vec.y * 0.01f;
	m_rot.x = min(DtoR(45), max(DtoR(-45), m_rot.x));

	//�����L�[�̓��͕����x�N�g��
	CVector3D key_dir(0, 0, 0);

	//���͉�]�l
	float key_ang = 0;


	const float move_speed = 4.0f;

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
		//�ړ����� ��]�s��~�ړ�����
		CVector3D dir = CMatrix::MRotationY(m_rot.y) * key_dir;
		m_pos += dir * move_speed;

		m_model_a3m.ChangeAnimation(1);
	}
	else {
		m_model_a3m.ChangeAnimation(0);
	}
	//���[�V�����̍X�V
	m_model_a3m.UpdateAnimation();



	//������
	m_vec.y -= GRAVITY;
	m_pos += m_vec;
	if (HOLD(CInput::eButton1)) m_vec.y =10;
	//���W�A��]�A�X�P�[���ݒ�
	m_model_a3m.SetPos(m_pos);
	m_model_a3m.SetRot(0, m_rot.y, 0);
	m_model_a3m.SetScale(0.5f, 0.5f, 0.5f);
	//�����̃{�[���͌����w��
	m_model_a3m.BindFrameMatrix(5, CMatrix::MRotation(m_rot));
	//�s��̍X�V
	m_model_a3m.UpdateMatrix();

	m_wepon_matrix = m_model_a3m.GetFrameMatrix(31) * CMatrix::MTranselate(-17.981f, -5.383f, 7.500) * CMatrix::MRotation(DtoR(90), 0, DtoR(-90));


	//���N���b�N�Œe����
	if (HOLD(CInput::eMouseL)) {
		static float speed = 20.0f;
		CMatrix hand_matrix = m_model_a3m.GetFrameMatrix(31);
		CMatrix rot_matrix = CMatrix::MRotation(m_rot);
		CVector3D pos = m_wepon_matrix * CVector4D(0, 0, 50, 1);
		CVector3D dir = rot_matrix.GetFront();
		Base::Add(new CannonBall(pos, dir * speed));
	}

	//���J�v�Z���̐ݒ�
	m_lineS = m_pos + CVector3D(0, 80, 0);
	m_lineE = m_pos + CVector3D(0, m_rad, 0);
}
//�`�揈��
//Base::DrawALL�֐����ŌĂ΂�Ă���
void ShooterMan::Draw() {
	//���̕\��
	//Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 1, 1));
	m_model_a3m.SetPos(m_pos);
	m_model_a3m.SetRot(0, m_rot.y, 0);
	m_model_a3m.SetScale(0.5f, 0.5f, 0.5f);
	m_model_a3m.BindFrameMatrix(5, CMatrix::MRotation(m_rot));
	m_model_a3m.Render();

	m_wepon_model.Render(m_wepon_matrix);
}
//�����蔻�菈��
//Base::CollisionALL�֐����őS�ẴI�u�W�F�N�g���m�̑g�ݍ��킹�ŌĂ΂�Ă���
//               �����ɏՓˌ��ؑΏۂ̃I�u�W�F�N�g(b)���󂯎��
void ShooterMan::HitCheck(Base* b) {
	//�Փˌ��ؑΏۂ̃I�u�W�F�N�g�̎�ނŕ���
	switch (int t = b->GetType()) {
		//
	case eId_Enemy:
		if (CollisionCapsule(b)) {
			CVector3D v = b->GetPos() - m_pos;
			float s = m_rad + b->GetRad() - v.Length();
			v.Normalize(); v.y = 0;
			b->MovePos(v * s);
		}

		break;
	case eId_Field:
		//��
		if (Stage* s = dynamic_cast<Stage*>(b)) {
			Base::CollisionModel(&m_pos, &m_vec, m_rad, s->GetCollisionModel());
		}
		break;
	}}

