#include "Input.h"

KeyInfo	Input::s_keyState;

//Vector2 Input::s_mousePos;
//Vector2 Input::s_mousePosOld;
//Vector2 Input::s_mouseVec;

void Input::InitializeInput(void)
{
	for (int i = 0; i < KeyBindMax; i++)
	{
		s_keyState.keyBind[i] = -1;
	}
	s_keyState.keyState = 0;
	s_keyState.keyStateOld = 0;
}

void Input::FinalizeInput(void)
{
	InitializeInput();
}

void Input::UpdateInput(void)
{
	//�}�E�X���W�̎擾
	POINT point;
	GetCursorPos(&point);
	/*s_mousePos = Vector2(point.x, point.y);
	s_mouseVec = s_mousePos - s_mousePosOld;*/
	/*s_mousePosOld = Vector2(point.x, point.y);*/

	BYTE keyboardState[256];
	// �L�[�{�[�h��Ԃ̎擾
	GetKeyboardState(keyboardState);

	int keyState = 0;
	for (int i = 0; i < KeyBindMax; i++)
	{
		// �L�[���o�C���h����Ă��Ȃ���΃X���[����
		int key = s_keyState.keyBind[i];
		if (key == -1) continue;

		// ���͂���Ă���ꍇ�̓L�[�̃r�b�g�𗧂Ă�
		if (keyboardState[key] & 0x80)
		{
			keyState |= (1 << i);
		}
	}
	// �X�e�[�g�̍X�V
	s_keyState.keyStateOld = s_keyState.keyState;
	s_keyState.keyState = keyState;
}

void Input::BindKey(EKeyBind key, int keycode)
{
	s_keyState.keyBind[key] = keycode;
}

bool Input::IsKeyPress(EKeyBind key)
{
	int bit = (1 << key);
	// �P���Ɍ��݂̃X�e�[�g���画��
	int state = s_keyState.keyState;
	return (state & bit) ? true : false;
}

bool Input::IsKeyPush(EKeyBind key)
{
	int bit = (1 << key);
	// ����ƑO��Ƃ̃X�e�[�g�̍�(1 & ~0)�Ŕ���
	int state = s_keyState.keyState & ~s_keyState.keyStateOld;
	return (state & bit) ? true : false;
}

bool Input::IsKeyReleases(EKeyBind key)
{
	int bit = (1 << key);
	// �O��ƍ���̃X�e�[�g�̍�(1 & ~0)�Ŕ���
	int state = s_keyState.keyStateOld & ~s_keyState.keyState;
	return (state & bit) ? true : false;
}

//Vector2 Input::GetMousePos()
//{
//	return s_mousePos;
//}
//
//Vector2 Input::GetMouseVec()
//{
//	return s_mouseVec;
//}
