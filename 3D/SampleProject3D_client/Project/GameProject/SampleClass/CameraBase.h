#pragma once
#include "../Base/Base.h"

class Camera;
class CameraBase {
public:
	//カメラ更新
	virtual void UpdateCamera(Camera* c) = 0;
};

class Camera : public Base {
	//現在使用中のカメラ
	CameraBase* mp_curret;
	//テスト用　3種類のカメラ
	CameraBase* mp_camera[3];
protected:
	CVector3D	m_eye, m_new_eye;	//視点
	CVector3D   m_at, m_new_at;		//注視点
	CVector3D	m_up, m_new_up;		//上方向ベクトル
	float		m_t;				//補間係数
public:
	//コンストラクタ
	Camera();
	//視点　注視点　UPベクトルを設定
	void SetParam(const CVector3D& eye, const CVector3D& at, const CVector3D& up);
	//更新処理
	void Update();
	//描画の処理
	void Draw();
	//使用するカメラの変更
	void ChangeCamera(CameraBase* c);
	//使用するカメラの変更
	void ChangeCamera(int i);

};