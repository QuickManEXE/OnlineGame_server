/*
	ボーンの行列を取得する
	武器を持つ
	GetFrameMatrix　行列の取得
	BindFrameMatrix　行列の固定
*/


#include "stdafx.h"
#include "Global.h"
//モーション有モデルクラス
CModelA3M model;
//座標
CVector3D pos(0,0,0);
//回転
CVector3D rot(0, 0, 0);
//回転行列
CMatrix rot_matrix;

//武器のモデル
CModelObj wepon_model;
//武器の行列
CMatrix wepon_matrix;

//フィールドモデル
CModelField* field;

void RenderSkybox();

void MainLoop(void) {


	//マウス操作でキャラクターを回転----
	CVector2D mouse_vec = CInput::GetMouseVec();
	rot.y += mouse_vec.x * -0.01f;
	rot.x += mouse_vec.y * 0.01f;
	rot.x = min(DtoR(45), max(DtoR(-45), rot.x));

	
	//方向キーの入力方向ベクトル
	CVector3D key_dir(0, 0, 0);

	//入力回転値
	float key_ang = 0;


	const float move_speed = 1.0f;

	static int anim = 0;

	//方向キーから入力方向ベクトルを設定
	if (HOLD(CInput::eUp)) {
		key_dir.z = 1;
		anim = 1;
	}
	if (HOLD(CInput::eDown)) {
		key_dir.z = -1;
		anim = 4;
	}
	if (HOLD(CInput::eLeft)) {
		key_dir.x = 1;		
		anim = 2;
	}
	if (HOLD(CInput::eRight)) {
		key_dir.x = -1;
		anim = 3;
	}


	static bool site = false;
	if (HOLD(CInput::eMouseR)) site = true;
	else site = false;
	//キー入力があれば
	if (key_dir.LengthSq() > 0) {
		//移動処理 回転行列×移動方向
		CVector3D dir = CMatrix::MRotationY(rot.y)*key_dir;
		pos += dir * move_speed;
	}
	else {
		anim = 0;
	}

	if (site) anim += 5;
	model.ChangeAnimation(anim);
	//モーションの更新
	model.UpdateAnimation();
	

	{//キャラクターの接地処理
	//接触点と法線
		CVector3D cross, normal;
		//フィールドと線分（キャラクターの頭→足元）との衝突判定
		if (field->CollisionRay(&cross, &normal, pos + CVector3D(0, 50, 0), pos)) {
			//高さのみ設定
			pos.y = cross.y;
		}
	}

	//ズレを防ぐため
	//武器の設定の前に、キャラクターの行列を更新する;
	//座標、回転、スケール設定
	model.SetPos(pos);
	model.SetRot(0, rot.y, 0);
	model.SetScale(0.5f, 0.5f, 0.5f);
	//★腰のボーンの向きを固定
	model.BindFrameMatrix(5, CMatrix::MRotation(rot));
	//行列の更新
	model.UpdateMatrix();
	//★武器の行列を設定する
	//手のボーン行列[親]　×　武器のローカル行列[子](平行移動×回転×スケール)
	// 
	//wepon_matrix = model.GetFrameMatrix("hand_r") * CMatrix::MTranselate(-17.981f, -5.383f, 7.500) * CMatrix::MRotation(DtoR(90), 0, DtoR(-90));;
	wepon_matrix = model.GetFrameMatrix(31) * CMatrix::MTranselate(-17.981f, -5.383f, 7.500)* CMatrix::MRotation(DtoR(90), 0, DtoR(-90));

	{//カメラ設定
		float fov = DtoR(45);
		CMatrix m;
		if (site) {
			fov = DtoR(30);
			m = CMatrix::MTranselate(pos) * CMatrix::MTranselate(CVector3D(0, 60, 0)) * CMatrix::MRotation(rot) * CMatrix::MTranselate(CVector3D(-25,25, -100));
		}else{
			fov = DtoR(45);
			m = CMatrix::MTranselate(pos) * CMatrix::MTranselate(CVector3D(0, 60, 0)) * CMatrix::MRotation(rot) * CMatrix::MTranselate(CVector3D(-40, 30, -100));
		}
		CCamera::GetCamera()->Perspective(fov, (float)CCamera::GetCurrent()->GetWhidth() / (float)CCamera::GetCurrent()->GetHeight(), 1.0, 10000.0);
		CCamera::GetCurrent()->SetTranseRot(m);
	}

	//スカイボックスの描画
	RenderSkybox();



	field->Render();

	//キャラクター表示
	model.SetPos(pos);
	//Y軸回転のみ適用
	model.SetRot(0,rot.y,0);
	model.SetScale(0.5f, 0.5f, 0.5f);
	model.BindFrameMatrix(5, CMatrix::MRotation(rot));
	model.Render();

	//★武器の表示(行列指定)
	wepon_model.Render(wepon_matrix);

	
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


	CInput::SetMouseInside(true);
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

	ADD_RESOURCE("Antman", CModel::CreateModel("Charactor/antman/antman.a3m"));
	ADD_RESOURCE("Scar", CModel::CreateModel("Wepon/Scar/Scar.obj"));
	ADD_RESOURCE("Field", CModel::CreateModel("Field/Land/land.field"));

	//モデル複製
	model = COPY_RESOURCE("Antman",CModelA3M);
	//モデル複製
	wepon_model = COPY_RESOURCE("Scar", CModelObj);

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


void RenderSkybox() {
	static CModel* skybox = nullptr;
	if (!skybox) {
		ADD_RESOURCE("Sky", CModel::CreateModel("Field/Sky/Sky.obj"));
		skybox = GET_RESOURCE("Sky", CModel);
		for (int i = 0; i < skybox->GetMaterialSize(); i++) {
			if (CTexture* t = skybox->GetMaterial(i)->m_pTex) {
				t->SetWrapST(GL_CLAMP_TO_EDGE);
				t->SetFilter(GL_LINEAR);
			}
		}
	}
	glDisable(GL_DEPTH_TEST);
	CCamera* back = CCamera::GetCurrent();
	CCamera* c = CCamera::GetCamera(CCamera::eSkyBox);
	CMatrix matrix = back->GetViewMatrix();
	matrix.m03 = 0; matrix.m13 = 0; matrix.m23 = 0;
	c->SetViewMatrix(matrix);
	c->SetProjectionMatrix(back->GetProjectionMatrix());
	CCamera::SetCurrent(c);

	CLight::SetLighting(false);
	skybox->Render();
	CLight::SetLighting(true);
	CCamera::SetCurrent(back);
	glEnable(GL_DEPTH_TEST);


}
