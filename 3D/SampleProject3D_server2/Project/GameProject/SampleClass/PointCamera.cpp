#include "PointCamera.h"
#include "../GID.h"
//コンストラクタ　オブジェクト生成時に呼ばれる
PointCamera::PointCamera(const CVector3D& eye, const CVector3D& at, const CVector3D& up):
m_eye(eye),m_at(at),m_up(up){


}
//カメラ挙動
void PointCamera::UpdateCamera(Camera* c) {

	//カメラ本体へデータを渡す
	c->SetParam(m_eye, m_at, m_up);
}