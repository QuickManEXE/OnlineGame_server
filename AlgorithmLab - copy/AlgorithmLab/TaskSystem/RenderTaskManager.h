#ifndef INCLUDE_TASK_RENDER_MANAGER
#define INCLUDE_TASK_RENDER_MANAGER

#include "RenderTask.h"

class RenderTaskManager
{
private:
	static RenderTaskManager* mp_Instance;		// �C���X�^���X

	RenderTask* mp_FirstList;					// �`�惊�X�g�̐�[�|�C���^

public:
	// �C���X�^���X�擾
	static RenderTaskManager* GetInstance();	
	// �C���X�^���X���
	static void ReleaseInstance();			

	// �`��
	void RenderAll();
	// �ǉ�
	void AddRenderTask(RenderTask* _task);
	// �o�^����
	void RemoveTask(RenderTask* _removeTask);
	// �o�^����(Task���猟��)
	void RemoveTask(Task* _removeTask);

	// �D��x�ύX
	void ChangePriority(RenderTask* _task);

private:
	RenderTaskManager();
	~RenderTaskManager();


};
#endif // !INCLUDE_TASK_RENDER_MANAGER
