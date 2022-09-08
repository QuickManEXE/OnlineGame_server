#include "Bullet.h"
#include "../GID.h"
//コンストラクタ　オブジェクト生成時に呼ばれる
//　　　　　引数にpos(座標)とrot(回転値)を受け取る
//　　　　　　　　　　　　　　　　　　　　基底クラス（Base）へ種類の情報を渡す
Bullet::Bullet(const CVector3D& pos, float rot,float speed,int bullet_type, 
	NetWorkObjectManager::ObjectDataForSocket* od) : NetWorkObjectBase(bullet_type,od) {
	//座標の設定
	m_pos = pos;
	//回転値の設定
	m_rot.y = rot;
	//半径の設定
	m_rad = 0.2f;
	m_speed = speed;
	m_cnt = 0;
}
//更新処理
//Base::UpdateALL関数内で呼ばれている
void Bullet::Update() {
	//移動速度設定
	//前方向を求める
	CVector3D dir(sin(m_rot.y), 0,cos(m_rot.y));
	//前に移動
	m_pos += dir * m_speed;
	if (m_cnt++ > 60*10) SetKill();

}

void Bullet::UpdateByOwner()
{
	//移動速度設定
	//前方向を求める
	CVector3D dir(sin(m_rot.y), 0, cos(m_rot.y));
	//前に移動
	m_pos += dir * m_speed;
	if (m_cnt++ > 60 * 10) SetKill();
}

//描画処理
//Base::DrawALL関数内で呼ばれている
void Bullet::Draw() {
	//円の表示
	if(m_type == eId_Player_Bullet) 
		Utility::DrawSphere(m_pos, m_rad, CVector4D(0, 1, 0, 1));
	else
		Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 1, 1));
}
//当たり判定処理
//Base::CollisionALL関数内で全てのオブジェクト同士の組み合わせで呼ばれている
//               引数に衝突検証対象のオブジェクト(b)を受け取る
void Bullet::HitCheck(Base* b) {
	//衝突検証対象のオブジェクトの種類で分岐
	switch (int t = b->GetType()) {
	//敵の場合
	case eId_Enemy:
	case eId_Player:
		//円での衝突検証
		if ( ((t == eId_Player && m_type == eId_Enemy_Bullet)  || (t == eId_Enemy && m_type == eId_Player_Bullet)) && CollisionSphere(b))
			//自身を削除
			SetKill();
		break;
	}
}

