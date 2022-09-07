#pragma once
#include "../Base/Base.h"
#include "CameraBase.h"

class Tank : public Base,public CameraBase {
private:
	enum {
		eBottom,	//車両部分
		eTop,		//砲塔部分
		eCannon,	//主砲部分
		ePartsMax,
	};
	//スタティックメッシュモデル
	CModelObj m_model[ePartsMax];

	//戦車の各パーツの行列
	CMatrix m_matrix[ePartsMax];

	//移動量
	CVector3D m_move_vec;
	//回転量
	CVector3D m_rot_vec;

	//戦車の各パーツの座標
	CVector3D m_tank_pos[ePartsMax] = {
		CVector3D(0, 0, 0),
		CVector3D(0, 2.95f, 0),
		CVector3D(0, 0.66f, 0)
	};
	//戦車の各パーツの回転値
	CVector3D m_tank_rot[ePartsMax] = {
		CVector3D(0, 0, 0),
		CVector3D(0, 0, 0),
		CVector3D(0, 0, 0)
	};

public:
	//コンストラクタ
	//引数　:発射位置
	Tank(const CVector3D& pos, float rot);
	//移動の処理
	void Update();
	//描画の処理
	void Draw();

	//当たり判定検証
	void HitCheck(Base* b);


	//CameraBaseより
	void UpdateCamera(Camera* c);
};