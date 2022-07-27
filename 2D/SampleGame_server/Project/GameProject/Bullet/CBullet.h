#pragma once
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"
#include "../System/CollisionCall.h"
//�e�N���X
class CBulletBase : public Task, public CollisionCall {
public:
	CImage		img;
	CVector2D	pos;			//�ʒu
	CVector2D	dir;			//�����x�N�g��
	float		speed;		//����
	int			cnt;			//�������ŗp�J�E���^�[
	Collision	collision;

public:
	CBulletBase(const CVector2D &pos, const float ang, float speed, int layer);
	CBulletBase(const CVector2D &pos, const CVector2D &dir, float speed, int layer);
	~CBulletBase();
	void Update();
	void Render();

	//CollisionCall���I�[�o�[���C�h
	//�ڐG���ɌĂ΂��
	void CallCollision(Collision *c);

};
namespace Player {
	//�e�N���X
	class CBullet : public CBulletBase {
	public:
	
	public:
		CBullet(const CVector2D &pos, const float ang, float speed);
		CBullet(const CVector2D &pos, const CVector2D &dir, float speed);
	};
}

namespace Enemy {
	//�e�N���X
	class CBullet : public CBulletBase {
	public:

	public:
		CBullet(const CVector2D &pos, const float ang, float speed);
		CBullet(const CVector2D &pos, const CVector2D &dir, float speed);
	};
}
