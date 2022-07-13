#pragma once
#include"State.h"
#include"Charactor.h"


class StateIdle : public State<Charactor> {
public:
	StateIdle(Charactor* owner) : State(owner) {};

	int cnt;

	void Enter() {

		printf("�A�C�h���̊J�n����\n");

		cnt = 0;
	}


	void Execute() {

		printf("�A�C�h���̎��s����\n");

		if (cnt++ >= 1) {
			
			owner->stateAI.ChangeState(eState::Attack);

		}

	}


	void Exit() {

		printf("�A�C�h���̏I������\n");

		cnt = 0;
	}

};