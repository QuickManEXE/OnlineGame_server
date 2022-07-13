#pragma once
#include"stdafx.h"

class Soket {

public:

	char server_ip_addr[32];
	int port_number;

	// Windows Sockets仕様に関する情報を格納する構造体
	WSADATA wsa_data;
	
	struct sockaddr_in dst_addr;
	
	int dst_socket;

public:
	Soket();
	void Init();
	void Run();
	void Finalize();

};