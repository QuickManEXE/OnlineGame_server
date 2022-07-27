#pragma once
#include "../stdafx.h"
#include "../GID.h"
#include "../Global.h"
#include <list>

class Base {
protected:
	CModelObj	m_model;	//モデル
	CVector3D	m_pos;		//座標
	CVector3D	m_rot;		//回転値
	bool		m_kill;		//削除フラグ
	float		m_rad;		//半径
	int			m_type;		//種類
	//■カプセル
	CVector3D  m_lineS;
	CVector3D  m_lineE;
	static std::list<Base*> m_list;	//ゲームオブジェクト用コンテナ
public:
	//コンストラクタ
	//type : 種類
	Base(int type);
	//デストラクタ
	virtual ~Base();
	//削除フラグON
	void SetKill();
	//種類の取得
	int GetType() {
		return m_type;
	}
	//座標の取得
	CVector3D GetPos() {
		return m_pos;
	}
	//移動の取得
	void MovePos(const CVector3D& v) {
		m_pos += v;
	}
	//回転値の取得
	CVector3D GetRot() {
		return m_rot;
	}
	//半径の取得
	float GetRad() {
		return m_rad;
	}
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//オブジェクト同士の当たり判定検証
	virtual void HitCheck(Base* b);
	//モデルのとの衝突判定
	void CollisionModel(CVector3D* pos, CVector3D* vec, float rad, CModel* model);
	//カプセルと球の衝突判定
	bool CollisionCapsuleToSphere(Base* b);
	//球とカプセルの衝突判定
	bool CollisionSphereToCapsule(Base* b);
	//カプセルの衝突判定
	bool CollisionCapsule(Base* b);
	//球の衝突判定
	bool CollisionSphere(Base* b);
	//全てのオブジェクトの削除
	static void KillALL();
	//全てのオブジェクトの削除チェック
	static void CheckKillALL();
	//全てのオブジェクトの更新
	static void UpdateALL();
	//全てのオブジェクトの描画
	static void DrawALL();
	//全てのオブジェクトの当たり判定
	static void HitCheckALL();
	//オブジェクトを追加
	static void Add(Base* b);
	//オブジェクトの検索
	static Base* FindObject(int type);
	//フレンドクラス
	friend class Base;
};
