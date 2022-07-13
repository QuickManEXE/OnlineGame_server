#include "CollisionTaskManager.h"

#include <assert.h>

CollisionTask::CollisionTask() :
	mp_Prev(nullptr),
	mp_Next(nullptr),
	m_Priority(0),
	m_Name(nullptr),
	mp_Task(nullptr),
	m_Func(nullptr),
	m_IsPause(false)
{
}

CollisionTask::~CollisionTask()
{
	// ���X�g����O��
	CollisionTaskManager::GetInstance()->RemoveTask(m_LayerID,this);
}

void CollisionTask::CollisionCheck(CollisionTask* _task)
{
	// �֐��|�C���^�Ăяo��
	(mp_Task->*m_Func)(_task);
}

void CollisionTask::RegistCollision(int _layerID,Task* _task, CollisionFunc _func, int _priority, const char* _name)
{
	// �^�X�N�|�C���^���֐��|�C���^�����ɐݒ肳��Ă���ꍇ�͌x��
	assert(((m_Func == nullptr) && (mp_Task == nullptr)));

	// �^�X�N�|�C���^�Ɗ֐��|�C���^�̂ǂ��炩�ł�null�̏ꍇ�͌x��
	assert(((_func != nullptr) && (_task != nullptr)));

	// �ϐ��ݒ�
	mp_Task = _task;
	m_Func = _func;
	m_Priority = _priority;
	m_Name = _name;
	m_LayerID = _layerID;

	// DrawTaskManager�ɓo�^
	CollisionTaskManager::GetInstance()->AddCollisionTask(m_LayerID,this);
}

void CollisionTask::Remove()
{
	// ���X�g����O��
	CollisionTaskManager::GetInstance()->RemoveTask(m_LayerID,this);

	// �ϐ�������
	mp_Task = nullptr;
	m_Func = nullptr;
	m_Priority = 0;
	m_Name = "";
}

void CollisionTask::ChangePriority(int _priority)
{
	// �o�^����Ă���ꍇ�̂ݗD��x�ύX
	if (IsRegist())
	{
		m_Priority = _priority;
		CollisionTaskManager::GetInstance()->ChangePriority(m_LayerID,this);
	}
}

void CollisionTask::SetPause(bool _isPause)
{
	m_IsPause = _isPause;
}

bool CollisionTask::IsRegist()const
{
	// �^�X�N�|�C���^�Ɗ֐��|�C���^���ݒ肳��Ă���ꍇ�͓o�^����Ă��锻��
	return (mp_Task || m_Func);
}

int CollisionTask::GetPriority()const
{
	return m_Priority;
}

bool CollisionTask::IsPause()const
{
	return m_IsPause;
}

const char* CollisionTask::GetName()const
{
	return m_Name;
}

Task* CollisionTask::GetTask()
{
	return mp_Task;
}

