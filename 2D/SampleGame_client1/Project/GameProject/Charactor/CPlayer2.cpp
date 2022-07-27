#include "CPlayer2.h"



CPlayer2::CPlayer2(const float x, const float y, CNetWorkDataManager::ObjectDataForSocket* od)
	:CPlayer2(CVector2D(x, y), od){}

CPlayer2::CPlayer2(const CVector2D pos, CNetWorkDataManager::ObjectDataForSocket* od)
	: CNetWorkObjectBase(eId_Player, eUp_Player, eRd_Player,od),
	collision(&rect, this, eLayer_Player)
{
	//èâä˙âª
	//ÉvÉåÉCÉÑÅ[âÊëúÇÃéÊìæ
	img = COPY_RESOURCE("Player", CImage);
	img.SetCenter(32, 32);

	rect = CRect(CVector2D(pos), CVector2D(32, 128));
}

CPlayer2::~CPlayer2()
{
}

void CPlayer2::Update()
{
	CVector2D pos(GetObjectData()->pos.x, GetObjectData()->pos.y);
	rect = CRect(pos.x - 32, pos.y - 128, pos.x + 32, pos.y + 128);

}

void CPlayer2::Render()
{
	//img.SetPos(GetObjectData()->pos.x,GetObjectData()->pos.y);

	//ï`âÊèàóù
	//img.Draw();

	Utility::DrawQuad(rect.m_pos, CVector2D(62,256), CColorRGBA(1, 0, 0, 1));

}

void CPlayer2::UpdateByOwner()
{
	for (int i = 0; i < CInput::eKeyMax; i++) {
		GetObjectData()->key[i] = 0;
	}

	if (HOLD(CInput::eUp)) {
		GetObjectData()->key[CInput::eUp] = 1;
		GetObjectData()->pos.y -= 4;
	}
	if (HOLD(CInput::eDown)) {
		GetObjectData()->key[CInput::eDown] = 1;
		GetObjectData()->pos.y += 4;
	}
}

void CPlayer2::CallCollision(Collision* c)
{
}
