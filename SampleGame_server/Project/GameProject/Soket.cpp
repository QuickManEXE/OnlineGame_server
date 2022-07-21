#include "Soket.h"
#include"PlayerDataManager.h"

void Soket::Init()
{
	
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
	
	memset(buf, 0, sizeof(buf));
}

void Soket::Run()
{

	PlayerDataManager::PlayerData playerData;

	//int addrlen;
	sockaddr_in fromaddr;
	int addrlen = sizeof(fromaddr);
	int n = recvfrom(sock, (char*)(&playerData), sizeof(playerData), 0, (struct sockaddr*)&fromaddr, &addrlen);
	if (n != SOCKET_ERROR) {
		PlayerDataManager::Instance().UpdateMembersData(playerData);
		std::map<int, PlayerDataManager::MemberData> members_data =  PlayerDataManager::Instance().GetMembersData();
		int s = sendto(sock, (char*)(&members_data), sizeof(members_data), 0, (struct sockaddr*)&fromaddr, sizeof(fromaddr));
	}

}

void Soket::finalize()
{
	closesocket(sock);

	WSACleanup();
}
