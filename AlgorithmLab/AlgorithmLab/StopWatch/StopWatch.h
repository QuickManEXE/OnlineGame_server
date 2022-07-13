#pragma once
#include<windows.h>



class StopWatch {
public:
	StopWatch() {
		QueryPerformanceFrequency(&m_Freq);//���g�����擾
	}

	void Reset() {
		QueryPerformanceCounter(&m_Start);
	}

	double Sec()const {

		//�I�����Ԃ̎擾
		LARGE_INTEGER End;
		QueryPerformanceCounter(&End);

		//�X�^�[�g����G���h�܂łɂ����������g�����Ȃ�b�����肩�̎��g���Ŋ��邱�Ƃłɂ����������Ԃ��킩��
		const LONGLONG TICK_DELTA = 1000000000;
		const double INV_TICK_DELTA = 1.0 / (double)TICK_DELTA;
		return (double)(((End.QuadPart - m_Start.QuadPart) * TICK_DELTA) / m_Freq.QuadPart) * INV_TICK_DELTA;

	}

private:
	LARGE_INTEGER m_Freq;//���g��
	LARGE_INTEGER m_Start;//�J�n����
};