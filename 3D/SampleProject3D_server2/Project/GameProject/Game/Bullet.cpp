#include "Bullet.h"
#include "../GID.h"
//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
//�@�@�@�@�@������pos(���W)��rot(��]�l)���󂯎��
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���N���X�iBase�j�֎�ނ̏���n��
Bullet::Bullet(const CVector3D& pos, float rot,float speed,int bullet_type, 
	NetWorkObjectManager::ObjectDataForSocket* od) : NetWorkObjectBase(bullet_type,od) {
	//���W�̐ݒ�
	m_pos = pos;
	//��]�l�̐ݒ�
	m_rot.y = rot;
	//���a�̐ݒ�
	m_rad = 0.2f;
	m_speed = speed;
	m_cnt = 0;
}
//�X�V����
//Base::UpdateALL�֐����ŌĂ΂�Ă���
void Bullet::Update() {
	//�ړ����x�ݒ�
	//�O���������߂�
	CVector3D dir(sin(m_rot.y), 0,cos(m_rot.y));
	//�O�Ɉړ�
	m_pos += dir * m_speed;
	if (m_cnt++ > 60*10) SetKill();

}

void Bullet::UpdateByOwner()
{
	//�ړ����x�ݒ�
	//�O���������߂�
	CVector3D dir(sin(m_rot.y), 0, cos(m_rot.y));
	//�O�Ɉړ�
	m_pos += dir * m_speed;
	if (m_cnt++ > 60 * 10) SetKill();
}

//�`�揈��
//Base::DrawALL�֐����ŌĂ΂�Ă���
void Bullet::Draw() {
	//�~�̕\��
	if(m_type == eId_Player_Bullet) 
		Utility::DrawSphere(m_pos, m_rad, CVector4D(0, 1, 0, 1));
	else
		Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 1, 1));
}
//�����蔻�菈��
//Base::CollisionALL�֐����őS�ẴI�u�W�F�N�g���m�̑g�ݍ��킹�ŌĂ΂�Ă���
//               �����ɏՓˌ��ؑΏۂ̃I�u�W�F�N�g(b)���󂯎��
void Bullet::HitCheck(Base* b) {
	//�Փˌ��ؑΏۂ̃I�u�W�F�N�g�̎�ނŕ���
	switch (int t = b->GetType()) {
	//�G�̏ꍇ
	case eId_Enemy:
	case eId_Player:
		//�~�ł̏Փˌ���
		if ( ((t == eId_Player && m_type == eId_Enemy_Bullet)  || (t == eId_Enemy && m_type == eId_Player_Bullet)) && CollisionSphere(b))
			//���g���폜
			SetKill();
		break;
	}
}

