/**
* @Brief	�^�X�N�V�X�e���̃����N�`��
*/

#ifndef TASK_LINKER_GUARD
#define TASK_LINKER_GUARD

class Task;

class TaskLinker
{
private:
	Task		*mp_task;					//���g�|�C���^
	TaskLinker	*mp_prev;					//�O�|�C���^
	TaskLinker	*mp_next;					//���|�C���^
	int			 m_priority;				//�D��x 

public:
	TaskLinker();
	TaskLinker(int priority, Task *task);
	~TaskLinker();

	void SetPriority(int priority)			//�D��x�ݒ� 
	{
		m_priority = priority;
	}

	inline int GetPriority() const			//�D��x�擾 
	{
		return m_priority;
	}		

	friend class TaskManager;
};

#endif