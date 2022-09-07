/*
	行列
*/


#include "stdafx.h"
#include "Global.h"
//モーション有モデルクラス
CModelA3M model;
//座標
CVector3D pos(0,0,0);
//回転
CVector3D rot(0, 0, 0);

CVector3D scale(0.5f, 0.5f, 0.5f);


//平行移動行列
CMatrix mat_trans;
//回転行列
CMatrix mat_rotX;
CMatrix mat_rotY;
CMatrix mat_rotZ;
CMatrix mat_rot;

//スケール行列
CMatrix mat_scale;

//ワールド行列（ModelMatrix、WorldMatrix）【キャラクターの行列】
CMatrix matrix_model;

//ビュー行列（ViewMatrix）【カメラの行列】
CMatrix matrix_view;

//投影行列（ProjectionMatrix）【レンズの行列】
CMatrix matrix_proj;

//ビューポート行列（ViewportMatrix）【スクリーンの行列】
CMatrix matrix_view_port;






void MainLoop(void) {

	model.ChangeAnimation(0);
	model.UpdateAnimation();
	if (0) {

		//位置、回転値、スケールを設定して描画
		model.SetPos(pos);
		model.SetRot(rot);
		model.SetScale(scale);
		model.Render();


		Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(100, 0, 0), CVector4D(1, 0, 0, 1));
		Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 100, 0), CVector4D(0, 1, 0, 1));
		Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 0, 100), CVector4D(0, 0, 1, 1));

	}else
	if(1){



		static bool psw = true;
		//Zボタンで投影切り替え
		if (CInput::GetState(0, CInput::ePush, CInput::eButton1))
			psw = !psw;

		//アフィン変換行列
		mat_trans = CMatrix::MTranselate(pos);
		mat_rotX = CMatrix::MRotationX(rot.x);
		mat_rotY = CMatrix::MRotationX(rot.y);
		mat_rotZ = CMatrix::MRotationX(rot.z);
		mat_rot = mat_rotZ * mat_rotY * mat_rotX;
		mat_scale = CMatrix::MScale(scale);
		//①モデル行列
		//           = 平行移動行列×回転行列×スケール行列
		matrix_model = mat_trans  * mat_rot * mat_scale;

		for(int i=0;i<2;i++) {	//画面分割する場合　【ビュー行列】【投影行列】【ビューポート行列】を画面ごとに設定する。
			//②ビュー行列
			/*{
				CVector3D cam_pos(200, 200, 200);
				CVector3D cam_at(0, 0, 0);
				CVector3D cam_up(0, 1, 0);

				CCamera::GetCurrent()->LookAt(cam_pos, cam_at, cam_up);
			}*/
			{	//２画面用
				CVector3D cam_pos[2] = { CVector3D(0, 200, 200),CVector3D(200, 200, 0) };
				CVector3D cam_at[2] = { CVector3D(0, 0, 0),CVector3D(0, 0, 0) };
				CVector3D cam_up(0, 1, 0);

				CCamera::GetCurrent()->LookAt(cam_pos[i], cam_at[i], cam_up);
			}


			//③投影行列
			//カメラのレンズの設定
			static float fov = DtoR(45);
			//アスペクト比
			float aspect = (float)(SCREEN_WIDTH) / (float)(SCREEN_HEIGHT/2);
			//float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
			if (psw) {
				//マウスホイールで視野角を変更する
				fov += CInput::GetMouseWheel() * DtoR(1.0f);
				//透視投影行列
				//☆各パラメータを変えて変化を確認する
				//☆FOVを広げる、狭める
				//☆アスペクト比をビューポートに合わせる
				CCamera::GetCurrent()->Perspective(fov, aspect, 1.0, 1000.0);
			}
			else {
				//正投影行列
				//☆各パラメータを変えて変化を確認する
				//☆画面サイズ同様に横２：縦１の比率
				CCamera::GetCurrent()->Ortho(-10, 10, -5, 5, 1.0, 1000.0);
			}

			//④ビューポート行列
			/*{

				CRect rect = { 0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT };
				CCamera::GetCurrent()->Viewport(rect.m_x, rect.m_y, rect.m_width, rect.m_height);
			}*/
			{

				//★各パラメータを変更する
				//☆左半分や右半分だけ描画等
				//描画範囲		{x,y,w,h};
				CRect rect[2] = {
					{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2 },
					{ 0 , SCREEN_HEIGHT /2, SCREEN_WIDTH, SCREEN_HEIGHT/2 },
				};
				CCamera::GetCurrent()->Viewport(rect[i].m_x, rect[i].m_y, rect[i].m_width, rect[i].m_height);
			}
			




			//位置、回転値、スケールを設定して描画
			//model.SetPos(pos);
			//model.SetRot(rot);
			//model.SetScale(scale);
			//model.Render();

			//行列を指定してモデルを描画
			model.Render(matrix_model);

			Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(100, 0, 0), CVector4D(1, 0, 0, 1));
			Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 100, 0), CVector4D(0, 1, 0, 1));
			Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 0, 100), CVector4D(0, 0, 1, 1));


			FONT_T()->Draw(0, 32, 1, 0, 0, "%d", i);
		}

	}else
	{	//
		//描画パイプランのソフトウェア演算
		//

		CVector3D cam_pos(100, 200, 200);
		CVector3D cam_at(0, 0, 0);
		CVector3D cam_up(0, 1, 0);
		//カメラのレンズの設定
		static float fov = DtoR(45);
		//アスペクト比
		float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
		CRect rect = { 0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };

		//ビュー行列(カメラ)
		matrix_view.LookAtView(cam_pos, cam_at, cam_up);
		//投影行列(カメラのレンズ)
		matrix_proj.Perspective(fov, aspect, 1.0, 1000.0);
		//ビューポート行列（画面への表示範囲）
		matrix_view_port.Viewport(rect.m_x, rect.m_y, rect.m_width, rect.m_height);


		//4つの頂点
		const float cube_size = 1.0f;
		const CVector3D vertex[] = {
			CVector3D(cube_size, cube_size, cube_size),
			CVector3D(cube_size, cube_size, -cube_size),
			CVector3D(-cube_size, cube_size, -cube_size),
			CVector3D(-cube_size, cube_size, cube_size),
		};

		for (int i = 0; i < 4; i++) {
			//		ビューポート行列 * 投影行列 * ビュー行列 * ワールド行列 * 頂点座標
			CVector4D o = matrix_view_port * matrix_proj * matrix_view * matrix_model * CVector4D(vertex[i], 1);
			o = CVector4D(o.x / o.w, o.y / o.w, o.z / o.w, 1);
			Utility::DrawCircle(CVector2D(o.x, SCREEN_HEIGHT - o.y), 8.0f, CVector4D(1, 0, 0, 1));
		}
	}


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

	//★モデルの読み込み
	//Charactor/antman/antman.a3m
	ADD_RESOURCE("Antman", CModel::CreateModel("Charactor/antman/antman.a3m"));

	//★モデル複製
	model = COPY_RESOURCE("Antman",CModelA3M);
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
