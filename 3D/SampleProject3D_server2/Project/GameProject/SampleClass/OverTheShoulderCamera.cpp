#include "OverTheShoulderCamera.h"
#include "../GID.h"

//コンストラクタ　オブジェクト生成時に呼ばれる
OverTheShoulderCamera::OverTheShoulderCamera(Base* target) {
	mp_target = target;

}
//カメラ挙動
void OverTheShoulderCamera::UpdateCamera(Camera* c) {
	CVector3D pos = mp_target->GetPos();
	CVector3D rot = mp_target->GetRot();


	CMatrix m = CMatrix::MTranselate(pos) * CMatrix::MTranselate(CVector3D(0, 80, 0)) * CMatrix::MRotation(rot) * CMatrix::MTranselate(CVector3D(-40, 0, -100));

	//カメラ本体へデータを渡す
	c->SetParam(m.GetPosition(), m.GetPosition() + m.GetFront(), m.GetUp());
}
/*
//コンストラクタ　オブジェクト生成時に呼ばれる
OverTheShoulderCamera::OverTheShoulderCamera(Base* target) :Base(eId_Camera) {
	mp_target = target;

}
//カメラ挙動
void OverTheShoulderCamera::Update() {
	CVector3D pos = mp_target->GetPos();
	CVector3D rot = mp_target->GetRot();


	CMatrix m = CMatrix::MTranselate(pos) * CMatrix::MTranselate(CVector3D(0, 80, 0)) * CMatrix::MRotation(rot) * CMatrix::MTranselate(CVector3D(-40, 0, -100));

	//視点、注視点へと変換
	CCamera::GetCurrent()->LookAt(m.GetPosition(), m.GetPosition() + m.GetFront(), m.GetUp());

}
*/
