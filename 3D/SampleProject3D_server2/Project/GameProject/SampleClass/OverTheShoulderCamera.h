#pragma once

#include "CameraBase.h"
class OverTheShoulderCamera:public CameraBase {
	//��������I�u�W�F�N�g
	Base* mp_target;
public:
	//�R���X�g���N�^
	OverTheShoulderCamera(Base* target);
	//�J�����X�V
	void UpdateCamera(Camera* c);

};

/*
#include "../Base/Base.h"

class OverTheShoulderCamera :public Base {
	//��������I�u�W�F�N�g
	Base* mp_target;
public:
	//�R���X�g���N�^
	OverTheShoulderCamera(Base* target);
	//�J�����X�V
	void Update();

};
*/