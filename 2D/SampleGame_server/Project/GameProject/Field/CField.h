#pragma once

//Taskシステムへ登録するのに必要なヘッダーファイル
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"
#include "../System/CollisionCall.h"
//Taskは継承必須、
//衝突後のコールバック関数も継承(インターフェイス)
class CField : public Task,public CollisionCall{
private:

public:
	CField();

	//TaskのRenderをオーバーライド
	void Render();

	//衝突コールバックをオーバーライド
	void CallCollision(Collision *c);
	

};