//----------------------------------------
// 创建时间 : 2015-1-10
// 作者 : hanzhe
// 说明 : 工具集

#ifndef _UTILITY_H_
#define _UTILITY_H_

template <typename T>
class Singleton
{
public:
	Singleton() {}
	virtual ~Singleton() {}
	static void delMe(void)
	{//可以在子类的destoryMe中被调用
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

#endif