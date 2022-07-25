#pragma once
#include<memory>
#include"../stdafx.h"
#include"../Singleton/Singleton.h"


class SceneManager : public Singleton<SceneManager> {
public:
	// �������p�֐�
	typedef	bool (*InitFunc)(void);
	// ����p�֐�
	typedef	void (*FinalFunc)(void);
	// �X�V�p�֐�
	typedef	void (*UpdateFunc)(void);
	// �`��p�֐�
	typedef	void (*RenderFunc)(void);

	// �V�[�������ݒ�p�\����
	struct SceneProc
	{
		const char* Name;
		InitFunc		Init;
		FinalFunc		Final;
		UpdateFunc		Update;
		RenderFunc		Render;
	};

	// �V�[���J�ڗp�̊֐��^
	typedef SceneProc(*SetupFunc)(void);
	// �V�[���Ǘ��̏�����
	void InitializeSceneManager(void);
	// �V�[���Ǘ��̉��
	void FinalizeSceneManager(void);
	// �V�[���̍X�V
	void UpdateSceneManager(void);
	// �V�[���̕`��
	void RenderSceneManager(void);

	// �V�[���̑J��
	bool JumpScene(SetupFunc Func);
	// �V�[�����̎擾
	const char* GetSceneName(void);

private:
	// ���݂̃V�[�����ێ��p
	SceneProc g_currentScene;
};