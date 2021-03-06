#pragma once
#include "../Base/Base.h"
class Enemy :public Base {
private:
	int m_cnt;
public:
	Enemy(const CVector3D& pos, float rot);
	//移動の処理
	void Update();
	//描画の処理
	void Draw();
	//当たり判定検証
	void HitCheck(Base* b);
};