#pragma once
#include"stdafx.h"


class Soket {
public:
	struct CVector2DAndID {
		int member_id;
		CVector2D pos;
	};
public:

	static const UINT WM_ASYNC = (WM_USER + 1);	// 非同期通信イベントID

	WSADATA wsaData;

	SOCKET sock;
	struct sockaddr_in addr;

	char buf[2048];

	sockaddr_in fromaddr;
	int addrlen = sizeof(fromaddr);

	CVector2DAndID mempos;
public:
	void Init();
	void Run(CVector2D* pos);
	void finalize();
	void SendRenderUpdateData(CVector3D _pos);
};