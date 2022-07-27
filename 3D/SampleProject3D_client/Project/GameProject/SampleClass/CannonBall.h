#pragma once
#include "../stdafx.h"
#include "../Global.h"

#include "../Base/Base.h"

//砲弾クラス
class CannonBall : public Base{
private:
	//Baseクラスで定義済み
//	CModelObj	m_model;		//モデル
//	CVector3D	m_pos;			//座標
	CVector3D	m_vec;			//移動量
	int			m_cnt;			//消滅用カウンター
public:
	/*!
	@brief	コンストラクタ
	@param	pos				[in] 発生位置
	@param	vec				[in] 移動量
	**/
	CannonBall(const CVector3D& pos, const CVector3D& vec);
	/*!
	@brief	デストラクタ
	**/
	~CannonBall();
	/*!
	@brief	更新
	**/
	void Update();
	/*!
	@brief	描画
	**/
	void Draw();
};

