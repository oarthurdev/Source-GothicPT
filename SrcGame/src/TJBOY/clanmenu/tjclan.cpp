#define TJCLAN_CPP

#include "tjclanDEF.h"


#ifdef USE_PROSTONTALE		

#include "sinbaram\\SinLinkHeader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "Language\\language.h"
#include "HoBaram\\HoTextFile.h"

#include "tjclan.h"
#include "tjscroll.h"
#include "cE_Cmake.h"
#include "cE_chip.h"
#include "cE_user.h"
#include "cE_isclanmember.h"
#include "cE_report.h"
#include "cE_chatlist.h"
#include "cE_deletecha.h"
#include "cE_Cjoin.h"
#include "cE_CViewClanInfo.h"
#include "cE_Updatecldata.h"
#include "cE_Notice.h"

#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "Help.h"
#include "GuideHelp.h" 

#include "..\\ygy\\ygyheader.h"









extern HWND hTextWnd;
extern HWND hFocusWnd;

extern char UserAccount[ACCOUNT_SIZE];
extern char	szConnServerName[16];




#define MOUSE0() TJmb[0]


#else						

#include <windows.h>
#include <stdio.h>
#include "tjclan.h"
#include "tjscroll.h"

#include "clan_Enti.h"
#include "cE_Cmake.h"
#include "cE_chip.h"
#include "cE_user.h"
#include "cE_isclanmember.h"
#include "cE_report.h"
#include "cE_chatlist.h"
#include "cE_deletecha.h"
#include "cE_CJoin.h"
#include "cE_CViewClanInfo.h"
#include "cE_Updatecldata.h"
#include "cE_Notice.h"

#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"





#define MAX_PARTY_MEMBER	6

#define PARTY_NONE		500
#define PARTY_START		1000
#define PARTY_PROCESS	2000
#define PARTY_END		3000

char UserAccount[ACCOUNT_SIZE];
char szConnServerName[16];

extern int MouseButton[3];
extern int MouseDblClick;


extern HWND    g_hwnd;
extern POINT	pCursorPos;
extern HINSTANCE g_hInst;


#define MOUSE0() MouseButton[0]


#endif


int ClanCharMove = 0;
int ClanCLCharMove = 0;


int  banisF[100];


void fd2(char *fmt, ...);





int GuideHelpButton[3] = { 0,0,0 };
int LevelpUpButton[3] = { 0,0,0 };


BOOL bKeyDown = FALSE;
int nKeyDown = 0;
BOOL bKeyUp = FALSE;
int nKeyUp = 0;
BOOL bLButtonDown = FALSE;
BOOL bKeyPageDown = FALSE;
BOOL bKeyPageUp = FALSE;

BOOL IsDrawGuideHelp = FALSE;


void clan_Mouse(int msg, WPARAM wParam)
{
	switch(msg)
	{

		case WM_KEYUP:
		switch(wParam)
		{
			case VK_DOWN:
			GuideHelpButton[0] = FALSE;
			bKeyUp = FALSE;
			bKeyDown = FALSE;
			break;
			case VK_UP:
			bKeyDown = FALSE;
			bKeyUp = FALSE;
			GuideHelpButton[0] = FALSE;
			break;

		}
		break;
		case WM_KEYDOWN:
		switch(wParam)
		{
			case VK_DOWN:
			GuideHelpButton[0] = TRUE;
			bKeyDown = TRUE;
			bKeyUp = FALSE;
			nKeyDown++;
			break;
			case VK_UP:
			GuideHelpButton[0] = TRUE;
			bKeyUp = TRUE;
			bKeyDown = FALSE;
			nKeyUp++;
			break;
			case VK_ESCAPE:
			g_GuideHelp.GuidHelpEnd();
			g_Help.HelpEnd();
			break;

		}
		break;


		case WM_LBUTTONDOWN:
		TJmb2[0] = TJmb[0] = TRUE;

		bKeyDown = FALSE;
		bKeyUp = FALSE;

		GuideHelpButton[0] = TRUE;
		LevelpUpButton[0] = TRUE;


		break;

		case WM_LBUTTONUP:
		TJmb2[0] = TJmb[0] = FALSE;

		bKeyDown = FALSE;
		bKeyUp = FALSE;
		bLButtonDown = FALSE;

		GuideHelpButton[0] = FALSE;
		LevelpUpButton[0] = FALSE;

		break;

		case WM_RBUTTONDOWN:
		TJmb2[1] = TJmb[1] = TRUE;
		break;

		case WM_RBUTTONUP:
		TJmb2[1] = TJmb[1] = FALSE;
		break;

		case WM_MBUTTONDOWN:
		TJmb2[2] = TJmb[2] = TRUE;
		break;

		case WM_MBUTTONUP:
		TJmb2[2] = TJmb[2] = FALSE;
		break;
	}
}



void ktj_imsi_clanMENU_Main()
{
	static int cnt = 0;
	cnt++;

	int mainchk;

	if(cnt < 10)
	{
		mainchk = PARTY_START;

	}
	else
	{
		mainchk = PARTY_PROCESS;
	}



	Interface_clanmenu.Main(mainchk);
#ifdef VOICE_CHAT

	g_CtrlProcess.Main();

#endif
}

void ktj_imsi_clanMENU_Draw()
{
	if(cSinHelp.sinGetHelpShowFlag() && !IsDrawGuideHelp) return;
	Interface_clanmenu.Draw();
}


void clanMENUinit()
{
	Interface_clanmenu.CLANmenu_INIT();

	Interface_clanmenu.CLANmenu_clanPOSITION();
}





void InitHelp()
{
	if(!g_GuideHelp.GetIsOn()) return;

	g_Help.SetStartPos(0, 0);
	if(!g_Help.CheckLevel(sinChar->Level, sinChar->JOB_CODE)) return;
	g_Help.SetHelpN(LEVELUP_HELP);
	g_Help.menuInit(LEVELUP_HELP);

}

void InitGuideHelp()
{
	g_GuideHelp.SetDoing(TRUE);
	g_GuideHelp.SetStartPos(0, 0);
	g_GuideHelp.CheckLevel(sinChar->Level);

	g_GuideHelp.SetHelpN(GUIDEHELP_LIST);
	g_GuideHelp.menuInit(GUIDEHELP_LIST);

	IsDrawGuideHelp = TRUE;
}



void HelpDraw()
{
	if(g_Help.GetHelpN() != -1)
	{
		switch(g_Help.GetHelpN())
		{
			case LEVELUP_HELP:
			g_Help.Draw(0);
			break;
			case LEVELUP_HELP_CONTENT:

			g_Help.Draw(0);
			break;
		}
	}
}

void CLAN_MENU::GuideHelpDraw()
{
	if(g_GuideHelp.GetHelpN() != -1)
	{
		switch(g_GuideHelp.GetHelpN())
		{
			case GUIDEHELP_LIST:
			DrawBox(NOTICE_X, NOTICE_Y - 50, 9, 9);
			g_GuideHelp.Draw();
			break;
			case GUIDEHELP_CONTENT:
			DrawBox(NOTICE_X, NOTICE_Y - 50, 9, 9);
			g_GuideHelp.Draw();
			break;

		}
	}
}
int GoWavDown_Check = 0;

char szWavUrl[255] = { 0, };
BOOL bWavError = FALSE;


int GoNotice_chking = 0;
int m_nNoticeCount = -1;
char szNoticeUrl[255] = { 0, };

int GetNoticeUrl(char *url)
{
	GoNotice_chking = 0;
	::ZeroMemory(szNoticeUrl, sizeof(szNoticeUrl));
	strcpy(szNoticeUrl, url);

	GoNotice_chking = 1;
	return 1;
}

void GoNotice_chk()
{
	if(OpenFlag == 1) return;

	if(GoNotice_chking == 1)
	{
		if(m_nNoticeCount < NOTICECOUNT - 1)
		{
			GoNotice_chking = 0;
			++m_nNoticeCount;
			void GoNotice();
			GoNotice();
		}

	}
}


void GoNotice()
{
	C_menuN2 = 0;
	OpenFlag = 1;
	C_menuN = CLAN_NOTICE;



}








void clanMENU_INIT(int setN)
{
	if(bCheckHostNameandPort == 0)
	{

		switch(setN)
		{
			case 0:
			void ReadWEBDebugOption();
			ReadWEBDebugOption();


			break;

			case 1:
			Interface_clanmenu.NoticeMessage_Init2();
		#ifdef USE_PROSTONTALE		
			Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, szConnServerName,
			sinChar->Money, 500000);
		#endif
			break;
		}
	}



	if(!bCheckHostNameandPort) return;




	switch(setN)
	{
		case -1:
		void ReadWEBDebugOption();
		ReadWEBDebugOption();


		ZeroMemory(&ClanWonList, sizeof(CLANWONLIST));

		Interface_clanmenu.CLANmenu_INIT();

		Interface_clanmenu.CLANmenu_clanPOSITION();


		break;


		case 0:
		void ReadWEBDebugOption();
		ReadWEBDebugOption();

		int LoadClanMessage();
		LoadClanMessage();

		void CreateSaveData_dir();
		CreateSaveData_dir();





		ZeroMemory(&ClanWonList, sizeof(CLANWONLIST));
		Interface_clanmenu.CLANmenu_INIT();
	#ifdef VOICE_CHAT



		g_CtrlProcess.CheckIPandPort(0, 0);

	#endif

		break;

		case 1:

	#ifdef VOICE_CHAT

		g_CtrlProcess.Init();
	#endif
	#ifdef USE_PROSTONTALE		

		cBaseMenu.Load2();
		cClanChatting.Load2();
		Interface_clanmenu.Init2();



	#ifdef USE_YAHEL

		Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, "¿©¿Õ¹ú¼­¹ö",
								   #else
		Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, szConnServerName,
								   #endif
									   sinChar->Money, 500000);



		Interface_clanmenu.CLANmenu_clanPOSITION();


	#endif
		break;
	}
}



int isDELETE_character(char *charName)
{
	if(!bCheckHostNameandPort) return 1;


	int web_DB_state_FLAG_WAIT();
	while(1)
	{
		if(web_DB_state_FLAG_WAIT() == 1)
			break;
	}




#ifdef USE_YAHEL

	Interface_clanmenu.SetUserData(UserAccount, charName, "¿©¿Õ¹ú¼­¹ö",
							   #else
	Interface_clanmenu.SetUserData(UserAccount, charName, szConnServerName,
							   #endif

								   500000, 500000);


	Interface_clanmenu.CLANmenu_clanPOSITION();
	cldata.myPosition = 0;
	while(1)
	{
		web_DB_main();
		cIsClanMember.Main();

		if(cldata.myPosition != 0)
			break;
	}

	while(1)
	{
		if(web_DB_state_FLAG_WAIT() == 1)
			break;
	}


	return cldata.myPosition;
}


//Carinha BC
void CLAN_MENU::Init2()
{
#ifdef USE_PROSTONTALE		

	MatPartyBackGround =
		CreateTextureMaterial("image\\Sinimage\\Help\\party_win.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);



	hBox1 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox2 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox3 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box3.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox4 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box4.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	hBox5 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box5.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox6 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box6.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox7 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box7.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox8 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box8.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox9 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box9.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);


	hScl_icon_tj = CreateTextureMaterial("image\\Sinimage\\Help\\scl_icon.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	g_Help.Load();
	g_GuideHelp.Load();


	cBaseMenu.copy_LoadResource2(&cIsClanMember);
	cBaseMenu.copy_LoadResource2(&cClanChip);
	cBaseMenu.copy_LoadResource2(&cClanUser);
	cBaseMenu.copy_LoadResource2(&cClanMake);
	cBaseMenu.copy_LoadResource2(&cClanReport);
	cBaseMenu.copy_LoadResource2(&cClanChatting);
	cBaseMenu.copy_LoadResource2(&cClanDeleteCha);
	cBaseMenu.copy_LoadResource2(&cClanJoin);

	cBaseMenu.copy_LoadResource2(&cClanNotice);

#endif
}


void CLAN_MENU::NoticeMessage_Init2()
{
#ifdef USE_PROSTONTALE		

	MatPartyBackGround =
		CreateTextureMaterial("image\\Sinimage\\Help\\party_win.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);



	hBox1 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox2 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox3 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box3.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox4 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box4.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	hBox5 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box5.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox6 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box6.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox7 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box7.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox8 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box8.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox9 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box9.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);


	hScl_icon_tj = CreateTextureMaterial("image\\Sinimage\\Help\\scl_icon.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cBaseMenu.copy_LoadResource2(&cClanNotice);

#endif
}




void CLAN_MENU::CLANmenu_INIT()
{
	if(!bCheckHostNameandPort) return;


	Init();


#ifdef  USE_PROSTONTALE






#ifdef USE_YAHEL

	SetUserData(UserAccount, sinChar->szName, "¿©¿Õ¹ú¼­¹ö",
			#else
	SetUserData(UserAccount, sinChar->szName, szConnServerName,
			#endif
				sinChar->Money, 500000);




#else





	strcpy(szConnServerName, "Æë±Ï¼­¹ö");
	SetUserData("Red", "»¡°­", szConnServerName, 500000, 100000);
	SetUserData("ccc", "»¡°­4", szConnServerName, 500000, 100000);








#endif
}



BOOL bGetChaClan = FALSE;
int  nGetChaClan = 0;
int nStatusCount = 0;


int cntsu = 0;
char *szSelectCha[5][2];


void InitSelectCha()
{
	if(!bCheckHostNameandPort) return;

	nStatusCount = 0;
	ZeroMemory(chacldata, sizeof(chacldata));
	ZeroMemory(szSelectCha, sizeof(szSelectCha));
	cntsu = 0;
}

void ClearSelectCha()
{
	if(!bCheckHostNameandPort) return;


	int i;
#ifdef USE_PROSTONTALE		
	for(i = 0; i < 5; i++)
	{
		if(chacldata[i].hClanMark)
		{

			chacldata[i].hClanMark->Release();
			chacldata[i].hClanMark = NULL;

		}
		if(chacldata[i].hClanMark16)
		{

			chacldata[i].hClanMark16->Release();
			chacldata[i].hClanMark16 = NULL;

		}
	}


#else
	for(i = 0; i < 5; i++)
	{
		if(chacldata[i].hClanMark)
		{


			DeleteObject(chacldata[i].hClanMark);

		}
		if(chacldata[i].hClanMark16)
		{

			DeleteObject(chacldata[i].hClanMark16);

		}
	}
#endif
	bGetChaClan = FALSE;
	ZeroMemory(szSelectCha, sizeof(szSelectCha));
	ZeroMemory(chacldata, sizeof(chacldata));
	ZeroMemory(&cldata, sizeof(CLANDATA));
	nStatusCount = 0;

}


int HONG_GetChaClanName(char* id, char* chaname)
{
	if(!bCheckHostNameandPort) return 0;


	int i;
	int nReturn = 0;;
	for(i = 0; i < 5; i++)
	{
		if(szSelectCha[i][0] == NULL)
		{
			szSelectCha[i][0] = id;
			szSelectCha[i][1] = chaname;
			nReturn = 1;

			break;
		}
	}

	cntsu = i + 1;

	if(i == 5) return -1;

	return nReturn;
}




int  main_chaC()
{
	if(!bCheckHostNameandPort) return 0;



	Interface_clanmenu.Main(PARTY_PROCESS);

	if(nStatusCount >= cntsu)
	{
		return 1;
	}
	else
	{
		if(OpenFlag == 0)
		{
			bGetChaClan = TRUE;
			int GetChaClanName(char* id, char* chaname, char* gserver);
			GetChaClanName(szSelectCha[nStatusCount][0], szSelectCha[nStatusCount][1], szConnServerName);
		}
	}
	return 0;
}


int GetChaClanName(char* id, char* chaname, char* gserver)
{
	if(!bCheckHostNameandPort) return 0;



	Interface_clanmenu.Main(PARTY_PROCESS);


	bGetChaClan = FALSE;
	C_menuN2 = 0;
	OpenFlag = 1;
	joinAnswer = 0;
	nGetChaClan = 0;
	void SetUserData2(char* id, char* chaname, char* gserver);
	SetUserData2(id, chaname, gserver);
	C_menuN = CLAN_isClanWon;
	bGetChaClan = TRUE;

	return 1;
}







#ifdef VOICE_CHAT
BOOL bCheckClan = FALSE;
#endif
int CLAN_MENU::CLANmenu_clanPOSITION()
{

	if(!bCheckHostNameandPort)
	{
		cldata.myPosition = CLAN_NOCONNECT;
		return 0;
	}

	if(OpenFlag == 1) return 0;

	C_menuN2 = 0;
	OpenFlag = 1;
	joinAnswer = 0;
	C_menuN = CLAN_isClanWon;
	menuInit(C_menuN);
	ClanCharMove = 1;

#ifdef VOICE_CHAT	
	bCheckClan = TRUE;
#endif
	return 1;
}



void CLANmenu_meetNPC()
{
	Interface_clanmenu.CLANmenu_meetNPC();
}
int CLAN_MENU::CLANmenu_meetNPC()
{
	if(OpenFlag == 1)
	{
		if(C_menuN == CLAN_DISPLAY_INFO)
		{
			C_menuN = CLAN_CLOSE_END_BEFORE;

		}
		return 0;
	}


	C_menuN2 = 0;
	OpenFlag = 1;
	joinAnswer = 0;
	if(!bCheckHostNameandPort)
	{
		C_menuN = CLANSERVER_INSPECT_BEFORE;

	}
	else
	{
		C_menuN = CLAN_GO_NPCSTART;
	}




	ClanCharMove = 1;
	return 1;
}





void CLANmenu_ChatList(int sw)
{
	Interface_clanmenu.CLANmenu_ChatList(sw);
}
void CLAN_MENU::CLANmenu_ChatList(int sw)
{

	if(!bCheckHostNameandPort) return;
	if(OpenFlag == 1) return;
	if(bOpenChatList) return;

	ChatList_CmenuN2 = 0;

	switch(sw)
	{
		case 0:

		cClanChatting.InitClanChatList();
		if(bIsReadData) ChatList_CmenuN = CLAN_DISPLAY_OPEN;
		else	ChatList_CmenuN = CHATLIST_READDATA;

		cClanChatting.menuInit(ChatList_CmenuN);

		break;
		case 1:
		cClanChatting.NoScroll();



		ChatList_CmenuN = CLAN_DISPLAY_INFO;
		cClanChatting.menuInit(ChatList_CmenuN);

	#ifdef USE_PROSTONTALE		

	#else
		OpenFlag = 1;
		C_menuN = ChatList_CmenuN;

	#endif


		break;
	}
}




void CLANmenu_ChatList_Main()
{
	cClanChatting.Main();
}
void CLANmenu_ChatList_Draw()
{
	cClanChatting.Draw();
}



void Updatecldata()
{

	g_UpdateCldata.Updatecldata();
}




void ClanJoin(char *oneClanName, char *oneChipCharid)
{

	Interface_clanmenu.SetJoinData(oneClanName, oneChipCharid);
	Interface_clanmenu.ClanJoin();
}



int JoinAnswer()
{
	return cClanJoin.nJoinAnswer;
}

void CLAN_MENU::ClanJoin()
{
	if(OpenFlag == 1) return;
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;
	C_menuN = CLAN_JOIN_before;

}




void joinClanMember()
{
	Interface_clanmenu.joinClanMember();
}

void CLAN_MENU::joinClanMember()
{
	if(OpenFlag == 1) return;


	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;
	C_menuN = CLAN_JOIN_chip;
}


void CLANmenu_DeleteCha(char *id, char *gserver, char *chaname)
{
	cClanDeleteCha.SetDeleteChaInfo(id, gserver, chaname);
	Interface_clanmenu.CLANmenu_DeleteCha();

	cClanDeleteCha.bFlag = FALSE;
}



void ktj_IMSI_DELETE()
{



}




void CLANmenu_DeleteCha_SetCharacter(char *id, char *gserver, char *chaname)
{
	cClanDeleteCha.SetDeleteChaInfo(id, gserver, chaname);


	Interface_clanmenu.CLANmenu_DeleteCha();
}


void CLAN_MENU::CLANmenu_DeleteCha()
{
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;
	C_menuN = CLAN_DELETECHA_START;

	cClanDeleteCha.SetHowDeleteChaFlag();
}


int CLANmenu_DeleteCha_flag()
{




	return cClanDeleteCha.GetHowDeleteChaFlag();
}









int g_ClanCount = -1;
int ClanMark[10] = { 0,0,0,0,0,0,0,0,0,0 };


int ReadClanInfo(DWORD dwClanNum)
{

	g_ClanCount++;
	if(g_ClanCount > 9) g_ClanCount = 0;
	ClanMark[g_ClanCount] = dwClanNum;




	g_ViewClanInfo.SearchClan(dwClanNum);
	return ClanInfo_nNum;
}




int ReadClanInfo_32X32(DWORD dwClanNum)
{
	int claninfo_n = ReadClanInfo(dwClanNum);
	if(claninfo_n >= 0)
	{
		int clanINFO_Load32X32(int claninfo_n);
		clanINFO_Load32X32(claninfo_n);
	}
	return claninfo_n;
}


















CLAN_MENU::CLAN_MENU()
{
	nClanWon_Num = 0;
	nScl_Bar = 0;
	g_nClanIconNum;
	g_HelpIconNumber = 0;
	g_HelpDisPlay = 0;

}

CLAN_MENU::~CLAN_MENU()
{
}



POINT clanBoxPos;
POINT clanCLBoxPos;
void CLAN_MENU::Init()
{
	OpenFlag = 0;

	C_menuN = 0;
	C_menuN2 = 0;









	BackStartPos.x = 101;
	BackStartPos.y = 114;



	clanBoxPos.x = BackStartPos.x;
	clanBoxPos.y = BackStartPos.y;


	clanCLBoxPos.x = 540 + 60;
	clanCLBoxPos.y = CHATLIST_BOX_Y;




	ZeroMemory(szRemoveClanWon, sizeof(char) * 500);
	ZeroMemory(ClanHelpIcon, sizeof(CLANHELPICON)*CLANHELPICON_NUM);
	ZeroMemory(cldata.szJoinClanName, sizeof(char) * 64);
	ZeroMemory(cldata.ChaName, sizeof(char) * 64);
	ZeroMemory(cldata.szJoinClanChipName, sizeof(char) * 64);
	ZeroMemory(szReconfReleaseMsg, sizeof(char) * 2048);


	nClanWon_Num = 0;
	nReleaseClanWon = 0;



#ifndef USE_PROSTONTALE		
	int LoadClanMessage();
	LoadClanMessage();
#endif

	Load();
	cClanChatting.Load();



	cBaseMenu.Load();


	cIsClanMember.Init(1);
	cIsClanMember.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cIsClanMember);

	cClanChip.Init(1);
	cClanChip.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanChip);
	cBaseMenu.SetBase(&cClanChip);

	cClanUser.Init(1);
	cClanUser.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanUser);
	cBaseMenu.SetBase(&cClanUser);

	cClanMake.Init(1);
	cClanMake.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanMake);

	cClanReport.Init(1);
	cClanReport.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanReport);


	cClanChatting.Init(1);
	cClanChatting.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanChatting);
	cBaseMenu.SetBase(&cClanChatting);


	cClanDeleteCha.Init(1);
	cClanDeleteCha.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanDeleteCha);

	cClanJoin.Init(1);
	cClanJoin.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanJoin);


	cClanNotice.Init(1);
	cClanNotice.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanNotice);







	g_GuideHelp.Init(1);
	g_GuideHelp.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&g_GuideHelp);
	g_GuideHelp.InitLevelHelpLabel();

}




void CLAN_MENU::NoticeMessage_Init()
{
	BackStartPos.x = 101;
	BackStartPos.y = 114;

	cBaseMenu.Load();

	cClanNotice.Init(1);
	cClanNotice.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanNotice);

	g_Help.Load();
	g_GuideHelp.Load();

	g_GuideHelp.Init(1);
	g_GuideHelp.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&g_GuideHelp);
	g_GuideHelp.InitLevelHelpLabel();

}



void CLAN_MENU::menuInit(int num)
{

	cIsClanMember.menuInit(num);
	cClanMake.menuInit(num);
	cClanChip.menuInit(num);
	cClanUser.menuInit(num);
	cClanChatting.menuInit(num);
	cClanDeleteCha.menuInit(num);
	cClanJoin.menuInit(num);
}





int CLAN_MENU::chkMenu(int x, int y, RECT *r)
{
	if(r->left <= x   &&   x <= r->right)
		if(r->top <= y   &&   y <= r->bottom)
			return 1;
	return 0;
}
int CLAN_MENU::chkeckMenuN()
{
	int i;

	for(i = 0; i < menuSu; i++)
	{
		if(chkMenu(pCursorPos.x, pCursorPos.y, &menuPos[i]))
		{
			return i;
		}
	}
	return -1;
}






void menu_joinOpen(char *chipCharID)
{

}



int CLAN_MENU::menu_joinOpen(char *chipCharID)
{


	return 1;

}





void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID)
{
	Interface_clanmenu.menu_joinOpen_Chip(isOK, clanWonID, clanWonCharID, 0, 0);
}
void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel)
{
	Interface_clanmenu.menu_joinOpen_Chip(isOK, clanWonID, clanWonCharID, clanWonJob, clanWonLevel);
}


void g_IsCheckClanMember(smCHAR *pChar)
{
	Interface_clanmenu.IsCheckClanMember(pChar);
}

int CLAN_MENU::IsCheckClanMember(smCHAR *pChar)
{
	if(OpenFlag == 1)
		return 0;

	C_menuN = CLAN_IS_CHECK_MEMBER;
	cldata.TargetChar = NULL;
	if(pChar)
		cldata.TargetChar = pChar;



	C_menuN2 = 0;
	OpenFlag = 1;
	joinAnswer = 0;
	ClanCharMove = 1;

	return 0;
}






BOOL CheckClanWon(int level);






int CLAN_MENU::menu_joinOpen_Chip(int joinOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel)
{
	if(OpenFlag == 1) return 0;


#ifdef __CLANSUBCHIP__

	if(cldata.myPosition == 101 || cldata.myPosition == 104) goto jmp1;
	return 0;
jmp1:
#else
	if(cldata.myPosition != 101) return 0;
#endif




#ifdef USE_PROSTONTALE		
	int chk = CheckClanWon(sinChar->Level);
	if(chk == 0)
	{
		return 0;
	}
#endif


	C_menuN = CLAN_JOIN_chip;
	strcpy(cldata.clanJoinID, clanWonID);
	strcpy(cldata.clanJoinCharID, clanWonCharID);
	cldata.clanJoinJob = clanWonJob;
	cldata.clanJoinLevel = clanWonLevel;


	C_menuN2 = 0;

	OpenFlag = 1;
	joinAnswer = 0;


	ClanCharMove = 1;


	return 1;
}











extern BOOL bip_port_error;
int CLAN_MENU::Main(int sw)
{
	web_DB_main();

	GoNotice_chk();
	if((bip_port_error == 1) || GoNotice_chking || (m_nNoticeCount > -1))
	{

		cClanNotice.Main();
	}

	g_Help.Main();
	g_GuideHelp.Main();




	if(bip_port_error) return 0;


	if(OpenFlag == 0) return 0;


	switch(sw)
	{
		case PARTY_START:
		return 1;
		case PARTY_END:
		return 1;
	}



	cBaseMenu.Main();
	cIsClanMember.Main();
	cClanReport.Main();
	cClanMake.Main();
	cClanChip.Main();
	cClanUser.Main();
	cClanJoin.Main();
#ifdef USE_PROSTONTALE		


#else
	cClanChatting.Main();
#endif

	cClanDeleteCha.Main();
	cClanNotice.Main();

	return TRUE;
}




char loadis[256] = { 0, };
char loadis2[256] = { 0, };
char updateis[256] = { 0, };






int ktj_imsiDRAWinfo = 0;


int CLAN_MENU::Draw()
{


#ifndef USE_PROSTONTALE
	window_renderINIT();
#endif


	HelpDraw();
	GuideHelpDraw();


	if((bip_port_error == 1) || (m_nNoticeCount > -1))
	{
		if(C_menuN == CLAN_DRAWNOTICE)
		{
			DrawBox(NOTICE_X, NOTICE_Y - 50, 9, 10);
			Draw_C_menuN();
		}
		if(m_nNoticeCount > -1)
			cClanNotice.Draw();
	}



	if(bip_port_error) return 0;

#ifdef USE_PROSTONTALE		


#ifdef VOICE_CHAT



#endif







	if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && ktj_imsiDRAWinfo == 1)
	{


		char buf[256];

		wsprintf(buf, "bug :  %d ================ : (myPos:%d ) (Å¬·£¸¶Å©¹øÈ£%s,%d)  cldata.money %d, cldata.nCurrentClanWon_Num %d ", C_menuN, cldata.myPosition, cldata.ClanMark, cldata.intClanMark, cldata.money, cldata.nCurrentClanWon_Num);
		Draw_C_Text(buf, 0, 0, 0);


		wsprintf(buf, "cldata.szID %s  cldata.ChaName %s cldata.name %s (C_menuN %d C_menuN2 %d) ================ ", cldata.szID, cldata.ChaName, cldata.name, C_menuN, C_menuN2);
		Draw_C_Text(buf, 0, 16, 0);



		int cinfoX = 0;
		int cinfoY = 32;
		int i2;
		for(i2 = 0; i2 < 100; i2++)
		{
			if(ClanInfo[i2].nStatus == 0) continue;

			char buf[256];
			wsprintf(buf, "ClanInfo[%d] %s %s %s ", i2,
					 ClanInfo[i2].ClanInfoHeader.ClanMark_Num,
					 ClanInfo[i2].ClanInfoHeader.ClanName,
					 ClanInfo[i2].ClanInfoHeader.ClanReport);

			Draw_C_Text(buf, cinfoX, cinfoY, 0);
			cinfoY += 16;
		}


		int cinfoX2 = 16 * 25;
		int cinfoY2 = 32;

		for(i2 = 0; i2 < 10; i2++)
		{
			char buf[256];
			wsprintf(buf, "up ¸¶Å©¹øÈ£ [%d]:%d (ÃÖÁ¾ %d)", i2, ClanMark[i2], g_ClanCount);
			Draw_C_Text(buf, cinfoX2, cinfoY2, 0);
			cinfoY2 += 16;
		}


		cinfoX2 = 20 * 35;
		cinfoY2 = 32;

		for(i2 = 0; i2 < 41; i2++)
		{




			Draw_C_Text(cldata.clanWon[i2], cinfoX2, cinfoY2, 0);
			cinfoY2 += 16;
		}

	#ifdef VOICE_CHAT

		char Msg3[1024] = { 0, };
		int nPos = 0;
		{
			extern char g_AllClanWon[_CLANWON_MAX][STRING_MAX];
			for(int i = 0; i < 90; i += 5)
			{
				wsprintf(Msg3, "%s, %s,  %s , %s, %s\n",
						 g_AllClanWon[i], g_AllClanWon[i + 1], g_AllClanWon[i + 2], g_AllClanWon[i + 3]
						 , g_AllClanWon[i + 4]);
				Draw_C_Text(Msg3, 300, 230 + nPos, 0);
				nPos += 20;
			}


		}
	#endif







	}




#endif









	if(OpenFlag == 0) return 0;


#ifndef USE_PROSTONTALE		


	HDC hdc = GetDC(g_hwnd);
	HDC sorDC;
	sorDC = CreateCompatibleDC(hdc);
	HDC destdc = CreateCompatibleDC(hdc);
	SelectObject(destdc, Dback.hb);
	PatBlt(destdc, 0, 0, 800, 600, PATCOPY);
	char szBuf[100];
	extern POINT	pCursorPos;


	wsprintf(szBuf, "C_menuN : %d  ,x = %d, y = %d , ÁøÇà °úÁ¤ : %d Å¬·£ ÀÌ¸§ : %s,myposition=%d",
			 C_menuN, pCursorPos.x, pCursorPos.y, nCheckDownLoad, cldata.name, cldata.myPosition);
	dsTextLineOut(destdc, 100, 0, szBuf, lstrlen(szBuf));

	SelectObject(hdc, ClanInfo[ClanInfo_nNum].hClanMark);
	BitBlt(destdc, 0, 0, 32, 32, sorDC, 0, 0, SRCCOPY);
	dsTextLineOut(destdc, 0, 50, ClanInfo[ClanInfo_nNum].ClanInfoHeader.ClanReport, lstrlen(ClanInfo[ClanInfo_nNum].ClanInfoHeader.ClanReport));
	DeleteDC(destdc);
	DeleteDC(sorDC);
	ReleaseDC(g_hwnd, hdc);

#endif



	switch(C_menuN)
	{
		case CLAN_DRAWNOTICE:

		DrawBox(NOTICE_X, NOTICE_Y, 9, 10);

		cClanNotice.Draw();
		break;
		case CLAN_NOLEVEL:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_ABILITYDOWN:
		case CLANSERVER_INSPECT:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_READ_CLANMARK:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_isCheckClanJang_Result:
		case CLAN_isCheckClanJang:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_MAKE_is:

		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLANMAKE_NOMONEY:
		case CLAN_MONEY_is:

		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();

		break;
		case CLAN_NAME_is:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_NONAME:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_NAME_BEING:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_MARK_expl:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();

		break;
		case CLAN_INSPECTION_expl:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();

		break;

		case CLANMAKE_REAMMAKR_ERROR:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_NotMake:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLANMAKE_DOWN_INFO:
		case CLANMAKE_READ_CLANMARK:
		case CLAN_MAKE_FINISH:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_AllEnd:
		break;


		case CLAN_ERROR:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;








	#ifdef __CLANSUBCHIP__
		case CLANCHIP_SUBCHIP_LOAD_DATA:
		case	CLANCHIP_APPOINTSUBCHIP_DO:
		case CLANCHIP_RELEASESUBCHIP_DO:
		case CLANCHIP_SUBCHIP_APPOINT_FLAG:
		case CLANCHIP_SUBCHIP_RELEASE_FLAG:
		case CLANCHIP_SUBCHIP_READMSG_FLAG:
		case CLANUSER_SUBCHIP_READMSG_FLAG:
		case CLANCHIP_SUBCHIP_LIST:
		case CLANCHIP_RESUBCHIP_APPOINT:
		case CLANCHIP_RESUBCHIP_APPOINT_END:
		case CLANCHIP_RELEASESUBCHIP:
		case CLANCHIP_RELEASESUBCHIP_END:
		case CLANCHIP_SUBCHIP_APPOINTMSG:
		case CLANCHIP_SUBCHIP_RELEASEMSG:
		case CLANUSER_SUBCHIP_APPOINTMSG:
		case CLANUSER_SUBCHIP_RELEASEMSG:
		case CLANCHIP_NOSUBCHIP:

	#endif


		case CLANCHIP_LEAVECLAN_NOLEVEL:
		case CLANCHIP_LEAVECLANDOWNLEVEL:
		case	CLANCHIP_LEAVECLAN_PFLAG:
		case CLANCHIP_LEAVECLAN_MESSAGE:
		case CLANUSER_LEAVECLAN_MESSAGE:
		case CLANCHIP_LEAVECLAN_MESSAGEEND:
		case CLANUSER_LEAVECLAN_MESSAGEEND:
		case CLANCHIP_NOLEAVECLAN:
		case CLANCHIP_LEAVECLAN_RECONFIRM:
		case CLANCHIP_LEAVECLAN_CONFIRM:
		case CLANCHIP_LEAVECLAN_NOMONEY:
		case CLANCHIP_LEAVECLAN_SUCESS:
		case CLANCHIP_LEAVECLAN:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_CHIP:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;


		case CLAN_REMOVE:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_REMOVE_SHORTCLANWON_RESULT:
		case CLAN_REMOVE_RESULT:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_REMOVE_SHORTCLANWON:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_RELEASE:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_RECONF_RELEASE:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_FINISH_RELEASE:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLANCHIP_RELEASEMESSAGE:
		case CLAN_WAREHOUSE_RIGHT:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_MARK1:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_MARK2:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_MARK3:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_HELP:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_HELP_CONTENT:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;


		case CLANCHIP_LEAVECLAN_DO:
		case ISPFLAG_CHIP:
		case CLANCHIP_MAKE_FIRSTMESSAGE:
		case CLANCHIP_DOWN6_CLANWON:
		case CLANCHIP_DOWN6_CLANWON_MESSAGE:
		case CLAN_NOMAKE:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;

		case CLANUSER_REMOVE:
		case	CLANUSER_AUTORELEASE:
		case CLAN_USER:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;

		case CLAN_USER_NOMAKE:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_SECESSION:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_RECONF_SECESSION:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_FINISH_SECESSION:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLANUSER_MAKE_FIRSTMESSAGE:
		case CLANUSER_DOWN6_CLANWON_MESSAGE:
		case CLANUSER_DOWN6_CLANWON:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;


		case CLANUSER_JOIN:
		case CLAN_CLANWONOVER:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;

		case CLAN_JOIN:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;

		case CLAN_USER_WAREHOUSE:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_USER_HELP:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_USER_HELP_CONTENT:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;

		case CLAN_DISPLAY_END:
		case CLAN_DISPLAY_OPEN:
		case CLAN_DISPLAY_CLOSE:
		case CLAN_CLOSE_ENDING:
		case CLAN_DISPLAY_INFO:
		case CHATLIST_READDATA:
	#ifdef USE_PROSTONTALE		

	#else
		cClanChatting.Draw();
	#endif
		break;


		case CLAN_DELETECHA_RELEASECLAN_BEFORE:
		case CLAN_DELETECHA_RELEASECLAN:
		case	CLAN_DELETECHA_SECESSION_BEFORE:
		case	CLAN_DELETECHA_SECESSION:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		cClanDeleteCha.Draw();
		break;
		case CLAN_REAMMAKR_ERROR:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;
		case CLAN_RELEASE_LOADING:
		case CLAN_REMOVE_SHORTCLANWON_LOADING:
		case CLAN_REMOVE_LOADING:
		case CLAN_CHIP_ReadDATA:
		case CLAN_NPC_START:
		case CLAN_USER_ReadDATA:
		case ISPFLAG_USER:
		case CLANUSER_RELEASEMESSAGE:
		case CLANUSER_RELEASE_FLAG:
		case CLAN_RECONF_SECESSION_LOADING:
		DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		Draw_C_menuN();
		break;

	}

#ifndef USE_PROSTONTALE		
	window_renderFLIP();
#endif

	return TRUE;
}



void CLAN_MENU::Draw_C_Text(char *str, int x, int y, int sw = 0)
{
#ifdef USE_PROSTONTALE		
	char strbuf[1024];

	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt = 0;
	int i = 0;

	while(1)
	{


		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')
		{
			strbuf[i] = 0;
			i = 0;
		jmp1:



			if(sw == 2)
			{
				SetFontTextColor( RGB(100, 100, 100));

				dsTextLineOut( x + 1, y + 1, strbuf, lstrlen(strbuf));

				SetFontTextColor( RGB(230, 255, 240));
				dsTextLineOut( x, y, strbuf, lstrlen(strbuf));
			}
			else
			{
				SetFontTextColor( RGB(230, 255, 240));
				dsTextLineOut( x, y, strbuf, lstrlen(strbuf));
			}




			ZeroMemory(strbuf, sizeof(strbuf));
			y += 16;

			if(cnt >= strL) break;
		}
		else if(cnt >= strL)
		{
			goto jmp1;
		}
		else
		{
			i++;
		}
	}


	if(sw == 1)
	{
		static int cnt = 0;
		cnt++;
		if(cnt < 20)
		{
			SetFontTextColor( RGB(255, 255, 255));
			dsTextLineOut( x + (lstrlen(str) * 6), y - 16, "|", 1);
		}
		if(cnt >= 40) cnt = 0;
	}

#else

#endif
}







int g_nTotalWidth = 0;
int CLAN_MENU::DrawBox(int x, int y, int x_width, int y_height)
{

	if(cSinHelp.sinGetHelpShowFlag() && !IsDrawGuideHelp) return FALSE;
	isDrawClanMenu = 1;
	g_nTotalWidth = x_width;



#ifdef USE_PROSTONTALE		

#define BOXFONTSIZE 64

	if(d3ddev == NULL)
		return FALSE;

	






	sinDrawTexImage(hBox5, (float)x + 64, (float)y + 32, (float)(64 + ((x_width - 2) * 32)), (float)(32 + ((y_height - 1) * 32)),
					0, 0,
					0, 0, 32, 32,
					255);






	sinDrawTexImage(hBox1, (float)x, (float)y, (float)64, (float)32,
		(float)0, (float)0,
					(float)0, (float)0, (float)64, (float)32,
					255);

	sinDrawTexImage(hBox3, (float)(x + (32 * x_width) + 64), (float)y, 64, 32,
		(float)0, (float)0,
					(float)0, (float)0, (float)64, (float)32,
					255);

	sinDrawTexImage(hBox7, (float)x, (float)(y + (32 * y_height) + 32), 64, 64,
		(float)0, (float)0,
					(float)0, (float)0, (float)64, (float)32,
					255);

	sinDrawTexImage(hBox9, (float)(x + (32 * x_width) + 64), (float)(y + (32 * y_height) + 32), 64, 64,
		(float)0, (float)0,
					(float)0, (float)0, (float)64, (float)32,
					255);

	int line;
	int sx = x + 64;
	int ey = y + (32 * y_height) + 32;
	for(line = 0; line < x_width; line++)
	{

		sinDrawTexImage(hBox2, (float)sx, (float)y, 32, 32,
			(float)0, (float)0,
						(float)0, (float)0, (float)32, (float)32,
						255);


		sinDrawTexImage(hBox8, (float)sx, (float)(ey), 32, 64,
						0, 0,
						0, 0, 32, 64,
						255);

		sx += 32;
	}

	int sy = y + 32;
	int ex = x + (32 * x_width) + 64;
	for(line = 0; line < y_height; line++)
	{

		sinDrawTexImage(hBox4, (float)x, (float)sy, 64, 32,
						0, 0,
						0, 0, 64, 32,
						255);

		sinDrawTexImage(hBox6, (float)ex, (float)sy, 64, 32,
						0, 0,
						0, 0, 64, 32,
						255);
		sy += 32;
	}

	






#else









	BITMAP bit;
	int bx, by;
	int i;
	int nTotal_Width = 0;
	int nTotal_Height = 0;







	HDC hdc = GetDC(g_hwnd);

	HDC sorDC = CreateCompatibleDC(hdc);
	HDC destdc = CreateCompatibleDC(hdc);

	SelectObject(destdc, Dback.hb);






	SelectObject(sorDC, hBox1);
	GetObject(hBox1, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	nTotal_Width += bx;
	by = bit.bmHeight;
	BitBlt(destdc, x, y, bx, by, sorDC, 0, 0, SRCCOPY);

	for(i = 0; i < x_width; i++)
	{
		SelectObject(sorDC, hBox2);
		GetObject(hBox2, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		nTotal_Width += bx;
		by = bit.bmHeight;
		StretchBlt(destdc, x + BOXCORNER_WIDTH + (bx*i), y, bx, by, sorDC, 0, 0, bx, by, SRCCOPY);
	}



	SelectObject(sorDC, hBox3);
	GetObject(hBox3, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;
	StretchBlt(destdc, x + nTotal_Width, y, bx, by, sorDC, 0, 0, bx, by, SRCCOPY);




	for(i = 0; i < y_height; i++)
	{
		SelectObject(sorDC, hBox4);
		GetObject(hBox4, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		nTotal_Height += by;
		StretchBlt(destdc, x, y + BOXCORNER_HEIGHT + (by*i), bx, by, sorDC, 0, 0, bx, by, SRCCOPY);
	}






	SelectObject(sorDC, hBox7);
	GetObject(hBox7, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	StretchBlt(destdc, x, y + BOXCORNER_HEIGHT + nTotal_Height, bx, by, sorDC, 0, 0, bx, by, SRCCOPY);

	for(i = 0; i < x_width; i++)
	{
		SelectObject(sorDC, hBox8);
		GetObject(hBox8, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		StretchBlt(destdc, x + BOXCORNER_WIDTH + (bx*i), y + BOXCORNER_HEIGHT + nTotal_Height, bx, by, sorDC, 0, 0, bx, by, SRCCOPY);
	}


	SelectObject(sorDC, hBox9);
	GetObject(hBox9, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;
	StretchBlt(destdc, x + nTotal_Width, y + BOXCORNER_HEIGHT + nTotal_Height, bx, by, sorDC, 0, 0, bx, by, SRCCOPY);



	for(i = 0; i < y_height; i++)
	{
		SelectObject(sorDC, hBox6);
		GetObject(hBox6, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		StretchBlt(destdc, x + nTotal_Width, y + BOXCORNER_HEIGHT + (by*i), bx, by, sorDC, 0, 0, bx, by, SRCCOPY);
	}


	DeleteDC(sorDC);
	DeleteDC(destdc);

	ReleaseDC(g_hwnd, hdc);


#endif

	return TRUE;
}

void CLAN_MENU::RenderMenu()
{

}


void CLAN_MENU::Draw_C_menuN()
{
	cBaseMenu.Draw();
	cClanChip.Draw();
	cClanUser.Draw();
	cClanMake.Draw();
	cClanReport.Draw();
#ifdef USE_PROSTONTALE		
#else
	cClanChatting.Draw();
#endif
	cClanJoin.Draw();

}







void SetUserData2(char* id, char* chaname, char* gserver)
{
	strcpy(cldata.szID, id);
	strcpy(cldata.ChaName, chaname);
	strcpy(cldata.gserver, gserver);

}


void CLAN_MENU::SetUserData(char* id, char* chaname, char* gserver, int money, int ability)
{
	strcpy(cldata.szID, id);
	strcpy(cldata.ChaName, chaname);
	strcpy(cldata.gserver, gserver);

	cldata.money = money;


	cldata.ability = ability;
}




void CLAN_MENU::SetJoinData(char *joinclanname, char *joinclanchip)
{
	strcpy(cldata.szJoinClanName, joinclanname);
	strcpy(cldata.szJoinClanChipName, joinclanchip);
}











#ifdef USE_PROSTONTALE		

void DrawSprite_TJB(int winX, int winY, int winxlen, int winylen, LPDIRECT3DTEXTURE9 pdds, int x, int y, int width, int height, int Bltflag)
{
	if(!pdds)
		return;
}
#endif




#ifdef USE_PROSTONTALE		
#else

void Draw_Text(int x, int y, char *str)
{
	char strbuf[1024];


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt = 0;
	int i = 0;

	while(1)
	{
		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')
		{
			strbuf[i] = 0;
			i = 0;
		jmp1:

			dsTextLineOut( x, y, strbuf, lstrlen(strbuf));

			ZeroMemory(strbuf, sizeof(strbuf));
			y += 16;

			if(cnt >= strL) break;
		}
		else if(cnt >= strL)
		{
			goto jmp1;
		}
		else
		{
			i++;
		}
	}


}
#endif



void Text_Out1(HDC hdc, int x, int y, char *str)
{
}

void Text_Out2(HDC hdc, int x, int y, char *str)
{
}

void Text_Out3(HDC hdc, int x, int y, char *str)
{
}
void Text_Out(HDC hdc, int x, int y, char *str)
{
	char strbuf[1024];


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt = 0;
	int i = 0;

	while(1)
	{
		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')
		{
			strbuf[i] = 0;
			i = 0;
		jmp1:

			dsTextLineOut( x, y, strbuf, lstrlen(strbuf));

			ZeroMemory(strbuf, sizeof(strbuf));
			y += 16;

			if(cnt >= strL) break;
		}
		else if(cnt >= strL)
		{
			goto jmp1;
		}
		else
		{
			i++;
		}
	}

}



void CLAN_MENU::Load()
{
#ifdef USE_PROSTONTALE		

	MatPartyBackGround =
		CreateTextureMaterial("image\\Sinimage\\Help\\party_win.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);




	hBox1 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox2 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox3 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box3.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox4 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box4.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	hBox5 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box5.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox6 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box6.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox7 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box7.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox8 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box8.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hBox9 =
		CreateTextureMaterial("image\\Sinimage\\Help\\box9.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);






#else


	MatPartyBackGround = (HBITMAP)LoadImage(
		NULL,
		"image\\Sinimage\\Help\\box-test-title2.bmp",
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE);



	hBox1 = (HBITMAP)LoadImage(NULL, "image\\clanimage\\MessageBox\\box1.bmp",
							   IMAGE_BITMAP,
							   0, 0,
							   LR_LOADFROMFILE);

	hBox2 = (HBITMAP)LoadImage(NULL, "image\\clanimage\\MessageBox\\box2.bmp",
							   IMAGE_BITMAP,
							   0, 0,
							   LR_LOADFROMFILE);
	hBox3 = (HBITMAP)LoadImage(NULL, "image\\clanimage\\MessageBox\\box3.bmp",
							   IMAGE_BITMAP,
							   0, 0,
							   LR_LOADFROMFILE);
	hBox4 = (HBITMAP)LoadImage(NULL, "image\\clanimage\\MessageBox\\box4.bmp",
							   IMAGE_BITMAP,
							   0, 0,
							   LR_LOADFROMFILE);

	hBox6 = (HBITMAP)LoadImage(NULL, "image\\clanimage\\MessageBox\\box6.bmp",
							   IMAGE_BITMAP,
							   0, 0,
							   LR_LOADFROMFILE);
	hBox7 = (HBITMAP)LoadImage(NULL, "image\\clanimage\\MessageBox\\box7.bmp",
							   IMAGE_BITMAP,
							   0, 0,
							   LR_LOADFROMFILE);

	hBox8 = (HBITMAP)LoadImage(NULL, "image\\clanimage\\MessageBox\\box8.bmp",
							   IMAGE_BITMAP,
							   0, 0,
							   LR_LOADFROMFILE);
	hBox9 = (HBITMAP)LoadImage(NULL, "image\\clanimage\\MessageBox\\box9.bmp",
							   IMAGE_BITMAP,
							   0, 0,
							   LR_LOADFROMFILE);






	hOk_Gray = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\MessageBox\\Button_Ok_Glay.bmp",
								  IMAGE_BITMAP,
								  0, 0,
								  LR_LOADFROMFILE);

	hOk_Yellow = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\MessageBox\\Button_Ok_Yellow.bmp",
									IMAGE_BITMAP,
									0, 0,
									LR_LOADFROMFILE);


	if(hOk_Yellow == NULL)
	{
		char temp[50];
		wsprintf(temp, "Num : %d", GetLastError());
	}

	hCancel_Gray = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\MessageBox\\Button_Cancel_Glay.bmp",
									  IMAGE_BITMAP,
									  0, 0,
									  LR_LOADFROMFILE);

	hCancel_Yellow = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\MessageBox\\Button_Cancel_Yellow.bmp",
										IMAGE_BITMAP,
										0, 0,
										LR_LOADFROMFILE);
	hYes_Gray = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\MessageBox\\Button_Yes_Glay.bmp",
								   IMAGE_BITMAP,
								   0, 0,
								   LR_LOADFROMFILE);
	hYes_Yellow = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\MessageBox\\Button_Yes_Yellow.bmp",
									 IMAGE_BITMAP,
									 0, 0,
									 LR_LOADFROMFILE);

	hNo_Gray = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\MessageBox\\Button_No_Glay.bmp",
								  IMAGE_BITMAP,
								  0, 0,
								  LR_LOADFROMFILE);

	hNo_Yellow = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\MessageBox\\Button_No_Yellow.bmp",
									IMAGE_BITMAP,
									0, 0,
									LR_LOADFROMFILE);









	hClanName = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\Help\\box-test-title.bmp",
								   IMAGE_BITMAP,
								   0, 0,
								   LR_LOADFROMFILE);
	hWareHouse[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\whc.bmp",
									   IMAGE_BITMAP,
									   0, 0,
									   LR_LOADFROMFILE);
	hWareHouse[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\whc1.bmp",
									   IMAGE_BITMAP,
									   0, 0,
									   LR_LOADFROMFILE);
	hWHRight[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\whr.bmp",
									 IMAGE_BITMAP,
									 0, 0,
									 LR_LOADFROMFILE);
	hWHRight[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\whr1.bmp",
									 IMAGE_BITMAP,
									 0, 0,
									 LR_LOADFROMFILE);
	hClanMark[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\m.bmp",
									  IMAGE_BITMAP,
									  0, 0,
									  LR_LOADFROMFILE);
	hClanMark[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\m1.bmp",
									  IMAGE_BITMAP,
									  0, 0,
									  LR_LOADFROMFILE);
	hRemove[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\r.bmp",
									IMAGE_BITMAP,
									0, 0,
									LR_LOADFROMFILE);
	hRemove[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\r1.bmp",
									IMAGE_BITMAP,
									0, 0,
									LR_LOADFROMFILE);
	hClanRelease[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\cr.bmp",
										 IMAGE_BITMAP,
										 0, 0,
										 LR_LOADFROMFILE);
	hClanRelease[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\cr1.bmp",
										 IMAGE_BITMAP,
										 0, 0,
										 LR_LOADFROMFILE);
	hHelp[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\h.bmp",
								  IMAGE_BITMAP,
								  0, 0,
								  LR_LOADFROMFILE);
	hHelp[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\h1.bmp",
								  IMAGE_BITMAP,
								  0, 0,
								  LR_LOADFROMFILE);
	hOut[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\MessageBox\\o.bmp",
								 IMAGE_BITMAP,
								 0, 0,
								 LR_LOADFROMFILE);
	hOut[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\MessageBox\\o1.bmp",
								 IMAGE_BITMAP,
								 0, 0,
								 LR_LOADFROMFILE);


	hSecession[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\s.bmp",
									   IMAGE_BITMAP,
									   0, 0,
									   LR_LOADFROMFILE);

	hSecession[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\s1.bmp",
									   IMAGE_BITMAP,
									   0, 0,
									   LR_LOADFROMFILE);

	hIcon = (HBITMAP)LoadImage(NULL, "image\\party\\party_man_0.bmp",
							   IMAGE_BITMAP,
							   0, 0,
							   LR_LOADFROMFILE);
	hIcon_Click = (HBITMAP)LoadImage(NULL, "image\\party\\party_man_1.bmp",
									 IMAGE_BITMAP,
									 0, 0,
									 LR_LOADFROMFILE);

	hRemoveToMenu[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\MessageBox\\Button_deport_Glay.bmp",
										  IMAGE_BITMAP,
										  0, 0,
										  LR_LOADFROMFILE);

	hRemoveToMenu[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\MessageBox\\Button_deport_Yellow.bmp",
										  IMAGE_BITMAP,
										  0, 0,
										  LR_LOADFROMFILE);

	hClose[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\MessageBox\\c.bmp",
								   IMAGE_BITMAP,
								   0, 0,
								   LR_LOADFROMFILE);

	hClose[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\MessageBox\\c1.bmp",
								   IMAGE_BITMAP,
								   0, 0,
								   LR_LOADFROMFILE);

	hHelp1 = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\chipbutton\\help1.bmp",
								IMAGE_BITMAP,
								0, 0,
								LR_LOADFROMFILE);

	hButton_Box = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\msBox.bmp",
									 IMAGE_BITMAP,
									 0, 0,
									 LR_LOADFROMFILE);
	hClanTitle = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\title.bmp",
									IMAGE_BITMAP,
									0, 0,
									LR_LOADFROMFILE);
	hScl_Bar = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\scl_bar.bmp",
								  IMAGE_BITMAP,
								  0, 0,
								  LR_LOADFROMFILE);
	hScl_icon = (HBITMAP)LoadImage(NULL, "image\\Sinimage\\help\\scl_icon.bmp",
								   IMAGE_BITMAP,
								   0, 0,
								   LR_LOADFROMFILE);

#ifndef _LANGUAGE_BRAZIL 
	hTxt_Remove[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\txt_r_.bmp",
										IMAGE_BITMAP,
										0, 0,
										LR_LOADFROMFILE);

	hTxt_Remove[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\txt_r.bmp",
										IMAGE_BITMAP,
										0, 0,
										LR_LOADFROMFILE);

	hTxt_Release[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\txt_cr_.bmp",
										 IMAGE_BITMAP,
										 0, 0,
										 LR_LOADFROMFILE);

	hTxt_Release[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\txt_cr.bmp",
										 IMAGE_BITMAP,
										 0, 0,
										 LR_LOADFROMFILE);
#endif

	hTxt_Mark[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\txt_m_.bmp",
									  IMAGE_BITMAP,
									  0, 0,
									  LR_LOADFROMFILE);

	hTxt_Mark[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\txt_m.bmp",
									  IMAGE_BITMAP,
									  0, 0,
									  LR_LOADFROMFILE);

	hTxt_Help[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\txt_h_.bmp",
									  IMAGE_BITMAP,
									  0, 0,
									  LR_LOADFROMFILE);

	hTxt_Help[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\txt_h.bmp",
									  IMAGE_BITMAP,
									  0, 0,
									  LR_LOADFROMFILE);

	hTxt_Secession[0] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\txt_out_.bmp",
										   IMAGE_BITMAP,
										   0, 0,
										   LR_LOADFROMFILE);

	hTxt_Secession[1] = (HBITMAP)LoadImage(NULL, "image\\clanImage\\chipbutton\\txt_out.bmp",
										   IMAGE_BITMAP,
										   0, 0,
										   LR_LOADFROMFILE);







#endif
}




void clanMENU_close()
{
	Interface_clanmenu.Close();
}

void CLAN_MENU::Close()
{
#ifdef USE_PROSTONTALE		





	if(cldata.hClanMark)
	{
		cldata.hClanMark->Release(); cldata.hClanMark = NULL;
	}
	if(cldata.hClanMark16)
	{
		cldata.hClanMark16->Release(); cldata.hClanMark16 = NULL;
	}

	cClanChatting.Close();
	cBaseMenu.Close();


#else


	DeleteObject(MatPartyBackGround);



	DeleteObject(hOk_Gray);
	DeleteObject(hOk_Yellow);
	DeleteObject(hCancel_Gray);
	DeleteObject(hCancel_Yellow);
	DeleteObject(hYes_Yellow);
	DeleteObject(hYes_Gray);
	DeleteObject(hNo_Gray);
	DeleteObject(hNo_Yellow);
	DeleteObject(hMark);
	DeleteObject(hClanName);
	DeleteObject(hScl_Bar);
	DeleteObject(hScl_icon);


	for(int i = 0; i < 2; i++)
	{
		DeleteObject(hWHRight[i]);
		DeleteObject(hWareHouse[i]);
		DeleteObject(hClanMark[i]);
		DeleteObject(hRemove[i]);
		DeleteObject(hClanRelease[i]);
		DeleteObject(hHelp[i]);
		DeleteObject(hOut[i]);
		DeleteObject(hClose[i]);
		DeleteObject(hSecession[i]);
	#ifndef _LANGUAGE_BRAZIL 
		DeleteObject(hTxt_Remove[i]);
		DeleteObject(hTxt_Release[i]);
	#endif
		DeleteObject(hTxt_Mark[i]);
		DeleteObject(hTxt_Help[i]);
		DeleteObject(hTxt_Secession[i]);
	}



	DeleteObject(hIcon);
	DeleteObject(hHelp1);



#endif
#ifdef VOICE_CHAT
	g_CtrlProcess.Clear();
#endif
}

void CLAN_MENU::Loading()
{
#ifdef USE_PROSTONTALE		
	Draw_C_Text(clanLoading.szMsg, BackStartPos.x + 80, BackStartPos.y + 90);
#else

	HDC hdc, sorDC, destdc;

	hdc = GetDC(g_hwnd);
	sorDC = CreateCompatibleDC(hdc);
	destdc = CreateCompatibleDC(hdc);
	SelectObject(destdc, Dback.hb);


	DeleteDC(sorDC);
	DeleteDC(destdc);
	ReleaseDC(g_hwnd, hdc);
#endif

}


#ifdef USE_PROSTONTALE		

int SendClanCommandUser(smWINSOCK *lpsmSock, DWORD	dwCode, int Param1, int Param2, CLANWONLIST *lpClanUserList, int ClanUserCount);
#endif


void SetClanWon()
{

	if(cldata.nTotalClanWonCount == 0) return;

	memcpy(ClanWonList.clanWon, cldata.clanWon, sizeof(cldata.clanWon));





#ifdef USE_PROSTONTALE		



	SendClanCommandUser(smWsockDataServer, OpCode::OPCODE_CLAN_UPDATE, 0, 0, &ClanWonList, cldata.nTotalClanWonCount);


#endif

}






BOOL SearchDirectory(char *dir)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	char t[50];
	wsprintf(t, "%s\\*.*", dir);
	hFind = FindFirstFile(t, &wfd);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	return TRUE;
}

void MakeDirectory(char *dir)
{
	CreateDirectory(dir, NULL);
}


void CreateSaveData_dir()
{
	char szTemp[100];
	if(!SearchDirectory(SAVEDATA_DIR)) MakeDirectory(SAVEDATA_DIR);
	if(!SearchDirectory(CLANDATA_DIR)) MakeDirectory(CLANDATA_DIR);

	ZeroMemory(szTemp, sizeof(szTemp));
	wsprintf(szTemp, "%s", CLANDATA_DIR);
	wsprintf(szTemp, "%s\\%s", szTemp, szConnServerName);

	if(!SearchDirectory(szTemp)) MakeDirectory(szTemp);

}











#define CLANMESSAGE_DIR "image/clanImage/Help/clanText.msg"

int LoadClanMessage()
{
	char *g_ClanMessage;


	HANDLE hFile = NULL;
	DWORD dwFileSize;
	DWORD dwRead = 0;
	char c;
	c = '\n';
	hFile = CreateFile(CLANMESSAGE_DIR, GENERIC_READ, FILE_SHARE_READ,
					   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL) return -1;

	dwFileSize = GetFileSize(hFile, NULL);

	g_ClanMessage = new char[dwFileSize];

	ReadFile(hFile, g_ClanMessage, dwFileSize, &dwRead, NULL);
	CloseHandle(hFile);

	int ReadMessage(char *save, char *savename, char *readbuf);

	ReadMessage(clanMake1.szMsg, "szMsg1", g_ClanMessage);
	CheckMsgPos(&clanMake1, BOX_MAX_WIDTH, 0);
	ReadMessage(clanMake2.szMsg, "szMsg2", g_ClanMessage);
	CheckMsgPos(&clanMake2, BOX_MAX_WIDTH, 0);
	ReadMessage(clanMake4.szMsg, "szMsg4", g_ClanMessage);
	CheckMsgPos(&clanMake4, BOX_MAX_WIDTH, 0);
	ReadMessage(clanMake5.szMsg, "szMsg5", g_ClanMessage);
	CheckMsgPos(&clanMake5, BOX_MAX_WIDTH, 0);
	ReadMessage(clanMake6.szMsg, "szClanMakeFinishMsg", g_ClanMessage);
	CheckMsgPos(&clanMake6, BOX_MAX_WIDTH, 0);


	ReadMessage(szMsg3, "szMsg3", g_ClanMessage);

	ReadMessage(clanMsg21.szMsg, "szMsg21", g_ClanMessage);
	CheckMsgPos(&clanMsg21, BOX_MAX_WIDTH, 0);

	ReadMessage(clanMsg254.szMsg, "szMsg254", g_ClanMessage);
	CheckMsgPos(&clanMsg254, BOX_MAX_WIDTH, 0);
	ReadMessage(clanMsg15.szMsg, "szMsg15", g_ClanMessage);
	CheckMsgPos(&clanMsg15, BOX_MAX_WIDTH, 0);
	ReadMessage(clanJoin.szMsg, "szJoin", g_ClanMessage);
	CheckMsgPos(&clanJoin, BOX_MAX_WIDTH, 0);
	ReadMessage(clanSecession.szMsg, "szSecession", g_ClanMessage);
	CheckMsgPos(&clanSecession, BOX_MAX_WIDTH, 0);
	ReadMessage(clanServerConnectErrorMsg.szMsg, "szServerConnectErrorMsg", g_ClanMessage);
	CheckMsgPos(&clanServerConnectErrorMsg, BOX_MAX_WIDTH, 0);
	ReadMessage(clanszError_Msg.szMsg, "szError_Msg", g_ClanMessage);
	CheckMsgPos(&clanszError_Msg, BOX_MAX_WIDTH, 0);
	ReadMessage(clanCancelMakeClan.szMsg, "szCancelMakeClan", g_ClanMessage);
	CheckMsgPos(&clanCancelMakeClan, BOX_MAX_WIDTH, 0);
	ReadMessage(clanClanNameError.szMsg, "szClanNameError", g_ClanMessage);
	CheckMsgPos(&clanClanNameError, BOX_MAX_WIDTH, 0);























	ReadMessage(clanSecession6DownMsg.szMsg, "szSecession6DownMsg", g_ClanMessage);
	CheckMsgPos(&clanSecession6DownMsg, BOX_MAX_WIDTH, 0);



	ReadMessage(clanClanJoinMsg.szMsg, "szClanJoinMsg", g_ClanMessage);
	CheckMsgPos(&clanClanJoinMsg, BOX_MAX_WIDTH, 0);





	ReadMessage(clanClanJoinCancelMsg.szMsg, "szClanJoinCancelMsg", g_ClanMessage);
	CheckMsgPos(&clanClanJoinCancelMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanClanJoinsucesssMsg.szMsg, "szClanJoinsucesssMsg", g_ClanMessage);
	CheckMsgPos(&clanClanJoinsucesssMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanszReMoveClanWonMsg.szMsg, "szReMoveClanWonMsg", g_ClanMessage);
	CheckMsgPos(&clanszReMoveClanWonMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanReMoveHeaderMsg.szMsg, "szReMoveHeaderMsg", g_ClanMessage);
	CheckMsgPos(&clanReMoveHeaderMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanszReConfReleaseMsg.szMsg, "szReConfReleaseMsg", g_ClanMessage);
	CheckMsgPos(&clanszReConfReleaseMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanNoRecordReleaseMsg.szMsg, "szNoRecordReleaseMsg", g_ClanMessage);
	CheckMsgPos(&clanNoRecordReleaseMsg, BOX_MAX_WIDTH, 0);


	ReadMessage(clanFinishReleaseMsg.szMsg, "szFinishReleaseMsg", g_ClanMessage);
	CheckMsgPos(&clanFinishReleaseMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanSecessionMsg.szMsg, "szSecessionMsg", g_ClanMessage);
	CheckMsgPos(&clanSecessionMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanFinishSecessionMsg.szMsg, "szFinishSecessionMsg", g_ClanMessage);
	CheckMsgPos(&clanFinishSecessionMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanisCheckClanJangErrorMsg.szMsg, "szisCheckClanJangErrorMsg", g_ClanMessage);
	CheckMsgPos(&clanisCheckClanJangErrorMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanMoneyErrorMsg.szMsg, "szMoneyErrorMsg", g_ClanMessage);
	CheckMsgPos(&clanMoneyErrorMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanAbilityErrorMsg.szMsg, "szAbilityErrorMsg", g_ClanMessage);
	CheckMsgPos(&clanAbilityErrorMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanszRemoveShortClanWonMsg.szMsg, "szRemoveShortClanWonMsg", g_ClanMessage);
	CheckMsgPos(&clanszRemoveShortClanWonMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanRemoveShowrtClanWonResultMsg.szMsg, "szRemoveShowrtClanWonResultMsg", g_ClanMessage);
	CheckMsgPos(&clanRemoveShowrtClanWonResultMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanNoName.szMsg, "szNoName", g_ClanMessage);
	CheckMsgPos(&clanNoName, BOX_MAX_WIDTH, 0);

	ReadMessage(clanLoading.szMsg, "szLoading", g_ClanMessage);
	CheckMsgPos(&clanLoading, BOX_MAX_WIDTH, 0);

	ReadMessage(clanMsg6.szMsg, "szMsg6", g_ClanMessage);
	CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);




	ReadMessage(szDeleteChaReleaseBefore, "szDeleteChaReleaseBefore", g_ClanMessage);
	ReadMessage(szDeleteChaReleaseFinish, "szDeleteChaReleaseFinish", g_ClanMessage);
	ReadMessage(szDeleteChaSecessionBefore, "szDeleteChaSecessionBefore", g_ClanMessage);
	ReadMessage(szDeleteChaSecessionFinish, "szDeleteChaSecessionFinish", g_ClanMessage);


	ReadMessage(clanDeleteChaError.szMsg, "szDeleteChaError", g_ClanMessage);
	CheckMsgPos(&clanDeleteChaError, BOX_MAX_WIDTH, 0);

	ReadMessage(clanMakeFinishClan.szMsg, "szMakeFinishClan", g_ClanMessage);
	CheckMsgPos(&clanMakeFinishClan, BOX_MAX_WIDTH, 0);


	ReadMessage(szClanWon6Down, "szClanWon6Down", g_ClanMessage);

	ReadMessage(clanClanUserNoMakeMsg.szMsg, "szClanUserNoMakeMsg", g_ClanMessage);
	CheckMsgPos(&clanClanUserNoMakeMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanMakeFinishClanWon.szMsg, "szMakeFinishClanWon", g_ClanMessage);
	CheckMsgPos(&clanMakeFinishClanWon, BOX_MAX_WIDTH, 0);

	ReadMessage(clanClanServerInspect.szMsg, "ClanServerInspect", g_ClanMessage);
	CheckMsgPos(&clanClanServerInspect, BOX_MAX_WIDTH, 0);

	ReadMessage(clanClanUserRelease.szMsg, "szClanUserRelease", g_ClanMessage);
	CheckMsgPos(&clanClanUserRelease, BOX_MAX_WIDTH, 0);




	ReadMessage(clanClanMakedowninfo.szMsg, "szClanMakedowninfo", g_ClanMessage);
	CheckMsgPos(&clanClanMakedowninfo, BOX_MAX_WIDTH, 0);

	ReadMessage(clanClanUserReleaseMsg.szMsg, "szClanUserReleaseMsg", g_ClanMessage);
	CheckMsgPos(&clanClanUserReleaseMsg, BOX_MAX_WIDTH, 0);

	ReadMessage(clanClanUserRemove.szMsg, "szClanUserRemove", g_ClanMessage);
	CheckMsgPos(&clanClanUserRemove, BOX_MAX_WIDTH, 0);

	ReadMessage(clanClanWonOver.szMsg, "szClanWonOver", g_ClanMessage);
	CheckMsgPos(&clanClanWonOver, BOX_MAX_WIDTH, 0);


	ReadMessage(clanMsg7.szMsg, "szMsg7", g_ClanMessage);
	CheckMsgPos(&clanMsg7, BOX_MAX_WIDTH, 0);

	ReadMessage(clanNoLevel.szMsg, "szNoLevel", g_ClanMessage);
	CheckMsgPos(&clanNoLevel, BOX_MAX_WIDTH, 0);

	ReadMessage(clanRemoveSecond.szMsg, "szRemoveSecond", g_ClanMessage);
	CheckMsgPos(&clanRemoveSecond, BOX_MAX_WIDTH, 0);

	ReadMessage(clanRemoveSecondResult.szMsg, "szRemoveSecondResult", g_ClanMessage);
	CheckMsgPos(&clanRemoveSecondResult, BOX_MAX_WIDTH, 0);

	ReadMessage(LeaveClanConfirm.szMsg, "szLeaveClanConfirm", g_ClanMessage);
	CheckMsgPos(&LeaveClanConfirm, BOX_MAX_WIDTH, 0);

	ReadMessage(LeaveClanNoMoney.szMsg, "szLeaveClanNoMoney", g_ClanMessage);
	CheckMsgPos(&LeaveClanNoMoney, BOX_MAX_WIDTH, 0);

	ReadMessage(LeaveClanSuccess.szMsg, "szLeaveClanSuccess", g_ClanMessage);
	CheckMsgPos(&LeaveClanSuccess, BOX_MAX_WIDTH, 0);

	ReadMessage(LeaveClanNoLevel.szMsg, "szLeaveClanNoLevel", g_ClanMessage);
	CheckMsgPos(&LeaveClanNoLevel, BOX_MAX_WIDTH, 0);

	ReadMessage(LeaveClanReConfirm.szMsg, "szLeaveClanReConfirm", g_ClanMessage);
	CheckMsgPos(&LeaveClanReConfirm, BOX_MAX_WIDTH, 0);

	ReadMessage(NoLeaveClan.szMsg, "szNoLeaveClan", g_ClanMessage);
	CheckMsgPos(&NoLeaveClan, BOX_MAX_WIDTH, 0);

	ReadMessage(LeaveClanMessage.szMsg, "szLeaveClanMessage", g_ClanMessage);
	CheckMsgPos(&LeaveClanMessage, BOX_MAX_WIDTH, 0);

	ReadMessage(LeaveClanDownLevel.szMsg, "szLeaveClanDownLevel", g_ClanMessage);
	CheckMsgPos(&LeaveClanDownLevel, BOX_MAX_WIDTH, 0);

	ReadMessage(SubChipAppoint.szMsg, "szSubChipAppoint", g_ClanMessage);
	CheckMsgPos(&SubChipAppoint, BOX_MAX_WIDTH, 0);

	ReadMessage(SubChipAppointEnd.szMsg, "szSubChipAppointEnd", g_ClanMessage);
	CheckMsgPos(&SubChipAppointEnd, BOX_MAX_WIDTH, 0);

	ReadMessage(SubChipRelease.szMsg, "szSubChipRelease", g_ClanMessage);
	CheckMsgPos(&SubChipRelease, BOX_MAX_WIDTH, 0);

	ReadMessage(SubChipReleaseEnd.szMsg, "szSubChipReleseEnd", g_ClanMessage);
	CheckMsgPos(&SubChipReleaseEnd, BOX_MAX_WIDTH, 0);

	ReadMessage(NoSubChip.szMsg, "szNoSubChip", g_ClanMessage);
	CheckMsgPos(&NoSubChip, BOX_MAX_WIDTH, 0);



	ReadMessage(ClanIs4DayCheckMsg.szMsg, "szClanIs4DayCheckMsg", g_ClanMessage);
	CheckMsgPos(&ClanIs4DayCheckMsg, BOX_MAX_WIDTH, 0);






	delete[] g_ClanMessage;
	g_ClanMessage = NULL;
	return 1;
}

int ReadMessage(char *save, char *savename, char *readbuf)
{
	char szTemp[256];
	char *pBuf;
	char szReadData[1024];
	int nCount = 0;
	int nCount1 = 0;
	BOOL bFlag = FALSE;

	ZeroMemory(szReadData, sizeof(szReadData));
	wsprintf(szTemp, "*%s", savename);

	pBuf = strstr(readbuf, szTemp);
	if(pBuf == NULL)
	{
		return -1;
	}

	pBuf = pBuf + strlen(szTemp) + 2;
	nCount = (int)(pBuf - readbuf);

	if(readbuf[nCount] == 0x0a)
	{
		nCount++;
	}


	while(1)
	{
		if((readbuf[nCount] == 0x5c))
		{
			szReadData[nCount1] = '\n';
			nCount1++;
			nCount += 3;
			if(readbuf[nCount] == 0x0a)
			{
				nCount++;
				continue;
			}

		}
		if((readbuf[nCount] == 0x0d) || (readbuf[nCount] == 0x0a)) break;
		szReadData[nCount1] = readbuf[nCount];
		nCount++;
		nCount1++;

	}

	strcpy(save, szReadData);
	return 1;
}




void MsgXsu_Ysu(CLANMSG* clanmsg, int *xsu, int *ysu)
{
	char strbuf[256], strbuf2[256];
	ZeroMemory(strbuf, sizeof(strbuf));

	int nCount = 0;
	int maxXsu = 0;
	int cntX = 0, cntY = 0;

	while(1)
	{
		strbuf[cntX] = clanmsg->szMsg[nCount];

		if(clanmsg->szMsg[nCount] == '\n')
		{
			strbuf[cntX] = 0;
			if(cntX > maxXsu)
			{
				maxXsu = cntX;
				strcpy(strbuf2, strbuf);
			}

			cntY++;
			cntX = -1;
		}

		if(clanmsg->szMsg[nCount] == 0x00)
		{
			strbuf[cntX] = 0;
			if(cntX > maxXsu)
			{
				maxXsu = cntX;
				strcpy(strbuf2, strbuf);
			}
			cntY++;
			break;
		}


		cntX++;
		nCount += 1;
	}

	*xsu = maxXsu;
	*ysu = cntY;
}



void CheckMsgPos(CLANMSG* clanmsg, int width, int height)
{
	int nCount = 0;
	int nXMax = 0, nYMax;
	int nX = 0;

	nX = width;
	nX = nX / 2;
	int nY = 40;

	MsgXsu_Ysu(clanmsg, &nXMax, &nYMax);
	int strDotlen = nXMax * 6;
	strDotlen /= 2;

	if(nYMax == 1) nY = 80;
	if(nYMax == 2) nY = 60;

	clanmsg->pos.x = (nX - strDotlen);
	clanmsg->pos.y = nY;
}



int g_nCount = 0;
void DebugMessage(char* msg, ...)
{
#define DEBUG_MSG_MAX 4096
	HANDLE hFile;
	char buff[DEBUG_MSG_MAX];
	char szDebugMsg[5120];
	DWORD dwWrite = 0;
	int nMsgStrOver = 0;
	SYSTEMTIME	SystemTime;


	va_list args;

	va_start(args, msg);
	vsprintf(buff, msg, args);
	va_end(args);





	GetLocalTime(&SystemTime);

	hFile = CreateFile("ClanDebug.txt", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	wsprintf(szDebugMsg, "%d.%d³â%d¿ù%dÀÏ : %s\r\n", g_nCount++,
			 SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, buff);


	if(hFile != INVALID_HANDLE_VALUE)
	{
		SetFilePointer(hFile, 0, NULL, FILE_END);

		WriteFile(hFile, szDebugMsg, lstrlen(szDebugMsg), &dwWrite, NULL);
		if(lstrlen(buff) > DEBUG_MSG_MAX - 2)
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);
			char szMsg[256] = "..\n¸Þ½ÃÁö°¡ ³Ê¹«±æ¾î¼­ Àß¶úÀ½";
			WriteFile(hFile, szMsg, lstrlen(szMsg), &dwWrite, NULL);
		}



	}


	if(hFile) CloseHandle(hFile);
}


#define DEBUGOPTION  "DDD2.txt"
BOOL	g_bDebugOption = FALSE;
void ReadWEBDebugOption()
{
	HANDLE hFile = NULL;
	DWORD dwRead;
	char DebugOption;
	hFile = CreateFile(DEBUGOPTION, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, &DebugOption, 1, &dwRead, NULL);
		CloseHandle(hFile);

		DebugOption = '1';
	}
	else
	{





		DebugOption = '0';
	}
	if(DebugOption == '1') g_bDebugOption = TRUE;
	else g_bDebugOption = FALSE;
}

