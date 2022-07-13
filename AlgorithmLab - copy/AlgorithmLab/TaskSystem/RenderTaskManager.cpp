#include "RenderTaskManager.h"

#include <assert.h>

RenderTaskManager* RenderTaskManager::mp_Instance;

RenderTaskManager * RenderTaskManager::GetInstance()
{
	if (!mp_Instance)
	{
		mp_Instance = new RenderTaskManager();
	}
	return mp_Instance;
}

void RenderTaskManager::ReleaseInstance()
{
	// �^�X�N���폜����Ă��Ȃ��\��������܂��B(TaskManager�̕��Ń^�X�N���폜����Ƃ��Ɉꏏ�ɊO���Ă���͂�)
	assert(!mp_Instance->mp_FirstList);

	delete mp_Instance;
	mp_Instance = nullptr;
}

RenderTaskManager::RenderTaskManager():
	mp_FirstList(nullptr)
{
}

RenderTaskManager::~RenderTaskManager()
{
}

void RenderTaskManager::RenderAll()
{
	// �X�V(�`��)
	RenderTask* currentTask = mp_FirstList;
	
	// 
	while (currentTask)
	{
		// �ꎞ��~���Ă��Ȃ��ꍇ�͕`��
		if (!currentTask->m_IsPause)
		{
			currentTask->Render();
		}

		// ���̃^�X�N
		currentTask = currentTask->mp_Next;
	}
}

void RenderTaskManager::AddRenderTask(RenderTask * _task)
{
	// �擪�|�C���^��null�̏ꍇ�͐擪�|�C���^�ɐݒ肵�Ēǉ��I��
	if (!mp_FirstList)
	{
		mp_FirstList = _task;
		return;
	}

	// �w��̃O���[�v�ƗD��x�̏ꏊ�ɒǉ�
	RenderTask* currentTask = mp_FirstList;
	RenderTask* nextTask = currentTask->mp_Next;

	// �O���[�v
	while (currentTask)
	{
		// �D��x�����X�g�̃^�X�N���Ⴂ�ꍇ�͂��̑O�̂Ƃ���Ƀ^�X�N��ǉ�
		if (_task->m_Priority < currentTask->m_Priority)
		{
			// �ǉ������^�X�N�̑O���ݒ�
			_task->mp_Prev = currentTask->mp_Prev;
			_task->mp_Next = currentTask;

			// ���X�g�̃^�X�N���q���ς���
			if (currentTask->mp_Prev)
			{
				currentTask->mp_Prev->mp_Next = _task;
			}

			currentTask->mp_Prev = _task;

			// �擪�ɒǉ����ꂽ�ꍇ�͐擪�|�C���^�ύX
			if (mp_FirstList == currentTask)
			{
				mp_FirstList = _task;
			}

			return;
		}

		// ���̃^�X�N���Ȃ��ꍇ�́A�Ō�ɒǉ�����
		if (!currentTask->mp_Next)
		{
			currentTask->mp_Next = _task;
			_task->mp_Prev = currentTask;
			return;
		}

		// ���̃^�X�N
		currentTask = currentTask->mp_Next;
	}
}

void RenderTaskManager::RemoveTask(RenderTask * _removeTask)
{
	RenderTask * prev = _removeTask->mp_Prev;
	RenderTask * next = _removeTask->mp_Next;

	// �^�X�N�̃O���[�v�̑O��
	if (prev)
	{
		prev->mp_Next = next;

	}
	if (next)
	{
		next->mp_Prev = prev;
	}

	// �擪�|�C���^�����ւ���ꍇ�X�V
	if (_removeTask == mp_FirstList)
	{
		mp_FirstList = _removeTask->mp_Next;
	}

	// �O�㍶�E�̂Ȃ����������
	_removeTask->mp_Prev = nullptr;
	_removeTask->mp_Next = nullptr;
}

void RenderTaskManager::RemoveTask(Task * _removeTask)
{
	RenderTask* currentTask = mp_FirstList;

	// �^�X�N����(�����o�^�����邩������Ȃ��̂őS���m�F����)
	while (currentTask)
	{
		RenderTask* nextTask = currentTask->mp_Next;

		// �^�X�N�|�C���^����v���Ă���ꍇ�̓��X�g�������
		if (currentTask->mp_Task == _removeTask)
		{
			RemoveTask(currentTask);
		}

		// ���̃^�X�N
		currentTask = nextTask;
	}
}

void RenderTaskManager::ChangePriority(RenderTask * _task)
{
	// �`�惊�X�g����O��
	RemoveTask(_task);

	// �`�惊�X�g�ɒǉ�
	AddRenderTask(_task);

}
