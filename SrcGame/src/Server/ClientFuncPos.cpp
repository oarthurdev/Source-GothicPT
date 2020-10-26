#define _WIN32_WINNT    0x0403  
#define _WIN32_WINDOWS  0x0403
#include <windows.h>
#include <io.h>
#include <stdio.h>         
#include <string.h>        
#include <memory.h>
#include <process.h>       



#include "Resources\resource.h"
#include "..\\smwsock.h"



#include "..\\smlib3d\\smd3d.h"
#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "..\\field.h"
#include "..\\sinbaram\\sinlinkheader.h"
#include "..\\effectsnd.h"

#include "..\\record.h"
#include "..\playsub.h"

#include "DllServer.h"

#include "Language\\language.h"

#include "ClientFuncPos.h"

extern rsSERVER_CONFIG		rsServerConfig;

static char	*szFuncDirectory = "FuncBox";

#define	CLIENT_FUNC_POS_MAX		8

TRANS_CLIENT_FUNPOS	ClientFuncPos[CLIENT_FUNC_POS_MAX];
int	InitClientFuncPos = 0;





int	rsAddClientFuncPos(TRANS_CLIENT_FUNPOS	*lpClentFuncPos);

int	rsRecvClientFuncPos(TRANS_CLIENT_FUNPOS	*lpClentFuncPos);

TRANS_CLIENT_FUNPOS *rsGetClientPos(int Version);

int	rsResetClientFuncPos();


int rsSendDataServer(smWINSOCK *lpsmSock, void *szData);

int rsSendGameServer(smWINSOCK *lpsmSock, void *szData);



int	rsRecvClientFuncPos(TRANS_CLIENT_FUNPOS	*lpClentFuncPos)
{
	FILE *fp = nullptr;
	char szBuff[256] = { 0 };

	CreateDirectory(szFuncDirectory, NULL);

	wsprintf(szBuff, "%s\\%d.dat", szFuncDirectory, lpClentFuncPos->ClientVersion);
	fp = fopen(szBuff, "wb");

	if(fp)
	{
		fwrite(lpClentFuncPos, lpClentFuncPos->size, 1, fp);
		fclose(fp);
	}

	rsAddClientFuncPos(lpClentFuncPos);

	return TRUE;
}


int	rsAddClientFuncPos(TRANS_CLIENT_FUNPOS	*lpClentFuncPos)
{
	int cnt;

	if(!InitClientFuncPos)
	{
		ZeroMemory(ClientFuncPos, sizeof(TRANS_CLIENT_FUNPOS)*CLIENT_FUNC_POS_MAX);
	}

	InitClientFuncPos = TRUE;


	for(cnt = 0; cnt < CLIENT_FUNC_POS_MAX; cnt++)
	{
		if(ClientFuncPos[cnt].code && ClientFuncPos[cnt].ClientVersion == lpClentFuncPos->ClientVersion)
		{
			memcpy(&ClientFuncPos[cnt], lpClentFuncPos, sizeof(TRANS_CLIENT_FUNPOS));
			return TRUE;
		}
	}


	for(cnt = 0; cnt < CLIENT_FUNC_POS_MAX; cnt++)
	{
		if(!ClientFuncPos[cnt].code)
		{
			memcpy(&ClientFuncPos[cnt], lpClentFuncPos, sizeof(TRANS_CLIENT_FUNPOS));
			return TRUE;
		}
	}

	return FALSE;
}


TRANS_CLIENT_FUNPOS *rsGetClientPos(int Version)
{
	int cnt;

	for(cnt = 0; cnt < CLIENT_FUNC_POS_MAX; cnt++)
	{
		if(ClientFuncPos[cnt].code && ClientFuncPos[cnt].ClientVersion == Version)
		{
			return	&ClientFuncPos[cnt];
		}
	}

	return NULL;
}


int	rsResetClientFuncPos()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	TRANS_CLIENT_FUNPOS	TransClientFuncPos;
	char	szBuff[256];
	FILE	*fp;

	wsprintf(szBuff, "%s\\*.dat", szFuncDirectory);

	ZeroMemory(ClientFuncPos, sizeof(TRANS_CLIENT_FUNPOS)*CLIENT_FUNC_POS_MAX);

	InitClientFuncPos = TRUE;

	hFindHandle = FindFirstFile(szBuff, &fd);
	if(hFindHandle == INVALID_HANDLE_VALUE) return FALSE;

	while(1)
	{
		wsprintf(szBuff, "%s\\%s", szFuncDirectory, fd.cFileName);
		fp = fopen(szBuff, "rb");
		if(fp)
		{
			fread(&TransClientFuncPos, sizeof(TRANS_CLIENT_FUNPOS), 1, fp);
			fclose(fp);


			if(TransClientFuncPos.ClientVersion >= rsServerConfig.LimitVersion)
				rsAddClientFuncPos(&TransClientFuncPos);
		}

		if(FindNextFile(hFindHandle, &fd) == FALSE) break;
	}

	FindClose(hFindHandle);

	return TRUE;
}



int	rsSendGameServer_FuncError(rsPLAYINFO *lpPlayInfo, int WParam, int LParam)
{
	smTRANS_COMMAND	smTransCommand;

	if(!lpPlayInfo->dwFuncChkErrorFlag) return FALSE;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_FUNCERROR;
	smTransCommand.WParam = WParam;
	smTransCommand.LParam = LParam;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
		rsSendGameServer(lpPlayInfo->lpsmSock, &smTransCommand);

	return TRUE;
}






#ifdef _W_SERVER

BYTE BCode_funcCheckMemSum[] = {
  0x55, 0x8b , 0xec , 0x81 , 0xec , 0xfc , 0x00 , 0x00 , 0x00 , 0x53 , 0x56 , 0x57 , 0x8d , 0xbd , 0x04 , 0xff , 0xff,
  0xff, 0xb9 , 0x3f , 0x00 , 0x00 , 0x00 , 0xb8 , 0xcc , 0xcc , 0xcc , 0xcc , 0xf3 , 0xab , 0x8b , 0x45 , 0x08 , 0x8b,
  0x48, 0x0c , 0x89 , 0x4d , 0xc8 , 0x8b , 0x45 , 0x08 , 0x8b , 0x48 , 0x08 , 0x89 , 0x4d , 0xd4 , 0xc7 , 0x45 , 0xec,
  0x00, 0x00 , 0x00 , 0x00 , 0xc7 , 0x45 , 0xe0 , 0x01 , 0x00 , 0x00 , 0x00 , 0xc7 , 0x45 , 0xf8 , 0x00 , 0x00 , 0x00,
  0x00, 0xeb , 0x09 , 0x8b , 0x45 , 0xf8 , 0x83 , 0xc0 , 0x01 , 0x89 , 0x45 , 0xf8 , 0x8b , 0x45 , 0xf8 , 0x3b , 0x45,
  0xc8, 0x7d , 0x20 , 0x8b , 0x45 , 0xe0 , 0x03 , 0x45 , 0xf8 , 0x89 , 0x45 , 0xe0 , 0x8b , 0x45 , 0xf8 , 0x8b , 0x4d,
  0xd4, 0x8b , 0x14 , 0x81 , 0x0f , 0xaf , 0x55 , 0xe0 , 0x8b , 0x45 , 0xec , 0x03 , 0xc2 , 0x89 , 0x45 , 0xec , 0xeb,
  0xcf, 0x8b , 0x45 , 0x0c , 0xc7 , 0x40 , 0x04 , 0x30 , 0x04 , 0x32 , 0x50 , 0x8b , 0x45 , 0x0c , 0xc7 , 0x00 , 0x18,
  0x00, 0x00 , 0x00 , 0x8b , 0x45 , 0x0c , 0x8b , 0x4d , 0x08 , 0x8b , 0x51 , 0x08 , 0x89 , 0x50 , 0x0c , 0x8b , 0x45,
  0x0c, 0x8b , 0x4d , 0x08 , 0x8b , 0x51 , 0x0c , 0x89 , 0x50 , 0x08 , 0x8b , 0x45 , 0x0c , 0x8b , 0x4d , 0x08 , 0x8b,
  0x51, 0x10 , 0x89 , 0x50 , 0x10 , 0x8b , 0x45 , 0x0c , 0x8b , 0x4d , 0xec , 0x89 , 0x48 , 0x14 , 0x8b , 0x45 , 0xec,
  0x5f, 0x5e , 0x5b , 0x8b , 0xe5 , 0x5d , 0xc3 , 0,0,0,0
};

#else
BYTE BCode_funcCheckMemSum[2] = { 0,0 };
#endif


int rsSendFuncMemToClient(rsPLAYINFO *lpPlayInfo, DWORD dwFuncMem, DWORD	dwLen)
{

	TRANS_FUNC_MEMORY	TransFuncMemory;
	int val;


	ZeroMemory(&TransFuncMemory, sizeof(TRANS_FUNC_MEMORY));

	TransFuncMemory.size = 300;
	TransFuncMemory.code = OpCode::OPCODE_FUNCTION_MEM;

	TransFuncMemory.Param[0] = dwFuncMem;
	TransFuncMemory.Param[1] = dwLen;

	memcpy(TransFuncMemory.szData, BCode_funcCheckMemSum, 300);

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		val = lpPlayInfo->lpsmSock->Send((char *)&TransFuncMemory, TransFuncMemory.size, TRUE);
	}

	if(val)
	{
		if(lpPlayInfo->dwClientFuncChk_1)
		{
			lpPlayInfo->FuncChkFailCount1++;
			lpPlayInfo->dwClientFuncChk_1 = 0;
		}

		lpPlayInfo->ClientFunChk1_Count++;
		lpPlayInfo->dwClientFuncChk_1 = dwFuncMem;
		return TRUE;
	}

	return FALSE;
}



int rsSendFuncMemToClient2(rsPLAYINFO *lpPlayInfo)
{

	TRANS_FUNC_MEMORY	TransFuncMemory;
	TRANS_CLIENT_FUNPOS *lpTransClientFuncPos;
	int	cnt;
	int val;


	lpTransClientFuncPos = rsGetClientPos(lpPlayInfo->Client_Version);

	if(!lpTransClientFuncPos) return FALSE;

	cnt = lpTransClientFuncPos->FuncCount - 1;
	if(cnt <= 0) return FALSE;

	ZeroMemory(&TransFuncMemory, sizeof(TRANS_FUNC_MEMORY));

	TransFuncMemory.size = 300 + (rand() % 80);
	TransFuncMemory.code = OpCode::OPCODE_FUNCTION_MEM2;

	TransFuncMemory.Param[0] = lpTransClientFuncPos->dwFuncValue[cnt].dwFunc;
	TransFuncMemory.Param[1] = lpTransClientFuncPos->dwFuncValue[cnt].dwLen;

	memcpy(TransFuncMemory.szData, BCode_funcCheckMemSum, 300);

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		val = lpPlayInfo->lpsmSock->Send((char *)&TransFuncMemory, TransFuncMemory.size, TRUE);
	}

	if(val)
	{
		if(lpPlayInfo->dwClientFuncChk_1)
		{
			lpPlayInfo->FuncChkFailCount1++;
			lpPlayInfo->dwClientFuncChk_1 = 0;
		}

		lpPlayInfo->ClientFunChk1_Count++;
		lpPlayInfo->dwClientFuncChk_1 = lpTransClientFuncPos->dwFuncValue[cnt].dwFunc;
		return TRUE;
	}

	return FALSE;
}


int	rsCheckClientFuncMem(rsPLAYINFO *lpPlayInfo)
{
	TRANS_CLIENT_FUNPOS *lpTransClientFuncPos;
	int	cnt;


	lpTransClientFuncPos = rsGetClientPos(lpPlayInfo->Client_Version);
	if(lpTransClientFuncPos)
	{

		if((lpPlayInfo->ClientFunChk1_Count & 1) == 0)
		{
			rsSendFuncMemToClient2(lpPlayInfo);
		}
		else
		{
			cnt = lpTransClientFuncPos->FuncCount - 1;
			if(cnt > 0)
			{
				cnt = rand() % cnt;
				rsSendFuncMemToClient(lpPlayInfo, lpTransClientFuncPos->dwFuncValue[cnt].dwFunc, lpTransClientFuncPos->dwFuncValue[cnt].dwLen);
			}
		}
	}
	return TRUE;
}


int	rsCompClientFuncMem(rsPLAYINFO *lpPlayInfo, DWORD	dwFunc, DWORD dwChkSum)
{
	TRANS_CLIENT_FUNPOS *lpTransClientFuncPos;
	int cnt;


	lpTransClientFuncPos = rsGetClientPos(lpPlayInfo->Client_Version);
	if(lpTransClientFuncPos)
	{
		for(cnt = 0; cnt < lpTransClientFuncPos->FuncCount; cnt++)
		{
			if(lpTransClientFuncPos->dwFuncValue[cnt].dwFunc == dwFunc)
			{
				if(lpTransClientFuncPos->dwFuncValue[cnt].dwChkSum == dwChkSum)
				{
					if(lpPlayInfo->dwClientFuncChk_1 != dwFunc)
						lpPlayInfo->FuncChkFailCount1++;
					else
						lpPlayInfo->FuncChkSucessCount1++;

					lpPlayInfo->dwClientFuncChk_1 = 0;
					return TRUE;
				}
				if(lpPlayInfo->getSecurity() < AccountTypes::SEC_MODERATOR)
				{

					rsSendGameServer_FuncError(lpPlayInfo, 1, 0);

					if(dwFunc)
						lpPlayInfo->dwFuncChkErrorFlag = dwFunc;
					else
						lpPlayInfo->dwFuncChkErrorFlag = 1;
				}
				return FALSE;
			}
		}
	}

	if(lpPlayInfo->getSecurity() < AccountTypes::SEC_MODERATOR)
	{

		rsSendGameServer_FuncError(lpPlayInfo, 1, 0);

		if(dwFunc)
			lpPlayInfo->dwFuncChkErrorFlag = dwFunc;
		else
			lpPlayInfo->dwFuncChkErrorFlag = 1;

	}

	return FALSE;
}


int	rsCompClientFuncMem2(rsPLAYINFO *lpPlayInfo, DWORD dwFuncCode)
{
	TRANS_CLIENT_FUNPOS *lpTransClientFuncPos;
	int cnt;

	DWORD	dwFunLow_Code;
	DWORD	dwChkLow_Code;
	DWORD	dwFunLow;
	DWORD	dwChkLow;

	if(!dwFuncCode) return FALSE;

	dwFunLow_Code = dwFuncCode & 0xFFFF;
	dwChkLow_Code = dwFuncCode >> 16;



	lpTransClientFuncPos = rsGetClientPos(lpPlayInfo->Client_Version);
	if(lpTransClientFuncPos)
	{
		for(cnt = 0; cnt < lpTransClientFuncPos->FuncCount; cnt++)
		{

			dwFunLow = lpTransClientFuncPos->dwFuncValue[cnt].dwFunc & 0xFFFF;
			dwChkLow = lpTransClientFuncPos->dwFuncValue[cnt].dwChkSum & 0xFFFF;

			if(dwFunLow_Code == dwFunLow && dwChkLow_Code == dwChkLow)
			{

				if((lpPlayInfo->dwClientFuncChk_2 & 0xFFFF) != dwFunLow)
					lpPlayInfo->FuncChkFailCount2++;
				else
					lpPlayInfo->FuncChkSucessCount2++;

				lpPlayInfo->dwClientFuncChk_2 = 0;
				return TRUE;
			}
		}
		if(lpPlayInfo->getSecurity() < AccountTypes::SEC_MODERATOR)
		{

			rsSendGameServer_FuncError(lpPlayInfo, 1, 0);

			lpPlayInfo->dwFuncChkErrorFlag = dwFunLow_Code;
		}
	}

	if(lpPlayInfo->getSecurity() < AccountTypes::SEC_MODERATOR)
	{

		rsSendGameServer_FuncError(lpPlayInfo, 1, 0);

		lpPlayInfo->dwFuncChkErrorFlag = -1;
	}

	return FALSE;
}

