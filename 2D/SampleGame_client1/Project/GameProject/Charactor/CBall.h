#pragma once
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"
#include"CNetWorkObjectBase.h"


class CBall : public CNetWorkObjectBase, public CollisionCall {
private:
	CImage		img;

	Collision	collision;

	CFont m_text;

	

	float rad;

	float speed;

	CRect rect;
	CVector2D vec;
public:
	CBall(int id, const CVector2D p,CNetWorkDataManager::ObjectDataForSocket* od);
	CBall(int id, const float x, const float y, CNetWorkDataManager::ObjectDataForSocket* od);
	~CBall();

	void Update();
	void Render();
	void UpdateByOwner()override;

	void CallCollision(Collision* c);

};