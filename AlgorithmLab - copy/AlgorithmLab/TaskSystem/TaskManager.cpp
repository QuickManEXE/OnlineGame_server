#include "TaskManager.h"
#include "RenderTaskManager.h"
#include"CollisionTaskManager.h"
#include"../GID.h"

// printf_s ���g�p���邽�߃C���N���[�h
#include <iostream>

#include <assert.h>

#define ARRAY_LENGTH(ary) (sizeof(ary) / sizeof(ary[0]))

TaskManager* TaskManager::mp_Instance = nullptr;

TaskManager * TaskManager::GetInstance()
{
	// �C���X�^���X���Ȃ��ꍇ�͐���
	if (!mp_Instance)	mp_Instance = new TaskManager();

	return mp_Instance;
}

void TaskManager::ReleaseInstance()
{
	// �S�����폜����
	mp_Instance->AllKill();

	// �^�X�N���c���Ă��邩�ǂ����ȈՊm�F

	// �X�V�^�X�N���폜����Ă��Ȃ��\��������܂��B
	assert(!mp_Instance->mp_ListFirst);
	// �폜�^�X�N���폜����Ă��Ȃ��\��������܂��B
	assert(!mp_Instance->mp_DeleteListFirst);


	delete mp_Instance;
	mp_Instance = nullptr;
}

TaskManager::TaskManager():
	mp_ListFirst(nullptr),
	mp_DeleteListFirst(nullptr)
{
}

TaskManager::~TaskManager()
{
}

void TaskManager::UpdateAll()
{
	PreKill();

	// �^�X�N�폜(�O��̃t���[���ō폜�\��̂��̂����폜)
	KillTask();

	// �X�V�^�X�N
	Task* currentTask = mp_ListFirst;

	// �X�V
	while (currentTask)
	{
		// ���̃^�X�N
		Task* nextTask = currentTask->mp_Next;

		// State���ʏ�̏ꍇ�ɍX�V����
		if (!currentTask->m_IsPause)
		{
			currentTask->Update();
		}

		// ���̃^�X�N
		currentTask = nextTask;
	}
}

void TaskManager::AddTask(Task * _addTask)
{
	// �擪�^�X�N���Ȃ��ꍇ�͐擪�^�X�N�ɐݒ肵�ďI��
	if (!mp_ListFirst)
	{
		mp_ListFirst = _addTask;
		return;
	}

	Task* currentTask = mp_ListFirst;

	// ���X�g�ɒǉ�
	while (currentTask)
	{
		// �ǉ�����^�X�N�̕����D��x���Ⴂ�ꍇ�͌���̈�O�Ƀ^�X�N��ǉ�
		if (_addTask->m_Priority < currentTask->m_Priority)
		{
			// �ǉ������^�X�N�̑O���ݒ�
			_addTask->mp_Prev = currentTask->mp_Prev;
			_addTask->mp_Next = currentTask;

			// ���X�g�̃^�X�N���q���ς���
			if (currentTask->mp_Prev)
			{
				currentTask->mp_Prev->mp_Next = _addTask;
			}

			currentTask->mp_Prev = _addTask;


			// �擪�ɒǉ����ꂽ�ꍇ�͐擪�|�C���^�ύX
			if (mp_ListFirst == currentTask)
			{
				mp_ListFirst = _addTask;
			}

			return;
		}

		// ���̃^�X�N���Ȃ��ꍇ�́A�Ō�ɒǉ�����
		if (!currentTask->mp_Next)
		{
			currentTask->mp_Next = _addTask;
			_addTask->mp_Prev = currentTask;
			return;
		}

		currentTask = currentTask->mp_Next;
	}
}

void TaskManager::PreKill()
{
	// �X�V�^�X�N
	Task* currentTask = mp_ListFirst;

	// �X�V
	while (currentTask)
	{
		// ���̃^�X�N
		Task* nextTask = currentTask->mp_Next;

		// m_kill���^�̏ꍇ�ɍ폜
		if (currentTask->m_Kill)
		{
			AddKill(currentTask);
		}

		// ���̃^�X�N
		currentTask = nextTask;
	}
}

void TaskManager::AddKill(Task * _killTask)
{
	// �X�V���X�g����^�X�N���O��
	RemoveUpdateTaskList(_killTask);


	// ��[�|�C���^���Ȃ��ꍇ�͐�[�|�C���^�ɐݒ�
	if (!mp_DeleteListFirst)
	{
		mp_DeleteListFirst = _killTask;
		return;
	}

	Task* currentTask = mp_DeleteListFirst;

	// ���̃^�X�N�����邩�ǂ����m�F
	while (currentTask->mp_Next)
	{
		// ���̃^�X�N
		currentTask = currentTask->mp_Next;

	}

	// �����Ƀ^�X�N��ǉ�
	currentTask->mp_Next = _killTask;

}

Task* TaskManager::FindTask(int _priorty)
{
	// �X�V�^�X�N
	Task* currentTask = mp_ListFirst;

	// �X�V
	while (currentTask)
	{
		// ���̃^�X�N
		Task* nextTask = currentTask->mp_Next;

		// m_kill���^�̏ꍇ�ɍ폜
		if (currentTask->GetPriority()==_priorty)
		{
			return currentTask;
		}

		// ���̃^�X�N
		currentTask = nextTask;
	}
	return nullptr;
}

void TaskManager::AddTaskList(Task * _firstList, Task * _addTask)
{
	Task* currentTask = _firstList;

	while (currentTask)
	{
		// ���̃^�X�N�����邩�ǂ����m�F
		if (currentTask->mp_Next)
		{
			// ���̃^�X�N
			currentTask = currentTask->mp_Next;
		}
		else
		{
			// �����Ƀ^�X�N��ǉ�
			_addTask->mp_Prev = currentTask;
			_addTask->mp_Next = nullptr;
			currentTask->mp_Next = _addTask;
		}
	}
}

void TaskManager::RemoveUpdateTaskList(Task * _removeTask)
{
	Task * prev = _removeTask->mp_Prev;
	Task * next = _removeTask->mp_Next;


	// �^�X�N�̗D�揇��(�O��)
	if (prev)
	{
		prev->mp_Next = next;

	}
	if (next)
	{
		next->mp_Prev = prev;
	}
			
	// �擪�|�C���^���O���ꍇ�͎��̃^�X�N(��������null)��ݒ肷��
	if (_removeTask == mp_ListFirst)
	{
		mp_ListFirst = _removeTask->mp_Next;
	}

	// �O�㍶�E�̂Ȃ����������
	_removeTask->mp_Prev = nullptr;
	_removeTask->mp_Next = nullptr;

}

void TaskManager::RemoveKillTaskList(Task * _removeTask)
{
	Task * prev = _removeTask->mp_Prev;
	Task * next = _removeTask->mp_Next;


	// �^�X�N�̗D�揇��(�O��)
	if (prev)
	{
		prev->mp_Next = next;

	}
	if (next)
	{
		next->mp_Prev = prev;
	}

	// �擪�|�C���^���O���ꍇ�͎��̃^�X�N(��������null)��ݒ肷��
	if (_removeTask == mp_DeleteListFirst)
	{
		mp_DeleteListFirst = _removeTask->mp_Next;
	}

	// �O�㍶�E�̂Ȃ����������
	_removeTask->mp_Prev = nullptr;
	_removeTask->mp_Next = nullptr;

}

void TaskManager::KillTask()
{
	// �폜���X�g������ꍇ�̓��X�g���̃^�X�N���폜����
	if (mp_DeleteListFirst)
	{
		Task* currentTask = mp_DeleteListFirst;

		while (currentTask)
		{
			// ���̃^�X�N�ۑ�
			Task* nextTask = currentTask->mp_Next;

			// ���X�g����O��
			RemoveKillTaskList(currentTask);

			// �^�X�N�폜
 			delete currentTask;

			// ���̃^�X�N
			currentTask = nextTask;
		}
	}
}

void TaskManager::AllKill()
{
	// �X�V�^�X�N
	Task* currentTask = mp_ListFirst;

	// �X�V
	while (currentTask)
	{
		// ���̃^�X�N
		Task* nextTask = currentTask->mp_Next;

		currentTask->SetKill();

		// ���̃^�X�N
		currentTask = nextTask;

	}

	// �^�X�N���폜
	/*Task* listfirstGroup[] = {m_DeleteListFirst, m_ListFirst };

	for (int i = 0; i < ARRAY_LENGTH(listfirstGroup); i++)
	{
		Task* currentTask = listfirstGroup[i];

		// ���X�g���܂킷
		while (currentTask)
		{
			// ���̃^�X�N��ێ����Ă���
			Task* nextTask = currentTask->m_Next;

			// ���X�g����O��
			if (i == 0)
			{
				// �폜���X�g
				RemoveKillTaskList(currentTask);
			}
			else
			{
				// �X�V���X�g
				RemoveUpdateTaskList(currentTask);
			}

			// �`�惊�X�g����폜����
			DrawTaskManager::GetInstance()->RemoveTask(currentTask);

			// �Փ˔��胊�X�g����폜����
			CollisionTaskManager::GetInstance()->RemoveTask(currentTask);

			// �^�X�N�폜
			delete currentTask;

			// ���̃^�X�N�ɐi�߂�
			currentTask = nextTask;
		}
	}*/
}