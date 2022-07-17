#include "Soket.h"
#include"GameManager.h"
#include<iostream>


#pragma comment(lib, "Ws2_32.lib")

Soket::Soket()
{
}

void Soket::Init(int _member_id)
{
	if (_member_id != GameManager::id)return;

	// WinSockの初期化処理(Version 2.0)
	if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
		std::cerr << "Winsockの初期化失敗(WSAStartup)" << std::endl;
	}

	// ユーザ入力
	std::cout << "接続先IPアドレスを入力してください(xxx.xxx.xxx.xxx)" << std::endl;
	std::cin >> server_ip_addr;
	std::cout << "ポート番号を入力してください" << std::endl;
	std::cin >> port_number;

	// sockaddr_in構造体の作成とポート番号、IPタイプの入力
	memset(&dst_addr, 0, sizeof(dst_addr));
	dst_addr.sin_port = htons(port_number);		// ポート番号
	dst_addr.sin_family = AF_INET;				// AF_INETはipv4を示す
	//dst_addr.sin_addr.S_un.S_addr = inet_addr(server_ip_addr);

	// 引数は (1) Type(ipv4 or v6) (2) IPアドレスのテキスト形式 (3) IPアドレスのバイナリ形式【(2)→(3)に変換】
	inet_pton(dst_addr.sin_family, server_ip_addr, &dst_addr.sin_addr.s_addr);
	
	
	// AF_INETはipv4のIPプロトコル & SOCK_STREAMはTCPプロトコル
	dst_socket = socket(AF_INET, SOCK_DGRAM, 0);
	
	// ここで、ノンブロッキングに設定しています。
	// val = 0でブロッキングモードに設定できます。
	// ソケットの初期設定はブロッキングモードです。
	u_long val = 1;
	ioctlsocket(dst_socket, FIONBIO, &val);

	receve_pos = CVector2D::zero;

	//// 接続処理
	//if (connect(dst_socket, (struct sockaddr*)&dst_addr, sizeof(dst_addr))) {
	//	std::cerr << "接続失敗(サーバIPアドレス" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl;
	//	exit(0);
	//}

	std::cout << "接続完了(サーバIPアドレス" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl << std::endl;
	
	//FD_ZERO(&readfds);
	//FD_SET(dst_socket, &readfds);
}

void Soket::Run(int _member_id, CVector2D* pos)
{
	if (_member_id != GameManager::id)return;

	/*int i;
	int n = recv(dst_socket, (char*)(&pos), sizeof(pos), 0);
	if (n != SOCKET_ERROR) {
		printf("receved data\n");
	}*/
	//int s = sendto(dst_socket, (char*)(&pos), sizeof(pos), 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
	/*if (HOLD(CInput::eRight)) {
		i = 0;
		int s = sendto(dst_socket, (char*)(&i), sizeof(i), 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
	}
	if (HOLD(CInput::eLeft)) {
		i = 1;
		int s = sendto(dst_socket, (char*)(&i), sizeof(i), 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
	}*/

	//std::cout << "何か文字をを入力してください" << std::endl;
	//std::cin >> send_buf1;

	//std::cout << send_buf1 << std::endl;

	// Packetの送信(SOCKET, Buffer, Datasize, 送信方法)
	//send(dst_socket, send_buf1, 256, 0);
	//send(dst_socket, "a", 256, 0);
	//sendto(dst_socket, "HELLO", 5, 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
	//send(dst_socket, (char*)(&pos), sizeof(pos), 0);

	static int a = 0;
	sockaddr_in fromaddr;
	int addrlen;
	int n = recv(dst_socket, (char*)(pos), sizeof(*pos), 0);
	CVector2DAndID mempos;
	mempos.member_id = GameManager::id;
	
	if (n != SOCKET_ERROR) {
		printf("receved data\n");
		
	}
	if (HOLD(CInput::eRight)) {
		pos->x += 4;
	}
	if (HOLD(CInput::eLeft)) {
		pos->x -= 4;
	}
	

	int s = sendto(dst_socket, (char*)(pos), sizeof(*pos), 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
	printf("send %d\n", s);
}

void Soket::Finalize()
{
	// 解放処理
	closesocket(dst_socket);

	// WinSockの終了処理
	WSACleanup();
}

CVector2D Soket::RecvRenderUpdateData()
{
	
	int n;

	//n = recv(sock, buf, sizeof(buf), 0);
	n = recv(dst_socket, (char*)(&pos), sizeof(pos), 0);
	//printf("%d\n", n);
	if (n < 1) {
		if (WSAGetLastError() == WSAEWOULDBLOCK) {
			// まだ来ない。
			printf("MADA KONAI\n");
		}
		else {
			printf("error : 0x%x\n", WSAGetLastError());

		}
	}
	else {
		printf("received data\n");
		//printf("%s\n", buf);

	}

	
	//memcpy(&fds, &readfds, sizeof(fd_set));
	//
	//int select_ret = select(0, &fds, NULL, NULL, &t_val);
	//printf("%d", select_ret);
	//if (select_ret != 0) {
	//	// ソケットにデータがある
	//	if (FD_ISSET(dst_socket, &fds)) {
	//		// 受信データ処理
	//		//memset(buf, 0, BUFFER);
	//		recv(dst_socket, (char*)(&receve_pos), sizeof(receve_pos), 0);
	//		//recv(dst_socket, buf, BUFFER, 0);
	//		//buf[BUFFER - 1] = '\0';
	//		//printf("%s\n", buf);
	//	}
	//}
	
	return receve_pos;
}
