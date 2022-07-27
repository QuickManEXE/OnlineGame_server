#include "TaskManager.h"

TaskManager* TaskManager::mp_instance = nullptr;

TaskManager::TaskManager() : 
	mp_updateHead(nullptr), 
	mp_updateTail(nullptr),
	mp_renderHead(nullptr),
	mp_renderTail(nullptr), 
	mp_collHead(nullptr), 
	mp_collTail(nullptr)
{

}

TaskManager::~TaskManager()
{
	
}

void TaskManager::AddTask(Task *p)
{
	//�X�V�p���X�g�ɒǉ� 
	AddTaskInner( &(p->m_updateLink), &mp_updateHead, &mp_updateTail );
	//�`��p���X�g�ɒǉ� 
	AddTaskInner( &(p->m_renderLink), &mp_renderHead, &mp_renderTail );
}

void TaskManager::AddColl(Task * p)
{
	//�Փ˔���p���X�g�ɒǉ�
	AddTaskInner(&(p->m_collLink), &mp_collHead, &mp_collTail);
}

void TaskManager::KillAppoint()
{
	//�擪���珇�ɍ폜�t���O���^�̃^�X�N���폜
	TaskLinker *p = mp_updateHead;
	while (p)
	{
		TaskLinker	*next = p->mp_next;
		if (p->mp_task->m_destroyFlg)Kill(p->mp_task);
		if (next) p = next;
		else return;
	}

}

void TaskManager::KillAll()
{
	//�擪����^�X�N���폜
	TaskLinker *p = mp_updateHead;
	while ( p )
	{
		TaskLinker *next = p->mp_next;
		Kill( p->mp_task );
		p = next;
	}
}

void TaskManager::UpdateAll()
{
	//�擪���珇�Ƀ^�X�N���X�V
	TaskLinker *p = mp_updateHead;
	while ( p )
	{
		//�X�g�b�v���Ԃ�0�ȏ�Ȃ�X�V�ꎞ��~
		if(p->mp_task->m_stopTime > 0.0f)p->mp_task->m_stopTime--;
		//�ȊO�Ȃ�S�X�V
		else p->mp_task->Update();
		//���̃^�X�N��
		p = p->mp_next;
	}
}

void TaskManager::RenderAll()
{
	//�擪���珇�Ƀ^�X�N��`��
	TaskLinker *p = mp_renderHead;
	while ( p )
	{
		p->mp_task->Render();
		p = p->mp_next;
	}
}
void TaskManager::CollisionAll()
{
	//�擪���珇�ɏՓ˔�����`�F�b�N
	TaskLinker *p = mp_collHead;
	while (p)
	{
		TaskLinker *p2 = p->mp_next;
		while (p2)
		{
			p->mp_task->CheckCollision(p2->mp_task);
			p2 = p2->mp_next;
		}
		p = p->mp_next;
	}
}

void TaskManager::ChangeUpdatePrio(Task *p, int prio)
{
	//�����N���珜�O���� 
	RemoveTaskLinker( &(p->m_updateLink), &mp_updateHead, &mp_updateTail );
	//�D�揇�ʂ�ݒ� 
	p->m_updateLink.SetPriority(prio);
	//�X�V�p���X�g�ɒǉ� 
	AddTaskInner( &(p->m_updateLink), &mp_updateHead, &mp_updateTail );
}

void TaskManager::ChangeRenderPrio(Task *p, int prio)
{
	//�����N���珜�O���� 
	RemoveTaskLinker( &(p->m_renderLink), &mp_renderHead, &mp_renderTail );
	//�D�揇�ʂ�ݒ� 
	p->m_renderLink.SetPriority(prio);
	//�`��p���X�g�ɒǉ� 
	AddTaskInner( &(p->m_renderLink), &mp_renderHead, &mp_renderTail );
}

Task* TaskManager::Kill(Task *p)
{
	Task *next = nullptr;
	if (p->m_updateLink.mp_next != nullptr) next = p->m_updateLink.mp_next->mp_task;
	//���X�g���珜�O 
	Remove(p);
	//�폜�㏉����
	delete p;
	p = nullptr;
	//�㑱��Ԃ� 
	return next;
}
void TaskManager::Remove(Task *p) {
	//���X�g���珜�O 
	RemoveTaskLinker(&(p->m_updateLink), &mp_updateHead, &mp_updateTail);
	RemoveTaskLinker(&(p->m_renderLink), &mp_renderHead, &mp_renderTail);
	RemoveTaskLinker(&(p->m_collLink), &mp_collHead, &mp_collTail);
	p->m_updateLink.mp_next = nullptr; p->m_updateLink.mp_prev = nullptr;
	p->m_renderLink.mp_next = nullptr; p->m_renderLink.mp_prev = nullptr;
	p->m_collLink.mp_next = nullptr; p->m_collLink.mp_prev = nullptr;
}

Task* TaskManager::GetTask(int id)const
{
	//���݂��Ă���Ύw��ID�̃^�X�N��Ԃ�
	TaskLinker *p = mp_updateHead;
	while ( p )
	{
		if ( p->mp_task->m_id == id ) 
			return p->mp_task;
		p = p->mp_next;
	}
	//�ȊO�Ȃ�null��Ԃ�
	return nullptr;
}

std::list<Task*> TaskManager::GetTasks(int id)const
{
	//�w���ID�̃��X�g��Ԃ�
	std::list<Task*> list;
	TaskLinker *p = mp_updateHead;
	while (p)
	{
		//�擾������ID�ƈ�v���Ă���΃��X�g�ɒǉ�
		if (p->mp_task->m_id == id) list.push_back(p->mp_task);
		p = p->mp_next;
	}
	return list;
}

TaskManager* TaskManager::GetInstance()
{
	//�C���X�^���X����x�̂ݐ������Ċi�[
	if (mp_instance == nullptr) mp_instance = new TaskManager();
	//�����Ԃ�
	return mp_instance;
}

void TaskManager::ClearInstance()
{
	//���������[�N���
	if (mp_instance != nullptr) delete mp_instance;
	mp_instance = nullptr;
}

int TaskManager::GetCount(int id)const
{
	//�w���ID�̃^�X�N����Ԃ�
	int cnt = 0;
	TaskLinker *p = mp_updateHead;
	while (p)
	{
		if (p->mp_task->m_id == id) cnt++;
		p = p->mp_next;
	}
	return cnt;
}

void TaskManager::SetStop(float time, int id)
{
	//�w���ID�̍X�V���w�莞�Ԉꎞ��~
	TaskLinker *p = mp_updateHead;
	while (p)
	{
		if (p->mp_task->m_id == id) p->mp_task->SetStop(time);
		p = p->mp_next;
	}
}

void TaskManager::AddTaskInner(TaskLinker *p, TaskLinker **pHead, TaskLinker **pTail)
{
	//�擪�����݂��Ȃ����
	if ((*pHead) == nullptr)
	{
		//�ǉ����ꂽ�^�X�N��擪��
		*pHead = p;
		p->mp_prev = nullptr;
		p->mp_next = nullptr;
		*pTail = p;
	}
	//�擪�����݂��Ă����
	else
	{
		TaskLinker *t = (*pHead);

		while (t != nullptr)
		{
			// �}�����ׂ��D��x��T�� 
			if (p->GetPriority() <= t->GetPriority())
			{
				// �}�� 
				TaskLinker	*prev = t->mp_prev;
				if (prev != nullptr) prev->mp_next = p;
				t->mp_prev = p;
				p->mp_prev = prev;
				p->mp_next = t;
				// �擪�̏ꍇ 
				if (t == *pHead) *pHead = p;
				return;
			}
			// ���� 
			t = t->mp_next;
		}
		// �����ɒǉ�  
		TaskLinker* prev = *pTail;
		if (prev != nullptr) prev->mp_next = p;
		p->mp_prev = prev;
		p->mp_next = nullptr;
		(*pTail)->mp_next = p;
		(*pTail) = p;
	}
}

void TaskManager::RemoveTaskLinker(TaskLinker *p, TaskLinker **pHead, TaskLinker **pTail)
{
	//�O����q������ 
	TaskLinker *prev = p->mp_prev;
	TaskLinker *next = p->mp_next;
	if (prev != nullptr) prev->mp_next = next;
	if (next != nullptr) next->mp_prev = prev;
	//���g�̃����N���N���A 
	p->mp_prev = nullptr;
	p->mp_next = nullptr;
	//�擪���Đݒ� 
	if (*pHead == p) *pHead = next;
	//�I�[���Đݒ� 
	if (*pTail == p) *pTail = prev;
}