/**
*	�G�t�F�N�g�T���v��
*/
#include "stdafx.h"
#include "Global.h"
#include "GID.h"
#include "Base/Base.h"
#include "SampleClass/Effect.h"


CModelObj	model;
float		scale = 100.0f;
float		alpha = 1.0f;
CVector2D	st(0,0);

void RenderSkybox();
void ControllCamera(const CVector3D& at);
void MainLoop(void) {
	ControllCamera(CVector3D(0,0,0));
	//�X�J�C�{�b�N�X�̕`��
	RenderSkybox();
	//--------------------------------------------------------------
	//�Q�[�����̓����͂����ɏ���
	//�Q�[�����͂��̊֐�_��1�b�Ԃ�60��Ăяo���Ă���
	//--------------------------------------------------------------
	Base::CheckKillALL();
	Base::UpdateALL();
	Base::HitCheckALL();
	Base::DrawALL();
	
	if (PUSH(CInput::eButton1)) {
		for (int i = 0; i < 2; i++) {
			const float speed = 0.05f;
			CVector3D vec(Utility::Rand(-speed, speed), Utility::Rand(0.0f, speed), Utility::Rand(-speed, speed));
			Base::Add(new CParticleEffect("SmokeB", CVector3D(0, 0, 0), vec, 10.0, 2.0f, true, false));
		}
		for (int i = 0; i < 5; i++) {
			const float speed = 0.05f;
			CVector3D vec(Utility::Rand(-speed, speed), Utility::Rand(-speed, speed), Utility::Rand(-speed, speed));
			Base::Add(new CParticleEffect("Bomb", CVector3D(0, 0, 0), vec, 100.0,-1.0f, true,true));
		}
	}
	if (PUSH(CInput::eButton2)) {
		Base::Add(new CMagicEffect("CircleR", CVector3D(0, 0, 0), 100.0,120));
	}
	
	if (PUSH(CInput::eButton3)) {
		Base::Add(new CUVEffect("Bullet", CVector3D(0, 0, 0), CVector3D(0, 0, 0), 100.0, CVector2D(0.01, 0), 120));
	}
	if (HOLD(CInput::eMouseL)) {
		const float speed = 0.1f;
		CVector3D vec(Utility::Rand(-speed, speed), Utility::Rand(-speed, speed), Utility::Rand(-speed, speed));
		Base::Add(new CEffect("Bomb", CVector3D(0, 0, 0), vec, CVector3D(0,0.05f,0),50,-1.0,-0.01,CEffect::eBlendAdd,true,CVector3D::zero,CVector3D::zero));
	}
	
	
//	scale += 20.0f;
//	alpha -= 0.01f;
	//st += CVector2D(0.01f,0);
	//�X�P�[��
	//model.SetScale(scale, scale, scale);
	//�A���t�@�l
//	model.GetMaterial(0)->m_alpha = alpha;
	//UV�X���C�h
	//model.GetMaterial(0)->m_st = st;


	//���C�e�B���OOFF
	//CLight::SetLighting(false);
	//�[�x�o�b�t�@�̏������݂Ȃ�
//	glDepthMask(GL_FALSE);
	//���Z�u�����h
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//if (0) model.RenderBuilbord();
	//else model.Render();


	//���̐ݒ�֖߂�
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glDepthMask(GL_TRUE);
	//CLight::SetLighting(true);
	
	
	//���E�̎���\��
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(100, 0, 0), CVector4D(1, 0, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 100, 0), CVector4D(0, 1, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 0, 100), CVector4D(0, 0, 1, 1));
}
void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//�u�����h�̗L����
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//�Œ�V�F�[�_�[�p
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);

	CFPS::SetFPS(60);
	//�t���[�����䏉����
	CFPS::Init();
	//�{�^���̐ݒ�
	CInput::Init();
	CInput::SetButton(0, CInput::eButton1, 'Z');
	CInput::SetButton(0, CInput::eButton2, 'X');
	CInput::SetButton(0, CInput::eButton3, 'C');
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
	CInput::ShowCursor(false);
	CInput::UpDate();
	CInput::UpDate();


	//���C�g�ݒ�
	CLight::SetType(0, CLight::eLight_Direction);
	CLight::SetPos(0, CVector3D(0, 200, 200));
	CLight::SetDir(0, CVector3D(-1, -2, 1).GetNormalize());
	CLight::SetColor(0, CVector3D(0.2f, 0.2f, 0.2f), CVector3D(0.8f, 0.8f, 0.8f));


	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 700, 800);
	
	//�J����������
	CCamera::GetCamera()->LookAt(CVector3D(0, 20, -20),
		CVector3D(0, 0, 0),
		CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();

	

	//������

	
	ADD_RESOURCE("Bomb", CModel::CreateModel("Effect/Bomb.obj"));
	ADD_RESOURCE("Smoke", CModel::CreateModel("Effect/Smoke.obj"));
	ADD_RESOURCE("SmokeB", CModel::CreateModel("Effect/SmokeB.obj"));
	ADD_RESOURCE("Bullet", CModel::CreateModel("Effect/bullet.obj"));
	ADD_RESOURCE("CircleR", CModel::CreateModel("Effect/CircleR.obj"));

	//model = COPY_RESOURCE("Bullet",CModelObj);

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

	//��ʉ𑜓x�ϓ�
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//��ʉ𑜓x�Œ�
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera::GetCamera()->SetScreenRect(CRect(0, 0, (float)w, (float)h));
	CCamera::GetCamera()->Viewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	CMatrix mProj;
	mProj.Perspective(Utility::DgreeToRadian(45.0), (float)w / (float)h, 1.0, 10000.0);
	CCamera::GetCurrent()->SetProjectionMatrix(mProj);
	glLoadMatrixf(mProj.f);

	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
	GL::window_x = x;
	GL::window_y = y;
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
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

//�t���X�N���[��?�E�C���h�E���[�h�̐؂�ւ�
//Alt+Enter�Ő؂�ւ���
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
	// ���������[�N���o
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
		//���݂̃V�X�e���̃J�E���g�����擾
		QueryPerformanceCounter(&time_buf);

		CInput::UpDate();
		//�e�o�b�t�@�[���N���A
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
		skybox = GET_RESOURCE("Sky",CModel);
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

void ControllCamera(const CVector3D& at) {
	//�J�����̈ʒu
	static CVector3D cam_pos(0, 0, 0);
	//�J�����̉�]�l
	static CVector3D cam_rot(0, 0, 0);
	//�J�����̋���
	static float cam_dist = 200;

	//�}�E�X���삩��J��������]

	//�}�E�X�ړ���
	CVector2D mouse_vec = CInput::GetMouseVec();
	cam_rot.y += mouse_vec.x * -0.01f;
	cam_rot.x += mouse_vec.y * -0.01f;
	//�J�����̋�����ύX
	cam_dist += CInput::GetMouseWheel() * 5.0f;
	//�J�����̈ʒu���v�Z
	cam_pos = at + CMatrix::MRotation(cam_rot).GetFront() * -cam_dist;

	//�ʒu�ƒ����_��ݒ肵�ăJ�������X�V
	CCamera::GetCurrent()->LookAt(cam_pos, at, CVector3D(0, 1, 0));
}
