#include "CPlayer2.h"



CPlayer2::CPlayer2(const float x, const float y, CNetWorkDataManager::ObjectDataForSocket* od)
	:CPlayer2(CVector2D(x, y), od){}

CPlayer2::CPlayer2(const CVector2D pos, CNetWorkDataManager::ObjectDataForSocket* od)
	: CNetWorkObjectBase(eId_Player, eUp_Player, eRd_Player,od)
{
	//‰Šú‰»
	//ƒvƒŒƒCƒ„[‰æ‘œ‚Ìæ“¾
	img = COPY_RESOURCE("Player", CImage);
	img.SetCenter(32, 32);

	rect = CRect(CVector2D(pos), CVector2D(32, 128));
}

CPlayer2::~CPlayer2()
{
}

void CPlayer2::Update()
{
	
}

void CPlayer2::Render()
{
	img.SetPos(GetObjectData()->pos.x,GetObjectData()->pos.y);

	//•`‰æˆ—
	img.Draw();
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
