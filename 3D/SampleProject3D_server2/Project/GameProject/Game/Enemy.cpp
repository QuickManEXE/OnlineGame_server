#include "../GID.h"
#include"Enemy.h"
#include"Bullet.h"

Enemy::Enemy(const CVector3D& pos,float rot) :Base(eId_Enemy) {
	m_pos = pos;
	m_rot.y = rot;
	m_rad = 1;
	m_cnt = Utility::Rand(0, 220);
	
}
void Enemy::Update() {
	float m_speed = 0.02f;
	//‘O•ûŒü‚ğ‹‚ß‚é
	CVector3D dir = CVector3D(sin(m_rot.y), 0, cos(m_rot.y));
	m_cnt++;
	if (m_cnt < 180) {
		m_pos += dir * m_speed;
	} else if (m_cnt<240) {
		if (Base * p = Base::FindObject(eId_Player)) {
			CVector3D v = p->GetPos() - m_pos;
			m_rot.y = atan2(v.x, v.z);
		}
	} else if (m_cnt < 320) {
		if (m_cnt % 30 == 0) {
			Base::Add(new Bullet(m_pos, m_rot.y,0.1f, eId_Enemy_Bullet));
		}
	} else if(m_cnt>380){
		m_cnt = 0;
	}
}
void Enemy::Draw() {
	Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 0, 1));
}
void Enemy::HitCheck(Base* b) {
	switch (b->GetType()) {
	case eId_Player_Bullet:
		if (CollisionSphere(b))
			SetKill();
		break;
	}
}
