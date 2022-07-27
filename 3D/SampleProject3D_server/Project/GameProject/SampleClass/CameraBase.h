#pragma once
#include "../Base/Base.h"

class Camera;
class CameraBase {
public:
	//�J�����X�V
	virtual void UpdateCamera(Camera* c) = 0;
};

class Camera : public Base {
	//���ݎg�p���̃J����
	CameraBase* mp_curret;
	//�e�X�g�p�@3��ނ̃J����
	CameraBase* mp_camera[3];
protected:
	CVector3D	m_eye, m_new_eye;	//���_
	CVector3D   m_at, m_new_at;		//�����_
	CVector3D	m_up, m_new_up;		//������x�N�g��
	float		m_t;				//��ԌW��
public:
	//�R���X�g���N�^
	Camera();
	//���_�@�����_�@UP�x�N�g����ݒ�
	void SetParam(const CVector3D& eye, const CVector3D& at, const CVector3D& up);
	//�X�V����
	void Update();
	//�`��̏���
	void Draw();
	//�g�p����J�����̕ύX
	void ChangeCamera(CameraBase* c);
	//�g�p����J�����̕ύX
	void ChangeCamera(int i);

};