#pragma once
#include "../Base/Base.h"


class NPC : public Base {
private:
	CModelA3M m_model_a3m;
	CVector3D m_vec;
public:
	//コンストラクタ
	//引数　:発射位置
	NPC(const CVector3D& pos, float rot);
	//移動の処理
	void Update();
	//描画の処理
	void Draw();

	//当たり判定検証
	void HitCheck(Base* b);
};