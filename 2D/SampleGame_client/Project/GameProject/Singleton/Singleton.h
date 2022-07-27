#pragma once


template<class T>
class Singleton
{
protected:
    //  コンストラクタの外部での使用を禁止
    Singleton() {}
    virtual ~Singleton() {}
private:
    // コピーコンストラクタの使用を禁止
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