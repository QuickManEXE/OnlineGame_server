#include "CPlayer.h"
#include "../Bullet/CBullet.h"
#include "../Charactor/CEnemy.h"
#include "../Effect/CEffect.h"
using namespace Player;
CPlayer::CPlayer(const float x, const float y):CPlayer(CVector2D(x,y)) {
}
CPlayer::CPlayer(const CVector2D p):Task(eId_Player,eUp_Player,eRd_Player), 
collision(&pos,28.0f,this,eLayer_Player)
{
	//������
	//�v���C���[�摜�̎擾
	img = COPY_RESOURCE("Player",CImage);
	img.SetCenter(32, 32);

	//�v���C���[�̏����ʒu
	pos = p;
	soket.pos = pos;

	soket.Init();
	//soket.Run();
}

CPlayer::~CPlayer()
{
	soket.Finalize();
}

void CPlayer::Update()
{

	//�X�V����
	//printf("�����̏������J��Ԃ����s���Ă��܂�");
	//if �Ƃ̑g�ݍ��킹
	//�e�����L�[�������Ă����
	//HOLD(CInput::eUp) HOLD(CInput::eDown) HOLD(CInput::eLeft) HOLD(CInput::eRight)
	//�{�^�� Z						X			        C
	//PUSH(CInput::eButton1),PUSH(CInput::eButton2),PUSH(CInput::eButton3)
	
	//�v���C���[�̈ʒu
	//pos.x ���̈ʒu�@	pos.y�@�c�̈ʒu
	/*if (HOLD(CInput::eRight)) {
		pos.x += 4;
	}
	if (HOLD(CInput::eLeft)) {
		pos.x -= 4;
	}*/
	/*if (HOLD(CInput::eRight)) {
		soket.pos.x += 4;
	}
	if (HOLD(CInput::eLeft)) {
		soket.pos.x -= 4;
	}*/


	if (PUSH(CInput::eButton1)) {
		new CBullet(pos, 180, 5);			//�^��֌���
	}

	//�e����     �ʒu�@���ˊp�@����
	//new CBullet(pos, 0, 5);			//�^���Ɍ���
	//new CBullet(pos, 180, 5);			//�^��֌���
	

	//�G����       x�@y
	//new CEnemy(500,200);				//(500,200)�̏ꏊ�֓G�𐶐�����
	
	//�v���C���[���� x�@y
	//new CPlayer(pos);				//�����ꏊ�Ƀv���C���[�𐶐�����
	

	soket.Run();
	
}

void CPlayer::Render()
{
	//CVector3D pos3D = soket.RecvRenderUpdateData();
	//CVector2D pos2D(pos3D.x, pos3D.y);
	
	//pos = CVector2D(soket.pos.x, soket.pos.y);
	img.SetPos(soket.pos.x,soket.pos.y);

	//�`�揈��
	img.Draw();
}

void CPlayer::CallCollision(Collision * c)
{
	if (c->GetObj()->GetID() == eId_Player) {
		//�v���C���[���m�̓����蔻��
		CPlayer *p = static_cast<CPlayer*>(c->GetObj());
		CVector2D v =  p->GetPos() - pos;
		float l = v.Length();
		if (l > 0) {
			pos -= v/l * (28 + 28 - l)/2;
		} else {
			pos -= CVector2D(1, 0.1);
		}
	} else {
		new CEffect(pos);
		//�Փˎ�����
		SetKill();
	}
}


