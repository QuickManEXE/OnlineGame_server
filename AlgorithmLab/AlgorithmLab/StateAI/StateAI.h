#pragma once
#include"StateMachine.h"
#include<vector>

template <typename T,typename TEnum>
class StateAI {
public:
	//登録ステートのリスト
	std::vector<State<T>*> state_vector;

	//ステートマシンの登録
	StateMachine<T>* stateMachine;

	void ChangeState(TEnum state) {

		//ステートマシンがない場合
		if (stateMachine == nullptr) {
			return;//弾く
		}

		//現在ステートを変える
		stateMachine->ChangeState(state_vector[(int)state]);

	}


	//現在のステートUpdateを実行
	void Update(){

		if (stateMachine != nullptr) {

			stateMachine->Update();

		}
	}

};