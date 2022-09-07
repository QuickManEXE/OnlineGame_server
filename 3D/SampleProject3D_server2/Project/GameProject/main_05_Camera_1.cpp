/*
	��_�J����
*/


#include "stdafx.h"
#include "Global.h"
//���[�V�����L���f���N���X
CModelA3M model;
//���W
CVector3D pos(0,0,0);
//��]
CVector3D rot(0, 0, 0);



void PointCamera() {
	//��_�J����

	//�J�����ݒu�|�C���g�̐�
#define CAMERA_POINT_MAX	3
	//���݂̐ݒu�|�C���g
	static int camera_idx = 0;

	//�ʒu�f�[�^
	static CVector3D camera_pos[CAMERA_POINT_MAX] = {
		CVector3D(200,0,0),
		CVector3D(0,200,0),
		CVector3D(0,0,200)
	};
	//��]�l�f�[�^
	static CVector3D camera_rot[CAMERA_POINT_MAX] = {
		CVector3D(0,DtoR(-90),0),
		CVector3D(DtoR(90),0,0),
		CVector3D(0,DtoR(180),0)
	};
	//���̐ݒu�|�C���g��
	if (CInput::GetState(0, CInput::ePush, CInput::eMouseL)) {
		camera_idx = (camera_idx + 1) % CAMERA_POINT_MAX;
	}
	//�ʒu�Ɖ�]�ݒ肵�ăJ�������X�V
	CCamera::GetCurrent()->SetTranseRot(camera_pos[camera_idx], camera_rot[camera_idx]);


}
void LookAtCamera(const CVector3D& at) {
	//�J�����̈ʒu
	CVector3D camera_pos(0, 200, 200);
	//�ʒu�ƒ����_��ݒ肵�ăJ�������X�V
	CCamera::GetCurrent()->LookAt(camera_pos, at, CVector3D(0, 1, 0));
}
void RailCamera(const CVector3D& at) {
	//���[���̎n�_�ƏI�_
	CVector3D points[2] = { CVector3D(-200,200,200),CVector3D(200,200,200) };
	//�J�����̈ʒu�����[�����at�ƍł��߂��Ȃ�ʒu�֐ݒ肷��
	CVector3D camera_pos = CCollision::PointOnLineSegmentNearestPoint(points[0], points[1], at);
	//�ʒu�ƒ����_��ݒ肵�ăJ�������X�V
	CCamera::GetCurrent()->LookAt(camera_pos, at, CVector3D(0, 1, 0));
}
void MainLoop(void) {
	bool move_flag = false;
	CVector3D dir(sin(rot.y), 0, cos(rot.y));
	const float move_speed = 1.0f;

	if (CInput::GetState(0, CInput::eHold, CInput::eUp)) {
		move_flag = true;
		pos += dir * move_speed;
	}

	if (CInput::GetState(0, CInput::eHold, CInput::eLeft))
		rot.y += DtoR(1.0f);
	if (CInput::GetState(0, CInput::eHold, CInput::eRight))
		rot.y -= DtoR(1.0f);
	if (move_flag)
		model.ChangeAnimation(1);
	else
		model.ChangeAnimation(0);

	//���[�V�����̍X�V
	model.UpdateAnimation();

	//�J�����ݒ�
	enum {
		eCamera_Point,	//��_�J����
		eCamera_LookAt,	//�����J����
		eCamera_Rail,	//���[���J����
		eCamera_Max,
	};

	//�J�����̎��
	static int camera_type = eCamera_Point;

	//���̃J������ނ�
	if (CInput::GetState(0, CInput::ePush, CInput::eMouseR)) {
		camera_type = (camera_type + 1) % eCamera_Max;
	}
	//�J�����̎�ނ��ƂɃJ������ݒ�
	switch (camera_type)
	{
	case eCamera_Point:
		PointCamera();
		FONT_T()->Draw(420, 96, 0, 0, 0, "���N���b�N�F�A���O���؂�ւ�");
		break;
	case eCamera_LookAt:
		LookAtCamera(pos);
		break;
	case eCamera_Rail:
		RailCamera(pos);
		break;
	default:
		break;
	}

	//���ʒu�ƒ����_��ݒ�
	//CCamera::GetCurrent()->LookAt(CVector3D(0,100,100),
	//								pos,CVector3D(0, 1, 0));
	
	//���ʒu�Ɖ�]�l��ݒ�
	CCamera::GetCurrent()->SetTranseRot(
		CVector3D(-100, 100, 100),
		CVector3D(DtoR(15),DtoR(135),0));

	//�L�����N�^�[�\��
	model.SetPos(pos);
	model.SetRot(rot);
	model.SetScale(0.5f, 0.5f, 0.5f);
	model.Render();

	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(100, 0, 0), CVector4D(1, 0, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 100, 0), CVector4D(0, 1, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 0, 100), CVector4D(0, 0, 1, 1));
	char str[eCamera_Max][64] = { "��_�J����","�����J����", "���[���J����" };
//	FONT_T()->Draw(0, 32, 0, 0, 0, str[camera_type]);
//	FONT_T()->Draw(0, 64, 0, 0, 0, "�E�N���b�N�F�J�����̎�ނ̐؂�ւ�");
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
