#include "Soket.h"
#include"GameManager.h"
#include<iostream>


#pragma comment(lib, "Ws2_32.lib")

Soket::Soket()
{
}

void Soket::Init(int _member_id)
{

	playerData.member_id = _member_id;

	playerData.pos = CVector2D(300, 600);

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
	//dst_addr.sin_addr.S_un.S_addr = inet_addr(server_ip_addr);

	// ������ (1) Type(ipv4 or v6) (2) IP�A�h���X�̃e�L�X�g�`�� (3) IP�A�h���X�̃o�C�i���`���y(2)��(3)�ɕϊ��z
	inet_pton(dst_addr.sin_family, server_ip_addr, &dst_addr.sin_addr.s_addr);
	
	
	// AF_INET��ipv4��IP�v���g�R�� & SOCK_STREAM��TCP�v���g�R��
	dst_socket = socket(AF_INET, SOCK_DGRAM, 0);
	
	// �����ŁA�m���u���b�L���O�ɐݒ肵�Ă��܂��B
	// val = 0�Ńu���b�L���O���[�h�ɐݒ�ł��܂��B
	// �\�P�b�g�̏����ݒ�̓u���b�L���O���[�h�ł��B
	u_long val = 1;
	ioctlsocket(dst_socket, FIONBIO, &val);

	///* �ڑ�����
	//if (connect(dst_socket, (struct sockaddr*)&dst_addr, sizeof(dst_addr))) {
	//	std::cerr << "�ڑ����s(�T�[�oIP�A�h���X" << server_ip_addr << "/�ڑ���|�[�g�ԍ�" << port_number << std::endl;
	//	exit(0);
	//}*/

	std::cout << "�ڑ�����(�T�[�oIP�A�h���X" << server_ip_addr << "/�ڑ���|�[�g�ԍ�" << port_number << std::endl << std::endl;
	
	printf("���Ȃ���ID��[%d]�ł�\n", _member_id);
}

void Soket::Run(PlayerDataManager::PlayerData* pd)
{

	PlayerDataManager::PlayerData* playerData = pd;

	for (int i = 0; i < CInput::eKeyMax; i++) {
		playerData->key[i] = 0;
	}
	
	if (HOLD(CInput::eUp)) {
		playerData->key[CInput::eUp] = 1;
		playerData->pos.y -= 4;
	}
	if (HOLD(CInput::eDown)) {
		playerData->key[CInput::eDown] = 1;
		playerData->pos.y += 4;
	}	

	int s = sendto(dst_socket, (char*)(playerData), sizeof(*playerData), 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
	printf("send %d\n", s);
}

void Soket::Finalize()
{
	// �������
	closesocket(dst_socket);

	// WinSock�̏I������
	WSACleanup();
}

void Soket::ReceiveMembersData()
{
	//int addrlen = sizeof(dst_addr);
	//���M�f�[�^�T�C�Y int + MemberData * �l��
	//UINT bufsize = sizeof(int) + sizeof(PlayerDataManager::MemberData) * 2;


	//int n = 0;
	while (1) {
		//��M�f�[�^�ő�T�C�Y
		const int size_max = 1024;
		//�̈�m��
		char* buf = new char[size_max];
		//�ǂݍ��݃|�C���^�p
		char* b = buf;
		//��M
		int n = recv(dst_socket, buf, size_max, 0);printf("�󂯎����%d\n",n);
		if (n == SOCKET_ERROR)break;
		//�ŏ��̃f�[�^�F�l��
		int player_cnt = *((int*)b);
		b += sizeof(int);
		//�l�����ǂݍ���
		for (int i = 0; i < player_cnt; i++, b += sizeof(PlayerDataManager::PlayerData)) {
			PlayerDataManager::PlayerData* data = (PlayerDataManager::PlayerData*)b;
			PlayerDataManager::Instance().UpdateMembersData(*data);
			

		}

		delete buf;
		
	}
	
}

