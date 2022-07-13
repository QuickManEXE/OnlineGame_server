#include "Soket.h"

void Soket::Init()
{
	
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(sock, (struct sockaddr*)&addr, sizeof(addr));

	// �����ŁA�m���u���b�L���O�ɐݒ肵�Ă��܂��B
	// val = 0�Ńu���b�L���O���[�h�ɐݒ�ł��܂��B
	// �\�P�b�g�̏����ݒ�̓u���b�L���O���[�h�ł��B
	u_long val = 1;
	ioctlsocket(sock, FIONBIO, &val);
	
	memset(buf, 0, sizeof(buf));
}

void Soket::Run()
{
	int n;

	//n = recv(sock, buf, sizeof(buf), 0);
	n = recv(sock, (char*)(&pos), sizeof(pos), 0);
	//printf("%d\n", n);
	if (n < 1) {
		if (WSAGetLastError() == WSAEWOULDBLOCK) {
			// �܂����Ȃ��B
			//printf("MADA KONAI\n");
		}
		else {
			printf("error : 0x%x\n", WSAGetLastError());

		}
	}
	else {
		printf("received data\n");
		//printf("%s\n", buf);

	}


}

void Soket::finalize()
{
	closesocket(sock);

	WSACleanup();
}
