#include "CPlayer2.h"



CPlayer2::CPlayer2(int id, const float x, const float y, CNetWorkDataManager::ObjectDataForSocket* od)
	:CPlayer2(id, CVector2D(x, y), od)
{

}

CPlayer2::CPlayer2(int id, const CVector2D pos, CNetWorkDataManager::ObjectDataForSocket* od)
	: CNetWorkObjectBase(id, eUp_Player, eRd_Player,od)
{
}

CPlayer2::~CPlayer2()
{
}

void CPlayer2::Update()
{
}

void CPlayer2::Render()
{
}

void CPlayer2::UpdateByOwner()
{
}
