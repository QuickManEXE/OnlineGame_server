#ifndef INCLUDE_TASK_COLLISION
#define INCLUDE_TASK_COLLISION

#include "Task.h"

class CollisionTask;

typedef void(Task::*CollisionFunc)(CollisionTask*);

class CollisionTask
{
	friend class CollisionTaskManager;

public:
	CollisionTask();
	~CollisionTask();
	
	enum {
		eLayer_System,
		eLayer_Game,
		eLayer_HUD,
		eLayer_Max,
	};
private:

	CollisionTask* mp_Prev;			// �D�揇�ʂ̑O�̃|�C���^
	CollisionTask* mp_Next;			// �D�揇�ʂ̌�̃|�C���^

	int m_Priority;				// �D�揇��
	const char* m_Name;			// �f�o�b�O�p���O
	int m_LayerID;				//���C���[�̎��ʔԍ�

	Task* mp_Task;				// �^�X�N�|�C���^
	CollisionFunc m_Func;			// �֐��|�C���^

	bool m_IsPause;				// �ꎞ��~�t���O

public:
	// �Փ˔���֐��o�^
	void RegistCollision(int _layerID,Task* _task, CollisionFunc _func, int _priority, const char* _name);
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
	// �Փ˔���^�X�N�̖��O
	const char* GetName()const;

	Task* GetTask();
private:
	// �Փ˔���(�֐��|�C���^�Ăяo��)
	void CollisionCheck(CollisionTask* _task);

};

#endif // !INCLUDE_TASK_COLLISION