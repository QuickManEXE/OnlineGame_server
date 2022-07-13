#include"RenderTaskManager.h"

#include <assert.h>

RenderTask::RenderTask():
	mp_Prev(nullptr),
	mp_Next(nullptr),
	m_Priority(0),
	m_Name(nullptr),
	mp_Task(nullptr),
	m_Func(nullptr),
	m_IsPause(false)
{
}

RenderTask::~RenderTask()
{
	// ���X�g����O��
	RenderTaskManager::GetInstance()->RemoveTask(this);
}

void RenderTask::Render()
{
	// �֐��|�C���^�Ăяo��
	(mp_Task->*m_Func)();
}

void RenderTask::RegistRender(Task * _task, RenderFunc _func, int _priority, const char * _name)
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

	// DrawTaskManager�ɓo�^
	RenderTaskManager::GetInstance()->AddRenderTask(this);
}

void RenderTask::Remove()
{
	// ���X�g����O��
	RenderTaskManager::GetInstance()->RemoveTask(this);

	// �ϐ�������
	mp_Task = nullptr;
	m_Func = nullptr;
	m_Priority = 0;
	m_Name = "";
}

void RenderTask::ChangePriority(int _priority)
{
	// �o�^����Ă���ꍇ�̂ݗD��x�ύX
	if (IsRegist())
	{
		m_Priority = _priority;
		RenderTaskManager::GetInstance()->ChangePriority(this);
	}
}

void RenderTask::SetPause(bool _isPause)
{
	m_IsPause = _isPause;
}

bool RenderTask::IsRegist()const
{
	// �^�X�N�|�C���^�Ɗ֐��|�C���^���ݒ肳��Ă���ꍇ�͓o�^����Ă��锻��
	return (mp_Task || m_Func);
}

int RenderTask::GetPriority()const
{
	return m_Priority;
}

bool RenderTask::IsPause()const
{
	return m_IsPause;
}

const char * RenderTask::GetName()const
{
	return m_Name;
}
