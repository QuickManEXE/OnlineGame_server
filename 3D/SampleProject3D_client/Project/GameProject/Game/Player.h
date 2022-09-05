#pragma once
#include "../Base/Base.h"
#include"../NetWorkObjectBase/NetWorkObjectBase.h"

class Player : public NetWorkObjectBase{
private:
	CVector3D m_vec;
public:
	Player(const CVector3D& pos,NetWorkObjectManager::ObjectDataForSocket* od);
	void Update();
	void UpdateByOwner()override;
	void Draw();
	void HitCheck(Base* b);
};