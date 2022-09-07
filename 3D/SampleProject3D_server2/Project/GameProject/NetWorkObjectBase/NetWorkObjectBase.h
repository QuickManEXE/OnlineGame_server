#pragma once
#include "../Base/Base.h"
#include"../Singleton/Singleton.h"


class NetWorkObjectBase;


class NetWorkObjectManager : public Singleton<NetWorkObjectManager> {
public:
	struct ObjectDataForSocket {
		int unique_id;//このオブジェクトのユニークなID
		int owner_id;//このオブジェクトを管理するユーザーのユニークなID
		int object_id;//これが何のオブジェクトか判別するID
		CVector3D pos;//座標
		CVector3D rot;//回転値
		CVector3D vec;//移動量
		int key[CInput::eKeyMax]{ 0 };
	};
	struct NetWorkObjectData {
		NetWorkObjectBase* object_pointer;
		ObjectDataForSocket object_data;
	};
public:
	std::map<int, NetWorkObjectData> m_network_objects_data;
public:
	enum class E_MODE{
		ESERVER,
		ECLIENT,
	};
	E_MODE m_mode;//サーバーかクライアントか
	E_MODE GetMode() {
		return m_mode;
	}
	void SetMode(E_MODE _mode){
		m_mode = _mode;
	}
	int m_unique_id; //この通信プログラムのユニークID
	int GetUniqueID() {
		return m_unique_id;
	}
	void SetUniqueID(int _id) {
		m_unique_id = _id;
	}
public:
	//サーバー用変数
	WSADATA wsaData;

	SOCKET sock;
	struct sockaddr_in addr;

	sockaddr_in fromaddr;
	int addrlen = sizeof(fromaddr);
public:
	//クライアント用変数
	char server_ip_addr[32];
	int port_number;

	// Windows Sockets仕様に関する情報を格納する構造体
	WSADATA wsa_data;

	struct sockaddr_in dst_addr;
	int addlen;
	int dst_socket;

	struct timeval t_val = { 0, 1000 };
public:
	void Init(E_MODE _mode);
	void Update(E_MODE _mode);
public:
	//サーバー用関数
	void InitServer();//サーバー初期化
	void UpdateReciveAndSend();//サーバー情報送受信
public:
	//クライアント用関数
	void InitClient();//クライアント初期化
	void Finalize();//ソケット通信終了する
	void ReceiveMembersData();//クライアント情報受け取り更新
	void UpdateObjectsData(ObjectDataForSocket od);//情報の更新、初の情報なら追加
	void SendToObjectsData(std::map<int, NetWorkObjectData> od);//自分のデータを送る
	void UpdateAllByOwner();//自分の所有しているオブジェクトの更新処理を呼び出す
	void AddObjectData(int object_id, CVector3D pos);//ネットワークオブジェクトの追加
	std::map<int, NetWorkObjectData> GetObjectsData() {
		return m_network_objects_data;
	};
};


class NetWorkObjectBase : public Base{
private:

	NetWorkObjectManager::ObjectDataForSocket* m_object_data;//ネットワーク通信に必要なデータ

public:
	NetWorkObjectBase(int id,NetWorkObjectManager::ObjectDataForSocket* od);
	~NetWorkObjectBase();

	virtual void UpdateByOwner();

	NetWorkObjectManager::ObjectDataForSocket* GetObjectData() const{
		return m_object_data;
	};
	void SetObjectData(NetWorkObjectManager::ObjectDataForSocket* od) {
		m_object_data = od;
	}
};

