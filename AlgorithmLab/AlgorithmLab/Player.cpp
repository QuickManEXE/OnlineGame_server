#include "Player.h"
#include"Enemy.h"

Player::Player(std::string _name) : Base_SmartPointer(_name)
{


}

void Player::CollisionCheck(std::shared_ptr<Base_SmartPointer> _base)
{
	
	if (std::shared_ptr<Enemy> e = std::dynamic_pointer_cast<Enemy>(_base)) {

		const char* a_name = this->GetNameC();
		const char* b_name = (*e).GetNameC();

		printf("%s‚Í%s‚É“–‚½‚Á‚Ä‚¢‚Ü‚·\n", a_name, b_name);

	}
}
