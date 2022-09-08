#pragma once
#include "../Base/Base.h"
#include"../NetWorkObjectBase/NetWorkObjectBase.h"

class Bullet : public NetWorkObjectBase {
	float m_speed;
	int m_cnt;
public:
	//コンストラクタ
	//引数　:発射位置
	Bullet(const CVector3D& pos, float rot,float speed,int bullet_type, NetWorkObjectManager::ObjectDataForSocket* od);
	//移動の処理
	void Update();
	void UpdateByOwner()override;
	//描画の処理
	void Draw();

	//当たり判定検証
	void HitCheck(Base* b);
};