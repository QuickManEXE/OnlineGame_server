#pragma once
#include"State.h"

//�X�e�[�g�i��ԁj�̊��N���X
//�n�܂�
//���s��
//�I���
//�̏�Ԃɕʂ��
template <typename T>
class StateMachine {
public:
	//���݂̃X�e�[�g
	State<T>* currentState;

	//�R���X�g���N�^
	StateMachine() {
		//���݂̃X�e�[�g��null��
		currentState = nullptr;

	};

	//���݂̃X�e�[�g���擾
	State<T> GetCurrentState() {
		return currentState;
	}

	void Update() {

		//���݂̃X�e�[�g�����݂���Ȃ�
		if (currentState != nullptr) {

			//���s���̃X�e�[�g���Ăяo��
			currentState->Execute();

		}

	}


	void ChangeState(State<T>* state) {

		//���݂̃X�e�[�g������Ȃ�
		if (currentState != nullptr) {

			//�I���������Ăяo��
			currentState->Exit();
		}

		//���݂̃X�e�[�g�̕ύX
		currentState = state;

		//���݂̃X�e�[�g�̊J�n�������Ă�
		currentState->Enter();
	}



};