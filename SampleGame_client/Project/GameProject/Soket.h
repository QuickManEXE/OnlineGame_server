#pragma once
#include"stdafx.h"

class Soket {

public:

	char server_ip_addr[32];
	int port_number;

	// Windows Socketsd—l‚ÉŠÖ‚·‚éî•ñ‚ğŠi”[‚·‚é\‘¢‘Ì
	WSADATA wsa_data;
	
	struct sockaddr_in dst_addr;
	
	int dst_socket;

public:
	Soket();
	void Init();
	void Run();
	void Finalize();

};