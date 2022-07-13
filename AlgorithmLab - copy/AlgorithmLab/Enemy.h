#pragma once
#include"SmartPointer\Base_SmartPointer.h"



class Enemy : public Base_SmartPointer {
public:

	Enemy(std::string _name);

	virtual void CollisionCheck(std::shared_ptr<Base_SmartPointer> _base)override;
};