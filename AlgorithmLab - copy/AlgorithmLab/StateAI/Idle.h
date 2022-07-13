#pragma once
#include"State.h"
#include"Charactor.h"


class StateIdle : public State<Charactor> {
public:
	StateIdle(Charactor* owner) : State(owner) {};

	int cnt;

	void Enter() {

		printf("アイドルの開始処理\n");

		cnt = 0;
	}


	void Execute() {

		printf("アイドルの実行処理\n");

		if (cnt++ >= 1) {
			
			owner->stateAI.ChangeState(eState::Attack);

		}

	}


	void Exit() {

		printf("アイドルの終了処理\n");

		cnt = 0;
	}

};