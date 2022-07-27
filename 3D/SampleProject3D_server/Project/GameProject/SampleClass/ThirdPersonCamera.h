#pragma once

#include "CameraBase.h"
class ThirdPersonCamera:public CameraBase {
	//カメラの位置
	CVector3D m_cam_pos;
	//カメラの回転値
	CVector3D m_cam_rot;
	//カメラの距離
	float m_dist;
	//注視するオブジェクト
	Base* mp_target;
public:
	//コンストラクタ
	ThirdPersonCamera(Base* target);
	//カメラ更新
	void UpdateCamera(Camera* c);

};

/*
#include "../Base/Base.h"

class ThirdPersonCamera :public Base {
	//カメラの位置
	CVector3D m_cam_pos;
	//カメラの回転値
	CVector3D m_cam_rot;
	//カメラの距離
	float m_dist;
	//注視するオブジェクト
	Base* mp_target;
public:
	//コンストラクタ
	ThirdPersonCamera(Base* target);
	//カメラ更新
	void Update();

};
*/