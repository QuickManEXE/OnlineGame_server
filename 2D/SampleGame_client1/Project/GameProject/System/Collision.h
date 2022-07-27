/**
* @Author	YukiYamaji
* @Day		17/11/18
* @Brief	衝突判定基底
*/

#ifndef COLLISION_GUARD
#define COLLISION_GUARD

#include "CollisionCall.h"
#include "Task.h"

//各マスク設定
enum ECOLLISION_Layer{
	eLayer_Player,
	eLayer_Enemy,
	eLayer_Field,
	eLayer_BulletPlayer,
	eLayer_BulletEnemy,
	eLayer_Max,
};
enum ECOLLISION_Type {
	eCollision_Shpere,
	eCollision_Rect,
};


//球データ
struct T_Shpere
{
	CVector2D	*pos;	//座標
	float		rad;	//半径
};

struct T_Rect
{
	CRect *rect;
};


class Collision : public Task
{	
private:
	CollisionCall	*mp_obj;		//衝突判定オブジェクトポインタ
	//各形状データポインタ
	T_Shpere		m_shpere;		
	T_Rect           m_rect;
	int				 m_type;		//形状タイプ
	unsigned int	 m_body;		//自身マスク
	bool			m_active;		//衝突有効フラグ
	static char m_layer_mask[eLayer_Max][eLayer_Max];
public:

	//球用コンストラクタ
	Collision(CVector2D *p,float rad, CollisionCall *obj, unsigned int body);
	Collision(CRect* rect, CollisionCall* obj, unsigned int body);
	~Collision();
	void CheckCollision(Task *t);										//各衝突判定チェック
	static bool CollosionShpere(Collision *c1, Collision *c2);			//球対球
	static bool CollisionRect(Collision* c1, Collision* c2);

																		//衝突球取得
	const T_Shpere *GetColllisionShpere() const
	{
		return &m_shpere;
	}
	//衝突判定オブジェクト取得
	Task* GetObj() const
	{
		return dynamic_cast<Task*>(mp_obj);
	}
	//衝突有効フラグを設定
	//@param [in] m_actice true:有効 false:無効
	void SetActive(bool f) { m_active = f; }
	friend class Collision;
};

#endif