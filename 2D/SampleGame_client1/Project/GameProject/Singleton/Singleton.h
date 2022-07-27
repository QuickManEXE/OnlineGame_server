#pragma once


template<class T>
class Singleton
{
protected:
    //  �R���X�g���N�^�̊O���ł̎g�p���֎~
    Singleton() {}
    virtual ~Singleton() {}
private:
    // �R�s�[�R���X�g���N�^�̎g�p���֎~
    Singleton(const Singleton&);
    Singleton& operator = (const Singleton&);
public:
    static void Build()
    {
        assert(!m_pInstance);
        m_pInstance = new T;
    }
    static void Release()
    {
        assert(m_pInstance);
        m_pInstance = null;
    }
    static T& Instance()
    {
        return *m_pInstance;
    }
private:
    static T* m_pInstance;
};

template<class T>
T* Singleton<T>::m_pInstance = NULL;