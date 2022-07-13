#ifndef	INCLUDE_TASK
#define	INCLUDE_TASK

class Task
{
	friend class TaskManager;

private:
	Task * mp_Prev;					// �D�揇�ʂ̑O�̃|�C���^
	Task * mp_Next;					// �D�揇�ʂ̌�̃|�C���^

	int m_Priority;					// �D�揇��(�������̂��珈��������)
	bool m_IsPause;					// �|�[�Y
	
	const char * m_Name;			// �^�X�N�̖��O	

	bool m_Protect;					//�폜�h�~���邩�ǂ���
	bool m_Kill;					//�L�����邩�ǂ���
public:
	// �R���X�g���N�^ �E �f�X�g���N�^
	Task(int _priority, const char * _name);
	Task();
	virtual ~Task();

	//�폜�h�~
	void SetProtect(bool _isProtect);
	// �ʏ�֐�
	void SetKill();
	// �폜
	void Kill();	

	// �ꎞ��~
	void SetPause(bool _isPause);
	// �D��x�擾
	int GetPriority()const;
	// �ꎞ��~���Ă��邩�ǂ���
	bool IsPause()const;
	// �^�X�N�̖��O
	const char* GetName()const;

private:

	// �X�V
	virtual void Update();

};

#endif // INCLUDE_TASK