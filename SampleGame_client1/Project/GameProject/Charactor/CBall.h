#pragma once
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"
#include"../PlayerDataManager.h"


class CBall : public Task, public CollisionCall {
private:
	CImage		img;
	CVector2D	pos;
	Collision	collision;
	CRect rect;
	float rad;

	int member_id;

	CVector2D vec;

	PlayerDataManager::PlayerData m_ballData;
public:
	CBall(int id, const CVector2D p);
	CBall(int id, const float x, const float y);
	~CBall();

	void Update();
	void Render();


	void CallCollision(Collision* c);

	CVector2D GetPos() const {
		return pos;
	}
};