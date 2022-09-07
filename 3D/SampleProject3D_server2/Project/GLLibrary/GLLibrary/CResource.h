#pragma once
#pragma once
/**
* @file		AsSet.h
* @brief	���\�[�X�Ǘ��N���X
*
* @author	shinya nagakawa
*/


#include <map>
#include <vector>
#include <string>

class CResource {
	char m_name[128];
public:
	CResource():m_name(""){}
	/**
	* @fn
	* �R���X�g���N
	* @brief �R���X�g���N�^
	* @param name [in]�@���O
	*/
	CResource(char *name) { memcpy(m_name, name, sizeof(m_name)); }
	/**
	* @fn
	* �f�X�g���N�^
	* @brief �f�X�g���N�^
	*/
	virtual ~CResource() {};
	/**
	* @fn
	* ���O�̎擾
	* @brief ���O�̎擾
	* @return ���O
	*/
	std::string GetName() const {
		return m_name;
	}
	/**
	* @fn
	* ���\�[�X�T�C�Y�擾
	* @brief ���\�[�X�T�C�Y�擾
	*/
	virtual unsigned int GetDataSize() { return 0; };

	/**
	* @fn
	* ���\�[�X�J������
	* @brief ���\�[�X�J������
	*/
	virtual void Release() {};
	friend class CResourceManager;

};
class CResourceManager {
private:
	std::map<int,std::map<std::string, CResource*>> m_list;
	static CResourceManager*	m_instance;
public:
	static CResourceManager* GetInstance() {
		if (!m_instance) m_instance = new CResourceManager;
		return m_instance;
	}
	/**
	* @fn�@���\�[�X��S�Ĕj������
	* @brief ���\�[�X��S�Ĕj������
	*/
	static void ClearInstance() {
		if (!m_instance) return;
		delete m_instance;
		m_instance = nullptr;
	}
	CResourceManager();
	~CResourceManager();
	/**
	* @fn
	* ���\�[�X�̒ǉ�
	* @brief ���\�[�X�̒ǉ�
	* @param res [in]�@�ǉ����郊�\�[�X
	* @param group [in]�@�O���[�v
	*/
	void Add(CResource* res,int group=0);
	/**
	* @fn
	* ���\�[�X�̒ǉ�
	* @brief ���\�[�X�̒ǉ�
	* @param name [in]�@���\�[�X�̖��O
	* @param res [in]�@�ǉ����郊�\�[�X
	* @param group [in]�@�O���[�v
	*/
	void Add(std::string name, CResource* res,int group=0);
	/**
	* @fn
	* ���\�[�X�̎擾
	* @brief ���\�[�X�̂̎擾
	* @param name [in]�@���\�[�X�̖��O
	* @param group [in]�@�O���[�v
	* @return ���\�[�X
	*/
	CResource* Get(std::string name, int group = 0);


	/**
	* @fn
	* ���\�[�X�����邩�`�F�b�N
	* @brief ���\�[�X�����邩�`�F�b�N
	* @param name [in]�@���\�[�X�̖��O
	* @param group [in]�@�O���[�v
	* @return true:���݂���,false:����
	*/
	bool IsSet(std::string name, int group = 0);
	/**
	* @fn
	* ���\�[�X�̍폜
	* @brief ���\�[�X�̂̍폜
	* @param group [in]�@�O���[�v
	* @param name [in]�@���\�[�X�̖��O
	*/
	void Delete(std::string name, int group = 0);
	/**
	* @fn
	* ���\�[�X�̍폜
	* @brief ���\�[�X�̂̍폜
	* @param name [in]�@���\�[�X�O���[�v
	*/
	void Delete(int group = 0);

	unsigned int GetDataSize();
};

#define ADD_RESOURCE(name,obj) if(!CResourceManager::GetInstance()->IsSet(name)) CResourceManager::GetInstance()->Add(name,obj)
#define CREATE_MODEL(name,path) ADD_RESOURCE(name,CModel::CreateModel(path))
#define CREATE_MODEL_C(name,path,x,y,z) ADD_RESOURCE(name,CModel::CreateModel(path,x,y,z))
#define CREATE_IMAGE(name,path)  ADD_RESOURCE(name,CImage::CreateImage(path))
#define CREATE_ANIM_IMAGE(name,path,d,w,h) ADD_RESOURCE(name,CImage::CreateImage(path,d,w,h))

#define GET_RESOURCE(name,T) dynamic_cast<T*>(CResourceManager::GetInstance()->Get(name))
#define GET_FIELD(name) dynamic_cast<CModelField*>(CResourceManager::GetInstance()->Get(name))
#define COPY_MODEL(name) *dynamic_cast<CModelA3M*>(CResourceManager::GetInstance()->Get(name))
#define COPY_IMAGE(name) *dynamic_cast<CImage*>(CResourceManager::GetInstance()->Get(name))
#define COPY_RESOURCE(name,T) *dynamic_cast<T*>(CResourceManager::GetInstance()->Get(name))
#define DUPLICATE_RESOURCE(name,T) new T(*dynamic_cast<T*>(CResourceManager::GetInstance()->Get(name)))

