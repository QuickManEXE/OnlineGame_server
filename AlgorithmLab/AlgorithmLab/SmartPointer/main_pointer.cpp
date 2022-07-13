#include<memory>
#include"Base_SmartPointer.h"
#include"../Player.h"
#include"../Enemy.h"


void main() {

	//���j�[�N�|�C���^�[�i���L����1�����j
	//std::unique_ptr<int> u_ptr(new int(10));

	//�ʂ̍������j�[�N�|�C���^�[�@������̂ق����ԈႢ�Ȃ�
	std::unique_ptr<int> u_ptr1 = std::make_unique<int>(10);

	//�V�F�A�|�C���^�[�i�ق��̃V�F�A�|�C���^�[����Q�Ƃł���j
	//std::shared_ptr<int> s_ptr(new int(15));

	//�ʂ̍����V�F�A�|�C���^�[�@������̂ق����ԈႢ�Ȃ�
	std::shared_ptr<int> s_ptr1 = std::make_shared<int>(15);

	//�E�B�[�N�|�C���^�[�i�V�F�A�|�C���^�[�����ł͏z�Q�Ƃ�������̂ŕK�v�ȃ|�C���^�[�j
	std::weak_ptr<int> w_ptr;


	u_ptr1.get();

	printf("%d\n", (*u_ptr1));

	if (u_ptr1) {

		printf("�|�C���^�[\n");
	}

	u_ptr1.reset(new int(20));

	printf("%d\n", *u_ptr1);

	new Player("Player");
	new Enemy("Enemy");
	new Base_SmartPointer("NPC");


	int loop[3];
	for (auto i : loop) {

		Base_SmartPointer::UpdateAll();

		Base_SmartPointer::CollisionCheckAll();

	}


}