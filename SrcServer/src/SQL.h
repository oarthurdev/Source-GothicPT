#pragma once


#include <sql.h>
#include <sqlext.h>

class SQL
{
public:
	virtual ~SQL();

	static SQL* GetInstance()
	{
		static SQL instance;
		return &instance;
	}

	BOOL		Connect(LPCSTR szServer, LPCSTR szUser, LPCSTR szPw);
	BOOL		IsConnected() { return m_bConnect; }
	void		Disconnect();
	void		Init();
	void		EnterSqlSection();
	void		LeaveSqlSection();
	BOOL		Execute(LPCSTR szQuery);
	BOOL		Fetch();
	

	SQLINTEGER	GetColLength(int nCol);

	BOOL		GetDataValue(int nCol, char* szData);
	BOOL		GetDataValue(int nCol, int* nData);
	
	
	
private:
	SQL();
	CRITICAL_SECTION	m_SqlSection;
	BOOL				m_bConnect;
	SQLHENV				m_hENV;
	SQLHDBC				m_hDBC;
	SQLHSTMT			m_hSTMT;
};


