#include "Player.h"
#include "Bullet.h"

//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
//�@�@�@�@�@������pos(���W)���󂯎��
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@���N���X�iBase�j�֎�ނ̏���n��
Player::Player(const CVector3D& pos,NetWorkObjectManager::ObjectDataForSocket* od) : NetWorkObjectBase(eId_Player,od){
	//�ǂݍ��ݍς݂̉摜�𕡐�
	m_model = COPY_RESOURCE("Player", CModelObj);
	//m_model.SetScale(0.01f, 0.01f, 0.01f);
	//���S�ʒu��ݒ�i��]���ɉe���j
	//���W��ݒ�
	m_pos = pos;
	//���a��ݒ�
	m_rad = 1;
	m_vec = CVector3D(0, 0, 0);
}
//�X�V����
//Base::UpdateALL�֐����ŌĂ΂�Ă���
void Player::Update() {
	//�ړ����x�ݒ�
	const float speed = 0.012f;
	//�O���������߂�
	CVector3D dir = CVector3D(sin(m_rot.y),0,cos(m_rot.y));
	
	//��L�[�������Ă����
	if (HOLD(CInput::eUp))
		//�O�Ɉړ�
		m_vec += dir * speed;
	//���L�[�������Ă����
	if (HOLD(CInput::eLeft))
		//���ɉ�]
		m_rot.y += DtoR(2);
	//�E�L�[�������Ă����
	if (HOLD(CInput::eRight))
		//�E�ɉ�]
		m_rot.y += DtoR(-2);
	m_vec *= 0.94f;
	if (m_vec.Length() < speed/2) m_vec = CVector3D::zero;
	m_pos += m_vec;
	/*if (HOLD(CInput::eRight))
		m_vec.x -= speed;

	if (HOLD(CInput::eLeft))
		m_pos.x += speed;
		*/
	//�{�^��5��������

	if (GetObjectData()->key[CInput::eButton5] == 1) {

		//if (PUSH(CInput::eButton5))
		//�e�̐����ƃ��X�g�ւ̒ǉ�
		//					���g�̍��W�Ɖ�]��n��
		Base::Add(new Bullet(m_pos, m_rot.y,0.4f,eId_Player_Bullet));

	}

	

}
void Player::UpdateByOwner()
{

	CVector3D* m_pos = &GetObjectData()->pos;

	CVector3D* m_rot = &GetObjectData()->rot;

	CVector3D* m_vec = &GetObjectData()->vec;

	//�ړ����x�ݒ�
	const float speed = 0.012f;
	//�O���������߂�
	CVector3D dir = CVector3D(sin(m_rot->y), 0, cos(m_rot->y));

	//��L�[�������Ă����
	if (HOLD(CInput::eUp))
		//�O�Ɉړ�
		*m_vec += dir * speed;
	//���L�[�������Ă����
	if (HOLD(CInput::eLeft))
		//���ɉ�]
		m_rot->y += DtoR(2);
	//�E�L�[�������Ă����
	if (HOLD(CInput::eRight))
		//�E�ɉ�]
		m_rot->y += DtoR(-2);
	*m_vec *= 0.94f;
	if (m_vec->Length() < speed / 2) *m_vec = CVector3D::zero;
	*m_pos += *m_vec;
	/*if (HOLD(CInput::eRight))
		m_vec.x -= speed;

	if (HOLD(CInput::eLeft))
		m_pos.x += speed;
		*/
		//�{�^��5��������
	if (PUSH(CInput::eButton5))
		//�e�̐����ƃ��X�g�ւ̒ǉ�
		//					���g�̍��W�Ɖ�]��n��
		//Base::Add(new Bullet(*m_pos, m_rot->y, 0.4f, eId_Player_Bullet));
		GetObjectData()->key[CInput::eButton5] = 1;





}
//�`�揈��
//Base::DrawALL�֐����ŌĂ΂�Ă���
void Player::Draw() {


	CVector3D m_pos = GetObjectData()->pos;
	CVector3D m_rot = GetObjectData()->rot;

	//�\���ʒu�̐ݒ�
	m_model.SetPos(m_pos);
	//��]�l��ݒ�
	m_model.SetRot(m_rot);
	//�`��
	m_model.Render();

}
//�����蔻�菈��
//Base::CollisionALL�֐����őS�ẴI�u�W�F�N�g���m�̑g�ݍ��킹�ŌĂ΂�Ă���
//               �����ɏՓˌ��ؑΏۂ̃I�u�W�F�N�g(b)���󂯎��
void Player::HitCheck(Base* b) {
	//�Փˌ��ؑΏۂ̃I�u�W�F�N�g�̎�ނŕ���
	switch (b->GetType()) {
		//�G�̏ꍇ
	case eId_Enemy:
		//�~�ł̏Փˌ���
		{
			//�Q�_�Ԃ̃x�N�g�������߂�
			CVector3D v = b->GetPos()- m_pos;
			//�x�N�g���̒��������߂�
			//�i�Q�_�Ԃ̋�����������j
			float l = v.Length();
			//�Q�_�Ԃ̋������Q�̉~��
			//���a�ȉ��Ȃ�Γ������Ă���
			if (l <= m_rad + b->GetRad()) {
				CVector3D nv = v.GetNormalize();
				float s = m_rad + b->GetRad() - l;
				MovePos(-nv * s * 0.2);
				b->MovePos(nv * s * 0.8);
			}
 
		}
		break;
	case eId_Enemy_Bullet:
		//�~�ł̏Փˌ���
		if (CollisionSphere(b))
			//���g���폜
			SetKill();
		break;
	}
}

