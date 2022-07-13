#include<memory>
#include"Base_SmartPointer.h"
#include"../Player.h"
#include"../Enemy.h"


void main() {

	//ユニークポインター（所有権が1つだけ）
	//std::unique_ptr<int> u_ptr(new int(10));

	//別の作り方ユニークポインター　こちらのほうが間違いない
	std::unique_ptr<int> u_ptr1 = std::make_unique<int>(10);

	//シェアポインター（ほかのシェアポインターから参照できる）
	//std::shared_ptr<int> s_ptr(new int(15));

	//別の作り方シェアポインター　こちらのほうが間違いない
	std::shared_ptr<int> s_ptr1 = std::make_shared<int>(15);

	//ウィークポインター（シェアポインターだけでは循環参照がおきるので必要なポインター）
	std::weak_ptr<int> w_ptr;


	u_ptr1.get();

	printf("%d\n", (*u_ptr1));

	if (u_ptr1) {

		printf("ポインター\n");
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