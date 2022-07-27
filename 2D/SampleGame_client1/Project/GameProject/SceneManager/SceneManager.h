#pragma once
#include<memory>
#include"../stdafx.h"
#include"../Singleton/Singleton.h"


class SceneManager : public Singleton<SceneManager> {
public:
	// 初期化用関数
	typedef	bool (*InitFunc)(void);
	// 解放用関数
	typedef	void (*FinalFunc)(void);
	// 更新用関数
	typedef	void (*UpdateFunc)(void);
	// 描画用関数
	typedef	void (*RenderFunc)(void);

	// シーン処理設定用構造体
	struct SceneProc
	{
		const char* Name;
		InitFunc		Init;
		FinalFunc		Final;
		UpdateFunc		Update;
		RenderFunc		Render;
	};

	// シーン遷移用の関数型
	typedef SceneProc(*SetupFunc)(void);
	// シーン管理の初期化
	void InitializeSceneManager(void);
	// シーン管理の解放
	void FinalizeSceneManager(void);
	// シーンの更新
	void UpdateSceneManager(void);
	// シーンの描画
	void RenderSceneManager(void);

	// シーンの遷移
	bool JumpScene(SetupFunc Func);
	// シーン名の取得
	const char* GetSceneName(void);

private:
	// 現在のシーン情報保持用
	SceneProc g_currentScene;
};