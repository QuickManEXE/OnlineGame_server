#include "Task.h"
#include "TaskManager.h"
#include "../GID.h"
#include <stdio.h>

//�f�t�H���g�R���X�g���N�^
Task::Task() :
	m_updateLink(eUp_Max,this),
	m_renderLink(eRd_Max,this),
	m_collLink(0, this),
	m_id(eId_Max),
	m_stopTime(0.0f),
	m_destroyFlg(false)
{
	
}

Task::Task(int id, int updatePrio, int renderPrio) :
	m_updateLink(updatePrio,this),
	m_renderLink(renderPrio,this),
	m_collLink(0,this),
	m_id(id),
	m_stopTime(0.0f),
	m_destroyFlg(false)
{
//	printf("CTask[%d] Prio[%d/%d]\n", id, updatePrio, renderPrio);
	//�^�X�N�쐬��A�����Ń}�l�[�W���[�ɓo�^
	TaskManager::GetInstance()->AddTask(this);
}

Task::~Task()
{
	
}

void Task::Update()
{
//	printf("Update[%d] Prio[%d]\n", m_id, m_updateLink.GetPriority());
}

void Task::PauseUpdate()
{
	//������
	/*
	�^�X�N�̒ʏ�X�V�ƒ�~�p�X�V��ʁX�Ŏ�����
	�q�b�g�X�g�b�v��C�x���g��~�Ȃǂ��X�V��ԂŎ���
	*/
}

void Task::Render()
{
//	printf("Render[%d] Prio:[%d]\n", m_id, m_renderLink.GetPriority());	
}

void Task::CheckCollision(Task *t)
{
	
}

void Task::ChangeUpdatePrio(int updatePrio)
{
	TaskManager::GetInstance()->ChangeUpdatePrio(this, updatePrio);
}

void Task::ChangeRenderPrio(int renderPrio)
{
	TaskManager::GetInstance()->ChangeRenderPrio(this, renderPrio);
}
