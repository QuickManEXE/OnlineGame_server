#include "Soket.h"
#include"PlayerDataManager.h"

void Soket::Init()
{
	/* �����n��̕ύX */
	srand((unsigned)time(NULL));
	m_unique_member_id = rand();

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

	PlayerDataManager::PlayerData playerData;

	
	sockaddr_in fromaddr;
	int addrlen = sizeof(fromaddr);
	
	while (1) {
		int n = recvfrom(sock, (char*)(&playerData), sizeof(playerData), 0, (struct sockaddr*)&fromaddr, &addrlen);
		if (n != SOCKET_ERROR) {
			PlayerDataManager::Instance().UpdateMembersData(playerData);
			std::map<int, PlayerDataManager::MemberData> members_data = PlayerDataManager::Instance().GetMembersData();
			//���M�f�[�^�T�C�Y int + MemberData * �l��
			UINT bufsize = sizeof(int) + sizeof(PlayerDataManager::PlayerData) * members_data.size();
			char* buf = new char[bufsize];
			//�l���L�^
			int* num = (int*)buf;
			*num = members_data.size();
			//�v���C���[�̊e�f�[�^���L�^
			PlayerDataManager::PlayerData* pd = (PlayerDataManager::PlayerData*)(buf + 4);
			for (auto v : members_data) {
				*pd = v.second.pointer->m_playerData;
				pd++;
			}
			//int s = sendto(sock, (char*)(&members_data), sizeof(members_data), 0, (struct sockaddr*)&fromaddr, sizeof(fromaddr));
			int s = sendto(sock, buf, bufsize, 0, (struct sockaddr*)&fromaddr, sizeof(fromaddr));
			printf("%d\n", s);
		}
		else {
			break;
		}
	}

}

void Soket::finalize()
{
	closesocket(sock);

	WSACleanup();
}
