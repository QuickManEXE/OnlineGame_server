#pragma once
#include"SmartPointer\Base_SmartPointer.h"



class Player : public Base_SmartPointer{
public:

	Player(std::string _name);

	virtual void CollisionCheck(std::shared_ptr<Base_SmartPointer> _base)override;
};