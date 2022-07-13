#pragma once
#include<windows.h>
//#include"ADLibrary/Vector.h"

enum EKeyBind
	{
		Option,	// Option
		A,		// A
		B,		// B

		Up,		// ��
		Down,	// ��
		Left,	// ��
		Right,	// ��

		MouseL, //�}�E�XL
		MouseR, //�}�E�XR
		MouseM, //�}�E�X�z�C�[��

		KeyBindMax,
	};

	struct KeyInfo
	{
		int keyBind[KeyBindMax];	// �L�[�o�C���h���
		int keyState;				// �L�[�X�e�[�g
		int keyStateOld;			// �O��̃L�[�X�e�[�g
	};

class Input {
public:
	
	// �L�[�������̂��`
	static KeyInfo	s_keyState;

	////�}�E�X�̍��W
	//static Vector2 s_mousePos;
	//static Vector2 s_mousePosOld;
	//static Vector2 s_mouseVec;
public:
	// ���̓V�X�e���̏�����
	static void InitializeInput(void);
	// ���̓V�X�e���̉��
	static void FinalizeInput(void);
	// ���͏󋵂̍X�V
	static void UpdateInput(void);

	//// �L�[�o�C���h�̐ݒ�̗�
	//BindKey(EKeyBind::Up, 'W');
	//BindKey(EKeyBind::Down, 'S');
	//BindKey(EKeyBind::Left, 'A');
	//BindKey(EKeyBind::Right, 'D');
	// �L�[�o�C���h�̐ݒ�
	static void BindKey(EKeyBind key, int keycode);

	// �L�[��������Ă��邩�H
	static bool IsKeyPress(EKeyBind key);
	// �L�[�������ꂽ���H
	static bool IsKeyPush(EKeyBind key);
	// �L�[�������ꂽ���H
	static bool IsKeyReleases(EKeyBind key);

	////�}�E�X�̍��W�擾
	//static Vector2 GetMousePos();
	////�}�E�X�̈ړ��ʎ擾
	//static Vector2 GetMouseVec();
};