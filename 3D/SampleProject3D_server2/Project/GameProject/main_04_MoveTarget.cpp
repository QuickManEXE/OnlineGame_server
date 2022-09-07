/*
	�RD�Q�[���ł̃L�����N�^�[�̈ړ�
	�w��ֈʒu�ֈړ�
*/


#include "stdafx.h"
#include "Global.h"
//�����[�V�����L���f���N���X
CModelA3M model;
//�����W
CVector3D pos(0,0,0);
//����]
CVector3D rot(0, 0, 0);



//�^�[�Q�b�g���W
CVector3D target(50,0,0);


void MainLoop(void) {
	//�L�����N�^�[�ړ�
	//�ړ���
	const float move_speed = 1.0f;
	
	//���L�����N�^�[���^�[�Q�b�g�֌����Ĉړ�������
	//�P�D�L�����N�^�[�̉�]�l���^�[�Q�b�g�ւ̕�������t�Z����
	//�L�����N�^�[����^�[�Q�b�g�ւ̃x�N�g��
	CVector3D vec = target - pos;
	//atan2���g���^�[�Q�b�g�ւ̃x�N�g�������]�l���v�Z
	rot.y = atan2(vec.x,vec.z);



	//�Q�D���̋���������΃L�����N�^�[��O�i������
	//vec.Length()�Ńx�N�g���̑傫�����킩��
	


	//0�ԁi�ҋ@�j�̃A�j���[�V�������Đ�
	model.ChangeAnimation(0);
	//�A�j���[�V�������X�V
	model.UpdateAnimation();

	//���L�����N�^�[�̍��W�A��]�A�X�P�[���ݒ�ƕ\��
	model.SetPos(pos);
	model.SetRot(rot);
	//�`��
	model.Render();


	//�^�[�Q�b�g�̈ʒu
	//���͋C�ɂ��Ȃ�
	//�}�E�X�̍��W�i�X�N���[�����W�j
	CVector2D m= CInput::GetMousePoint();
	//�}�E�X�̍��W�F�߁i���[���h���W�j
	CVector3D m_w_near;
	//�}�E�X�̍��W�F���i���[���h���W�j
	CVector3D m_w_far;
	//�X�N���[�����W�����[���h���W�ϊ�
	Utility::ScreenToWorld(&m_w_near, CVector3D(m.x,m.y, 0));
	Utility::ScreenToWorld(&m_w_far, CVector3D(m.x, m.y, 1.0f));
	//�Q�[�����w�U�����ƖʂƂ̏Փ˂Ŋw�K------------------------
	//���̕���
	CVector3D lay = (m_w_far - m_w_near).GetNormalize();
	//�ʂ̖@��
	CVector3D N(0, 1, 0);
	//�ʏ�̓_
	CVector3D P(0, 0, 0);
	//�ʂƐ��Ƃ̏Փ˒n�_
	target = m_w_near + lay * CVector3D::Dot(P- m_w_near, N)/ CVector3D::Dot(lay, N);
	//------------------------------------------------
	//�^�[�Q�b�g�̕\��
	Utility::DrawCube(target, 5.0f, CVector4D(1, 0, 0, 1));


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


	//���C�g�ݒ�
	CLight::SetType(0, CLight::eLight_Direction);
	CLight::SetPos(0, CVector3D(0, 200, 200));
	CLight::SetDir(0, CVector3D(-1, -2, 1).GetNormalize());
	CLight::SetColor(0, CVector3D(0.4f, 0.4f, 0.4f), CVector3D(0.6f, 0.6f, 0.6f));

//	CLight::SetType(1, CLight::eLight_Point);
//	CLight::SetColor(1, CVector3D(0.0f, 0.0f, 0.0f), CVector3D(1.0f, 1.0f, 1.0f));
//	CLight::SetAttenuation(1,0.10f);
//	CLight::SetRadiationAngle(1, Utility::DgreeToRadian(5.0f));

	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 700, 800);
	//�J����������

	CCamera::GetCamera()->LookAt(	CVector3D(200,200,200),
									CVector3D(0,10,0),
									CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();
	//������

	//�����f���̓ǂݍ���
	//Charactor/antman/antman.a3m
	ADD_RESOURCE("Antman", CModel::CreateModel("Charactor/antman/antman.a3m"));

	//�����f������
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

	//��ʉ𑜓x�ϓ�
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//��ʉ𑜓x�Œ�
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
