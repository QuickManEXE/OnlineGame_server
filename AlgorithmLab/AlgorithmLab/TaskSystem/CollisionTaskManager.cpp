#include "CollisionTaskManager.h"

#include <assert.h>

CollisionTaskManager* CollisionTaskManager::mp_Instance;

CollisionTaskManager* CollisionTaskManager::GetInstance()
{
	if (!mp_Instance)
	{
		mp_Instance = new CollisionTaskManager();
	}
	return mp_Instance;
}

void CollisionTaskManager::ReleaseInstance()
{
	// �^�X�N���폜����Ă��Ȃ��\��������܂��B(TaskManager�̕��Ń^�X�N���폜����Ƃ��Ɉꏏ�ɊO���Ă���͂�)
	assert(!mp_Instance->m_FirstList);

	delete mp_Instance;
	mp_Instance = nullptr;
}

CollisionTaskManager::CollisionTaskManager()
{
	for (int i = CollisionTask::eLayer_System; i < CollisionTask::eLayer_Max; i++)
	{
		m_FirstList[i] = nullptr;
	}
}

CollisionTaskManager::~CollisionTaskManager()
{
}

void CollisionTaskManager::CollisionCheckAll()
{
	// �X�V(�Փ˔���)

	for (int i = CollisionTask::eLayer_System; i < CollisionTask::eLayer_Max; i++) {

		CollisionTask* currentTask = m_FirstList[i];


		while (currentTask)
		{
			CollisionTask* nextTask = currentTask->mp_Next;

			// �ꎞ��~���Ă��Ȃ��ꍇ�͏Փ˔���
			if (!currentTask->m_IsPause)
			{
				while (nextTask) {

					if (!nextTask->m_IsPause) {
						//�ʂ�Task�ƏՓ˔���
						currentTask->CollisionCheck(nextTask);

						nextTask->CollisionCheck(currentTask);
					}

					nextTask = nextTask->mp_Next;
				}


			}

			// ���̃^�X�N
			currentTask = currentTask->mp_Next;
		}
	}
}

void CollisionTaskManager::AddCollisionTask(int _layerID,CollisionTask* _task)
{
	int i = _layerID;
	// �擪�|�C���^��null�̏ꍇ�͐擪�|�C���^�ɐݒ肵�Ēǉ��I��
	if (!m_FirstList[i])
	{
		m_FirstList[i] = _task;
		return;
	}

	// �w��̃O���[�v�ƗD��x�̏ꏊ�ɒǉ�
	CollisionTask* currentTask = m_FirstList[i];
	CollisionTask* nextTask = currentTask->mp_Next;

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
			if (m_FirstList[i] == currentTask)
			{
				m_FirstList[i] = _task;
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

void CollisionTaskManager::RemoveTask(int _layerID, CollisionTask* _removeTask)
{
	int i = _layerID;
	CollisionTask* prev = _removeTask->mp_Prev;
	CollisionTask* next = _removeTask->mp_Next;

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
	if (_removeTask == m_FirstList[i])
	{
		m_FirstList[i] = _removeTask->mp_Next;
	}

	// �O�㍶�E�̂Ȃ����������
	_removeTask->mp_Prev = nullptr;
	_removeTask->mp_Next = nullptr;
}

void CollisionTaskManager::RemoveTask(Task* _removeTask)
{
	for (int i = CollisionTask::eLayer_System; i < CollisionTask::eLayer_Max; i++) {
		CollisionTask* currentTask = m_FirstList[i];

		// �^�X�N����(�����o�^�����邩������Ȃ��̂őS���m�F����)
		while (currentTask)
		{
			CollisionTask* nextTask = currentTask->mp_Next;

			// �^�X�N�|�C���^����v���Ă���ꍇ�̓��X�g�������
			if (currentTask->mp_Task == _removeTask)
			{
				RemoveTask(i,currentTask);
			}

			// ���̃^�X�N
			currentTask = nextTask;
		}
	}
}

void CollisionTaskManager::ChangePriority(int _layerID, CollisionTask* _task)
{
	// �����蔻�胊�X�g����O��
	RemoveTask(_layerID, _task);

	// �����蔻�胊�X�g�ɒǉ�
	AddCollisionTask(_layerID, _task);
}

std::vector<CollisionTask*> CollisionTaskManager::GetCollisionList()
{
	// �Q�[�����C���[��
	int i = CollisionTask::eLayer_Game;

	CollisionTask* currentTask = m_FirstList[i];

	std::vector<CollisionTask*> task_vector;

	while (currentTask)
	{
		// �ꎞ��~���Ă��Ȃ��ꍇ
		if (!currentTask->m_IsPause)
		{
			//���X�g�ɓ����
			task_vector.push_back(currentTask);

		}

		// ���̃^�X�N
		currentTask = currentTask->mp_Next;
	}

	return task_vector;
}
