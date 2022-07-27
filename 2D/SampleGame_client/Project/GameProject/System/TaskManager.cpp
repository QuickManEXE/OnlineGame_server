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
	//更新用リストに追加 
	AddTaskInner( &(p->m_updateLink), &mp_updateHead, &mp_updateTail );
	//描画用リストに追加 
	AddTaskInner( &(p->m_renderLink), &mp_renderHead, &mp_renderTail );
}

void TaskManager::AddColl(Task * p)
{
	//衝突判定用リストに追加
	AddTaskInner(&(p->m_collLink), &mp_collHead, &mp_collTail);
}

void TaskManager::KillAppoint()
{
	//先頭から順に削除フラグが真のタスクを削除
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
	//先頭からタスクを削除
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
	//先頭から順にタスクを更新
	TaskLinker *p = mp_updateHead;
	while ( p )
	{
		//ストップ時間が0以上なら更新一時停止
		if(p->mp_task->m_stopTime > 0.0f)p->mp_task->m_stopTime--;
		//以外なら全更新
		else p->mp_task->Update();
		//次のタスクへ
		p = p->mp_next;
	}
}

void TaskManager::RenderAll()
{
	//先頭から順にタスクを描画
	TaskLinker *p = mp_renderHead;
	while ( p )
	{
		p->mp_task->Render();
		p = p->mp_next;
	}
}
void TaskManager::CollisionAll()
{
	//先頭から順に衝突判定をチェック
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
	//リンクから除外する 
	RemoveTaskLinker( &(p->m_updateLink), &mp_updateHead, &mp_updateTail );
	//優先順位を設定 
	p->m_updateLink.SetPriority(prio);
	//更新用リストに追加 
	AddTaskInner( &(p->m_updateLink), &mp_updateHead, &mp_updateTail );
}

void TaskManager::ChangeRenderPrio(Task *p, int prio)
{
	//リンクから除外する 
	RemoveTaskLinker( &(p->m_renderLink), &mp_renderHead, &mp_renderTail );
	//優先順位を設定 
	p->m_renderLink.SetPriority(prio);
	//描画用リストに追加 
	AddTaskInner( &(p->m_renderLink), &mp_renderHead, &mp_renderTail );
}

Task* TaskManager::Kill(Task *p)
{
	Task *next = nullptr;
	if (p->m_updateLink.mp_next != nullptr) next = p->m_updateLink.mp_next->mp_task;
	//リストから除外 
	Remove(p);
	//削除後初期化
	delete p;
	p = nullptr;
	//後続を返す 
	return next;
}
void TaskManager::Remove(Task *p) {
	//リストから除外 
	RemoveTaskLinker(&(p->m_updateLink), &mp_updateHead, &mp_updateTail);
	RemoveTaskLinker(&(p->m_renderLink), &mp_renderHead, &mp_renderTail);
	RemoveTaskLinker(&(p->m_collLink), &mp_collHead, &mp_collTail);
	p->m_updateLink.mp_next = nullptr; p->m_updateLink.mp_prev = nullptr;
	p->m_renderLink.mp_next = nullptr; p->m_renderLink.mp_prev = nullptr;
	p->m_collLink.mp_next = nullptr; p->m_collLink.mp_prev = nullptr;
}

Task* TaskManager::GetTask(int id)const
{
	//存在していれば指定IDのタスクを返す
	TaskLinker *p = mp_updateHead;
	while ( p )
	{
		if ( p->mp_task->m_id == id ) 
			return p->mp_task;
		p = p->mp_next;
	}
	//以外ならnullを返す
	return nullptr;
}

std::list<Task*> TaskManager::GetTasks(int id)const
{
	//指定のIDのリストを返す
	std::list<Task*> list;
	TaskLinker *p = mp_updateHead;
	while (p)
	{
		//取得したいIDと一致していればリストに追加
		if (p->mp_task->m_id == id) list.push_back(p->mp_task);
		p = p->mp_next;
	}
	return list;
}

TaskManager* TaskManager::GetInstance()
{
	//インスタンスを一度のみ生成して格納
	if (mp_instance == nullptr) mp_instance = new TaskManager();
	//それを返す
	return mp_instance;
}

void TaskManager::ClearInstance()
{
	//メモリリーク回避
	if (mp_instance != nullptr) delete mp_instance;
	mp_instance = nullptr;
}

int TaskManager::GetCount(int id)const
{
	//指定のIDのタスク数を返す
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
	//指定のIDの更新を指定時間一時停止
	TaskLinker *p = mp_updateHead;
	while (p)
	{
		if (p->mp_task->m_id == id) p->mp_task->SetStop(time);
		p = p->mp_next;
	}
}

void TaskManager::AddTaskInner(TaskLinker *p, TaskLinker **pHead, TaskLinker **pTail)
{
	//先頭が存在しなければ
	if ((*pHead) == nullptr)
	{
		//追加されたタスクを先頭に
		*pHead = p;
		p->mp_prev = nullptr;
		p->mp_next = nullptr;
		*pTail = p;
	}
	//先頭が存在していれば
	else
	{
		TaskLinker *t = (*pHead);

		while (t != nullptr)
		{
			// 挿入すべき優先度を探す 
			if (p->GetPriority() <= t->GetPriority())
			{
				// 挿入 
				TaskLinker	*prev = t->mp_prev;
				if (prev != nullptr) prev->mp_next = p;
				t->mp_prev = p;
				p->mp_prev = prev;
				p->mp_next = t;
				// 先頭の場合 
				if (t == *pHead) *pHead = p;
				return;
			}
			// 次へ 
			t = t->mp_next;
		}
		// 末尾に追加  
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
	//前後を繋ぎ直し 
	TaskLinker *prev = p->mp_prev;
	TaskLinker *next = p->mp_next;
	if (prev != nullptr) prev->mp_next = next;
	if (next != nullptr) next->mp_prev = prev;
	//自身のリンクをクリア 
	p->mp_prev = nullptr;
	p->mp_next = nullptr;
	//先頭を再設定 
	if (*pHead == p) *pHead = next;
	//終端を再設定 
	if (*pTail == p) *pTail = prev;
}