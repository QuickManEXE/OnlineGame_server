#pragma once
#include"stdafx.h"


class Soket {

public:
	WSADATA wsaData;

	SOCKET sock;
	struct sockaddr_in addr;

	char buf[2048];

public:
	void Init();
	void Run();
	void finalize();
};