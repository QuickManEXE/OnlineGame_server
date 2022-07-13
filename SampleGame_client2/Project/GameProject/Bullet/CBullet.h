#pragma once
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"
#include "../System/CollisionCall.h"
//弾クラス
class CBulletBase : public Task, public CollisionCall {
public:
	CImage		img;
	CVector2D	pos;			//位置
	CVector2D	dir;			//方向ベクトル
	float		speed;		//速さ
	int			cnt;			//自動消滅用カウンター
	Collision	collision;

public:
	CBulletBase(const CVector2D &pos, const float ang, float speed, int layer);
	CBulletBase(const CVector2D &pos, const CVector2D &dir, float speed, int layer);
	~CBulletBase();
	void Update();
	void Render();

	//CollisionCallよりオーバーライド
	//接触時に呼ばれる
	void CallCollision(Collision *c);

};
namespace Player {
	//弾クラス
	class CBullet : public CBulletBase {
	public:
	
	public:
		CBullet(const CVector2D &pos, const float ang, float speed);
		CBullet(const CVector2D &pos, const CVector2D &dir, float speed);
	};
}

namespace Enemy {
	//弾クラス
	class CBullet : public CBulletBase {
	public:

	public:
		CBullet(const CVector2D &pos, const float ang, float speed);
		CBullet(const CVector2D &pos, const CVector2D &dir, float speed);
	};
}
