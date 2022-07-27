#include "ThirdPersonCamera.h"
#include "../GID.h"

//コンストラクタ　オブジェクト生成時に呼ばれる
ThirdPersonCamera::ThirdPersonCamera(Base* target):m_dist(200) {
	mp_target = target;

}
//カメラ挙動
void ThirdPersonCamera::UpdateCamera(Camera* c) {

	CVector3D at = mp_target->GetPos();
	//注視点　上に視点を移動する
	CVector3D cam_at = at + CVector3D(0, 80, 0);
	//マウス操作からカメラを回転----
	//マウス移動量
	CVector2D mouse_vec = CInput::GetMouseVec();
	m_cam_rot.y += mouse_vec.x * -0.01f;
	m_cam_rot.x += mouse_vec.y * 0.01f;
	m_cam_rot.x = min(DtoR(45), max(DtoR(-10), m_cam_rot.x));

	//カメラの距離を変更
	m_dist += CInput::GetMouseWheel() * 5.0f;
	//カメラの位置を計算
	CVector3D dir = CMatrix::MRotation(m_cam_rot).GetFront();
	//CVector3D dir(sin(cam_rot.y),0,cos(cam_rot.y));
	m_cam_pos = cam_at + dir * -m_dist;
	//カメラ本体へデータを渡す
	c->SetParam(m_cam_pos, at, CVector3D(0, 1, 0));
}

/*
//コンストラクタ　オブジェクト生成時に呼ばれる
ThirdPersonCamera::ThirdPersonCamera(Base* target) :Base(eId_Camera),m_dist(200) {
	mp_target = target;

}
//カメラ挙動
void ThirdPersonCamera::Update() {
	//ここ作る
	CVector3D at = mp_target->GetPos();
	//注視点　上に視点を移動する
	CVector3D cam_at = at + CVector3D(0, 80, 0);
	//マウス操作からカメラを回転----
	//マウス移動量
	CVector2D mouse_vec = CInput::GetMouseVec();
	m_cam_rot.y += mouse_vec.x * -0.01f;
	m_cam_rot.x += mouse_vec.y * 0.01f;
	//if文による制限
	//if (cam_rot.x > DtoR(45)) cam_rot.x = DtoR(45);
	//if (cam_rot.x < DtoR(-10)) cam_rot.x = DtoR(-10);
	//min,max関数による制限
	//cam_rot.x = min(DtoR(45), cam_rot.x);
	//cam_rot.x = max(DtoR(-10), cam_rot.x);
	//clamp関数と同等の処理
	m_cam_rot.x = min(DtoR(45), max(DtoR(-10), m_cam_rot.x));

	//カメラの距離を変更
	m_dist += CInput::GetMouseWheel() * 5.0f;
	//カメラの位置を計算
	CVector3D dir = CMatrix::MRotation(m_cam_rot).GetFront();
	//CVector3D dir(sin(cam_rot.y),0,cos(cam_rot.y));
	m_cam_pos = cam_at + dir * -m_dist;
	//位置と注視点を設定してカメラを更新
	CCamera::GetCurrent()->LookAt(m_cam_pos, cam_at, CVector3D(0, 1, 0));
}
*/