#include "TaskManager.h"
#include "RenderTaskManager.h"
#include"CollisionTaskManager.h"

// printf_s ���g�p���邽�߃C���N���[�h
#include <iostream>

// �R���X�g���N�^
Task::Task(int _priority, const char * _name) :
	mp_Prev(nullptr),
	mp_Next(nullptr),
	m_Priority(_priority),
	m_IsPause(false),
	m_Name(_name),
	m_Protect(false),
	m_Kill(false)
{
	// �^�X�N�}�l�[�W���[�ɓo�^
	TaskManager::GetInstance()->AddTask(this);
}

Task::Task() :
	mp_Prev(nullptr),
	mp_Next(nullptr),
	m_Priority(0),
	m_IsPause(false),
	m_Name("Task"),
	m_Kill(false)
{
	// �^�X�N�}�l�[�W���[�ɓo�^
	TaskManager::GetInstance()->AddTask(this);
}

// �f�X�g���N�^
Task::~Task()
{
}

void Task::SetProtect(bool _isProtect)
{
	m_Protect = _isProtect;
}

void Task::SetKill()
{
	if(!m_Protect)m_Kill = true;
}

void Task::Kill()
{
	// �X�V���X�g����O���č폜���X�g�ɒǉ�����
	TaskManager::GetInstance()->AddKill(this);
	
	// �`�惊�X�g����O��
	RenderTaskManager::GetInstance()->RemoveTask(this);

	// �Փ˔��胊�X�g����O��
	CollisionTaskManager::GetInstance()->RemoveTask(this);

}

void Task::SetPause(bool _isPause)
{
	m_IsPause = _isPause;
}

int Task::GetPriority()const
{
	return m_Priority;
}

bool Task::IsPause()const
{
	return m_IsPause;
}

const char * Task::GetName()const
{
	return m_Name;
}

void Task::Update()
{
	//printf_s("%s �͊���N���X�̍X�V���Ăяo���Ă��܂��B\n", m_Name);

}