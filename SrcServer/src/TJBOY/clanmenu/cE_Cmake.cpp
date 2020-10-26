#define CE_CMAKE_CPP

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		

#include "sinbaram\\SinLinkHeader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "Language\\language.h"
#include "Language\\jts.h"
#include "HoBaram\\HoTextFile.h"
#endif

#include "tjclan.h"
#include "cE_Cmake.h"
#include "cE_report.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "..\\ygy\\ygyheader.h"
#include "CurseFilter.h"	


int usehFocus = 0;
int oldLIMITchattingWnd = 0;
extern char	szConnServerName[16];
extern int g_ClanMakeMoney;



CLANEntity_make::CLANEntity_make()
{
	m_bEventClanMoney = false;
}
CLANEntity_make::~CLANEntity_make()
{

}



int CLANEntity_make::Init(int Life)
{
	life = Life;
	ZeroMemory(szClanMakeMsg, sizeof(szClanMakeMsg));
	return 1;
}

int CLANEntity_make::Clear()
{
	return 1;
}



void CLANEntity_make::Main()
{
	char szFile[256];
	char szFile2[256];
	char server;
	char UniqueClanMark[64];
	int  nMoney = 500000;
	if(life == 0) return;

	int i;
	switch(C_menuN)
	{
		case CLAN_ABILITYDOWN:
		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		if(MOUSE0())
		{
			MOUSE0() = 0;
			i = i;
			switch(i)
			{
				case 0:
				C_menuN = CLAN_AllEnd;



				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLANMAKE_REAMMAKR_ERROR:
		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		if(MOUSE0())
		{
			MOUSE0() = 0;
			i = i;
			switch(i)
			{
				case 0:
				C_menuN = CLAN_AllEnd;



				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLAN_GO_MAKE:
		C_menuN = CLAN_isCheckClanJang;
		menuInit(C_menuN);
		C_menuN2 = 1;
		break;
		case CLAN_isCheckClanJang_LOADING:
		if(ANSdata.ret_val != -1) C_menuN = CLAN_isCheckClanJang;
		break;



		case CLAN_isCheckClanJang:
		switch(C_menuN2)
		{
			case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();
			WebDB.isCheckClanJang(cldata.szID, cldata.gserver);
			C_menuN2 = 2;
			break;
			case 2:






			switch(ANSdata.ret_val)
			{
				case -1:


				break;
				case 1:
				WebDB.Suspend();
				C_menuN2 = 0;


				C_menuN = CLAN_isCheckClanJang_Result;
				menuInit(C_menuN);

				break;
				case 0:
				WebDB.Suspend();
				C_menuN2 = 0;
				C_menuN = CLAN_MAKE_is;
				menuInit(C_menuN);

				cldata.myPosition = CLANNO_REGESTER;
				ZeroMemory(cldata.name, sizeof(cldata.name));
				ZeroMemory(cldata.explanation, sizeof(cldata.explanation));
				ZeroMemory(cldata.ClanZang_Name, sizeof(cldata.ClanZang_Name));
				ZeroMemory(cldata.ClanMark, sizeof(cldata.ClanMark));
				cldata.intClanMark = 0;
				ZeroMemory(cldata.PFlag, sizeof(cldata.PFlag));


				break;

				case 100:

				WebDB.Suspend();
				C_menuN2 = 0;


				wsprintf(szErrorMsg, "%s (1)", clanszError_Msg.szMsg);
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();

				wsprintf(szErrorMsg, "%s (0)", clanszError_Msg.szMsg);
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;

				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN2 = 0;

					wsprintf(szErrorMsg, "%s (2)", clanszError_Msg.szMsg);
					C_menuN = CLAN_ERROR;
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;
				}
				break;
			}
			break;
		}
		break;
		case CLANMAKE_NOMONEY:
		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		if(MOUSE0())
		{
			MOUSE0() = 0;
			i = i;
			switch(i)
			{
				case 0:
				C_menuN = CLAN_AllEnd;



				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLAN_isCheckClanJang_Result:
		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		if(MOUSE0())
		{
			MOUSE0() = 0;
			i = i;
			switch(i)
			{
				case 0:
				C_menuN = CLAN_AllEnd;



				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;











		case CLAN_MAKE_is:
		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			case 1:
			menuMouseOver[1] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
		}

		if(MOUSE0())
		{
			MOUSE0() = 0;
			switch(i)
			{
				case 0:








				if((cldata.money - g_ClanMakeMoney) < 0)
				{



					C_menuN = CLANMAKE_NOMONEY;
					menuInit(C_menuN);



					CLAN_ERROR_ret = CLAN_AllEnd;
					break;
				}


				if(cldata.ability < ABILITY)
				{


					C_menuN = CLAN_ABILITYDOWN;
					menuInit(C_menuN);
					CLAN_ERROR_ret = CLAN_AllEnd;
					break;
				}



				C_menuN = CLAN_MONEY_is;
				menuInit(C_menuN);

				break;

				case 1:


				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanCancelMakeClan.szMsg);
				cClanReport.menuInit(C_menuN, clanCancelMakeClan.pos.x, clanCancelMakeClan.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;

				default:
				break;
			}
		}
		break;

		case CLAN_MONEY_is:
		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			case 1:
			menuMouseOver[1] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}

		if(MOUSE0())
		{
			MOUSE0() = 0;
			switch(i)
			{
				case 0:









				C_menuN = CLAN_NAME_is;
				keydownEnt = 0;
				menuInit(C_menuN);
				C_menuN2 = -1;
				break;

				case 1:



				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanCancelMakeClan.szMsg);
				cClanReport.menuInit(C_menuN, clanCancelMakeClan.pos.x, clanCancelMakeClan.pos.y);

				CLAN_ERROR_ret = CLAN_AllEnd;
				break;

				default:
				break;
			}
		}
		break;

		case CLAN_NAME_is:



		switch(C_menuN2)
		{
			case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();
			WebDB.isCheckClanName(cldata.name, cldata.gserver);
			C_menuN2 = 2;
			break;
			case 2:

			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				C_menuN2 = 0;
				C_menuN = CLAN_MARK_expl;;
				menuInit(C_menuN);

				break;
				case 1:

				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_NAME_BEING;
				menuInit(C_menuN);
				break;

				case 100:
				WebDB.Suspend();
				C_menuN2 = 0;

				wsprintf(szErrorMsg, "%s (3)", clanszError_Msg.szMsg);
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;

				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				wsprintf(szErrorMsg, "%s (4)", clanszError_Msg.szMsg);

				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;

				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN2 = 0;
					wsprintf(szErrorMsg, "%s (5)", clanszError_Msg.szMsg);
					C_menuN = CLAN_ERROR;
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;
				}
				break;
			}
			break;
		}




		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;


			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}


		if(keydownEnt == 1)
		{
			keydownEnt = 0;
			goto keydownenter;
		}


		if(MOUSE0())
		{
			MOUSE0() = 0;
			switch(i)
			{
				case 0:

			keydownenter:



				if(cldata.name[0] == 0)
				{
				#ifdef USE_PROSTONTALE		
					SendMessage(hFocusWnd, EM_SETLIMITTEXT, oldLIMITchattingWnd, 0);
					hFocusWnd = 0;
					usehFocus = 0;
					SetIME_Mode(0);

				#endif
					C_menuN = CLAN_NONAME;
					menuInit(C_menuN);
					break;
				}
				C_menuN2 = 1;
			#ifdef USE_PROSTONTALE		
				SendMessage(hFocusWnd, EM_SETLIMITTEXT, oldLIMITchattingWnd, 0);
				hFocusWnd = 0;
				usehFocus = 0;
				SetIME_Mode(0);
			#endif

				break;


				default:
				break;
			}
		}
		break;
		case CLAN_NONAME:
		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}

		if(MOUSE0())
		{
			MOUSE0() = 0;
			switch(i)
			{
				case 0:
				C_menuN = CLAN_NAME_is;
				menuInit(C_menuN);


				break;
			}
		}
		break;
		case CLAN_NAME_BEING:
		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}

		if(MOUSE0())
		{
			MOUSE0() = 0;
			switch(i)
			{
				case 0:
				C_menuN = CLAN_NAME_is;
				menuInit(C_menuN);



				break;
			}
		}
		break;

		case CLAN_MARK_expl:

		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);

			break;
		}


		if(MOUSE0())
		{
			MOUSE0() = 0;
			switch(i)
			{
				case 0:
				C_menuN = CLAN_INSPECTION_expl;
				menuInit(C_menuN);
				break;

			}
		}
		break;


		case CLAN_INSPECTION_expl:


		switch(C_menuN2)
		{
			case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();
		#ifdef USE_PROSTONTALE		
			WebDB.make_Clan(cldata.szID, cldata.gserver, cldata.ChaName,
							cldata.name,
							"설명없음.", sinChar->JOB_CODE, sinChar->Level);
		#else
			WebDB.make_Clan(cldata.szID, cldata.gserver, cldata.ChaName,
							cldata.name,
							"설명없음.", 1, 50);
		#endif
			C_menuN2 = 2;
			break;
			case 2:






			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();



				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (6)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case 1:

				WebDB.Suspend();
				C_menuN2 = 0;
				cldata.myPosition = CLANCHIP;
				C_menuN = CLANMAKE_DOWN_INFO;
				menuInit(C_menuN);






			#ifdef USE_PROSTONTALE		



				int sinMinusMoney(int Money, int Kind = 0);
				sinMinusMoney(g_ClanMakeMoney);








			#endif






				break;
				case 2:
				WebDB.Suspend();
				C_menuN2 = 0;

				wsprintf(szErrorMsg, "%s (7)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN = CLAN_ERROR;
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_NAME_is;
				break;
				case 3:
				WebDB.Suspend();
				C_menuN2 = 0;


				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (8)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				CLAN_ERROR_ret = CLAN_NAME_is;
				break;

				case 100:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (9)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (10)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN2 = 0;
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (11)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;
				}
				break;
			}
			break;
		}

		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			case 3:
			menuMouseOver[3] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}

		if(MOUSE0())
		{
			MOUSE0() = 0;
			switch(i)
			{
				case 0:


				C_menuN2 = 1;
				break;
				case 3:


				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanCancelMakeClan.szMsg);
				cClanReport.menuInit(C_menuN, clanCancelMakeClan.pos.x, clanCancelMakeClan.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;

				break;
			}
		}
		break;

		case CLAN_NotMake:

		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}

		if(MOUSE0())
		{
			MOUSE0() = 0;
			switch(i)
			{
				case 0:
				C_menuN = CLAN_AllEnd;
				break;
			}
		}
		break;
		case CLANMAKE_DOWN_INFO:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.isClanMember(cldata.szID, cldata.gserver, cldata.ChaName);
			C_menuN2 = 1;
			break;
			case 1:




			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				bIsLoading = FALSE;
				C_menuN = CLAN_AllEnd;
				cldata.myPosition = CLANNO_REGESTER;
				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;

				break;


				case 1:
				WebDB.Suspend();
				bIsLoading = FALSE;

				ParsingIsClanMember(ANSdata.ret_Buf);
				cldata.myPosition = CLANUSER;
				C_menuN2 = 0;



			#ifdef VOICE_CHAT
				if(bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
											   cldata.name, (DWORD)atoi(cldata.ClanMark), cldata.myPosition);


				}
			#endif

				break;

				case 2:
				WebDB.Suspend();


				ParsingIsClanMember(ANSdata.ret_Buf);
				WriteMyClanInfo();
				C_menuN2 = 0;
				C_menuN = CLANMAKE_READ_CLANMARK;
				menuInit(C_menuN);


				cldata.myPosition = CLANCHIP;
			#ifdef VOICE_CHAT
				if(bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
											   cldata.name, (DWORD)cldata.intClanMark, cldata.myPosition);


				}
			#endif

				break;
				case 3:
				WebDB.Suspend();
				ParsingIsClanMember2(ANSdata.ret_Buf);
				bIsLoading = FALSE;
				C_menuN2 = 0;
				C_menuN = CLAN_AllEnd;
				cldata.myPosition = CLANNO_REGESTER;

			#ifdef VOICE_CHAT
				if(bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
											   NULL, 0, cldata.myPosition);


				}
			#endif

				break;
				case 100:
				WebDB.Suspend();
				cldata.myPosition = CLAN_NOCONNECT;
				C_menuN = CLAN_AllEnd;
				menuInit(C_menuN);
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				cldata.myPosition = CLAN_NOCONNECT;
				C_menuN = CLAN_AllEnd;
				menuInit(C_menuN);

				break;
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					bIsLoading = FALSE;
					C_menuN2 = 0;
					C_menuN = CLAN_AllEnd;
					cldata.myPosition = CLAN_NOCONNECT;
				}
			}
		}
		break;

		case CLANMAKE_READ_CLANMARK:


		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			WebDB.MarkREAD(cldata.name, cldata.ClanMark);
			C_menuN2 = 1;
			break;
			case 1:

			if(ANSdata.ret_val != -1)
				ANSdata.ret_val = ANSdata.ret_val;


			switch(ANSdata.ret_val)
			{

				case 1:
				WebDB.Suspend();

				server = cldata.ClanMark[0];
				strcpy(UniqueClanMark, &cldata.ClanMark[3]);
				wsprintf(szFile, "%s\\%s\\%c_%s.%s", SAVE_DIR, szConnServerName, server, UniqueClanMark, SAVE_EXE);
				wsprintf(szFile2, "%s\\%s\\%c_%s_16.%s", SAVE_DIR, szConnServerName, server, UniqueClanMark, SAVE_EXE);
			#ifdef  USE_PROSTONTALE
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

			#else
				cldata.hClanMark16 = (HBITMAP)LoadImage(NULL, szFile2,
														IMAGE_BITMAP,
														0, 0,
														LR_LOADFROMFILE);
				cldata.hClanMark = (HBITMAP)LoadImage(NULL, szFile,
													  IMAGE_BITMAP,
													  0, 0,
													  LR_LOADFROMFILE);
			#endif
				C_menuN = CLAN_MAKE_FINISH;
				menuInit(C_menuN);
				C_menuN2 = -1;



				break;
				case 2:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (65)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);






				C_menuN2 = -1;
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();


				C_menuN = CLAN_ERROR;

				wsprintf(szErrorMsg, "%s (66)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);








				C_menuN2 = -1;
				break;

				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();

					C_menuN = CLAN_AllEnd;
					C_menuN2 = -1;
					CLAN_ERROR_ret = -1;
				}
				break;
			}
		}
		break;
		case CLAN_MAKE_FINISH:
		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}

		if(MOUSE0())
		{
			MOUSE0() = 0;
			switch(i)
			{
				case 0:


				C_menuN = CLAN_AllEnd;
				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;




				break;
			}
		}
		break;
	}

}




void CLANEntity_make::RenderMain()
{
	if(life == 0) return;

}





void CLANEntity_make::menuInit(int num)
{
	int bx = 0, by = 0;

	switch(num)
	{
		case CLAN_ABILITYDOWN:
		menuSu = 3;
	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else			
		bx = 64;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + clanAbilityErrorMsg.pos.x;
		menuPos[1].top = BackStartPos.y + clanAbilityErrorMsg.pos.y;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
		case CLANMAKE_REAMMAKR_ERROR:
		menuSu = 3;
	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else			
		bx = 64;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + 30;
		menuPos[1].top = BackStartPos.y + 40;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
		case CLANMAKE_NOMONEY:
		menuSu = 3;
	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else			
		bx = 64;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + clanMoneyErrorMsg.pos.x;
		menuPos[1].top = BackStartPos.y + clanMoneyErrorMsg.pos.y;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
		case CLAN_isCheckClanJang_Result:
		menuSu = 3;
	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else			
		bx = 64;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + 18;
		menuPos[1].top = BackStartPos.y + 40;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
		case CLANMAKE_DOWN_INFO:
		menuPos[0].left = BackStartPos.x + clanClanMakedowninfo.pos.x;
		menuPos[0].top = BackStartPos.y + clanClanMakedowninfo.pos.y;
		menuPos[0].right = 0;
		menuPos[0].bottom = 0;
		break;
		case CLANMAKE_READ_CLANMARK:
		menuPos[0].left = BackStartPos.x + clanClanMakedowninfo.pos.x;
		menuPos[0].top = BackStartPos.y + clanClanMakedowninfo.pos.y;
		menuPos[0].right = 0;
		menuPos[0].bottom = 0;
		break;

		case CLAN_isCheckClanJang:

		menuPos[0].left = BackStartPos.x + clanLoading.pos.x;
		menuPos[0].top = BackStartPos.y + clanLoading.pos.y;
		menuPos[0].right = 0;
		menuPos[0].bottom = 0;
		break;
		case CLAN_MAKE_is:
		menuSu = 2;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else			
		bx = 32;
		by = 16;
	#endif

		menuPos[0].left = BackStartPos.x + BUTTON2_X;
		menuPos[0].top = BackStartPos.y + +BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;



	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else			
		bx = 32;
		by = 16;
	#endif

		menuPos[1].left = BackStartPos.x + BUTTON3_X;
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;


		menuPos[2].left = BackStartPos.x + clanMake1.pos.x;
		menuPos[2].top = BackStartPos.y + clanMake1.pos.y;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;


	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else			
		bx = 68;
		by = 27;
	#endif

		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else			
		bx = 68;
		by = 27;
	#endif
		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		break;
		case CLAN_MONEY_is:
		menuSu = 2;
	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else

		bx = 32;
		by = 16;
	#endif

		menuPos[0].left = BackStartPos.x + BUTTON2_X;
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;



	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else

		bx = 32;
		by = 16;
	#endif

		menuPos[1].left = BackStartPos.x + BUTTON3_X;
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;


		menuPos[2].left = BackStartPos.x + clanMake2.pos.x;
		menuPos[2].top = BackStartPos.y + clanMake2.pos.y;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;


	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else
		bx = 68;
		by = 27;
	#endif

		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else
		bx = 68;
		by = 27;
	#endif

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		break;
		case CLAN_NAME_is:

	#ifdef USE_PROSTONTALE		

		if(hFocusWnd == 0)
		{
			ZeroMemory(cldata.name, sizeof(cldata.name));
			hFocusWnd = hTextWnd;
			SetWindowText(hFocusWnd, "");

			oldLIMITchattingWnd = SendMessage(hFocusWnd, EM_GETLIMITTEXT, 0, 0);
			SendMessage(hFocusWnd, EM_SETLIMITTEXT, 12, 0);
			usehFocus = 1;
		#ifdef	_LANGUAGE_JAPANESE		
			SetIME_Mode(1);
		#endif	
		}
	#endif

		menuSu = 2;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;





		menuPos[2].left = BackStartPos.x + 60;
		menuPos[2].top = BackStartPos.y + 40;
		menuPos[2].right = menuPos[2].left + 190;
		menuPos[2].bottom = menuPos[2].top + 180;


	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else
		bx = 68;
		by = 27;
	#endif

		menuPos[3].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[3].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else

		bx = 68;
		by = 27;
	#endif

		menuPos[4].left = BackStartPos.x + CLANINPUTNAME_X;
		menuPos[4].top = BackStartPos.y + CLANINPUTNAME_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;


		break;
		case CLAN_NONAME:

		menuSu = 1;
	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else

		bx = 32;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + clanNoName.pos.x;
		menuPos[1].top = BackStartPos.y + clanNoName.pos.y;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
		case CLAN_NAME_BEING:
		menuSu = 3;
	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else

		bx = 32;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + clanClanNameError.pos.x;
		menuPos[1].top = BackStartPos.y + clanClanNameError.pos.y;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
		case CLAN_MARK_expl:
		menuSu = 1;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + clanMake4.pos.x;
		menuPos[1].top = BackStartPos.y + clanMake4.pos.y;
		menuPos[1].right = menuPos[1].left + 190;
		menuPos[1].bottom = menuPos[1].top + 180;


	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else
		bx = 68;
		by = 27;
	#endif

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
		case CLAN_INSPECTION_expl:
		menuSu = 5;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else

		bx = 32;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON2_X;
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + clanMake5.pos.x;
		menuPos[1].top = BackStartPos.y + clanMake5.pos.y;
		menuPos[1].right = menuPos[1].left + 260;
		menuPos[1].bottom = menuPos[1].top + 180;


	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else
		bx = 68;
		by = 27;
	#endif

		menuPos[2].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else

		bx = 32;
		by = 16;
	#endif
		menuPos[3].left = BackStartPos.x + BUTTON3_X;
		menuPos[3].top = BackStartPos.y + BUTTON3_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;


	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else
		bx = 68;
		by = 27;
	#endif

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;
		break;
		case CLAN_NotMake:
		menuSu = 3;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 64;
	#else
		bx = 64;
		by = 64;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + clanMsg254.pos.x;
		menuPos[1].top = BackStartPos.y + clanMsg254.pos.y;
		menuPos[1].right = menuPos[1].left + 260;
		menuPos[1].bottom = menuPos[1].top + 180;


	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else
		bx = 68;
		by = 27;
	#endif

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
		case CLAN_MAKE_FINISH:
		menuSu = 3;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else

		bx = 32;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + clanMake6.pos.x;
		menuPos[1].top = BackStartPos.y + clanMake6.pos.y;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;


	}
}

void CLANEntity_make::Draw()
{
	int i = 0, nIconCount = 0;
	int nIconPos = 0;

	int nSaveTop = 0, nAdd = 0;
	int nStrLen = 0;
	char szDrawMenuMsg[2024];
	ZeroMemory(szDrawMenuMsg, sizeof(char) * 2024);

#ifdef USE_PROSTONTALE		
#else
	HDC hdc;
	HDC sorDC;
	BITMAP bit;
	int bx, by;

	RECT rect;
	int j = 0;



	char string[500];


#endif


#ifdef USE_PROSTONTALE		
	switch(C_menuN)
	{
		case CLAN_ABILITYDOWN:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanAbilityErrorMsg.szMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLANMAKE_REAMMAKR_ERROR:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szClanMakeMsg, menuPos[1].left, menuPos[1].top);
		break;

		case CLANMAKE_NOMONEY:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, clanMoneyErrorMsg.szMsg, g_ClanMakeMoney);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLAN_isCheckClanJang_Result:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanisCheckClanJangErrorMsg.szMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLAN_isCheckClanJang:
		Draw_C_Text(clanLoading.szMsg, menuPos[0].left, menuPos[0].top);
		break;
		case 0:
		break;
		case CLAN_MAKE_is:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);
		Draw_C_Text(clanMake1.szMsg, menuPos[2].left, menuPos[2].top);

		break;

		case CLAN_MONEY_is:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, clanMake2.szMsg, g_ClanMakeMoney);
		Draw_C_Text(szDrawMenuMsg, menuPos[2].left, menuPos[2].top);
		break;

		case CLAN_NAME_is:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);

		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		Draw_C_Text(szMsg3, menuPos[2].left, menuPos[2].top);




		if(hFocusWnd != 0)
		{
			GetWindowText(hFocusWnd, cldata.name, 64);

			void KeyFilter(char *szBuffer);
			KeyFilter(cldata.name);



			DrawSprite(menuPos[4].left, menuPos[4].top, hClanNameInput, 0, 0, 100, 20, 1);

			Draw_C_Text(cldata.name, menuPos[4].left + 1, menuPos[4].top + 4, 1);
		}
		break;
		case CLAN_NONAME:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanNoName.szMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLAN_NAME_BEING:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		Draw_C_Text(clanClanNameError.szMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLAN_MARK_expl:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		Draw_C_Text(clanMake4.szMsg, menuPos[1].left, menuPos[1].top);

		break;
		case CLAN_INSPECTION_expl:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[3] > 0)	DrawSprite(menuPos[3].left, menuPos[3].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[3].left, menuPos[3].top, hCancel_Gray, 0, 0, 32, 16, 1);
		wsprintf(szDrawMenuMsg, clanMake5.szMsg, cldata.name);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);

		break;

		case CLAN_NotMake:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanMsg254.szMsg, menuPos[1].left, menuPos[1].top);


		break;
		case CLAN_MAKE_FINISH:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanMake6.szMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLANMAKE_DOWN_INFO:
		Draw_C_Text(clanClanMakedowninfo.szMsg, menuPos[0].left, menuPos[0].top);
		break;
		case CLANMAKE_READ_CLANMARK:
		Draw_C_Text(clanClanMakedowninfo.szMsg, menuPos[0].left, menuPos[0].top);
		break;

	}
#else


	HDC destdc;

	switch(C_menuN)
	{
		case CLAN_ABILITYDOWN:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);
		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);
			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);
			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}


		Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanAbilityErrorMsg.szMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANMAKE_NOMONEY:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);
		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);
			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);
			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}


		Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanMoneyErrorMsg.szMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLAN_isCheckClanJang_Result:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);
		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);
			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);
			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}


		Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanisCheckClanJangErrorMsg.szMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLANMAKE_DOWN_INFO:
		case CLANMAKE_READ_CLANMARK:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);

		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);
		Text_Out(destdc, menuPos[0].left, menuPos[0].top, clanClanMakedowninfo.szMsg);
		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLAN_isCheckClanJang:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);

		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);




		Text_Out(destdc, menuPos[0].left, menuPos[0].top, clanLoading.szMsg);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case 0:

		break;
		case CLAN_MAKE_is:

		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[4].left, menuPos[4].top, menuPos[4].right, menuPos[4].bottom, sorDC, 0, 0, SRCCOPY);
		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hYes_Yellow);

			GetObject(hYes_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hYes_Gray);

			GetObject(hYes_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		if(menuMouseOver[1] > 0)
		{
			SelectObject(sorDC, hNo_Yellow);

			GetObject(hNo_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			BitBlt(destdc, menuPos[1].left, menuPos[1].top, menuPos[1].right, menuPos[1].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hNo_Gray);

			GetObject(hNo_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			BitBlt(destdc, menuPos[1].left, menuPos[1].top, menuPos[1].right, menuPos[1].bottom, sorDC, 0, 0, SRCCOPY);
		}

		wsprintf(string, "%s", szMsg1);
		rect.left = menuPos[2].left;
		rect.top = menuPos[2].top;
		rect.right = menuPos[2].right;
		rect.bottom = menuPos[2].bottom;


		Text_Out(destdc, menuPos[2].left, menuPos[2].top, clanMake1.szMsg);


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);


		break;

		case CLAN_MONEY_is:
		if(m_hClanName)
		{
			ShowWindow(m_hClanName, SW_HIDE);
		}
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);


		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[4].left, menuPos[4].top, menuPos[4].right, menuPos[4].bottom, sorDC, 0, 0, SRCCOPY);

		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);

			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);

			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		if(menuMouseOver[1] > 0)
		{
			SelectObject(sorDC, hCancel_Yellow);

			GetObject(hCancel_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			BitBlt(destdc, menuPos[1].left, menuPos[1].top, menuPos[1].right, menuPos[1].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hCancel_Gray);

			GetObject(hCancel_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			BitBlt(destdc, menuPos[1].left, menuPos[1].top, menuPos[1].right, menuPos[1].bottom, sorDC, 0, 0, SRCCOPY);
		}

		wsprintf(string, "%s", szMsg2);
		rect.left = menuPos[2].left;
		rect.top = menuPos[2].top;
		rect.right = menuPos[2].right;
		rect.bottom = menuPos[2].bottom;


		Text_Out(destdc, menuPos[2].left, menuPos[2].top, clanMake2.szMsg);


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLAN_NAME_is:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);
		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);

		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);

			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;


			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);

			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;


			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}


		SelectObject(sorDC, hClanNameInput);

		GetObject(hClanNameInput, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;


		BitBlt(destdc, menuPos[4].left, menuPos[4].top, menuPos[4].right, menuPos[4].bottom, sorDC, 0, 0, SRCCOPY);

		wsprintf(string, "%s", szMsg3);


		Text_Out(destdc, menuPos[2].left, menuPos[2].top, string);
		ShowWindow(m_hClanName, SW_SHOW);


		GetWindowText(m_hClanName, cldata.name, 64);






		DeleteDC(sorDC);
		DeleteDC(destdc);

		ReleaseDC(g_hwnd, hdc);

		break;
		case CLAN_NONAME:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);
		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);
			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);
			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}



		Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanNoName.szMsg);




		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;

		case CLAN_NAME_BEING:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);
			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);
			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}




		Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanClanNameError.szMsg);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;

		case CLAN_MARK_expl:
		if(m_hClanName)
		{
			ShowWindow(m_hClanName, SW_HIDE);
		}
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);

			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;


			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);

			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;


			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}




		Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanMake4.szMsg);


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLAN_INSPECTION_expl:
		if(m_hClanName)
		{
			ShowWindow(m_hClanName, SW_HIDE);
		}
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(hdc, menuPos[4].left, menuPos[4].top, menuPos[4].right, menuPos[4].bottom, sorDC, 0, 0, SRCCOPY);

		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);

			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;


			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);

			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;


			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}

		if(menuMouseOver[3] > 0)
		{
			SelectObject(sorDC, hCancel_Yellow);

			GetObject(hCancel_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;


			BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hCancel_Gray);

			GetObject(hCancel_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;


			BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);
		}


		wsprintf(szDrawMenuMsg, clanMake5.szMsg, cldata.name);

		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLAN_MAKE_FINISH:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);
			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);
			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}



		Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanMake6.szMsg);




		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLAN_NotMake:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);

			GetObject(hOk_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;


			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);

			GetObject(hOk_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;


			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}


		wsprintf(string, "%s", szMsg254);


		Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanMsg254.szMsg);


		DeleteDC(sorDC);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLAN_AllEnd:
		break;
	}
#endif
}




void KeyFilter(char *szBuffer)
{
#ifdef  USE_PROSTONTALE
	int start;
	int result = 0;

	if(hFocusWnd != NULL && hTextWnd != NULL)
	{

		for(int index = 0; index < (int)lstrlen(szBuffer); index++)
		{
		#ifdef _LANGUAGE_JAPANESE
			if(index > 0)
			{
				if((((szBuffer[index - 1] & 0xff) >= 0x81) && ((szBuffer[index - 1] & 0xff) <= 0x9F))
				   || (((szBuffer[index - 1] & 0xff) >= 0xE0) && ((szBuffer[index - 1] & 0xff) <= 0xEF)))
				{
					index = index;
				}
				else if((szBuffer[index] >= 0x1f && szBuffer[index] <= 0x2f) ||
					(szBuffer[index] >= 0x3a && szBuffer[index] <= 0x40) ||
						(szBuffer[index] == 0x5c) ||
						(szBuffer[index] == 0x5e) ||
						(szBuffer[index] == 0x5f) ||
						(szBuffer[index] == 0x60) ||
						(szBuffer[index] >= 0x7b && szBuffer[index] <= 0x7f))
				{
					szBuffer[index] = 0;
					SetWindowText(hFocusWnd, 0);
					SetWindowText(hFocusWnd, szBuffer);
					SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
					break;
				}
			}
			else
			{
				if((szBuffer[index] >= 0x1f && szBuffer[index] <= 0x2f) ||
					(szBuffer[index] >= 0x3a && szBuffer[index] <= 0x40) ||
				   (szBuffer[index] == 0x5c) ||
				   (szBuffer[index] == 0x5e) ||
				   (szBuffer[index] == 0x5f) ||
				   (szBuffer[index] == 0x60) ||
				   (szBuffer[index] >= 0x7b && szBuffer[index] <= 0x7f))
				{
					szBuffer[index] = 0;
					SetWindowText(hFocusWnd, 0);
					SetWindowText(hFocusWnd, szBuffer);
					SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
					break;
				}
			}
		#else
			if((szBuffer[index] < 48 && szBuffer[index] > 0) ||
				(szBuffer[index] >= 58 && szBuffer[index] <= 64) ||
			   (szBuffer[index] >= 91 && szBuffer[index] <= 96) ||
			   (szBuffer[index] >= 123 && szBuffer[index] <= 127))
			{
				szBuffer[index] = 0;
				SetWindowText(hFocusWnd, 0);
				SetWindowText(hFocusWnd, szBuffer);
				SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
				break;
			}
		#endif



		}

		if(lstrlen(szBuffer) >= 1)
		{
			for(int index = 0; index < (int)lstrlen(szBuffer); index++)
			{


				if((BYTE)szBuffer[index] >= 0x80)
				{

				#ifdef _LANGUAGE_CHINESE


					int fstByte = (BYTE)szBuffer[index];
					int sndByte = (BYTE)szBuffer[index + 1];

					if(fstByte < 0xA1 || fstByte>0xF7 || sndByte < 0xA1 || sndByte>0xFE)
					{
						szBuffer[index] = 0;
						SetWindowText(hFocusWnd, 0);
						SetWindowText(hFocusWnd, szBuffer);
						SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
						break;
					}
					else
						index++;

				#endif

				#ifdef _LANGUAGE_KOREAN

					int fstByte = (BYTE)szBuffer[index];
					int sndByte = (BYTE)szBuffer[index + 1];

					result = (fstByte - 0xb0) * 94 + sndByte - 0xa1;

					if(result < 0 || result >= 2350)
					{
						szBuffer[index] = 0;
						SetWindowText(hFocusWnd, 0);
						SetWindowText(hFocusWnd, szBuffer);
						SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
						break;
					}
					else
						index++;
				#endif

				}
			}
		}

	#ifdef _LANGUAGE_JAPANESE

		result = IsJTS(szBuffer);
		if(result >= 0)
		{
			szBuffer[result] = 0;

			SetWindowText(hFocusWnd, 0);
			SetWindowText(hFocusWnd, szBuffer);
			SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
		}

	#endif
	#ifdef _LANGUAGE_THAI
		result = IsTHAI(szBuffer);
		if((result >= 0) && (IsCurse(szBuffer) == 0))
		{
			szBuffer[result] = 0;

			SetWindowText(hFocusWnd, 0);
			SetWindowText(hFocusWnd, szBuffer);
			SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
		}
		else if(IsCurse(szBuffer) != 0)
		{
			SetWindowText(hFocusWnd, "");
			ZeroMemory(szBuffer, sizeof(char) * 20);
		}
	#endif

	#ifdef _LANGUAGE_ENGLISH
		result = IsENG(szBuffer);
		if(result >= 0)
		{
			szBuffer[result] = 0;

			SetWindowText(hFocusWnd, 0);
			SetWindowText(hFocusWnd, szBuffer);
			SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
		}


	#endif
	#ifdef _LANGUAGE_TAIWAN

		result = IsTaiwan(szBuffer);
		if(result >= 0)
		{
			szBuffer[result] = 0;

			SetWindowText(hFocusWnd, 0);
			SetWindowText(hFocusWnd, szBuffer);
			SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
		}
	#endif

		SendMessage(hFocusWnd, EM_GETSEL, (WPARAM)&start, NULL);
	}

#endif
}