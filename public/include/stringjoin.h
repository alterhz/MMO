//----------------------------------------
// 创建时间 : 2015-1-4
// 作者 : hanzhe
// 说明 : 字符串拼接


#ifndef _STRINGJOIN_
#define _STRINGJOIN_

#include <string>
using std::string;

#ifdef WIN32
	#define swPrintf _snprintf_s
#else
	#include <memory.h>
	#define swPrintf snprintf
#endif // WIN32


template<unsigned int LENGTH>
class StringJoin
{
public:
	StringJoin() 
	{
		memset(m_szData, 0, sizeof(m_szData));
	}
	~StringJoin() 
	{
	}

	StringJoin & operator + (short n)
	{
		char szFormat[32] = {0};
		swPrintf(szFormat, sizeof(szFormat)-1, "%d", n);
		strcat(m_szData, szFormat);
		return *this;
	}
	StringJoin & operator + (unsigned short n)
	{
		char szFormat[32] = {0};
		swPrintf(szFormat, sizeof(szFormat)-1, "%d", n);
		strcat(m_szData, szFormat);
		return *this;
	}
	StringJoin & operator + (int n)
	{
		char szFormat[32] = {0};
		swPrintf(szFormat, sizeof(szFormat)-1, "%d", n);
		strcat(m_szData, szFormat);
		return *this;
	}
	StringJoin & operator + (unsigned int n)
	{
		char szFormat[32] = {0};
		swPrintf(szFormat, sizeof(szFormat)-1, "%d", n);
		strcat(m_szData, szFormat);
		return *this;
	}
	StringJoin & operator + (long n)
	{
		char szFormat[32] = {0};
		swPrintf(szFormat, sizeof(szFormat)-1, "%ld", n);
		strcat(m_szData, szFormat);
		return *this;
	}
	StringJoin & operator + (unsigned long n)
	{
		char szFormat[32] = {0};
		swPrintf(szFormat, sizeof(szFormat)-1, "%ld", n);
		strcat(m_szData, szFormat);
		return *this;
	}
	StringJoin & operator + (float n)
	{
		char szFormat[32] = {0};
		swPrintf(szFormat, sizeof(szFormat)-1, "%f", n);
		strcat(m_szData, szFormat);
		return *this;
	}
	StringJoin & operator + (double n)
	{
		char szFormat[32] = {0};
		swPrintf(szFormat, sizeof(szFormat)-1, "%lf", n);
		strcat(m_szData, szFormat);
		return *this;
	}
	StringJoin & operator + (const char *p)
	{
		strcat(m_szData, p);
		return *this;
	}
	StringJoin & operator + (string s)
	{
		strcat(m_szData, s.data());
		return *this;
	}
	StringJoin & operator + (bool b)
	{
		if (b)
		{
			strcat(m_szData, "true");
		}
		else
		{
			strcat(m_szData, "false");
		}

		return *this;
	}


	const char * GetData() const { return m_szData; }

private:
	char m_szData[LENGTH];

};

#endif