#include "CBall.h"


CBall::CBall(int id, const CVector2D p, CNetWorkDataManager::ObjectDataForSocket* od)
	: CNetWorkObjectBase(eId_Bullet, eUp_Bullet, eRd_Bullet,od),
	collision(&pos, 28.0f, this, eLayer_BulletEnemy)
{
	rad = 28.0f;

	vec = CVector2D(1, 1);
}

CBall::CBall(int id, const float x, const float y, CNetWorkDataManager::ObjectDataForSocket* od)
	:CBall(id, CVector2D(x, y),od)
{
}

CBall::~CBall()
{
}

void CBall::Update()
{
	

}

void CBall::Render()
{
	Utility::DrawCircle(CVector2D(GetObjectData()->pos.x,GetObjectData()->pos.y), rad, CColorRGBA(0, 1, 0, 1));
}

void CBall::UpdateByOwner()
{
	GetObjectData()->pos += vec;

	//左端
	if (GetObjectData()->pos.x - rad < 0) {
		vec.x *= -1;
	}
	//右端
	if (GetObjectData()->pos.x + rad > SCREEN_WIDTH) {
		vec.x *= -1;
	}
	//上端
	if (GetObjectData()->pos.y - rad < 0) {
		vec.y *= -1;
	}
	//下端
	if (GetObjectData()->pos.y + rad > SCREEN_HEIGHT) {
		vec.y *= -1;
	}
}

void CBall::CallCollision(Collision* c)
{
}
