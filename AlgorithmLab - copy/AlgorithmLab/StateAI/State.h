#pragma once
#include<stdio.h>

//ステート（状態）の基底クラス
//始まり
//実行中
//終わり
//の状態に別れる
template <typename T>
class State {
public:

	T* owner;

	State<T>(T* owner) {

		this->owner = owner;

	}

	//ステート開始時の処理
	virtual void Enter() {

		printf("ステートの開始\n");

	}

	//ステート中の処理
	virtual void Execute() {

		printf("ステートの実行中\n");
	}

	//ステート終了時の処理
	virtual void Exit() {

		printf("ステートの終了\n");

	}




};