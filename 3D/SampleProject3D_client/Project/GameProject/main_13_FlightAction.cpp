/*
	平行移動と回転
	（フライトアクションゲーム）
*/


#include "stdafx.h"
#include "Global.h"

//スタティックメッシュモデル
CModelObj model_obj;
//キャラクター座標
CVector3D pos(0, 50, 0);
//キャラクター回転行列
CMatrix model_matrix_rot;
//キャラクターワールド（モデル）行列
CMatrix model_matrix;
//回転ベクトル
CVector3D rot_vec;

//カメラのワールド（モデル）行列
CMatrix matrix_camera;
//計器
CImage img_adi[2];


//フィールドモデル
CModelField* field;

void RenderSkybox();

void MainLoop(void) {


	//回転速度
	const float rot_speed = 2.0f;
	//回転加速度
	const float rot_accel = 0.1f;
	//移動量
	const float move_speed = 0.5f;

	//回転減速処理
	rot_vec *= 0.9f;
	//★回転処理
	//現在の姿勢（回転行列）から、ローカルなXYZ軸で回転する
	//ジンバルロックを防ぐ
	//https://upload.wikimedia.org/wikipedia/commons/4/49/Gimbal_Lock_Plane.gif
	//↑XYZ回転を組み合わせて、こうなってしまうと同じ回転しかできなくなる。
	model_matrix_rot *= CMatrix::MRotation(rot_vec);
	//前方向へ移動
	//     回転行列の前方向ベクトル * 移動量
	pos += model_matrix_rot.GetFront() * move_speed;

	//キー入力により回転速度を上げる。
	//(常に減速しているので、加速<減速が回転速度の頭打ち)
	//ピッチ（上下）
	if (HOLD(CInput::eUp)) {
		rot_vec.x += DtoR(rot_accel);
	}
	if (HOLD(CInput::eDown)) {
		rot_vec.x -= DtoR(rot_accel);
	}
	//ロール（ひねり回転）
	if (HOLD(CInput::eLeft)) {
		rot_vec.z -= DtoR(rot_accel);
	}
	if (HOLD(CInput::eRight)) {
		rot_vec.z += DtoR(rot_accel);
	}
	//ヨー（左右旋回）
	if (HOLD(CInput::eButton5)) {
		rot_vec.y += DtoR(rot_accel);
	}
	if (HOLD(CInput::eButton7)) {
		rot_vec.y -= DtoR(rot_accel);
	}
	//★飛行機のワールド（モデル）行列を計算する
	//ワールド行列 = 平行移動行列（座標）*	回転行列
	model_matrix = CMatrix::MTranselate(pos) * model_matrix_rot;
	
	//カメラ設定
	//キャラクターの子となる構造
	if (0) {
		//一人称視点
		matrix_camera = model_matrix * CMatrix::MTranselate(0, -1, 0);
	} else {
		//平行移動を変えると背面からのカメラとなる
		if (0) {
			matrix_camera = model_matrix * CMatrix::MTranselate(0, 1, -10);
		} else {
			//が、完全にくっつくより、遅れて着いてきた方が動いている感がある。
			CMatrix new_camera = model_matrix * CMatrix::MTranselate(0, 1, -10);
			//割合による補間
			matrix_camera = matrix_camera * 0.9f + new_camera * 0.1f;

		}
	}
	//モデル行列でカメラを設定（引数の行列を元に、内部でビュー行列に変換する）
	CCamera::GetCurrent()->SetTranseRot(matrix_camera);

	//ここから描画処理
	RenderSkybox();

	//キャラクター表示（行列を指定）
	model_obj.Render(model_matrix);




	//フィールド表示
	field->Render();



	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(100, 0, 0), CVector4D(1, 0, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 100, 0), CVector4D(0, 1, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 0, 100), CVector4D(0, 0, 1, 1));




	static CFont* font = nullptr;
	if (!font)font = new CFont();
	//前方向のベクトル
	CVector3D f = model_matrix.GetFront();
	//上方向のベクトル
	CVector3D u = model_matrix.GetUp();
	//左方向のベクトル
	//CVector3D r = model_matrix.GetRight();
	CVector3D r = model_matrix.GetLeft();

	//回転行列から水平線との角度を取り出し
	font->Draw(0, 32, 1, 0, 0, "%.2f %.2f(%.2f)", RtoD(asin(f.y)), RtoD(asin(r.y)), RtoD(atan2(r.y, u.y)));

	//★計器の表示
	//　行列から回転値を逆算する
	//ADI_1　これはそのまま表示
	//中心点を設定
	img_adi[0].SetCenter(256, 256);
	//位置を画面の真ん中に設定
	img_adi[0].SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//表示サイズを設定
	img_adi[0].SetSize(512, 512);
	//描画
	img_adi[0].Draw();


	//ADI_2(姿勢指示器)（回転行列からピッチとロールを取り出す）
	//中心点を設定
	img_adi[1].SetCenter(640 / 2, 320 / 2);
	//位置を画面の真ん中に設定
	img_adi[1].SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//表示サイズを設定
	img_adi[1].SetSize(640, 320);

	//ピッチ（水平線に対しての機首の上下の傾き）
	float x = asin(f.y);
	//ロール（水平線に対しての翼の左右の傾き）
	float z = atan2(r.y, u.y);
	//切り抜きの中心値を計算
	//ピッチ0°で画像の中心 y = 512   90°での切り抜き中心 y=56px
	float t = 512 - x / (float)M_PI_2 * (512 - 56);
	//tを中心に上下64px切り出す
	img_adi[1].SetRect(0, t - 64, 256, t + 64);
	//回転値も設定
	img_adi[1].SetAng(z);
	//描画
	img_adi[1].Draw();
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
	CInput::SetButton(0, CInput::eButton4, VK_SPACE);
	CInput::SetButton(0, CInput::eButton5, 'Q');
	CInput::SetButton(0, CInput::eButton7, 'E');
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
	ADD_RESOURCE("F16", CModel::CreateModel("Charactor/F16/F16.obj"));
	model_obj = COPY_RESOURCE("F16", CModelObj);

	ADD_RESOURCE("ADI_1", CImage::CreateImage("UI/ADI_1.png"));
	ADD_RESOURCE("ADI_2", CImage::CreateImage("UI/ADI_2.png"));
	img_adi[0] = COPY_RESOURCE("ADI_1", CImage);
	img_adi[1] = COPY_RESOURCE("ADI_2", CImage);


	ADD_RESOURCE("Field", CModel::CreateModel("Field/Land/Land.field"));
	field = GET_RESOURCE("Field", CModelField);
	field->SetScale(50, 50, 50);
	field->SetDrawLength(1000);

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
