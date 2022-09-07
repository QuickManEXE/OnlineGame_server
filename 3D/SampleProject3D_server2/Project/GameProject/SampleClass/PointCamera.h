#pragma once
#include "CameraBase.h"

//テスト用定点カメラ
class PointCamera:public CameraBase {
	CVector3D m_eye;
	CVector3D m_at;
	CVector3D m_up;
public:
	//コンストラクタ
	//視点、注視点,Upベクトルを設定して定点カメラを作成
	PointCamera(const CVector3D& eye, const CVector3D& at, const CVector3D& up);
	//カメラ更新
	void UpdateCamera(Camera* c);

};