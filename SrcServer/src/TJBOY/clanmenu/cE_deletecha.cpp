#define CE_DELETECHA_CPP
#include <windows.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		

#include "sinbaram\\SinLinkHeader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "Language\\language.h"
#include "HoBaram\\HoTextFile.h"
#endif


#include "tjclan.h"
#include "cE_deletecha.h"
#include "cE_report.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "..\\ygy\\ygyheader.h"



CLANEntity_deletecha::CLANEntity_deletecha()
{
	nHowDeleteChaFlag = 0;
}

CLANEntity_deletecha::~CLANEntity_deletecha()
{
}


int CLANEntity_deletecha::Init(int Life)
{
	life = Life;
	return 1;
}


void CLANEntity_deletecha::SetDeleteChaInfo(char *id, char *gserver, char *chaname)
{
	strcpy(cldata.szID, id);
	strcpy(cldata.ChaName, chaname);
	strcpy(cldata.gserver, gserver);
}


int CLANEntity_deletecha::Clear()
{
	return 1;
}




void CLANEntity_deletecha::Main()
{
	int i;
	switch(C_menuN)
	{
		case CLAN_DELETECHA_START:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;
			nHowDeleteChaFlag = 0;

			WebDB.Resume();
			WebDB.isClanMember(cldata.szID, cldata.gserver, cldata.ChaName);
			C_menuN2 = 1;
			break;
			case 1:

			if(ANSdata.ret_val != -1)
				ANSdata.ret_val = ANSdata.ret_val;

			switch(ANSdata.ret_val)
			{
				case 4:
				case 3:
				case 0:
				WebDB.Suspend();
				bIsLoading = FALSE;
				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;
				cldata.myPosition = CLANNO_REGESTER;
				nHowDeleteChaFlag = 0;


			#ifdef VOICE_CHAT
				if(bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
											   NULL, 0, cldata.myPosition);


				}
			#endif


				break;


				case 1:
				WebDB.Suspend();
				ParsingIsClanMember(ANSdata.ret_Buf);

				if(bFlag)
				{
					C_menuN = CLAN_DELETECHA_SECESSION_BEFORE;
					menuInit(C_menuN);
					cldata.myPosition = CLANUSER;
					nHowDeleteChaFlag = 0;
					C_menuN2 = -1;
				}
				else
				{
					C_menuN = CLAN_DIRECT_DELETE;
					menuInit(C_menuN);
					cldata.myPosition = CLANUSER;
					nHowDeleteChaFlag = 0;
					C_menuN2 = 0;

				}

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

				C_menuN = CLAN_AllEnd;
				C_menuN2 = -1;
				nHowDeleteChaFlag = 3;
				break;

				case 100:
				WebDB.Suspend();
				C_menuN = CLAN_AllEnd;
				C_menuN2 = -1;
				nHowDeleteChaFlag = 3;
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_AllEnd;
				C_menuN2 = -1;
				nHowDeleteChaFlag = 3;
				break;
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					bIsLoading = FALSE;
					C_menuN2 = 0;
					C_menuN = CLAN_AllEnd;
					cldata.myPosition = CLAN_NOCONNECT;
					C_menuN2 = -1;
					nHowDeleteChaFlag = 3;
				}
				break;
			}
			break;
		}
		break;





		case CLAN_DELETECHA_RELEASECLAN_BEFORE:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;
			nHowDeleteChaFlag = 1;

			WebDB.Resume();
			WebDB.BreakUP_Clan(cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name);
			C_menuN2 = 1;
			break;
			case 1:
			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanDeleteChaError.szMsg);
				cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
				CLAN_ERROR_ret = 255;
				nHowDeleteChaFlag = 3;
				break;
				case 1:
				WebDB.Suspend();
				C_menuN = CLAN_DELETECHA_RELEASECLAN;
				menuInit(C_menuN);
				C_menuN2 = -1;
				nHowDeleteChaFlag = 2;
				break;








				case 100:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanDeleteChaError.szMsg);
				cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
				CLAN_ERROR_ret = 255;
				nHowDeleteChaFlag = 3;
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanServerConnectErrorMsg.szMsg);
				cClanReport.menuInit(C_menuN, clanServerConnectErrorMsg.pos.x, clanServerConnectErrorMsg.pos.y);
				nHowDeleteChaFlag = 3;
				break;

				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();

					C_menuN = CLAN_ERROR;
					cClanReport.InitMsg(clanDeleteChaError.szMsg);
					cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
					CLAN_ERROR_ret = 255;
					C_menuN2 = -1;
					nHowDeleteChaFlag = 3;
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
				C_menuN = CLAN_AllEnd;
				break;
				default:
				break;
			}
		}
		break;


		case CLAN_DELETECHA_RELEASECLAN:
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
				default:
				break;
			}
		}
		break;
		case CLAN_DIRECT_DELETE:
		switch(C_menuN2)
		{

			case 0:
			ANSdata.ret_val = -1;
			nHowDeleteChaFlag = 1;

			WebDB.Resume();

			WebDB.Secession(cldata.szID, cldata.gserver, cldata.ChaName, cldata.name);
			C_menuN2 = 1;
			break;
			case 1:

			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();


				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanDeleteChaError.szMsg);
				cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
				CLAN_ERROR_ret = CLAN_USER;
				C_menuN2 = -1;
				nHowDeleteChaFlag = 3;
				break;
				case 1:
				WebDB.Suspend();
				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;
				nHowDeleteChaFlag = 2;
				break;









				case 3:
				WebDB.Suspend();

				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;
				nHowDeleteChaFlag = 2;
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();


				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanServerConnectErrorMsg.szMsg);
				cClanReport.menuInit(C_menuN, clanServerConnectErrorMsg.pos.x, clanServerConnectErrorMsg.pos.y);
				nHowDeleteChaFlag = 3;
				break;
				case 2:
				case 4:
				case 100:
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();



					C_menuN = CLAN_ERROR;
					cClanReport.InitMsg(clanDeleteChaError.szMsg);
					cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
					CLAN_ERROR_ret = CLAN_USER;
					C_menuN2 = -1;
					nHowDeleteChaFlag = 3;
				}
				break;
			}
			break;


		}
		break;
		case CLAN_DELETECHA_SECESSION_BEFORE:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;
			nHowDeleteChaFlag = 1;

			WebDB.Resume();

			WebDB.Secession(cldata.szID, cldata.gserver, cldata.ChaName, cldata.name);
			C_menuN2 = 1;
			break;
			case 1:

			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();


				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanDeleteChaError.szMsg);
				cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
				CLAN_ERROR_ret = CLAN_USER;
				C_menuN2 = -1;
				nHowDeleteChaFlag = 3;
				break;
				case 1:
				WebDB.Suspend();

				C_menuN = CLAN_DELETECHA_SECESSION;
				menuInit(C_menuN);

				C_menuN2 = -1;
				nHowDeleteChaFlag = 2;
				break;









				case 3:
				WebDB.Suspend();


				C_menuN = CLAN_DELETECHA_SECESSION;
				menuInit(C_menuN);
				C_menuN2 = -1;
				nHowDeleteChaFlag = 2;
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();


				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanServerConnectErrorMsg.szMsg);
				cClanReport.menuInit(C_menuN, clanServerConnectErrorMsg.pos.x, clanServerConnectErrorMsg.pos.y);
				nHowDeleteChaFlag = 3;
				break;
				case 2:
				case 4:
				case 100:
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();



					C_menuN = CLAN_ERROR;
					cClanReport.InitMsg(clanDeleteChaError.szMsg);
					cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
					CLAN_ERROR_ret = CLAN_USER;
					C_menuN2 = -1;
					nHowDeleteChaFlag = 3;
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
				case 1:
				C_menuN = CLAN_AllEnd;
				break;
				case 0:
				C_menuN2 = 0;

				default:
				break;
			}
		}
		break;


		case CLAN_DELETECHA_SECESSION:
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
				default:
				break;
			}
		}
		break;
	}
}

void CLANEntity_deletecha::Draw()
{
#ifdef USE_PROSTONTALE		
	switch(C_menuN)
	{
		case CLAN_DELETECHA_RELEASECLAN_BEFORE:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szDeleteChaReleaseBefore, menuPos[2].left, menuPos[2].top);

		break;

		case CLAN_DELETECHA_RELEASECLAN:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szDeleteChaReleaseFinish, menuPos[1].left, menuPos[1].top);
		break;
		case CLAN_DELETECHA_SECESSION_BEFORE:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if(menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if(menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szDeleteChaSecessionBefore, menuPos[2].left, menuPos[2].top);

		break;
		break;
		case CLAN_DELETECHA_SECESSION:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 27, 1);
		if(menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szDeleteChaSecessionFinish, menuPos[1].left, menuPos[1].top);
		break;
	}
#else
	HDC hdc, sorDC, destdc;
	BITMAP bit;
	int bx, by;

	switch(C_menuN)
	{
		case CLAN_DELETECHA_RELEASECLAN_BEFORE:
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
		Text_Out(destdc, menuPos[2].left, menuPos[2].top, szDeleteChaReleaseBefore);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLAN_DELETECHA_RELEASECLAN:
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

		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDeleteChaReleaseFinish);
		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLAN_DELETECHA_SECESSION_BEFORE:
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
		Text_Out(destdc, menuPos[2].left, menuPos[2].top, szDeleteChaSecessionBefore);

		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
		case CLAN_DELETECHA_SECESSION:
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

		Text_Out(destdc, menuPos[1].left, menuPos[1].top, szDeleteChaSecessionFinish);
		DeleteDC(sorDC);
		DeleteDC(destdc);
		ReleaseDC(g_hwnd, hdc);
		break;
	}
#endif
}

void CLANEntity_deletecha::menuInit(int num)
{
	int bx = 0, by = 0;
	switch(num)
	{
		case CLAN_DELETECHA_RELEASECLAN_BEFORE:
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



		menuPos[2].left = BackStartPos.x + 20;
		menuPos[2].top = BackStartPos.y + 50;
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
		case CLAN_DELETECHA_RELEASECLAN:
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


		menuPos[1].left = BackStartPos.x + 70;
		menuPos[1].top = BackStartPos.y + 70;
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
		case CLAN_DELETECHA_SECESSION_BEFORE:
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



		menuPos[2].left = BackStartPos.x + 30;
		menuPos[2].top = BackStartPos.y + 70;
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
		case CLAN_DELETECHA_SECESSION:
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


		menuPos[1].left = BackStartPos.x + 70;
		menuPos[1].top = BackStartPos.y + 70;
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
	}

}

