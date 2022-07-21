#include "CPlayer.h"
#include "../Bullet/CBullet.h"
#include "../Charactor/CEnemy.h"
#include "../Effect/CEffect.h"



using namespace Player;
CPlayer::CPlayer(int id,const float x, const float y):CPlayer(id,CVector2D(x,y)) {
}
CPlayer::CPlayer(int id,const CVector2D p):Task(eId_Player,eUp_Player,eRd_Player), 
collision(&pos,28.0f,this,eLayer_Player)
{
	//初期化
	//プレイヤー画像の取得
	img = COPY_RESOURCE("Player",CImage);
	img.SetCenter(32, 32);

	//プレイヤーの初期位置
	pos = p;

	//soket.Init();

	member_id = id;
}

CPlayer::~CPlayer()
{
	//soket.finalize();
}

void CPlayer::Update()
{
	if (m_playerData.key[CInput::eRight]) {
		pos.x += 4;
	}
	if (m_playerData.key[CInput::eLeft]) {
		pos.x -= 4;
	}



	//更新処理
	//printf("ここの処理を繰り返し実行しています");
	//if との組み合わせ
	//各方向キーを押していれば
	//HOLD(CInput::eUp) HOLD(CInput::eDown) HOLD(CInput::eLeft) HOLD(CInput::eRight)
	//ボタン Z						X			        C
	//PUSH(CInput::eButton1),PUSH(CInput::eButton2),PUSH(CInput::eButton3)

	//プレイヤーの位置
	//pos.x 横の位置　	pos.y　縦の位置
	/*if (HOLD(CInput::eRight)) {
		pos.x += 4;
	}
	if (HOLD(CInput::eLeft)) {
		pos.x -= 4;
	}*/


	//if (PUSH(CInput::eButton1)) {
	//	new CBullet(pos, 180, 5);			//真上へ撃つ
	//}

	//弾生成     位置　発射角　速さ
	//new CBullet(pos, 0, 5);			//真下に撃つ
	//new CBullet(pos, 180, 5);			//真上へ撃つ


	//敵生成       x　y
	//new CEnemy(500,200);				//(500,200)の場所へ敵を生成する

	//プレイヤー生成 x　y
	//new CPlayer(pos);				//同じ場所にプレイヤーを生成する

	//移動処理の初期化
	//soket.pos = CVector3D::zero;
	//サーバーの更新
	//soket.Run(&pos);
	//移動の更新
	//pos += CVector2D(soket.pos.x,soket.pos.y);

}

void CPlayer::Render()
{
	//soket.SendRenderUpdateData(pos);
	//CVector2D pos(soket.pos.x, soket.pos.y);

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


