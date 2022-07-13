#include "../stdafx.h"
#include "Collision.h"
#include "../GID.h"
#include "TaskManager.h"
#include <assert.h>
//�Ίp����͓����l��ݒ�
char Collision::m_layer_mask[eLayer_Max][eLayer_Max] = {
  // P E F BP BE
	{1,1,0,0,1},	// P
	{1,1,0,1,0},	// E
	{0,0,0,0,0},	// F
	{0,1,0,0,1},	// BP
	{1,0,0,1,0},	// BE
};


Collision::Collision(CVector2D *p, float rad, CollisionCall *obj, unsigned int body) :
	Task(eId_Collision, eUp_Collision, eRd_Collision),
	mp_obj(nullptr),
	m_type(0), m_active(true)
{
	mp_obj		= obj;
	m_shpere.pos = p;
	m_shpere.rad = rad;
	m_type		= eCollision_Shpere;
	m_body		= body;
	//�Փ˔���o�^
	TaskManager::GetInstance()->AddColl(this);
}

Collision::~Collision()
{
	TaskManager::GetInstance()->Remove(this);
}

void Collision::CheckCollision(Task * t)
{
	//�^�X�N���Փ˔���ɃL���X�g
	Collision *c = dynamic_cast<Collision*>(t);
	//�f�o�b�O
	assert(t);
	//�Փ˃t���OOFF
	bool hit = false;
	//�Փːݒ肳��Ă��Ȃ����͓̂�����Ȃ�
	if (!m_layer_mask[m_body][c->m_body] || 
		!m_active || !c->m_active) return;
	//�`��^�C�v����
	switch (m_type) 
	{
	case eCollision_Shpere:
		switch (c->m_type) 
		{
		case eCollision_Shpere:
			hit = CollosionShpere(this, c);
			break;
		default:
			assert(false);
			break;
		}
		break;
	}
	//�q�b�g�t���OON��
	if (hit)
	{
		//�����̏Փˏ����ďo
		mp_obj->CallCollision(c);
		c->mp_obj->CallCollision(this);
	}
}

bool Collision::CollosionShpere(Collision *c1, Collision *c2)
{
	CVector2D v = *c1->m_shpere.pos - *c2->m_shpere.pos;
	if(v.LengthSq()>pow(c1->m_shpere.rad+ c2->m_shpere.rad,2))
		return false;
	return true;
}

