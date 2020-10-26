#pragma once

#include <objbase.h>
#include <vector>
#include <memory>
#include <comdef.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

enum EDatabaseID
{
	DATABASEID_NULL,
	DATABASEID_AccountDB,
	DATABASEID_BillingDB,
	DATABASEID_BillingLogDB,
	DATABASEID_ClanDB,
	DATABASEID_GameLogDB,
	DATABASEID_ItemLogDB,
	DATABASEID_LogDB,
	DATABASEID_PCRoom,
	DATABASEID_PCRoomLog,
	DATABASEID_rPTDB,
	DATABASEID_SoD2DB,
	DATABASEID_SodDB,
	DATABASEID_PristonDB,
	DATABASEID_Priston,
	DATABASEID_QuestDB,
};

enum EDatabaseDataType
{
	PARAMTYPE_Integer,
	PARAMTYPE_String,
	PARAMTYPE_Float,
	PARAMTYPE_Int64,
	PARAMTYPE_Short,
	PARAMTYPE_Time,
};

struct DatabaseStructureData
{
	EDatabaseID eDatabaseID;
	char * pszDatabaseName;
};


class Database
{
private:
	DatabaseStructureData * GetDatabaseData(EDatabaseID eDatabaseID);
	SQLHANDLE hEnv;
	SQLHANDLE hConnection;
	SQLHANDLE hStatement;
	EDatabaseID eID;
	char szDatabaseName[64];

	char szQuery[2048];

	CRITICAL_SECTION sCriticalSection;

public:

	bool Init(EDatabaseID eDatabaseID);

	BOOL SQLTimeStampToSystemTime(SYSTEMTIME * psSystemTime, SQL_TIMESTAMP_STRUCT * psSQLTimeStamp);

	BOOL Open();
	BOOL Prepare(const char * pszQuery);
	BOOL Execute(BOOL bFetch = TRUE);

	BOOL BindInputParameter(void * pParameter, int iPosition, EDatabaseDataType eDataType);
	BOOL GetData(void * pParameter, int iSize, int iPosition, EDatabaseDataType eDataType);
	BOOL NextRow();
	BOOL Close();

	static std::shared_ptr<Database> GetConnection(EDatabaseID eDatabaseID);

	Database();
	virtual ~Database();
};

