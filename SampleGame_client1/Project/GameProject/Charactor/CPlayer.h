#pragma once
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"
#include"../Soket.h"
#include"../PlayerDataManager.h"

class CPlayer : public Task , public CollisionCall{
private:
	CImage		img;
	CVector2D	pos;
	Collision	collision;

	int member_id;

public:

	PlayerDataManager::PlayerData* m_playerData;

public:
	CPlayer(int id,const CVector2D pos, PlayerDataManager::PlayerData* pd);
	CPlayer(int id,const float x, const float y,PlayerDataManager::PlayerData* pd);
	~CPlayer();

	void Update();
	void Render();


	void CallCollision(Collision *c);

	CVector2D GetPos() const {
		return pos;
	}
};