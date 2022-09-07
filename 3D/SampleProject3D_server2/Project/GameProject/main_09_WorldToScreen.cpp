/*
	スクリーン座標、ワールド座標の相互変換
*/


#include "stdafx.h"
#include "Global.h"
//モーション有モデルクラス
CModelA3M model;
//座標
CVector3D pos(0,0,0);
//回転
CVector3D rot(0, 0, 0);

//ターゲット座標
CVector3D target(50,0,0);

//フィールドモデル
CModelField* field;


void MainLoop(void) {
	//キャラクター移動
	//移動量
	const float move_speed = 1.0f;

	//キャラクターをターゲットへ向けて移動させる
	//ターゲットへのベクトル
	CVector3D vec = target - pos;
	//回転値を逆算
	rot.y = atan2(vec.x, vec.z);
	//距離が10以上なら
	if (vec.Length() >= 10.0f) {
		//移動方向
		CVector3D dir(sin(rot.y), 0, cos(rot.y));
		//移動
		pos += dir * move_speed;
		//1番（待機）のアニメーションを再生
		model.ChangeAnimation(1);
	} else {
		//0番（待機）のアニメーションを再生
		model.ChangeAnimation(0);
	}
	//アニメーションを更新
	model.UpdateAnimation();

	{//キャラクターの接地処理
		//接触点と法線
		CVector3D cross, normal;
		//フィールドと線分（キャラクターの頭→足元）との衝突判定
		if (field->CollisionRay(&cross, &normal, pos + CVector3D(0,50,0) , pos)) {
			//高さのみ設定
			pos.y = cross.y;
		}
	}

	//キャラクターの座標、回転、スケール設定と表示
	model.SetPos(pos);
	model.SetRot(rot);
	model.SetScale(0.25, 0.25, 0.25);
	model.Render();


	field->Render();



	/*{//★スクリーン座標→ワールド座標のテスト
		CVector2D m = CInput::GetMousePoint();
		CVector3D w_pos;
		static float dist = 0;
		dist += CInput::GetMouseWheel() * 0.05f;
		Utility::ScreenToWorld(&w_pos, CVector3D(m.x, m.y, dist));
		Utility::DrawSphere(w_pos, 1.0f, CVector4D(0, 0, 1, 1));
		FONT_T()->Draw(0, 32, 0, 0, 1, "dist[%.2f] ", dist);
	}*/
	{//★マウスのクリックした場所を指す(スクリーン座標→ワールド座標)
		//マウスの座標（スクリーン座標）
		CVector2D m = CInput::GetMousePoint();
		//マウスの座標：近（ワールド座標）
		CVector3D m_w_near;
		//マウスの座標：遠（ワールド座標）
		CVector3D m_w_far;
		//スクリーン座標→ワールド座標変換
		Utility::ScreenToWorld(&m_w_near, CVector3D(m.x, m.y, 0));
		Utility::ScreenToWorld(&m_w_far, CVector3D(m.x, m.y, 1.0f));
		//マウスのワールド座標（近）からマウスのワールド座標（遠）への線分と
		//フィールドモデルとの衝突

		//接触点と法線
		CVector3D cross, normal;
		//フィールドと線分との衝突判定
		if (field->CollisionRay(&cross, &normal, m_w_near, m_w_far)) {
			//接触点の表示
			Utility::DrawCube(cross, 5.0f, CVector4D(1, 1, 0, 1));
			//クリックでターゲット位置更新
			if (PUSH(CInput::eMouseL))
				target = cross;
		}
	}

	//ターゲットの表示
	Utility::DrawCube(target, 5.0f, CVector4D(1, 0, 0, 1));

	{//★キャラクターの座標に名前を表示する（ワールド座標→スクリーン座標）

		CVector3D p;
		//ワールド座標→スクリーン座標
		Utility::WorldToScreen(&p, pos);
		//文字の表示
		FONT_T()->Draw(p.x, p.y, 1, 0, 0, "Player");
	}
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(100, 0, 0), CVector4D(1, 0, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 100, 0), CVector4D(0, 1, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 0, 100), CVector4D(0, 0, 1, 1));
}
void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//ブレンドの有効化
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);

	CFPS::SetFPS(60);
	//フレーム制御初期化
	CFPS::Init();
	//ボタンの設定
	CInput::Init();
	CInput::SetButton(0, CInput::eButton1, 'Z');
	CInput::SetButton(0, CInput::eButton2, 'X');
	CInput::SetButton(0, CInput::eButton3, 'R');
	CInput::SetButton(0, CInput::eButton4, 'V');
	CInput::SetButton(0, CInput::eButton5, VK_SPACE);
	CInput::SetButton(0, CInput::eButton10, VK_RETURN);
	CInput::SetButton(0, CInput::eUp, 'W');
	CInput::SetButton(0, CInput::eDown, 'S');
	CInput::SetButton(0, CInput::eLeft, 'A');
	CInput::SetButton(0, CInput::eRight, 'D');
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);
	CInput::SetButton(0, CInput::eMouseC, VK_MBUTTON);


//	CInput::SetMouseInside(true);
//	CInput::ShowCursor(false);
	CInput::UpDate();
	CInput::UpDate();


	//ライト設定
	CLight::SetType(0, CLight::eLight_Direction);
	CLight::SetPos(0, CVector3D(0, 200, 200));
	CLight::SetDir(0, CVector3D(-1, -2, 1).GetNormalize());
	CLight::SetColor(0, CVector3D(0.4f, 0.4f, 0.4f), CVector3D(0.6f, 0.6f, 0.6f));

//	CLight::SetType(1, CLight::eLight_Point);
//	CLight::SetColor(1, CVector3D(0.0f, 0.0f, 0.0f), CVector3D(1.0f, 1.0f, 1.0f));
//	CLight::SetAttenuation(1,0.10f);
//	CLight::SetRadiationAngle(1, Utility::DgreeToRadian(5.0f));

	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 700, 800);
	//カメラ初期化

	CCamera::GetCamera()->LookAt(	CVector3D(200,200,200),
									CVector3D(0,10,0),
									CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();
	//初期化

	//モデルの読み込み
	//Charactor/antman/antman.a3m
	ADD_RESOURCE("Antman", CModel::CreateModel("Charactor/antman/antman.a3m"));
	ADD_RESOURCE("Field", CModel::CreateModel("Field/Land/land.field"));

	//モデル複製
	model = COPY_RESOURCE("Antman",CModelA3M);

	//フィールドモデルは複製しない
	field = GET_RESOURCE("Field", CModelField);
	field->SetScale(50, 50, 50);
}


void Release()
{
	CLoadThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
}
static void ResizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	//画面解像度変動
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//画面解像度固定
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera::GetCamera()->SetScreenRect(CRect(0, 0, (float)w, (float)h));
	CCamera::GetCamera()->Viewport(0, 0, w, h);

	
	CCamera::GetCamera()->Perspective(Utility::DgreeToRadian(45.0), (float)w / (float)h, 1.0, 10000.0);
	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow *_window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow *_window, int x, int y) {
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);

}
static void FocusCallback(GLFWwindow *_window, int f) {
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

int __main(int* argcp, char** argv) {
	// メモリリーク検出
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//OpenGL4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;
//	glutInit(argcp, argv);

	GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
	glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
	glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

	glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
	glfwSetScrollCallback(GL::window, WheelCallback);
	glfwSetWindowFocusCallback(GL::window, FocusCallback);
	glfwSetWindowPosCallback(GL::window, PosCallback);
	if (!GL::window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GL::window);
	glfwSwapInterval(1);
	ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		printf("%s\n", glewGetString(GLEW_VERSION));
	}
	else {
		printf("%s\n", glewGetErrorString(err));
		getchar();
		return -1;
	}
	HDC glDc = wglGetCurrentDC();
	GL::hWnd = WindowFromDC(glDc);

	Init();

	while (!glfwWindowShouldClose(GL::window)) {
		static LARGE_INTEGER time;
		static LARGE_INTEGER time_buf;
		static long t_buf = 0;
		//現在のシステムのカウント数を取得
		QueryPerformanceCounter(&time_buf);

		CInput::UpDate();
		//各バッファーをクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		MainLoop();


		glfwSwapBuffers(GL::window);
		

		CFPS::Wait();

		char title[32];
		sprintf_s(title, "sample fps:%d dt:%.3f", CFPS::GetFPS(), CFPS::GetDeltaTime());
		glfwSetWindowTitle(GL::window, title);

		glfwPollEvents();
		if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(GL::window, GL_TRUE);
		}

	}

	glfwTerminate();




	Release();
	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}
