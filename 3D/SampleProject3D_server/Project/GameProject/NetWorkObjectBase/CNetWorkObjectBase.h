#pragma once
#include "../stdafx.h"
#include "../System/Task.h"
#include"../Soket.h"

class CNetWorkObjectBase;


class CNetWorkDataManager : public Singleton<CNetWorkDataManager> {
public:
	struct ObjectDataForSocket {
		int unique_id;//���̃I�u�W�F�N�g�̃��j�[�N��ID
		int owner_id;//���̃I�u�W�F�N�g���Ǘ����郆�[�U�[�̃��j�[�N��ID
		int object_id;//���ꂪ���̃I�u�W�F�N�g�����ʂ���ID
		CVector3D pos;//���W
		CVector3D vec;//�ړ���
		int key[CInput::eKeyMax]{ 0 };
	};
	struct NetWorkObjectData {
		CNetWorkObjectBase* object_pointer;
		ObjectDataForSocket object_data;
	};
public:
	std::map<int, NetWorkObjectData> m_network_objects_data;
public:
	char server_ip_addr[32];
	int port_number;

	// Windows Sockets�d�l�Ɋւ�������i�[����\����
	WSADATA wsa_data;

	struct sockaddr_in dst_addr;
	int addlen;
	int dst_socket;

	char send_buf1[256], send_buf2[256];
	char recv_buf[256];

	CVector2D pos;

	struct timeval t_val = { 0, 1000 };

	fd_set fds, readfds;

	int member_id;

public:
	void InitClient();
	void Finalize();
	void ReceiveMembersData();
	void UpdateObjectsData(ObjectDataForSocket od);
	void SendToObjectsData(std::map<int, NetWorkObjectData> od);
	void UpdateAllByOwner();
	void AddObjectData(int object_id, CVector3D pos);
};


class CNetWorkObjectBase : public Task{
private:

	CNetWorkDataManager::ObjectDataForSocket* m_object_data;//�l�b�g���[�N�ʐM�ɕK�v�ȃf�[�^

public:
	CNetWorkObjectBase(int id, int updatePrio, int renderPrio, CNetWorkDataManager::ObjectDataForSocket* od);
	~CNetWorkObjectBase();

	virtual void UpdateByOwner();

	CNetWorkDataManager::ObjectDataForSocket* GetObjectData() const{
		return m_object_data;
	};
	void SetObjectData(CNetWorkDataManager::ObjectDataForSocket* od) {
		m_object_data = od;
	}
};

