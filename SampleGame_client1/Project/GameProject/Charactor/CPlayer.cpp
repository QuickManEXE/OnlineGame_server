#include "CPlayer.h"
#include "../Bullet/CBullet.h"
#include "../Charactor/CEnemy.h"
#include "../Effect/CEffect.h"
using namespace Player;
CPlayer::CPlayer(int id,const float x, const float y,PlayerDataManager::PlayerData* pd):CPlayer(id,CVector2D(x,y),pd) {
}
CPlayer::CPlayer(int id,const CVector2D p,PlayerDataManager::PlayerData* pd):Task(eId_Player,eUp_Player,eRd_Player), 
collision(&pos,28.0f,this,eLayer_Player)
{
	//初期化
	//プレイヤー画像の取得
	img = COPY_RESOURCE("Player",CImage);
	img.SetCenter(32, 32);

	//プレイヤーの初期位置
	pos = p;
	member_id = id;

	m_playerData = pd;
	
	
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Update()
{
	pos = m_playerData->pos;
	//更新処理
	//if との組み合わせ
	//各方向キーを押していれば
	//HOLD(CInput::eUp) HOLD(CInput::eDown) HOLD(CInput::eLeft) HOLD(CInput::eRight)
	//ボタン Z						X			        C
	//PUSH(CInput::eButton1),PUSH(CInput::eButton2),PUSH(CInput::eButton3)
	
	//プレイヤーの位置
	//pos.x 横の位置　	pos.y　縦の位置
	if (m_playerData->key[CInput::eRight]) {
		m_playerData->pos.x += 4;
	}
	if (m_playerData->key[CInput::eLeft]) {
		m_playerData->pos.x -= 4;
	}

	if (PUSH(CInput::eButton1)) {
		new CBullet(pos, 180, 5);			//真上へ撃つ
	}

	//弾生成     位置　発射角　速さ
	//new CBullet(pos, 0, 5);			//真下に撃つ
	//new CBullet(pos, 180, 5);			//真上へ撃つ
	

	//敵生成       x　y
	//new CEnemy(500,200);				//(500,200)の場所へ敵を生成する
	
	//プレイヤー生成 x　y
	//new CPlayer(pos);				//同じ場所にプレイヤーを生成する
}

void CPlayer::Render()
{

	img.SetPos(pos);

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


