#include "Tank.h"
#include "../GID.h"
#include "CannonBall.h"
//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
//�@�@�@�@�@������pos(���W)��rot(��]�l)���󂯎��
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���N���X�iBase�j�֎�ނ̏���n��
Tank::Tank(const CVector3D& pos, float rot):Base(eId_Player) {
	//���W�̐ݒ�
	m_pos = pos;
	//��]�l�̐ݒ�
	m_rot.y = rot;
	//���a�̐ݒ�
	m_rad = 1.0f;

	//ADD_RESOURCE("TankBottom", CModel::CreateModel("Wepon/Tank/Bottom.obj"));
	//ADD_RESOURCE("TankTop", CModel::CreateModel("Wepon/Tank/Top.obj"));
	//ADD_RESOURCE("TankGun", CModel::CreateModel("Wepon/Tank/Gun.obj"));

	//���f���̕���

	m_model[eBottom] = COPY_RESOURCE("TankBottom", CModelObj);
	m_model[eTop] = COPY_RESOURCE("TankTop", CModelObj);
	m_model[eCannon] = COPY_RESOURCE("TankGun", CModelObj);


}
//�X�V����
//Base::UpdateALL�֐����ŌĂ΂�Ă���
void Tank::Update() {


	//��]�����x
	const float rot_accel = 0.1f;
	//�ړ���
	const float move_accel = 0.1f;

	//�C���A��C�̉�]
	CVector2D mouse_vec = CInput::GetMouseVec();
	m_tank_rot[eTop].y += mouse_vec.x * -0.01f;
	m_tank_rot[eCannon].x += mouse_vec.y * 0.01f;


	//��]��������
	m_rot_vec *= 0.9f;
	//�ړ���������
	m_move_vec *= 0.9f;
	//��]����	
	m_tank_rot[eBottom] += m_rot_vec;
	//�ړ�����
	m_tank_pos[eBottom] += m_move_vec;

	//�ԗ��̉�]
	if (HOLD(CInput::eLeft)) {
		m_rot_vec.y += DtoR(rot_accel);
	}
	if (HOLD(CInput::eRight)) {
		m_rot_vec.y -= DtoR(rot_accel);
	}
	//�ړ�����
	if (HOLD(CInput::eUp)) {
		m_move_vec += m_matrix[eBottom].GetFront() * move_accel;
	}

	if (HOLD(CInput::eDown)) {
		m_move_vec -= m_matrix[eBottom].GetFront() * move_accel;
	}
	//-------------------------------------------------


	//��Ԃ̍s���ݒ肷��
	//�K�w�\�����\�z����@[�e�~�q]
	m_matrix[eBottom] = CMatrix::MTranselate(m_tank_pos[eBottom]) *
		CMatrix::MRotation(m_tank_rot[eBottom])*
		CMatrix::MScale(10,10,10);
	m_matrix[eTop] = m_matrix[eBottom] * CMatrix::MTranselate(0, 2.95f, 0) * CMatrix::MRotation(m_tank_rot[eTop]);
	m_matrix[eCannon] = m_matrix[eTop] * CMatrix::MTranselate(0, 0.66f, 0) * CMatrix::MRotation(m_tank_rot[eCannon]);



	//���N���b�N�Œe����
	if (PUSH(CInput::eMouseL)) {
		static float speed = 20.0f;
		CVector3D dir=m_matrix[eCannon].GetFront().GetNormalize();
		//CVector3D pos= m_matrix[eCannon].GetPosition();
		//CVector3D pos = 
			//�@��C�̍s��@�~�@�O��5���s�ړ�
		//	(m_matrix[eCannon] * CMatrix::MTranselate(0, 0, 5)).GetPosition();

		//�@��C�̍s��@�~�@�O��5�ړ�����x�N�g��
		CVector3D pos = m_matrix[eCannon] * CVector4D(0, 0, 5, 1);
		Base::Add(new CannonBall(pos, dir* speed));
	}

	//�ėp���W�Ɖ�]�l�ɃR�s�[
	//�i�J�����Ŏg�p���Ă��邽�߁j
	m_pos = m_tank_pos[eBottom];
	m_rot = m_tank_rot[eBottom];

}
//�`�揈��
//Base::DrawALL�֐����ŌĂ΂�Ă���
void Tank::Draw() {

	//�s����w�肵�ĕ`��
	for (int i = 0; i < ePartsMax; i++) {
		m_model[i].Render(m_matrix[i]);
	}

}
//�����蔻�菈��
//Base::CollisionALL�֐����őS�ẴI�u�W�F�N�g���m�̑g�ݍ��킹�ŌĂ΂�Ă���
//               �����ɏՓˌ��ؑΏۂ̃I�u�W�F�N�g(b)���󂯎��
void Tank::HitCheck(Base* b) {
	//�Փˌ��ؑΏۂ̃I�u�W�F�N�g�̎�ނŕ���
	switch (int t = b->GetType()) {
	//
	case eId_Charactor:

		break;
	}
}
//�J�����̍X�V
void Tank::UpdateCamera(Camera* c)
{
	CMatrix m = m_matrix[eTop] * CMatrix::MTranselate(0, 4.00, -15.0);
	//�J�����{�̂փf�[�^��n��
	c->SetParam(m.GetPosition(), m.GetPosition() + m.GetFront(), m.GetUp());

}

