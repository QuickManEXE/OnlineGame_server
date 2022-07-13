#pragma once
#include<windows.h>



class StopWatch {
public:
	StopWatch() {
		QueryPerformanceFrequency(&m_Freq);//周波数を取得
	}

	void Reset() {
		QueryPerformanceCounter(&m_Start);
	}

	double Sec()const {

		//終了時間の取得
		LARGE_INTEGER End;
		QueryPerformanceCounter(&End);

		//スタートからエンドまでにかかった周波数をなん秒あたりかの周波数で割ることでにかかった時間がわかる
		const LONGLONG TICK_DELTA = 1000000000;
		const double INV_TICK_DELTA = 1.0 / (double)TICK_DELTA;
		return (double)(((End.QuadPart - m_Start.QuadPart) * TICK_DELTA) / m_Freq.QuadPart) * INV_TICK_DELTA;

	}

private:
	LARGE_INTEGER m_Freq;//周波数
	LARGE_INTEGER m_Start;//開始時間
};