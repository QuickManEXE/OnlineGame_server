/**
* @Brief	�e�^�X�N���X�g�Ǘ�
*/

#ifndef TASK_MANAGER_GUARD
#define TASK_MANAGER_GUARD

#include "Task.h"
#include <list>

class TaskManager
{
private:
	static TaskManager* mp_instance;			//���g�|�C���^

protected:
	TaskLinker *mp_updateHead;					//�X�V�擪�|�C���^
	TaskLinker *mp_updateTail;					//�X�V�����|�C���^
	TaskLinker *mp_renderHead;					//�`��擪�|�C���^
	TaskLinker *mp_renderTail;					//�`�斖���|�C���^
	TaskLinker *mp_collHead;					//�Փ˔���p�擪�|�C���^
	TaskLinker *mp_collTail;					//�Փ˔���p�����|�C���^

private:
	//���X�g�ɒǉ� 
	void AddTaskInner( TaskLinker *p, TaskLinker **pHead, TaskLinker **pTail );
	//���X�g���珜�O
	void RemoveTaskLinker( TaskLinker *p, TaskLinker **pHead, TaskLinker **pTail );

public:
	TaskManager();
	~TaskManager();
	void AddTask(Task *p);						//���X�g�ǉ��֐�
	void AddColl(Task *p);						//�Փ˔���p���X�g�ǉ��֐�
	void KillAppoint();							//���X�g���w��폜�֐�
	void KillAll();								//���X�g���S�폜�֐�
	void UpdateAll();							//���X�g�X�V�֐�
	void RenderAll();							//���X�g�`��֐�
	void CollisionAll();						//�Փ˔���p�X�V�֐�
	void ChangeUpdatePrio(Task *p, int prio);	//�X�V�D��x�ύX 
	void ChangeRenderPrio(Task *p, int prio);	//�`��D��x�ύX 
	Task* Kill(Task *p);						//���X�g���폜�֐�
	Task* GetTask(int id) const;				//�^�X�N�擾�֐�
	void Remove(Task *p);
	std::list<Task*> GetTasks(int id) const;	//�^�X�N���X�g�擾�֐�
	static TaskManager* GetInstance();			//�C���X�^���X�����擾
	static void ClearInstance();				//�i�[����Ă�����̂��폜
	int GetCount(int id) const;					//�^�X�N�J�E���g�֐�
	void SetStop(float time, int id);		//�w�莞�Ԏw��^�X�NID���X�V��~
};

#endif