/*
	�s����g�����K�w�\���i�e�q�֌W�j
	�i��ԃQ�[���j
*/


#include "stdafx.h"
#include "Global.h"

enum {
	eBottom,	//�ԗ�����
	eTop,		//�C������
	eCannon,	//��C����
	ePartsMax,
};
//�X�^�e�B�b�N���b�V�����f��
CModelObj tank_model[ePartsMax];

//��Ԃ̊e�p�[�c�̍s��
CMatrix tank_matrix[ePartsMax];

//�ړ���
CVector3D move_vec(0, 0, 0);
//��]��
CVector3D rot_vec(0, 0, 0);

//��Ԃ̊e�p�[�c�̍��W
CVector3D tank_pos[ePartsMax] = {
	CVector3D(0, 0, 0),
	CVector3D(0, 2.95f, 0),
	CVector3D(0, 0.66f, 0)
};
//��Ԃ̊e�p�[�c�̉�]�l
CVector3D tank_rot[ePartsMax] = {
	CVector3D(0, 0, 0),
	CVector3D(0, 0, 0),
	CVector3D(0, 0, 0)
};

//�t�B�[���h���f��
CModelField* field;

void RenderSkybox();

void MainLoop(void) {


	//��]�����x
	const float rot_accel = 0.1f;
	//�ړ���
	const float move_accel = 0.05f;
	
	//�C���A��C�̉�]
	CVector2D mouse_vec = CInput::GetMouseVec();
	tank_rot[eTop].y += mouse_vec.x * -0.01f;
	tank_rot[eCannon].x += mouse_vec.y * 0.01f;
	tank_rot[eCannon].x = min(DtoR(0), max(DtoR(-30.0f), tank_rot[eCannon].x));


	//��]��������
	rot_vec *= 0.9f;
	//�ړ���������
	move_vec *= 0.9f;
	//��]����	
	tank_rot[eBottom] += rot_vec;
	//�ړ�����
	tank_pos[eBottom] += move_vec;

	//�ԗ��̉�]
	if (HOLD(CInput::eLeft)) {
		rot_vec.y += DtoR(rot_accel);
	}
	if (HOLD(CInput::eRight)) {
		rot_vec.y -= DtoR(rot_accel);
	}
	//�ړ�����
	if (HOLD(CInput::eUp)) {
		move_vec += tank_matrix[eBottom].GetFront() * move_accel;
	}

	if (HOLD(CInput::eDown)) {
		move_vec -= tank_matrix[eBottom].GetFront() * move_accel;
	}
	//-------------------------------------------------


	//��Ԃ̍s���ݒ肷��
	//���K�w�\�����\�z����@[�e�~�q](�e�p�[�c�̃��f���s��͕��s�ړ��~��]�̏��ō��)
	tank_matrix[eBottom] =
		CMatrix::MTranselate(tank_pos[eBottom])*
		CMatrix::MRotation(tank_rot[eBottom]);

	tank_matrix[eTop] = tank_matrix[eBottom]*
		CMatrix::MTranselate(tank_pos[eTop])*
		CMatrix::MRotation(tank_rot[eTop]);

	tank_matrix[eCannon] = tank_matrix[eTop] *
		CMatrix::MTranselate(tank_pos[eCannon]) *
		CMatrix::MRotation(tank_rot[eCannon]);

	//�J�����̃��f���s��
	CMatrix matrix_camera = tank_matrix[eTop]*
		CMatrix::MTranselate(0,3,-10);

	//���f���s��ŃJ������ݒ�i�����̍s������ɁA�����Ńr���[�s��ɕϊ�����j
	CCamera::GetCurrent()->SetTranseRot(matrix_camera);

	//��������`�揈��
	RenderSkybox();

	//�s����w�肵�ĕ`��
	for (int i = 0; i < ePartsMax; i++) {
		tank_model[i].Render(tank_matrix[i]);
	}

	//�t�B�[���h�\��
	field->Render();



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

	CCamera::GetCamera()->LookAt(	CVector3D(20,20,20),
									CVector3D(0,0,0),
									CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();
	//������

	//���f���̓ǂݍ���
	
	ADD_RESOURCE("TankBottom", CModel::CreateModel("Wepon/Tank/Bottom.obj"));
	ADD_RESOURCE("TankTop", CModel::CreateModel("Wepon/Tank/Top.obj"));
	ADD_RESOURCE("TankGun", CModel::CreateModel("Wepon/Tank/Gun.obj"));

	tank_model[eBottom] = COPY_RESOURCE("TankBottom", CModelObj);
	tank_model[eTop] = COPY_RESOURCE("TankTop", CModelObj);
	tank_model[eCannon] = COPY_RESOURCE("TankGun", CModelObj);



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
