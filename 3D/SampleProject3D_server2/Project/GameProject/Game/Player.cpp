#include "Player.h"
#include "Bullet.h"

//コンストラクタ　オブジェクト生成時に呼ばれる
//　　　　　引数にpos(座標)を受け取る
//　　　　　　　　　　　　　　基底クラス（Base）へ種類の情報を渡す
Player::Player(const CVector3D& pos,NetWorkObjectManager::ObjectDataForSocket* od) : NetWorkObjectBase(eId_Player,od){
	//読み込み済みの画像を複製
	m_model = COPY_RESOURCE("Player", CModelObj);
	//m_model.SetScale(0.01f, 0.01f, 0.01f);
	//中心位置を設定（回転軸に影響）
	//座標を設定
	m_pos = pos;
	//半径を設定
	m_rad = 1;
	m_vec = CVector3D(0, 0, 0);
}
//更新処理
//Base::UpdateALL関数内で呼ばれている
void Player::Update() {
	//移動速度設定
	const float speed = 0.012f;
	//前方向を求める
	CVector3D dir = CVector3D(sin(m_rot.y),0,cos(m_rot.y));
	
	//上キーを押していれば
	if (HOLD(CInput::eUp))
		//前に移動
		m_vec += dir * speed;
	//左キーを押していれば
	if (HOLD(CInput::eLeft))
		//左に回転
		m_rot.y += DtoR(2);
	//右キーを押していれば
	if (HOLD(CInput::eRight))
		//右に回転
		m_rot.y += DtoR(-2);
	m_vec *= 0.94f;
	if (m_vec.Length() < speed/2) m_vec = CVector3D::zero;
	m_pos += m_vec;
	/*if (HOLD(CInput::eRight))
		m_vec.x -= speed;

	if (HOLD(CInput::eLeft))
		m_pos.x += speed;
		*/
	//ボタン5を押せば

	if (GetObjectData()->key[CInput::eButton5] == 1) {

		//if (PUSH(CInput::eButton5))
		//弾の生成とリストへの追加
		//					自身の座標と回転を渡す
		Base::Add(new Bullet(m_pos, m_rot.y,0.4f,eId_Player_Bullet));

	}

	

}
void Player::UpdateByOwner()
{

	CVector3D* m_pos = &GetObjectData()->pos;

	CVector3D* m_rot = &GetObjectData()->rot;

	CVector3D* m_vec = &GetObjectData()->vec;

	//移動速度設定
	const float speed = 0.012f;
	//前方向を求める
	CVector3D dir = CVector3D(sin(m_rot->y), 0, cos(m_rot->y));

	//上キーを押していれば
	if (HOLD(CInput::eUp))
		//前に移動
		*m_vec += dir * speed;
	//左キーを押していれば
	if (HOLD(CInput::eLeft))
		//左に回転
		m_rot->y += DtoR(2);
	//右キーを押していれば
	if (HOLD(CInput::eRight))
		//右に回転
		m_rot->y += DtoR(-2);
	*m_vec *= 0.94f;
	if (m_vec->Length() < speed / 2) *m_vec = CVector3D::zero;
	*m_pos += *m_vec;
	/*if (HOLD(CInput::eRight))
		m_vec.x -= speed;

	if (HOLD(CInput::eLeft))
		m_pos.x += speed;
		*/
		//ボタン5を押せば
	if (PUSH(CInput::eButton5))
		//弾の生成とリストへの追加
		//					自身の座標と回転を渡す
		//Base::Add(new Bullet(*m_pos, m_rot->y, 0.4f, eId_Player_Bullet));
		GetObjectData()->key[CInput::eButton5] = 1;





}
//描画処理
//Base::DrawALL関数内で呼ばれている
void Player::Draw() {


	CVector3D m_pos = GetObjectData()->pos;
	CVector3D m_rot = GetObjectData()->rot;

	//表示位置の設定
	m_model.SetPos(m_pos);
	//回転値を設定
	m_model.SetRot(m_rot);
	//描画
	m_model.Render();

}
//当たり判定処理
//Base::CollisionALL関数内で全てのオブジェクト同士の組み合わせで呼ばれている
//               引数に衝突検証対象のオブジェクト(b)を受け取る
void Player::HitCheck(Base* b) {
	//衝突検証対象のオブジェクトの種類で分岐
	switch (b->GetType()) {
		//敵の場合
	case eId_Enemy:
		//円での衝突検証
		{
			//２点間のベクトルを求める
			CVector3D v = b->GetPos()- m_pos;
			//ベクトルの長さを求める
			//（２点間の距離が分かる）
			float l = v.Length();
			//２点間の距離が２つの円の
			//半径以下ならば当たっている
			if (l <= m_rad + b->GetRad()) {
				CVector3D nv = v.GetNormalize();
				float s = m_rad + b->GetRad() - l;
				MovePos(-nv * s * 0.2);
				b->MovePos(nv * s * 0.8);
			}
 
		}
		break;
	case eId_Enemy_Bullet:
		//円での衝突検証
		if (CollisionSphere(b))
			//自身を削除
			SetKill();
		break;
	}
}

