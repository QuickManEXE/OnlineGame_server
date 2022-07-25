#include "SceneManager.h"


// �V�[���Ǘ��̏�����
void SceneManager::InitializeSceneManager(void)
{
	memset(&g_currentScene,0,sizeof(g_currentScene));
}

// �V�[���Ǘ��̉��
void SceneManager::FinalizeSceneManager(void)
{
	// �Ō�͉�����ďI���
	if (g_currentScene.Final) g_currentScene.Final();

	memset(&g_currentScene,0,sizeof(g_currentScene));
}

// �V�[���̍X�V
void SceneManager::UpdateSceneManager(void)
{
	if (g_currentScene.Update) g_currentScene.Update();
}

// �V�[���̕`��
void SceneManager::RenderSceneManager(void)
{
	if (g_currentScene.Render) g_currentScene.Render();
}

// �V�[���̑J��
bool SceneManager::JumpScene(SetupFunc Func)
{
	// ���݂̃V�[�����������
	if (g_currentScene.Final) g_currentScene.Final();

	memset(&g_currentScene,0, sizeof(g_currentScene));

	bool ret = true;
	// ���̃V�[��������Ώ���������
	if (Func)
	{
		g_currentScene = Func();
		if (g_currentScene.Init) ret = g_currentScene.Init();
	}
	return ret;
}

// �V�[�����̎擾
const char* SceneManager::GetSceneName(void)
{
	if (g_currentScene.Name) return g_currentScene.Name;
	return "Unknown";
}