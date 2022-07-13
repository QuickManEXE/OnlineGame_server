#include "CBullet.h"
#include "../Effect/CEffect.h"
CBulletBase::CBulletBase(const CVector2D &pos, const float ang, float speed, int layer) : CBulletBase(pos, CVector2D(sin(DtoR(ang)), cos(DtoR(ang))), speed,layer) {

}
CBulletBase::CBulletBase(const CVector2D &p, const CVector2D &d, float sp,int layer):
	Task(eId_Bullet, eUp_Bullet, eRd_Bullet),
	collision(&pos,12.0f,this, layer){
	pos = p;
	dir = d;
	speed = sp;
	cnt = 0;
}
CBulletBase::~CBulletBase() {

}
void CBulletBase::Update() {
	pos += dir * speed;
	if (pos.y < 0 || pos.y > SCREEN_HEIGHT || pos.x < 0 || pos.x > SCREEN_WIDTH)
		SetKill();
	
}
void CBulletBase::CallCollision(Collision * c)
{
	
	//íeè¡ñ≈
	SetKill();
}
void CBulletBase::Render() {

	img.SetPos(pos);
	img.Draw();
}

Player::CBullet::CBullet(const CVector2D & pos, const float ang, float speed)
	:CBullet(pos, CVector2D(sin(DtoR(ang)), cos(DtoR(ang))), speed)
{

}

Player::CBullet::CBullet(const CVector2D & pos, const CVector2D & dir, float speed)
	: CBulletBase(pos, dir, speed,eLayer_BulletPlayer)
{
	img = COPY_RESOURCE("Bullet", CImage);
	img.SetCenter(16, 16);

}

Enemy::CBullet::CBullet(const CVector2D & pos, const float ang, float speed)
	:CBullet(pos, CVector2D(sin(DtoR(ang)), cos(DtoR(ang))), speed)
{

}

Enemy::CBullet::CBullet(const CVector2D & pos, const CVector2D & dir, float speed)
	: CBulletBase(pos, dir, speed, eLayer_BulletEnemy)
{
	img = COPY_RESOURCE("Bullet2", CImage);
	img.SetCenter(16, 16);

}
