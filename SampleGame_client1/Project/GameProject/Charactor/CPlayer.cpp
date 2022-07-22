#include "CPlayer.h"
#include "../Bullet/CBullet.h"
#include "../Charactor/CEnemy.h"
#include "../Effect/CEffect.h"
using namespace Player;
CPlayer::CPlayer(int id,const float x, const float y,PlayerDataManager::PlayerData* pd):CPlayer(id,CVector2D(x,y),pd) {
}
CPlayer::CPlayer(int id,const CVector2D p,PlayerDataManager::PlayerData* pd):Task(eId_Player,eUp_Player,eRd_Player), 
collision(&pos,28.0f,this,eLayer_Player)
{
	//������
	//�v���C���[�摜�̎擾
	img = COPY_RESOURCE("Player",CImage);
	img.SetCenter(32, 32);

	//�v���C���[�̏����ʒu
	pos = p;
	member_id = id;

	m_playerData = pd;
	
	
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Update()
{
	pos = m_playerData->pos;
	//�X�V����
	//if �Ƃ̑g�ݍ��킹
	//�e�����L�[�������Ă����
	//HOLD(CInput::eUp) HOLD(CInput::eDown) HOLD(CInput::eLeft) HOLD(CInput::eRight)
	//�{�^�� Z						X			        C
	//PUSH(CInput::eButton1),PUSH(CInput::eButton2),PUSH(CInput::eButton3)
	
	//�v���C���[�̈ʒu
	//pos.x ���̈ʒu�@	pos.y�@�c�̈ʒu
	if (m_playerData->key[CInput::eRight]) {
		m_playerData->pos.x += 4;
	}
	if (m_playerData->key[CInput::eLeft]) {
		m_playerData->pos.x -= 4;
	}

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
}

void CPlayer::Render()
{

	img.SetPos(pos);

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


