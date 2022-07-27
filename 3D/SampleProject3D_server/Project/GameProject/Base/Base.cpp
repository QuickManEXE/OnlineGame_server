#include "Base.h"
std::list<Base*> Base::m_list;
Base::Base(int type) :m_kill(false), m_type(type) {
}
Base::~Base() {

}
void Base::SetKill() {
	//�폜�t���OON
	m_kill = true;
}
void Base::Update() {
}
void Base::Draw() {
}
void Base::HitCheck(Base* b) {
}

//�����f���̂Ƃ̏Փ˔���
void Base::CollisionModel(CVector3D* pos, CVector3D* vec, float rad, CModel* model) {
	//���f���Ƃ̔���(��)
	//�Փ˃f�[�^�i�[�p
	CCollTriangle out[256];
	//�����߂���
	CVector3D v(0, 0, 0);
	//���ƃ��f���Ƃ̏Փ�
	//�G���[���o����c�P�E�ǂݍ���łȂ��Ȃ��@�Q�E�R���W������ݒ肵�Ă��Ȃ�
	int cnt = model->CollisionSphere(out, *pos + CVector3D(0, rad, 0), rad, 250);
	//�ڐG�����ʂ̐��J��Ԃ�
	for (int i = 0; i < cnt; i++) {
		//�ڐG�����ʂ��΂߂���������Ă�����n��
		if (out[i].m_normal.y > 0.5f) {
			//�d�͗������x��0�ɖ߂�
			if (vec->y < 0) {
				vec->y = 0;
			}
		}
		//�ڐG�����ʂ̕����ցA�߂荞�񂾕������߂�
		CVector3D nv = out[i].m_normal * (rad - out[i].m_dist);
		//�ł��傫�Ȉړ��ʂ����߂�
		v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
		v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
		v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
	}
	//�����߂�
	*pos += v;
	printf("c = %d\n", cnt);

}
bool Base::CollisionCapsuleToSphere(Base* b)
{
	return CCollision::CollisionCapsuleShpere(m_lineS, m_lineE, m_rad, b->m_pos, b->m_rad);
}
bool Base::CollisionSphereToCapsule(Base* b)
{
	return CCollision::CollisionCapsuleShpere(b->m_lineS, b->m_lineE, b->m_rad, m_pos, m_rad);
}
bool Base::CollisionCapsule(Base* b)
{
	
	return CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->m_lineS, b->m_lineE, b->m_rad);
}
bool Base::CollisionSphere(Base* b) {
	//���̏Փ˔���̎���

	return CCollision::CollisionShpere(m_pos,m_rad,b->m_pos,b->m_rad);
}

void Base::KillALL() {
	auto itr = m_list.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_list.end()) {
		(*itr)->SetKill();
		itr++;
	}

}
void Base::CheckKillALL() {
	auto itr = m_list.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_list.end()) {
		//�폜�`�F�b�N
		if ((*itr)->m_kill) {
			//�폜
			delete* itr;
			//���X�g���珜�O����
			//���̃I�u�W�F�N�g���󂯎��
			itr = m_list.erase(itr);
		}
		else {
			//���̃I�u�W�F�N�g
			itr++;
		}
	}

}
void Base::UpdateALL() {
	//�C�e���[�^
	//http://vivi.dyndns.org/tech/cpp/iterator.html
	//�擪�̃I�u�W�F�N�g
	//std::list<Base*>::iterator itr = m_list.begin();
	auto itr = m_list.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_list.end()) {
		//�X�V
		(*itr)->Update();
		//���̃I�u�W�F�N�g
		itr++;
	}
}
void Base::DrawALL() {
	auto itr = m_list.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_list.end()) {
		//�X�V
		(*itr)->Draw();
		//���̃I�u�W�F�N�g
		itr++;
	}

}

void Base::HitCheckALL() {
	auto itr = m_list.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_list.end()) {
		auto ct = itr;
		ct++;
		while (ct != m_list.end()) {
			(*itr)->HitCheck(*ct);
			(*ct)->HitCheck(*itr);
			//���̃I�u�W�F�N�g
			ct++;
		}
		//���̃I�u�W�F�N�g
		itr++;
	}

}

void Base::Add(Base * b) {
	//
	auto itr = m_list.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_list.end()) {
		if ((*itr)->GetType() > b->GetType()) {
			m_list.insert(itr, b);
			return;
		}
		//���̃I�u�W�F�N�g
		itr++;
	}
	m_list.push_back(b);

}



Base* Base::FindObject(int type) {
	//�擪���疖���܂ŌJ��Ԃ�
	for (auto it = m_list.begin(); it != m_list.end(); ++it) {
		//�I�u�W�F�N�g��type��������type�ƈ�v����΁@���̃I�u�W�F�N�g��Ԃ�
		if ((*it)->GetType() == type) return (*it);
	}
	return nullptr;
}



