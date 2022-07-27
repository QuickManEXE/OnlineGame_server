#include "TitleScene.h"

// 初期化
static bool SceneInit(void)
{
	printf("TitleSceneです\n");
	return true;
}

// 解放
static void SceneFinal(void)
{

}

// 更新
static void SceneUpdate(void)
{
}

// 描画
static void SceneRender(void)
{
}

// シーン処理の設定
SceneManager::SceneProc SetupTitleScene(void)
{
	SceneManager::SceneProc proc =
	{
		"Title",
		SceneInit,
		SceneFinal,
		SceneUpdate,
		SceneRender,
	};
	return proc;
}