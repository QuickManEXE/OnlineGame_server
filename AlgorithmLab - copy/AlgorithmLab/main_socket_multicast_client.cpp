#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int
main()
{
	WSAData wsaData;

	SOCKET sock;
	struct sockaddr_in addr;
	struct ip_mreq mreq;

	char buf[2048];

	WSAStartup(MAKEWORD(2, 0), &wsaData);

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(sock, (struct sockaddr*)&addr, sizeof(addr));

	// setsockoptは、bind以降で行う必要あり
	memset(&mreq, 0, sizeof(mreq));
	mreq.imr_interface.S_un.S_addr = INADDR_ANY;
	//mreq.imr_multiaddr.S_un.S_addr = inet_addr("239.192.1.2");
	const char* server_ip_addr = "239.192.1.2";
	inet_pton(addr.sin_family, server_ip_addr, &mreq.imr_multiaddr.S_un.S_addr);


	if (setsockopt(sock,
		IPPROTO_IP,
		IP_ADD_MEMBERSHIP,
		(char*)&mreq, sizeof(mreq)) != 0) {
		printf("setsockopt : %d\n", WSAGetLastError());
		return 1;
	}

	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);

	printf("%s\n", buf);

	closesocket(sock);

	WSACleanup();

	return 0;
}