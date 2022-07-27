#include "CEnemy.h"
#include "../Bullet/CBullet.h"
#include "../Effect/CEffect.h"
using namespace Enemy;
CEnemy::CEnemy(CVector2D p):Task(eId_Enemy,eUp_Enemy,eRd_Enemy),
collision(&pos,15.0f,this,eLayer_Enemy)
{
	img = COPY_RESOURCE("Enemy",CImage);
	pos = p;
	img.SetCenter(16, 16);
	cnt = 0;

}

CEnemy::CEnemy(float x, float y) :CEnemy(CVector2D(x, y))
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update()
{
	//�J�E���^�[ [1]���Z
	//�X�V���ɃJ�E���g�A�b�v
	cnt++;

	//�G�̓�������낤




}

void CEnemy::Render()
{
	img.SetPos(pos);
	img.Draw();
}

void CEnemy::CallCollision(Collision * c)
{
	if (c->GetObj()->GetID() == eId_Enemy) {
		//�v���C���[���m�̓����蔻��
		CEnemy *p = static_cast<CEnemy*>(c->GetObj());
		CVector2D v = p->GetPos() - pos;
		float l = v.Length();
		if (l > 0) {
			pos -= v / l * (28 + 28 - l) / 2;
		}
		else {
			pos -= CVector2D(1, 0.1);
		}
	}
	else {
		new CEffect(pos);
		//�Փˎ�����
		SetKill();
	}


}


