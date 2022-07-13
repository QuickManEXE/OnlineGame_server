#pragma once

#include "GL.h"
#include "CVector.h"
#include "AL/alc.h"
#include "AL/al.h"
#include <map>
#include <string>
class CCamera;
struct SSoundParam {
	float		vol;
	float		pan;
	float		pitch;
	bool		is3D;
	float		dist;
	float		rolloff_factor;
	float		reference_distance;
	SSoundParam() {
		vol = 1.0f;
		pan = 0.0f;
		pitch = 1.0f;
		is3D = false;
		dist = FLT_MAX;
		rolloff_factor = 1.0f;
		reference_distance = 1.0f;
	}
};
class CSoundBase {
	ALuint *m_source;
	ALuint m_buffer;
	ALuint m_current;
	int m_layer_max;
	int m_channels;
	int m_sample_rate;
	SSoundParam m_param;
public:
	CSoundBase();
	~CSoundBase();
	bool Load(const char *path, int layer=1,bool is3D=false);
	int Play(bool boLoop=false);
	void Resume(bool boLoop=false,int layer=0);
	int Play3D(const CVector3D& pos,const CVector3D& velocity, bool boLoop = false);
	void SetPos(CVector3D pos, int layer = -1);
	void SetdMaxDistance(float dist) { m_param.dist = dist; }
	void Stop(int layer=-1);
	void Pause(int layer=-1);

	/*!
	@brief	���ʂ̐ݒ�
	@param	volumes			[in] ����(�y�ŏ��z0.0�`1.0�y�f�t�H���g�z) 
	**/
	void Volume(float volumes, int layer=-1);
	/*!
	@brief	�Đ����x�̐ݒ�
	@param	rato			[in] ���x(�y�x���z0.0�`1.0�y�f�t�H���g�z�`�y�����z)
	**/
	void Pitch(float ratio, int layer=-1);
	/*!
	@brief	�p���̐ݒ�
	@param	pan			[in] �p��(�y���z-1.0�`0.0�y���S�z�`1.0�y�E�z)
	**/
	void Pan(float pan, int layer = -1);
	/*!
	@brief	���������̐ݒ�
	@param	max_distance		[in] �����l
	@param	reference_distance	[in] �����l
	@param	rolloff_factor		[in] �����l
	**/
	void SetDistance(float max_distance, float reference_distance, float rolloff_factor, int layer = -1);

	bool CheckEnd(int layer = 0);

	/*!
	@brief	�Đ��ʒu���擾
	@retval	�Đ��ʒu�i�b�j
	**/
	float GetOffset(int layer = 0);
};
class CSound {
	std::map<std::string, CSoundBase*> m_list;
	static CSound *m_instance;
	friend class CSoundBase;
public:
	CSound();
	~CSound();
	/*!
	@brief	�T�E���h�}�l�[�W���[�̎擾
	**/
	static CSound* GetInstance() {
		if (!m_instance) m_instance = new CSound();
		return m_instance;
	}
	static void ClearInstance() {
		if (!m_instance) return;
		delete m_instance;
		m_instance = nullptr;
	}
	/*!
	@brief	�T�E���h�I�u�W�F�N�g�̎擾
	@param	name			[in]���ʖ�
	**/
	CSoundBase* GetSound(const char *name) {
		if (!m_list[name]) m_list[name] = new CSoundBase();
		return m_list[name];
	}
	/*!
	@brief	�T�E���h�I�u�W�F�N�g�̔j��
	@param	name			[in]���ʖ�
	**/
	void ReleaseSound(const char *name);
	/*!
	@brief	���X�i�[�̍X�V
	**/
	void UpdateListener();

	
	void StopAll();
	
};

#define SOUND(name)	CSound::GetInstance()->GetSound(name)
