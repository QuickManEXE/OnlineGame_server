/**
* @Brief	タスクシステムのリンク形成
*/

#ifndef TASK_LINKER_GUARD
#define TASK_LINKER_GUARD

class Task;

class TaskLinker
{
private:
	Task		*mp_task;					//自身ポインタ
	TaskLinker	*mp_prev;					//前ポインタ
	TaskLinker	*mp_next;					//次ポインタ
	int			 m_priority;				//優先度 

public:
	TaskLinker();
	TaskLinker(int priority, Task *task);
	~TaskLinker();

	void SetPriority(int priority)			//優先度設定 
	{
		m_priority = priority;
	}

	inline int GetPriority() const			//優先度取得 
	{
		return m_priority;
	}		

	friend class TaskManager;
};

#endif