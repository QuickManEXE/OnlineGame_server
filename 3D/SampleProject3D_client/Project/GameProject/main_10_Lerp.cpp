/*
	���`���
	�i�ʒu�A�p�x�j
*/


#include "stdafx.h"
#include "Global.h"
//���[�V�����L���f���N���X
CModelA3M model;
//���W
CVector3D pos(0,0,0);
//��]
CVector3D rot(0, 0, 0);
//��]�̖ڕW�l
CVector3D rot_target(0, 0, 0);


//�������闧����
const int cube_size = 3;
CVector3D cube_pos[cube_size] = {
	CVector3D(200, 0, 0),
	CVector3D(0, 0, 200),
	CVector3D(-200, 0, 200),
};



//�~�T�C�����f��
CModelObj	model_missile;
//�~�T�C�����W
CVector3D	pos_missile(0, 10, -10);
//�~�T�C����](�N�H�[�^�j�I��)
CQuaternion quat_missile;


//�J�����̈ʒu
CVector3D cam_pos(0, 0, 0);
//�J�����̒����_
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
		//�����X�Ǝ��_��ς���ۂɒ����_��⊮����T���v��
		static int now = 0;
		static int old = 0;

		//��ԌW�� 0 �` 1
		static float t = 0;


		//�O�̃^�[�Q�b�g��
		if (PUSH(CInput::eLeft)) {
			old = now;
			now = (now == 0) ? now = cube_size - 1 : now-1;
			t = 0;

		}
		//���̃^�[�Q�b�g��
		if (PUSH(CInput::eRight)) {
			old = now;
			now = (now+1) % cube_size;
			t = 0;
		}
		if(cate == 0){
			//�ȑO�̃^�[�Q�b�g����V�����^�[�Q�b�g�ŕ�Ԃ���
			//�����֌W�Ȃ���莞�Ԃŕ�Ԃ���������B
			//����ԓr���Ń^�[�Q�b�g��؂�ւ���Əu���Ɉړ�����
			//��ԌW�����ő�1.0f�܂ő���
			t += 0.05f;
			t = min(1.0f, t);

			cam_at = cube_pos[old] * (1 - t) + cube_pos[now] * t;

		} else
		if (cate ==1) {
			//���݂̒����_�ƐV���������_�ւ̍��W���y�����z�ō�����
			//�����֌W�Ȃ���莞�Ԃŕ�Ԃ���������B

			cam_at = cam_at * 0.9f + cube_pos[now] * 0.1f;


		} else {
			//��苗���ŕ��
			//1�X�V�ňړ���
			float length = 1.0f;
			//�Q�_�Ԃ̃x�N�g��
			CVector3D v = cam_at - cube_pos[now];
			//����/�ړ��ʂŕ�ԌW�����v�Z
			float t = length/v.Length();
			//�����1.0f
			t = min(1.0f,t);

			cam_at = cam_at * (1-t) + cube_pos[now] * t;


		}
		CVector3D cam_pos_now = CVector3D(0, 200, 0);
		cam_pos = cam_pos * 0.9f + cam_pos_now * 0.1f;
	} else if(type==1){
		if (cate >= 2) cate = 0;
		//���L�����N�^�[�̉�]���Ԃ���
		//�����L�[�̓��͕����x�N�g��
		CVector3D key_dir(0, 0, 0);
		//�J�����̕����x�N�g��
		CVector3D cam_dir = CCamera::GetCurrent()->GetDir();
		//���͉�]�l
		float key_ang = 0;
		//�J�����̉�]�l
		float cam_ang = atan2(cam_dir.x, cam_dir.z);
		//�L�����N�^�[�̈ړ���
		const float move_speed = 1.0f;

		//�����L�[������͕����x�N�g����ݒ�
		if (CInput::GetState(0, CInput::eHold, CInput::eUp)) key_dir.z = 1;
		if (CInput::GetState(0, CInput::eHold, CInput::eDown)) key_dir.z = -1;
		if (CInput::GetState(0, CInput::eHold, CInput::eLeft)) key_dir.x = 1;
		if (CInput::GetState(0, CInput::eHold, CInput::eRight)) key_dir.x = -1;

		//�L�[���͂������
		if (key_dir.LengthSq() > 0) {
			//���͕���������͉�]�l���v�Z
			key_ang = atan2(key_dir.x, key_dir.z);
			//�J�����̉�]�l�Ɠ��͉�]�l����L�����N�^�[�̉�]�l������
			//������rot.y�ɐݒ肹����U�ڕW�l��ݒ肷��
			rot_target.y = cam_ang + key_ang;

			//�ړ�����
			CVector3D dir(sin(rot.y), 0, cos(rot.y));
			pos += dir * move_speed;

			model.ChangeAnimation(1);
		}
		else {
			model.ChangeAnimation(0);
		}
		//���[�V�����̍X�V
		model.UpdateAnimation();
		//------------------------------------------------------
		//���p�x�̕��
		//�p�x���������߂�i�ڕW�l-���ݒl�j
		//�p�x������-��(-180)�`��(180)�͈̔͂ɐ�����
		float a = Utility::NormalizeAngle(rot_target.y- rot.y);


		if (cate == 0) {
			//�����ɂ��p�x���
			rot.y += a * 0.2f;
		}else {
			//���ʉ�]�ɂ��p�x���
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
		//��Ԍ��-��(-180)�`��(180)�͈̔͂Ɋp�x�𐮂���
		rot.y = Utility::NormalizeAngle(rot.y);
		//--------------------------------------------------------
		//�J�����͊ȒP�Ɋ������
		CVector3D cam_at_new = pos + CVector3D(0, 20, 0);
		CVector3D cam_pos_new = pos + CVector3D(0, 200, 200);
		cam_at = cam_at * 0.9f + cam_at_new * 0.1f;
		cam_pos = cam_pos * 0.9f + cam_pos_new * 0.1f;
	} else {

		if (cate >= 2) cate = 0;
		//�~�T�C���̊p�x���
		//���N�H�[�^�j�I���̋��`���

		//�����_���ȂR�̃^�[�Q�b�g
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

		//�^�[�Q�b�g�ւ̉�]�l
		CQuaternion target_quat;
		target_quat.LookAt(pos_missile, target_pos[target_idx]);

		if(cate==0){
			//�P�����
			quat_missile = CQuaternion::Slerp(quat_missile, target_quat, 0.1);
		} else {
			//���p��]����
			static const float rot_speed = DtoR(2.0f);
			float t = 0.1f;
			float a = 0;

			//�~�T�C���̕����x�N�g��
			CVector3D d1 = quat_missile * CVector3D(0, 0, 1);
			//�ڕW�ւ̕����x�N�g��
			CVector3D d2 = target_quat * CVector3D(0, 0, 1);
			//���ς���p�x�������߂�i1.0f�����Ȃ��悤��clamp�����j
			a = acos(min(1.0,max(-1.0,CVector3D::Dot(d1, d2))));

			//�p�x�������ԌW�����v�Z

			//�p�x������]���x�������ꍇ
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
		//�J�����͊ȒP�Ɋ������
		CVector3D cam_at_new = target_pos[target_idx] * 0.5f + pos_missile * 0.5f;
		CVector3D cam_pos_new = cam_at_new + CVector3D(0, 300, -300);
		cam_at = cam_at * 0.95f + cam_at_new * 0.05f;
		cam_pos = cam_pos * 0.95f + cam_pos_new * 0.05f;

	}


	CCamera::GetCurrent()->LookAt(cam_pos, cam_at, CVector3D(0, 1, 0));

	for (int i = 0; i < cube_size; i++)
		Utility::DrawCube(cube_pos[i], 10.0f, CVector4D(1, 0, 0, 1));

	//�L�����N�^�[�\��
	model.SetPos(pos);
	model.SetRot(rot);
	model.SetScale(0.5f, 0.5f, 0.5f);
	model.Render();
	//�~�T�C���\��

	model_missile.SetPos(pos_missile);
	//Z���D��ŃI�C���[�p�֕ϊ�
	model_missile.SetRot(quat_missile.GetEuler(CMatrix::eZYX));
	model_missile.SetScale(4.0f, 4.0f, 4.0f);
	model_missile.Render();


	
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(100, 0, 0), CVector4D(1, 0, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 100, 0), CVector4D(0, 1, 0, 1));
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 0, 100), CVector4D(0, 0, 1, 1));


	static char str[3][3][128] = {
		{
			"���W���`��� : �����@�����_ = �O�̃^�[�Q�b�g�����̃^�[�Q�b�g",
			"���W���`��� : �����@�����_ = �����_�����̃^�[�Q�b�g",
			"���W���`��� : ��葬�x�@�����_ = �����_�����̃^�[�Q�b�g",
		},
		{
			"�p�x���`��ԁF�����ɂ��L�����N�^�[�̉�]�l���",
			"�p�x���`��ԁF��葬�x�ɂ��L�����N�^�[�̉�]�l���",
		},
		{
			"�N�H�[�^�j�I�����`��ԁF�����ɂ���]���",
			"�N�H�[�^�j�I�����`��ԁF��葬�x�ɂ���]���",
		}
	};
	FONT_T()->Draw(0, 32, 0, 0, 0, str[type][cate]);
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

	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 1000, 1200);
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
	ADD_RESOURCE("Missile", CModel::CreateModel("Wepon/Missile/Missile.obj"));

	//���f������
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