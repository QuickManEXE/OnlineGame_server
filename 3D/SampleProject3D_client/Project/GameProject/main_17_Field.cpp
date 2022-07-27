/*
	�t�B�[���h�쐬
	.field�̓ǂݍ���
	�R���W�����ݒ�t�����f���ǂݍ���
*/


#include "stdafx.h"
#include "Global.h"
//���[�V�����L���f���N���X
CModelA3M model;
//���W
CVector3D pos(0,0,0);
//�ړ���
CVector3D vec(0, 0, 0);
//��]
CVector3D rot(0, 0, 0);
//��]�s��
CMatrix rot_matrix;
//���a
float rad = 10.0f;
//���t�B�[���h���f��
CModelField* field;


//���������f��
CModelObj farm_house;

void RenderSkybox();

void ControllCamera(const CVector3D& at);

void CollisionModel(CVector3D* pos, CVector3D* vec ,float rad, CModel* model) {
	//���f���Ƃ̔���(��)
	//�Փ˃f�[�^�i�[�p
	CCollTriangle out[256];
	//�����߂���
	CVector3D v(0, 0, 0);
	//���ƃ��f���Ƃ̏Փ�
	//�G���[���o����c�P�E�ǂݍ���łȂ��Ȃ��@�Q�E�R���W������ݒ肵�Ă��Ȃ�
	int cnt = model->CollisionSphere(out, *pos + CVector3D(0, rad, 0), rad, 250);
	//�ڐG�����ʂ̐��J��Ԃ�
	for (int i = 0; i < cnt; i++) {
		//�ڐG�����ʂ��΂߂���������Ă�����n��
		if (out[i].m_normal.y > 0.5f) {
			//�d�͗������x��0�ɖ߂�
			if (vec->y < 0) {
				vec->y = 0;
			}
		}
		//�ڐG�����ʂ̕����ցA�߂荞�񂾕������߂�
		CVector3D nv = out[i].m_normal * (rad - out[i].m_dist);
		//�ł��傫�Ȉړ��ʂ����߂�
		v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
		v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
		v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
	}
	//�����߂�
	*pos += v;

}

void CollisionModel(CVector3D* pos,CModel* model) {
	CVector3D cross;
	CVector3D normal;
	if (model->CollisionRay(&cross, &normal, *pos + CVector3D(0, 500, 0), *pos)) {
		pos->y = cross.y;
	}
}

void MainLoop(void) {


	//�����L�[�̓��͕����x�N�g��
	CVector3D key_dir(0, 0, 0);
	//�J�����̕����x�N�g��
	CVector3D cam_dir = CCamera::GetCurrent()->GetDir();
	//���͉�]�l
	float key_ang = 0;
	//�J�����̉�]�l
	float cam_ang = atan2(cam_dir.x, cam_dir.z);

	float move_speed = 2.0f;
	if (HOLD(CInput::eButton6)) move_speed *= 10;
	//�����L�[������͕����x�N�g����ݒ�
	if (HOLD(CInput::eUp)) key_dir.z = 1;
	if (HOLD(CInput::eDown)) key_dir.z = -1;
	if (HOLD(CInput::eLeft)) key_dir.x = 1;
	if (HOLD(CInput::eRight)) key_dir.x = -1;
	//�L�[���͂������
	if (key_dir.LengthSq() > 0) {
		//���͕���������͉�]�l���v�Z
		key_ang = atan2(key_dir.x, key_dir.z);
		//�J�����̉�]�l�Ɠ��͉�]�l����L�����N�^�[�̉�]�l������
		rot.y += Utility::NormalizeAngle(Utility::NormalizeAngle(cam_ang + key_ang)- rot.y)*0.15f;
		//�ړ�����
		CVector3D dir(sin(rot.y), 0, cos(rot.y));
		pos += dir * move_speed;
		model.ChangeAnimation(1);
	} else {
		model.ChangeAnimation(0);
	}
	//����
	vec.y -= GRAVITY;
	pos += vec;
	//���[�V����r�̍X�V
	model.UpdateAnimation();

	//���f���Ƃ̏Փ�
	CollisionModel(&pos,&vec,rad,&farm_house);
	CollisionModel(&pos, &vec, rad, field);
	//CollisionModel(&pos,field);
	//�J����
	ControllCamera(pos + CVector3D(0, 80, 0));
	
	//�X�J�C�{�b�N�X�̕`��
	RenderSkybox();


	//���t�B�[���h�`��
	field->Render();

	//�������`��
	farm_house.Render();

	//�L�����N�^�[�\��
	model.SetPos(pos);
	model.SetRot(rot);
	model.SetScale(0.5f, 0.5f, 0.5f);
	model.Render();


	Utility::DrawSphere(pos + CVector3D(0, rad, 0), rad, CVector4D(1, 0, 0, 1));
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
	CInput::SetButton(0, CInput::eButton6, VK_SHIFT);
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
	
	//���t�H�O
	CLight::SetFogParam(CVector4D(1, 1, 1, 1),7000, 9000);

	//�J����������

	CCamera::GetCamera()->LookAt(	CVector3D(200,200,200),
									CVector3D(0,10,0),
									CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();
	//������

	//���f���̓ǂݍ���

	ADD_RESOURCE("Antman", CModel::CreateModel("Charactor/antman/antman.a3m"));
	//��.field�̓ǂݍ���[Field/Land/land.field]
	ADD_RESOURCE("Field", CModel::CreateModel("Field/Land/land2.field"));

	//���R���W�����ݒ�t���ǂݍ���[Field/FarmHouse/FarmHouse.obj] 4,2,4
	ADD_RESOURCE("FarmHouse",
		CModel::CreateModel("Field/FarmHouse/FarmHouse.obj",4,2,4));


	//���f������
	model = COPY_RESOURCE("Antman",CModelA3M);

	//���t�B�[���h���f���͖{�̂��Q�Ƃ���
	field = GET_RESOURCE("Field", CModelField);
	//���X�P�[���ݒ�
	field->SetScale(1000,1000,1000);
	//���`�拗���ݒ�
	field->SetDrawLength(9000);

	//���������f���𕡐����Ď擾
	farm_house = COPY_RESOURCE("FarmHouse",CModelObj);
	farm_house.SetPos(200, -50, 0);
	farm_house.SetScale(10, 10, 10);

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

void ControllCamera(const CVector3D& at) {
	//�J�����̈ʒu
	static CVector3D cam_pos(0, 0, 0);
	//�J�����̉�]�l
	static CVector3D cam_rot(0, 0, 0);
	//�J�����̋���
	static float cam_dist = 200;
	//�����_�@��Ɏ��_���ړ�����
	CVector3D cam_at = at + CVector3D(0, 80, 0);
	//�}�E�X���삩��J��������]----
	//�}�E�X�ړ���
	CVector2D mouse_vec = CInput::GetMouseVec();
	cam_rot.y += mouse_vec.x * -0.01f;
	cam_rot.x += mouse_vec.y * 0.01f;
	//if���ɂ�鐧��
	//if (cam_rot.x > DtoR(45)) cam_rot.x = DtoR(45);
	//if (cam_rot.x < DtoR(-10)) cam_rot.x = DtoR(-10);
	//min,max�֐��ɂ�鐧��
	//cam_rot.x = min(DtoR(45), cam_rot.x);
	//cam_rot.x = max(DtoR(-10), cam_rot.x);
	//clamp�֐��Ɠ����̏���
	cam_rot.x = min(DtoR(45), max(DtoR(-10), cam_rot.x));

	//�J�����̋�����ύX
	cam_dist += CInput::GetMouseWheel() * 5.0f;
	//�J�����̈ʒu���v�Z
	CVector3D dir = CMatrix::MRotation(cam_rot).GetFront();
	//CVector3D dir(sin(cam_rot.y),0,cos(cam_rot.y));
	cam_pos = cam_at + dir * -cam_dist;
	//�ʒu�ƒ����_��ݒ肵�ăJ�������X�V
	CCamera::GetCurrent()->LookAt(cam_pos, cam_at, CVector3D(0, 1, 0));
}