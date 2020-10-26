#define CE_CHIP_CPP
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		

#include "sinbaram\\SinLinkHeader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "Language\\language.h"
#include "HoBaram\\HoTextFile.h"
#endif

#include "tjclan.h"
#include "cE_chip.h"
#include "tjscroll.h"
#include "cE_Report.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "..\\ygy\\ygyheader.h"


CLANEntity_chip::CLANEntity_chip()
{
	Money = 0;
	bClan6Down = FALSE;
	ZeroMemory(szTemp, sizeof(szTemp));
	bRemoveSecondCheck = FALSE;
}

CLANEntity_chip::~CLANEntity_chip()
{

}



int CLANEntity_chip::Init(int Life)
{
	life = Life;
	bPFlag = FALSE;
	bRelease = FALSE;
	bSubChip = FALSE;
	bisSubChip = FALSE;
	return 1;
}

int CLANEntity_chip::Clear()
{
	return 1;
}



void CLANEntity_chip::Main()
{
	int i;
	char szClanMark[32];
	if(life == 0) return;

	switch(C_menuN)
	{
	#ifdef __CLANSUBCHIP__

		case CLANCHIP_NOSUBCHIP:
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
				C_menuN = CLAN_CHIP;

				menuInit(C_menuN);

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}

		break;
		case CLANCHIP_SUBCHIP_LOAD_DATA:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			WebDB.ReadClan(cldata.szID, cldata.gserver, cldata.ClanZang_Name);
		#ifdef CLAN_DEBUG
			DebugMessage("CLAN_CHIP_ReadDATA에서 WebDB.ReadClan(아이디 : %s,게임서버 : %s,캐릭터이름 : %s)", cldata.szID, cldata.gserver, cldata.ClanZang_Name);
		#endif
			C_menuN2 = 1;
			break;
			case 1:
			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (101)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				CLAN_ERROR_ret = 255;
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_CHIP_ReadDATA에서 리턴코드 0 가입한 클랜이 없음");
			#endif
				break;
				case 1:
				WebDB.Suspend();
				ParsigClanWon(ANSdata.ret_Buf);
				C_menuN = CLANCHIP_SUBCHIP_LIST;
				menuInit(C_menuN);
				break;
				case 100:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (102)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_CHIP_ReadDATA에서 리턴코드 100");
			#endif
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (103)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_CHIP_ReadDATA에서 서버에 접속할수 없음");
			#endif
				break;

				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_AllEnd;
					menuInit(C_menuN);

					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("CLAN_CHIP_ReadDATA에서 디폴트에러");
				#endif
				}
				break;

			}
			break;
		}
		break;


		case CLANCHIP_SUBCHIP_READMSG_FLAG:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			if(cldata.nKFlag == 4)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if(cldata.nKFlag == 16)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if(cldata.nKFlag == 5)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if((cldata.nKFlag == 7) && (cldata.nKFlag_Count))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if((cldata.nKFlag == 17) && (cldata.nKFlag_Count == 1))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if((cldata.nKFlag == 19) && (cldata.nKFlag_Count == 1))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 1) && (bSubChip == TRUE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 2) && (bSubChip == TRUE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 1) && (bSubChip == FALSE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 2) && (bSubChip == FALSE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if(cldata.nKFlag == 52)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1) && (bSubChip == TRUE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 2) && (bSubChip == TRUE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1) && (bSubChip == FALSE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 2) && (bSubChip == FALSE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 1))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 2))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if(cldata.nKFlag == 28)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if(cldata.nKFlag == 55)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else
			{
			}



			C_menuN2 = 1;
		#ifdef CLAN_DEBUG
			DebugMessage("CLANCHIP_LEAVECLAN_MESSAGEEND에서 WebDB.isPFlag(아이디 : %s,클랜이름 : %s,캐릭터이름 : %s,게임서버 : %s,플래그 : %s,0)", cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, cldata.PFlag);
		#endif
			break;
			case 1:
			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (86)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_LEAVECLAN_MESSAGEEND에서 삽입실패");
			#endif
				break;
				case 1:
				WebDB.Suspend();
				C_menuN2 = -1;
				if((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 1))
				{
					cldata.nKFlag_Count = 2;
					if(bSubChip) C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					else C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1))
				{
					cldata.nKFlag_Count = 2;
					if(bSubChip == TRUE) C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					else	C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 1))
				{
					cldata.nKFlag_Count = 2;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else
				{
				}
				if((cldata.nKFlag == 4) ||
					(cldata.nKFlag == 16) ||
				   (cldata.nKFlag == 17) ||
				   (cldata.nKFlag == 19) ||
				   (cldata.nKFlag == 5) ||
				   (cldata.nKFlag == 7) ||
				   (cldata.nKFlag == 52) ||
				   ((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 2)) ||
				   ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 2)) ||
				   (cldata.nKFlag == 55))
				{
					cldata.nKFlag_Count = 0;
				}


				if((strcmp(cldata.stats, "0") == 0) && (strcmp(cldata.PFlag, "0") == 0))
				{
					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					strcpy(szTemp, clanMsg6.szMsg);
					strcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					strcpy(clanMsg6.szMsg, szTemp);

					if(cldata.bIsOneDay)
					{

						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						strcpy(szTemp, clanMsg6.szMsg);
						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						strcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);

						strcpy(szTemp, clanMsg6.szMsg);

						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);

						strcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					bPFlag = FALSE;
					C_menuN2 = -1;
					break;
				}
				else if((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "0") == 0))
				{
					strcpy(cldata.PFlag, "2");
					strcpy(szTemp, clanMakeFinishClan.szMsg);
					wsprintf(szDrawMenuMsg, clanMakeFinishClan.szMsg, cldata.name);
					strcpy(clanMakeFinishClan.szMsg, szDrawMenuMsg);

					CheckMsgPos(&clanMakeFinishClan, BOX_MAX_WIDTH, 0);
					C_menuN = CLANCHIP_MAKE_FIRSTMESSAGE;
					menuInit(C_menuN);
					strcpy(clanMakeFinishClan.szMsg, szTemp);
					C_menuN2 = -1;
					bPFlag = TRUE;
					break;
				}








				else if((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "2") == 0) && (nClanWon_Num < 5))
				{

					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					strcpy(szTemp, clanMsg6.szMsg);
					strcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					strcpy(clanMsg6.szMsg, szTemp);

					if(cldata.bIsOneDay)
					{

						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						strcpy(szTemp, clanMsg6.szMsg);
						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						strcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);

						strcpy(szTemp, clanMsg6.szMsg);

						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);

						strcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = FALSE;
				}














				else
				{
					C_menuN = CLAN_CHIP;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = TRUE;
				}
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_LEAVECLAN_MESSAGE에서 리턴코드 1 성공");
			#endif


				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_LEAVECLAN_MESSAGEEND에서 삽입성공");
			#endif
				break;
				default:

				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (87)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("CLANCHIP_LEAVECLAN_MESSAGEEND에서 디폴트에러");
				#endif
				}
				break;
			}
		}
		break;
		case CLANCHIP_SUBCHIP_APPOINT_FLAG:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "200", "1");

			C_menuN2 = 1;
		#ifdef CLAN_DEBUG
			DebugMessage("CLANCHIP_LEAVECLAN_PFLAG에서 WebDB.isPFlag(아이디 : %s,클랜이름 : %s,캐릭터이름 : %s,게임서버 : %s,플래그 : %s,0)", cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, cldata.PFlag);
		#endif
			break;
			case 1:
			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (88)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_LEAVECLAN_PFLAG에서 삽입실패");
			#endif
				break;
				case 1:
				WebDB.Suspend();
				C_menuN2 = -1;

				C_menuN = CLANCHIP_LEAVECLAN_SUCESS;
				menuInit(C_menuN);

				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_LEAVECLAN_PFLAG에서 삽입성공");
			#endif
				break;
				default:

				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (89)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("CLANCHIP_LEAVECLAN_PFLAG에서 디폴트에러");
				#endif
				}
				break;
			}
		}
		break;
		case CLANCHIP_SUBCHIP_APPOINTMSG:
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

				C_menuN = CLANCHIP_SUBCHIP_READMSG_FLAG;

				menuInit(C_menuN);

				C_menuN2 = 0;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLANCHIP_SUBCHIP_RELEASEMSG:
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
				C_menuN = CLANCHIP_SUBCHIP_READMSG_FLAG;
				menuInit(C_menuN);

				C_menuN2 = 0;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLANCHIP_SUBCHIP_LIST:
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



		if(TJwheel != 0)
		{
			scrIconPos.top = tscr.ret_WHEELpoint(TJwheel, scrIconPos.top);
			nScl_Bar = tscr.topScrollLineNum(scrIconPos.top);
			TJwheel = 0;
		}



		if(MOUSE0())
		{
			switch(i)
			{
				case 12:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);

				scrIconPos.top = pCursorPos.y - 8;
				break;

				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:

				if(banisF[i - 4 + nScl_Bar] > 0)
				{
					banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];

					nSavePos = i - 4 + nScl_Bar;
				}
				else
				{
					ZeroMemory(banisF, sizeof(banisF));
					banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];
					nSavePos = i - 4 + nScl_Bar;
				}













				MOUSE0() = 0;
				break;
				case 15:
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
				case 21:
				case 22:

				if(banisF[i - 15 + nScl_Bar] > 0)
				{
					banisF[i - 15 + nScl_Bar] = !banisF[i - 15 + nScl_Bar];
					nSavePos = i - 14 + nScl_Bar;

				}
				else
				{
					ZeroMemory(banisF, sizeof(banisF));
					banisF[i - 15 + nScl_Bar] = !banisF[i - 15 + nScl_Bar];
					nSavePos = i - 15 + nScl_Bar;
				}













				MOUSE0() = 0;
				break;

				case 0:

				C_menuN2 = 0;
				if(nSavePos < 0)
				{
					C_menuN = CLAN_CHIP;
				}
				else
				{

					if(strcmp(cldata.clanWon[nSavePos], cldata.SubChip) == 0)
					{
						C_menuN = CLANCHIP_RELEASESUBCHIP;
						bisSubChip = FALSE;
					}
					else if((cldata.clanWon[nSavePos][0] != 0) && (cldata.SubChip[0] != 0) && (strcmp(cldata.clanWon[nSavePos], cldata.SubChip) != 0))
					{
						C_menuN = CLANCHIP_RELEASESUBCHIP;
						bisSubChip = TRUE;
					}
					else
					{
						C_menuN = CLANCHIP_RESUBCHIP_APPOINT;
					}

				}

				menuInit(C_menuN);

				MOUSE0() = 0;
				break;
				case 1:
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				MOUSE0() = 0;
				break;
				default:

				MOUSE0() = 0;
				break;
			}
		}
		break;
		case CLANCHIP_RESUBCHIP_APPOINT:
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


				C_menuN2 = 1;
				C_menuN = CLANCHIP_APPOINTSUBCHIP_DO;
				menuInit(C_menuN);

				break;

				case 1:


				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;

				default:
				break;
			}
		}
		break;
		case CLANCHIP_RESUBCHIP_APPOINT_END:
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
				C_menuN = CLAN_CHIP;

				menuInit(C_menuN);
				C_menuN2 = -1;

				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLANCHIP_RELEASESUBCHIP:
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


				C_menuN2 = 1;
				C_menuN = CLANCHIP_RELEASESUBCHIP_DO;
				menuInit(C_menuN);

				break;

				case 1:


				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;

				default:
				break;
			}
		}
		break;
		case CLANCHIP_RELEASESUBCHIP_END:
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
				ZeroMemory(cldata.SubChip, sizeof(cldata.SubChip));
				C_menuN = CLAN_CHIP;

				menuInit(C_menuN);

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLANCHIP_APPOINTSUBCHIP_DO:
		switch(C_menuN2)
		{
			case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();
			WebDB.AppointSubChip(cldata.szID, cldata.ChaName, cldata.name, cldata.gserver, cldata.clanWon[nSavePos]);
			C_menuN2 = 2;

			break;
			case 2:
			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (90)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case 3:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (100)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case 2:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (91)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case 1:
				WebDB.Suspend();
				C_menuN2 = 0;
				strcpy(cldata.SubChip, cldata.clanWon[nSavePos]);

				C_menuN = CLANCHIP_RESUBCHIP_APPOINT_END;
				menuInit(C_menuN);


				void SetClanWon();
				SetClanWon();
				break;


				case 100:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (92)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (93)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN2 = 0;
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (94)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;
				}
				break;
			}
		}
		break;
		case CLANCHIP_SUBCHIP_LOAD:
		break;
		case CLANCHIP_RELEASESUBCHIP_DO:
		switch(C_menuN2)
		{
			case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();

			WebDB.ReleaseSubChip(cldata.szID, cldata.ChaName, cldata.name, cldata.gserver, cldata.SubChip);
			C_menuN2 = 2;

			break;
			case 2:
			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (95)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case 2:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (96)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case 1:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLANCHIP_RELEASESUBCHIP_END;
				menuInit(C_menuN);


				void SetClanWon();
				SetClanWon();

				if(bisSubChip)
				{
					C_menuN = CLANCHIP_RESUBCHIP_APPOINT;
					menuInit(C_menuN);
				}
				break;

				case 100:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (97)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (98)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN2 = 0;
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (99)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;
				}
				break;
			}
		}
		break;

	#endif

		case CLANCHIP_GO_RELEASEMESSAGE:
		C_menuN = CLANCHIP_RELEASEMESSAGE;
		menuInit(C_menuN);
		break;
		case CLANCHIP_RELEASEMESSAGE:
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

				C_menuN = CLANCHIP_RELEASE_FLAG;

				menuInit(C_menuN);
				C_menuN2 = 0;

				break;
				default:
				i = i;
				break;

			}
		}
		break;

		case CLAN_REMOVE_SHORTCLANWON_LOADING:
		if(ANSdata.ret_val != -1) C_menuN = CLAN_REMOVE_SHORTCLANWON;
		break;
		case CLAN_REMOVE_LOADING:
		if(ANSdata.ret_val != -1) C_menuN = CLAN_REMOVE;
		break;
		case CLAN_RELEASE_LOADING:
		if(ANSdata.ret_val != -1) C_menuN = CLAN_RECONF_RELEASE;
		break;
		case CLAN_CHIP:
		i = chkeckMenuN();
		memset(menuMouseOver, -1, sizeof(menuMouseOver));
		switch(i)
		{

			case 2:
			menuMouseOver[2] = 1;
			break;
			case 3:
			menuMouseOver[3] = 1;
			break;
			case 4:
			menuMouseOver[4] = 1;
			break;

			case 5:
			menuMouseOver[5] = 1;
			break;
			case 6:

			menuMouseOver[6] = 1;
			break;
			case 7:
			menuMouseOver[7] = 1;
			break;
			case 18:
			if(cldata.stats[0] == '0') menuMouseOver[18] = 0;
			else menuMouseOver[18] = 1;
			break;


		#ifdef __CLANSUBCHIP__
			case 19:
			if(cldata.stats[0] == '0') menuMouseOver[19] = 0;
			else menuMouseOver[19] = 1;
			break;
		#endif

			default:
			memset(menuMouseOver, -1, sizeof(menuMouseOver));
			break;
		}

		if(MOUSE0())
		{

			MOUSE0() = 0;

			switch(i)
			{
				case 2:

				wsprintf(szClanMark, "%s", cldata.ClanMark);
				nMark = chkMark(szClanMark);
				switch(nMark)
				{
					case 0:
					C_menuN = CLAN_MARK1;
					menuInit(CLAN_MARK1);
					break;
					case 1:
					C_menuN = CLAN_MARK2;
					menuInit(CLAN_MARK2);
					break;
					case 2:
					C_menuN = CLAN_MARK3;
					menuInit(CLAN_MARK3);
					break;
				}
				break;
				case 3:
				ZeroMemory(banisF, sizeof(banisF));
				ZeroMemory(banisBuf1, sizeof(banisBuf1));
				ZeroMemory(banisBuf2, sizeof(banisBuf2));
				banisCnt = 1;

				C_menuN = CLAN_REMOVE;
				menuInit(CLAN_REMOVE);
				C_menuN2 = -1;
				break;
				case 4:
				C_menuN2 = -1;
				C_menuN = CLAN_RELEASE;
				menuInit(CLAN_RELEASE);
				break;
				case 5:


				LoadHelpImage();
				C_menuN2 = -1;

				LoadHelp(HELPCONTENT_TXT);
				C_menuN = CLAN_HELP_CONTENT;
				menuInit(C_menuN);

				break;
				case 6:
				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;
				break;
				case 18:
				if(cldata.stats[0] == '0')
				{
					C_menuN = CLANCHIP_NOLEAVECLAN;
				}
				else
				{
					C_menuN = CLANCHIP_LEAVECLAN_CONFIRM;
				}

				menuInit(C_menuN);
				break;


			#ifdef __CLANSUBCHIP__
				case 19:


				if(cldata.stats[0] == '0')
				{
					C_menuN = CLANCHIP_NOSUBCHIP;
					menuInit(C_menuN);

				}
				else
				{
					C_menuN = CLANCHIP_SUBCHIP_LOAD_DATA;
					menuInit(C_menuN);
					C_menuN2 = 0;
				}

				break;

			#endif
				default:
				break;
			}
		}
		break;
		case CLAN_WAREHOUSE:
		wsprintf(szErrorMsg, "창고메뉴는 준비중입니다.");
		C_menuN = CLAN_ERROR;
		menuInit(C_menuN);
		CLAN_ERROR_ret = CLAN_CHIP;
		break;


		case CLAN_MARK1:
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
				C_menuN = 4;
				menuInit(C_menuN);
				break;
				default:
				break;
			}
		}
		break;
		case CLAN_MARK2:
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
				break;
				case 1:
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;
				default:
				break;
			}
		}
		break;
		case CLAN_MARK3:
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
				break;
				case 1:
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;
				default:
				break;
			}
		}
		break;






		case CLANCHIP_LEAVECLAN_MESSAGE:
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
				C_menuN = CLANCHIP_LEAVECLAN_MESSAGEEND;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLANCHIP_LEAVECLAN_NOLEVEL:
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
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLANCHIP_LEAVECLANDOWNLEVEL:
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
				C_menuN = CLAN_CHIP;

				menuInit(C_menuN);

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;

		case CLANCHIP_NOLEAVECLAN:
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
				C_menuN = CLAN_CHIP;

				menuInit(C_menuN);

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLANCHIP_LEAVECLAN_MESSAGEEND:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			if((cldata.nKFlag == 1) && (cldata.nKFlag_Count == 1))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "0");
			}
			else if((cldata.nKFlag == 5) && (cldata.nKFlag_Count == 1))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "0");
			}
			else if((cldata.nKFlag == 17) && (cldata.nKFlag_Count == 1))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "0");
			}
			else if((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "0");
			}
			else
			{
			}

			C_menuN2 = 1;
		#ifdef CLAN_DEBUG
			DebugMessage("CLANCHIP_LEAVECLAN_MESSAGEEND에서 WebDB.isPFlag(아이디 : %s,클랜이름 : %s,캐릭터이름 : %s,게임서버 : %s,플래그 : %s,0)", cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, cldata.PFlag);
		#endif
			break;
			case 1:
			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (86)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_LEAVECLAN_MESSAGEEND에서 삽입실패");
			#endif
				break;
				case 1:
				WebDB.Suspend();
				C_menuN2 = -1;

				if((cldata.nKFlag == 1) && (cldata.nKFlag_Count == 1))
				{
					cldata.nKFlag_Count = 0;
				}
				else if(cldata.nKFlag == 17)
				{
					cldata.nKFlag_Count = 1;

					C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 5)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 21)
				{
					cldata.nKFlag_Count = 1;
					if(cldata.SubChip[0] == 0)
					{
						bSubChip = FALSE;
						C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					}
					else
					{
						bSubChip = TRUE;
						C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					}

					menuInit(C_menuN);
					break;
				}
				else
				{
				}


				if((strcmp(cldata.stats, "0") == 0) && (strcmp(cldata.PFlag, "0") == 0))
				{
					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					strcpy(szTemp, clanMsg6.szMsg);
					strcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					strcpy(clanMsg6.szMsg, szTemp);

					if(cldata.bIsOneDay)
					{

						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						strcpy(szTemp, clanMsg6.szMsg);
						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						strcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);

						strcpy(szTemp, clanMsg6.szMsg);

						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);

						strcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					bPFlag = FALSE;
					C_menuN2 = -1;
					break;
				}
				else if((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "0") == 0))
				{
					strcpy(cldata.PFlag, "2");
					strcpy(szTemp, clanMakeFinishClan.szMsg);
					wsprintf(szDrawMenuMsg, clanMakeFinishClan.szMsg, cldata.name);
					strcpy(clanMakeFinishClan.szMsg, szDrawMenuMsg);

					CheckMsgPos(&clanMakeFinishClan, BOX_MAX_WIDTH, 0);
					C_menuN = CLANCHIP_MAKE_FIRSTMESSAGE;
					menuInit(C_menuN);
					strcpy(clanMakeFinishClan.szMsg, szTemp);
					C_menuN2 = -1;
					bPFlag = TRUE;
					break;
				}








				else if((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "2") == 0) && (nClanWon_Num < 5))
				{

					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					strcpy(szTemp, clanMsg6.szMsg);
					strcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					strcpy(clanMsg6.szMsg, szTemp);

					if(cldata.bIsOneDay)
					{

						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						strcpy(szTemp, clanMsg6.szMsg);
						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						strcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);

						strcpy(szTemp, clanMsg6.szMsg);

						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);

						strcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = FALSE;
				}















				else
				{
					C_menuN = CLAN_CHIP;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = TRUE;
				}
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_LEAVECLAN_MESSAGE에서 리턴코드 1 성공");
			#endif


				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_LEAVECLAN_MESSAGEEND에서 삽입성공");
			#endif
				break;
				default:

				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (87)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("CLANCHIP_LEAVECLAN_MESSAGEEND에서 디폴트에러");
				#endif
				}
				break;
			}
		}
		break;


		case CLANCHIP_LEAVECLAN_PFLAG:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "200", "1");

			C_menuN2 = 1;
		#ifdef CLAN_DEBUG
			DebugMessage("CLANCHIP_LEAVECLAN_PFLAG에서 WebDB.isPFlag(아이디 : %s,클랜이름 : %s,캐릭터이름 : %s,게임서버 : %s,플래그 : %s,0)", cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, cldata.PFlag);
		#endif
			break;
			case 1:
			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (88)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_LEAVECLAN_PFLAG에서 삽입실패");
			#endif
				break;
				case 1:
				WebDB.Suspend();
				C_menuN2 = -1;

				C_menuN = CLANCHIP_LEAVECLAN_SUCESS;
				menuInit(C_menuN);

				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_LEAVECLAN_PFLAG에서 삽입성공");
			#endif
				break;
				default:

				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (89)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("CLANCHIP_LEAVECLAN_PFLAG에서 디폴트에러");
				#endif
				}
				break;
			}
		}
		break;


		case CLANCHIP_LEAVECLAN_DO:
		switch(C_menuN2)
		{
			case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();
			WebDB.LeaveClan(cldata.name, cldata.clanWon[nSavePos], cldata.gserver);
			C_menuN2 = 2;

			break;
			case 2:
			switch(ANSdata.ret_val)
			{
				case 1:

				WebDB.Suspend();
				C_menuN2 = 0;
			#ifdef USE_PROSTONTALE		

				int sinMinusMoney(int Money, int Kind = 0);
				sinMinusMoney(300000);
			#endif
				C_menuN = CLANCHIP_LEAVECLAN_PFLAG;
				menuInit(C_menuN);
				break;
				case 2:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (83)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case 3:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (82)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case 4:
				WebDB.Suspend();
				C_menuN2 = 0;
				C_menuN = CLANCHIP_LEAVECLAN_NOLEVEL;
				menuInit(C_menuN);





				break;
				case 5:
				WebDB.Suspend();
				C_menuN2 = 0;
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (80)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case 6:
				WebDB.Suspend();
				C_menuN2 = 0;
				C_menuN = CLANCHIP_LEAVECLAN_NOLEVEL;
				menuInit(C_menuN);


				break;
				case 100:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (76)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (77)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN2 = 0;
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (78)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;
				}
				break;
			}
		}
		break;
		case CLANCHIP_LEAVECLAN_RECONFIRM:

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


				C_menuN2 = 1;
				C_menuN = CLANCHIP_LEAVECLAN_DO;
				menuInit(C_menuN);

				break;

				case 1:


				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;

				default:
				break;
			}
		}
		break;
		case CLANCHIP_LEAVECLAN_CONFIRM:
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

				if(cldata.money < CLANCHIP_LEAVECLAN_MONEY)
				{
					C_menuN = CLANCHIP_LEAVECLAN_NOMONEY;
				}
				else
				{
					C_menuN = CLANCHIP_LEAVECLAN;
				}

				menuInit(C_menuN);

				break;

				case 1:

				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;

				default:
				break;
			}
		}
		break;
		case CLANCHIP_LEAVECLAN_NOMONEY:
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
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);




				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;
		case CLANCHIP_LEAVECLAN_SUCESS:
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
		case CLANCHIP_LEAVECLAN:
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



		if(TJwheel != 0)
		{
			scrIconPos.top = tscr.ret_WHEELpoint(TJwheel, scrIconPos.top);
			nScl_Bar = tscr.topScrollLineNum(scrIconPos.top);
			TJwheel = 0;
		}



		if(MOUSE0())
		{
			switch(i)
			{
				case 12:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);

				scrIconPos.top = pCursorPos.y - 8;
				break;

				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:

				if(banisF[i - 4 + nScl_Bar] > 0)
				{
					banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];

					nSavePos = i - 4 + nScl_Bar;
				}
				else
				{
					ZeroMemory(banisF, sizeof(banisF));
					banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];
					nSavePos = i - 4 + nScl_Bar;
				}













				MOUSE0() = 0;
				break;
				case 15:
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
				case 21:
				case 22:

				if(banisF[i - 15 + nScl_Bar] > 0)
				{
					banisF[i - 15 + nScl_Bar] = !banisF[i - 15 + nScl_Bar];
					nSavePos = i - 14 + nScl_Bar;

				}
				else
				{
					ZeroMemory(banisF, sizeof(banisF));
					banisF[i - 15 + nScl_Bar] = !banisF[i - 15 + nScl_Bar];
					nSavePos = i - 15 + nScl_Bar;
				}













				MOUSE0() = 0;
				break;

				case 0:

				C_menuN2 = 0;
				if(nSavePos < 0)
				{
					C_menuN = CLAN_CHIP;
				}
				else
				{
					C_menuN = CLANCHIP_LEAVECLAN_RECONFIRM;
				}

				menuInit(C_menuN);

				MOUSE0() = 0;
				break;
				case 1:
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				MOUSE0() = 0;
				break;
				default:

				MOUSE0() = 0;
				break;
			}
		}
		break;




		case CLAN_REMOVE:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.Banishiment(cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name, szRemoveClanWon);
			C_menuN2 = 1;
		#ifdef CLAN_DEBUG
			DebugMessage("CLAN_REMOVE에서 WebDB.Banishiment(아이디 : %s,게임서버 : %s,클랜장 : %s,클랜이름 : %s,클랜원%s)", cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name, szRemoveClanWon);
		#endif
			break;
			case 1:

			if(ANSdata.ret_val != -1)
			{
				ANSdata.ret_val = ANSdata.ret_val;
			}

			switch(ANSdata.ret_val)
			{
				case -1:
				C_menuN = CLAN_REMOVE_LOADING;
				menuInit(C_menuN);
				break;

				case 0:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (12)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_REMOVE에서 트랜잭션오류");
			#endif
				break;
				case 1:
				case 3:

				WebDB.Suspend();
				void SetClanWon();
				SetClanWon();
				C_menuN2 = 0;
				C_menuN = CLAN_REMOVE_RESULT;
				menuInit(C_menuN);
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_REMOVE에서 추방성공(%d)", ANSdata.ret_val);
			#endif

				break;
				case 2:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (13)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				CLAN_ERROR_ret = 255;

				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_REMOVE에서 클랜이 존재하지 않거나 클랜 장이 아닌경우 또는 클랜원이 아닌경우(%d)", ANSdata.ret_val);
			#endif
				break;
				case 100:
				WebDB.Suspend();


				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (14)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				CLAN_ERROR_ret = 255;
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_REMOVE에서 리턴코드 100");
			#endif
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();

				wsprintf(szErrorMsg, "%s (15)", clanszError_Msg.szMsg);
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_REMOVE에서 서버에접속할수 없음");
			#endif
				break;


				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();


					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (16)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = 255;
					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("CLAN_REMOVE에서 디폴트에러");
				#endif
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
			case 1:
			menuMouseOver[1] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}



		if(TJwheel != 0)
		{
			scrIconPos.top = tscr.ret_WHEELpoint(TJwheel, scrIconPos.top);
			nScl_Bar = tscr.topScrollLineNum(scrIconPos.top);
			TJwheel = 0;
		}



		if(MOUSE0())
		{
			switch(i)
			{
				case 12:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);

				scrIconPos.top = pCursorPos.y - 8;
				break;

				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:
				if(nReleaseClanWon >= 5)
				{
					if(banisF[i - 4 + nScl_Bar] > 0)
					{
						banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];
						nReleaseClanWon -= 1;
					}
				}
				else
				{

					banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];
					if(banisF[i - 4 + nScl_Bar])
					{
						nReleaseClanWon += 1;
					}
					else
					{
						nReleaseClanWon -= 1;
					}
				}


				MOUSE0() = 0;
				break;
				case 14:
				case 15:
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
				case 21:
				if(nReleaseClanWon >= 5)
				{
					if(banisF[i - 14 + nScl_Bar] > 0)
					{
						banisF[i - 4 + nScl_Bar] = !banisF[i - 14 + nScl_Bar];
						nReleaseClanWon -= 1;
					}
				}
				else
				{

					banisF[i - 14 + nScl_Bar] = !banisF[i - 14 + nScl_Bar];
					if(banisF[i - 14 + nScl_Bar])
					{
						nReleaseClanWon += 1;
					}
					else
					{
						nReleaseClanWon -= 1;
					}
				}


				MOUSE0() = 0;
				break;

				case 0:
				ZeroMemory(szRemoveClanWon, sizeof(szRemoveClanWon));
				for(i = 0; i < nClanWon_Num; i++)
				{
					if(banisF[i])
					{
						wsprintf(banisBuf1, "clwon%d=%s", banisCnt, cldata.clanWon[i]);

						if(banisCnt == 1)
						{
							wsprintf(banisBuf2, "%s", banisBuf1);
						}
						else
						{
							wsprintf(banisBuf2, "%s&%s", szRemoveClanWon, banisBuf1);
						}
						memcpy(szRemoveClanWon, banisBuf2, strlen(banisBuf2) + 1);
						banisCnt++;
					}
				}
				if(szRemoveClanWon[0] == 0)
				{
					C_menuN = CLAN_CHIP;
					menuInit(C_menuN);

					MOUSE0() = 0;
					break;
				}

				ReMoveClanWon(szRemoveClanWon);
				if((nClanWon_Num - nReleaseClanWon) < 5)
				{
					bRemoveSecondCheck = FALSE;
					C_menuN = CLAN_REMOVE_SHORTCLANWON;
					menuInit(C_menuN);

					MOUSE0() = 0;
					break;
				}
				else
				{

					bRemoveSecondCheck = TRUE;
					C_menuN = CLAN_REMOVE_SHORTCLANWON;
					menuInit(C_menuN);

					MOUSE0() = 0;
					break;
				}
				C_menuN2 = 0;

				MOUSE0() = 0;
				break;
				case 1:
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				MOUSE0() = 0;
				break;
				default:

				MOUSE0() = 0;
				break;
			}
		}
		break;
		case CLAN_REMOVE_SHORTCLANWON:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.Banishiment(cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name, szRemoveClanWon);

			C_menuN2 = 1;
		#ifdef CLAN_DEBUG
			DebugMessage("CLAN_REMOVE_SHORTCLANWON에서 WebDB.Banishiment(아이디 : %s,게임서버 : %s,클랜장 : %s,클랜이름 : %s,클랜원%s)", cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name, szRemoveClanWon);
		#endif
			break;
			case 1:

			switch(ANSdata.ret_val)
			{
				case -1:
				C_menuN = CLAN_REMOVE_SHORTCLANWON_LOADING;
				menuInit(C_menuN);
				break;

				case 0:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (17)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				CLAN_ERROR_ret = 255;
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_REMOVE_SHORTCLANWON에서 트랜잭션오류");
			#endif
				break;
				case 1:
				case 3:

				WebDB.Suspend();
				C_menuN2 = 0;

				void SetClanWon();
				SetClanWon();



				if(nReleaseClanWon > 0) cldata.nCurrentClanWon_Num -= nReleaseClanWon;

				C_menuN = CLAN_REMOVE_SHORTCLANWON_RESULT;
				menuInit(C_menuN);




				break;
				case 2:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (18)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				menuInit(C_menuN);
				CLAN_ERROR_ret = 255;

				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_REMOVE_SHORTCLANWON에서 클랜이 존재하지 않거나 클랜 장이 아닌경우 또는 클랜원이 아닌경우(2)");
			#endif
				break;

				case 100:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (19)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_REMOVE_SHORTCLANWON에서 리턴코드 100");
			#endif

				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (20)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_REMOVE_SHORTCLANWON에서 서버에 접속할수 없음");
			#endif
				break;


				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();

					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (21)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = 255;
					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("CLAN_REMOVE_SHORTCLANWON에서 디폴트에러");
				#endif
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
				C_menuN2 = 0;
				break;
				case 1:
				ZeroMemory(banisBuf1, sizeof(banisBuf1));
				ZeroMemory(banisBuf2, sizeof(banisBuf2));

				memset(banisF, 0, sizeof(int) * 100);
				ZeroMemory(szRemoveClanWon, sizeof(char) * 500);
				ZeroMemory(szRemoveClanWonResult, sizeof(szRemoveClanWonResult));
				banisCnt = 1;
				C_menuN = CLAN_REMOVE;
				menuInit(C_menuN);
				break;
			}
		}
		break;
		case CLAN_REMOVE_SHORTCLANWON_RESULT:
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
				bClan6Down = TRUE;
				C_menuN2 = 0;
				C_menuN = CLAN_CHIP_ReadDATA;

				menuInit(C_menuN);

				break;
				default:
				break;
			}
		}
		break;
		case CLAN_REMOVE_RESULT:
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
				C_menuN2 = 0;
				C_menuN = CLAN_CHIP_ReadDATA;

				menuInit(C_menuN);
				break;
				default:
				break;
			}
		}
		break;

		case CLAN_RELEASE:
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
				if(strcmp(cldata.stats, "0") == 0)
				{

					wsprintf(szReconfReleaseMsg, clanNoRecordReleaseMsg.szMsg);
				}
				else
				{

					wsprintf(szReconfReleaseMsg, clanszReConfReleaseMsg.szMsg);

				}
				C_menuN = CLAN_RECONF_RELEASE;
				menuInit(C_menuN);
				break;
				case 1:
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;
				default:
				break;
			}
		}
		break;
		case CLAN_RECONF_RELEASE:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.BreakUP_Clan(cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name);
		#ifdef CLAN_DEBUG
			DebugMessage("CLAN_RECONF_RELEASE에서 WebDB.BreakUP_Clan(아이디 : %s,게임서버 이름 : %s,캐릭터이름 : %s,클랜이름 : %s)", cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name);
		#endif
			C_menuN2 = 1;
			break;
			case 1:
			switch(ANSdata.ret_val)
			{
				case -1:
				C_menuN = CLAN_RELEASE_LOADING;
				menuInit(C_menuN);
				break;
				case 0:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (22)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_RECONF_RELEASE에서 트랜잭션 오류");
			#endif
				break;
				case 1:
				WebDB.Suspend();
				cldata.myPosition = CLANNO_REGESTER;
				C_menuN = CLAN_FINISH_RELEASE;
				menuInit(C_menuN);

				C_menuN2 = 0;

				void SetClanWon();
				SetClanWon();


				cldata.myPosition = CLANNO_REGESTER;
				ZeroMemory(cldata.name, sizeof(cldata.name));
				ZeroMemory(cldata.explanation, sizeof(cldata.explanation));
				ZeroMemory(cldata.ClanZang_Name, sizeof(cldata.ClanZang_Name));
				ZeroMemory(cldata.ClanMark, sizeof(cldata.ClanMark));
				cldata.intClanMark = 0;
				ZeroMemory(cldata.PFlag, sizeof(cldata.PFlag));

				ZeroMemory(szChatClanWon, sizeof(szChatClanWon));
			#ifdef USE_PROSTONTALE		
				if(cldata.hClanMark)
				{
					cldata.hClanMark->Release();
					cldata.hClanMark = NULL;

				}
				if(cldata.hClanMark16)
				{
					cldata.hClanMark16->Release();
					cldata.hClanMark16 = NULL;
				}
			#endif



			#ifdef VOICE_CHAT
				if(bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
											   NULL, 0, cldata.myPosition);


				}
			#endif


			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_RECONF_RELEASE에서 클랜해체 성공");
			#endif				


				break;
				case 2:
				WebDB.Suspend();


				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (23)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_RECONF_RELEASE에서 현재 캐릭명이 현재 클랜의 장이 아니거나 해당클랜이 없음(2)");
			#endif
				break;
				case 100:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (24)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_RECONF_RELEASE에서 리턴코드 100");
			#endif
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (25)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_RECONF_RELEASE에서 서버에 접속할수 없음");
			#endif
				break;

				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();

					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (26)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = 255;
					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("CLAN_RECONF_RELEASE에서 디폴트에러");
				#endif
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
				C_menuN2 = 0;
				bRelease = TRUE;
				break;
				case 1:
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;
				default:
				break;
			}
		}
		break;
		case CLAN_FINISH_RELEASE:
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

				C_menuN = CLAN_AllEnd;;
				menuInit(C_menuN);
				break;
				default:
				break;
			}
		}
		break;
		case CLAN_HELP:
		i = chkeckMenuN();
		memset(menuMouseOver, -1, sizeof(int) * 30);

		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			case 2:
			menuMouseOver[2] = 1;
			break;
			case 3:
			menuMouseOver[3] = 1;
			break;
			case 4:
			menuMouseOver[4] = 1;
			break;
			case 5:
			menuMouseOver[5] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}


		if(MOUSE0())
		{
			switch(i)
			{
				case 0:

				DestroyClanHelpIcon();
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				MOUSE0() = 0;

				break;
				case 2:
				case 3:
				case 4:
				case 5:





				LoadHelp(ClanHelpIcon[i + nScl_Bar - 2].TextFilePath);

				C_menuN = CLAN_HELP_CONTENT;
				menuInit(C_menuN);

				MOUSE0() = 0;

				break;


				case 6:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);

				scrIconPos.top = pCursorPos.y - 8;
				break;

				default:

				MOUSE0() = 0;
				break;
			}
		}
		break;
		case CLAN_HELP_CONTENT:
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




		if(TJwheel != 0)
		{
			scrIconPos.top = tscr.ret_WHEELpoint(TJwheel, scrIconPos.top);
			nScl_Bar = tscr.topScrollLineNum(scrIconPos.top);
			TJwheel = 0;
		}



		if(MOUSE0())
		{
			switch(i)
			{
				case 0:
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				MOUSE0() = 0;


				tscr.Init(0);
				break;
				case 5:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);

				scrIconPos.top = pCursorPos.y - 8;
				break;

				default:

				MOUSE0() = 0;
				break;
			}
		}

		break;
		case CLANCHIP_RELEASE_FLAG:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.isPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "100", "0");
			C_menuN2 = 1;
		#ifdef CLAN_DEBUG
			DebugMessage("CLANCHIP_RELEASE_FLAG에서 WebDB.isPFlag(아이디 : %s,클랜이름 : %s,캐릭터이름 : %s,게임서버 : %s,100,0)", cldata.szID, cldata.name, cldata.ChaName, cldata.gserver);
		#endif
			break;
			case 1:
			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (27)", clanszError_Msg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_RELEASE_FLAG에서 삽입실패");
			#endif
				break;
				case 1:
				WebDB.Suspend();
				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;



			#ifdef CLAN_DEBUG
				DebugMessage("CLANCHIP_RELEASE_FLAG에서 삽입성공");
			#endif

				break;
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (28)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("CLANCHIP_RELEASE_FLAG에서 디폴트에러");
				#endif
				}
				break;
			}
		}
		break;
		case ISPFLAG_CHIP:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			WebDB.isPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, cldata.PFlag, "0");

			C_menuN2 = 1;
		#ifdef CLAN_DEBUG
			DebugMessage("ISPFLAG_CHIP에서 WebDB.isPFlag(아이디 : %s,클랜이름 : %s,캐릭터이름 : %s,게임서버 : %s,플래그 : %s,0)", cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, cldata.PFlag);
		#endif
			break;
			case 1:
			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (29)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("ISPFLAG_CHIP에서 삽입실패");
			#endif
				break;
				case 1:
				WebDB.Suspend();
				C_menuN2 = -1;
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("ISPFLAG_CHIP에서 삽입성공");
			#endif
				break;
				default:

				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (30)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("ISPFLAG_CHIP에서 디폴트에러");
				#endif
				}
				break;
			}
		}
		break;

		case CLANCHIP_MAKE_FIRSTMESSAGE:
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
				C_menuN = ISPFLAG_CHIP;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
				default:
				break;
			}
		}
		break;
		case CLANCHIP_DOWN6_CLANWON_MESSAGE:
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
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
				default:
				break;
			}
		}
		break;

		case CLANCHIP_DOWN6_CLANWON:
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
				C_menuN = ISPFLAG_CHIP;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
				default:
				break;
			}
		}
		break;
		case CLAN_NOMAKE:
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
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;
				default:
				break;
			}
		}

		break;


		case CLAN_CHIP_ReadDATA:

		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			WebDB.ReadClan(cldata.szID, cldata.gserver, cldata.ClanZang_Name);
		#ifdef CLAN_DEBUG
			DebugMessage("CLAN_CHIP_ReadDATA에서 WebDB.ReadClan(아이디 : %s,게임서버 : %s,캐릭터이름 : %s)", cldata.szID, cldata.gserver, cldata.ClanZang_Name);
		#endif
			C_menuN2 = 1;
			break;
			case 1:

			switch(ANSdata.ret_val)
			{
				case -1:


				break;

				case 0:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (31)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				CLAN_ERROR_ret = 255;
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_CHIP_ReadDATA에서 리턴코드 0 가입한 클랜이 없음");
			#endif
				break;
				case 1:
				WebDB.Suspend();
				ParsigClanWon(ANSdata.ret_Buf);
				if(bClan6Down)
				{
					bClan6Down = FALSE;
					C_menuN = CLAN_CHIP;
					menuInit(C_menuN);
					break;
				}

				if(cldata.nKFlag == 1)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 16)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 4)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 17)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 19)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 5)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 7)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 20)
				{
					if(cldata.SubChip[0] == 0)
					{
						bSubChip = FALSE;
						cldata.nKFlag_Count = 1;
						C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
						menuInit(C_menuN);
					}
					else
					{
						bSubChip = TRUE;
						cldata.nKFlag_Count = 1;
						C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
						menuInit(C_menuN);
					}
					break;
				}
				else if(cldata.nKFlag == 52)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 21)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 23)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 28)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if(cldata.nKFlag == 55)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else
				{
				}







				if((strcmp(cldata.stats, "0") == 0) && (strcmp(cldata.PFlag, "0") == 0))
				{
					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					strcpy(szTemp, clanMsg6.szMsg);
					strcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					strcpy(clanMsg6.szMsg, szTemp);

					if(cldata.bIsOneDay)
					{

						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						strcpy(szTemp, clanMsg6.szMsg);
						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						strcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);

						strcpy(szTemp, clanMsg6.szMsg);

						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);

						strcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					bPFlag = FALSE;
					C_menuN2 = -1;
					break;
				}
				else if((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "0") == 0))
				{
					strcpy(cldata.PFlag, "2");
					strcpy(szTemp, clanMakeFinishClan.szMsg);
					wsprintf(szDrawMenuMsg, clanMakeFinishClan.szMsg, cldata.name);
					strcpy(clanMakeFinishClan.szMsg, szDrawMenuMsg);

					CheckMsgPos(&clanMakeFinishClan, BOX_MAX_WIDTH, 0);
					C_menuN = CLANCHIP_MAKE_FIRSTMESSAGE;
					menuInit(C_menuN);
					strcpy(clanMakeFinishClan.szMsg, szTemp);
					C_menuN2 = -1;
					bPFlag = TRUE;
					break;
				}








				else if((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "2") == 0) && (nClanWon_Num < 5))
				{

					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					strcpy(szTemp, clanMsg6.szMsg);
					strcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					strcpy(clanMsg6.szMsg, szTemp);

					if(cldata.bIsOneDay)
					{

						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						strcpy(szTemp, clanMsg6.szMsg);
						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						strcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);

						strcpy(szTemp, clanMsg6.szMsg);

						strcpy(clanMsg6.szMsg, szDrawMenuMsg);

						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);

						strcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = FALSE;
				}














				else
				{
					C_menuN = CLAN_CHIP;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = TRUE;
				}
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_CHIP_ReadDATA에서 리턴코드 1 성공");
			#endif

				break;
				case 100:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (32)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				C_menuN2 = -1;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_CHIP_ReadDATA에서 리턴코드 100");
			#endif
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (33)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_CHIP_ReadDATA에서 서버에 접속할수 없음");
			#endif
				break;

				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_AllEnd;
					menuInit(C_menuN);

					C_menuN2 = -1;
				#ifdef CLAN_DEBUG
					DebugMessage("CLAN_CHIP_ReadDATA에서 디폴트에러");
				#endif
				}
				break;
			}
			break;
		}
		break;



	}

}




void CLANEntity_chip::RenderMain()
{
	if(life == 0) return;

}





void CLANEntity_chip::menuInit(int num)
{
	int bx = 0, by = 0;
	int      nNext = 0, i, nIconCount = 0, nIconPos = 0, nAdd = 0, nWidth = 0;
	int      nFirstIconSave = 0;
	switch(num)
	{


		case CLANCHIP_SUBCHIP_APPOINTMSG:
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


		menuPos[1].left = BackStartPos.x + SubChipAppointEnd.pos.x;
		menuPos[1].top = BackStartPos.y + SubChipAppointEnd.pos.y;

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
		case CLANCHIP_SUBCHIP_RELEASEMSG:
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


		menuPos[1].left = BackStartPos.x + SubChipReleaseEnd.pos.x;
		menuPos[1].top = BackStartPos.y + SubChipReleaseEnd.pos.y;

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
		case CLANCHIP_SUBCHIP_LIST:
		menuSu = 6 + DISPLAY_MAX + 9;

		nScl_Bar = 0;
		nSavePos = -1;
		nReleaseClanWon = 0;
		ZeroMemory(banisF, sizeof(banisF));
		memset(menuPos, 0, sizeof(RECT) * 30);





	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else

		bx = 32;
		by = 16;
	#endif

		menuPos[0].left = BackStartPos.x + BUTTON2_X;
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + BUTTONTEXT_WIDTH;
		menuPos[0].bottom = menuPos[0].top + BUTTONTEXT_HEIGHT;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[1].left = BackStartPos.x + BUTTON3_X;
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + BUTTONTEXT_WIDTH;
		menuPos[1].bottom = menuPos[1].top + BUTTONTEXT_HEIGHT;

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else
		bx = 68;
		by = 27;
	#endif

		menuPos[2].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[2].right = menuPos[2].left + BUTTONBOX_WIDTH;
		menuPos[2].bottom = menuPos[2].top + BUTTONBOX_HEIGHT;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[3].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[3].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[3].right = menuPos[3].left + BUTTONBOX_WIDTH;
		menuPos[3].bottom = menuPos[3].top + BUTTONBOX_HEIGHT;


		nIconCount = 3;

		memset(nClanWon, 0, sizeof(int) * 40);

		for(i = 0; i < nClanWon_Num; i++)

		{
			if(i >= DISPLAY_MAX) break;
			nIconCount += 1;

		#ifdef USE_PROSTONTALE		
			bx = 13;
			by = 17;
		#else
			bx = 13;
			by = 17;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 13;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;
			nNext += 1;
			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
		}
		nIconCount = 11;


		if(nClanWon_Num > DISPLAY_MAX)

		{
			nIconCount += 1;
		#ifdef USE_PROSTONTALE		
			bx = 8;
			by = 160;
		#else
			bx = 8;
			by = 160;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + SCROLLBAR_LEFT;
			menuPos[nIconCount].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 8;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 160;
			nClanWon[nIconCount] = 1;



			tscr.Init(1);
			tscr.Init(menuPos[nIconCount].top,
					  menuPos[nIconCount].top + 160,
					  nClanWon_Num, DISPLAY_MAX);

			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;
			scrIconPos.top = menuPos[nIconCount].top - 8;
		}

		nIconCount += 1;
	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[nIconCount].left = BackStartPos.x + CLANTITLE_X;
		menuPos[nIconCount].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[nIconCount].right = menuPos[nIconCount].left + bx;
		menuPos[nIconCount].bottom = menuPos[nIconCount].top + by;


		nIconCount += 1;
	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[nIconCount].left = BackStartPos.x + 9;
		menuPos[nIconCount].top = BackStartPos.y + 109 - 70;
		menuPos[nIconCount].right = menuPos[nIconCount].left + bx;
		menuPos[nIconCount].bottom = menuPos[nIconCount].top + by;
		break;

		case CLANCHIP_RESUBCHIP_APPOINT:
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


		menuPos[2].left = BackStartPos.x + SubChipAppoint.pos.x;
		menuPos[2].top = BackStartPos.y + SubChipAppoint.pos.y + 30;
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

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else			
		bx = 68;
		by = 27;
	#endif
		menuPos[5].left = BackStartPos.x + 9;
		menuPos[5].top = BackStartPos.y + 109 - 65;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else			
		bx = 68;
		by = 27;
	#endif
		menuPos[6].left = BackStartPos.x + CLANTITLE_X;
		menuPos[6].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

		break;
		case CLANCHIP_RESUBCHIP_APPOINT_END:
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


		menuPos[1].left = BackStartPos.x + SubChipAppointEnd.pos.x;
		menuPos[1].top = BackStartPos.y + SubChipAppointEnd.pos.y;

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
		case CLANCHIP_RELEASESUBCHIP:
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


		menuPos[2].left = BackStartPos.x + SubChipRelease.pos.x;
		menuPos[2].top = BackStartPos.y + SubChipRelease.pos.y + 30;
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

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else			
		bx = 68;
		by = 27;
	#endif
		menuPos[5].left = BackStartPos.x + 9;
		menuPos[5].top = BackStartPos.y + 109 - 65;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else			
		bx = 68;
		by = 27;
	#endif
		menuPos[6].left = BackStartPos.x + CLANTITLE_X;
		menuPos[6].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

		break;
		case CLANCHIP_RELEASESUBCHIP_END:
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


		menuPos[1].left = BackStartPos.x + SubChipReleaseEnd.pos.x;
		menuPos[1].top = BackStartPos.y + SubChipReleaseEnd.pos.y;

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
		case CLAN_CHIP:
		menuSu = 20;
	#ifdef USE_PROSTONTALE		
		if(hMark == NULL) hMark = GetClanMark();

	#else
		if(hMark == NULL) hMark = GetClanMark();
	#endif

	#ifdef USE_PROSTONTALE		
		bx = 152;
		by = 28;
	#else			
		bx = 152;
		by = 28;
	#endif


		menuPos[0].left = BackStartPos.x + CLANNAME_X;
		menuPos[0].top = BackStartPos.y + CLANNAME_Y + 4;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else			
		bx = 64;
		by = 16;
	#endif

		menuPos[10].left = BackStartPos.x + CLANNAMETEXT_X;
		menuPos[10].top = BackStartPos.y + CLANNAMETEXT_Y + 4;
		menuPos[10].right = 0;
		menuPos[10].bottom = 0;

	#ifdef USE_PROSTONTALE		
		bx = 16;
		by = 16;
	#else
		bx = 16;
		by = 16;
	#endif

		menuPos[1].left = BackStartPos.x + CLANMARKBOX_X - 68;
		menuPos[1].top = BackStartPos.y + CLANMARKBOX_Y + 55;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 16;
		by = 16;
	#else

		bx = 16;
		by = 16;
	#endif

		menuPos[9].left = BackStartPos.x + CLANMARK_X - 68;
		menuPos[9].top = BackStartPos.y + CLANMARK_Y + 55;
		menuPos[9].right = menuPos[9].left + bx;
		menuPos[9].bottom = menuPos[9].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 48;
		by = 23;
	#else			
		bx = 48;
		by = 23;
	#endif

		menuPos[8].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[8].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[8].right = menuPos[8].left + bx;
		menuPos[8].bottom = menuPos[8].top + by;


	#ifdef USE_PROSTONTALE		
		bx = 50;
		by = 44;
	#else			
		bx = 50;
		by = 44;
	#endif

		menuPos[2].left = -1;
		menuPos[2].top = -1;
		menuPos[2].right = -1;
		menuPos[2].bottom = -1;


	#ifdef USE_PROSTONTALE		
		bx = 120;
		by = 30;
	#else			
		bx = 120;
		by = 30;
	#endif

		menuPos[3].left = BackStartPos.x + CLANCHIPMENU_REMOVE_X;
		menuPos[3].top = BackStartPos.y + CLANCHIPMENU_REMOVE_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 120;
		by = 30;
	#else

		bx = 120;
		by = 30;
	#endif

		menuPos[4].left = BackStartPos.x + CLANCHIPMENU_RELEASE_X;
		menuPos[4].top = BackStartPos.y + CLANCHIPMENU_RELEASE_y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 120;
		by = 30;
	#else

		bx = 120;
		by = 30;
	#endif

		menuPos[5].left = BackStartPos.x + CLANCHIPMENU_HELP_X;
		menuPos[5].top = BackStartPos.y + CLANCHIPMENU_HELP_Y;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else			
		bx = 32;
		by = 16;
	#endif

		menuPos[6].left = BackStartPos.x + BUTTON1_X;
		menuPos[6].top = BackStartPos.y + BUTTON1_Y;
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 48;
		by = 27;
	#else			
		bx = 48;
		by = 27;
	#endif

		menuPos[7].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[7].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[7].right = menuPos[7].left + bx;
		menuPos[7].bottom = menuPos[7].top + by;


	#ifdef USE_PROSTONTALE		
		bx = 30;
		by = 30;
	#else			
		bx = 30;
		by = 30;
	#endif

		menuPos[11].left = BackStartPos.x + 75;
		menuPos[11].top = BackStartPos.y + 105;
		menuPos[11].right = menuPos[11].left + bx;
		menuPos[11].bottom = menuPos[11].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 30;
		by = 30;
	#else			
		bx = 30;
		by = 30;
	#endif

		menuPos[12].left = BackStartPos.x + 216;
		menuPos[12].top = BackStartPos.y + 105;
		menuPos[12].right = menuPos[12].left + bx;
		menuPos[12].bottom = menuPos[12].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 30;
		by = 30;
	#else			
		bx = 30;
		by = 30;
	#endif

		menuPos[13].left = BackStartPos.x + 75;
		menuPos[13].top = BackStartPos.y + 155;
		menuPos[13].right = menuPos[13].left + bx;
		menuPos[13].bottom = menuPos[13].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 30;
		by = 30;
	#else			
		bx = 30;
		by = 30;
	#endif

		menuPos[14].left = BackStartPos.x + 216;
		menuPos[14].top = BackStartPos.y + 155;
		menuPos[14].right = menuPos[14].left + bx;
		menuPos[14].bottom = menuPos[14].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 30;
		by = 30;
	#else			
		bx = 30;
		by = 30;
	#endif

		menuPos[15].left = BackStartPos.x + 75;
		menuPos[15].top = BackStartPos.y + 205;
		menuPos[15].right = menuPos[15].left + bx;
		menuPos[15].bottom = menuPos[15].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 30;
		by = 30;
	#else			
		bx = 30;
		by = 30;
	#endif
		menuPos[16].left = BackStartPos.x + 216;
		menuPos[16].top = BackStartPos.y + 205;
		menuPos[16].right = menuPos[16].left + bx;
		menuPos[16].bottom = menuPos[16].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 30;
		by = 30;
	#else			
		bx = 30;
		by = 30;
	#endif
		menuPos[17].left = BackStartPos.x + 9;
		menuPos[17].top = BackStartPos.y + 109 - 60;
		menuPos[17].right = menuPos[17].left + bx;
		menuPos[17].bottom = menuPos[17].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 120;
		by = 30;
	#else			
		bx = 120;
		by = 30;
	#endif
		menuPos[18].left = BackStartPos.x + CLANCHIPMENU_LC_X;
		menuPos[18].top = BackStartPos.y + CLANCHIPMENU_LC_Y;
		menuPos[18].right = menuPos[18].left + bx;
		menuPos[18].bottom = menuPos[18].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 120;
		by = 30;
	#else			
		bx = 120;
		by = 30;
	#endif
		menuPos[19].left = BackStartPos.x + CLANCHIPMENU_SUBCHIP_X;
		menuPos[19].top = BackStartPos.y + CLANCHIPMENU_SUBCHIP_Y;
		menuPos[19].right = menuPos[19].left + bx;
		menuPos[19].bottom = menuPos[19].top + by;




		break;
		case CLANCHIP_LEAVECLAN_MESSAGE:
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


		menuPos[1].left = BackStartPos.x + LeaveClanMessage.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanMessage.pos.y;

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
		case CLANCHIP_LEAVECLAN_RECONFIRM:
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


		menuPos[2].left = BackStartPos.x + LeaveClanReConfirm.pos.x;
		menuPos[2].top = BackStartPos.y + LeaveClanReConfirm.pos.y;
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
		case CLANCHIP_LEAVECLANDOWNLEVEL:
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


		menuPos[1].left = BackStartPos.x + LeaveClanDownLevel.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanDownLevel.pos.y;

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
		case CLANCHIP_NOSUBCHIP:
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


		menuPos[1].left = BackStartPos.x + NoSubChip.pos.x;
		menuPos[1].top = BackStartPos.y + NoSubChip.pos.y;

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

		case CLANCHIP_NOLEAVECLAN:
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


		menuPos[1].left = BackStartPos.x + NoLeaveClan.pos.x;
		menuPos[1].top = BackStartPos.y + NoLeaveClan.pos.y;

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
		case CLANCHIP_LEAVECLAN_NOLEVEL:
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


		menuPos[1].left = BackStartPos.x + LeaveClanNoLevel.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanNoLevel.pos.y;

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
		case CLANCHIP_LEAVECLAN_CONFIRM:
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


		menuPos[2].left = BackStartPos.x + LeaveClanConfirm.pos.x;
		menuPos[2].top = BackStartPos.y + LeaveClanConfirm.pos.y + 30;
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

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else			
		bx = 68;
		by = 27;
	#endif
		menuPos[5].left = BackStartPos.x + 9;
		menuPos[5].top = BackStartPos.y + 109 - 65;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else			
		bx = 68;
		by = 27;
	#endif
		menuPos[6].left = BackStartPos.x + CLANTITLE_X;
		menuPos[6].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

		break;
		case CLANCHIP_LEAVECLAN_NOMONEY:
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


		menuPos[1].left = BackStartPos.x + LeaveClanNoMoney.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanNoMoney.pos.y;

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
		case CLANCHIP_LEAVECLAN_SUCESS:
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


		menuPos[1].left = BackStartPos.x + LeaveClanSuccess.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanSuccess.pos.y;

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
		case CLANCHIP_LEAVECLAN:
		menuSu = 6 + DISPLAY_MAX + 9;

		nScl_Bar = 0;
		nSavePos = -1;
		nReleaseClanWon = 0;
		ZeroMemory(banisF, sizeof(banisF));
		memset(menuPos, 0, sizeof(RECT) * 30);





	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else

		bx = 32;
		by = 16;
	#endif

		menuPos[0].left = BackStartPos.x + BUTTON2_X;
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + BUTTONTEXT_WIDTH;
		menuPos[0].bottom = menuPos[0].top + BUTTONTEXT_HEIGHT;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[1].left = BackStartPos.x + BUTTON3_X;
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + BUTTONTEXT_WIDTH;
		menuPos[1].bottom = menuPos[1].top + BUTTONTEXT_HEIGHT;

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else
		bx = 68;
		by = 27;
	#endif

		menuPos[2].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[2].right = menuPos[2].left + BUTTONBOX_WIDTH;
		menuPos[2].bottom = menuPos[2].top + BUTTONBOX_HEIGHT;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[3].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[3].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[3].right = menuPos[3].left + BUTTONBOX_WIDTH;
		menuPos[3].bottom = menuPos[3].top + BUTTONBOX_HEIGHT;


		nIconCount = 3;

		memset(nClanWon, 0, sizeof(int) * 40);

		for(i = 0; i < nClanWon_Num; i++)

		{
			if(i >= DISPLAY_MAX) break;
			nIconCount += 1;

		#ifdef USE_PROSTONTALE		
			bx = 13;
			by = 17;
		#else
			bx = 13;
			by = 17;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 13;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;
			nNext += 1;
			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
		}
		nIconCount = 11;


		if(nClanWon_Num > DISPLAY_MAX)

		{
			nIconCount += 1;
		#ifdef USE_PROSTONTALE		
			bx = 8;
			by = 160;
		#else
			bx = 8;
			by = 160;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + SCROLLBAR_LEFT;
			menuPos[nIconCount].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 8;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 160;
			nClanWon[nIconCount] = 1;



			tscr.Init(1);
			tscr.Init(menuPos[nIconCount].top,
					  menuPos[nIconCount].top + 160,
					  nClanWon_Num, DISPLAY_MAX);

			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;
			scrIconPos.top = menuPos[nIconCount].top - 8;
		}

		nIconCount += 1;
	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[nIconCount].left = BackStartPos.x + CLANTITLE_X;
		menuPos[nIconCount].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[nIconCount].right = menuPos[nIconCount].left + bx;
		menuPos[nIconCount].bottom = menuPos[nIconCount].top + by;


		nIconCount += 1;
	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[nIconCount].left = BackStartPos.x + 9;
		menuPos[nIconCount].top = BackStartPos.y + 109 - 70;
		menuPos[nIconCount].right = menuPos[nIconCount].left + bx;
		menuPos[nIconCount].bottom = menuPos[nIconCount].top + by;
		break;
		case CLAN_REMOVE:
		menuSu = 6 + DISPLAY_MAX + 8;

		nScl_Bar = 0;
		nReleaseClanWon = 0;
		memset(menuPos, 0, sizeof(RECT) * 30);





	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else

		bx = 32;
		by = 16;
	#endif

		menuPos[0].left = BackStartPos.x + BUTTON2_X;
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + BUTTONTEXT_WIDTH;
		menuPos[0].bottom = menuPos[0].top + BUTTONTEXT_HEIGHT;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[1].left = BackStartPos.x + BUTTON3_X;
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + BUTTONTEXT_WIDTH;
		menuPos[1].bottom = menuPos[1].top + BUTTONTEXT_HEIGHT;

	#ifdef USE_PROSTONTALE		
		bx = 68;
		by = 27;
	#else
		bx = 68;
		by = 27;
	#endif

		menuPos[2].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[2].right = menuPos[2].left + BUTTONBOX_WIDTH;
		menuPos[2].bottom = menuPos[2].top + BUTTONBOX_HEIGHT;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[3].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[3].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[3].right = menuPos[3].left + BUTTONBOX_WIDTH;
		menuPos[3].bottom = menuPos[3].top + BUTTONBOX_HEIGHT;


		nIconCount = 3;

		memset(nClanWon, 0, sizeof(int) * 40);

		for(i = 0; i < nClanWon_Num; i++)

		{
			if(i >= DISPLAY_MAX) break;
			nIconCount += 1;

		#ifdef USE_PROSTONTALE		
			bx = 13;
			by = 17;
		#else
			bx = 13;
			by = 17;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 13;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;
			nNext += 1;
			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
		}
		nIconCount = 11;


		if(nClanWon_Num > DISPLAY_MAX)

		{
			nIconCount += 1;
		#ifdef USE_PROSTONTALE		
			bx = 8;
			by = 160;
		#else
			bx = 8;
			by = 160;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + SCROLLBAR_LEFT;
			menuPos[nIconCount].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 8;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 160;
			nClanWon[nIconCount] = 1;



			tscr.Init(1);
			tscr.Init(menuPos[nIconCount].top,
					  menuPos[nIconCount].top + 160,
					  nClanWon_Num, DISPLAY_MAX);

			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;
			scrIconPos.top = menuPos[nIconCount].top - 8;
		}

		nIconCount += 1;
	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[nIconCount].left = BackStartPos.x + CLANTITLE_X;
		menuPos[nIconCount].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[nIconCount].right = menuPos[nIconCount].left + bx;
		menuPos[nIconCount].bottom = menuPos[nIconCount].top + by;


		break;
		case CLAN_REMOVE_SHORTCLANWON:
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



		if(bRemoveSecondCheck)
		{
			menuPos[2].left = BackStartPos.x + clanRemoveSecond.pos.x;
			menuPos[2].top = BackStartPos.y + clanRemoveSecond.pos.y - 20;
		}
		else
		{
			menuPos[2].left = BackStartPos.x + clanszRemoveShortClanWonMsg.pos.x;
			menuPos[2].top = BackStartPos.y + clanszRemoveShortClanWonMsg.pos.y;
		}
		menuPos[2].right = menuPos[2].left + 190;
		menuPos[2].bottom = menuPos[2].top + 180;


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
		case CLAN_REMOVE_SHORTCLANWON_RESULT:
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


		if(bRemoveSecondCheck)
		{
			menuPos[1].left = BackStartPos.x + clanRemoveSecondResult.pos.x;
			menuPos[1].top = BackStartPos.y + clanRemoveSecondResult.pos.y;
		}
		else
		{
			menuPos[1].left = BackStartPos.x + clanRemoveShowrtClanWonResultMsg.pos.x;
			menuPos[1].top = BackStartPos.y + clanRemoveShowrtClanWonResultMsg.pos.y;
		}

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
		case CLAN_REMOVE_RESULT:
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


		menuPos[1].left = BackStartPos.x + clanReMoveHeaderMsg.pos.x;
		menuPos[1].top = BackStartPos.y + clanReMoveHeaderMsg.pos.y - 20;
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
		case CLANCHIP_RELEASEMESSAGE:
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


		menuPos[1].left = BackStartPos.x + clanClanUserRelease.pos.x;
		menuPos[1].top = BackStartPos.y + clanClanUserRelease.pos.y;
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
		case CLAN_WAREHOUSE_RIGHT:
		menuSu = 6;

	#ifdef USE_PROSTONTALE		

		bx = 13;
		by = 17;
	#else
		bx = 13;
		by = 17;
	#endif

		menuPos[0].left = BackStartPos.x + 70;
		menuPos[0].top = BackStartPos.y + 50 + WHR_ICON;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


	#ifdef USE_PROSTONTALE		
		bx = 13;
		by = 17;
	#else
		bx = 13;
		by = 17;
	#endif

		menuPos[1].left = BackStartPos.x + 70;
		menuPos[1].top = BackStartPos.y + 80 + WHR_ICON;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 13;
		by = 17;
	#else
		bx = 13;
		by = 17;
	#endif

		menuPos[2].left = BackStartPos.x + 70;
		menuPos[2].top = BackStartPos.y + 110 + WHR_ICON;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 13;
		by = 17;
	#else
		bx = 13;
		by = 17;
	#endif

		menuPos[3].left = BackStartPos.x + 70;
		menuPos[3].top = BackStartPos.y + 140 + WHR_ICON;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;


	#ifdef USE_PROSTONTALE		
		bx = 13;
		by = 17;
	#else
		bx = 13;
		by = 17;
	#endif

		menuPos[4].left = BackStartPos.x + 70;
		menuPos[4].top = BackStartPos.y + 170 + WHR_ICON;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;


	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[5].left = BackStartPos.x + BUTTON3_X;
		menuPos[5].top = BackStartPos.y + BUTTON3_Y;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;


		menuPos[6].left = menuPos[0].left + bx + XCAP;
		menuPos[6].top = menuPos[0].top + YDOWN;

		menuPos[7].left = menuPos[1].left + bx + XCAP;
		menuPos[7].top = menuPos[1].top + YDOWN;

		menuPos[8].left = menuPos[2].left + bx + XCAP;
		menuPos[8].top = menuPos[2].top + YDOWN;

		menuPos[9].left = menuPos[3].left + bx + XCAP;
		menuPos[9].top = menuPos[3].top + YDOWN;

		menuPos[10].left = menuPos[4].left + bx + XCAP;
		menuPos[10].top = menuPos[4].top + YDOWN;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else

		bx = 64;
		by = 16;
	#endif

		menuPos[11].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[11].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[11].right = menuPos[11].left + bx;
		menuPos[11].bottom = menuPos[11].top + by;

		break;





		case CLAN_MARK1:
		menuSu = 1;

	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON3_X;
		menuPos[0].top = BackStartPos.y + BUTTON3_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + 60;
		menuPos[1].top = BackStartPos.y + 100;
		menuPos[1].right = menuPos[1].left + 260;
		menuPos[1].bottom = menuPos[1].top + 180;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 64;
	#else
		bx = 64;
		by = 64;
	#endif
		menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;


	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[3].left = BackStartPos.x + CLANTEXT_IMAGE_X;
		menuPos[3].top = BackStartPos.y + CLANTEXT_IMAGE_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;
		break;
		case CLAN_MARK2:
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


	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[1].left = BackStartPos.x + BUTTON2_X;
		menuPos[1].top = BackStartPos.y + BUTTON2_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 64;
	#else
		bx = 64;
		by = 64;
	#endif

		menuPos[2].left = BackStartPos.x + 150;
		menuPos[2].top = BackStartPos.y + 150;
		menuPos[2].right = menuPos[2].left + 15;
		menuPos[2].bottom = menuPos[2].top + 15;




		menuPos[3].left = BackStartPos.x + 60;
		menuPos[3].top = BackStartPos.y + 100;
		menuPos[3].right = menuPos[3].left + 260;
		menuPos[3].bottom = menuPos[3].top + 180;


	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 64;
	#else
		bx = 64;
		by = 64;
	#endif

		menuPos[4].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[4].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[4].right = menuPos[4].left + 15;
		menuPos[4].bottom = menuPos[4].top + 15;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 64;
	#else
		bx = 64;
		by = 64;
	#endif

		menuPos[5].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[5].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[5].right = menuPos[5].left + 15;
		menuPos[5].bottom = menuPos[5].top + 15;

	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[6].left = BackStartPos.x + CLANTEXT_IMAGE_X;
		menuPos[6].top = BackStartPos.y + CLANTEXT_IMAGE_Y;
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

		break;
		case CLAN_MARK3:
		menuSu = 2;


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


	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 64;
	#else
		bx = 64;
		by = 64;
	#endif

		menuPos[1].left = BackStartPos.x + BUTTON2_X;
		menuPos[1].top = BackStartPos.y + BUTTON2_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 64;
	#else
		bx = 64;
		by = 64;
	#endif

		menuPos[2].left = BackStartPos.x + 100;
		menuPos[2].top = BackStartPos.y + 150;
		menuPos[2].right = menuPos[2].left + 15;
		menuPos[2].bottom = menuPos[2].top + 15;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 64;
	#else
		bx = 64;
		by = 64;
	#endif

		menuPos[3].left = BackStartPos.x + 200;
		menuPos[3].top = BackStartPos.y + 150;
		menuPos[3].right = menuPos[3].left + 15;
		menuPos[3].bottom = menuPos[3].top + 15;


		menuPos[4].left = BackStartPos.x + 60;
		menuPos[4].top = BackStartPos.y + 100;
		menuPos[4].right = menuPos[4].left + 260;
		menuPos[4].bottom = menuPos[4].top + 180;


	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 64;
	#else
		bx = 64;
		by = 64;
	#endif

		menuPos[5].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[5].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[5].right = menuPos[5].left + 15;
		menuPos[5].bottom = menuPos[5].top + 15;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 64;
	#else
		bx = 64;
		by = 64;
	#endif

		menuPos[6].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[6].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[6].right = menuPos[6].left + 15;
		menuPos[6].bottom = menuPos[6].top + 15;

	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[7].left = BackStartPos.x + CLANTEXT_IMAGE_X;
		menuPos[7].top = BackStartPos.y + CLANTEXT_IMAGE_Y;
		menuPos[7].right = menuPos[7].left + bx;
		menuPos[7].bottom = menuPos[7].top + by;
		break;


		case CLAN_RELEASE:
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


		menuPos[2].left = BackStartPos.x + clanMsg15.pos.x;
		menuPos[2].top = BackStartPos.y + clanMsg15.pos.y;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;


	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif

		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[5].left = BackStartPos.x + CLANTITLE_X;
		menuPos[5].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

		break;
		case CLAN_RECONF_RELEASE:
		menuSu = 6;

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


		menuPos[2].left = BackStartPos.x + CLAN_RECONF_RELEASE_X;
		menuPos[2].top = BackStartPos.y + CLAN_RECONF_RELEASE_Y;
		menuPos[2].right = 0;
		menuPos[2].bottom = 0;


	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif

		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[5].left = BackStartPos.x + CLANTITLE_X;
		menuPos[5].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;



		break;
		case CLAN_FINISH_RELEASE:
		menuSu = 4;

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

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif

		menuPos[1].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[1].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif

		menuPos[2].left = BackStartPos.x + CLANTITLE_X;
		menuPos[2].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;


		menuPos[3].left = BackStartPos.x + clanFinishReleaseMsg.pos.x;
		menuPos[3].top = BackStartPos.y + clanFinishReleaseMsg.pos.y;
		menuPos[3].right = 0;
		menuPos[3].bottom = 0;

		break;
		case CLAN_HELP:
		menuSu = 2 + CLANHELPICON_DISPLAY_MAX + 3;


		nScl_Bar = 0;




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

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[1].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[1].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		nIconPos = 2;
		nAdd = 0;
		for(i = 0; i < CLANHELPICON_DISPLAY_MAX; i++)
		{
		#ifdef USE_PROSTONTALE		
			bx = CLANTEXT_IMAGE_WIDTH;
			by = CLANTEXT_IMAGE_HEIGHT;
		#else

			bx = CLANTEXT_IMAGE_WIDTH;
			by = CLANTEXT_IMAGE_HEIGHT;
		#endif

			menuPos[nIconPos].left = BackStartPos.x + CLANHELPLIST_X;
			menuPos[nIconPos].top = BackStartPos.y + CLANHELPLIST_Y + nAdd;
			menuPos[nIconPos].right = menuPos[nIconPos].left + CLANHELPICON_WIDTH;
			menuPos[nIconPos].bottom = menuPos[nIconPos].top + CLANHELPICON_HEIGHT;
			nIconPos += 1;
			nAdd += CLANHELPICON_CAP;

		}
		nIconPos = 6;


		tscr.Init(0);


		if(g_nClanIconNum > CLANHELPICON_DISPLAY_MAX)

		{

		#ifdef USE_PROSTONTALE		
			bx = 16;
			by = 16;
		#else
			bx = 16;
			by = 16;
		#endif


			menuPos[nIconPos].left = BackStartPos.x + SCROLLBAR_LEFT;
			menuPos[nIconPos].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconPos].right = menuPos[nIconPos].left + 8;
			menuPos[nIconPos].bottom = menuPos[nIconPos].top + 160;



			tscr.Init(1);
			tscr.Init(menuPos[nIconPos].top,
					  menuPos[nIconPos].top + 160,
					  g_nClanIconNum, CLANHELPICON_DISPLAY_MAX);

			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;
			scrIconPos.top = menuPos[nIconPos].top - 8;
		}

		nIconPos += 1;

	#ifdef USE_PROSTONTALE		
		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#else

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;
	#endif
		menuPos[nIconPos].left = BackStartPos.x + CLANTITLE_X;
		menuPos[nIconPos].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[nIconPos].right = menuPos[nIconPos].left + bx;
		menuPos[nIconPos].bottom = menuPos[nIconPos].top + by;


		break;
		case CLAN_HELP_CONTENT:
		menuSu = 1 + HLEPDISPLAY_MAX + 5;

		nScl_Bar = 0;
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
	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[1].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[1].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 120;
		by = 30;
	#else

		bx = 120;
		by = 30;
	#endif
		menuPos[2].left = BackStartPos.x + CLANTITLE_X;
		menuPos[2].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 30;
		by = 30;
	#else

		bx = 30;
		by = 30;
	#endif

		menuPos[3].left = BackStartPos.x + 14;
		menuPos[3].top = BackStartPos.y + 12;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 30;
		by = 30;
	#else

		bx = 30;
		by = 30;
	#endif

		menuPos[4].left = BackStartPos.x + 9;
		menuPos[4].top = BackStartPos.y + 45;
		menuPos[4].right = menuPos[3].left + bx;
		menuPos[4].bottom = menuPos[3].top + by;




		nIconPos = 5;



		if(g_HelpDisPlay > HLEPDISPLAY_MAX)

		{

		#ifdef USE_PROSTONTALE		
			bx = 16;
			by = 16;
		#else
			bx = 16;
			by = 16;
		#endif

			menuPos[nIconPos].left = BackStartPos.x + SCROLLBAR_LEFT;
			menuPos[nIconPos].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconPos].right = menuPos[nIconPos].left + 8;
			menuPos[nIconPos].bottom = menuPos[nIconPos].top + 160;


			tscr.Init(1);
			tscr.Init(menuPos[nIconPos].top,
					  menuPos[nIconPos].top + 160,
					  g_HelpDisPlay, HLEPDISPLAY_MAX);

			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;
			scrIconPos.top = menuPos[nIconPos].top - 8;
		}


		nIconPos = 7;
		nAdd = 0;
		for(i = 0; i < HLEPDISPLAY_MAX; i++)
		{
		#ifdef USE_PROSTONTALE		
			bx = 64;
			by = 16;
		#else
			bx = 64;
			by = 16;
		#endif

			menuPos[nIconPos].left = BackStartPos.x + HELPCONTENT_X;
			menuPos[nIconPos].top = BackStartPos.y + HELPCONTENT_Y + nAdd;
			menuPos[nIconPos].right = 0;
			menuPos[nIconPos].bottom = 0;
			nIconPos += 1;
			nAdd += HELPCONTENT_CAP;
		}



		break;
		case CLANCHIP_MAKE_FIRSTMESSAGE:
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


		menuPos[1].left = BackStartPos.x + clanMakeFinishClan.pos.x;
		menuPos[1].top = BackStartPos.y + clanMakeFinishClan.pos.y;

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
		case CLANCHIP_DOWN6_CLANWON:
		case CLANCHIP_DOWN6_CLANWON_MESSAGE:
		case CLAN_NOMAKE:
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


		menuPos[1].left = BackStartPos.x + clanMsg6.pos.x;
		menuPos[1].top = BackStartPos.y + clanMsg6.pos.y;

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
		case CLANCHIP_SUBCHIP_LOAD_DATA:
		case CLANCHIP_SUBCHIP_READMSG_FLAG:
		case	CLANCHIP_APPOINTSUBCHIP_DO:
		case CLANCHIP_RELEASESUBCHIP_DO:
		case CLANCHIP_LEAVECLAN_PFLAG:
		case CLANCHIP_LEAVECLAN_DO:
		case ISPFLAG_CHIP:
		case CLAN_REMOVE_SHORTCLANWON_LOADING:
		case CLAN_REMOVE_LOADING:
		case CLAN_RELEASE_LOADING:
		case CLAN_CHIP_ReadDATA:


		menuPos[0].left = BackStartPos.x + clanLoading.pos.x;
		menuPos[0].top = BackStartPos.y + clanLoading.pos.y;
		menuPos[0].right = 0;
		menuPos[0].bottom = 0;

		break;
	}
}






int CLANEntity_chip::chkMark(char *clanName)
{
	nChkMark = -1;
	if(!SearchMarkClient(clanName))
	{
		if(!SearchMarkServer(clanName))
		{
			nChkMark = 0;
		}
	}
	else if(SearchMarkClient(clanName))
	{
		if(!SearchMarkServer(clanName))
		{
			nChkMark = 1;
		}
		else
		{
			nChkMark = 2;
		}
	}

	return nChkMark;
}

BOOL CLANEntity_chip::CheckMark(char* filename)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	char szTemp[50];
	memset(szTemp, 0, sizeof(char) * 50);

	wsprintf(szTemp, "image\\clanDATA\\%s.bmp", filename);
	hFind = FindFirstFile(szTemp, &wfd);

	if(hFind == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CLANEntity_chip::SearchMarkClient(char *clanName)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	char szTemp[50];
	memset(szTemp, 0, sizeof(char) * 50);

	wsprintf(szTemp, "image\\clanDATA\\%s.bmp", clanName);
	hFind = FindFirstFile(szTemp, &wfd);

	if(hFind == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

#ifdef USE_PROSTONTALE
	hClinetMark = LoadDibSurfaceOffscreen(szTemp);
#else
	hClinetMark = (HBITMAP)LoadImage(NULL, szTemp,
									 IMAGE_BITMAP,
									 0, 0,
									 LR_LOADFROMFILE);

#endif

	FindClose(hFind);
	return TRUE;
}

BOOL CLANEntity_chip::SearchMarkServer(char *clanName)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	char szTemp[50];
	memset(szTemp, 0, sizeof(char) * 50);

	wsprintf(szTemp, "image\\clanDATA\\%s.bmp", clanName);
	hFind = FindFirstFile(szTemp, &wfd);

	if(hFind == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
#ifdef USE_PROSTONTALE
	hServerMark = LoadDibSurfaceOffscreen(szTemp);
#else
	hServerMark = (HBITMAP)LoadImage(NULL, szTemp,
									 IMAGE_BITMAP,
									 0, 0,
									 LR_LOADFROMFILE);
#endif

	FindClose(hFind);
	return TRUE;
}




void CLANEntity_chip::Draw()
{
	int i = 0, nIconCount = 0;
	int nIconPos = 0;
	char szClanWon[30];
	int nSaveTop = 0, nAdd = 0;
	int nStrLen = 0;

	int bx, by;
	char szTemp[256];


#ifdef USE_PROSTONTALE		
	char szHelpContent[HELPWIDTH];
#else
	HDC hdc;
	HDC sorDC;
	BITMAP bit;


	RECT rect;
	int j = 0;
	char szHelpContent[HELPWIDTH];




#endif
	char string[500];
#ifdef USE_PROSTONTALE		


	switch(C_menuN)
	{


		case CLANCHIP_SUBCHIP_APPOINTMSG:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		if(cldata.SubChip[0] == 0)
		{
			wsprintf(szDrawMenuMsg, SubChipAppointEnd.szMsg, cldata.OldSubChip);
		}
		else
		{
			wsprintf(szDrawMenuMsg, SubChipAppointEnd.szMsg, cldata.SubChip);
		}
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLANCHIP_SUBCHIP_RELEASEMSG:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, SubChipReleaseEnd.szMsg, cldata.OldSubChip);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;

		case CLANCHIP_SUBCHIP_LIST:
		nIconCount = 11;
		if(nClanWon_Num > DISPLAY_MAX)
		{
			nIconCount += 1;




			DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hScl_Bar,
					   0, 0, 8, 160, 1);

			renderDevice.BeginScene();




			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);
			renderDevice.EndScene();

		}
		nIconCount += 1;
		DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hTxt_SubChip[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		nIconCount += 1;

		renderDevice.BeginScene();
		sinDrawTexImage(hLine, (float)menuPos[nIconCount].left, (float)menuPos[nIconCount].top,
			(float)240, 10.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);
		renderDevice.EndScene();





		nIconCount = 3;
		for(i = 0; i < DISPLAY_MAX; i++)
		{
			if(i == nClanWon_Num) break;
			nIconCount += 1;
			if(banisF[nScl_Bar + i])
			{
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon_Click, 0, 0, 13, 17, 1);
			}
			else
			{
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon, 0, 0, 13, 17, 1);
			}
		}


		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0) DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);


		nIconCount = 15;
		nAdd = 0;
		for(i = 0; i < nClanWon_Num; i++)
		{
			if(i >= DISPLAY_MAX) break;

		#ifdef USE_PROSTONTALE		
			bx = 13;
			by = 17;
		#else
			GetObject(hIcon, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X + 30;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = (BackStartPos.x + 120) + cldata.clanWonStrLen[i + nScl_Bar];
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;

			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
			nIconCount += 1;
		}

		nIconCount = 15;
		for(i = 0; i < DISPLAY_MAX; i++)
		{

			if(nClanWon[nIconCount])
			{
				if(strcmp(cldata.clanWon[i + nScl_Bar], cldata.SubChip) == 0)
				{
					strcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
					Draw_C_Text2(szClanWon, menuPos[nIconCount].left + 30, menuPos[nIconCount].top);
				}
				else
				{
					ZeroMemory(szClanWon, sizeof(szClanWon));
					strcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
					Draw_C_Text(szClanWon, menuPos[nIconCount].left + 30, menuPos[nIconCount].top);
				}
				nIconCount += 1;
			}
		}

		break;
		case CLANCHIP_RESUBCHIP_APPOINT:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[6].left, menuPos[6].top, hTxt_LeaveClan[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		renderDevice.BeginScene();
		sinDrawTexImage(hLine, (float)menuPos[5].left, (float)menuPos[5].top,
			(float)240, 10.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);
		renderDevice.EndScene();
		wsprintf(szDrawMenuMsg, SubChipAppoint.szMsg, cldata.clanWon[nSavePos]);
		Draw_C_Text(szDrawMenuMsg, menuPos[2].left, menuPos[2].top);

		break;

		case CLANCHIP_RESUBCHIP_APPOINT_END:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		wsprintf(szDrawMenuMsg, SubChipAppointEnd.szMsg, cldata.clanWon[nSavePos]);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLANCHIP_RELEASESUBCHIP:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[6].left, menuPos[6].top, hTxt_LeaveClan[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		renderDevice.BeginScene();
		sinDrawTexImage(hLine, (float)menuPos[5].left, (float)menuPos[5].top,
			(float)240, 10.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);
		renderDevice.EndScene();
		wsprintf(szDrawMenuMsg, SubChipRelease.szMsg, cldata.SubChip);
		Draw_C_Text(szDrawMenuMsg, menuPos[2].left, menuPos[2].top);

		break;
		case CLANCHIP_RELEASESUBCHIP_END:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		wsprintf(szDrawMenuMsg, SubChipReleaseEnd.szMsg, cldata.SubChip);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;

		case CLAN_CHIP:


		DrawSprite(menuPos[0].left, menuPos[0].top, hClanName, 0, 0, CLANNAME_WIDTH, CLANNAME_HEIGHT, 1);


		if(menuMouseOver[3] > 0)
		{
			DrawSprite(menuPos[3].left, menuPos[3].top, hTxt_Remove[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);;
		}
		else
		{
			DrawSprite(menuPos[3].left, menuPos[3].top, hTxt_Remove[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		}

		if(menuMouseOver[4] > 0)
		{
			DrawSprite(menuPos[4].left, menuPos[4].top, hTxt_Release[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		}
		else
		{
			DrawSprite(menuPos[4].left, menuPos[4].top, hTxt_Release[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		}

		if(menuMouseOver[5] > 0)
		{


			DrawSprite(menuPos[5].left, menuPos[5].top, hTxt_Help[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		}
		else
		{


			DrawSprite(menuPos[5].left, menuPos[5].top, hTxt_Help[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		}

		if(menuMouseOver[18] > 0)
		{
			DrawSprite(menuPos[18].left, menuPos[18].top, hTxt_LeaveClan[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		}
		else
		{
			DrawSprite(menuPos[18].left, menuPos[18].top, hTxt_LeaveClan[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		}



	#ifdef __CLANSUBCHIP__
		if(menuMouseOver[19] > 0)
		{


			DrawSprite(menuPos[19].left, menuPos[19].top, hTxt_SubChip[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		}
		else
		{



			DrawSprite(menuPos[19].left, menuPos[19].top, hTxt_SubChip[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		}
	#endif




		DrawSprite(menuPos[1].left, menuPos[1].top, hMark_box, 0, 0, 69, 59, 1);

		if(cldata.hClanMark)
		{










			DrawSprite(menuPos[9].left, menuPos[9].top, cldata.hClanMark, 0, 0, 32, 32, 1);
		}


		DrawSprite(menuPos[7].left, menuPos[7].top, hButton_Box, 0, 0, 48, 23, 1);

		if(menuMouseOver[6] > 0) DrawSprite(menuPos[6].left, menuPos[6].top, hClose[1], 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[6].left, menuPos[6].top, hClose[0], 0, 0, 32, 16, 1);

		nStrLen = lstrlen(cldata.name) / 2;

		if(nStrLen % 2)
		{
			nStrLen = nStrLen / 2;
			nStrLen += 1;
			Draw_C_Text(cldata.name, menuPos[10].left - (nStrLen * 11), menuPos[10].top, 2);
		}
		else
		{
			nStrLen = nStrLen / 2;
			Draw_C_Text(cldata.name, menuPos[10].left - (nStrLen * 11) - 3, menuPos[10].top, 2);
		}

		renderDevice.BeginScene();
		sinDrawTexImage(hLine, (float)menuPos[17].left, (float)menuPos[17].top,
			(float)240, 10.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);
		renderDevice.EndScene();


		break;
		case CLANCHIP_LEAVECLAN_NOLEVEL:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(LeaveClanNoLevel.szMsg, menuPos[1].left, menuPos[1].top);

		break;
		case CLANCHIP_LEAVECLAN_RECONFIRM:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, LeaveClanReConfirm.szMsg, cldata.clanWon[nSavePos]);
		Draw_C_Text(szDrawMenuMsg, menuPos[2].left, menuPos[2].top);

		break;
		case CLANCHIP_LEAVECLAN_CONFIRM:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[6].left, menuPos[6].top, hTxt_LeaveClan[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		renderDevice.BeginScene();
		sinDrawTexImage(hLine, (float)menuPos[5].left, (float)menuPos[5].top,
			(float)240, 10.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);
		renderDevice.EndScene();
		Draw_C_Text(LeaveClanConfirm.szMsg, menuPos[2].left, menuPos[2].top);

		break;
		case CLANCHIP_LEAVECLAN_MESSAGE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, LeaveClanMessage.szMsg, cldata.OldChipChaName, cldata.ClanZang_Name);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLANCHIP_LEAVECLANDOWNLEVEL:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(LeaveClanDownLevel.szMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLANCHIP_NOSUBCHIP:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(NoSubChip.szMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLANCHIP_NOLEAVECLAN:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(NoLeaveClan.szMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLANCHIP_LEAVECLAN_NOMONEY:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(LeaveClanNoMoney.szMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLANCHIP_LEAVECLAN_SUCESS:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		wsprintf(szDrawMenuMsg, LeaveClanSuccess.szMsg, cldata.clanWon[nSavePos]);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;


		case CLANCHIP_LEAVECLAN:
		nIconCount = 11;
		if(nClanWon_Num > DISPLAY_MAX)
		{
			nIconCount += 1;




			DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hScl_Bar,
					   0, 0, 8, 160, 1);

			renderDevice.BeginScene();




			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);
			renderDevice.EndScene();

		}
		nIconCount += 1;
		DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hTxt_LeaveClan[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		nIconCount += 1;

		renderDevice.BeginScene();
		sinDrawTexImage(hLine, (float)menuPos[nIconCount].left, (float)menuPos[nIconCount].top,
			(float)240, 10.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);
		renderDevice.EndScene();





		nIconCount = 3;
		for(i = 0; i < DISPLAY_MAX; i++)
		{
			if(i == nClanWon_Num) break;
			nIconCount += 1;
			if(banisF[nScl_Bar + i])
			{
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon_Click, 0, 0, 13, 17, 1);
			}
			else
			{
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon, 0, 0, 13, 17, 1);
			}
		}


		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0) DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);


		nIconCount = 15;
		nAdd = 0;
		for(i = 0; i < nClanWon_Num; i++)
		{
			if(i >= DISPLAY_MAX) break;

		#ifdef USE_PROSTONTALE		
			bx = 13;
			by = 17;
		#else
			GetObject(hIcon, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X + 30;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = (BackStartPos.x + 120) + cldata.clanWonStrLen[i + nScl_Bar];
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;

			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
			nIconCount += 1;
		}

		nIconCount = 15;
		for(i = 0; i < DISPLAY_MAX; i++)
		{

			if(nClanWon[nIconCount])
			{
				ZeroMemory(szClanWon, sizeof(szClanWon));
				strcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
				Draw_C_Text(szClanWon, menuPos[nIconCount].left + 30, menuPos[nIconCount].top);
				nIconCount += 1;
			}
		}
		break;


		case CLAN_REMOVE:
		nIconCount = 11;
		if(nClanWon_Num > DISPLAY_MAX)
		{
			nIconCount += 1;




			DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hScl_Bar,
					   0, 0, 8, 160, 1);

			renderDevice.BeginScene();




			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);
			renderDevice.EndScene();

		}
		nIconCount += 1;
		DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hTxt_Remove[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);




		nIconCount = 3;
		for(i = 0; i < DISPLAY_MAX; i++)
		{
			if(i == nClanWon_Num) break;
			nIconCount += 1;
			if(banisF[nScl_Bar + i])
			{
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon_Click, 0, 0, 13, 17, 1);
			}
			else
			{
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon, 0, 0, 13, 17, 1);
			}
		}


		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hRemoveToMenu[1], 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hRemoveToMenu[0], 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0) DrawSprite(menuPos[1].left, menuPos[1].top, hClose[1], 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[1].left, menuPos[1].top, hClose[0], 0, 0, 32, 16, 1);


		nIconCount = 14;
		nAdd = 0;
		for(i = 0; i < nClanWon_Num; i++)
		{
			if(i >= DISPLAY_MAX) break;

		#ifdef USE_PROSTONTALE		
			bx = 13;
			by = 17;
		#else
			GetObject(hIcon, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X + 30;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = (BackStartPos.x + 120) + cldata.clanWonStrLen[i + nScl_Bar];
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;

			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
			nIconCount += 1;
		}

		nIconCount = 14;
		for(i = 0; i < DISPLAY_MAX; i++)
		{

			if(nClanWon[nIconCount])
			{
				ZeroMemory(szClanWon, sizeof(szClanWon));
				strcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
				Draw_C_Text(szClanWon, menuPos[nIconCount].left + 30, menuPos[nIconCount].top);
				nIconCount += 1;
			}
		}


		break;

		case CLAN_REMOVE_SHORTCLANWON:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		for(i = 0; i < 5; i++)
		{
			if(szRemoveClanWonResult[i][0])
			{
				Draw_C_Text(szRemoveClanWonResult[i], menuPos[2].left, menuPos[2].top + nAdd);
				nSaveTop = menuPos[2].top + nAdd;
				nAdd += 20;
			}
		}

		if(bRemoveSecondCheck)
		{
			Draw_C_Text(clanRemoveSecond.szMsg, menuPos[2].left, nSaveTop + 20);
		}
		else
		{
			Draw_C_Text(clanszRemoveShortClanWonMsg.szMsg, menuPos[2].left, nSaveTop + 20);
		}




		break;
		case CLAN_REMOVE_SHORTCLANWON_RESULT:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		if(bRemoveSecondCheck)
		{
			Draw_C_Text(clanRemoveSecondResult.szMsg, menuPos[1].left, menuPos[1].top);
		}
		else
		{
			Draw_C_Text(clanRemoveShowrtClanWonResultMsg.szMsg, menuPos[1].left, menuPos[1].top);
		}

		break;
		case CLANCHIP_RELEASEMESSAGE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		Draw_C_Text(clanClanUserRelease.szMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLAN_REMOVE_RESULT:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		Draw_C_Text(clanReMoveHeaderMsg.szMsg, menuPos[1].left, menuPos[1].top);

		for(i = 0; i < 5; i++)
		{
			if(szRemoveClanWonResult[i][0])
			{
				Draw_C_Text(szRemoveClanWonResult[i], menuPos[1].left, menuPos[1].top + 20 + nAdd);
				nSaveTop = menuPos[1].top + 40 + nAdd;
				nAdd += 20;
			}
		}


		break;






		case CLAN_MARK1:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 8, 27, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hTxt_Mark[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		wsprintf(string, "%s", szMark1);
		Draw_C_Text(string, menuPos[1].left, menuPos[1].top);
		break;
		case CLAN_MARK2:
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 27, 1);
		DrawSprite(menuPos[5].left, menuPos[5].top, hButton_Box, 0, 0, 48, 27, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0) DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[6].left, menuPos[6].top, hTxt_Mark[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		wsprintf(string, "%s", szMark2);
		Draw_C_Text(string, menuPos[2].left, menuPos[2].top);

		break;
		case CLAN_MARK3:
		DrawSprite(menuPos[5].left, menuPos[5].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[6].left, menuPos[6].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[7].left, menuPos[7].top, hTxt_Mark[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0) DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);




		DrawSprite(menuPos[2].left, menuPos[2].top, hClinetMark, 0, 0, 32, 32, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hServerMark, 0, 0, 32, 32, 1);

		wsprintf(string, "%s", szMark3);
		Draw_C_Text(string, menuPos[4].left, menuPos[4].top);

		break;


		case CLAN_RELEASE:

		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0) DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[5].left, menuPos[5].top, hTxt_Release[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);




		Draw_C_Text(clanMsg15.szMsg, menuPos[2].left, menuPos[2].top);

		break;
		case CLAN_RECONF_RELEASE:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0) DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[5].left, menuPos[5].top, hTxt_Release[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);



		Draw_C_Text(szReconfReleaseMsg, menuPos[2].left, menuPos[2].top);
		break;
		case CLAN_FINISH_RELEASE:
		DrawSprite(menuPos[1].left, menuPos[1].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[2].left, menuPos[2].top, hTxt_Release[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);



		Draw_C_Text(clanFinishReleaseMsg.szMsg, menuPos[3].left, menuPos[3].top);

		break;

		case CLAN_HELP:

		DrawSprite(menuPos[1].left, menuPos[1].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		nIconPos = 2;
		for(i = 0; i < CLANHELPICON_DISPLAY_MAX; i++)
		{
			if(i == g_nClanIconNum) break;
			if(menuMouseOver[nIconPos] > 0)
			{


				DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hClanHelpIcon[i + nScl_Bar][0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

			}
			else
			{


				DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hClanHelpIcon[i + nScl_Bar][1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
			}
			nIconPos += 1;
		}

		nIconPos = 6;
		if(g_nClanIconNum > CLANHELPICON_DISPLAY_MAX)
		{




			DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hScl_Bar,
					   0, 0, 8, 160, 1);
			renderDevice.BeginScene();

			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);
			renderDevice.EndScene();
		}
		nIconPos += 1;

		DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hTxt_Help[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);


		break;
		case CLAN_HELP_CONTENT:


		DrawSprite(menuPos[1].left, menuPos[1].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		DrawSprite(menuPos[2].left, menuPos[2].top, hTxt_Help[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hBt_Help, 0, 0, 30, 30, 1);





		renderDevice.BeginScene();
		sinDrawTexImage(hLine, (float)menuPos[4].left, (float)menuPos[4].top,
			(float)240, 10.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);
		renderDevice.EndScene();



		nIconPos = 5;
		if(g_HelpDisPlay > HLEPDISPLAY_MAX)
		{


			DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hScl_Bar,
					   0, 0, 8, 160, 1);
			renderDevice.BeginScene();

			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);
			renderDevice.EndScene();

		}
		nIconPos = 7;
		for(i = 0; i < HLEPDISPLAY_MAX; i++)
		{
			if(i == g_HelpDisPlay) break;

			ZeroMemory(szHelpContent, sizeof(char)*HELPWIDTH);

			strncpy(szHelpContent, HelpContents[i + nScl_Bar].szHelpContent, lstrlen(HelpContents[i + nScl_Bar].szHelpContent));
			Draw_C_Text(szHelpContent, menuPos[nIconPos].left, menuPos[nIconPos].top);
			nIconPos += 1;
		}

		break;

		case CLANCHIP_MAKE_FIRSTMESSAGE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
		case CLANCHIP_DOWN6_CLANWON_MESSAGE:
		case CLANCHIP_DOWN6_CLANWON:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		if(cldata.bIsOneDay)
		{
			wsprintf(szTemp, "시간 : %d : %d 남았습니다", cldata.nMinute, cldata.nHour);
			wsprintf(szDrawMenuMsg, szClanWon6Down, szTemp);
			Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		}
		else
		{
			wsprintf(szTemp, "날짜 : %d일 남았습니다", cldata.nLastDay);
			wsprintf(szDrawMenuMsg, szClanWon6Down, szTemp);
			Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);

		}


		break;

		case CLAN_NOMAKE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		if(cldata.bIsOneDay)
		{

			Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);

		}
		else
		{

			Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		}


		break;

		case CLANCHIP_SUBCHIP_APPOINT_FLAG:
		case CLANCHIP_SUBCHIP_RELEASE_FLAG:
		case CLANUSER_SUBCHIP_READMSG_FLAG:

		case	CLANCHIP_APPOINTSUBCHIP_DO:
		case CLANCHIP_RELEASESUBCHIP_DO:
		case CLANCHIP_LEAVECLAN_PFLAG:
		case CLANCHIP_LEAVECLAN_DO:
		case ISPFLAG_CHIP:
		case CLAN_REMOVE_SHORTCLANWON_LOADING:
		case CLAN_REMOVE_LOADING:
		case CLAN_RELEASE_LOADING:
		case CLAN_CHIP_ReadDATA:
		Draw_C_Text(clanLoading.szMsg, menuPos[0].left, menuPos[0].top);
		break;
	}
#else
	HDC destdc;
	switch(C_menuN)
	{

		case CLANCHIP_SUBCHIP_APPOINTMSG:
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


		if(cldata.SubChip[0] == 0)
		{
			wsprintf(szDrawMenuMsg, SubChipAppointEnd.szMsg, cldata.OldSubChip);
		}
		else
		{
			wsprintf(szDrawMenuMsg, SubChipAppointEnd.szMsg, cldata.SubChip);
		}
		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANCHIP_SUBCHIP_RELEASEMSG:
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


		wsprintf(szDrawMenuMsg, SubChipReleaseEnd.szMsg, cldata.OldSubChip);
		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANCHIP_SUBCHIP_LIST:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);

		nIconCount = 3;
		for(i = 0; i < DISPLAY_MAX; i++)
		{
			if(i == nClanWon_Num) break;
			nIconCount += 1;
			if(nClanWon[nIconCount])
			{
				if(banisF[nScl_Bar + i])
				{
					SelectObject(sorDC, hIcon_Click);
					GetObject(hIcon_Click, sizeof(BITMAP), &bit); ;
					BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);
				}
				else
				{
					SelectObject(sorDC, hIcon);
					GetObject(hIcon, sizeof(BITMAP), &bit);
					BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);
				}
			}
		}
		nIconCount = 11;
		if(nClanWon_Num > DISPLAY_MAX)
		{
			nIconCount += 1;
			SelectObject(sorDC, hScl_Bar);
			GetObject(hScl_Bar, sizeof(BITMAP), &bit);
			BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);


			SelectObject(sorDC, hScl_icon);
			GetObject(hScl_icon, sizeof(BITMAP), &bit);
			BitBlt(hdc, scrIconPos.left, scrIconPos.top, 16, 16, sorDC, 0, 0, SRCCOPY);

		}
		nIconCount += 1;
		SelectObject(sorDC, hTxt_SubChip[0]);
		GetObject(hTxt_SubChip[1], sizeof(BITMAP), &bit);
		BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);

		nIconCount += 1;
		SelectObject(sorDC, hLine);
		GetObject(hLine, sizeof(BITMAP), &bit);
		StretchBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, 240, 16, sorDC, 0, 0, 16, 16, SRCCOPY);




		nIconCount = 15;
		nAdd = 0;
		for(i = 0; i < nClanWon_Num; i++)
		{
			if(i >= DISPLAY_MAX) break;

		#ifdef USE_PROSTONTALE		
			bx = 13;
			by = 17;
		#else
			GetObject(hIcon, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X + 30;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = (BackStartPos.x + 120) + cldata.clanWonStrLen[i + nScl_Bar];
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;

			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
			nIconCount += 1;
		}
		nIconCount = 15;
		for(i = 0; i < DISPLAY_MAX; i++)
		{

			if(nClanWon[nIconCount])
			{
				if(strcmp(cldata.clanWon[i + nScl_Bar], cldata.SubChip) == 0)
				{
					strcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
					SetTextColor(destdc, RGB(0, 255, 0));
					dsTextLineOut(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, szClanWon, lstrlen(szClanWon));
				}
				else
				{
					SetTextColor(destdc, RGB(0, 0, 0));
					strcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);

					dsTextLineOut(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, szClanWon, lstrlen(szClanWon));
				}

				nIconCount += 1;
			}
		}

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

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



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANCHIP_RESUBCHIP_APPOINT:
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

		SelectObject(sorDC, hLine);
		GetObject(hLine, sizeof(BITMAP), &bit);
		StretchBlt(destdc, menuPos[5].left, menuPos[5].top, 240, 16, sorDC, 0, 0, 16, 16, SRCCOPY);

		SelectObject(sorDC, hTxt_LeaveClan[0]);
		GetObject(hTxt_LeaveClan[1], sizeof(BITMAP), &bit);
		BitBlt(destdc, menuPos[6].left, menuPos[6].top, menuPos[6].right, menuPos[6].bottom, sorDC, 0, 0, SRCCOPY);



		wsprintf(szDrawMenuMsg, SubChipAppoint.szMsg, cldata.clanWon[nSavePos]);


		Text_Out(destdc, menuPos[2].left, menuPos[2].top, szDrawMenuMsg);


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);


		break;
		case CLANCHIP_RESUBCHIP_APPOINT_END:
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


		wsprintf(szDrawMenuMsg, SubChipAppointEnd.szMsg, cldata.clanWon[nSavePos]);
		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANCHIP_RELEASESUBCHIP:
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

		SelectObject(sorDC, hLine);
		GetObject(hLine, sizeof(BITMAP), &bit);
		StretchBlt(destdc, menuPos[5].left, menuPos[5].top, 240, 16, sorDC, 0, 0, 16, 16, SRCCOPY);

		SelectObject(sorDC, hTxt_LeaveClan[0]);
		GetObject(hTxt_LeaveClan[1], sizeof(BITMAP), &bit);
		BitBlt(destdc, menuPos[6].left, menuPos[6].top, menuPos[6].right, menuPos[6].bottom, sorDC, 0, 0, SRCCOPY);



		wsprintf(szDrawMenuMsg, SubChipRelease.szMsg, cldata.SubChip);

		Text_Out(destdc, menuPos[2].left, menuPos[2].top, szDrawMenuMsg);


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);


		break;
		case CLANCHIP_RELEASESUBCHIP_END:
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


		wsprintf(szDrawMenuMsg, SubChipReleaseEnd.szMsg, cldata.SubChip);
		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;



		case CLAN_CHIP:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hClanName);
		GetObject(hClanName, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);

		nStrLen = lstrlen(cldata.name) / 2;

		if(nStrLen % 2)
		{
			nStrLen = nStrLen / 2;
			nStrLen += 1;
		}
		else nStrLen = nStrLen / 2;


		Text_Out(destdc, menuPos[10].left - (nStrLen * 11), menuPos[10].top, cldata.name);



		SelectObject(sorDC, hMark_box);
		GetObject(hMark_box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[1].left, menuPos[1].top, menuPos[1].right, menuPos[1].bottom, sorDC, 0, 0, SRCCOPY);
		if(cldata.hClanMark)
		{


			SelectObject(sorDC, cldata.hClanMark);
			GetObject(cldata.hClanMark, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[9].left, menuPos[9].top, menuPos[9].right, menuPos[9].bottom, sorDC, 0, 0, SRCCOPY);
		}




		if(menuMouseOver[2] > 0)
		{
			SelectObject(sorDC, hClanMark[1]);
			GetObject(hClanMark[1], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

			SelectObject(sorDC, hTxt_Mark[1]);
			GetObject(hTxt_Mark[1], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[2].left - CLANMARK_TXT_X, menuPos[2].bottom + CLANMARK_TXT_Y, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hClanMark[0]);
			GetObject(hClanMark[0], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

			SelectObject(sorDC, hTxt_Mark[0]);
			GetObject(hTxt_Mark[0], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[2].left - CLANMARK_TXT_X, menuPos[2].bottom + CLANMARK_TXT_Y, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);
		}



	#ifndef _LANGUAGE_BRAZIL	
		if(menuMouseOver[3] > 0)
		{












			SelectObject(sorDC, hTxt_Remove[1]);
			GetObject(hTxt_Remove[1], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);


		}
		else
		{












			SelectObject(sorDC, hTxt_Remove[0]);
			GetObject(hTxt_Remove[0], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);
		}



		if(menuMouseOver[4] > 0)
		{












			SelectObject(sorDC, hTxt_Release[1]);
			GetObject(hTxt_Release[1], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[4].left, menuPos[4].top, menuPos[4].right, menuPos[4].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{












			SelectObject(sorDC, hTxt_Release[0]);
			GetObject(hTxt_Release[0], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[4].left, menuPos[4].top, menuPos[4].right, menuPos[4].bottom, sorDC, 0, 0, SRCCOPY);
		}
	#endif


		if(menuMouseOver[5] > 0)
		{

			SelectObject(sorDC, hTxt_Help[1]);
			GetObject(hTxt_Help[1], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[5].left, menuPos[5].top, menuPos[5].right, menuPos[5].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{

			SelectObject(sorDC, hTxt_Help[0]);
			GetObject(hTxt_Help[0], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[5].left, menuPos[5].top, menuPos[5].right, menuPos[5].bottom, sorDC, 0, 0, SRCCOPY);
		}

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[7].left, menuPos[7].top, menuPos[7].right, menuPos[7].bottom, sorDC, 0, 0, SRCCOPY);
		if(menuMouseOver[6] > 0)
		{
			SelectObject(sorDC, hClose[1]);
			GetObject(hClose[1], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[6].left, menuPos[6].top, menuPos[6].right, menuPos[6].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hClose[0]);
			GetObject(hClose[0], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[6].left, menuPos[6].top, menuPos[6].right, menuPos[6].bottom, sorDC, 0, 0, SRCCOPY);
		}



		SelectObject(sorDC, hLine);
		GetObject(hLine, sizeof(BITMAP), &bit);
		StretchBlt(destdc, menuPos[17].left, menuPos[17].top, 240, 16, sorDC, 0, 0, 16, 16, SRCCOPY);

		if(menuMouseOver[18] > 0)
		{

			SelectObject(sorDC, hTxt_LeaveClan[1]);
			GetObject(hTxt_LeaveClan[1], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[18].left, menuPos[18].top, menuPos[18].right, menuPos[18].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{

			SelectObject(sorDC, hTxt_LeaveClan[0]);
			GetObject(hTxt_LeaveClan[0], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[18].left, menuPos[18].top, menuPos[18].right, menuPos[18].bottom, sorDC, 0, 0, SRCCOPY);
		}
	#ifdef __CLANSUBCHIP__
		if(menuMouseOver[19] > 0)
		{

			SelectObject(sorDC, hTxt_SubChip[1]);
			GetObject(hTxt_SubChip[1], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[19].left, menuPos[19].top, menuPos[19].right, menuPos[19].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{

			SelectObject(sorDC, hTxt_SubChip[0]);
			GetObject(hTxt_SubChip[0], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[19].left, menuPos[19].top, menuPos[19].right, menuPos[19].bottom, sorDC, 0, 0, SRCCOPY);
		}
	#endif


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANCHIP_LEAVECLANDOWNLEVEL:
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


		Text_Out(destdc, menuPos[1].left, menuPos[1].top, LeaveClanDownLevel.szMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANCHIP_NOSUBCHIP:
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


		Text_Out(destdc, menuPos[1].left, menuPos[1].top, NoSubChip.szMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANCHIP_NOLEAVECLAN:
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


		Text_Out(destdc, menuPos[1].left, menuPos[1].top, NoLeaveClan.szMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;

		case CLANCHIP_LEAVECLAN_CONFIRM:
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

		SelectObject(sorDC, hLine);
		GetObject(hLine, sizeof(BITMAP), &bit);
		StretchBlt(destdc, menuPos[5].left, menuPos[5].top, 240, 16, sorDC, 0, 0, 16, 16, SRCCOPY);

		SelectObject(sorDC, hTxt_LeaveClan[0]);
		GetObject(hTxt_LeaveClan[1], sizeof(BITMAP), &bit);
		BitBlt(destdc, menuPos[6].left, menuPos[6].top, menuPos[6].right, menuPos[6].bottom, sorDC, 0, 0, SRCCOPY);




		Text_Out(destdc, menuPos[2].left, menuPos[2].top, LeaveClanConfirm.szMsg);


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);


		break;
		case CLANCHIP_LEAVECLAN_NOLEVEL:
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


		Text_Out(destdc, menuPos[1].left, menuPos[1].top, LeaveClanNoLevel.szMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANCHIP_LEAVECLAN_RECONFIRM:
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



		wsprintf(szDrawMenuMsg, LeaveClanReConfirm.szMsg, cldata.clanWon[nSavePos]);
		Text_Out(destdc, menuPos[2].left, menuPos[2].top, szDrawMenuMsg);


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLANCHIP_LEAVECLAN_MESSAGE:
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


		wsprintf(szDrawMenuMsg, LeaveClanMessage.szMsg, cldata.OldChipChaName, cldata.ClanZang_Name);
		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;

		case CLANCHIP_LEAVECLAN_NOMONEY:
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


		Text_Out(destdc, menuPos[1].left, menuPos[1].top, LeaveClanNoMoney.szMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLANCHIP_LEAVECLAN_SUCESS:
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


		wsprintf(szDrawMenuMsg, LeaveClanSuccess.szMsg, cldata.clanWon[nSavePos]);
		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLANCHIP_LEAVECLAN:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);

		nIconCount = 3;
		for(i = 0; i < DISPLAY_MAX; i++)
		{
			if(i == nClanWon_Num) break;
			nIconCount += 1;
			if(nClanWon[nIconCount])
			{
				if(banisF[nScl_Bar + i])
				{
					SelectObject(sorDC, hIcon_Click);
					GetObject(hIcon_Click, sizeof(BITMAP), &bit); ;
					BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);
				}
				else
				{
					SelectObject(sorDC, hIcon);
					GetObject(hIcon, sizeof(BITMAP), &bit);
					BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);
				}
			}
		}
		nIconCount = 11;
		if(nClanWon_Num > DISPLAY_MAX)
		{
			nIconCount += 1;
			SelectObject(sorDC, hScl_Bar);
			GetObject(hScl_Bar, sizeof(BITMAP), &bit);
			BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);


			SelectObject(sorDC, hScl_icon);
			GetObject(hScl_icon, sizeof(BITMAP), &bit);
			BitBlt(hdc, scrIconPos.left, scrIconPos.top, 16, 16, sorDC, 0, 0, SRCCOPY);

		}
		nIconCount += 1;
		SelectObject(sorDC, hTxt_LeaveClan[0]);
		GetObject(hTxt_LeaveClan[1], sizeof(BITMAP), &bit);
		BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);

		nIconCount += 1;
		SelectObject(sorDC, hLine);
		GetObject(hLine, sizeof(BITMAP), &bit);
		StretchBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, 240, 16, sorDC, 0, 0, 16, 16, SRCCOPY);




		nIconCount = 15;
		nAdd = 0;
		for(i = 0; i < nClanWon_Num; i++)
		{
			if(i >= DISPLAY_MAX) break;

		#ifdef USE_PROSTONTALE		
			bx = 13;
			by = 17;
		#else
			GetObject(hIcon, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X + 30;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = (BackStartPos.x + 120) + cldata.clanWonStrLen[i + nScl_Bar];
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;

			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
			nIconCount += 1;
		}
		nIconCount = 15;
		for(i = 0; i < DISPLAY_MAX; i++)
		{

			if(nClanWon[nIconCount])
			{
				strcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
				dsTextLineOut(destdc, 0, 30 * i, szClanWon, lstrlen(szClanWon));
				dsTextLineOut(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, szClanWon, lstrlen(szClanWon));
				nIconCount += 1;
			}
		}

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

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



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;

	#ifndef _LANGUAGE_BRAZIL	
		case CLAN_REMOVE:

		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);

		nIconCount = 3;
		for(i = 0; i < DISPLAY_MAX; i++)
		{
			if(i == nClanWon_Num) break;
			nIconCount += 1;
			if(nClanWon[nIconCount])
			{
				if(banisF[nScl_Bar + i])
				{
					SelectObject(sorDC, hIcon_Click);
					GetObject(hIcon_Click, sizeof(BITMAP), &bit); ;
					BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);
				}
				else
				{
					SelectObject(sorDC, hIcon);
					GetObject(hIcon, sizeof(BITMAP), &bit);
					BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);
				}
			}
		}
		nIconCount = 11;
		if(nClanWon_Num > DISPLAY_MAX)
		{
			nIconCount += 1;
			SelectObject(sorDC, hScl_Bar);
			GetObject(hScl_Bar, sizeof(BITMAP), &bit);
			BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);


			SelectObject(sorDC, hScl_icon);
			GetObject(hScl_icon, sizeof(BITMAP), &bit);
			BitBlt(hdc, scrIconPos.left, scrIconPos.top, 16, 16, sorDC, 0, 0, SRCCOPY);





		}
		nIconCount += 1;
		SelectObject(sorDC, hTxt_Remove[0]);
		GetObject(hTxt_Remove[1], sizeof(BITMAP), &bit);
		BitBlt(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, menuPos[nIconCount].right, menuPos[nIconCount].bottom, sorDC, 0, 0, SRCCOPY);














		nIconCount = 14;
		nAdd = 0;
		for(i = 0; i < nClanWon_Num; i++)
		{
			if(i >= DISPLAY_MAX) break;

		#ifdef USE_PROSTONTALE		
			bx = 13;
			by = 17;
		#else
			GetObject(hIcon, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
		#endif

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X + 30;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = (BackStartPos.x + 120) + cldata.clanWonStrLen[i + nScl_Bar];
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;

			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
			nIconCount += 1;
		}
		nIconCount = 14;
		for(i = 0; i < DISPLAY_MAX; i++)
		{

			if(nClanWon[nIconCount])
			{

				strcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
				dsTextLineOut(destdc, 0, 30 * i, szClanWon, lstrlen(szClanWon));

				dsTextLineOut(destdc, menuPos[nIconCount].left, menuPos[nIconCount].top, szClanWon, lstrlen(szClanWon));
				nIconCount += 1;
			}
		}

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);
		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hRemoveToMenu[1]);
			GetObject(hRemoveToMenu[1], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hRemoveToMenu[0]);
			GetObject(hRemoveToMenu[0], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		if(menuMouseOver[1] > 0)
		{
			SelectObject(sorDC, hClose[1]);
			GetObject(hClose[1], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[1].left, menuPos[1].top, menuPos[1].right, menuPos[1].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hClose[0]);
			GetObject(hClose[0], sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			BitBlt(destdc, menuPos[1].left, menuPos[1].top, menuPos[1].right, menuPos[1].bottom, sorDC, 0, 0, SRCCOPY);
		}



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
	#endif
		case CLAN_REMOVE_SHORTCLANWON:
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


		for(i = 0; i < 5; i++)
		{
			if(szRemoveClanWonResult[i][0])
			{


				Text_Out(destdc, menuPos[2].left, menuPos[2].top + nAdd, szRemoveClanWonResult[i]);

				nSaveTop = menuPos[2].top + nAdd;
				nAdd += 20;
			}
		}

		if(bRemoveSecondCheck)
		{
			Text_Out(destdc, menuPos[2].left, nSaveTop + 20, clanRemoveSecond.szMsg);

		}
		else
		{
			Text_Out(destdc, menuPos[2].left, nSaveTop + 20, clanszRemoveShortClanWonMsg.szMsg);
		}





		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLANCHIP_RELEASEMESSAGE:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);

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

		Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanClanUserRelease.szMsg);
		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;

		case CLAN_REMOVE_SHORTCLANWON_RESULT:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);

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
		if(bRemoveSecondCheck)
		{
			Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanRemoveSecondResult.szMsg);
		}
		else
		{
			Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanRemoveShowrtClanWonResultMsg.szMsg);
		}


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;

		case CLAN_REMOVE_RESULT:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);

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

		rect.left = 70;
		rect.top = 70;
		rect.right = 280;
		rect.bottom = 250;






		for(i = 0; i < 5; i++)
		{
			if(szRemoveClanWonResult[i][0])
			{


				Text_Out(destdc, menuPos[1].left, menuPos[1].top + 40 + nAdd, szRemoveClanWonResult[i]);
				nSaveTop = menuPos[1].top + 40 + nAdd;
				nAdd += 20;
			}
		}
		Text_Out(destdc, menuPos[1].left, menuPos[1].top, clanReMoveHeaderMsg.szMsg);




		SelectObject(sorDC, hButton_Box);



		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;



		case CLAN_MARK1:
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

		wsprintf(string, "%s", szMark1);

		Text_Out(destdc, menuPos[1].left, menuPos[1].top, string);


		SelectObject(sorDC, hTxt_Mark[1]);

		GetObject(hTxt_Mark[1], sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLAN_MARK2:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);

		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[4].left, menuPos[4].top, menuPos[4].right, menuPos[4].bottom, sorDC, 0, 0, SRCCOPY);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[5].left, menuPos[5].top, menuPos[5].right, menuPos[5].bottom, sorDC, 0, 0, SRCCOPY);


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



		SelectObject(sorDC, hClinetMark);
		GetObject(hClinetMark, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		wsprintf(string, "%s", szMark2);
		Text_Out(destdc, menuPos[3].left, menuPos[3].top, string);



		SelectObject(sorDC, hTxt_Mark[1]);

		GetObject(hTxt_Mark[1], sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		BitBlt(destdc, menuPos[6].left, menuPos[6].top, menuPos[6].right, menuPos[6].bottom, sorDC, 0, 0, SRCCOPY);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLAN_MARK3:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);

		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[5].left, menuPos[5].top, menuPos[5].right, menuPos[5].bottom, sorDC, 0, 0, SRCCOPY);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[6].left, menuPos[6].top, menuPos[6].right, menuPos[6].bottom, sorDC, 0, 0, SRCCOPY);

		SelectObject(sorDC, hOk_Gray);

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

		SelectObject(sorDC, hClinetMark);
		GetObject(hClinetMark, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		SelectObject(sorDC, hServerMark);
		GetObject(hServerMark, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);

		wsprintf(string, "%s", szMark2);

		Text_Out(destdc, menuPos[4].left, menuPos[4].top, string);

		SelectObject(sorDC, hTxt_Mark[1]);

		GetObject(hTxt_Mark[1], sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[7].left, menuPos[7].top, menuPos[7].right, menuPos[7].bottom, sorDC, 0, 0, SRCCOPY);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;

	#ifndef _LANGUAGE_BRAZIL	
		case CLAN_RELEASE:
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


		wsprintf(string, "%s", szMsg15);


		Text_Out(destdc, menuPos[2].left, menuPos[2].top, clanMsg15.szMsg);


		SelectObject(sorDC, hTxt_Release[0]);
		GetObject(hTxt_Release[1], sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[5].left, menuPos[5].top, menuPos[5].right, menuPos[5].bottom, sorDC, 0, 0, SRCCOPY);


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLAN_RECONF_RELEASE:
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






		Text_Out(destdc, menuPos[2].left, menuPos[2].top, szReconfReleaseMsg);


		SelectObject(sorDC, hTxt_Release[0]);
		GetObject(hTxt_Release[1], sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[5].left, menuPos[5].top, menuPos[5].right, menuPos[5].bottom, sorDC, 0, 0, SRCCOPY);


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLAN_FINISH_RELEASE:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[1].left, menuPos[1].top, menuPos[1].right, menuPos[1].bottom, sorDC, 0, 0, SRCCOPY);








		if(menuMouseOver[0] > 0)
		{
			SelectObject(sorDC, hOk_Yellow);

			GetObject(hYes_Yellow, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(sorDC, hOk_Gray);

			GetObject(hYes_Gray, sizeof(BITMAP), &bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;

			BitBlt(destdc, menuPos[0].left, menuPos[0].top, menuPos[0].right, menuPos[0].bottom, sorDC, 0, 0, SRCCOPY);
		}


		SelectObject(sorDC, hTxt_Release[0]);
		GetObject(hTxt_Release[1], sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);


		Text_Out(destdc, menuPos[3].left, menuPos[3].top, clanFinishReleaseMsg.szMsg);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
	#endif

		case CLAN_HELP:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		BitBlt(destdc, menuPos[1].left, menuPos[1].top, menuPos[1].right, menuPos[1].bottom, sorDC, 0, 0, SRCCOPY);

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



		nIconPos = 2;

		for(i = 0; i < CLANHELPICON_DISPLAY_MAX; i++)
		{
			if(i == g_nClanIconNum) break;
			if(menuMouseOver[nIconPos] > 0)
			{
				SelectObject(sorDC, hClanHelpIcon[i + nScl_Bar][0]);
				GetObject(hClanHelpIcon[i + nScl_Bar][0], sizeof(BITMAP), &bit);
				bx = bit.bmWidth;
				by = bit.bmHeight;
				BitBlt(destdc, menuPos[nIconPos].left, menuPos[nIconPos].top, menuPos[nIconPos].right, menuPos[nIconPos].bottom, sorDC, 0, 0, SRCCOPY);













			}
			else
			{






				SelectObject(sorDC, hClanHelpIcon[i + nScl_Bar][1]);
				GetObject(hClanHelpIcon[i + nScl_Bar][1], sizeof(BITMAP), &bit);
				bx = bit.bmWidth;
				by = bit.bmHeight;
				BitBlt(destdc, menuPos[nIconPos].left, menuPos[nIconPos].top, menuPos[nIconPos].right, menuPos[nIconPos].bottom, sorDC, 0, 0, SRCCOPY);






			}
			nIconPos += 1;
		}


		nIconPos = 6;
		if(g_nClanIconNum > CLANHELPICON_DISPLAY_MAX)
		{

			SelectObject(sorDC, hScl_Bar);
			GetObject(hScl_Bar, sizeof(BITMAP), &bit);
			BitBlt(destdc, menuPos[nIconPos].left, menuPos[nIconPos].top, menuPos[nIconPos].right, menuPos[nIconPos].bottom, sorDC, 0, 0, SRCCOPY);



		}
		nIconPos += 1;
		SelectObject(sorDC, hTxt_Help[0]);
		GetObject(hTxt_Help[0], sizeof(BITMAP), &bit);
		BitBlt(destdc, menuPos[nIconPos].left, menuPos[nIconPos].top, menuPos[nIconPos].right, menuPos[nIconPos].bottom, sorDC, 0, 0, SRCCOPY);



		DeleteDC(destdc);
		DeleteDC(sorDC);
		ReleaseDC(g_hwnd, hdc);

		break;
		case CLAN_HELP_CONTENT:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);
		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);

		SelectObject(sorDC, hButton_Box);
		GetObject(hButton_Box, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		BitBlt(destdc, menuPos[1].left, menuPos[1].top, menuPos[1].right, menuPos[1].bottom, sorDC, 0, 0, SRCCOPY);

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










		SelectObject(sorDC, hTxt_Help[0]);
		GetObject(hTxt_Help[0], sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[2].left, menuPos[2].top, menuPos[2].right, menuPos[2].bottom, sorDC, 0, 0, SRCCOPY);

		SelectObject(sorDC, hBt_Help);
		GetObject(hBt_Help, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		BitBlt(destdc, menuPos[3].left, menuPos[3].top, menuPos[3].right, menuPos[3].bottom, sorDC, 0, 0, SRCCOPY);










		SelectObject(sorDC, hLine);
		GetObject(hLine, sizeof(BITMAP), &bit);
		StretchBlt(destdc, menuPos[4].left, menuPos[4].top, 240, 16, sorDC, 0, 0, 16, 16, SRCCOPY);

		nIconPos = 5;
		if(g_HelpDisPlay > HLEPDISPLAY_MAX)
		{

			SelectObject(sorDC, hScl_Bar);
			GetObject(hScl_Bar, sizeof(BITMAP), &bit);
			BitBlt(destdc, menuPos[nIconPos].left, menuPos[nIconPos].top, menuPos[nIconPos].right, menuPos[nIconPos].bottom, sorDC, 0, 0, SRCCOPY);
			nIconPos += 1;

			SelectObject(sorDC, hScl_icon);
			GetObject(hScl_icon, sizeof(BITMAP), &bit);
			BitBlt(destdc, scrIconPos.left, scrIconPos.top, 16, 16, sorDC, 0, 0, SRCCOPY);
			nIconPos += 1;




		}

		nIconPos = 7;

		for(i = 0; i < HLEPDISPLAY_MAX; i++)
		{
			if(i == g_HelpDisPlay) break;
			ZeroMemory(szHelpContent, sizeof(char)*HELPWIDTH); ;

			strncpy(szHelpContent, HelpContents[i + nScl_Bar].szHelpContent, lstrlen(HelpContents[i + nScl_Bar].szHelpContent));

			Text_Out(destdc, menuPos[nIconPos].left, menuPos[nIconPos].top, szHelpContent);
			nIconPos += 1;
		}


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANCHIP_MAKE_FIRSTMESSAGE:
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







		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLANCHIP_DOWN6_CLANWON_MESSAGE:
		case CLANCHIP_DOWN6_CLANWON:
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






		if(cldata.bIsOneDay)
		{
			wsprintf(szTemp, "시간 : %d : %d 남았습니다", cldata.nMinute, cldata.nHour);
			wsprintf(szDrawMenuMsg, szClanWon6Down, szTemp);
			Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);
		}
		else
		{
			wsprintf(szTemp, "날짜 : %d일 남았습니다", cldata.nLastDay);
			wsprintf(szDrawMenuMsg, szClanWon6Down, szTemp);
			Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);
		}


		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLAN_NOMAKE:
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







		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDrawMenuMsg);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;

		case CLANCHIP_SUBCHIP_LOAD_DATA:
		case CLANCHIP_SUBCHIP_READMSG_FLAG:

		case CLANCHIP_SUBCHIP_APPOINT_FLAG:
		case CLANCHIP_SUBCHIP_RELEASE_FLAG:
		case	CLANCHIP_APPOINTSUBCHIP_DO:
		case CLANCHIP_RELEASESUBCHIP_DO:
		case CLANCHIP_LEAVECLAN_PFLAG:
		case CLANCHIP_LEAVECLAN_DO:
		case CLAN_REMOVE_SHORTCLANWON_LOADING:
		case CLAN_REMOVE_LOADING:
		case CLAN_RELEASE_LOADING:
		case ISPFLAG_CHIP:
		case CLAN_CHIP_ReadDATA:
		hdc = GetDC(g_hwnd);
		sorDC = CreateCompatibleDC(hdc);

		destdc = CreateCompatibleDC(hdc);
		SelectObject(destdc, Dback.hb);




		Text_Out(destdc, menuPos[0].left, menuPos[0].top, clanLoading.szMsg);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
	}
#endif
}


