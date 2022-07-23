#pragma once
#include"stdafx.h"
#include"Charactor\CPlayer.h"
#include"Singleton\Singleton.h"

class Soket : public Singleton<Soket> {
public:

	static const UINT WM_ASYNC = (WM_USER + 1);	// 非同期通信イベントID

	WSADATA wsaData;

	SOCKET sock;
	struct sockaddr_in addr;

	char buf[2048];

	sockaddr_in fromaddr;
	int addrlen = sizeof(fromaddr);
private:
	int m_unique_member_id;//この通信を行うサーバーのID
public:
	void Init();
	void Run();
	void finalize();
};