#include "CannonBall.h"
CannonBall::CannonBall(const CVector3D& pos, const CVector3D& vec) :
	Base(eId_Player_Bullet),
	m_vec(vec), m_cnt(0){
	m_pos = pos;


}
CannonBall::~CannonBall() {

}
void CannonBall::Update() {

	//Å°ÉJÉvÉZÉã
	m_lineS = m_pos;
	//óéâ∫
	m_vec.y -= GRAVITY;
	//à⁄ìÆ
	m_pos += m_vec;
	//180FÇ≈è¡ñ≈
	if (m_cnt++ >= 180) {
		SetKill();
	}
	//Å°
	m_lineE = m_pos;

}
void CannonBall::Draw() {
	Utility::DrawSphere(m_pos, 5.0f, CVector4D(0.2, 0.2, 0.2, 1));

}
