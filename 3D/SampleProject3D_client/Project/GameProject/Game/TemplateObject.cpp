#include "TemplateObject.h"
#include "../GID.h"
//コンストラクタ　オブジェクト生成時に呼ばれる
//　　　　　引数にpos(座標)とrot(回転値)を受け取る
//　　　　　　　　　　　　　　　　　　　　基底クラス（Base）へ種類の情報を渡す
TemplateObject::TemplateObject(const CVector3D& pos, float rot):Base(eId_Charactor) {
	//座標の設定
	m_pos = pos;
	//回転値の設定
	m_rot.y = rot;
	//半径の設定
	m_rad = 1.0f;

}
//更新処理
//Base::UpdateALL関数内で呼ばれている
void TemplateObject::Update() {
	
	//回転
	m_rot.y += DtoR(1.0f);

	//前方向を求める
	CVector3D dir(sin(m_rot.y), 0,cos(m_rot.y));
	
	//前に移動
	m_pos += dir * 0.1f;

	//ボタン５（スペースキー）を押した
	if (PUSH(CInput::eButton5)) {
		//オブジェクト削除
		SetKill();
	}
}
//描画処理
//Base::DrawALL関数内で呼ばれている
void TemplateObject::Draw() {
	//球の表示
	Utility::DrawSphere(m_pos, m_rad, CVector4D(1, 0, 1, 1));
}
//当たり判定処理
//Base::CollisionALL関数内で全てのオブジェクト同士の組み合わせで呼ばれている
//               引数に衝突検証対象のオブジェクト(b)を受け取る
void TemplateObject::HitCheck(Base* b) {
	//衝突検証対象のオブジェクトの種類で分岐
	switch (int t = b->GetType()) {
	//
	case eId_Charactor:
		//球での衝突検証
		//if (CollisionSphere(b)) {
			//自身を削除
			//SetKill();
		//}
		break;
	}
}

