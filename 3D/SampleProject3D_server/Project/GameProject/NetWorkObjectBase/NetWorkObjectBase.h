#pragma once
#include "../Base/Base.h"
#include"../Singleton/Singleton.h"


class NetWorkObjectBase;


class NetWorkObjectManager : public Singleton<NetWorkObjectManager> {
public:
	struct ObjectDataForSocket {
		int unique_id;//���̃I�u�W�F�N�g�̃��j�[�N��ID
		int owner_id;//���̃I�u�W�F�N�g���Ǘ����郆�[�U�[�̃��j�[�N��ID
		int object_id;//���ꂪ���̃I�u�W�F�N�g�����ʂ���ID
		CVector3D pos;//���W
		CVector3D rot;//��]�l
		CVector3D vec;//�ړ���
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
	E_MODE m_mode;//�T�[�o�[���N���C�A���g��
	E_MODE GetMode() {
		return m_mode;
	}
	void SetMode(E_MODE _mode){
		m_mode = _mode;
	}
	int m_unique_id; //���̒ʐM�v���O�����̃��j�[�NID
	int GetUniqueID() {
		return m_unique_id;
	}
	void SetUniqueID(int _id) {
		m_unique_id = _id;
	}
public:
	//�T�[�o�[�p�ϐ�
	WSADATA wsaData;

	SOCKET sock;
	struct sockaddr_in addr;

	sockaddr_in fromaddr;
	int addrlen = sizeof(fromaddr);
public:
	//�N���C�A���g�p�ϐ�
	char server_ip_addr[32];
	int port_number;

	// Windows Sockets�d�l�Ɋւ�������i�[����\����
	WSADATA wsa_data;

	struct sockaddr_in dst_addr;
	int addlen;
	int dst_socket;

	struct timeval t_val = { 0, 1000 };
public:
	void Init(E_MODE _mode);
	void Update(E_MODE _mode);
public:
	//�T�[�o�[�p�֐�
	void InitServer();//�T�[�o�[������
	void UpdateReciveAndSend();//�T�[�o�[��񑗎�M
public:
	//�N���C�A���g�p�֐�
	void InitClient();//�N���C�A���g������
	void Finalize();//�\�P�b�g�ʐM�I������
	void ReceiveMembersData();//�N���C�A���g���󂯎��X�V
	void UpdateObjectsData(ObjectDataForSocket od);//���̍X�V�A���̏��Ȃ�ǉ�
	void SendToObjectsData(std::map<int, NetWorkObjectData> od);//�����̃f�[�^�𑗂�
	void UpdateAllByOwner();//�����̏��L���Ă���I�u�W�F�N�g�̍X�V�������Ăяo��
	void AddObjectData(int object_id, CVector3D pos);//�l�b�g���[�N�I�u�W�F�N�g�̒ǉ�
	std::map<int, NetWorkObjectData> GetObjectsData() {
		return m_network_objects_data;
	};
};


class NetWorkObjectBase : public Base{
private:

	NetWorkObjectManager::ObjectDataForSocket* m_object_data;//�l�b�g���[�N�ʐM�ɕK�v�ȃf�[�^

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

