#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int
main()
{
	WSAData wsaData;

	SOCKET sock;
	struct sockaddr_in addr;
	DWORD ipaddr;

	WSAStartup(MAKEWORD(2, 0), &wsaData);

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	//addr.sin_addr.S_un.S_addr = inet_addr("239.192.1.2");
	const char* server_ip_addr = "239.192.1.2";
	inet_pton(addr.sin_family, server_ip_addr, &addr.sin_addr.S_un.S_addr);


	//ipaddr = inet_addr("127.0.0.1");
	inet_pton(addr.sin_family, "127.0.0.1", &ipaddr);
	if (setsockopt(sock,
		IPPROTO_IP,
		IP_MULTICAST_IF,
		(char*)&ipaddr, sizeof(ipaddr)) != 0) {
		printf("setsockopt : %d\n", WSAGetLastError());
		return 1;
	}

	sendto(sock, "HELLO", 5, 0, (struct sockaddr*)&addr, sizeof(addr));

	closesocket(sock);

	WSACleanup();

	return 0;
}