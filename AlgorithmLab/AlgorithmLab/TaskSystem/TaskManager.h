#ifndef INCLUDE_TASK_MANAGER
#define INCLUDE_TASK_MANAGER

#include "Task.h"

// �V���O���g��

class TaskManager
{
private:
	static TaskManager* mp_Instance;		// �C���X�^���X(���s����1�����C���X�^���X�𐶐������Ȃ�)

	Task* mp_ListFirst;					// �X�V���X�g�̐�[�|�C���^

	Task* mp_DeleteListFirst;			// �폜���X�g�̐�[�|�C���^

public:
	// �C���X�^���X�擾
	static TaskManager* GetInstance();	
	// �C���X�^���X���
	static void ReleaseInstance();		

	// �^�X�N���S����(��Еt���Ɏg�p����)
	void AllKill();						

	// Task�X�V
	void UpdateAll();

	// �^�X�N�����X�g�ɒǉ�
	void AddTask(Task* _addTask);

	//�\��폜�̎��s
	void PreKill();

	// �폜���X�g�ɒǉ�
	void AddKill(Task* _killTask);

	Task* FindTask(int _priorty);
private:
	TaskManager();
	~TaskManager();

	// �^�X�N�폜
	void KillTask();

	// Task�����X�g����O��
	void RemoveUpdateTaskList(Task* _removeTask);
	void RemoveKillTaskList(Task* _removeTask);

	// Task�����X�g�ɒǉ�����
	void AddTaskList(Task* _firstTask, Task* _removeTask);

};

#endif // !INCLUDE_TASK_MANAGER
