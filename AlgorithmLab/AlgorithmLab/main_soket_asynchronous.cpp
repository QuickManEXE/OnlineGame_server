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

	// �����ŁA�m���u���b�L���O�ɐݒ肵�Ă��܂��B
	// val = 0�Ńu���b�L���O���[�h�ɐݒ�ł��܂��B
	// �\�P�b�g�̏����ݒ�̓u���b�L���O���[�h�ł��B
	u_long val = 1;
	ioctlsocket(sock, FIONBIO, &val);

	int n;

	memset(buf, 0, sizeof(buf));
	while (1) {
		n = recv(sock, buf, sizeof(buf), 0);
		if (n < 1) {
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
				// �܂����Ȃ��B
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

		// �Ƃ肠������b�҂��Ă݂�
		Sleep(1000);
	}

	closesocket(sock);

	WSACleanup();

	return 0;
}
