
#define CE_ISCLANMEMBER_CPP
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
#include "cE_isclanmember.h"
#include "tjscroll.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "..\\ygy\\ygyheader.h"

extern char	szConnServerName[16];


CLANEntity_IsClanMember::CLANEntity_IsClanMember()
{

}

CLANEntity_IsClanMember::~CLANEntity_IsClanMember()
{

}



int CLANEntity_IsClanMember::Init(int Life)
{
	life = Life;
	return 1;
}

int CLANEntity_IsClanMember::Clear()
{
	return 1;
}



extern BOOL bGetChaClan;

extern int nStatusCount;

extern BOOL bCheckClan;
void CLANEntity_IsClanMember::Main()
{
	if(life == 0) return;

	switch(C_menuN)
	{
		case CLAN_isClanWon:

		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.isClanMember(cldata.szID, cldata.gserver, cldata.ChaName);
			C_menuN2 = 1;
		#ifdef CLAN_DEBUG
			DebugMessage("CLAN_isClanWon에서 WebDB.isClanMember(아이디 : %s,게임서버 : %s,캐릭터이름 : %s)", cldata.szID, cldata.gserver, cldata.ChaName);
		#endif
			break;
			case 1:

			if(ANSdata.ret_val != -1)
				ANSdata.ret_val = ANSdata.ret_val;

			switch(ANSdata.ret_val)
			{
				case 0:
				WebDB.Suspend();
				if(bGetChaClan) ++nStatusCount;

				bIsLoading = FALSE;
				C_menuN2 = 0;
				C_menuN = CLAN_AllEnd;
				cldata.myPosition = CLANNO_REGESTER;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_isClanWon에서 무등록");
			#endif     
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
				bIsLoading = FALSE;

				cldata.myPosition = CLANUSER;
				ParsingIsClanMember(ANSdata.ret_Buf);
				if(bGetChaClan)
				{
					if(CheckMark(bGetChaClan) == 1)
					{
						C_menuN2 = 0;
						C_menuN = CLAN_AllEnd;
						break;
					}
					else
					{
						WriteMyClanInfo();



						C_menuN2 = 0;
						C_menuN = MYCLAN_UPDATE;

					}
				}
				else
				{
					WriteMyClanInfo();
					C_menuN2 = 0;
					C_menuN = MYCLAN_UPDATE;
				}
			#ifdef VOICE_CHAT
				if(bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
											   cldata.name, (DWORD)atoi(cldata.ClanMark), cldata.myPosition);


				}
			#endif

			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_isClanWon에서 클랜원등록");
			#endif				

				break;

				case 2:
				WebDB.Suspend();
				bIsLoading = FALSE;

				cldata.myPosition = CLANCHIP;
				ParsingIsClanMember(ANSdata.ret_Buf);
				cldata.isSubChip[0] = '0';
				if(bGetChaClan)
				{
					if(CheckMark(bGetChaClan) == 1)
					{
						C_menuN2 = 0;
						C_menuN = CLAN_AllEnd;
						break;
					}
					else
					{
						WriteMyClanInfo();
						C_menuN2 = 0;
						C_menuN = MYCLAN_UPDATE;


					}
				}
				else
				{
					WriteMyClanInfo();
					C_menuN2 = 0;
					C_menuN = MYCLAN_UPDATE;


				}

			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_isClanWon에서 클랜장");
			#endif				
			#ifdef VOICE_CHAT
				if(bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
											   cldata.name, (DWORD)atoi(cldata.ClanMark), cldata.myPosition);


				}
			#endif


				break;
				case 4:
				WebDB.Suspend();
				bIsLoading = FALSE;
				C_menuN2 = 0;
				C_menuN = CLAN_AllEnd;
				cldata.myPosition = CLANNO_REGESTER;
				if(bGetChaClan)
				{
					++nStatusCount;
					bGetChaClan = FALSE;
				}
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_isClanWon에서 클랜이해체된 클랜원");
			#endif
			#ifdef VOICE_CHAT
				if(bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
											   NULL, 0, cldata.myPosition);


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
				if(bGetChaClan)
				{
					++nStatusCount;
					bGetChaClan = FALSE;
				}
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_isClanWon에서 클랜이 해체됨  클랜 장");
			#endif
			#ifdef VOICE_CHAT
				if(bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
											   NULL, 0, cldata.myPosition);


				}
			#endif
				break;
				case 5:
				WebDB.Suspend();
				bIsLoading = FALSE;

				cldata.myPosition = CLAN_SUBCHIP;
				ParsingIsClanMember(ANSdata.ret_Buf);
				cldata.isSubChip[0] = '1';
				if(bGetChaClan)
				{
					if(CheckMark(bGetChaClan) == 1)
					{
						C_menuN2 = 0;
						C_menuN = CLAN_AllEnd;
						break;
					}
					else
					{
						WriteMyClanInfo();



						C_menuN2 = 0;
						C_menuN = MYCLAN_UPDATE;

					}
				}
				else
				{
					WriteMyClanInfo();
					C_menuN2 = 0;
					C_menuN = MYCLAN_UPDATE;
				}

			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_isClanWon에서 클랜원등록");
			#endif				

			#ifdef VOICE_CHAT
				if(bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
											   cldata.name, (DWORD)atoi(cldata.ClanMark), cldata.myPosition);


				}
			#endif
				break;
				case 100:
				WebDB.Suspend();
				bIsLoading = FALSE;
				cldata.myPosition = CLAN_NOCONNECT;
				C_menuN = CLAN_AllEnd;
				if(bGetChaClan)
				{
					++nStatusCount;
					bGetChaClan = FALSE;
				}
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_isClanWon에서 리턴코드 100");
			#endif
				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				bIsLoading = FALSE;


				cldata.myPosition = CLAN_NOCONNECT;
				C_menuN = CLAN_AllEnd;
				menuInit(C_menuN);
				if(bGetChaClan)
				{
					++nStatusCount;
					bGetChaClan = FALSE;
				}
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_isClanWon에서 서버에 접속할수 없음");
			#endif

				break;
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					bIsLoading = FALSE;
					C_menuN2 = 0;
					C_menuN = CLAN_AllEnd;
					cldata.myPosition = CLAN_NOCONNECT;
					if(bGetChaClan)
					{
						++nStatusCount;
						bGetChaClan = FALSE;
					}
				#ifdef CLAN_DEBUG
					DebugMessage("CLAN_isClanWon에서 디폴트에러");
				#endif
				}
				break;
			}
			break;
		}
		break;
	}

}




void CLANEntity_IsClanMember::RenderMain()
{
	if(life == 0) return;

}





void CLANEntity_IsClanMember::menuInit(int num)
{

}





