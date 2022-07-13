#include"StateAIBase.h"
#include"Idle.h"
#include"Attack.h"
#include"StopWatch.h"
#include<string.h>
#include<time.h>
#include"Charactor.h"


void main() {

	//仮のキャラクターの実体int （本当ならEnemyとか）
	Charactor chara;

	//ステートマシンを設定
	chara.stateAI.stateMachine = new StateMachine<Charactor>;

	//ステートマシンのステートホルダーにステートを入れる（enumの番号と連動してるのでいれる順番に注意）
	chara.stateAI.state_vector.push_back(new StateIdle(&chara));
	chara.stateAI.state_vector.push_back(new StateAttack(&chara));


	//初期化処理　まずはidleに設定
	chara.stateAI.ChangeState(eState::Idle);

	//ステートのアップデートを呼ぶ（1回だけ）
	chara.stateAI.Update();



	printf("\n\n\nここから実験\n\n\n");

	StopWatch watch;

	float count = 0;
	//ループ
	while (count<=1) {

		watch.Reset();



		chara.stateAI.Update();

		count +=  watch.Sec();

	}




}