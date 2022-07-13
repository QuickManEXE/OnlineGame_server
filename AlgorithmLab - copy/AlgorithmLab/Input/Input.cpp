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
	//マウス座標の取得
	POINT point;
	GetCursorPos(&point);
	/*s_mousePos = Vector2(point.x, point.y);
	s_mouseVec = s_mousePos - s_mousePosOld;*/
	/*s_mousePosOld = Vector2(point.x, point.y);*/

	BYTE keyboardState[256];
	// キーボード状態の取得
	GetKeyboardState(keyboardState);

	int keyState = 0;
	for (int i = 0; i < KeyBindMax; i++)
	{
		// キーがバインドされていなければスルーする
		int key = s_keyState.keyBind[i];
		if (key == -1) continue;

		// 入力されている場合はキーのビットを立てる
		if (keyboardState[key] & 0x80)
		{
			keyState |= (1 << i);
		}
	}
	// ステートの更新
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
	// 単純に現在のステートから判定
	int state = s_keyState.keyState;
	return (state & bit) ? true : false;
}

bool Input::IsKeyPush(EKeyBind key)
{
	int bit = (1 << key);
	// 今回と前回とのステートの差(1 & ~0)で判定
	int state = s_keyState.keyState & ~s_keyState.keyStateOld;
	return (state & bit) ? true : false;
}

bool Input::IsKeyReleases(EKeyBind key)
{
	int bit = (1 << key);
	// 前回と今回のステートの差(1 & ~0)で判定
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
