// サーバ側 WinSock2

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

int main() {

	// ポート番号
	int port_number = 12345;

	// Windows Sockets仕様に関する情報を格納する構造体
	WSADATA wsa_data;

	// WinSockの初期化処理(Version 2.0)
	if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
		std::cerr << "Winsockの初期化失敗(WSAStartup)" << std::endl;
	}

	// サーバ側ソケット作成
	int src_socket;

	// sockaddr_in構造体の作成とポート番号、IPタイプの入力
	struct sockaddr_in src_addr;
	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.sin_port = htons(port_number);
	src_addr.sin_family = AF_INET;
	src_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// AF_INETはipv4のIPプロトコル & SOCK_STREAMはTCPプロトコル
	src_socket = socket(AF_INET, SOCK_STREAM, 0);

	// サーバ側のソケットを特定のIPアドレスとポートに紐付ける
	bind(src_socket, (struct sockaddr*)&src_addr, sizeof(src_addr));

	// クライアント側のソケット設定1
	int dst_socket;
	struct sockaddr_in dst_addr;
	int dst_addr_size = sizeof(dst_addr);

	// 接続の待受を開始する
	listen(src_socket, 1);

	// 送受信に使用するバッファ
	char recv_buf1[256], recv_buf2[256];
	char send_buf[256];


	// クライアント側のソケット設定2
	int dst_socket2;
	struct sockaddr_in dst_addr2;
	int dst_addr_size2 = sizeof(dst_addr2);

	// 接続の待受を開始する
	//listen(src_socket, 1);

	// 送受信に使用するバッファ
	char recv_buf1_2[256], recv_buf2_2[256];
	char send_buf2[256];

	// クライアントからの接続待ちループ関数
	while (1) {

		std::cout << "クライアントからの接続待ち1" << std::endl;

		// クライアントからの接続を受信する
		dst_socket = accept(src_socket, (struct sockaddr*)&dst_addr, &dst_addr_size);
		
		std::cout << "クライアントからの接続有り1" << std::endl;

		snprintf(send_buf, 256, "1");
		// 結果を格納したパケットの送信
		send(dst_socket, send_buf, sizeof(char) * 256, 0);
		
		std::cout << "クライアントからの接続待ち2" << std::endl;

		dst_socket2 = accept(src_socket, (struct sockaddr*)&dst_addr, &dst_addr_size);

		std::cout << "クライアントからの接続有り2" << std::endl;

		snprintf(send_buf, 256, "2");
		// 結果を格納したパケットの送信
		send(dst_socket2, send_buf, sizeof(char) * 256, 0);

		//クライアントの集結確認
		snprintf(send_buf, 256, "対戦相手がそろいました");
		// 結果を格納したパケットの送信
		send(dst_socket, send_buf, sizeof(char) * 256, 0);
		// 結果を格納したパケットの送信
		send(dst_socket2, send_buf, sizeof(char) * 256, 0);


		// 接続後の処理
		while (1) {

			int status;

			//クライアント１からの受信
			//パケットの受信(recvは成功すると受信したデータのバイト数を返却。切断で0、失敗で-1が返却される
			int recv1_result = recv(dst_socket, recv_buf1, sizeof(char) * 256, 0);
			if (recv1_result == 0 || recv1_result == -1) {
				status = closesocket(dst_socket); break;
			}
			std::cout << "受信した数字1個目 : " << recv_buf1 << std::endl;

			/*int recv2_result = recv(dst_socket, recv_buf2, sizeof(char) * 256, 0);
			if (recv2_result == 0 || recv2_result == -1) {
				status = closesocket(dst_socket); break;
			}
			std::cout << "受信した数字2個目 : " << recv_buf2 << std::endl;*/

			//クライアント２からの受信
			int recv2_result = recv(dst_socket2, recv_buf2, sizeof(char) * 256, 0);
			if (recv2_result == 0 || recv2_result == -1) {
				status = closesocket(dst_socket2); break;
			}
			std::cout << "受信した数字2個目 : " << recv_buf2 << std::endl;

			
			// 受信した数字を加算

			int num1 = atoi(recv_buf1);
			int num2 = atoi(recv_buf2);

			if (num1 == num2) {
				snprintf(send_buf, 256, "引き分け");
			}
			else if(num1%3 < num2 % 3){
				snprintf(send_buf, 256, "クライアント１の勝ち");
			}
			else {
				snprintf(send_buf, 256, "クライアント２の勝ち");
			}
			
			// 結果を格納したパケットの送信
			send(dst_socket, send_buf, sizeof(char) * 256, 0);
			// 結果を格納したパケットの送信
			send(dst_socket2, send_buf, sizeof(char) * 256, 0);
		}
	}

	// WinSockの終了処理
	WSACleanup();

	return 0;
}