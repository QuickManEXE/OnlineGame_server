/**
* @Brief	タスクシステム基底
*/

#ifndef TASK_GUARD
#define TASK_GUARD

#include "TaskLinker.h"
#include "../GID.h"
#include "../Global.h"

class Task
{
protected:
	TaskLinker m_updateLink;				//更新用リンク 
	TaskLinker m_renderLink;				//描画用リンク 
	TaskLinker m_collLink;					//衝突判定用リンク 
	int		   m_id;						//タスクID
	float	   m_stopTime;					//更新停止時間
	bool	   m_destroyFlg;				//削除フラグ

public:
	Task();						    
	Task(int id, int updateprio, int renderPrio);
	virtual ~Task();				
	virtual void Update();					//派生先で更新
	virtual void PauseUpdate();				//ポーズ時更新処理
	virtual void Render();					//派生先で描画
	virtual void CheckCollision(Task *t);	//派生先で衝突判定
	void ChangeUpdatePrio(int updatePrio);	//更新順位変更
	void ChangeRenderPrio(int renderPrio);	//描画順位変更
								
	void SetKill()							//削除フラグON 
	{
		m_destroyFlg = true;
	}

	inline int GetUpdatePrio() const		//更新順位取得関数
	{
		return m_updateLink.GetPriority();
	}

	inline int GetRenderPrio() const		//描画順位取得関数
	{
		return m_renderLink.GetPriority();
	}

	inline int GetID() const				//タスクID取得 
	{
		return m_id; 
	}

	void SetStop(float time)				//一時停止時間設定
	{
		m_stopTime = time;
	}

	friend class TaskManager;
};

#endif