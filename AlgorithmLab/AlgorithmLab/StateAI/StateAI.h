#pragma once
#include"StateMachine.h"
#include<vector>

template <typename T,typename TEnum>
class StateAI {
public:
	//�o�^�X�e�[�g�̃��X�g
	std::vector<State<T>*> state_vector;

	//�X�e�[�g�}�V���̓o�^
	StateMachine<T>* stateMachine;

	void ChangeState(TEnum state) {

		//�X�e�[�g�}�V�����Ȃ��ꍇ
		if (stateMachine == nullptr) {
			return;//�e��
		}

		//���݃X�e�[�g��ς���
		stateMachine->ChangeState(state_vector[(int)state]);

	}


	//���݂̃X�e�[�gUpdate�����s
	void Update(){

		if (stateMachine != nullptr) {

			stateMachine->Update();

		}
	}

};