#include"StateAIBase.h"
#include"Idle.h"
#include"Attack.h"
#include"StopWatch.h"
#include<string.h>
#include<time.h>
#include"Charactor.h"


void main() {

	//���̃L�����N�^�[�̎���int �i�{���Ȃ�Enemy�Ƃ��j
	Charactor chara;

	//�X�e�[�g�}�V����ݒ�
	chara.stateAI.stateMachine = new StateMachine<Charactor>;

	//�X�e�[�g�}�V���̃X�e�[�g�z���_�[�ɃX�e�[�g������ienum�̔ԍ��ƘA�����Ă�̂ł���鏇�Ԃɒ��Ӂj
	chara.stateAI.state_vector.push_back(new StateIdle(&chara));
	chara.stateAI.state_vector.push_back(new StateAttack(&chara));


	//�����������@�܂���idle�ɐݒ�
	chara.stateAI.ChangeState(eState::Idle);

	//�X�e�[�g�̃A�b�v�f�[�g���Ăԁi1�񂾂��j
	chara.stateAI.Update();



	printf("\n\n\n�����������\n\n\n");

	StopWatch watch;

	float count = 0;
	//���[�v
	while (count<=1) {

		watch.Reset();



		chara.stateAI.Update();

		count +=  watch.Sec();

	}




}