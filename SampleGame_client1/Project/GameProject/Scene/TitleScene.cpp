#include "TitleScene.h"

// ������
static bool SceneInit(void)
{
	printf("TitleScene�ł�\n");
	return true;
}

// ���
static void SceneFinal(void)
{

}

// �X�V
static void SceneUpdate(void)
{
}

// �`��
static void SceneRender(void)
{
}

// �V�[�������̐ݒ�
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