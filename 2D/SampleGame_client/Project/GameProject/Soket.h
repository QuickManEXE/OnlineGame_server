#pragma once
#include"stdafx.h"
#include"Singleton/Singleton.h"
#include"PlayerDataManager.h"


class Soket : public Singleton<Soket>{
public:

	char server_ip_addr[32];
	int port_number;

	// Windows Sockets仕様に関する情報を格納する構造体
	WSADATA wsa_data;
	
	struct sockaddr_in dst_addr;
	int addlen;
	int dst_socket;

	char send_buf1[256], send_buf2[256];
	char recv_buf[256];

	CVector2D pos;

	struct timeval t_val = { 0, 1000 };

	fd_set fds, readfds;

public:

	PlayerDataManager::PlayerData playerData;

	std::map<int, PlayerDataManager::MemberData> m_members_data;
public:
	Soket();
	void Init(int _member_id);
	void Run(PlayerDataManager::PlayerData* pd);
	void Finalize();
	void ReceiveMembersData();
};