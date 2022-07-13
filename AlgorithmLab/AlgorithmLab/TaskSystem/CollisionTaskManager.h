#ifndef INCLUDE_TASK_COLLISION_MANAGER
#define INCLUDE_TASK_COLLISION_MANAGER

#include "CollisionTask.h"
#include<vector>


class CollisionTaskManager
{
private:
	static CollisionTaskManager* mp_Instance;		// �C���X�^���X

	CollisionTask* m_FirstList[CollisionTask::eLayer_Max];	// �Փ˔��胊�X�g�̐�[�|�C���^

public:
	// �C���X�^���X�擾
	static CollisionTaskManager* GetInstance();
	// �C���X�^���X���
	static void ReleaseInstance();

	// �Փ˔���
	void CollisionCheckAll();
	// �ǉ�
	void AddCollisionTask(int _layerID,CollisionTask* _task);
	// �o�^����
	void RemoveTask(int _layerID,CollisionTask* _removeTask);
	// �o�^����(Task���猟��)
	void RemoveTask(Task* _removeTask);

	// �D��x�ύX
	void ChangePriority(int _layerID,CollisionTask* _task);


	std::vector<CollisionTask*> GetCollisionList();

private:
	CollisionTaskManager();
	~CollisionTaskManager();

	
};
#endif // !INCLUDE_TASK_COLLISION_MANAGER
