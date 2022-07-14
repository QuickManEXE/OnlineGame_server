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

	char send_buf1[256], send_buf2[256];
	char recv_buf[256];

	CVector3D pos;

	struct timeval t_val = { 0, 1000 };

	fd_set fds, readfds;

	CVector3D receve_pos;
public:
	Soket();
	void Init();
	void Run();
	void Finalize();
	CVector3D RecvRenderUpdateData();
};