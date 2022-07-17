#pragma once
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"

class CEnemy : public Task , public CollisionCall{
private:
	CImage		img;
	CVector2D	pos;
	Collision	collision;
	int			cnt;

public:
	CEnemy(CVector2D pos);
	CEnemy(float x,float y);
	~CEnemy();

	void Update();
	void Render();


	void CallCollision(Collision *c);


	CVector2D GetPos() const {
		return pos;
	}
};