//----------------------------------------
// ����ʱ�� : 2015-1-10
// ���� : hanzhe
// ˵�� : ���߼�

#ifndef _UTILITY_H_
#define _UTILITY_H_

template <typename T>
class Singleton
{
public:
	Singleton() {}
	virtual ~Singleton() {}
	static void delMe(void)
	{//�����������destoryMe�б�����
		if (m_pSingleTon)
		{
			delete m_pSingleTon;
			m_pSingleTon = nullptr;
		}
	}

	static T* instance( void )
	{
		if (!m_pSingleTon)
		{
			m_pSingleTon = new T;
		}

		return m_pSingleTon;
	}

	static T& getMe(void)
	{
		return *instance();
	}

protected:
	static T* m_pSingleTon;

private:
	Singleton(const Singleton&);
	Singleton & operator= (const Singleton &);
};
template <typename T> T* Singleton<T>::m_pSingleTon = NULL;


// �ӿ�
class IAppInterface
{
public:
	virtual ~IAppInterface() {}

public:
	virtual bool Init() = 0;
	virtual void Release() = 0;
	virtual void Run() = 0;
	virtual void Stop() = 0;
};


#endif