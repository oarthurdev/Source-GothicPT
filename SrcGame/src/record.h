#ifndef	_RECORD_HEADER

#define _RECORD_HEADER

#define RECORD_ITEM_MAX		200
#define	TRANS_RECORD_LEN	(smSOCKBUFF_SIZE-32)


#define	PRIME_ITEM_PACKAGE_NONE			0
#define	PRIME_ITEM_PACKAGE_BRONZE		1
#define	PRIME_ITEM_PACKAGE_SILVER		2
#define	PRIME_ITEM_PACKAGE_GOLD			3
#define	PRIME_ITEM_PACKAGE_ULTRA		4

#define	PRIME_ITEM_PACKAGE_BRONZE2		5
#define	PRIME_ITEM_PACKAGE_SILVER2		6
#define	PRIME_ITEM_PACKAGE_GOLD2		7
#define	PRIME_ITEM_PACKAGE_ULTRA2		8
#define	PRIME_ITEM_PACKAGE_NONE_50_EXPUP		 9 
#define	PRIME_ITEM_PACKAGE_NONE_100_EXPUP		10 


struct	sRECORD_ITEM
{
	int	ItemCount;
	int x, y;
	int	ItemPosition;

	sITEMINFO sItemInfo;
};

const int _SIN_MAX_USE_SKILL = 16;


struct	RECORD_SKILL
{
	BYTE	bSkillPoint[_SIN_MAX_USE_SKILL];
	WORD	wSkillMastery[_SIN_MAX_USE_SKILL];
	BYTE	bShortKey[_SIN_MAX_USE_SKILL];
	WORD	wSelectSkill[2];

};


struct	sQUEST_INFO
{
	WORD	wQuestCode[2];

	DWORD	Data[7];
};

#define	LAST_QUEST_MAX		32
#define	LAST_QUEST_MASK		31

struct	sLAST_QUEST_INFO
{
	WORD wLastQuest[LAST_QUEST_MAX];
	int	LastQuestCount;
};

extern sLAST_QUEST_INFO	RecordLastQuestInfo;



struct	sGAME_SAVE_INFO
{
	DWORD	Head;

	int		PlayStageNum;
	int		CameraMode;
	int		PosX, PosZ;
	int		LastMoeny;

	DWORD	dwChkSum_CharInfo;

	RECORD_SKILL	SkillInfo;

	int		SaveTime;

	int		PCRNo;
	short	EventPlay[2];

	short	sPetInfo[2];

	short	sPotionUpdate[2];
	short	sPotionCount[3][4];
	WORD	wForceOrbUsing[2];

	DWORD	dwLevelQuestLog;

	int		ShortKey_NormalAttack;

	int		BlessCastleTax;
	DWORD	dwBlessCastleMaster;

	DWORD	dwElementaryQuestLog;


	DWORD	dwTime_PrimeItem_X2;
	DWORD	dwTime_PrimeItem_ExpUp;
	DWORD	dwTime_PrimeItem_VampCuspid;
	DWORD	dwTime_PrimeItem_ManaRecharg;
	DWORD	dwPrimeItem_PackageCode;
	DWORD	dwTime_PrimeItem_MightofAwell;
	DWORD	dwTime_PrimeItem_MightofAwell2;
	DWORD	dwTime_PrimeItem_ManaReduce;
	DWORD	dwTime_PrimeItem_PhenixPet;
	DWORD	dwTime_PrimeItem_HelpPet;
	DWORD	dwTime_PrimeItem_VampCuspid_EX;
	DWORD	dwTime_PrimeItem_StaminaReduce;


	int		TotalSubExp;
	int		TotalMoney;
	int		TotalExp;

	char	szMasterID[ACCOUNT_SIZE];

	sQUEST_INFO			QuestInfo;
	sLAST_QUEST_INFO	LastQuestInfo;

	DWORD	TT_ServerID;

	WORD	wLifeBoosterUsing[2];
	WORD	wManaBoosterUsing[2];
	WORD	wStaminaBoosterUsing[2];

	WORD	wSkillDelayUsing[2];

	DWORD	dwTemp2[34];

	DWORD   QuestDiary_State;
	DWORD   QuestDiary_Time;
	DWORD   QuestDiary_Kill;
	int     BattleLevel;
	int     BattleExp;

};



struct	TRANS_RECORD_DATA
{
	int size, code;

	char	szHeader[8];

	smCHAR_INFO smCharInfo;

	sGAME_SAVE_INFO	GameSaveInfo;

	sTHROW_ITEM_INFO ThrowItemInfo[THROW_ITEM_INFO_MAX];
	int		ThrowItemCount;

	int		ItemCount;
	int		ItemSubStart;
	
	int		DataSize;
	BYTE	Data[sizeof(sRECORD_ITEM) * RECORD_ITEM_MAX];

	TRANS_RECORD_DATA()
	{
		size = 0;
		code = 0;

		ZeroMemory(szHeader, sizeof(szHeader));
		ZeroMemory(ThrowItemInfo, sizeof(ThrowItemInfo));

		ThrowItemCount = 0;
		ItemCount = 0;
		ItemSubStart = 0;
		DataSize = 0;

		ZeroMemory(Data, sizeof(Data));
	}
};


struct	TRANS_RECORD_DATAS
{
	int	size, code;
	int	Count, Total;
	int	TransSize;

	char szData[TRANS_RECORD_LEN];

	TRANS_RECORD_DATAS()
	{
		size = 0;
		code = 0;
		Count = 0;
		Total = 0;
		TransSize = 0;

		ZeroMemory(szData, sizeof(szData));
	}
};
#define sPLAY_CHAR_MAX		6




struct	sPLAY_USER_DATA
{
	char	szHeader[16];
	char	szID[32];

	char	szCharName[sPLAY_CHAR_MAX][32];
};



struct	_TRANS_CHAR_INFO
{
	char	szName[NAME_SIZE];
	char	szModelName[64];
	char	szModelName2[64];
	DWORD	JOB_CODE;
	int		Level;
	DWORD	Brood;
	DWORD	dwArmorCode;
	int		StartField;
	int		PosX, PosZ;
	DWORD	dwTemp[13];
};

struct	TRANS_USERCHAR_INFO
{
	int		size, code;

	char	szID[ACCOUNT_SIZE];
	int		PlayUserCount;

	_TRANS_CHAR_INFO	CharInfo[sPLAY_CHAR_MAX];
};


class rsRECORD_DBASE
{
public:
	TRANS_RECORD_DATA TransRecordData;
	int	TransLastPartCount;
	BYTE	TransDataBlock[64];
	DWORD	dwRecordTime;
	DWORD	dwNextRecordTime;

	rsRECORD_DBASE()
	{
		TransLastPartCount = 0;
		ZeroMemory(&TransDataBlock, sizeof(TransDataBlock));
		dwRecordTime = 0;
		dwNextRecordTime = 0;
	}


	int MakeRecordData(smCHAR_INFO *lpCharInfo, sITEM *lpItems, sITEM *lpItems2, sITEM *lpMouseItem = 0);

	int	ResotrRecordData(smCHAR_INFO *lpCharInfo, sITEM *lpItems, sITEM *lpItems2, sITEM *lpMouseItem = 0);



	int SendRecordDataToServer(smWINSOCK *lpsmSock);

	int RecvRecordDataFromServer(TRANS_RECORD_DATAS *lpTransRecord);



	int RecvRecordDataFromClient(TRANS_RECORD_DATAS *lpTransRecord, rsPLAYINFO *lpPlayInfo);


	int SendRecordDataToClient(rsPLAYINFO *lpPlayInfo, char *szName, smWINSOCK *lpsmSock, int Mode = 0);


	int MakeRecordItemList(rsPLAYINFO *lpPlayInfo);




	int DeleteCharData(const char *szID, char *szName);

	int InsertCharData(const char *szID, char *szName, int Mode = 0);


	int IsData(char *szName);

	int SendUserDataToClient(const char *szID, smWINSOCK *lpsmSock, char *szServerID);


	int SaveThrowData(char *szName, sTHROW_ITEM_INFO *lpThrowItemList, int Count, int SaveMoney);

};

int GetUserDataFile(const char *szName, char *szFileName);


int rsRecordMemoryBuffToFile(rsPLAYINFO *lpPlayInfo, const char *szName, char *lpRecordMemBuff);



int rsRecordMemoryBuff_CheckInvenItem(rsPLAYINFO *lpPlayInfo, int Mode = 0);

int rsSaveThrowData(rsPLAYINFO *lpPlayInfo);



int rsSaveWareHouseData(const char *szID, TRANS_WAREHOUSE *lpTransWareHouse);

int rsLoadWareHouseData(rsPLAYINFO *lpPlayInfo);

int rsCheckAccountChar(const char *szID, char *szName);

int rsLoadWareHouseData_Admin(rsPLAYINFO *lpPlayInfo, char *szID, int Day);


int rsLoadServerForce(rsPLAYINFO *lpPlayInfo, sGAME_SAVE_INFO *lpGameSaveInfo);

int rsSaveServerForce(rsPLAYINFO *lpPlayInfo, sGAME_SAVE_INFO *lpGameSaveInfo);

int rsSaveServerPotion(rsPLAYINFO *lpPlayInfo, sGAME_SAVE_INFO *lpGameSaveInfo);

int rsCompareServerPotion(rsPLAYINFO *lpPlayInfo, sGAME_SAVE_INFO *lpGameSaveInfo);



int CreateDataServerDirectory();


int Record_LastQuest(WORD	wQuestCode);

int FindLastQuestCode(WORD wQuestCode);


int	CheckSkillPoint(int Level, RECORD_SKILL *lpRecordSkill, int *spTotal, DWORD dwLevelQuestLog);




int	rsSavePostBox(rsPLAYINFO	*lpPlayInfo);

int	rsLoadPostBox(rsPLAYINFO	*lpPlayInfo);

int	rsAddPostBox_Present(rsPLAYINFO *lpPlayInfo);


int	OpenStarPointEvent(rsPLAYINFO *lpPlayInfo, smCHAR_INFO *lpCharInfo);

int	OpenStarPointTicket(rsPLAYINFO *lpPlayInfo);


int ImportTTServerUser(char *szID, char *szServerID);

int SetServerID(char *szID, char *szServerID, size_t size);



int rsTimeRecData();

int rsInitDataBase();

int rsCloseDataBase();



int GetSkillPoint_LevelQuest(int Level, DWORD dwLevelQuestLog);

int GetStatePoint_LevelQuest(int Level, DWORD dwLevelQuestLog);

int ReformCharStatePoint(smCHAR_INFO *lpCharInfo, DWORD dwLevelQuestLog);



int	rsCheck_LoginServerSafeKey(smCHAR_INFO *lpCharInfo, DWORD dwSpdSumCode = 0);

int rsSet_LoginServerSafeKey(smCHAR_INFO *lpCharInfo);

DWORD	rsGetLoginSafeKey(smCHAR_INFO *lpCharInfo, DWORD dwSpdSumCode = 0);



extern int	Permit_CheckMoney;
extern int	Permit_CheckExp;


struct	sBILLING_INFO
{
	int	PCRNo;
	int	EventPlay[2];
};

extern sBILLING_INFO	*sBiInfo;


#endif
