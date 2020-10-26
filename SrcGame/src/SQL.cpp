#include "sinbaram\\sinlinkheader.h"


SQL::SQL()
{
	m_bConnect	= FALSE;
}

SQL::~SQL()
{
}

BOOL SQL::Connect(LPCSTR szServer, LPCSTR szUser, LPCSTR szPw)
{
	if (SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hENV)))
		if (SQL_SUCCEEDED(SQLSetEnvAttr(m_hENV, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)))
			if (SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, m_hENV, &m_hDBC)))
			{
				char OutConnectionString[1024] = {};
				char InConnectionString[1024] = {};
				wsprintf(InConnectionString, "DRIVER={SQL Server};SERVER=%s;UID=%s;PWD=%s;", szServer, szUser, szPw);

				if (SQL_SUCCEEDED(SQLDriverConnect(m_hDBC, NULL, (SQLCHAR*)InConnectionString, SQL_NTS,
					(SQLCHAR*)OutConnectionString, sizeof(OutConnectionString), NULL, SQL_DRIVER_NOPROMPT)))
						m_bConnect = TRUE;
				InitializeCriticalSection(&m_SqlSection);
			}

	return m_bConnect;
}

void SQL::Disconnect()
{
	if (m_bConnect)
	{
		m_bConnect = FALSE;
		SQLDisconnect(m_hDBC);
		SQLFreeHandle(SQL_HANDLE_STMT, m_hSTMT);
		SQLFreeHandle(SQL_HANDLE_DBC, m_hDBC);
		SQLFreeHandle(SQL_HANDLE_ENV, m_hENV);

		DeleteCriticalSection(&m_SqlSection);
	}
}

void SQL::Init()
{
	InitializeCriticalSection(&m_SqlSection);
}

void SQL::EnterSqlSection()
{
	EnterCriticalSection(&m_SqlSection);
}

void SQL::LeaveSqlSection()
{
	LeaveCriticalSection(&m_SqlSection);
}

BOOL SQL::Execute(LPCSTR szQuery)
{
	if (m_hSTMT)
		SQLFreeHandle(SQL_HANDLE_STMT, m_hSTMT);

	SQLAllocHandle(SQL_HANDLE_STMT, m_hDBC, &m_hSTMT);

	SQLRETURN Result = SQLExecDirect(m_hSTMT, (SQLCHAR*)szQuery, SQL_NTS);

	if (SQL_SUCCEEDED(Result))
		return TRUE;

	SQLFreeHandle(SQL_HANDLE_STMT, m_hSTMT);
	m_hSTMT = 0;

	return FALSE;
}

BOOL SQL::Fetch()
{
	SQLRETURN Result = SQLFetch(m_hSTMT);

	return SQL_SUCCEEDED(Result);
}

SQLINTEGER SQL::GetColLength(int nCol)
{
	SQLSMALLINT sDataType, sDig, sNullable;
	SQLUINTEGER nColSize;

	SQLDescribeCol(m_hSTMT, nCol, NULL, 0, NULL, &sDataType, &nColSize, &sDig, &sNullable);

	return nColSize;
}

BOOL SQL::GetDataValue(int nCol, char* szData)
{
	SQLRETURN Result;
	SQLINTEGER nLenOrInd;
	SQLINTEGER nLength = GetColLength(nCol);

	Result = SQLGetData(m_hSTMT, (SQLUSMALLINT)nCol, SQL_C_CHAR, szData, nLength, &nLenOrInd);

	return SQL_SUCCEEDED(Result);
}

BOOL SQL::GetDataValue(int nCol, int* nData)
{
	SQLRETURN Result;
	SQLINTEGER nLenOrInd;
	SQLINTEGER nLength = GetColLength(nCol);

	Result = SQLGetData(m_hSTMT, (SQLUSMALLINT)nCol, SQL_C_LONG, nData, nLength, &nLenOrInd);

	return SQL_SUCCEEDED(Result);
}




