/**
* @Brief	�^�X�N�V�X�e�����
*/

#ifndef TASK_GUARD
#define TASK_GUARD

#include "TaskLinker.h"
#include "../GID.h"
#include "../Global.h"

class Task
{
protected:
	TaskLinker m_updateLink;				//�X�V�p�����N 
	TaskLinker m_renderLink;				//�`��p�����N 
	TaskLinker m_collLink;					//�Փ˔���p�����N 
	int		   m_id;						//�^�X�NID
	float	   m_stopTime;					//�X�V��~����
	bool	   m_destroyFlg;				//�폜�t���O

public:
	Task();						    
	Task(int id, int updateprio, int renderPrio);
	virtual ~Task();				
	virtual void Update();					//�h����ōX�V
	virtual void PauseUpdate();				//�|�[�Y���X�V����
	virtual void Render();					//�h����ŕ`��
	virtual void CheckCollision(Task *t);	//�h����ŏՓ˔���
	void ChangeUpdatePrio(int updatePrio);	//�X�V���ʕύX
	void ChangeRenderPrio(int renderPrio);	//�`�揇�ʕύX
								
	void SetKill()							//�폜�t���OON 
	{
		m_destroyFlg = true;
	}

	inline int GetUpdatePrio() const		//�X�V���ʎ擾�֐�
	{
		return m_updateLink.GetPriority();
	}

	inline int GetRenderPrio() const		//�`�揇�ʎ擾�֐�
	{
		return m_renderLink.GetPriority();
	}

	inline int GetID() const				//�^�X�NID�擾 
	{
		return m_id; 
	}

	void SetStop(float time)				//�ꎞ��~���Ԑݒ�
	{
		m_stopTime = time;
	}

	friend class TaskManager;
};

#endif