/**
* @Author	YukiYamaji
* @Day		17/11/18
* @Brief	è’ìÀåƒèoä«óù
*/

#ifndef COLLISION_CALL_GUARD
#define COLLISION_CALL_GUARD

class Collision;

class CollisionCall
{
public:
	CollisionCall() {};
	~CollisionCall() {};
	virtual void CallCollision(Collision *c) {};
};

#endif