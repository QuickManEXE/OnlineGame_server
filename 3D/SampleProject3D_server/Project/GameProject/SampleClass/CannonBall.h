#pragma once
#include "../stdafx.h"
#include "../Global.h"

#include "../Base/Base.h"

//�C�e�N���X
class CannonBall : public Base{
private:
	//Base�N���X�Œ�`�ς�
//	CModelObj	m_model;		//���f��
//	CVector3D	m_pos;			//���W
	CVector3D	m_vec;			//�ړ���
	int			m_cnt;			//���ŗp�J�E���^�[
public:
	/*!
	@brief	�R���X�g���N�^
	@param	pos				[in] �����ʒu
	@param	vec				[in] �ړ���
	**/
	CannonBall(const CVector3D& pos, const CVector3D& vec);
	/*!
	@brief	�f�X�g���N�^
	**/
	~CannonBall();
	/*!
	@brief	�X�V
	**/
	void Update();
	/*!
	@brief	�`��
	**/
	void Draw();
};

