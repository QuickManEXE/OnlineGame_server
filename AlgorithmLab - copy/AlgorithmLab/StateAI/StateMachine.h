#pragma once
#include"State.h"

//ステート（状態）の基底クラス
//始まり
//実行中
//終わり
//の状態に別れる
template <typename T>
class StateMachine {
public:
	//現在のステート
	State<T>* currentState;

	//コンストラクタ
	StateMachine() {
		//現在のステートをnullに
		currentState = nullptr;

	};

	//現在のステートを取得
	State<T> GetCurrentState() {
		return currentState;
	}

	void Update() {

		//現在のステートが存在するなら
		if (currentState != nullptr) {

			//実行中のステートを呼び出す
			currentState->Execute();

		}

	}


	void ChangeState(State<T>* state) {

		//現在のステートがあるなら
		if (currentState != nullptr) {

			//終了処理を呼び出す
			currentState->Exit();
		}

		//現在のステートの変更
		currentState = state;

		//現在のステートの開始処理を呼ぶ
		currentState->Enter();
	}



};