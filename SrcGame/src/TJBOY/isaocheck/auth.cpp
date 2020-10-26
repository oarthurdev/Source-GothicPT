#define __AUTH_CPP__

#include <windowsx.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "..\\..\\sinbaram\\sinLinkHeader.h"

#pragma comment(lib,"ws2_32.lib")



#include "../clanmenu/tjclanDEF.h"

#ifdef USE_PROSTONTALE 

#include "..\\..\\sinbaram\\SinLinkHeader.h"
#include "..\\..\\HoBaram\\HoLinkHeader.h"
#include "Language\language.h"
#include "..\\..\\HoBaram\\HoTextFile.h"
#include "..\\clanmenu\\cE_CViewClanInfo.h"


#endif
#include "..\\clanmenu\\tjclanDEF.h"
#include "..\\clanmenu\\tjclan.h"


#include "auth.h"
#include "isaocheck.h"

extern char szConnServerName[16];

void fd(char *fmt, ...);
void fd2(char *fmt, ...);


BOOL workfound;


int AUTH_QUE_nums = 0;
CRITICAL_SECTION g_cs;

AUTH_QUE *AUTH_que;
AUTHLINKTBL aAuthLinkTbl[AUTHLINKTBL_MAX];

DWORD WINAPI AUTH_MainLoop(void* pVoid);

static BOOL AUTH_proc(int mode, int quenum, int threadindex);



int AUTH_proc_isClanMember(int quenum, int threadindex);
int AUTH_proc_isClanMember_Result(int quenum, int threadindex);


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






int AUTH_proc_sodindex(int quenum, int threadindex);
int AUTH_proc_sodindex_Result(int quenum, int threadindex);


int AUTH_proc_isCheckClanMember(int quenum, int threadindex);
int AUTH_proc_isCheckClanMember_Result(int quenum, int threadindex);


typedef int(*FUNC)(int, int);
FUNC AUTH_proc_jmptbl[][AUTH_QUE_CMD_ALLNUM] =
{
	{
		NULL,
		AUTH_proc_isClanMember,
		AUTH_proc_ClanMake,
		AUTH_proc_Mmake,
		AUTH_proc_ReadClan,
		AUTH_proc_BreakUP,
		AUTH_proc_Banishiment,
		AUTH_proc_WarhouseR,
		AUTH_proc_updateFlag,

		AUTH_proc_Secession,


		AUTH_proc_MarkREAD,
		AUTH_proc_isCheckClanJang,
		AUTH_proc_isCheckClanName,
		AUTH_proc_isPFlag,
		AUTH_proc_ReadClanInfo,
		AUTH_proc_MarkREAD2,
		AUTH_proc_Updatcldata,
		AUTH_proc_ReadNotice,
		AUTH_proc_LeaveClan,
		AUTH_proc_isKPFlag,
		AUTH_proc_AppointSubChip,
		AUTH_proc_ReleaseSubChip,
		AUTH_proc_GetWavFile,
		AUTH_proc_sodindex,
		AUTH_proc_isCheckClanMember,

	},
	{
		NULL,
		AUTH_proc_isClanMember_Result,
		AUTH_proc_ClanMake_Result,
		AUTH_proc_Mmake_Result,
		AUTH_proc_ReadClan_Result,
		AUTH_proc_BreakUP_Result,
		AUTH_proc_Banishiment_Result,
		AUTH_proc_WarhouseR_Result,
		AUTH_proc_updateFlag_Result,

		AUTH_proc_Secession_Result,

		AUTH_proc_MarkREAD_Result,
		AUTH_proc_isCheckClanJang_Result,
		AUTH_proc_isCheckClanName_Result,
		AUTH_proc_isPFlag_Result,
		AUTH_proc_ReadClanInfo_Result,
		AUTH_proc_MarkREAD2_Result,
		AUTH_proc_Updatcldata_Result,
		AUTH_proc_ReadNotice_Result,
		AUTH_proc_LeaveClan_Result,
		AUTH_proc_isKPFlag_Result,
		AUTH_proc_AppointSubChip_Result,
		AUTH_proc_ReleaseSubChip_Result,
		AUTH_proc_GetWavFile_Result,
		AUTH_proc_sodindex_Result,
		AUTH_proc_isCheckClanMember_Result,
	}
};









int AUTH_QUE_AppendTail(AUTH_QUE *pNow, int type);
AUTH_QUE* AUTH_QUE_getTop(int type);
int AUTH_QUE_Remove(AUTH_QUE *pNow);
int AUTH_QUE_Count(int type);
int AUTH_addQue(AUTH_QUE *que);



int AUTH_QUE_AppendTail(AUTH_QUE *pNow, int type)
{
	AUTH_QUE *pOldTail;

	pOldTail = aAuthLinkTbl[type].QueTail.pPrev;

	pOldTail->pNext = pNow;


	aAuthLinkTbl[type].QueTail.pPrev = pNow;


	pNow->pPrev = pOldTail;

	pNow->pNext = &aAuthLinkTbl[type].QueTail;

	return TRUE;
}



AUTH_QUE* AUTH_QUE_getTop(int type)
{




	if(aAuthLinkTbl[type].QueTop.pNext == &aAuthLinkTbl[type].QueTail)
	{
		return NULL;
	}


	return aAuthLinkTbl[type].QueTop.pNext;
}


int AUTH_QUE_Remove(AUTH_QUE *pNow)
{
	AUTH_QUE *pOldNext, *pOldPrev;


	pOldNext = pNow->pNext;
	pOldPrev = pNow->pPrev;

	pNow->pNext = NULL;
	pNow->pPrev = NULL;

	pOldNext->pPrev = pOldPrev;
	pOldPrev->pNext = pOldNext;

	return TRUE;
}


int AUTH_QUE_Count(int type)
{
	int iCount = 0;
	AUTH_QUE *pNow;

	pNow = aAuthLinkTbl[type].QueTop.pNext;

	for(; pNow->pNext; pNow = pNow->pNext)
	{
		iCount++;
	}

	return iCount;
}











int AUTH_addQue(AUTH_QUE *que)
{
	AUTH_QUE *pNew;
	EnterCriticalSection(&g_cs);



	pNew = AUTH_QUE_getTop(AUTHLINKTBL_FREE);
	if(pNew == NULL)
	{

		LeaveCriticalSection(&g_cs);

		return -1;
	}


	pNew->command = que->command;
	pNew->fdid = que->fdid;
	pNew->result = AUTH_ERROR_OTHER;


	pNew->query_time = 10;
	strcpy_s(pNew->cdkey, sizeof(pNew->cdkey), que->cdkey);
	strcpy_s(pNew->isaokey, sizeof(pNew->isaokey), que->isaokey);
	strcpy_s(pNew->password, sizeof(pNew->password), que->password);


	strcpy_s(pNew->ip_address, sizeof(pNew->ip_address), que->ip_address);
	strcpy_s(pNew->id, sizeof(pNew->id), que->id);
	strcpy_s(pNew->expl, sizeof(pNew->expl), que->expl);
	strcpy_s(pNew->clanName, sizeof(pNew->clanName), que->clanName);
	strcpy_s(pNew->charId, sizeof(pNew->charId), que->charId);

	strcpy_s(pNew->ClanZang_ID, sizeof(pNew->ClanZang_ID), que->ClanZang_ID);
	strcpy_s(pNew->ClanZang_ChaName, sizeof(pNew->ClanZang_ChaName), que->ClanZang_ChaName);
	strcpy_s(pNew->gserver, sizeof(pNew->gserver), que->gserver);
	strcpy_s(pNew->ClanWon_ID, sizeof(pNew->ClanWon_ID), que->ClanWon_ID);
	strcpy_s(pNew->ClanWon_ChaName, sizeof(pNew->ClanWon_ChaName), que->ClanWon_ChaName);
	strcpy_s(pNew->Mark, sizeof(pNew->Mark), que->Mark);
	strcpy_s(pNew->Gubun, sizeof(pNew->Gubun), que->Gubun);
	strcpy_s(pNew->PFlag, sizeof(pNew->PFlag), que->PFlag);

	pNew->howmanyTime = que->howmanyTime;
	pNew->nNum = que->nNum;
	pNew->ci = que->ci;
	pNew->job_code = que->job_code;
	pNew->level = que->level;
	pNew->joinlevel = que->joinlevel;
	pNew->joinjobcode = que->joinjobcode;

	strcpy_s(pNew->chipflag, sizeof(pNew->chipflag), que->chipflag);
	strcpy_s(pNew->szWavFileName, sizeof(pNew->szWavFileName), que->szWavFileName);






	pNew->status = AUTH_QUE_STATUS_EXIST;
	pNew->sod2index = que->sod2index;




	AUTH_QUE_Remove(pNew);

	AUTH_QUE_AppendTail(pNew, AUTHLINKTBL_START_WAIT);

	LeaveCriticalSection(&g_cs);


	return pNew->index;
}




DWORD WINAPI AUTH_MainLoop(void* pVoid)
{
	THREADstruct *thr = (THREADstruct *)pVoid;

	int cnt = 0;

	static struct timeval prev = { 0,0 };
	unsigned long thread_index = -1;
	int ret = 0;




	while(true)
	{
		Sleep(10);

		time_t myTime;
		time(&myTime);


		switch(thr->flag)
		{
			case FLAG_WAIT:
			time(&myTime);



			thr->state = FLAG_WAIT;

			SuspendThread((void *)thr->thrHandle);



			time(&myTime);
			fd2("쓰레드메인루프 FLAG_WAIT 끝. %d ", myTime);
			break;

			case FLAG_EXIT:
			goto _EXIT;

			case FLAG_EXEC:
			thr->state = FLAG_EXEC;






			workfound = FALSE;
			EnterCriticalSection(&g_cs);


			AUTH_QUE *que;
			que = AUTH_QUE_getTop(AUTHLINKTBL_START_WAIT);

			if(que != NULL)
			{
				workfound = TRUE;
				cnt = que->index;
			}
			else
			{
				workfound = FALSE;
			}


			if(!workfound)
			{
				LeaveCriticalSection(&g_cs);
				continue;
			}



			AUTH_que[cnt].status = AUTH_QUE_STATUS_BEGINAUTHPROC;

			AUTH_QUE_Remove(&AUTH_que[cnt]);
			AUTH_QUE_AppendTail(&AUTH_que[cnt], AUTHLINKTBL_WORKING);

			LeaveCriticalSection(&g_cs);




			if(!AUTH_proc(0, cnt, thread_index))
			{
				fd2("auth_proc error [que:%d command:%d]\n", cnt, AUTH_que[cnt].command);
				break;
			}


			EnterCriticalSection(&g_cs);


			AUTH_QUE_Remove(&AUTH_que[cnt]);
			AUTH_QUE_AppendTail(&AUTH_que[cnt], AUTHLINKTBL_FINISH);

			AUTH_que[cnt].status = AUTH_QUE_STATUS_ENDOFAUTHPROC;
			LeaveCriticalSection(&g_cs);


			break;
		}
	}
_EXIT:
	thr->flag = FLAG_DEAD;

	ExitThread(TRUE);
	return TRUE;




}







BOOL AUTH_proc(int mode, int quenum, int threadindex)
{

	if(mode == 0)
		mode = 0;

	if(mode == 1)
		mode = 1;

	BOOL ret = FALSE;

	if(quenum < 0 || quenum > AUTH_QUE_nums)
	{
		fd2("err: quenum \n");
		return FALSE;
	}

	if(AUTH_que[quenum].command <= AUTH_QUE_CMD_NONE || AUTH_que[quenum].command >= AUTH_QUE_CMD_ALLNUM)
	{
		fd2("err: command \n");
		return FALSE;
	}

	FUNC func = AUTH_proc_jmptbl[mode][AUTH_que[quenum].command];

	if(func)
		ret = func(quenum, threadindex);
	else
		fd2("err: no such function\n");

	if(!ret)
		fd2("err func:\n");
	return ret;

}



WebDB_Thread::WebDB_Thread()
{

}
WebDB_Thread::~WebDB_Thread()
{



	AUTH_close();

}
void WebDB_Thread::init()
{
}

void WebDB_Thread::main()
{
	AUTH_getResultLoop();
}


void WebDB_Thread::end()
{

}



int WebDB_Thread::AUTH_init(int Num)
{
	fd2("AUTH_init()함수 start");


	AUTH_QUE_nums = Num;



	AUTH_que = new AUTH_QUE[AUTH_QUE_nums];

	if(AUTH_que == NULL)
	{

		fd2("can not allocatte memory %d\n", "new memory");
		return FALSE;
	}




	for(int i = 0; i < (int)AUTH_QUE_nums; i++)
	{
		AUTH_que[i].status = AUTH_QUE_STATUS_NONE;
		AUTH_que[i].command = AUTH_QUE_CMD_NONE;
		AUTH_que[i].index = i;
		AUTH_que[i].fdid = -1;
		AUTH_que[i].cdkey[0] = '\0';
		AUTH_que[i].isaokey[0] = '\0';
		AUTH_que[i].password[0] = '\0';

		AUTH_que[i].result = AUTH_ERROR_OTHER;
	}



	InitializeCriticalSection(&g_cs);




	for(int i = 0; i < AUTHLINKTBL_MAX; i++)
	{
		aAuthLinkTbl[i].QueTop.pNext = &aAuthLinkTbl[i].QueTail;
		aAuthLinkTbl[i].QueTop.pPrev = NULL;

		aAuthLinkTbl[i].QueTail.pPrev = &aAuthLinkTbl[i].QueTop;
		aAuthLinkTbl[i].QueTail.pNext = NULL;
	}


	for(int i = 0; i < (int)AUTH_QUE_nums; i++)
		AUTH_QUE_AppendTail(&AUTH_que[i], AUTHLINKTBL_FREE);




	DWORD dwSendMsgId;
	ThreadS.thrHandle = 0;
	ThreadS.flag = 0;

	ThreadS.cnt = 0;
	DWORD thrHandle = (unsigned long)CreateThread(NULL, 0, AUTH_MainLoop, (void*)&ThreadS,
												  0, &dwSendMsgId);
	ThreadS.thrHandle = thrHandle;

	if(ThreadS.thrHandle == 0)
		return 0;


	fd2("AUTH_init()함수 end");

	return TRUE;
}


int WebDB_Thread::AUTH_close(void)
{

	TerminateThread((void*)ThreadS.thrHandle, 0);

	if(AUTH_que)
	{
		delete[] AUTH_que;
		AUTH_que = nullptr;
	}

	DeleteCriticalSection(&g_cs);

	fd2("AUTH_close()함수 ");
	return TRUE;
}



void WebDB_Thread::Suspend()
{




	fd2("중지함수 Suspend() 00 ");
	ThreadS.flag = FLAG_WAIT;

	fd2("중지함수 Suspend() 11 ");
}

void WebDB_Thread::Resume()
{
	fd2("재개함수 Resume() 들어감 ");

	if(ThreadS.flag == FLAG_EXEC)
		return;

	fd2("재개함수 Resume() while 시작 ");

	while(true)
	{
		fd2("재개함수 Resume() while 중 ");

		if(ThreadS.flag == FLAG_WAIT)
		{

			fd2("재개함수 Resume() while 중 break; ");


			break;
		}
	}

	ThreadS.flag = FLAG_EXEC;
	ResumeThread((void *)ThreadS.thrHandle);

	fd2("재개함수 Resume() 끝");
}





int WebDB_Thread::AUTH_getResultLoop(void)
{
	static int cnt = -1;

	EnterCriticalSection(&g_cs);

	for(int i = 0; i < AUTH_QUE_nums; i++)
	{
		AUTH_QUE *que = AUTH_QUE_getTop(AUTHLINKTBL_FINISH);
		if(que != NULL)
		{
			cnt = que->index;

			AUTH_QUE_Remove(que);

			if(!AUTH_proc(1, cnt, -1))
			{

			}
			AUTH_que[cnt].status = AUTH_QUE_STATUS_NONE;

			AUTH_QUE_AppendTail(&AUTH_que[cnt], AUTHLINKTBL_FREE);
		}
		else
		{
			break;
		}
	}
	LeaveCriticalSection(&g_cs);
	return TRUE;
}



int WebDB_Thread::ReadNotice(char *userid, char *chaname, char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AuthQueTmp));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReadNotice;


	strncpy(AuthQueTmp.ClanZang_ID, userid, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.ClanZang_ChaName, chaname, sizeof(AuthQueTmp.ClanZang_ChaName));



	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_ReadNotice(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadNotice(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadNotice(int quenum, int threadindex)
{
	char *chaname, *gserver, *userid;
	int knret = 1, iBadMsg = 0;

	userid = AUTH_que[quenum].ClanZang_ID;
	chaname = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;


	fd2("AUTH_proc_ReadClanInfo %s ", AUTH_que[quenum].Mark);



	knret = iCheck.ReadNotice(userid, chaname, gserver, AUTH_que[quenum].ret_Buf);



	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
int AUTH_proc_ReadNotice_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadNotice_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReadNotice_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		sprintf_s(szData, sizeof(szData), "faild");

	char szBuffer[256];


	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;








	switch(iResultCode)
	{
		case 0:
		ANSdata.ret_val = iResultCode;
		break;
		case 1:
		ANSdata.ret_val = iResultCode;
		strcpy_s(ANSdata.ret_Buf, sizeof(ANSdata.ret_Buf), AUTH_que[quenum].ret_Buf);
		break;
		case 100:
		ANSdata.ret_val = iResultCode;
		break;
		case 1004:
		ANSdata.ret_val = iResultCode;
		break;
		default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}







	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);




	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}

int AUTH_proc_ReadClanInfo(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClanInfo(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReadClanInfo(int quenum, int threadindex)
{
	char *szMarkNum;
	CLANINFO* claninfo;

	int knret = 1, iBadMsg = 0;
	char* clnaName;


	szMarkNum = AUTH_que[quenum].Mark;
	claninfo = AUTH_que[quenum].ci;




	fd2("AUTH_proc_ReadClanInfo %s ", AUTH_que[quenum].Mark);



	knret = iCheck.ReadClanInfo(szMarkNum, AUTH_que[quenum].ret_Buf);
	if(knret == 1)
	{
		char* clanINFO_result(char *marknum, char *szInfo, CLANINFO* ci);
		clnaName = clanINFO_result(AUTH_que[quenum].Mark, AUTH_que[quenum].ret_Buf, claninfo);
		knret = iCheck.read_ClanImage2(clnaName, AUTH_que[quenum].Mark, claninfo);
		if(knret == 1)
		{
			claninfo->nStatus = 2;
		}
		else
		{
			claninfo->nStatus = 3;
		}



	}
	else
	{
		claninfo->nStatus = 3;
	}


	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
int AUTH_proc_ReadClanInfo_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClanInfo_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadClanInfo_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	char szBuffer[256];


	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	}
	else
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	int clanINFO_result2(int ret_code, char *marknum, CLANINFO *ci);



	clanINFO_result2(iResultCode, AUTH_que[quenum].Mark, AUTH_que[quenum].ci);






	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


int WebDB_Thread::ReadClanInfo(char *clanNum, CLANINFO *ci)
{

	static int cnt = 0;
	fd2("ReadClanInfo: 클랜마크번호 %s (cnt %d )", clanNum, cnt);
	cnt++;


	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReadClanInfo;


	strncpy(AuthQueTmp.Mark, clanNum, sizeof(AuthQueTmp.Mark));

	AuthQueTmp.ci = ci;

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}




int WebDB_Thread::isCheckClanMember(char *pszServerName, char *pszUserName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isCheckClanMember;


	strncpy(AuthQueTmp.ClanZang_ChaName, pszUserName, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.gserver, pszServerName, sizeof(AuthQueTmp.gserver));


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{
		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;

}

int AUTH_proc_isCheckClanMember_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanMember_Result(quenum, threadindex);
}

int AUTH_proc_isCheckClanMember(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanMember(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanMember(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver;
	int knret = 1, iBadMsg = 0;


	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;

	knret = iCheck.isCheckClanMember(gserver, ClanZang_ChaName);



	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;

	return TRUE;
}

int WebDB_Thread::AUTH_proc_isCheckClanMember_Result(int quenum, int threadindex)
{
	int iResultCode;
	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 0:
		ANSdata.ret_val = iResultCode;
		break;
		case 1:
		ANSdata.ret_val = iResultCode;
		break;

		default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}
	return TRUE;
}



int AUTH_proc_isClanMember(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isClanMember(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isClanMember(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver;
	int knret = 1, iBadMsg = 0;


	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;


	knret = iCheck.isClanMember(ClanZang_ID, gserver, ClanZang_ChaName, AUTH_que[quenum].ret_Buf);



	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_isClanMember_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isClanMember_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isClanMember_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	char szBuffer[256];


	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	}
	else
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 0:
		ANSdata.ret_val = iResultCode;
		strcpy_s(ANSdata.ret_Buf, sizeof(ANSdata.ret_Buf), AUTH_que[quenum].ret_Buf);
		break;
		case 1:
		ANSdata.ret_val = iResultCode;
		strcpy_s(ANSdata.ret_Buf, sizeof(ANSdata.ret_Buf), AUTH_que[quenum].ret_Buf);
		break;
		case 5:
		case 4:
		case 3:
		case 2:
		ANSdata.ret_val = iResultCode;
		strcpy_s(ANSdata.ret_Buf, sizeof(ANSdata.ret_Buf), AUTH_que[quenum].ret_Buf);
		break;
		case 100:
		ANSdata.ret_val = iResultCode;
		break;
		case 1004:
		ANSdata.ret_val = iResultCode;
		break;
		default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}







	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);




	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}

int AUTH_proc_isPFlag(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isPFlag(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isPFlag(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver, *PFlag, *Gubun, *ClanName;
	int knret = 1, iBadMsg = 0;


	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	PFlag = AUTH_que[quenum].PFlag;
	Gubun = AUTH_que[quenum].Gubun;
	ClanName = AUTH_que[quenum].clanName;


	knret = iCheck.isPFlag(ClanZang_ID, ClanName, ClanZang_ChaName, gserver, PFlag, Gubun);



	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_isPFlag_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isPFlag_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isPFlag_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		sprintf_s(szData, sizeof(szData), "faild");

	char szBuffer[256];


	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 0:
		ANSdata.ret_val = iResultCode;
		break;
		case 1:
		ANSdata.ret_val = iResultCode;
		break;
		case 100:
		ANSdata.ret_val = iResultCode;
		break;
		case 1004:
		ANSdata.ret_val = iResultCode;
		break;
		default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}







	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);




	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}

int WebDB_Thread::isPFlag(char *userid, char *clName, char *chName, char *gserver, char *PFlag, char *Gubun)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isPFlag;

	strncpy(AuthQueTmp.Gubun, Gubun, sizeof(AuthQueTmp.Gubun));
	strncpy(AuthQueTmp.ClanZang_ID, userid, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.clanName, clName, sizeof(AuthQueTmp.clanName));
	strncpy(AuthQueTmp.ClanZang_ChaName, chName, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.PFlag, PFlag, sizeof(AuthQueTmp.PFlag));




	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}


int WebDB_Thread::isCheckClanJang(char *ClanZang_ID, char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isCheckClanJang;

	strncpy(AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_isCheckClanJang(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanJang(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanJang(int quenum, int threadindex)
{
	char* ClanZang_ID, *gserver;
	int knret = 1, iBadMsg = 0;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	gserver = AUTH_que[quenum].gserver;


	knret = iCheck.isCheckClanJang(ClanZang_ID, gserver);












	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_isCheckClanJang_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanJang_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanJang_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	char szBuffer[256];



	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	}
	else
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1:
		iResultCode = AUTH_que[quenum].result;
		break;

		case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1004:
		iResultCode = ANSdata.ret_val;
		break;
		case 101:
		case 102:
		case 103:
		break;



		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}






	ANSdata.ret_val = iResultCode;
	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);





	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


int WebDB_Thread::isCheckClanName(char *ClanName, char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isCheckClanName;

	strncpy(AuthQueTmp.clanName, ClanName, sizeof(AuthQueTmp.clanName));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_isCheckClanName(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanName(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanName(int quenum, int threadindex)
{
	char* ClanName, *gserver;
	int knret = 1, iBadMsg = 0;

	ClanName = AUTH_que[quenum].clanName;
	gserver = AUTH_que[quenum].gserver;


	knret = iCheck.isCheckClanName(ClanName, gserver);












	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_isCheckClanName_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanName_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanName_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	char szBuffer[256];



	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	}
	else
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1:
		iResultCode = AUTH_que[quenum].result;
		break;

		case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1004:
		iResultCode = ANSdata.ret_val;
		break;
		case 101:
		case 102:
		case 103:
		break;



		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}






	ANSdata.ret_val = iResultCode;
	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);





	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


int AUTH_proc_ClanMake(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ClanMake(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ClanMake(int quenum, int threadindex)
{

	char* ClanZang_ID, *ClanZang_ChaName, *gserver, *ClanName, *expl;
	int knret = 1, iBadMsg = 0;
	DWORD chtype;
	int level;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	ClanName = AUTH_que[quenum].clanName;
	expl = AUTH_que[quenum].expl;
	gserver = AUTH_que[quenum].gserver;
	chtype = AUTH_que[quenum].job_code;
	level = AUTH_que[quenum].level;


	knret = iCheck.makeClan(ClanZang_ID, gserver, ClanZang_ChaName, ClanName, expl, chtype, level, AUTH_que[quenum].ret_Buf);












	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_ClanMake_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ClanMake_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ClanMake_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	char szBuffer[256];



	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	}
	else
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1:
		iResultCode = AUTH_que[quenum].result;
		strcpy_s(ANSdata.ret_Buf, sizeof(ANSdata.ret_Buf), AUTH_que[quenum].ret_Buf);
		break;
		case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 3:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1004:
		iResultCode = ANSdata.ret_val;
		break;
		case 101:
		case 102:
		case 103:
		break;



		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}






	ANSdata.ret_val = iResultCode;
	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);





	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}



int AUTH_proc_Mmake(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Mmake(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Mmake(int quenum, int threadindex)
{
	char *clanName, *memId, *memCharId;
	char *ClanZang_ID, *ClanZang_ChaName, *gserver, *ClanWon_ID, *ClanWon_ChaName, *chipflag;
	int knret = 1, iBadMsg = 0;
	int level = 0;
	int joinlevel;
	DWORD job_code;


	clanName = AUTH_que[quenum].clanName;
	memId = AUTH_que[quenum].id;
	memCharId = AUTH_que[quenum].charId;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	ClanWon_ID = AUTH_que[quenum].ClanWon_ID;
	ClanWon_ChaName = AUTH_que[quenum].ClanWon_ChaName;
	level = AUTH_que[quenum].level;
	job_code = AUTH_que[quenum].joinjobcode;
	joinlevel = AUTH_que[quenum].joinlevel;
	chipflag = AUTH_que[quenum].chipflag;





	knret = iCheck.joinClanMember(ClanZang_ID, gserver, ClanZang_ChaName, clanName, ClanWon_ChaName, ClanWon_ID, level, job_code, joinlevel, chipflag);


	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;

	return TRUE;
}


int AUTH_proc_Mmake_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Mmake_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Mmake_Result(int quenum, int threadindex)
{
	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch(iResultCode)
	{
		case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 3:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 4:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 101:
		case 102:
		case 103:
		break;



		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}

	ANSdata.ret_val = iResultCode;
	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);


	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return 1;
}



int AUTH_proc_ReadClan(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClan(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadClan(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver;
	int knret = 1, iBadMsg = 0;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;


	knret = iCheck.read_ClanData(ClanZang_ID, gserver, ClanZang_ChaName, AUTH_que[quenum].ret_Buf);



	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_ReadClan_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClan_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadClan_Result(int quenum, int threadindex)
{
	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch(iResultCode)
	{

		case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1:
		iResultCode = AUTH_que[quenum].result;
		strcpy_s(ANSdata.ret_Buf, sizeof(ANSdata.ret_Buf), AUTH_que[quenum].ret_Buf);
		break;
		case 100:
		ANSdata.ret_val = iResultCode;
		break;
		case 1004:
		ANSdata.ret_val = iResultCode;
		break;
		case 101:
		case 102:
		strcpy_s(ANSdata.ret_Buf, sizeof(ANSdata.ret_Buf), AUTH_que[quenum].ret_Buf);
		break;




		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}






	ANSdata.ret_val = iResultCode;
	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);




	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


int AUTH_proc_BreakUP(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_BreakUP(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_BreakUP(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver, *ClanName;
	int knret = 1, iBadMsg = 0;

	ClanName = AUTH_que[quenum].clanName;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;


	knret = iCheck.BreakUPClan(ClanZang_ID, gserver, ClanZang_ChaName, ClanName);


	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_BreakUP_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_BreakUP_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_BreakUP_Result(int quenum, int threadindex)
{
	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch(iResultCode)
	{



		case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 2:
		iResultCode = AUTH_que[quenum].result;
		break;

		case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 101:
		case 102:
		case 103:
		case 104:
		break;


		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}







	ANSdata.ret_val = iResultCode;
	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);




	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


int AUTH_proc_Secession(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Secession(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Secession(int quenum, int threadindex)
{
	char *clanName, *secession_id, *gserver, *clanzang;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;


	clanzang = AUTH_que[quenum].ClanWon_ChaName;
	gserver = AUTH_que[quenum].gserver;
	secession_id = AUTH_que[quenum].ClanWon_ID;





	knret = iCheck.Secession(secession_id, gserver, clanzang, clanName);



	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_Secession_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Secession_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Secession_Result(int quenum, int threadindex)
{
	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch(iResultCode)
	{

		case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 3:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
		case ISAO_ERR_TCP_CONNECT:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 101:
		break;



		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}






	ANSdata.ret_val = iResultCode;
	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);



	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


int AUTH_proc_Banishiment(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Banishiment(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Banishiment(int quenum, int threadindex)
{
	char *clanName, *ClanWon, *gserver, *ClanZang_ID, *ClanZang_ChaName;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	ClanWon = AUTH_que[quenum].ClanWon_ChaName;



	knret = iCheck.Banishiment(ClanZang_ID, gserver, ClanZang_ChaName, clanName, ClanWon);


	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_Banishiment_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Banishiment_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Banishiment_Result(int quenum, int threadindex)
{
	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch(iResultCode)
	{

		case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 3:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 101:
		break;



		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}






	ANSdata.ret_val = iResultCode;
	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);



	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}



int AUTH_proc_WarhouseR(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_WarhouseR(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_WarhouseR(int quenum, int threadindex)
{
	char *clanName, *banish_id;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	banish_id = AUTH_que[quenum].expl;


	knret = iCheck.WarhouseRight(clanName, banish_id);


	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_WarhouseR_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_WarhouseR_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_WarhouseR_Result(int quenum, int threadindex)
{
	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch(iResultCode)
	{
		case 100:
		case 101:
		case 102:
		break;

		case AUTH_OK:
		break;
		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}






	ANSdata.ret_val = iResultCode;
	fd2("창고권한 답변을 받음. : ret_val %d ", ANSdata.ret_val);



	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}



int AUTH_proc_updateFlag(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_updateFlag(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_updateFlag(int quenum, int threadindex)
{
	char *clanName, *banish_id;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	banish_id = AUTH_que[quenum].expl;

	knret = iCheck.updateFlag(clanName);


	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_updateFlag_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_updateFlag_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_updateFlag_Result(int quenum, int threadindex)
{
	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch(iResultCode)
	{
		case 100:
		case 101:
		case 102:
		break;

		case AUTH_OK:
		iResultCode = AUTH_que[quenum].result;
		break;
		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}






	ANSdata.ret_val = iResultCode;
	fd2("창고권한 답변을 받음. : ret_val %d ", ANSdata.ret_val);



	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}



int AUTH_proc_MarkREAD(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD(int quenum, int threadindex)
{

	char *Mark, *clanname;
	int knret = 1, iBadMsg = 0;

	Mark = AUTH_que[quenum].Mark;
	clanname = AUTH_que[quenum].clanName;


	knret = iCheck.read_ClanImage(clanname, Mark);


	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_MarkREAD_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD_Result(int quenum, int threadindex)
{
	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;




	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 1:

		iResultCode = AUTH_que[quenum].result;
		break;
		case 2:
		iResultCode = AUTH_que[quenum].result;
		break;

		case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 101:
		case 102:
		break;
		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;






		break;
	}






	ANSdata.ret_val = iResultCode;
	fd2("창고권한 답변을 받음. : ret_val %d ", ANSdata.ret_val);



	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}

int AUTH_proc_MarkREAD2(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD2(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD2(int quenum, int threadindex)
{

	char *Mark, *clanname;
	int knret = 1, iBadMsg = 0;

	Mark = AUTH_que[quenum].Mark;
	clanname = AUTH_que[quenum].clanName;









	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_MarkREAD2_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD2_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD2_Result(int quenum, int threadindex)
{
	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch(iResultCode)
	{
		case 1:

		iResultCode = AUTH_que[quenum].result;
		break;
		case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 101:
		case 102:
		break;
		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;







	}






	ANSdata.ret_val = iResultCode;
	fd2("창고권한 답변을 받음. : ret_val %d ", ANSdata.ret_val);



	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}



int AUTH_proc_Updatcldata(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Updatcldata(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_Updatcldata(int quenum, int threadindex)
{
	char *id, *chaname, *gserver;
	int knret = 1, iBadMsg = 0;


	id = AUTH_que[quenum].ClanZang_ID;
	chaname = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;


	knret = iCheck.isClanMember(id, gserver, chaname, AUTH_que[quenum].ret_Buf);
	if((knret == 0) || (knret == 2) || (knret == 1) || (knret == 3) || (knret == 4) || (knret == 5))
	{
		void ParsingIsClanMember(char* data, int myposition);
		ParsingIsClanMember(AUTH_que[quenum].ret_Buf, knret);
		if((knret == 2) || (knret == 1) || (knret == 5))
		{
			knret = iCheck.read_ClanData(id, gserver, chaname, AUTH_que[quenum].ret_Buf);
			if(knret == 1)
			{
				void ParsigClanWon(char* data);
				ParsigClanWon(AUTH_que[quenum].ret_Buf);
				knret = iCheck.read_ClanImage(chaname, cldata.ClanMark);
			}
		}
	}



	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;

	return 1;
}

int AUTH_proc_Updatcldata_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Updatcldata_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_Updatcldata_Result(int quenum, int threadindex)
{
	char szData[128];
	char GServer;
	char szNum[64];
	char szFile[256];
	char szFile2[256];
	ZeroMemory(szNum, sizeof(szNum));
	ZeroMemory(szFile, sizeof(szFile));
	ZeroMemory(szFile2, sizeof(szFile2));

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch(iResultCode)
	{

		case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
		case 1:
		iResultCode = AUTH_que[quenum].result;
		GServer = cldata.ClanMark[0];
		strcpy(szNum, &cldata.ClanMark[3]);
		wsprintf(szFile, "%s\\%s\\%c_%s.%s", SAVE_DIR, szConnServerName, GServer, szNum, SAVE_EXE);
		wsprintf(szFile2, "%s\\%s\\%c_%s_16.%s", SAVE_DIR, szConnServerName, GServer, szNum, SAVE_EXE);
	#ifdef USE_PROSTONTALE 
		if(cldata.hClanMark16)
		{
			cldata.hClanMark16->Release();
			cldata.hClanMark16 = NULL;
		}

		if(cldata.hClanMark)
		{
			cldata.hClanMark->Release();
			cldata.hClanMark = NULL;
		}

		cldata.hClanMark16 = LoadDibSurfaceOffscreen(szFile2);
		cldata.hClanMark = LoadDibSurfaceOffscreen(szFile);
	#endif

		break;
		case 100:
		ANSdata.ret_val = iResultCode;
		break;
		case 1004:
		ANSdata.ret_val = iResultCode;
		break;
		case 101:
		case 102:
		break;




		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}









	ANSdata.ret_val = iResultCode;
	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);




	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}



	void g_UpdateCldata_Close();
	g_UpdateCldata_Close();

	return TRUE;
}

int WebDB_Thread::Updatcldata(char *id, char *gserver, char *chaname)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));


	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_Updatcldata;



	strncpy(AuthQueTmp.ClanZang_ID, id, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.ClanZang_ChaName, chaname, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));




	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}


int WebDB_Thread::isClanMember(char *ClanZang_id, char* gserver, char* ClanZang_ChaName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isClanMember;



	strncpy(AuthQueTmp.ClanZang_ID, ClanZang_id, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}


int WebDB_Thread::joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char* ClanName, char* ClanWon, char* ClanWon_ID, int level, DWORD chtype, int joinlevel, char *chipflag)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AuthQueTmp));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_CL_MEMBER_MAKE;


	strncpy(AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.clanName, ClanName, sizeof(AuthQueTmp.clanName));
	strncpy(AuthQueTmp.ClanWon_ChaName, ClanWon, sizeof(AuthQueTmp.ClanWon_ChaName));
	strncpy(AuthQueTmp.ClanWon_ID, ClanWon_ID, sizeof(AuthQueTmp.ClanWon_ID));
	strncpy(AuthQueTmp.chipflag, chipflag, sizeof(AuthQueTmp.chipflag));

	AuthQueTmp.level = level;
	AuthQueTmp.joinlevel = joinlevel;
	AuthQueTmp.joinjobcode = (int)chtype;




	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}


int WebDB_Thread::make_Clan(char *ClanZang_ID, char* gserver, char* ClanZang_ChaName, char* ClanName, char *explanation, DWORD chtype, int level)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_CL_MAKE;

	strncpy(AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.expl, explanation, sizeof(AuthQueTmp.expl));
	strncpy(AuthQueTmp.clanName, ClanName, sizeof(AuthQueTmp.clanName));
	strncpy(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));

	AuthQueTmp.level = level;
	AuthQueTmp.job_code = chtype;

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}


int WebDB_Thread::ReadClan(char *ClanZang_ID, char* gserver, char* ClanZang_ChaName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReadClan;


	strncpy(AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof(AuthQueTmp.ClanZang_ChaName));


	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}

int WebDB_Thread::BreakUP_Clan(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char *ClanName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_BreakUP;


	strncpy(AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.clanName, ClanName, sizeof(AuthQueTmp.clanName));

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("BreakUP_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}




int WebDB_Thread::Banishiment(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char *ClanName, char *ClanWon)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_Banishiment;


	strncpy(AuthQueTmp.clanName, ClanName, sizeof(AuthQueTmp.clanName));
	strncpy(AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.ClanWon_ChaName, ClanWon, sizeof(AuthQueTmp.ClanWon_ChaName));


	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("BreakUP_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}






int WebDB_Thread::Secession(char* clanzang, char* gserver, char* SecessionID, char* claname)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_Secession;

	strncpy(AuthQueTmp.clanName, claname, sizeof(AuthQueTmp.clanName));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.ClanWon_ChaName, SecessionID, sizeof(AuthQueTmp.ClanWon_ChaName));
	strncpy(AuthQueTmp.ClanWon_ID, clanzang, sizeof(AuthQueTmp.ClanZang_ID));




	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("BreakUP_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}





int WebDB_Thread::Warhouse_right(char *clanName, char *right_str)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_WarhouseR;


	strncpy(AuthQueTmp.clanName, clanName, sizeof(AuthQueTmp.clanName));
	strncpy(AuthQueTmp.expl, right_str, strlen(right_str));

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("Warhouse_right() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}



int AUTH_proc_LeaveClan(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_LeaveClan(quenum, threadindex);
}
int AUTH_proc_LeaveClan_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_LeaveClan_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_LeaveClan(int quenum, int threadindex)
{

	char *clanname, *chaname, *gserver;
	int knret = 1, iBadMsg = 0;

	chaname = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	clanname = AUTH_que[quenum].clanName;

	knret = iCheck.LeaveClan(clanname, chaname, gserver);


	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return 1;
}
int WebDB_Thread::AUTH_proc_LeaveClan_Result(int quenum, int threadindex)
{
	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch(iResultCode)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 100:
		break;
		case 1004:
		break;
		default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}






	ANSdata.ret_val = iResultCode;
	fd2("창고권한 답변을 받음. : ret_val %d ", ANSdata.ret_val);



	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;

}
int WebDB_Thread::LeaveClan(char *clanname, char *chaname, char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AuthQueTmp));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_LeaveClan;


	strncpy(AuthQueTmp.clanName, clanname, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.ClanZang_ChaName, chaname, sizeof(AuthQueTmp.ClanZang_ChaName));



	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}



int WebDB_Thread::updateFlag(char *clanName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_updateFlag;

	strncpy(AuthQueTmp.clanName, clanName, sizeof(AuthQueTmp.clanName));

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("Warhouse_right() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}




int WebDB_Thread::MarkREAD(char *clanname, char *mark)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_MarkREAD;

	strncpy(AuthQueTmp.Mark, mark, sizeof(AuthQueTmp.Mark));
	strncpy(AuthQueTmp.clanName, clanname, sizeof(AuthQueTmp.clanName));

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("Warhouse_right() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}


int WebDB_Thread::MarkREAD2(char *clanname, char *mark)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_MarkREAD2;

	strncpy(AuthQueTmp.Mark, mark, sizeof(AuthQueTmp.Mark));
	strncpy(AuthQueTmp.clanName, clanname, sizeof(AuthQueTmp.clanName));

	DWORD myTime;
	time((time_t*)&myTime);
	AuthQueTmp.howmanyTime = (DWORD)myTime;


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("Warhouse_right() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}





extern BOOL bCheckHostNameandPort;
void WebDB_Thread::CheckHostNamePort(char *hostname, int port)
{
	if(hostname == NULL)
	{
		bCheckHostNameandPort = FALSE;
		return;
	}
	if(port == 0)
	{
		bCheckHostNameandPort = FALSE;
		return;
	}

	bCheckHostNameandPort = TRUE;
}
















int WebDB_Thread::start_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address)
{
	return 0;

	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));



	AuthQueTmp.fdid = 100;



	AuthQueTmp.command = AUTH_QUE_CMD_CL_MAKE;

	strncpy(AuthQueTmp.cdkey, cdkey, sizeof(AuthQueTmp.cdkey));
	strncpy(AuthQueTmp.isaokey, accountid, sizeof(AuthQueTmp.isaokey));
	strncpy(AuthQueTmp.password, passwd, sizeof(AuthQueTmp.password));
	strncpy(AuthQueTmp.ip_address, ip_address, sizeof(AuthQueTmp.ip_address));

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("끝내기 과금 에러 큐에 등록안됨. %s \n", accountid);
		return 0;
	}
	return 1;
}


int WebDB_Thread::end_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address)
{

	AUTH_QUE AuthQueTmp;




	AuthQueTmp.fdid = 100;


	AuthQueTmp.command = AUTH_QUE_CMD_CL_MEMBER_MAKE;

	strncpy(AuthQueTmp.cdkey, cdkey, sizeof(AuthQueTmp.cdkey));
	strncpy(AuthQueTmp.isaokey, accountid, sizeof(AuthQueTmp.isaokey));
	strncpy(AuthQueTmp.password, passwd, sizeof(AuthQueTmp.password));
	strncpy(AuthQueTmp.ip_address, ip_address, sizeof(AuthQueTmp.ip_address));
	AuthQueTmp.howmanyTime = 100;


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{







		fd2("끝내기 과금 에러 큐에 등록안됨. %s \n", accountid);
		return 0;
	}
	return 1;
}


char web_DBip0[64] = { 0, };
int web_DBport0 = 0;
char web_DBip1[64] = { 0, };
int web_DBport1 = 0;
int nClanTicket = 0;



void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1)
{
	strcpy(web_DBip0, ip0);
	strcpy(web_DBip1, ip1);

	web_DBport0 = port0;
	web_DBport1 = port1;

}

void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1, int ticket)
{
	strcpy(web_DBip0, ip0);
	strcpy(web_DBip1, ip1);

	web_DBport0 = port0;
	web_DBport1 = port1;
#ifdef __CLANSERVER__
	nClanTicket = 9999;
#else
	nClanTicket = ticket;
#endif
}


void web_DB_start(char *hostN0, int port0, char *hostN1, int port1);
void web_DB_start()
{





	char hostN0[] = "211.39.144.157";
	char hostN1[] = "211.39.144.158";






	int port0 = 80;
	int port1 = 80;






	web_DB_start(web_DBip0, web_DBport0, web_DBip1, web_DBport1);






}


BOOL bip_port_error = FALSE;


void web_DB_start(char *hostN0, int port0, char *hostN1, int port1)
{
	if((hostN0 == NULL) || (port0 == 0) || (hostN1 == NULL) || (port1 == 0))
	{
		bip_port_error = TRUE;



		WebDB.AUTH_init(10);
		WebDB.ThreadS.flag = FLAG_WAIT;
		WebDB.Suspend();

		while(1)
		{
			if(WebDB.ThreadS.flag == FLAG_WAIT)
				break;
		}

		return;
	}
	static int cnt = 0;

	if(cnt == 1)
		return;

	cnt = 1;










	iCheck.init(1, 5);


	WebDB.CheckHostNamePort(hostN0, port0);

	iCheck.init_HostName_Port(hostN0, port0);
	iCheck.init_HostName_Port1(hostN1, port1);





	WebDB.AUTH_init(10);
	WebDB.ThreadS.flag = FLAG_WAIT;
	WebDB.Suspend();

	while(1)
	{
		if(WebDB.ThreadS.flag == FLAG_WAIT)
			break;
	}
}


int web_DB_state_FLAG_WAIT()
{
	if(WebDB.ThreadS.flag == FLAG_WAIT)
		return 1;

	return 0;
}


void web_DB_main()
{
	WebDB.main();
}

void web_DB_end()
{
	WebDB.end();
}








int AUTH_proc_isKPFlag(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isKPFlag(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isKPFlag(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver, *PFlag, *Gubun, *ClanName;
	int knret = 1, iBadMsg = 0;


	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	PFlag = AUTH_que[quenum].PFlag;
	Gubun = AUTH_que[quenum].Gubun;
	ClanName = AUTH_que[quenum].clanName;


	knret = iCheck.isKPFlag(ClanZang_ID, ClanName, ClanZang_ChaName, gserver, PFlag, Gubun);



	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_isKPFlag_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isKPFlag_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isKPFlag_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	char szBuffer[256];


	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	}
	else
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 0:
		ANSdata.ret_val = iResultCode;
		break;
		case 1:
		ANSdata.ret_val = iResultCode;
		break;
		case 100:
		ANSdata.ret_val = iResultCode;
		break;
		case 1004:
		ANSdata.ret_val = iResultCode;
		break;
		default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}







	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);




	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}

int WebDB_Thread::isKPFlag(char *userid, char *clName, char *chName, char *gserver, char *PFlag, char *Gubun)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isKPFlag;

	strncpy(AuthQueTmp.Gubun, Gubun, sizeof(AuthQueTmp.Gubun));
	strncpy(AuthQueTmp.ClanZang_ID, userid, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.clanName, clName, sizeof(AuthQueTmp.clanName));
	strncpy(AuthQueTmp.ClanZang_ChaName, chName, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.PFlag, PFlag, sizeof(AuthQueTmp.PFlag));

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}

int WebDB_Thread::AppointSubChip(char* userid, char* chaname, char* clanname, char *gserver, char* clanwon)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_AppointSubChip;

	strncpy(AuthQueTmp.ClanZang_ID, userid, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.clanName, clanname, sizeof(AuthQueTmp.clanName));
	strncpy(AuthQueTmp.ClanZang_ChaName, chaname, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.ClanWon_ChaName, clanwon, sizeof(AuthQueTmp.ClanWon_ChaName));;

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}



int AUTH_proc_AppointSubChip(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_AppointSubChip(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_AppointSubChip(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver, *ClanName;
	int knret = 1, iBadMsg = 0;

	char *clanwon;


	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	clanwon = AUTH_que[quenum].ClanWon_ChaName;
	ClanName = AUTH_que[quenum].clanName;



	knret = iCheck.AppointSubChip(gserver, clanwon);










	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_AppointSubChip_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_AppointSubChip_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_AppointSubChip_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	char szBuffer[256];


	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	}
	else
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 0:
		ANSdata.ret_val = iResultCode;
		break;
		case 3:
		ANSdata.ret_val = iResultCode;
		break;
		case 2:
		ANSdata.ret_val = iResultCode;
		break;
		case 1:
		ANSdata.ret_val = iResultCode;
		break;

		case 100:
		ANSdata.ret_val = iResultCode;
		break;
		case 1004:
		ANSdata.ret_val = iResultCode;
		break;
		default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}







	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);




	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


int WebDB_Thread::ReleaseSubChip(char* userid, char* chaname, char* clanname, char *gserver, char* clanwon)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReleaseSubChip;

	strncpy(AuthQueTmp.ClanZang_ID, userid, sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.clanName, clanname, sizeof(AuthQueTmp.clanName));
	strncpy(AuthQueTmp.ClanZang_ChaName, chaname, sizeof(AuthQueTmp.ClanZang_ChaName));
	strncpy(AuthQueTmp.gserver, gserver, sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.ClanWon_ChaName, clanwon, sizeof(AuthQueTmp.ClanWon_ChaName));;


	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}


int AUTH_proc_ReleaseSubChip(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReleaseSubChip(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReleaseSubChip(int quenum, int threadindex)
{
	int knret = 1, iBadMsg = 0;
	char *gserver;
	char *clanwon;
	char *ClanZang_ID, *ClanZang_ChaName, *ClanName;


	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	clanwon = AUTH_que[quenum].ClanWon_ChaName;
	ClanName = AUTH_que[quenum].clanName;



	knret = iCheck.ReleaseSubChip(gserver, clanwon);






	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_ReleaseSubChip_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReleaseSubChip_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReleaseSubChip_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	char szBuffer[256];


	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	}
	else
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 0:
		ANSdata.ret_val = iResultCode;
		break;
		case 1:
		ANSdata.ret_val = iResultCode;
		break;
		case 2:
		ANSdata.ret_val = iResultCode;
		break;
		case 100:
		ANSdata.ret_val = iResultCode;
		break;
		case 1004:
		ANSdata.ret_val = iResultCode;
		break;
		default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}







	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);




	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


int WebDB_Thread::GetWavFile(char* FileName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_GetWavFile;

	strncpy(AuthQueTmp.szWavFileName, FileName, sizeof(AuthQueTmp.szWavFileName));

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = static_cast<DWORD>(myTime);


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_GetWavFile(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_GetWavFile(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_GetWavFile(int quenum, int threadindex)
{
	int knret = 1, iBadMsg = 0;
	char *szFileName;

	szFileName = AUTH_que[quenum].szWavFileName;



	knret = iCheck.GetWavFile(szFileName);






	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
int AUTH_proc_GetWavFile_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_GetWavFile_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_GetWavFile_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
		"OK",
		"Err CDKEY",
		"Err ISAO_ID",
		"Err PASSWORD",
		"Err EXPIRE",
		"Err LOCOUT",
		"Err ISAO_DB",
		"Err OTHER",
		""
	};

	char szData[128];

	if(AUTH_que[quenum].result == 0)
	{
		szData[0] = '\0';
	}
	else
	{
		sprintf_s(szData, sizeof(szData), "faild");
	}

	char szBuffer[256];


	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	}
	else
	{
		sprintf_s(szBuffer, sizeof(szBuffer), "ExtraCode=%d", AUTH_que[quenum].result);
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;



	switch(iResultCode)
	{
		case 0:
		ANSdata.ret_val = iResultCode;
		break;
		case 1:
		ANSdata.ret_val = iResultCode;
		break;
		case 2:
		ANSdata.ret_val = iResultCode;
		break;
		case 100:
		ANSdata.ret_val = iResultCode;
		break;
		case 1004:
		ANSdata.ret_val = iResultCode;
		break;
		default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}







	fd2("클랜멤버여부의 답변을 받음. : ret_val %d ", ANSdata.ret_val);




	if(0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{
	}
	else
	{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}

	return TRUE;
}






int sod2INFOindex(char *UserId, char* CharName, char* GServer, int Index)
{
	WebDB.sod2INFOindex(UserId, CharName, GServer, Index);
	return TRUE;
}



int WebDB_Thread::sod2INFOindex(char *UserId, char* CharName, char* GServer, int Index)
{
	Resume();


	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_SOD2;


	strncpy(AuthQueTmp.id, UserId, sizeof(AuthQueTmp.id));
	strncpy(AuthQueTmp.charId, CharName, sizeof(AuthQueTmp.charId));
	strncpy(AuthQueTmp.gserver, GServer, sizeof(AuthQueTmp.gserver));
	AuthQueTmp.sod2index = Index;


	if(AUTH_addQue(&AuthQueTmp) < 0)
	{





		fd2("make_Clan() 에러 : 큐에 등록안됨");
		return 0;
	}
	return 1;
}



int AUTH_proc_sodindex(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_sodindex(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_sodindex(int quenum, int threadindex)
{

	int knret = 1, iBadMsg = 0;
	knret = iCheck.read_sod2(AUTH_que[quenum].id, AUTH_que[quenum].charId, AUTH_que[quenum].gserver, AUTH_que[quenum].sod2index, AUTH_que[quenum].szSod2Buff);


	AUTH_que[quenum].result = knret;

	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_sodindex_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_sodindex_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_sodindex_Result(int quenum, int threadindex)
{

	cSinSod2.RecvWebData(AUTH_que[quenum].sod2index, AUTH_que[quenum].szSod2Buff);



	return TRUE;
}
