#pragma once
#include "../Base/Base.h"


class TemplateObject : public Base {

public:
	//コンストラクタ
	//引数　:発射位置
	TemplateObject(const CVector3D& pos, float rot);
	//移動の処理
	void Update();
	//描画の処理
	void Draw();

	//当たり判定検証
	void HitCheck(Base* b);
};