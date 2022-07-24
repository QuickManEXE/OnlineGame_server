#pragma once
#include "../stdafx.h"
#include"CNetWorkObjectBase.h"


class CPlayer2 : public CNetWorkObjectBase{
private:
	CImage img;
	CRect rect;

public:
	CPlayer2(const CVector2D pos, CNetWorkDataManager::ObjectDataForSocket* od);
	CPlayer2(const float x, const float y, CNetWorkDataManager::ObjectDataForSocket* od);
	~CPlayer2();

	void Update();
	void Render();
	void UpdateByOwner()override;
};