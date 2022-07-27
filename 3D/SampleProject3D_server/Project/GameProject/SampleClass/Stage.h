#pragma once
#include "../Base/Base.h"
#include "CameraBase.h"

class Stage : public Base {
private:
	//スタティックメッシュモデル
	//CModelObj m_model;
	//フィールドモデル
	//CModelField* m_field;
	//当たり判定用モデル
	CModelObj m_model_collision;



public:
	//コンストラクタ
	//引数　:発射位置
	Stage();
	//移動の処理
	void Update();
	//描画の処理
	void Draw();
	//衝突判定用モデルの取得
	CModel* GetCollisionModel();
};