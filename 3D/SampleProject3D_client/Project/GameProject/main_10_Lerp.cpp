/*
	線形補間
	（位置、角度）
*/


#include "stdafx.h"
#include "Global.h"
//モーション有モデルクラス
CModelA3M model;
//座標
CVector3D pos(0,0,0);
//回転
CVector3D rot(0, 0, 0);
//回転の目標値
CVector3D rot_target(0, 0, 0);


//注視する立方体
const int cube_size = 3;
CVector3D cube_pos[cube_size] = {
	CVector3D(200, 0, 0),
	CVector3D(0, 0, 200),
	CVector3D(-200, 0, 200),
};



//ミサイルモデル
CModelObj	model_missile;
//ミサイル座標
CVector3D	pos_missile(0, 10, -10);
//ミサイル回転(クォータニオン)
CQuaternion quat_missile;


//カメラの位置
CVector3D cam_pos(0, 0, 0);
//カメラの注視点
CVector3D cam_at(0, 0, 0);



void UpdatePlayer();

void MainLoop(void) {

	static int type = 0;
	static const int type_max = 2;
	static int cate = 0;
	if (PUSH(CInput::eMouseL)) {
		type++;
		if (type > type_max) type = 0;
	}

	if (PUSH(CInput::eMouseR)) {
		cate++;
	}
	if(type == 0){
		if (cate >= 3) cate = 0;
		//★次々と視点を変える際に注視点を補完するサンプル
		static int now = 0;
		static int old = 0;

		//補間係数 0 ～ 1
		static float t = 0;


		//前のターゲットへ
		if (PUSH(CInput::eLeft)) {
			old = now;
			now = (now == 0) ? now = cube_size - 1 : now-1;
			t = 0;

		}
		//次のターゲットへ
		if (PUSH(CInput::eRight)) {
			old = now;
			now = (now+1) % cube_size;
			t = 0;
		}
		if(cate == 0){
			//以前のターゲットから新しいターゲットで補間する
			//距離関係なく一定時間で補間が完了する。
			//※補間途中でターゲットを切り替えると瞬時に移動する
			//補間係数を最大1.0fまで増加
			t += 0.05f;
			t = min(1.0f, t);

			cam_at = cube_pos[old] * (1 - t) + cube_pos[now] * t;

		} else
		if (cate ==1) {
			//現在の注視点と新しい注視点への座標を【割合】で混ぜる
			//距離関係なく一定時間で補間が完了する。

			cam_at = cam_at * 0.9f + cube_pos[now] * 0.1f;


		} else {
			//一定距離で補間
			//1更新で移動量
			float length = 1.0f;
			//２点間のベクトル
			CVector3D v = cam_at - cube_pos[now];
			//距離/移動量で補間係数を計算
			float t = length/v.Length();
			//上限は1.0f
			t = min(1.0f,t);

			cam_at = cam_at * (1-t) + cube_pos[now] * t;


		}
		CVector3D cam_pos_now = CVector3D(0, 200, 0);
		cam_pos = cam_pos * 0.9f + cam_pos_now * 0.1f;
	} else if(type==1){
		if (cate >= 2) cate = 0;
		//★キャラクターの回転を補間する
		//方向キーの入力方向ベクトル
		CVector3D key_dir(0, 0, 0);
		//カメラの方向ベクトル
		CVector3D cam_dir = CCamera::GetCurrent()->GetDir();
		//入力回転値
		float key_ang = 0;
		//カメラの回転値
		float cam_ang = atan2(cam_dir.x, cam_dir.z);
		//キャラクターの移動量
		const float move_speed = 1.0f;

		//方向キーから入力方向ベクトルを設定
		if (CInput::GetState(0, CInput::eHold, CInput::eUp)) key_dir.z = 1;
		if (CInput::GetState(0, CInput::eHold, CInput::eDown)) key_dir.z = -1;
		if (CInput::GetState(0, CInput::eHold, CInput::eLeft)) key_dir.x = 1;
		if (CInput::GetState(0, CInput::eHold, CInput::eRight)) key_dir.x = -1;

		//キー入力があれば
		if (key_dir.LengthSq() > 0) {
			//入力方向から入力回転値を計算
			key_ang = atan2(key_dir.x, key_dir.z);
			//カメラの回転値と入力回転値からキャラクターの回転値を決定
			//即座にrot.yに設定せず一旦目標値を設定する
			rot_target.y = cam_ang + key_ang;

			//移動処理
			CVector3D dir(sin(rot.y), 0, cos(rot.y));
			pos += dir * move_speed;

			model.ChangeAnimation(1);
		}
		else {
			model.ChangeAnimation(0);
		}
		//モーションの更新
		model.UpdateAnimation();
		//------------------------------------------------------
		//★角度の補間
		//角度差分を求める（目標値-現在値）
		//角度差分を-π(-180)～π(180)の範囲に整える
		float a = Utility::NormalizeAngle(rot_target.y- rot.y);


		if (cate == 0) {
			//割合による角度補間
			rot.y += a * 0.2f;
		}else {
			//一定量回転による角度補間
			float rot_speed = DtoR(5);
			if (a > rot_speed) {
				rot.y += rot_speed;
			}else
			if (a < -rot_speed) {
				rot.y -= rot_speed;
			} else {
				rot.y += a;
			}
		}
		//補間後は-π(-180)～π(180)の範囲に角度を整える
		rot.y = Utility::NormalizeAngle(rot.y);
		//--------------------------------------------------------
		//カメラは簡単に割合補間
		CVector3D cam_at_new = pos + CVector3D(0, 20, 0);
		CVector3D cam_pos_new = pos + CVector3D(0, 200, 200);
		cam_at = cam_at * 0.9f + cam_at_new * 0.1f;
		cam_pos = cam_pos * 0.9f + cam_pos_new * 0.1f;
	} else {

		if (cate >= 2) cate = 0;
		//ミサイルの角度補間
		//★クォータニオンの球形補間

		//ランダムな３つのターゲット
		static const int target_size = 3;
		static int target_idx = 0;
		static CVector3D target_pos[target_size] = {
			CVector3D(300,300,300),
			CVector3D(300,0,-300),
			CVector3D(-300,300,-300),
		};
		static int target_change_cnt = 0;
		if (target_change_cnt++ % 180 == 0)
			target_idx = rand() % target_size;

		//ターゲットへの回転値
		CQuaternion target_quat;
		target_quat.LookAt(pos_missile, target_pos[target_idx]);

		if(cate==0){
			//１割補間
			quat_missile = CQuaternion::Slerp(quat_missile, target_quat, 0.1);
		} else {
			//一定角回転する
			static const float rot_speed = DtoR(2.0f);
			float t = 0.1f;
			float a = 0;

			//ミサイルの方向ベクトル
			CVector3D d1 = quat_missile * CVector3D(0, 0, 1);
			//目標への方向ベクトル
			CVector3D d2 = target_quat * CVector3D(0, 0, 1);
			//内積から角度差を求める（1.0f超えないようにclamp処理）
			a = acos(min(1.0,max(-1.0,CVector3D::Dot(d1, d2))));

			//角度差から補間係数を計算

			//角度差が回転速度を下回る場合
			if (a < rot_speed)
				t = 1.0f;
			else
				t = rot_speed/a;

			quat_missile = CQuaternion::Slerp(quat_missile, target_quat, t);
		}
		const float speed = 1.0f;
		pos_missile += quat_missile * CVector3D(0, 0, speed);
		Utility::DrawSphere(target_pos[target_idx], 5.0f, CVector4D(0, 0, 1, 1));

		//--------------------------------------------------------
		//カメラは簡単に割合補間
		CVector3D cam_at_new = target_pos[target_idx] * 0.5f + pos_missile * 0.5f;
		CVector3D cam_pos_new = cam_at_new + CVector3D(0, 300, -300);
		cam_at = cam_at * 0.95f + cam_at_new * 0.05f;
		cam_pos = cam_pos * 0.95f + cam_pos_new * 0.05f;

	}


	CCamera::GetCurrent()->LookAt(cam_pos, cam_at, CVector3D(0, 1, 0));

	for (int i = 0; i < cube_size; i++)
		Utility::DrawCube(cube_pos[i], 10.0f, CVector4D(1, 0, 0, 1));

	//キャラクター表示
	model.SetPos(pos);
	model.SetRot(rot);
	model.SetScale(0.5f, 0.5f, 0.5f);
	model.Render();
	//ミサイル表示

	model_missile.SetPos(pos_missile);
	//Z軸優先でオイラー角へ変換
	model_missile.SetRot(quat_missile.GetEuler(CMatrix::eZYX));
	model_missile.SetScale(4.0f, 4.0f, 4.0f);
	model_missile.Render();


	
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(100, 0, 0), CVector4D(1, 0, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 100, 0), CVector4D(0, 1, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 0, 100), CVector4D(0, 0, 1, 1));


	static char str[3][3][128] = {
		{
			"座標線形補間 : 割合　注視点 = 前のターゲット→今のターゲット",
			"座標線形補間 : 割合　注視点 = 注視点→今のターゲット",
			"座標線形補間 : 一定速度　注視点 = 注視点→今のターゲット",
		},
		{
			"角度線形補間：割合によるキャラクターの回転値補間",
			"角度線形補間：一定速度によるキャラクターの回転値補間",
		},
		{
			"クォータニオン球形補間：割合による回転補間",
			"クォータニオン球形補間：一定速度による回転補間",
		}
	};
	FONT_T()->Draw(0, 32, 0, 0, 0, str[type][cate]);
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

	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 1000, 1200);
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
	ADD_RESOURCE("Missile", CModel::CreateModel("Wepon/Missile/Missile.obj"));

	//モデル複製
	model = COPY_RESOURCE("Antman",CModelA3M);
	model_missile = COPY_RESOURCE("Missile", CModelObj);
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