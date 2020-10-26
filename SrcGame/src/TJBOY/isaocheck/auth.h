#ifndef __AUTH_H__
#define __AUTH_H__
#ifndef USE_PROSTONTALE		
#include "..\\clanmenu\\cE_CViewClanInfo.h"
#endif



#define CDKEYLEN 32
#define CONFIG   10

#define AUTH_ERROR_OTHER 1009
#define INET_ADDRSTRLEN 16
#define AUTH_ERROR_END  20
#define AUTH_OK 1



enum
{


	AUTH_QUE_CMD_NONE,

	AUTH_QUE_CMD_isClanMember,
	AUTH_QUE_CMD_CL_MAKE,
	AUTH_QUE_CMD_CL_MEMBER_MAKE,
	AUTH_QUE_CMD_ReadClan,
	AUTH_QUE_CMD_BreakUP,
	AUTH_QUE_CMD_Banishiment,
	AUTH_QUE_CMD_WarhouseR,
	AUTH_QUE_CMD_updateFlag,
	AUTH_QUE_CMD_Secession,

	AUTH_QUE_CMD_MarkREAD,

	AUTH_QUE_CMD_isCheckClanJang,
	AUTH_QUE_CMD_isCheckClanName,
	AUTH_QUE_CMD_isPFlag,
	AUTH_QUE_CMD_ReadClanInfo,
	AUTH_QUE_CMD_MarkREAD2,
	AUTH_QUE_CMD_Updatcldata,
	AUTH_QUE_CMD_ReadNotice,
	AUTH_QUE_CMD_LeaveClan,
	AUTH_QUE_CMD_isKPFlag,
	AUTH_QUE_CMD_AppointSubChip,
	AUTH_QUE_CMD_ReleaseSubChip,
	AUTH_QUE_CMD_GetWavFile,

	AUTH_QUE_CMD_SOD2,
	AUTH_QUE_CMD_isCheckClanMember,
	AUTH_QUE_CMD_ALLNUM,
};



enum
{
	AUTH_QUE_STATUS_NONE,
	AUTH_QUE_STATUS_EXIST,
	AUTH_QUE_STATUS_BEGINAUTHPROC,
	AUTH_QUE_STATUS_ENDOFAUTHPROC,
};


typedef struct _STRUCT_AUTH_QUE
{

	int status;
	int command;
	int fdid;
	int result;
	int badmsg;
	int index;
	unsigned int query_time;
	char cdkey[CDKEYLEN];
	char isaokey[128];
	char password[128];




	char ip_address[128];
	long howmanyTime;

	char id[64];
	char charId[64];
	char expl[256];
	char clanName[64];
	char ret_Buf[2048];
	char gserver[64];
	char ClanWon_ID[64];
	char ClanWon_ChaName[64];
	char ClanZang_ID[64];
	char ClanZang_ChaName[64];
	char Gubun[2];
	char Mark[64];
	int  nNum;
	CLANINFO* ci;
	int ClanInfo_Count;
	int level;

	int joinlevel;
	int joinjobcode;
	char chipflag[2];
	DWORD job_code;
	char  szWavFileName[64];
	char  szSod2Buff[65536];




	char PFlag[3];



	struct _STRUCT_AUTH_QUE *pNext;
	struct _STRUCT_AUTH_QUE *pPrev;



	int sod2index;
}AUTH_QUE;


int AUTH_addQue(AUTH_QUE *que);
int AUTH_getResultLoop(void);



DWORD WINAPI AUTH_MainLoop(void* pVoid);
int end_GOLDmoney(char* cdkey, char* isaokey, char* passwd, char* ip_address);
int end_GOLDmoney2(char* cdkey, char* isaokey, char* passwd, char* ip_address);
int start_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address);
int IsaoCheck2(char *id, char *pass, int iCheckOn, int iTimeOut, char *ipaddr, long usertime);

enum
{
	AUTHLINKTBL_FREE,
	AUTHLINKTBL_START_WAIT,
	AUTHLINKTBL_WORKING,
	AUTHLINKTBL_FINISH,
	AUTHLINKTBL_MAX
};
typedef struct
{
	AUTH_QUE QueTop, QueTail;
}AUTHLINKTBL;




int end_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address);

#endif





#define FLAG_DEAD  0
#define FLAG_EXEC  1
#define FLAG_WAIT  2
#define FLAG_EXIT  3

typedef struct
{
	DWORD thrHandle;
	int flag;
	int state;
	int cnt;
} THREADstruct;

class WebDB_Thread
{
public:


	THREADstruct ThreadS;

	WebDB_Thread();
	~WebDB_Thread();

	void init();
	void init(int iCheckON);
	void init_HostName_Port(char *hostname, int port);
	void main();
	void end();


	void CheckHostNamePort(char *hostname, int port);

	int AUTH_init(int Num);
	int AUTH_close(void);

	void Suspend();
	void Resume();

	int AUTH_getResultLoop(void);







	int AUTH_proc_isClanMember(int quenum, int threadindex);
	int AUTH_proc_isClanMember_Result(int quenum, int threadindex);


	int AUTH_proc_isCheckClanMember(int quenum, int threadindex);
	int AUTH_proc_isCheckClanMember_Result(int quenum, int threadindex);
	int isCheckClanMember(char *pszServerName, char *pszUserName);



	int AUTH_proc_ClanMake(int quenum, int threadindex);
	int AUTH_proc_ClanMake_Result(int quenum, int threadindex);



	int AUTH_proc_Mmake(int quenum, int threadindex);
	int AUTH_proc_Mmake_Result(int quenum, int threadindex);


	int AUTH_proc_ReadClan(int quenum, int threadindex);
	int AUTH_proc_ReadClan_Result(int quenum, int threadindex);



	int AUTH_proc_BreakUP(int quenum, int threadindex);
	int AUTH_proc_BreakUP_Result(int quenum, int threadindex);


	int AUTH_proc_Banishiment(int quenum, int threadindex);
	int AUTH_proc_Banishiment_Result(int quenum, int threadindex);


	int AUTH_proc_WarhouseR(int quenum, int threadindex);
	int AUTH_proc_WarhouseR_Result(int quenum, int threadindex);


	int AUTH_proc_updateFlag(int quenum, int threadindex);
	int AUTH_proc_updateFlag_Result(int quenum, int threadindex);



	int AUTH_proc_Secession(int quenum, int threadindex);
	int AUTH_proc_Secession_Result(int quenum, int threadindex);



	int AUTH_proc_MarkREAD(int quenum, int threadindex);
	int AUTH_proc_MarkREAD_Result(int quenum, int threadindex);



	int AUTH_proc_MarkREAD2(int quenum, int threadindex);
	int AUTH_proc_MarkREAD2_Result(int quenum, int threadindex);


	int AUTH_proc_isCheckClanJang(int quenum, int threadindex);
	int AUTH_proc_isCheckClanJang_Result(int quenum, int threadindex);


	int AUTH_proc_isCheckClanName(int quenum, int threadindex);
	int AUTH_proc_isCheckClanName_Result(int quenum, int threadindex);


	int AUTH_proc_isPFlag(int quenum, int threadindex);
	int AUTH_proc_isPFlag_Result(int quenum, int threadindex);


	int AUTH_proc_isKPFlag(int quenum, int threadindex);
	int AUTH_proc_isKPFlag_Result(int quenum, int threadindex);


	int AUTH_proc_ReadClanInfo(int quenum, int threadindex);
	int AUTH_proc_ReadClanInfo_Result(int quenum, int threadindex);


	int AUTH_proc_Updatcldata(int quenum, int threadindex);
	int AUTH_proc_Updatcldata_Result(int quenum, int threadindex);


	int AUTH_proc_ReadNotice(int quenum, int threadindex);
	int AUTH_proc_ReadNotice_Result(int quenum, int threadindex);


	int AUTH_proc_LeaveClan(int quenum, int threadindex);
	int AUTH_proc_LeaveClan_Result(int quenum, int threadindex);


	int AUTH_proc_AppointSubChip(int quenum, int threadindex);
	int AUTH_proc_AppointSubChip_Result(int quenum, int threadindex);


	int AUTH_proc_ReleaseSubChip(int quenum, int threadindex);
	int AUTH_proc_ReleaseSubChip_Result(int quenum, int threadindex);


	int AUTH_proc_GetWavFile(int quenum, int threadindex);
	int AUTH_proc_GetWavFile_Result(int quenum, int threadindex);




	int isClanMember(char *ClanZang_id, char* gserver, char* ClanZang_ChaName);



	int joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char* ClanName, char* ClanWon, char* ClanWon_ID, int level, DWORD chtype, int joinlevel, char *chipflag);

	int make_Clan(char *ClanZang_ID, char* gserver, char* ClanZang_ChaName, char* ClanName, char *explanation, DWORD chtype, int level);
	int ReadClan(char *ClanZang_ID, char* gserver, char* ClanZang_ChaName);

	int BreakUP_Clan(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char *ClanName);
	int Banishiment(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char *ClanName, char *ClanWon);
	int Warhouse_right(char *clanName, char *right_str);
	int updateFlag(char *clanName);


	int MarkREAD(char *clanname, char *mark);

	int MarkREAD2(char *clanname, char *mark);


	int Secession(char* clanzang, char* gserver, char* SecessionID, char* clname);

	int isPFlag(char *userid, char *clName, char *chName, char *gserver, char *PFlag, char *Gubun);


	int isKPFlag(char *userid, char *clName, char *chName, char *gserver, char *PFlag, char *Gubun);



	int isCheckClanJang(char *ClanZang_ID, char *gserver);


	int isCheckClanName(char *ClanName, char *gserver);

	int ReadClanInfo(char *clanNum, CLANINFO *ci);


	int Updatcldata(char *id, char *gserver, char *chaname);

	int ReadNotice(char *userid, char *chaname, char *gserver);


	int LeaveClan(char *clanname, char *chaname, char *gserver);


	int	GetWavFile(char* FileName);

	int AppointSubChip(char* userid, char* chaname, char* clanname, char *gserver, char* clanwon);
	int ReleaseSubChip(char* userid, char* chaname, char* clanname, char *gserver, char* clanwon);




	int sod2INFOindex(char *UserId, char* CharName, char* GServer, int Index);

	int AUTH_proc_sodindex(int quenum, int threadindex);
	int AUTH_proc_sodindex_Result(int quenum, int threadindex);







	int start_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address);
	int end_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address);
};



extern int sod2INFOindex(char *UserId, char* CharName, char* GServer, int Index);
extern BOOL bip_port_error;

#undef EXTERN
#ifdef __AUTH_CPP__
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN WebDB_Thread WebDB;






void web_DB_start();
void web_DB_main();
void web_DB_end();
