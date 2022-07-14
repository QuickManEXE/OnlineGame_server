#pragma once
#include "../stdafx.h"
#include "../System/Task.h"

//�G�t�F�N�g�N���X
class CEffect :public Task{
	CImage	img;
	CVector2D	pos;			//!���W
public:
	/*!
		@brief	�R���X�g���N�^
		@param	pos			[in] �����ʒu
		@retval	����
	**/
	CEffect(CVector2D &pos);

	~CEffect();
	void Update();
	void Render();
};
