#pragma once
#include "../stdafx.h"
#include "../GID.h"
#include "../Global.h"
#include <list>

class Base {
protected:
	CModelObj	m_model;	//���f��
	CVector3D	m_pos;		//���W
	CVector3D	m_rot;		//��]�l
	bool		m_kill;		//�폜�t���O
	float		m_rad;		//���a
	int			m_type;		//���
	//���J�v�Z��
	CVector3D  m_lineS;
	CVector3D  m_lineE;
	static std::list<Base*> m_list;	//�Q�[���I�u�W�F�N�g�p�R���e�i
public:
	//�R���X�g���N�^
	//type : ���
	Base(int type);
	//�f�X�g���N�^
	virtual ~Base();
	//�폜�t���OON
	void SetKill();
	//��ނ̎擾
	int GetType() {
		return m_type;
	}
	//���W�̎擾
	CVector3D GetPos() {
		return m_pos;
	}
	//�ړ��̎擾
	void MovePos(const CVector3D& v) {
		m_pos += v;
	}
	//��]�l�̎擾
	CVector3D GetRot() {
		return m_rot;
	}
	//���a�̎擾
	float GetRad() {
		return m_rad;
	}
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//�I�u�W�F�N�g���m�̓����蔻�茟��
	virtual void HitCheck(Base* b);
	//���f���̂Ƃ̏Փ˔���
	void CollisionModel(CVector3D* pos, CVector3D* vec, float rad, CModel* model);
	//�J�v�Z���Ƌ��̏Փ˔���
	bool CollisionCapsuleToSphere(Base* b);
	//���ƃJ�v�Z���̏Փ˔���
	bool CollisionSphereToCapsule(Base* b);
	//�J�v�Z���̏Փ˔���
	bool CollisionCapsule(Base* b);
	//���̏Փ˔���
	bool CollisionSphere(Base* b);
	//�S�ẴI�u�W�F�N�g�̍폜
	static void KillALL();
	//�S�ẴI�u�W�F�N�g�̍폜�`�F�b�N
	static void CheckKillALL();
	//�S�ẴI�u�W�F�N�g�̍X�V
	static void UpdateALL();
	//�S�ẴI�u�W�F�N�g�̕`��
	static void DrawALL();
	//�S�ẴI�u�W�F�N�g�̓����蔻��
	static void HitCheckALL();
	//�I�u�W�F�N�g��ǉ�
	static void Add(Base* b);
	//�I�u�W�F�N�g�̌���
	static Base* FindObject(int type);
	//�t�����h�N���X
	friend class Base;
};
