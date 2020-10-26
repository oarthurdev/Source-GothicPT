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


#include "..\\sinbaram\\sinitem.h"

#include "ClientFuncPos.h"

#include "OnServer.h"
#include "svr_Damage.h"

#include "svrEventSpawn.h"

#include "..\BellatraFontEffect.h"




rsEVENT_SPAWN	rsEventSpawn[STAGE_AREA_MAX];
int	rsEventSpawnInit = 0;

#include "Set_EventSpawn.h"

#define	CHR_MONSTER_MAX		400

extern int chrMonsterCnt;
//extern smCHAR_INFO *chrMonsterList;
extern smCHAR_INFO chrMonsterList[CHR_MONSTER_MAX];



int rsEVENT_SPAWN::InitCoreMonster(sHCORE_MONSTER *hCoreMonster)
{

	if(hCoreMonster->hCoreMonster1.lpCharInfo) return FALSE;


	for(int cnt2 = 0; cnt2 < chrMonsterCnt; cnt2++)
	{

		if(!hCoreMonster->hCoreMonster1.lpCharInfo && lstrcmpi(hCoreMonster->hCoreMonster1.szName, chrMonsterList[cnt2].szName) == 0)
			hCoreMonster->hCoreMonster1.lpCharInfo = &chrMonsterList[cnt2];

		if(!hCoreMonster->hCoreMonster2.lpCharInfo && lstrcmpi(hCoreMonster->hCoreMonster2.szName, chrMonsterList[cnt2].szName) == 0)
			hCoreMonster->hCoreMonster2.lpCharInfo = &chrMonsterList[cnt2];

		if(!hCoreMonster->hCoreMonster3.lpCharInfo && lstrcmpi(hCoreMonster->hCoreMonster3.szName, chrMonsterList[cnt2].szName) == 0)
			hCoreMonster->hCoreMonster3.lpCharInfo = &chrMonsterList[cnt2];

		if(!hCoreMonster->hCoreMonster4.lpCharInfo && lstrcmpi(hCoreMonster->hCoreMonster4.szName, chrMonsterList[cnt2].szName) == 0)
			hCoreMonster->hCoreMonster4.lpCharInfo = &chrMonsterList[cnt2];

		if(!hCoreMonster->hCoreMonsterBoss.lpCharInfo && lstrcmpi(hCoreMonster->hCoreMonsterBoss.szName, chrMonsterList[cnt2].szName) == 0)
			hCoreMonster->hCoreMonsterBoss.lpCharInfo = &chrMonsterList[cnt2];
	}


	hCoreMonster->PerCount = hCoreMonster->hCoreMonster1.perCount + hCoreMonster->hCoreMonster2.perCount + hCoreMonster->hCoreMonster3.perCount + hCoreMonster->hCoreMonster4.perCount;
	if(hCoreMonster->hCoreMonster2.lpCharInfo) hCoreMonster->hCoreMonster2.perCount += hCoreMonster->hCoreMonster1.perCount;
	if(hCoreMonster->hCoreMonster3.lpCharInfo) hCoreMonster->hCoreMonster3.perCount += hCoreMonster->hCoreMonster2.perCount;
	if(hCoreMonster->hCoreMonster4.lpCharInfo) hCoreMonster->hCoreMonster4.perCount += hCoreMonster->hCoreMonster3.perCount;

	return TRUE;
}

int	rsEVENT_SPAWN::OpenCoreMonster(smCHAR_INFO *lpCharInfo, int x, int z)
{

	STG_CHAR_INFO		 StgCharInfo;
	smCHAR *lpChar;

	StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
	StgCharInfo.smCharInfo.Life[0] = 100;
	StgCharInfo.smCharInfo.Mana[0] = 100;
	StgCharInfo.smCharInfo.Life[1] = 100;
	StgCharInfo.smCharInfo.State = TRUE;

	memcpy(&StgCharInfo.smCharInfo, lpCharInfo, sizeof(smCHAR_INFO));


#ifdef EVENTSPAWN_TEST_MODE

	StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
	StgCharInfo.smCharInfo.Life[0] = 100;
	StgCharInfo.smCharInfo.Mana[0] = 100;
	StgCharInfo.smCharInfo.Life[1] = 100;
	StgCharInfo.smCharInfo.State = TRUE;
#endif


	int EvnMonster = lpStageArea->EvnMonster;

	lpStageArea->EvnMonster = TRUE;
	lpChar = lpStageArea->OpenMonster(&StgCharInfo, 0);
	if(lpChar)
	{
		lpChar->pX = x*fONE;
		lpChar->pZ = z*fONE;
		lpChar->pY = lpStageArea->lpStage->GetHeight(lpChar->pX, lpChar->pZ);
		lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
		lpChar->TargetMoveCount = 0;
		lpChar->DistAroundDbl = (12 * 64 * 12 * 64);

		lpChar->PosiAround.x = lpChar->pX;
		lpChar->PosiAround.y = lpChar->pY;
		lpChar->PosiAround.z = lpChar->pZ;

		lpChar->smCharInfo.Sight = 800 * 800;

		lpChar->smMonsterInfo.EventCode = rsEVENT_CODE_SPAWN_FLAG;
	}
	lpStageArea->EvnMonster = EvnMonster;

	return TRUE;
}

int	rsEVENT_SPAWN::OpenCoreMonsters(sHCORE_MONSTER *hCoreMonster, int x, int z, int range)
{
	int cnt;
	int sx, sz;
	smCHAR_INFO *lpCharInfo;

	if(range == 0) range = 2;

	for(cnt = 0; cnt < hCoreMonster->MaxMonster; cnt++)
	{

		int rnd = rand() % 100;
		lpCharInfo = 0;



		if(rnd < 50)
		{
			if(rnd < 45) lpCharInfo = hCoreMonster->hCoreMonster1.lpCharInfo;
			else lpCharInfo = hCoreMonster->hCoreMonster4.lpCharInfo;
		}
		else
		{
			if(rnd < 80) lpCharInfo = hCoreMonster->hCoreMonster2.lpCharInfo;
			else lpCharInfo = hCoreMonster->hCoreMonster3.lpCharInfo;
		}

		if(lpCharInfo)
		{
			sx = rand() % range; sx -= range / 2; sz = rand() % range; sz -= range / 2;
			OpenCoreMonster(lpCharInfo, x + sx, z + sz);
		}
	}



	return TRUE;
}

int rsEVENT_SPAWN::FindEnemyCount()
{

	int FoundCount = 0;

	for(int cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
	{
		if(lpStageArea->lpCharMonster[cnt])
		{
			if(lpStageArea->lpCharMonster[cnt]->Flag &&
			   lpStageArea->lpCharMonster[cnt]->smMonsterInfo.EventCode == rsEVENT_CODE_SPAWN_FLAG &&
			   lpStageArea->lpCharMonster[cnt]->MotionInfo->State != CHRMOTION_STATE_DEAD &&
			   lpStageArea->lpCharMonster[cnt]->smCharInfo.State == smCHAR_STATE_ENEMY)
			{
				FoundCount++;
			}
		}
	}

	return FoundCount;
}

int rsEVENT_SPAWN::FindBossCount()
{

	int FoundCount = 0;

	for(int cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
	{
		if(lpStageArea->lpCharMonster[cnt])
		{
			if(lpStageArea->lpCharMonster[cnt]->Flag &&
			   lpStageArea->lpCharMonster[cnt]->smMonsterInfo.EventCode == rsEVENT_CODE_SPAWN_FLAG &&
			   lpStageArea->lpCharMonster[cnt]->MotionInfo->State != CHRMOTION_STATE_DEAD &&
			   lpStageArea->lpCharMonster[cnt]->smCharInfo.State == smCHAR_STATE_ENEMY &&
			   lpStageArea->lpCharMonster[cnt]->smCharInfo.wPlayClass[0] == MONSTER_CLASS_BOSS)
			{
				FoundCount++;
			}
		}
	}

	return FoundCount;
}


int rsEVENT_SPAWN::KillMonstersAll()
{

	smCHAR *lpChar;

	for(int cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
	{
		if(lpStageArea->lpCharMonster[cnt])
		{
			lpChar = lpStageArea->lpCharMonster[cnt];
			if(lpChar->Flag &&
			   lpChar->smMonsterInfo.EventCode == rsEVENT_CODE_SPAWN_FLAG &&
			   lpChar->MotionInfo->State != CHRMOTION_STATE_DEAD &&
			   lpChar->smCharInfo.State == smCHAR_STATE_ENEMY)
			{

				lpChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);

				EventCondition = 0;
			}
		}
	}


	return TRUE;
}


int	rsEVENT_SPAWN::Event_KillMonster(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar)
{
	if(lpChar->smMonsterInfo.EventCode != rsEVENT_CODE_SPAWN_FLAG) return FALSE;

	EventCondition++;

	if(lpChar->smCharInfo.wPlayClass[0] == MONSTER_CLASS_BOSS)
	{

		KillMonstersAll();
		dwEventPlayTime = 0;

		OpenUserEffect(E_BL_FONT_CON, EventSpawn_42_Posi.x, EventSpawn_42_Posi.y, EventSpawn_42_Range * 2);
	}

	if(lpPlayInfo->getSecurity() > AccountTypes::SEC_VIP)
	{

		TRANS_CHATMESSAGE	TransChatMessage;
		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		wsprintf(TransChatMessage.szMessage, ">Condition[%d] EventPlayTime[%d] BossTime[%d]", EventCondition, (dwEventPlayTime - dwPlayServTime) / 1000, (dwBossTime - dwPlayServTime) / 1000);
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
	}

	return TRUE;
}

int rsEVENT_SPAWN::OpenUserEffect(int FontEffectType, int x, int z, int range)
{
	int cnt;
	int rx, rz, dist;
	int drange = range*range;

	smTRANS_COMMAND	smTransCommand;
	smTransCommand.code = OpCode::OPCODE_SOD_INFOMATION;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = smCODE_SOD_EFFECT;
	smTransCommand.LParam = FontEffectType;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
		{
			rx = abs(x - (rsPlayInfo[cnt].Position.x >> FLOATNS));
			rz = abs(z - (rsPlayInfo[cnt].Position.z >> FLOATNS));
			dist = rx*rx + rz*rz;
			if(dist < drange && rx < range && rz < range)
			{
				rsPlayInfo[cnt].lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
			}
		}
	}

	return TRUE;
}




int rsEVENT_SPAWN::Main()
{
	if(!lpStageArea) return FALSE;

	if(FieldCode == 42)
	{
		if(dwEventPlayTime && dwEventPlayTime > dwPlayServTime)
		{
			if(dwSpawnTime < dwPlayServTime)
			{
				if(FindEnemyCount() < 10)
				{
					OpenCoreMonsters(&sHCore_EventSpawn42, EventSpawn_42_Posi.x, EventSpawn_42_Posi.y, EventSpawn_42_Range);
				}
				dwSpawnTime = dwPlayServTime + sHCore_EventSpawn42.DelayTime * 1000;

				if(dwBossTime && dwBossTime < dwPlayServTime)
				{

					int cnt = 0;
					while(1)
					{
						if(!sHCore_EventSpawn42_Boss[cnt].hCoreMonster1.szName[0]) break;
						if(EventCondition < sHCore_EventSpawn42_Boss[cnt].State)
						{
							OpenCoreMonsters(&sHCore_EventSpawn42_Boss[cnt], EventSpawn_42_Posi.x, EventSpawn_42_Posi.y, 16);
							break;
						}
						cnt++;
					}
					OpenCoreMonsters(&sHCore_EventSpawn42, EventSpawn_42_Posi.x, EventSpawn_42_Posi.y, EventSpawn_42_Range);
					dwBossTime = 0;
				}
			}
		}
		if(dwEventPlayTime && dwEventPlayTime < dwPlayServTime)
		{

			KillMonstersAll();
			dwEventPlayTime = 0;

			OpenUserEffect(E_BL_FONT_FAIL, EventSpawn_42_Posi.x, EventSpawn_42_Posi.y, EventSpawn_42_Range * 2);

		}
	}

	return TRUE;
}

int rsEVENT_SPAWN::Order(rsPLAYINFO *lpPlayInfo, char *szText)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	int x, z, dist;


	if(lpPlayInfo->Position.Area == 42)
	{

		x = (lpPlayInfo->Position.x >> FLOATNS) - EventSpawn_42_Posi.x;
		z = (lpPlayInfo->Position.z >> FLOATNS) - EventSpawn_42_Posi.y;
		dist = x*x + z*z;

		if(dist < (EventSpawn_42_Range*EventSpawn_42_Range))
		{

			int cnt = 0;

			while(1)
			{
				if(szEventSpawn_Order42[cnt][0] == 0)
				{
					cnt = -1; break;
				}

				if(strstr(szText, szEventSpawn_Order42[cnt][0]) != 0)
				{
					break;
				}
				cnt++;
			}


			if(cnt >= 0)
			{

				TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;

				if(dwOpenTime < dwPlayServTime)
				{

					dwEventPlayTime = dwPlayServTime + 60 * 1000 * EVENTSPAWN_PLAYING_TIME;
					dwOpenTime = dwPlayServTime + 60 * 1000 * EVENTSPAWN_OPEN_TIME;
					EventFlag = 1;

					InitCoreMonster(&sHCore_EventSpawn42);
					cnt = 0;
					while(1)
					{
						if(!sHCore_EventSpawn42_Boss[cnt].hCoreMonster1.szName[0]) break;
						InitCoreMonster(&sHCore_EventSpawn42_Boss[cnt]);
						cnt++;
					}

					dwBossTime = dwPlayServTime + sHCore_EventSpawn42.StartHour * 60 * 1000;

					OpenUserEffect(E_BL_FONT_START, EventSpawn_42_Posi.x, EventSpawn_42_Posi.y, EventSpawn_42_Range * 2);

				}
				else
				{
					if(dwEventPlayTime && dwEventPlayTime > dwPlayServTime)
					{

						wsprintf(TransChatMessage.szMessage, szEventSpawn_Order42[cnt][2]);
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
					}
					else
					{

						wsprintf(TransChatMessage.szMessage, szEventSpawn_Order42[cnt][1]);
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
					}
				}
			}



		}

	}


	return TRUE;
}


int rsEventSpawn_KillMonster(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar)
{

	if(lpPlayInfo->Position.Area >= 0 && lpPlayInfo->Position.Area < STAGE_AREA_MAX)
	{

		return rsEventSpawn[lpPlayInfo->Position.Area].Event_KillMonster(lpPlayInfo, lpChar);
	}

	return FALSE;
}

int rsEventSpawn_Order(rsPLAYINFO *lpPlayInfo, char *szText)
{

	if(lpPlayInfo->Position.Area >= 0 && lpPlayInfo->Position.Area < STAGE_AREA_MAX)
	{

		return rsEventSpawn[lpPlayInfo->Position.Area].Order(lpPlayInfo, szText);
	}

	return FALSE;
}

int rsEventSpawn_Main(STG_AREA *lpStgArea)
{

	if(!rsEventSpawnInit)
	{

		for(int cnt = 0; cnt < STAGE_AREA_MAX; cnt++)
		{
			ZeroMemory(&rsEventSpawn[cnt], sizeof(rsEVENT_SPAWN));

			if(StageArea[cnt].lpStage)
			{
				rsEventSpawn[cnt].lpStageArea = &StageArea[cnt];
				rsEventSpawn[cnt].FieldCode = cnt;
			}
		}
		rsEventSpawnInit = TRUE;
	}
	else
	{
		rsEventSpawn[lpStgArea->lpField->FieldCode].Main();
	}

	return TRUE;
}


