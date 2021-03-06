#include "CannonBall.h"
CannonBall::CannonBall(const CVector3D& pos, const CVector3D& vec) :
	Base(eId_Player_Bullet),
	m_vec(vec), m_cnt(0){
	m_pos = pos;


}
CannonBall::~CannonBall() {

}
void CannonBall::Update() {

	//■カプセル
	m_lineS = m_pos;
	//落下
	m_vec.y -= GRAVITY;
	//移動
	m_pos += m_vec;
	//180Fで消滅
	if (m_cnt++ >= 180) {
		SetKill();
	}
	//■
	m_lineE = m_pos;

}
void CannonBall::Draw() {
	Utility::DrawSphere(m_pos, 5.0f, CVector4D(0.2, 0.2, 0.2, 1));

}
