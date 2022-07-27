#include "ShooterMan.h"
#include "../GID.h"
#include "CannonBall.h"
#include "Stage.h"
//コンストラクタ　オブジェクト生成時に呼ばれる
//　　　　　引数にpos(座標)とrot(回転値)を受け取る
//　　　　　　　　　　　　　　　　　　　　基底クラス（Base）へ種類の情報を渡す
ShooterMan::ShooterMan(const CVector3D& pos, float rot):Base(eId_Player) {
	//座標の設定
	m_pos = pos;
	//回転値の設定
	m_rot.y = rot;
	//半径の設定
	m_rad = 20.0f;
	//モデルの複製
	m_model_a3m = COPY_RESOURCE("Antman", CModelA3M);

	m_wepon_model = COPY_RESOURCE("Scar", CModelObj);

	m_vec = CVector3D(0, 0, 0);
}
//更新処理
//Base::UpdateALL関数内で呼ばれている
void ShooterMan::Update() {
	//マウス操作でキャラクターを回転----
	CVector2D mouse_vec = CInput::GetMouseVec();
	m_rot.y += mouse_vec.x * -0.01f;
	m_rot.x += mouse_vec.y * 0.01f;
	m_rot.x = min(DtoR(45), max(DtoR(-45), m_rot.x));

	//方向キーの入力方向ベクトル
	CVector3D key_dir(0, 0, 0);

	//入力回転値
	float key_ang = 0;


	const float move_speed = 4.0f;

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
		//移動処理 回転行列×移動方向
		CVector3D dir = CMatrix::MRotationY(m_rot.y) * key_dir;
		m_pos += dir * move_speed;

		m_model_a3m.ChangeAnimation(1);
	}
	else {
		m_model_a3m.ChangeAnimation(0);
	}
	//モーションの更新
	m_model_a3m.UpdateAnimation();



	//★落下
	m_vec.y -= GRAVITY;
	m_pos += m_vec;
	if (HOLD(CInput::eButton1)) m_vec.y =10;
	//座標、回転、スケール設定
	m_model_a3m.SetPos(m_pos);
	m_model_a3m.SetRot(0, m_rot.y, 0);
	m_model_a3m.SetScale(0.5f, 0.5f, 0.5f);
	//★腰のボーンは向き指定
	m_model_a3m.BindFrameMatrix(5, CMatrix::MRotation(m_rot));
	//行列の更新
	m_model_a3m.UpdateMatrix();

	m_wepon_matrix = m_model_a3m.GetFrameMatrix(31) * CMatrix::MTranselate(-17.981f, -5.383f, 7.500) * CMatrix::MRotation(DtoR(90), 0, DtoR(-90));


	//左クリックで弾発射
	if (HOLD(CInput::eMouseL)) {
		static float speed = 20.0f;
		CMatrix hand_matrix = m_model_a3m.GetFrameMatrix(31);
		CMatrix rot_matrix = CMatrix::MRotation(m_rot);
		CVector3D pos = m_wepon_matrix * CVector4D(0, 0, 50, 1);
		CVector3D dir = rot_matrix.GetFront();
		Base::Add(new CannonBall(pos, dir * speed));
	}

	//■カプセルの設定
	m_lineS = m_pos + CVector3D(0, 80, 0);
	m_lineE = m_pos + CVector3D(0, m_rad, 0);
}
//描画処理
//Base::DrawALL関数内で呼ばれている
void ShooterMan::Draw() {
	//球の表示
	//Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 1, 1));
	m_model_a3m.SetPos(m_pos);
	m_model_a3m.SetRot(0, m_rot.y, 0);
	m_model_a3m.SetScale(0.5f, 0.5f, 0.5f);
	m_model_a3m.BindFrameMatrix(5, CMatrix::MRotation(m_rot));
	m_model_a3m.Render();

	m_wepon_model.Render(m_wepon_matrix);
}
//当たり判定処理
//Base::CollisionALL関数内で全てのオブジェクト同士の組み合わせで呼ばれている
//               引数に衝突検証対象のオブジェクト(b)を受け取る
void ShooterMan::HitCheck(Base* b) {
	//衝突検証対象のオブジェクトの種類で分岐
	switch (int t = b->GetType()) {
		//
	case eId_Enemy:
		if (CollisionCapsule(b)) {
			CVector3D v = b->GetPos() - m_pos;
			float s = m_rad + b->GetRad() - v.Length();
			v.Normalize(); v.y = 0;
			b->MovePos(v * s);
		}

		break;
	case eId_Field:
		//★
		if (Stage* s = dynamic_cast<Stage*>(b)) {
			Base::CollisionModel(&m_pos, &m_vec, m_rad, s->GetCollisionModel());
		}
		break;
	}}

