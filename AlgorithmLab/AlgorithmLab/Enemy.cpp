#include "Enemy.h"
#include"Player.h"

Enemy::Enemy(std::string _name) : Base_SmartPointer(_name)
{
}

void Enemy::CollisionCheck(std::shared_ptr<Base_SmartPointer> _base)
{
	if (std::shared_ptr<Player> p = std::dynamic_pointer_cast<Player>(_base)) {

		const char* a_name = this->GetNameC();
		const char* b_name = (*p).GetNameC();

		printf("%s‚Í%s‚É“–‚½‚Á‚Ä‚¢‚Ü‚·\n", a_name, b_name);

	}
}
