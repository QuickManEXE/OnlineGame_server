#pragma once

//Task�V�X�e���֓o�^����̂ɕK�v�ȃw�b�_�[�t�@�C��
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"
#include "../System/CollisionCall.h"
//Task�͌p���K�{�A
//�Փˌ�̃R�[���o�b�N�֐����p��(�C���^�[�t�F�C�X)
class CField : public Task,public CollisionCall{
private:

public:
	CField();

	//Task��Render���I�[�o�[���C�h
	void Render();

	//�Փ˃R�[���o�b�N���I�[�o�[���C�h
	void CallCollision(Collision *c);
	

};