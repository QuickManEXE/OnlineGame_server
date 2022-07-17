#pragma once
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"
#include"../Soket.h"

class CPlayer : public Task , public CollisionCall{
private:
	CImage		img;
	CVector2D	pos;
	Collision	collision;

	Soket soket;

	int member_id;
public:
	CPlayer(int id,const CVector2D pos);
	CPlayer(int id,const float x, const float y);
	~CPlayer();

	void Update();
	void Render();


	void CallCollision(Collision *c);

	CVector2D GetPos() const {
		return pos;
	}
};