#ifndef __ISAOCHECK_H__
#define __ISAOCHECK_H__
#ifndef USE_PROSTONTALE		
#include "..\\clanmenu\\cE_CViewClanInfo.h"
#endif

#define SAVE_DIR	"savedata\\clanDATA"
#define SAVE_EXE	"cl"




enum
{
	ISAO_REJECT_OK = 0,
	ISAO_REJECT_BADPASS = 1,
	ISAO_REJECT_BADNAME = 2,
	ISAO_REJECT_LOCKOUT = 3,
	ISAO_REJECT_TEST_OVER = 4,
	ISAO_REJECT_UNFAIR = 5,
	ISAO_REJECT_STOPPING = 6,
	ISAO_REJECT_EXPIRE = 7,
	ISAO_REJECT_NOT_BOUGHT = 8,
	ISAO_REJECT_DB_MAINTE = 9,
	ISAO_REJECT_OTHER = 10,







	ISAO_ERR_TOP = 1000,
	ISAO_ERR_WINSOCK_NOERR,
	ISAO_ERR_WINSOCK_START,
	ISAO_ERR_WINSOCK_VERSION,
	ISAO_ERR_TCP_CONNECT,
	ISAO_ERR_SSL_READ,
	ISAO_ERR_SSL_TIMEOUT,
	ISAO_ERR_NONE_REEJCT,
	ISAO_ERR_UNKNOWN_REJECT,
	ISAO_ERR_RECONNECT,
	ISAO_ERR_END
};

int IsaoCheck(char *id, char *pass, int iCheckOn, int iTimeOut, char *ipaddr, long StartTime);
int IsaoCheck2(char *id, char *pass, int iCheckOn, int iTimeOut, char *ipaddr, long usertime);

int UserLogin(char* UserID, char* PassWord);
int InsertUser(char* UserID, char* PassWord, char* UserName);
int DeleteUser(char* UserID);
int LoginCheck(char* UserID, char* start_time);
int Login_List(char* UserID, char* end_time, char* use_time);
#endif



bool MultiByteToWideCharByCodePage(char *szMBCS, wchar_t *szUnicode, int iCodePage);
bool WideCharToMultiByteByCodePage(wchar_t *szUnicode, char *szMBCS, int iCodePage);
bool MBCSToUTF8(char *szMBCS, char *szUTF8, int iMBCSCodePage);
bool UTF8ToWeb(char *szUTF8, char *szWeb);
bool MBCSToWeb(char *szMBCS, char *szWeb, int iMBCSCodePage);





class ISAOCHECK
{
public:
	int iCheckFlag;
	int iTimeOut;
	int hostPORT;
	char hostName[64];

	int hostPORT1;
	char hostName1[64];



	int HSsu;
	char *fileDATA_HS[30];


	ISAOCHECK();
	~ISAOCHECK();

	void init();
	void init(int iCheckON, int iTimeOUT);
	void init_HostName_Port(char *hostname, int port);
	void init_HostName_Port1(char *hostname, int port);
	void close();
	void main();



	int connect_WEBdb(char *szWriteBuffer, char *szReadBuffer);

	int connect_WEBdb_1(char *szWriteBuffer, char *szReadBuffer);

	int connect_WEBdb_BINARY(char *szWriteBuffer, char *szReadBuffer, int *dataSize);

	int chk_readbuffer(char *cmd, char *readbuf, int *iRejectC);
	int chk_readStrBuf(char *cmd, char *readbuf, char *retBuf);

	int IsaoCheck(char *id, char *pass, char *ipaddr, long StartTime);
	int IsaoCheck_GameExit(char *id, char *pass, char *ipaddr, long usertime);





	int isClanMember(char *ClanZang_id, char* gserver, char* ClanZang_ChaName, char* ret_Buf);


	int isCheckClanMember(char *pszServerName, char *pszUserName);




	int joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char* ClanName, char* ClanWon, char* ClanWon_ID, int level, DWORD chtype, int joinlevel, char *chipflag);




	int isCheckClanJang(char *ClanZang_ID, char *gserver);

	int isCheckClanName(char *ClanName, char *gserver);

	int makeClan(char *ClanZang_ID, char* gserver, char* ClanZang_ChaName, char* ClanName, char *explanation, DWORD chtype, int level, char* data);

	int read_ClanName(int readClumns);

	int read_ClanData(char *ClanZang_ID, char* gserver, char* ClanZang_ChaName, char* ret_Buf);

	int BreakUPClan(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char *ClanName);

	int Banishiment(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char *ClanName, char *ClanWon);
	int WarhouseRight(char *clname, char *right_str);
	int updateFlag(char *clname);

	int Secession(char* clanzang, char* gserver, char* SecessionID, char* clanname);

	int isPFlag(char *userid, char *clanname, char *chaname, char *gserver, char *pflag, char *gunbun);

	int ReadClanInfo(char *clanNum, char* ret_Buf);



	int read_ClanImage(char *clanname, char *filename);

	int read_ClanImage2(char *clanname, char *filename, CLANINFO *ci);

	int write_ClanImageFile(char *filename);



	int connect_WEBdb_NOTICE(char *szWriteBuffer, char *szReadBuffer);
	int ReadNotice(char *userid, char *chaname, char *gserver, char *buf);

	int LeaveClan(char *clanname, char *chaname, char *gserver);


	int isKPFlag(char *userid, char *clanname, char *chaname, char *gserver, char *pflag, char *gunbun);

	int AppointSubChip(char *gserver, char* clanwon);
	int ReleaseSubChip(char *gserver, char* clanwon);


	int	GetWavFile(char* FileName);


	void Convert_bin2HS(char *sorce, int len);
	int WEBdb_Exam();







	int read_sod2(char *usid, char *charname, char *gserver, int index, char *szSod2Buff);

};




#undef EXTERN
#ifdef __ISAOCHECK_CPP__
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN ISAOCHECK iCheck;




