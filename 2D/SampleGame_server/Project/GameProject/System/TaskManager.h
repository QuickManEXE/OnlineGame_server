/**
* @Brief	各タスクリスト管理
*/

#ifndef TASK_MANAGER_GUARD
#define TASK_MANAGER_GUARD

#include "Task.h"
#include <list>

class TaskManager
{
private:
	static TaskManager* mp_instance;			//自身ポインタ

protected:
	TaskLinker *mp_updateHead;					//更新先頭ポインタ
	TaskLinker *mp_updateTail;					//更新末尾ポインタ
	TaskLinker *mp_renderHead;					//描画先頭ポインタ
	TaskLinker *mp_renderTail;					//描画末尾ポインタ
	TaskLinker *mp_collHead;					//衝突判定用先頭ポインタ
	TaskLinker *mp_collTail;					//衝突判定用末尾ポインタ

private:
	//リストに追加 
	void AddTaskInner( TaskLinker *p, TaskLinker **pHead, TaskLinker **pTail );
	//リストから除外
	void RemoveTaskLinker( TaskLinker *p, TaskLinker **pHead, TaskLinker **pTail );

public:
	TaskManager();
	~TaskManager();
	void AddTask(Task *p);						//リスト追加関数
	void AddColl(Task *p);						//衝突判定用リスト追加関数
	void KillAppoint();							//リスト内指定削除関数
	void KillAll();								//リスト内全削除関数
	void UpdateAll();							//リスト更新関数
	void RenderAll();							//リスト描画関数
	void CollisionAll();						//衝突判定用更新関数
	void ChangeUpdatePrio(Task *p, int prio);	//更新優先度変更 
	void ChangeRenderPrio(Task *p, int prio);	//描画優先度変更 
	Task* Kill(Task *p);						//リスト内削除関数
	Task* GetTask(int id) const;				//タスク取得関数
	void Remove(Task *p);
	std::list<Task*> GetTasks(int id) const;	//タスクリスト取得関数
	static TaskManager* GetInstance();			//インスタンス生成取得
	static void ClearInstance();				//格納されているものを削除
	int GetCount(int id) const;					//タスクカウント関数
	void SetStop(float time, int id);		//指定時間指定タスクIDを更新停止
};

#endif