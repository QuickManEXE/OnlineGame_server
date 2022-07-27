#pragma once
#include "../stdafx.h"
#include"../System/Collision.h"
#include"CNetWorkObjectBase.h"


class CPlayer2 : public CNetWorkObjectBase, public CollisionCall {
private:
	CImage img;
	CRect rect;

	Collision	collision;
public:
	CPlayer2(const CVector2D pos, CNetWorkDataManager::ObjectDataForSocket* od);
	CPlayer2(const float x, const float y, CNetWorkDataManager::ObjectDataForSocket* od);
	~CPlayer2();

	void Update();
	void Render();
	void UpdateByOwner()override;

	void CallCollision(Collision* c);
};