#pragma once
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"
#include"../PlayerDataManager.h"

class CPlayer : public Task , public CollisionCall{
	friend class Soket;
	friend class PlayerDataManager;
private:
	CImage		img;
	CVector2D	pos;
	Collision	collision;

	int member_id;

	PlayerDataManager::PlayerData m_playerData;
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