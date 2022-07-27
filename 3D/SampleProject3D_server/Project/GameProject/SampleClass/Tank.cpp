#include "Tank.h"
#include "../GID.h"
#include "CannonBall.h"
//コンストラクタ　オブジェクト生成時に呼ばれる
//　　　　　引数にpos(座標)とrot(回転値)を受け取る
//　　　　　　　　　　　　　　　　　　　　基底クラス（Base）へ種類の情報を渡す
Tank::Tank(const CVector3D& pos, float rot):Base(eId_Player) {
	//座標の設定
	m_pos = pos;
	//回転値の設定
	m_rot.y = rot;
	//半径の設定
	m_rad = 1.0f;

	//ADD_RESOURCE("TankBottom", CModel::CreateModel("Wepon/Tank/Bottom.obj"));
	//ADD_RESOURCE("TankTop", CModel::CreateModel("Wepon/Tank/Top.obj"));
	//ADD_RESOURCE("TankGun", CModel::CreateModel("Wepon/Tank/Gun.obj"));

	//モデルの複製

	m_model[eBottom] = COPY_RESOURCE("TankBottom", CModelObj);
	m_model[eTop] = COPY_RESOURCE("TankTop", CModelObj);
	m_model[eCannon] = COPY_RESOURCE("TankGun", CModelObj);


}
//更新処理
//Base::UpdateALL関数内で呼ばれている
void Tank::Update() {


	//回転加速度
	const float rot_accel = 0.1f;
	//移動量
	const float move_accel = 0.1f;

	//砲塔、主砲の回転
	CVector2D mouse_vec = CInput::GetMouseVec();
	m_tank_rot[eTop].y += mouse_vec.x * -0.01f;
	m_tank_rot[eCannon].x += mouse_vec.y * 0.01f;


	//回転減速処理
	m_rot_vec *= 0.9f;
	//移動減速処理
	m_move_vec *= 0.9f;
	//回転処理	
	m_tank_rot[eBottom] += m_rot_vec;
	//移動処理
	m_tank_pos[eBottom] += m_move_vec;

	//車両の回転
	if (HOLD(CInput::eLeft)) {
		m_rot_vec.y += DtoR(rot_accel);
	}
	if (HOLD(CInput::eRight)) {
		m_rot_vec.y -= DtoR(rot_accel);
	}
	//移動処理
	if (HOLD(CInput::eUp)) {
		m_move_vec += m_matrix[eBottom].GetFront() * move_accel;
	}

	if (HOLD(CInput::eDown)) {
		m_move_vec -= m_matrix[eBottom].GetFront() * move_accel;
	}
	//-------------------------------------------------


	//戦車の行列を設定する
	//階層構造を構築する　[親×子]
	m_matrix[eBottom] = CMatrix::MTranselate(m_tank_pos[eBottom]) *
		CMatrix::MRotation(m_tank_rot[eBottom])*
		CMatrix::MScale(10,10,10);
	m_matrix[eTop] = m_matrix[eBottom] * CMatrix::MTranselate(0, 2.95f, 0) * CMatrix::MRotation(m_tank_rot[eTop]);
	m_matrix[eCannon] = m_matrix[eTop] * CMatrix::MTranselate(0, 0.66f, 0) * CMatrix::MRotation(m_tank_rot[eCannon]);



	//左クリックで弾発射
	if (PUSH(CInput::eMouseL)) {
		static float speed = 20.0f;
		CVector3D dir=m_matrix[eCannon].GetFront().GetNormalize();
		//CVector3D pos= m_matrix[eCannon].GetPosition();
		//CVector3D pos = 
			//　主砲の行列　×　前へ5平行移動
		//	(m_matrix[eCannon] * CMatrix::MTranselate(0, 0, 5)).GetPosition();

		//　主砲の行列　×　前へ5移動するベクトル
		CVector3D pos = m_matrix[eCannon] * CVector4D(0, 0, 5, 1);
		Base::Add(new CannonBall(pos, dir* speed));
	}

	//汎用座標と回転値にコピー
	//（カメラで使用しているため）
	m_pos = m_tank_pos[eBottom];
	m_rot = m_tank_rot[eBottom];

}
//描画処理
//Base::DrawALL関数内で呼ばれている
void Tank::Draw() {

	//行列を指定して描画
	for (int i = 0; i < ePartsMax; i++) {
		m_model[i].Render(m_matrix[i]);
	}

}
//当たり判定処理
//Base::CollisionALL関数内で全てのオブジェクト同士の組み合わせで呼ばれている
//               引数に衝突検証対象のオブジェクト(b)を受け取る
void Tank::HitCheck(Base* b) {
	//衝突検証対象のオブジェクトの種類で分岐
	switch (int t = b->GetType()) {
	//
	case eId_Charactor:

		break;
	}
}
//カメラの更新
void Tank::UpdateCamera(Camera* c)
{
	CMatrix m = m_matrix[eTop] * CMatrix::MTranselate(0, 4.00, -15.0);
	//カメラ本体へデータを渡す
	c->SetParam(m.GetPosition(), m.GetPosition() + m.GetFront(), m.GetUp());

}

