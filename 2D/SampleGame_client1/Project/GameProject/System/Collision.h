/**
* @Author	YukiYamaji
* @Day		17/11/18
* @Brief	�Փ˔�����
*/

#ifndef COLLISION_GUARD
#define COLLISION_GUARD

#include "CollisionCall.h"
#include "Task.h"

//�e�}�X�N�ݒ�
enum ECOLLISION_Layer{
	eLayer_Player,
	eLayer_Enemy,
	eLayer_Field,
	eLayer_BulletPlayer,
	eLayer_BulletEnemy,
	eLayer_Max,
};
enum ECOLLISION_Type {
	eCollision_Shpere,
	eCollision_Rect,
};


//���f�[�^
struct T_Shpere
{
	CVector2D	*pos;	//���W
	float		rad;	//���a
};

struct T_Rect
{
	CRect *rect;
};


class Collision : public Task
{	
private:
	CollisionCall	*mp_obj;		//�Փ˔���I�u�W�F�N�g�|�C���^
	//�e�`��f�[�^�|�C���^
	T_Shpere		m_shpere;		
	T_Rect           m_rect;
	int				 m_type;		//�`��^�C�v
	unsigned int	 m_body;		//���g�}�X�N
	bool			m_active;		//�Փ˗L���t���O
	static char m_layer_mask[eLayer_Max][eLayer_Max];
public:

	//���p�R���X�g���N�^
	Collision(CVector2D *p,float rad, CollisionCall *obj, unsigned int body);
	Collision(CRect* rect, CollisionCall* obj, unsigned int body);
	~Collision();
	void CheckCollision(Task *t);										//�e�Փ˔���`�F�b�N
	static bool CollosionShpere(Collision *c1, Collision *c2);			//���΋�
	static bool CollisionRect(Collision* c1, Collision* c2);

																		//�Փˋ��擾
	const T_Shpere *GetColllisionShpere() const
	{
		return &m_shpere;
	}
	//�Փ˔���I�u�W�F�N�g�擾
	Task* GetObj() const
	{
		return dynamic_cast<Task*>(mp_obj);
	}
	//�Փ˗L���t���O��ݒ�
	//@param [in] m_actice true:�L�� false:����
	void SetActive(bool f) { m_active = f; }
	friend class Collision;
};

#endif