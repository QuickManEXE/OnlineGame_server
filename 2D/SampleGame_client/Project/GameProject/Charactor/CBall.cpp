#include "CBall.h"
#include"CPlayer2.h"

CBall::CBall(int id, const CVector2D p, CNetWorkDataManager::ObjectDataForSocket* od)
	: CNetWorkObjectBase(eId_Bullet, eUp_Bullet, eRd_Bullet,od),
	collision(&rect, this, eLayer_BulletEnemy),m_text()
{
	rad = 28.0f;

	vec = CVector2D(1, 1);

	CVector2D pos(GetObjectData()->pos.x, GetObjectData()->pos.y);
	rect = CRect(pos.x - rad, pos.y - rad, pos.x + rad, pos.y + rad);

	speed = 3.0f;
	
	GetObjectData()->vec = CVector3D(0,0,60.0f*3.0f);
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
	CVector2D pos(GetObjectData()->pos.x, GetObjectData()->pos.y);
	rect = CRect(pos.x - rad, pos.y - rad, pos.x + rad, pos.y + rad);

}

void CBall::Render()
{
	Utility::DrawCircle(CVector2D(GetObjectData()->pos.x,GetObjectData()->pos.y), rad, CColorRGBA(0, 1, 0, 1));
	Utility::DrawQuad(rect.m_pos, CVector2D(56,56), CColorRGBA(0, 0, 1, 0.5));

	m_text.Draw(SCREEN_WIDTH / 2 - 100, 50, 0, 1, 1, "P1[%.0f]点　P2[%.0f]点", GetObjectData()->vec.x, GetObjectData()->vec.y);

	int l = GetObjectData()->vec.z;
	
	int m = l / 60;
	int s = l % 60;

	m_text.Draw(SCREEN_WIDTH / 2 - 100, 100, 0, 1, 1, "制限時間[%d:%d]",m,s);

}

void CBall::UpdateByOwner()
{
	GetObjectData()->pos += vec * speed;

	//左端
	if (GetObjectData()->pos.x - rad < 0) {
		vec.x *= -1;
		GetObjectData()->vec.y++;
	}
	//右端
	if (GetObjectData()->pos.x + rad > SCREEN_WIDTH) {
		vec.x *= -1;
		GetObjectData()->vec.x++;
	}
	//上端
	if (GetObjectData()->pos.y - rad < 0) {
		vec.y *= -1;
	}
	//下端
	if (GetObjectData()->pos.y + rad > SCREEN_HEIGHT) {
		vec.y *= -1;
	}

	GetObjectData()->vec.z -= CFPS::GetDeltaTime();
}

void CBall::CallCollision(Collision* c)
{
	if (c->GetObj()->GetID() == eId_Player) {
		//プレイヤー同士の当たり判定
		CPlayer2 *p = static_cast<CPlayer2*>(c->GetObj());
		CVector3D v =  p->GetObjectData()->pos - GetObjectData()->pos;
		float l = v.Length();
		if (l > 0) {
			vec.x *= -1;

			speed = min(20.0f, speed + 1.0f);

		} else {
			vec.x *= -1;
		}
	}
}
