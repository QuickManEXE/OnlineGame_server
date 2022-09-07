#include "CNetWorkObjectBase.h"
#include<iostream>

#include"CPlayer2.h"
#include"CBall.h"

#pragma comment(lib, "Ws2_32.lib")


void CNetWorkDataManager::InitServer()
{
	/* �����n��̕ύX */
	srand((unsigned)time(NULL));
	member_id = rand();

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

	
}

void CNetWorkDataManager::InitClient()
{
	/* �����n��̕ύX */
	srand((unsigned)time(NULL));
	member_id = rand();

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
	
	// ������ (1) Type(ipv4 or v6) (2) IP�A�h���X�̃e�L�X�g�`�� (3) IP�A�h���X�̃o�C�i���`���y(2)��(3)�ɕϊ��z
	inet_pton(dst_addr.sin_family, server_ip_addr, &dst_addr.sin_addr.s_addr);

	// AF_INET��ipv4��IP�v���g�R�� & SOCK_STREAM��TCP�v���g�R��
	dst_socket = socket(AF_INET, SOCK_DGRAM, 0);

	// �����ŁA�m���u���b�L���O�ɐݒ肵�Ă��܂��B
	// val = 0�Ńu���b�L���O���[�h�ɐݒ�ł��܂��B
	// �\�P�b�g�̏����ݒ�̓u���b�L���O���[�h�ł��B
	u_long val = 1;
	ioctlsocket(dst_socket, FIONBIO, &val);

	std::cout << "�ڑ�����(�T�[�oIP�A�h���X" << server_ip_addr << "/�ڑ���|�[�g�ԍ�" << port_number << std::endl << std::endl;

	printf("���Ȃ��̃����o�[ID��[%d]�ł�\n", member_id);
}

void CNetWorkDataManager::Finalize()
{
	// �������
	closesocket(dst_socket);

	// WinSock�̏I������
	WSACleanup();
}

void  CNetWorkDataManager::UpdateObjectsData(ObjectDataForSocket od)
{
	int id = od.unique_id;
	auto itr = m_network_objects_data.find(id);
	if (itr != m_network_objects_data.end()) {

		auto data = m_network_objects_data[id];
		data.object_data = od;
		(*data.object_pointer->GetObjectData()) = od;
	}
	else {
		//�V�����G���g���[����
		printf("�I�u�W�F�N�gID[%d]���G���g���[���܂���\n", id);
		NetWorkObjectData* member_data = &m_network_objects_data[id];
		switch (od.object_id)
		{
		case 0:
			member_data->object_pointer = new CPlayer2(CVector2D(0, 660), &member_data->object_data);
			member_data->object_data = od;
			break;
		case 1:
			member_data->object_pointer = new CBall(eId_Bullet,CVector2D(0, 660), &member_data->object_data);
			member_data->object_data = od;
			break;
		case 2:
			break;
		default:
			break;
		}
		
	}
}

void CNetWorkDataManager::ReceiveMembersData()
{
	while (1) {
		//��M�f�[�^�ő�T�C�Y
		const int size_max = 1024;
		//�̈�m��
		char* buf = new char[size_max];
		//�ǂݍ��݃|�C���^�p
		char* b = buf;
		//��M
		int n = recv(dst_socket, buf, size_max, 0); printf("�󂯎����%d\n", n);
		if (n == SOCKET_ERROR)break;
		//�ŏ��̃f�[�^�F�l��
		int player_cnt = *((int*)b);
		b += sizeof(int);
		//�l�����ǂݍ���
		for (int i = 0; i < player_cnt; i++, b += sizeof(ObjectDataForSocket)) {
			ObjectDataForSocket* data = (ObjectDataForSocket*)b;
			UpdateObjectsData(*data);
		}
		delete buf;
	}
}

void CNetWorkDataManager::UpdateAllByOwner()
{

	std::map<int,NetWorkObjectData> objects_data;

	for (auto itr = m_network_objects_data.begin(); itr != m_network_objects_data.end(); itr++) {

		auto obj = (*itr).second.object_pointer;
		if (obj->GetObjectData()->owner_id == member_id) {
			
			obj->UpdateByOwner();
			
			NetWorkObjectData tmp_data;
			tmp_data.object_data = (*obj->GetObjectData());
			tmp_data.object_pointer = obj;

			objects_data[obj->GetObjectData()->unique_id] = tmp_data;

		}

	}

	if (objects_data.size() > 0) {
		SendToObjectsData(objects_data);
	}
	
}

void CNetWorkDataManager::AddObjectData(int object_id,CVector3D pos)
{
	int id = rand();

	NetWorkObjectData* member_data = &m_network_objects_data[id];
	member_data->object_data.pos = pos;
	member_data->object_data.unique_id = id;
	member_data->object_data.owner_id = member_id;
	member_data->object_data.object_id = object_id;

	switch (object_id) {
	case 0:
		member_data->object_pointer = new CPlayer2(CVector2D(0, 660), &member_data->object_data);
		break;
	case 1:
		member_data->object_pointer = new CBall(eId_Bullet,CVector2D(0, 660), &member_data->object_data);
		break;
	}
	
}

void CNetWorkDataManager::UpdateReciveAndSend()
{

	sockaddr_in fromaddr;
	int addrlen = sizeof(fromaddr);

	while (1) {


		{//��M

			//��M�f�[�^�ő�T�C�Y
			const int size_max = 1024;
			//�̈�m��
			char* buf = new char[size_max];
			//�ǂݍ��݃|�C���^�p
			char* b = buf;
			//��M
			int n = recvfrom(sock, buf, size_max, 0, (struct sockaddr*)&fromaddr, &addrlen); printf("�󂯎����%d\n", n);
			if (n == SOCKET_ERROR)break;
			//�ŏ��̃f�[�^�F�l��
			int player_cnt = *((int*)b);
			b += sizeof(int);
			//�l�����ǂݍ���
			for (int i = 0; i < player_cnt; i++, b += sizeof(ObjectDataForSocket)) {
				ObjectDataForSocket* data = (ObjectDataForSocket*)b;
				UpdateObjectsData(*data);
			}
			delete buf;
		}


		{//���M

			std::map<int, NetWorkObjectData> members_data = GetObjectsData();
			//���M�f�[�^�T�C�Y int + MemberData * �l��
			UINT bufsize = sizeof(int) + sizeof(ObjectDataForSocket) * members_data.size();
			char* buf = new char[bufsize];
			//�l���L�^
			int* num = (int*)buf;
			*num = members_data.size();
			//�v���C���[�̊e�f�[�^���L�^
			ObjectDataForSocket* pd = (ObjectDataForSocket*)(buf + 4);
			for (auto v : members_data) {
				*pd = (*v.second.object_pointer->GetObjectData());
				pd++;
			}
			//int s = sendto(sock, (char*)(&members_data), sizeof(members_data), 0, (struct sockaddr*)&fromaddr, sizeof(fromaddr));
			int s = sendto(sock, buf, bufsize, 0, (struct sockaddr*)&fromaddr, sizeof(fromaddr));
			printf("%d\n", s);
		}
	}
	
}

void CNetWorkDataManager::SendToObjectsData(std::map<int, NetWorkObjectData> od)
{

	std::map<int, NetWorkObjectData> members_data = od;
	//���M�f�[�^�T�C�Y int + MemberData * �l��
	UINT bufsize = sizeof(int) + sizeof(ObjectDataForSocket) * members_data.size();
	char* buf = new char[bufsize];
	//�l���L�^
	int* num = (int*)buf;
	*num = members_data.size();
	//�v���C���[�̊e�f�[�^���L�^
	ObjectDataForSocket* pd = (ObjectDataForSocket*)(buf + 4);
	for (auto v : members_data) {
		*pd = (*v.second.object_pointer->GetObjectData());
		pd++;
	}
	
	int s = sendto(dst_socket, buf, bufsize, 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
	printf("send %d\n", s);
}



CNetWorkObjectBase::CNetWorkObjectBase(int id, int updatePrio, int renderPrio, CNetWorkDataManager::ObjectDataForSocket* od) 
	: Task(id,updatePrio,renderPrio),m_object_data(od)
{

}

CNetWorkObjectBase::~CNetWorkObjectBase()
{
}

void CNetWorkObjectBase::UpdateByOwner()
{
}