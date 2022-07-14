#pragma once
#include"stdafx.h"


class Soket {

public:

	static const UINT WM_ASYNC = (WM_USER + 1);	// 非同期通信イベントID

	WSADATA wsaData;

	SOCKET sock;
	struct sockaddr_in addr;

	char buf[2048];

	CVector3D pos;

	CVector3D receve_pos;

public:
	void Init();
	void Run();
	void finalize();
	void SendRenderUpdateData(CVector3D _pos);
};