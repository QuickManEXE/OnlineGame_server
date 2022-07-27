#pragma once
#include "../stdafx.h"
#include "../System/Task.h"

//エフェクトクラス
class CEffect :public Task{
	CImage	img;
	CVector2D	pos;			//!座標
public:
	/*!
		@brief	コンストラクタ
		@param	pos			[in] 発生位置
		@retval	無し
	**/
	CEffect(CVector2D &pos);

	~CEffect();
	void Update();
	void Render();
};
