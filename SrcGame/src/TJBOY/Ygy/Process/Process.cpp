#define PROCESS_CPP
#include <windows.h>
#include <stdio.h>
#include "..\\YgyHeader.h"
#include "smPacket.h"



extern void fd(char *fmt, ...);
extern void fd2(char *fmt, ...);

extern HWND hwnd;



#if 0



#pragma comment(lib, "tjboy/HookDll.lib") 
#include "../../khook.h"
UINT  g_uMsg = 0;


#define WM_KEYBOARDHOOK_ACTIVITY (WM_USER + 11)





void dll_open()
{
	g_uMsg = WM_KEYBOARDHOOK_ACTIVITY;

	if(InstallKeyboardHook(hwnd, g_uMsg))
		fd2("Hook installed OK\n");
	else
		fd2("Hook install FAILED\n");
}






void dll_close()
{
#if 0
	if(Hook != NULL)
	{
		UnhookWindowsHookEx(Hook);

		FreeLibrary(hLib);
		Hook = NULL;
	}
#endif

}

#endif

extern char UserAccount[ACCOUNT_SIZE];
extern char	szConnServerName[16];

int vrunRuning = 0;

int gameServerPORT = 0;
char gameServerIP[16] = { 0, };
BOOL bMic = 0;

char g_AllClanWon[_CLANWON_MAX][STRING_MAX];

CProcess::CProcess()
{
	m_cMemMap = NULL;
	m_hRemoteProcess = NULL;
	m_hRemoteWnd = NULL;

	m_bIsMemMap = FALSE;
	m_IsStart = FALSE;

}

CProcess::~CProcess()
{
}



extern HWND hwnd;
int CProcess::InitRemoteProcess()
{
	fd2("InitRemoteProcess()00");
	m_hRemoteWnd = FindWindow(REMOTEPROCESS_NAME, NULL);
	fd2("InitRemoteProcess()11 m_hRemoteWnd  %d", m_hRemoteWnd);

	if(m_hRemoteWnd)
	{
		SendMessage(m_hRemoteWnd, WM_CALLMEMMAP, 0, (LPARAM)hwnd);
		return 1;
	}
	return 0;









}



int CProcess::InitRmoteProcessWnd()
{
	m_nStep = INSIDE_GAMELOGIN;
	return 1;
}



BOOL CProcess::Init()
{

	if(m_IsStart)
	{



		m_cMemMap = (CMemMap*) new CMemMap;
		if(m_cMemMap == NULL)
		{
			return FALSE;
			m_bIsMemMap = FALSE;
		}

		m_cMemMap->SetMemMapSize(MEMORYMAP_MAX);
		m_cMemMap->SetName(MEMORYMAP_NAME);
		m_cMemMap->InitMemoryMap();
		m_bIsMemMap = TRUE;






		InitRmoteProcessWnd();
	}


	return TRUE;
}



VOID CProcess::Clear()
{
	if(!m_IsStart) return;

	UserOut();


	if(m_hRemoteProcess != NULL)
		TerminateProcess(m_hRemoteProcess, 0);

	m_Packet.Clear();
	m_cMemMap->Clear();
	if((m_cMemMap != NULL) && m_bIsMemMap)
	{
		delete m_cMemMap;
	}
}


void PacketParsing()
{
	g_CtrlProcess.PacketParsing();
}
VOID CProcess::PacketParsing()
{
	m_cMemMap->ReadMemoryMap((char*)m_Packet.GetData());
	m_Packet.Parsing();
}

VOID CProcess::Main()
{
	if(!m_IsStart) return;

	switch(m_nStep)
	{
		case INSIDE_GAMELOGIN:

	#if 0
		m_Packet.SetLogin(UserAccount);
		m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetGameLogin());
		SendMessage(m_hRemoteWnd, WM_CALLMEMMAP, (WPARAM)0, 0);
	#endif


		IPPORT ipport;
		ZeroMemory(&ipport, sizeof(ipport));

		ipport.sIndex.dwIndex = INSIDE_IPPORT;
		strcpy(ipport.ip, gameServerIP);
		ipport.port = gameServerPORT;



		m_cMemMap->WriteMemoryMap((char*)&ipport, sizeof(ipport));
		SendMessage(m_hRemoteWnd, WM_CALLMEMMAP, 0, 0);

		m_nStep = -1;
		break;

		case INSIDE_USERINFO:
		m_userInfo.sIndex.dwIndex = INSIDE_USERINFO;
		m_cMemMap->WriteMemoryMap((char*)&m_userInfo, sizeof(m_userInfo));
		SendMessage(m_hRemoteWnd, WM_CALLMEMMAP, 0, 0);
		m_nStep = -1;
		break;

		case INSIDE_USERINFOCHG:
		m_userInfo.sIndex.dwIndex = INSIDE_USERINFOCHG;
		m_cMemMap->WriteMemoryMap((char*)&m_userInfo, sizeof(m_userInfo));
		SendMessage(m_hRemoteWnd, WM_CALLMEMMAP, 0, 0);
		m_nStep = -1;
		break;




		case INSIDE_MICONOFF:
		VOICEONOFF vm;
		ZeroMemory(&vm, sizeof(vm));

		vm.sIndex.dwIndex = INSIDE_MICONOFF;


		vm.bMicONOFF = bMic;

		m_cMemMap->WriteMemoryMap((char*)&vm, sizeof(vm));
		SendMessage(m_hRemoteWnd, WM_CALLMEMMAP, 0, 0);
		m_nStep = -1;
		break;















	}
}





VOID	ParkSetMicOnOFF();

VOID	ParkSetMicOnOFF()
{
	g_CtrlProcess.SetMicOnOFF();
}
VOID	CProcess::SetMicOnOFF()
{
	if(!m_IsStart) return;

	m_nStep = INSIDE_MICONOFF;
}








VOID CProcess::TestInputData(HWND hWnd, WPARAM wParam, LPARAM lParam, char *temp)
{

}

VOID CProcess::SetStep(int step)
{
	m_nStep = step;
}






#if 0
VOID CProcess::SetSelectCha(char *id, char *chaname, char *clanname, DWORD clannum)
{
	if(!m_IsStart) return;


	ZeroMemory(&m_userInfo, sizeof(m_userInfo));
	m_userInfo.sIndex.dwIndex = INSIDE_USERINFO;
	if(id != NULL)
		strncpy(m_userInfo.szID, id, strlen(id));
	if(chaname != NULL)
		strncpy(m_userInfo.szCharName, chaname, strlen(chaname));
	if(clanname != NULL)
		strncpy(m_userInfo.szClanName, clanname, strlen(clanname));
	m_userInfo.dwClanNum = clannum;



	m_nStep = INSIDE_USERINFO;
}
#endif

int firstFlag = 0;
VOID CProcess::SetSelectCha(char *id, char *chaname, char *clanname, DWORD clannum, int utype)
{
	if(!m_IsStart) return;


	if(firstFlag == 0)
	{
		firstFlag = 1;


		ZeroMemory(&m_userInfo, sizeof(m_userInfo));
		m_userInfo.sIndex.dwIndex = INSIDE_USERINFO;



		extern char UserAccount[ACCOUNT_SIZE];
		strncpy(m_userInfo.szID, UserAccount, strlen(UserAccount));


		if(chaname != NULL)
			strncpy(m_userInfo.szCharName, chaname, strlen(chaname));
		if(clanname != NULL)
			strncpy(m_userInfo.szClanName, clanname, strlen(clanname));
		m_userInfo.dwClanNum = clannum;
		m_userInfo.utype = utype;





		if(strlen(szConnServerName) < 15)
		{
			strncpy(m_userInfo.szConnServerName, szConnServerName, strlen(szConnServerName));


			fd2("프리스턴클라: 서버이름  %s ", szConnServerName);
		}
		else
		{

			szConnServerName[15] = 0;
			fd2("프리스턴클라: 서버이름 이상????????????????????? %s ", szConnServerName);
		}

		m_nStep = INSIDE_USERINFO;
		return;
	}




	if(m_userInfo.dwClanNum == clannum)
	{
		return;
	}




	m_userInfo.sIndex.dwIndex = INSIDE_USERINFOCHG;
	if(clanname != NULL)
		strncpy(m_userInfo.szClanName, clanname, strlen(clanname));
	else
	{
		memset(&m_userInfo.szClanName, 0, sizeof(m_userInfo.szClanName));
	}
	m_userInfo.dwClanNum = clannum;
	m_userInfo.utype = utype;


	m_nStep = INSIDE_USERINFOCHG;
}



VOID CProcess::UserOut()
{
	if(!m_IsStart) return;

	P_Out pout;
	pout.sIndex.dwIndex = INSIDE_GAME_OUT;

	m_cMemMap->WriteMemoryMap((char*)&pout, sizeof(pout));
	SendMessage(m_hRemoteWnd, WM_CALLMEMMAP, (WPARAM)0, 0);
	Sleep(1000 * 2);
}


int read_GameOption(char *optStr, char *rStr)
{
	char fname[] = "luncher.INI";
	char folder[] = ".\\";
	char strFilename[128];
	strcpy(strFilename, folder);
	strcat(strFilename, fname);

	if(rStr == NULL)
	{
		return GetPrivateProfileInt("INITGAME", optStr, 0, strFilename);
	}

	GetPrivateProfileString("INITGAME", optStr, NULL, rStr, 128, strFilename);
	return 0;
}


int InitGAMEopt()
{
	FILE *fp;
	fp = fopen("luncher.ini", "rb");
	if(fp == NULL)
	{
		return 0;
	}
	else
	{
		fclose(fp);


		read_GameOption("gameServerIP", gameServerIP);
		gameServerPORT = read_GameOption("gameServerPORT", NULL);
	}
	return TRUE;
}




VOID CProcess::CheckIPandPort(char *ip, int port)
{


	extern BOOL bip_port_error;
	if(bip_port_error == TRUE)
	{
		m_IsStart = FALSE;
		return;

	}



	fd2("CheckIPandPort() 00 ");


	if(InitGAMEopt() == 0)
	{
		if((ip != NULL) && (port != 0))
		{
			fd2("CheckIPandPort() 11 ");

			gameServerPORT = port;
			strncpy(gameServerIP, ip, strlen(ip));

			if(InitRemoteProcess() == 1)
			{
				vrunRuning = 1;
				m_IsStart = TRUE;
				fd2("CheckIPandPort() 22 OK ");
			}
		}
		else
		{


			fd2("CheckIPandPort() 33 ");

			gameServerPORT = 7000;
			strcpy(gameServerIP, "211.44.231.13");

			if(InitRemoteProcess() == 1)
			{
				vrunRuning = 1;
				m_IsStart = TRUE;

				fd2("CheckIPandPort() 44 OK ");
			}

		}
	}
	else
	{
		if(gameServerPORT != 0 && gameServerIP[0] != 0)
		{

			fd2("CheckIPandPort() 55 ");
			if(InitRemoteProcess() == 1)
			{
				vrunRuning = 1;
				m_IsStart = TRUE;
				fd2("CheckIPandPort() 66 ok ");
			}
		}
		else
		{
			m_IsStart = FALSE;

			fd2("CheckIPandPort() 77 false ");
		}
	}
}

VOID CProcess::SetClanChat(char *msg)
{


}
