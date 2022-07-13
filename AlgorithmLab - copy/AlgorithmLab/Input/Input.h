#pragma once
#include<windows.h>
//#include"ADLibrary/Vector.h"

enum EKeyBind
	{
		Option,	// Option
		A,		// A
		B,		// B

		Up,		// ↑
		Down,	// ↓
		Left,	// ←
		Right,	// →

		MouseL, //マウスL
		MouseR, //マウスR
		MouseM, //マウスホイール

		KeyBindMax,
	};

	struct KeyInfo
	{
		int keyBind[KeyBindMax];	// キーバインド情報
		int keyState;				// キーステート
		int keyStateOld;			// 前回のキーステート
	};

class Input {
public:
	
	// キー情報を実体を定義
	static KeyInfo	s_keyState;

	////マウスの座標
	//static Vector2 s_mousePos;
	//static Vector2 s_mousePosOld;
	//static Vector2 s_mouseVec;
public:
	// 入力システムの初期化
	static void InitializeInput(void);
	// 入力システムの解放
	static void FinalizeInput(void);
	// 入力状況の更新
	static void UpdateInput(void);

	//// キーバインドの設定の例
	//BindKey(EKeyBind::Up, 'W');
	//BindKey(EKeyBind::Down, 'S');
	//BindKey(EKeyBind::Left, 'A');
	//BindKey(EKeyBind::Right, 'D');
	// キーバインドの設定
	static void BindKey(EKeyBind key, int keycode);

	// キーが押されているか？
	static bool IsKeyPress(EKeyBind key);
	// キーが押されたか？
	static bool IsKeyPush(EKeyBind key);
	// キーが離されたか？
	static bool IsKeyReleases(EKeyBind key);

	////マウスの座標取得
	//static Vector2 GetMousePos();
	////マウスの移動量取得
	//static Vector2 GetMouseVec();
};