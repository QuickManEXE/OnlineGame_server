#include "CNetWorkObjectBase.h"

#include<iostream>

#include"CPlayer.h"

#pragma comment(lib, "Ws2_32.lib")

void CNetWorkDataManager::Init()
{
	/* 乱数系列の変更 */
	srand((unsigned)time(NULL));
	member_id = rand();

	// WinSockの初期化処理(Version 2.0)
	if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
		std::cerr << "Winsockの初期化失敗(WSAStartup)" << std::endl;
	}

	// ユーザ入力
	std::cout << "接続先IPアドレスを入力してください(xxx.xxx.xxx.xxx)" << std::endl;
	std::cin >> server_ip_addr;
	std::cout << "ポート番号を入力してください" << std::endl;
	std::cin >> port_number;

	// sockaddr_in構造体の作成とポート番号、IPタイプの入力
	memset(&dst_addr, 0, sizeof(dst_addr));
	dst_addr.sin_port = htons(port_number);		// ポート番号
	dst_addr.sin_family = AF_INET;				// AF_INETはipv4を示す
	
	// 引数は (1) Type(ipv4 or v6) (2) IPアドレスのテキスト形式 (3) IPアドレスのバイナリ形式【(2)→(3)に変換】
	inet_pton(dst_addr.sin_family, server_ip_addr, &dst_addr.sin_addr.s_addr);

	// AF_INETはipv4のIPプロトコル & SOCK_STREAMはTCPプロトコル
	dst_socket = socket(AF_INET, SOCK_DGRAM, 0);

	// ここで、ノンブロッキングに設定しています。
	// val = 0でブロッキングモードに設定できます。
	// ソケットの初期設定はブロッキングモードです。
	u_long val = 1;
	ioctlsocket(dst_socket, FIONBIO, &val);

	std::cout << "接続完了(サーバIPアドレス" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl << std::endl;

	printf("あなたのメンバーIDは[%d]です\n", member_id);
}

void CNetWorkDataManager::Finalize()
{
	// 解放処理
	closesocket(dst_socket);

	// WinSockの終了処理
	WSACleanup();
}

void  CNetWorkDataManager::UpdateObjectsData(ObjectDataForSocket od)
{
	int id = od.member_id;
	auto itr = m_network_objects_data.find(id);
	if (itr != m_network_objects_data.end()) {

		auto data = m_network_objects_data[id];
		data.object_data = od;
		(*data.object_pointer->GetObjectData()) = od;
	}
	else {
		//新しくエントリーする
		printf("オブジェクトID[%d]がエントリーしました\n", id);
		NetWorkObjectData* member_data = &m_network_objects_data[id];
		switch (od.object_id)
		{
		case 0:
			//member_data->object_pointer = new CPlayer(id, CVector2D(0, 660), &member_data->playerData);
			//member_data->object_data = od;
			break;
		case 1:
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
		//受信データ最大サイズ
		const int size_max = 1024;
		//領域確保
		char* buf = new char[size_max];
		//読み込みポインタ用
		char* b = buf;
		//受信
		int n = recv(dst_socket, buf, size_max, 0); printf("受け取った%d\n", n);
		if (n == SOCKET_ERROR)break;
		//最初のデータ：人数
		int player_cnt = *((int*)b);
		b += sizeof(int);
		//人数分読み込み
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

			objects_data[obj->GetObjectData()->member_id] = tmp_data;

		}

	}

	if (objects_data.size() > 0) {
		SendToObjectsData(objects_data);
	}
	
}

void CNetWorkDataManager::AddObjectData(int object_id,CVector3D pos)
{
	/* 乱数系列の変更 */
	srand((unsigned)time(NULL));
	int id = rand();

	NetWorkObjectData* member_data = &m_network_objects_data[id];
	member_data->object_data.pos = pos;
	member_data->object_data.member_id = id;
	member_data->object_data.owner_id = member_id;
	member_data->object_data.object_id = object_id;

	switch (object_id) {
	case 0:
		//member_data->object_pointer = new CPlayer(id, CVector2D(0, 660), &member_data->object_data);
		break;
	}
	
}

void CNetWorkDataManager::SendToObjectsData(std::map<int, NetWorkObjectData> od)
{

	std::map<int, NetWorkObjectData> members_data = od;
	//送信データサイズ int + MemberData * 人数
	UINT bufsize = sizeof(int) + sizeof(ObjectDataForSocket) * members_data.size();
	char* buf = new char[bufsize];
	//人数記録
	int* num = (int*)buf;
	*num = members_data.size();
	//プレイヤーの各データを記録
	ObjectDataForSocket* pd = (ObjectDataForSocket*)(buf + 4);
	for (auto v : members_data) {
		*pd = (*v.second.object_pointer->GetObjectData());
		pd++;
	}
	
	int s = sendto(dst_socket, buf, bufsize, 0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
	printf("send %d\n", s);
}



CNetWorkObjectBase::CNetWorkObjectBase(int id, int updatePrio, int renderPrio, CNetWorkDataManager::ObjectDataForSocket* od) : Task(id,updatePrio,renderPrio),m_object_data(od)
{
}

CNetWorkObjectBase::CNetWorkObjectBase(int id, int updatePrio, int renderPrio)
	: Task(id, updatePrio, renderPrio) {};


CNetWorkObjectBase::~CNetWorkObjectBase()
{
}

void CNetWorkObjectBase::UpdateByOwner()
{
}
