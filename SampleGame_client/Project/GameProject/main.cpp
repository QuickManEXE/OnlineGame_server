#define FULL_SCREEN 0


#include "stdafx.h"
#include "Global.h"
#include "GID.h"
#include "System/TaskManager.h"
#include "Charactor/CPlayer.h"
#include "Charactor/CEnemy.h"
#include "UI/CUI.h"
#include "Field/CField.h"
#include "Charactor/AnimData.h"

void MainLoop(void) {
	//---------------------------------------
	// 
	//---------------------------------------
	
	TaskManager::GetInstance()->KillAppoint();

	TaskManager::GetInstance()->UpdateAll();
	TaskManager::GetInstance()->CollisionAll();


	//各種描画

	TaskManager::GetInstance()->RenderAll();


}
void LoadProc() {

}
void Init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);

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
	CInput::SetButton(0, CInput::eButton3, 'C');
	CInput::SetButton(0, CInput::eButton4, 'V');
	CInput::SetButton(0, CInput::eButton6, VK_SHIFT);
	CInput::SetButton(0, CInput::eButton7, 'Q');
	CInput::SetButton(0, CInput::eButton8, 'E');
	CInput::SetButton(0, CInput::eButton10, VK_RETURN);
	CInput::SetButton(0, CInput::eUp, VK_UP);
	CInput::SetButton(0, CInput::eDown, VK_DOWN);
	CInput::SetButton(0, CInput::eLeft, VK_LEFT);
	CInput::SetButton(0, CInput::eRight, VK_RIGHT);
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
	CLight::SetColor(0, CVector3D(0.8f, 0.8f, 0.8f), CVector3D(0.8f, 0.8f, 0.8f));


	//カメラ初期化
	CCamera::GetCamera()->LookAt(CVector3D(0, 20, -20),
		CVector3D(0, 2, 0),
		CVector3D(0.0, 1.0, 0.0));


	SetCurrentDirectory("data");

	//CShader::GetInstance("StaticMesh");
	//CShader::GetInstance("SkinMesh");
	CSound::GetInstance();
	//初期化

	
	ADD_RESOURCE("Player", CImage::CreateImage("Player.png"));
	ADD_RESOURCE("Missile", CImage::CreateImage("Missile.png"));
	ADD_RESOURCE("Bullet", CImage::CreateImage("Bullet.png"));
	ADD_RESOURCE("Bullet2", CImage::CreateImage("Bullet2.png"));
	ADD_RESOURCE("Enemy", CImage::CreateImage("Enemy.png"));
	ADD_RESOURCE("Effect_Bomb", CImage::CreateImage("Effect_Bomb.png", effectAnimData,96,96));
		
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++) {
			new CEnemy(64+j*64, 64+i*64);
		}
	}
	


	new CPlayer(CVector2D(300, 660));
	new CUI();
	
}



void Release()
{
	CLoadThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
}

static void ResizeCallback(GLFWwindow* window, int w, int h)
{

	CCamera::GetCamera()->Viewport(0, 0, w, h);
	//画面解像度変動
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//画面解像度固定
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	CCamera::GetCamera()->SetScreenRect(CRect(0, 0, (float)w, (float)h));

	CCamera::GetCurrent()->Perspective(Utility::DgreeToRadian(45.0), (float)w / (float)h, 1.0, 10000.0);


	GL::UpdateWindosRect(GL::window_x, GL::window_y, w, h);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
	GL::UpdateWindowRect(x, y, GL::window_width, GL::window_height);
	CInput::UpdateClipCursor(true);

}
static void FocusCallback(GLFWwindow* _window, int f) {
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}
//フルスクリーン?ウインドウモードの切り替え
//Alt+Enterで切り替える
void CheckFullScreen() {
	static CVector2D pos;
	static int key_enter = 0;
	static bool full_screen = false;
	int key_enter_buf = key_enter;
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT)) {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		if (!full_screen) {
			glfwGetWindowPos(GL::window, &pos.ix, &pos.iy);
			glfwSetWindowMonitor(GL::window, monitor, 0, 0, GL::window_width, GL::window_height, mode->refreshRate);
			full_screen = true;
		}
		else {
			glfwSetWindowMonitor(GL::window, nullptr, pos.ix, pos.iy, GL::window_width, GL::window_height, mode->refreshRate);
			full_screen = false;
		}
	}
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
		CheckFullScreen();
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
