#include "Soket.h"
#include<iostream>

#pragma comment(lib, "Ws2_32.lib")

Soket::Soket()
{
}

void Soket::Init()
{
	// WinSock�̏���������(Version 2.0)
	if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
		std::cerr << "Winsock�̏��������s(WSAStartup)" << std::endl;
	}

	// ���[�U����
	std::cout << "�ڑ���IP�A�h���X����͂��Ă�������(xxx.xxx.xxx.xxx)" << std::endl;
	std::cin >> server_ip_addr;
	std::cout << "�|�[�g�ԍ�����͂��Ă�������" << std::endl;
	std::cin >> port_number;

	// sockaddr_in�\���̂̍쐬�ƃ|�[�g�ԍ��AIP�^�C�v�̓���
	memset(&dst_addr, 0, sizeof(dst_addr));
	dst_addr.sin_port = htons(port_number);		// �|�[�g�ԍ�
	dst_addr.sin_family = AF_INET;				// AF_INET��ipv4������
	dst_addr.sin_addr.S_un.S_addr = inet_addr(server_ip_addr);

	
	// AF_INET��ipv4��IP�v���g�R�� & SOCK_STREAM��TCP�v���g�R��
	int dst_socket = socket(AF_INET, SOCK_DGRAM, 0);

	// �ڑ�����
	if (connect(dst_socket, (struct sockaddr*)&dst_addr, sizeof(dst_addr))) {
		std::cerr << "�ڑ����s(�T�[�oIP�A�h���X" << server_ip_addr << "/�ڑ���|�[�g�ԍ�" << port_number << std::endl;
		exit(0);
	}

	std::cout << "�ڑ�����(�T�[�oIP�A�h���X" << server_ip_addr << "/�ڑ���|�[�g�ԍ�" << port_number << std::endl << std::endl;
	
}

void Soket::Run()
{

	std::cout << "��������������͂��Ă�������" << std::endl;
	//std::cin >> send_buf1;

	//std::cout << send_buf1 << std::endl;

	// Packet�̑��M(SOCKET, Buffer, Datasize, ���M���@)
	//send(dst_socket, send_buf1, 256, 0);
	send(dst_socket, "a", 256, 0);
	//sendto(dst_socket, "HELLO", 5, 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));



}

void Soket::Finalize()
{
	// �������
	closesocket(dst_socket);

	// WinSock�̏I������
	WSACleanup();
}
