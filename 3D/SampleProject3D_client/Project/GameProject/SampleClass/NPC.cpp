#include "NPC.h"
#include "../GID.h"
#include "Stage.h"
//コンストラクタ　オブジェクト生成時に呼ばれる
//　　　　　引数にpos(座標)とrot(回転値)を受け取る
//　　　　　　　　　　　　　　　　　　　　基底クラス（Base）へ種類の情報を渡す
NPC::NPC(const CVector3D& pos, float rot):Base(eId_Enemy) {
	//座標の設定
	m_pos = pos;
	//回転値の設定
	m_rot.y = rot;
	//半径の設定
	m_rad = 20.0f;
	//モデルの複製
	m_model_a3m = COPY_RESOURCE("Antman", CModelA3M);
	m_vec = CVector3D(0, 0, 0);
}
//更新処理
//Base::UpdateALL関数内で呼ばれている
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

	//★落下
	m_vec.y -= GRAVITY;
	m_pos += m_vec;

	m_model_a3m.UpdateAnimation();

	//■カプセル
	m_lineS = m_pos + CVector3D(0, 80, 0);
	m_lineE = m_pos + CVector3D(0, m_rad, 0);


}
//描画処理
//Base::DrawALL関数内で呼ばれている
void NPC::Draw() {
	//球の表示
	//Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 1, 1));
	m_model_a3m.SetPos(m_pos);
	m_model_a3m.SetRot(m_rot);
	m_model_a3m.SetScale(0.5f, 0.5f, 0.5f);
	m_model_a3m.Render();
}
//当たり判定処理
//Base::CollisionALL関数内で全てのオブジェクト同士の組み合わせで呼ばれている
//               引数に衝突検証対象のオブジェクト(b)を受け取る
void NPC::HitCheck(Base* b) {
	//衝突検証対象のオブジェクトの種類で分岐
	switch (int t = b->GetType()) {
	//
	case eId_Charactor:

		break;
	//■弾との判定
	case eId_Player_Bullet:
		if (CollisionCapsule(b)) {
			SetKill();
		}
		break;
	case eId_Field:
		//★
		if (Stage* s = dynamic_cast<Stage*>(b)) {
			Base::CollisionModel(&m_pos, &m_vec, m_rad, s->GetCollisionModel());
		}
		break;

	}
}

