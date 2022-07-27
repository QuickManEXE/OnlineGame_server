#include "AntMan.h"
#include "../GID.h"
//コンストラクタ　オブジェクト生成時に呼ばれる
//　　　　　引数にpos(座標)とrot(回転値)を受け取る
//　　　　　　　　　　　　　　　　　　　　基底クラス（Base）へ種類の情報を渡す
AntMan::AntMan(const CVector3D& pos, float rot):Base(eId_Player) {
	//座標の設定
	m_pos = pos;
	//回転値の設定
	m_rot.y = rot;
	//半径の設定
	m_rad = 1.0f;
	//モデルの複製
	m_model_a3m = COPY_RESOURCE("Antman", CModelA3M);

}
//更新処理
//Base::UpdateALL関数内で呼ばれている
void AntMan::Update() {
	
	//方向キーの入力方向ベクトル
	CVector3D key_dir(0, 0, 0);

	//カメラの方向ベクトル
	CVector3D cam_dir = CCamera::GetCurrent()->GetDir();

	//入力回転値
	float key_ang = 0;
	//カメラの回転値
	float cam_ang = atan2(cam_dir.x, cam_dir.z);


	const float move_speed = 1.0f;

	//方向キーから入力方向ベクトルを設定
	if (CInput::GetState(0, CInput::eHold, CInput::eUp)) {
		key_dir.z = 1;
	}
	if (CInput::GetState(0, CInput::eHold, CInput::eDown)) {
		key_dir.z = -1;
	}
	if (CInput::GetState(0, CInput::eHold, CInput::eLeft)) {
		key_dir.x = 1;
	}
	if (CInput::GetState(0, CInput::eHold, CInput::eRight)) {
		key_dir.x = -1;
	}

	//キー入力があれば
	if (key_dir.LengthSq() > 0) {
		//入力方向から入力回転値を計算
		key_ang = atan2(key_dir.x, key_dir.z);
		//カメラの回転値と入力回転値からキャラクターの回転値を決定
		m_rot.y = cam_ang + key_ang;

		//移動処理
		CVector3D dir(sin(m_rot.y), 0, cos(m_rot.y));
		m_pos += dir * move_speed;

		m_model_a3m.ChangeAnimation(1);
	}
	else {
		m_model_a3m.ChangeAnimation(0);
	}
	//モーションの更新
	m_model_a3m.UpdateAnimation();
}
//描画処理
//Base::DrawALL関数内で呼ばれている
void AntMan::Draw() {
	//球の表示
	//Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 1, 1));
	m_model_a3m.SetPos(m_pos);
	m_model_a3m.SetRot(m_rot);
	m_model_a3m.SetScale(0.25f, 0.25f, 0.25f);
	m_model_a3m.Render();
}
//当たり判定処理
//Base::CollisionALL関数内で全てのオブジェクト同士の組み合わせで呼ばれている
//               引数に衝突検証対象のオブジェクト(b)を受け取る
void AntMan::HitCheck(Base* b) {
	//衝突検証対象のオブジェクトの種類で分岐
	switch (int t = b->GetType()) {
	//
	case eId_Charactor:

		break;
	}
}

