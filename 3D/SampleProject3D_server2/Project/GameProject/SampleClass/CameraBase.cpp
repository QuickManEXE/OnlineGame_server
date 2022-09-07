#include "CameraBase.h"
#include "PointCamera.h"
#include "ThirdPersonCamera.h"
#include "OverTheShoulderCamera.h"
#include "../GID.h"


//コンストラクタ　オブジェクト生成時に呼ばれる
//　　　　　引数にpos(座標)とrot(回転値)を受け取る
//　　　　　　　　　　　　　　　　　　　　基底クラス（Base）へ種類の情報を渡す
Camera::Camera():Base(eId_Camera),m_t(1.0f){
	//いくつかの種類のカメラを生成
	mp_camera[0] = new OverTheShoulderCamera(Base::FindObject(eId_Player));
	mp_camera[1] = new ThirdPersonCamera(Base::FindObject(eId_Player));
	//切り替えテスト用定点カメラ
	mp_camera[2] = new PointCamera(CVector3D(0,200,200),CVector3D(100,0,0),CVector3D(0,1,0));
	mp_curret = mp_camera[0];

}

void Camera::SetParam(const CVector3D& eye, const CVector3D& at, const CVector3D& up)
{
	m_new_eye = eye;
	m_new_at = at;
	m_new_up = up;
}

void Camera::Update()
{
	//カメラ切り替えテスト
	if (PUSH(CInput::eMouseR)) {
		static int idx = 0;
		idx = (idx + 1) % 3;
		ChangeCamera(idx);
	}
	//補間係数を最大1.0fまで増加
	m_t = min(1.0f, m_t + 0.01f);
	//補間しながら更新
	m_eye = m_eye * (1 - m_t) + m_new_eye * m_t;
	m_at = m_at * (1 - m_t) + m_new_at * m_t;
	m_up = m_up * (1 - m_t) + m_new_up * m_t;
	//現在使用中のカメラで更新
	if (mp_curret) mp_curret->UpdateCamera(this);

}
void Camera::Draw()
{

	//位置と注視点を設定してカメラを更新
	CCamera::GetCurrent()->LookAt(m_eye, m_at, m_up);
}
void Camera::ChangeCamera(CameraBase* c)
{
	mp_curret = c;
	//切り替え時には補間係数を0からスタート
	m_t = 0.0f;
}
void Camera::ChangeCamera(int i)
{
	mp_curret = mp_camera[i];
	//切り替え時には補間係数を0からスタート
	m_t = 0.0f;
}
