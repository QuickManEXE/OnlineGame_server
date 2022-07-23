#include "CPlayer.h"
#include "../Bullet/CBullet.h"
#include "../Charactor/CEnemy.h"
#include "../Effect/CEffect.h"



using namespace Player;
CPlayer::CPlayer(int id,const float x, const float y):CPlayer(id,CVector2D(x,y)) {
}
CPlayer::CPlayer(int id,const CVector2D p):Task(eId_Player,eUp_Player,eRd_Player), 
collision(&m_playerData.pos,28.0f,this,eLayer_Player)
{
	//初期化
	//プレイヤー画像の取得
	img = COPY_RESOURCE("Player",CImage);
	img.SetCenter(32, 32);

	//プレイヤーの初期位置
	m_playerData.pos = p;
	m_playerData.member_id = id;
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Update()
{
	if (m_playerData.key[CInput::eUp]) {
		m_playerData.pos.y -= 4;
	}
	if (m_playerData.key[CInput::eDown]) {
		m_playerData.pos.x += 4;
	}

}

void CPlayer::Render()
{

	img.SetPos(m_playerData.pos);

	//描画処理
	img.Draw();
}

void CPlayer::CallCollision(Collision * c)
{
	if (c->GetObj()->GetID() == eId_Player) {
		//プレイヤー同士の当たり判定
		CPlayer *p = static_cast<CPlayer*>(c->GetObj());
		CVector2D v =  p->GetPos() - pos;
		float l = v.Length();
		if (l > 0) {
			pos -= v/l * (28 + 28 - l)/2;
		} else {
			pos -= CVector2D(1, 0.1);
		}
	} else {
		new CEffect(pos);
		//衝突時処理
		SetKill();
	}
}


