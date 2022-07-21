#include "Soket.h"
#include"GameManager.h"
#include<iostream>


#pragma comment(lib, "Ws2_32.lib")

Soket::Soket()
{
}

void Soket::Init(int _member_id)
{

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

	///* 接続処理
	//if (connect(dst_socket, (struct sockaddr*)&dst_addr, sizeof(dst_addr))) {
	//	std::cerr << "接続失敗(サーバIPアドレス" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl;
	//	exit(0);
	//}*/

	std::cout << "接続完了(サーバIPアドレス" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl << std::endl;
	
	printf("あなたのIDは[%d]です\n", _member_id);
}

void Soket::Run(int _member_id)
{

	PlayerData playerData;
	playerData.member_id = _member_id;
	
	if (HOLD(CInput::eRight)) {
		playerData.key[CInput::eRight] = 1;
		
	}
	if (HOLD(CInput::eLeft)) {
		playerData.key[CInput::eLeft] = 1;
		
	}	

	int s = sendto(dst_socket, (char*)(&playerData), sizeof(playerData), 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
	printf("send %d\n", s);
}

void Soket::Finalize()
{
	// 解放処理
	closesocket(dst_socket);

	// WinSockの終了処理
	WSACleanup();
}

