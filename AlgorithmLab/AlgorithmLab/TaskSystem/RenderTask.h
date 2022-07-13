#ifndef INCLUDE_RENDER_TASK
#define	INCLUDE_RENDER_TASK

#include "Task.h"

typedef void(Task::*RenderFunc)();

class RenderTask
{
	friend class RenderTaskManager;

public:
	RenderTask();
	~RenderTask();

private:
	
	RenderTask* mp_Prev;			// �D�揇�ʂ̑O�̃|�C���^
	RenderTask* mp_Next;			// �D�揇�ʂ̌�̃|�C���^

	int m_Priority;				// �D�揇��
	const char* m_Name;			// �f�o�b�O�p���O

	Task* mp_Task;				// �^�X�N�|�C���^
	RenderFunc m_Func;			// �֐��|�C���^

	bool m_IsPause;				// �ꎞ��~�t���O

public: 
	// �`��֐��o�^
	void RegistRender(Task* _task, RenderFunc _func, int _priority,  const char * _name);
	// �o�^����
	void Remove();
	// �D�揇�ʕύX
	void ChangePriority(int _priority);

	// �ꎞ��~
	void SetPause(bool _isPause);
	// �o�^����Ă��邩�ǂ���
	bool IsRegist()const;
	// �D��x�擾
	int GetPriority()const;
	// �ꎞ��~���Ă��邩�ǂ���
	bool IsPause()const;
	// �`��^�X�N�̖��O
	const char* GetName()const;

private:
	// �`��(�֐��|�C���^�Ăяo��)
	void Render();
};




#endif // !INCLUDE_RENDER_TASK