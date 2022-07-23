#include "CBall.h"


CBall::CBall(int id, const float x, const float y):CBall(id, CVector2D(x, y))
{
}

CBall::CBall(int id, const CVector2D p) : Task(eId_Bullet, eUp_Bullet, eRd_Bullet),
collision(&pos, 28.0f, this, eLayer_BulletEnemy)
{
	//初期化
	//プレイヤー画像の取得
	img = COPY_RESOURCE("Player", CImage);
	img.SetCenter(32, 32);

	//プレイヤーの初期位置
	pos = p;
	member_id = id;

	rad = 28.0f;

	vec = CVector2D(1, 1);
}

CBall::~CBall()
{
}

void CBall::Update()
{
	pos += vec;

	//左端
	if (pos.x - rad < 0) {
		vec.x *= -1;
	}
	//右端
	if (pos.x + rad > SCREEN_WIDTH) {
		vec.x *= -1;
	}
	//上端
	if (pos.y - rad < 0) {
		vec.y *= -1;
	}
	//下端
	if (pos.y + rad > SCREEN_HEIGHT) {
		vec.y *= -1;
	}

}

void CBall::Render()
{
	Utility::DrawCircle(pos, rad, CColorRGBA(0, 1, 0, 1));
}

void CBall::CallCollision(Collision* c)
{
}
