#include "Soket.h"
#include<iostream>

#pragma comment(lib, "Ws2_32.lib")

Soket::Soket()
{
}

void Soket::Init()
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
	dst_addr.sin_addr.S_un.S_addr = inet_addr(server_ip_addr);

	
	// AF_INETはipv4のIPプロトコル & SOCK_STREAMはTCPプロトコル
	int dst_socket = socket(AF_INET, SOCK_DGRAM, 0);

	// 接続処理
	if (connect(dst_socket, (struct sockaddr*)&dst_addr, sizeof(dst_addr))) {
		std::cerr << "接続失敗(サーバIPアドレス" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl;
		exit(0);
	}

	std::cout << "接続完了(サーバIPアドレス" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl << std::endl;
	
}

void Soket::Run()
{

	std::cout << "何か文字をを入力してください" << std::endl;
	//std::cin >> send_buf1;

	//std::cout << send_buf1 << std::endl;

	// Packetの送信(SOCKET, Buffer, Datasize, 送信方法)
	//send(dst_socket, send_buf1, 256, 0);
	send(dst_socket, "a", 256, 0);
	//sendto(dst_socket, "HELLO", 5, 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));



}

void Soket::Finalize()
{
	// 解放処理
	closesocket(dst_socket);

	// WinSockの終了処理
	WSACleanup();
}
