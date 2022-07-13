// クライアント側 WinSock2

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include"Input\Input.h"

int main() {

	Input::InitializeInput();
	// キーバインドの設定
	Input::BindKey(EKeyBind::Up, 'W');
	Input::BindKey(EKeyBind::Down, 'S');
	Input::BindKey(EKeyBind::Left, 'A');
	Input::BindKey(EKeyBind::Right, 'D');

	char server_ip_addr[32];
	int port_number;

	// Windows Sockets仕様に関する情報を格納する構造体
	WSADATA wsa_data;
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
	struct sockaddr_in dst_addr;
	memset(&dst_addr, 0, sizeof(dst_addr));
	dst_addr.sin_port = htons(port_number);		// ポート番号
	dst_addr.sin_family = AF_INET;				// AF_INETはipv4を示す

	// 引数は (1) Type(ipv4 or v6) (2) IPアドレスのテキスト形式 (3) IPアドレスのバイナリ形式【(2)→(3)に変換】
	inet_pton(dst_addr.sin_family, server_ip_addr, &dst_addr.sin_addr.s_addr);

	// AF_INETはipv4のIPプロトコル & SOCK_STREAMはTCPプロトコル
	int dst_socket = socket(AF_INET, SOCK_STREAM, 0);

	// 接続処理
	if (connect(dst_socket, (struct sockaddr*)&dst_addr, sizeof(dst_addr))) {
		std::cerr << "接続失敗(サーバIPアドレス" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl;
		exit(0);
	}

	std::cout << "接続完了(サーバIPアドレス" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl << std::endl;;


	char send_buf1[256], send_buf2[256];
	char recv_buf[256];

	struct CVector3D {
		float x;
		float y;
		float z;
		CVector3D() { x = 0; y = 0; z = 0; }
		CVector3D(float _x, float _y, float _z) {
			x = _x; y = _y; z = _z;
		}
	};

	CVector3D recv_pos(500,600,700);

	std::cout << "受信した数字1個目 : " << recv_pos.x << recv_pos.y << recv_pos.z << std::endl;

	CVector3D send_pos;

	while (1) {

		Input::UpdateInput();
		
		// Packetの受信
		recv(dst_socket, (char*)(&send_pos), sizeof(send_pos), 0);

		//send(dst_socket, send_buf2, 256, 0);

		send_pos;

		if (Input::IsKeyReleases(EKeyBind::Up)) {
			send_pos.x += 100;
		}
		
		
		
		// Packetの送信(SOCKET, Buffer, Datasize, 送信方法)
		send(dst_socket, (char*)(&send_pos), sizeof(send_pos), 0);
		

		// 受信結果の表示
		std::cout << send_pos.x << send_pos.y << send_pos.z << std::endl << std::endl;
	}

	// 解放処理
	closesocket(dst_socket);

	// WinSockの終了処理
	WSACleanup();

	Input::FinalizeInput();
	return 0;
}