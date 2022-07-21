#pragma once
#include"stdafx.h"

class Soket {
public:
	struct CVector2DAndID {
		int member_id;
		CVector2D pos;
	};
public:

	char server_ip_addr[32];
	int port_number;

	// Windows Sockets�d�l�Ɋւ�������i�[����\����
	WSADATA wsa_data;
	
	struct sockaddr_in dst_addr;
	
	int dst_socket;

	char send_buf1[256], send_buf2[256];
	char recv_buf[256];

	CVector2D pos;

	struct timeval t_val = { 0, 1000 };

	fd_set fds, readfds;

	CVector2D receve_pos;

public:
	Soket();
	void Init(int _member_id);
	void Run(int _member_id, CVector2D* pos);
	void Finalize();
	CVector2D RecvRenderUpdateData();
};