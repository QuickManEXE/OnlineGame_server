#pragma once

#include "CameraBase.h"
class OverTheShoulderCamera:public CameraBase {
	//注視するオブジェクト
	Base* mp_target;
public:
	//コンストラクタ
	OverTheShoulderCamera(Base* target);
	//カメラ更新
	void UpdateCamera(Camera* c);

};

/*
#include "../Base/Base.h"

class OverTheShoulderCamera :public Base {
	//注視するオブジェクト
	Base* mp_target;
public:
	//コンストラクタ
	OverTheShoulderCamera(Base* target);
	//カメラ更新
	void Update();

};
*/