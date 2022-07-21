#pragma once
#include"stdafx.h"
#include"Singleton/Singleton.h"

class Soket : public Singleton<Soket>{
public:
	struct PlayerData {
		int member_id;
		CVector2D pos;
		CVector2D vec;
		int key[CInput::eKeyMax]{0};
	};
public:

	char server_ip_addr[32];
	int port_number;

	// Windows Socketsd—l‚ÉŠÖ‚·‚éî•ñ‚ğŠi”[‚·‚é\‘¢‘Ì
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
	void Run(int _member_id);
	void Finalize();
};