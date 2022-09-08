#include "NetWorkObjectBase.h"
#include"../Game/Player.h"

#pragma comment(lib, "Ws2_32.lib")

//サーバーかクライアントごとに初期化の内容を変える
void NetWorkObjectManager::Init(E_MODE _mode)
{
	switch (m_mode)
	{
	case NetWorkObjectManager::E_MODE::ESERVER:
		InitServer();
		break;
	case NetWorkObjectManager::E_MODE::ECLIENT:
		InitClient();
		break;
	default:
		break;
	}
}

//サーバーかクライアントごとにアップデートの内容を変える
void NetWorkObjectManager::Update(E_MODE _mode)
{
	switch (m_mode)
	{
	case NetWorkObjectManager::E_MODE::ESERVER:
		UpdateReciveAndSend();
		break;
	case NetWorkObjectManager::E_MODE::ECLIENT:
		UpdateAllByOwner();
		ReceiveMembersData();
		break;
	default:
		break;
	}
}

//サーバーの初期化
void NetWorkObjectManager::InitServer()
{
	/* 乱数系列の変更 */
	srand((unsigned)time(NULL));
	m_unique_id = rand();

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
}

//サーバーが行うデータの受信と返信
void NetWorkObjectManager::UpdateReciveAndSend()
{
	sockaddr_in fromaddr;
	int addrlen = sizeof(fromaddr);

	while (1) {


		{//受信

			//受信データ最大サイズ
			const int size_max = 1024;
			//領域確保
			char* buf = new char[size_max];
			//読み込みポインタ用
			char* b = buf;
			//受信
			int n = recvfrom(sock, buf, size_max, 0, (struct sockaddr*)&fromaddr, &addrlen); printf("受け取った%d\n", n);
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


		{//送信

			std::map<int, NetWorkObjectData> members_data = GetObjectsData();
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
			//int s = sendto(sock, (char*)(&members_data), sizeof(members_data), 0, (struct sockaddr*)&fromaddr, sizeof(fromaddr));
			int s = sendto(sock, buf, bufsize, 0, (struct sockaddr*)&fromaddr, sizeof(fromaddr));
			printf("%d\n", s);
		}
	}
}

//クライアント側の初期化
void NetWorkObjectManager::InitClient()
{
	/* 乱数系列の変更 */
	srand((unsigned)time(NULL));
	m_unique_id = rand();

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

	printf("あなたのメンバーIDは[%d]です\n", m_unique_id);
}

//終了処理
void NetWorkObjectManager::Finalize()
{
	// 解放処理
	closesocket(dst_socket);

	// WinSockの終了処理
	WSACleanup();
}

//オブジェクトのデータの更新
void  NetWorkObjectManager::UpdateObjectsData(ObjectDataForSocket od)
{
	int id = od.unique_id;
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
		Player* p;
		switch (od.object_id)
		{
		case eId_Player:
			p = new Player(CVector3D(0, 0, -10), &member_data->object_data);
			Base::Add(p);
			member_data->object_pointer = p;
			member_data->object_data = od;
			break;
		case eId_Enemy:
			//member_data->object_pointer = new CBall(eId_Bullet,CVector2D(0, 660), &member_data->object_data);
			//member_data->object_data = od;
			break;
		case eId_Effect:
			break;
		default:
			break;
		}
		
	}
}

//保存したデータの送信
void NetWorkObjectManager::ReceiveMembersData()
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
			if (data->owner_id != m_unique_id) {
				UpdateObjectsData(*data);
			}
		}
		delete buf;
	}
}

//オブジェクトを所持しているオーナーによる更新処理（全体）
void NetWorkObjectManager::UpdateAllByOwner()
{

	std::map<int,NetWorkObjectData> objects_data;

	for (auto itr = m_network_objects_data.begin(); itr != m_network_objects_data.end(); itr++) {

		auto obj = (*itr).second.object_pointer;
		if (obj->GetObjectData()->owner_id == m_unique_id) {
			
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

//オブジェクトデータを追加する処理
void NetWorkObjectManager::AddObjectData(int object_id,CVector3D pos)
{
	int id = rand();

	NetWorkObjectData* member_data = &m_network_objects_data[id];
	member_data->object_data.pos = pos;
	member_data->object_data.unique_id = id;
	member_data->object_data.owner_id = m_unique_id;
	member_data->object_data.object_id = object_id;
	
	Player* p;
	switch (object_id) {
	case eId_Player:
		p = new Player(pos, &member_data->object_data);
		Base::Add(p);
		member_data->object_pointer = p;
		break;
	case eId_Enemy:
		//member_data->object_pointer = new CBall(eId_Bullet,CVector2D(pos.x, pos.y), &member_data->object_data);
		break;
	}
	
}

//オブジェクトデータを送る処理
void NetWorkObjectManager::SendToObjectsData(std::map<int, NetWorkObjectData> od)
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



NetWorkObjectBase::NetWorkObjectBase(int id,NetWorkObjectManager::ObjectDataForSocket* od) 
	: Base(id),m_object_data(od)
{

}

NetWorkObjectBase::~NetWorkObjectBase()
{
}

void NetWorkObjectBase::UpdateByOwner()
{
}
