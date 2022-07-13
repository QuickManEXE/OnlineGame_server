#include"Base_SmartPointer.h"

std::list<std::shared_ptr<Base_SmartPointer>> Base_SmartPointer::m_list;

void Base_SmartPointer::AddList(std::shared_ptr<Base_SmartPointer> _base)
{
	m_list.push_back(_base);
}

void Base_SmartPointer::UpdateAll()
{
	for (auto obj : m_list) {
		obj->Update();
	}
}

void Base_SmartPointer::CollisionCheckAll()
{
	for (auto itr1 = m_list.begin(); itr1 != m_list.end(); itr1++) {

		auto itr2 = itr1;
		itr2++;
		for (; itr2 != m_list.end(); itr2++) {

			(*itr1)->CollisionCheck(*itr2);
			(*itr2)->CollisionCheck(*itr1);

		}
	}

}

Base_SmartPointer::Base_SmartPointer(std::string _name)
{
	
	AddList(std::shared_ptr<Base_SmartPointer>(this));
	SetName(_name);
}

void Base_SmartPointer::Update()
{
	printf("%s‚ÌXV‚µ‚Ä‚¢‚Ü‚·\n",GetNameC());
}

void Base_SmartPointer::CollisionCheck(std::shared_ptr<Base_SmartPointer> _base)
{
	printf("%s‚ª“–‚½‚è”»’è‚µ‚Ä‚¢‚Ü‚·\n",GetNameC());
}
