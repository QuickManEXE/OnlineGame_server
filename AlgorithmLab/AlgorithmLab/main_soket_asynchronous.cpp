#include <stdio.h>
#include <winsock2.h>

int
main()
{
	WSADATA wsaData;

	SOCKET sock;
	struct sockaddr_in addr;

	char buf[2048];

	WSAStartup(MAKEWORD(2, 0), &wsaData);

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(sock, (struct sockaddr*)&addr, sizeof(addr));

	// ここで、ノンブロッキングに設定しています。
	// val = 0でブロッキングモードに設定できます。
	// ソケットの初期設定はブロッキングモードです。
	u_long val = 1;
	ioctlsocket(sock, FIONBIO, &val);

	int n;

	memset(buf, 0, sizeof(buf));
	while (1) {
		n = recv(sock, buf, sizeof(buf), 0);
		if (n < 1) {
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
				// まだ来ない。
				printf("MADA KONAI\n");
			}
			else {
				printf("error : 0x%x\n", WSAGetLastError());
				break;
			}
		}
		else {
			printf("received data\n");
			printf("%s\n", buf);
			break;
		}

		// とりあえず一秒待ってみる
		Sleep(1000);
	}

	closesocket(sock);

	WSACleanup();

	return 0;
}
