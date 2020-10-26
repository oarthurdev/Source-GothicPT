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
#include "Language\\language.h"
#include "partymsg.h"
#include "onserver.h"

extern DWORD	dwPlayServTime;





rsPLAYINFO* srFindUserFromSerial(DWORD dwObjectSerial);

int	rsRegist_ItemSecCode(rsPLAYINFO* lpPlayInfo, TRANS_ITEMINFO* lpTransItemInfo, int NewItem);



int rsPLAYINFO::SendPartyData(rsPLAYINFO* lpPlayInfo_From, char* szData)
{
	int size;
	int cnt;


	size = ((smTRANS_COMMAND*)szData)->size;

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt] != lpPlayInfo_From)
		{
			if (lpPartyPlayers[cnt]->lpsmSock)
			{
				lpPartyPlayers[cnt]->lpsmSock->Send(szData, size, TRUE);
			}
		}
	}


	return TRUE;
}


int rsPLAYINFO::SendPartyMessage(char* szMessage, DWORD dwCode)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	int cnt;

	if (lpPartyMaster)
	{
		strcpy_s(TransChatMessage.szMessage, szMessage);
		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = dwCode;
		TransChatMessage.dwObjectSerial = 0;

		for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
		{
			if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock)
			{
				lpPartyPlayers[cnt]->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
			}
		}
	}
	else
	{
		strcpy_s(TransChatMessage.szMessage, szMessage);
		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		if (lpsmSock)
			lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
	}

	return TRUE;
}



int rsPLAYINFO::CreateParty(rsPLAYINFO* lpPlayInfo)
{
	int cnt;

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		lpPartyPlayers[cnt] = 0;
		dwPartyObjectCode[0] = 0;
	}

	PartyUpdateFlag = 0;
	dwPartyInfo = PARTY_STATE_MASTER;
	lpPartyMaster = this;


	lpPartyPlayers[0] = this;
	dwPartyObjectCode[0] = dwObjectSerial;
	if (this != lpPlayInfo)
	{
		lpPartyPlayers[1] = lpPlayInfo;
		dwPartyObjectCode[1] = lpPlayInfo->dwObjectSerial;

		lpPlayInfo->dwPartyInfo = PARTY_STATE_MEMBER;
		lpPlayInfo->lpPartyMaster = this;
	}

	UpdatePartyPlayer();

	return TRUE;
}


int	rsPLAYINFO::JoinPartyPlayer(rsPLAYINFO* lpPlayInfo)
{
	int cnt;

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt] == lpPlayInfo)
		{

			return FALSE;
		}
	}

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (!lpPartyPlayers[cnt])
		{
			lpPartyPlayers[cnt] = lpPlayInfo;
			dwPartyObjectCode[cnt] = lpPlayInfo->dwObjectSerial;
			lpPlayInfo->dwPartyInfo = PARTY_STATE_MEMBER;
			lpPlayInfo->lpPartyMaster = this;
			UpdatePartyPlayer();
			return TRUE;
		}
	}

	return FALSE;
}


int	rsPLAYINFO::DeletePartyPlayer(rsPLAYINFO* lpPlayInfo)
{
	int cnt;
	smTRANS_COMMAND		TransCommand;

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt] == lpPlayInfo)
		{
			lpPartyPlayers[cnt]->dwPartyInfo = PARTY_STATE_NONE;
			lpPartyPlayers[cnt]->lpPartyMaster = NULL;
			lpPartyPlayers[cnt] = 0;
			dwPartyObjectCode[cnt] = 0;
			UpdatePartyPlayer();


			if (lpPlayInfo->lpsmSock)
			{
				TransCommand.code = OpCode::OPCODE_PARTY_RELEASE;
				TransCommand.size = sizeof(smTRANS_COMMAND);
				TransCommand.WParam = dwObjectSerial;
				TransCommand.LParam = 0;
				TransCommand.SParam = 0;

				lpPlayInfo->lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
			}
			return TRUE;
		}
	}

	return FALSE;
}


int	rsPLAYINFO::ChangePartyPlayer(rsPLAYINFO* lpOldPlayInfo, rsPLAYINFO* lpNewPlayInfo)
{
	int cnt;

	if (!lpPartyMaster)
	{

		lpNewPlayInfo->dwPartyInfo = PARTY_STATE_NONE;
		lpNewPlayInfo->lpPartyMaster = NULL;
		return FALSE;
	}


	if (lpOldPlayInfo == lpPartyMaster)
	{
		for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
		{
			if (lpPartyPlayers[cnt])
			{
				lpPartyPlayers[cnt]->lpPartyMaster = lpNewPlayInfo;
			}
		}
		lpNewPlayInfo->dwPartyInfo = PARTY_STATE_MASTER;
		lpNewPlayInfo->lpPartyMaster = lpNewPlayInfo;
	}

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyMaster->lpPartyPlayers[cnt] == lpOldPlayInfo)
		{
			lpPartyMaster->lpPartyPlayers[cnt] = lpNewPlayInfo;
			break;
		}
	}

	lpOldPlayInfo->dwPartyInfo = PARTY_STATE_NONE;
	lpOldPlayInfo->lpPartyMaster = NULL;




	return TRUE;
}


int	rsPLAYINFO::UpdatePartyPlayer()
{
	int cnt, cnt2;
	TRANS_PARTY_USERS	TransPartyUsers;
	int	LevelAvg;

	cnt = 0;
	cnt2 = 0;

	if (!lpPartyMaster) return FALSE;


	TransPartyUsers.PartyUser[cnt2].dwObjectSerial = lpPartyMaster->dwObjectSerial;
	strcpy_s(TransPartyUsers.PartyUser[cnt2].szName, lpPartyMaster->smCharInfo.szName);
	strcpy_s(TransPartyUsers.PartyUser[cnt2].szModelName, lpPartyMaster->smCharInfo.szModelName);
	strcpy_s(TransPartyUsers.PartyUser[cnt2].szModelName2, lpPartyMaster->smCharInfo.szModelName2);
	TransPartyUsers.PartyUser[cnt2].Life[0] = lpPartyMaster->smCharInfo.Life[0];
	TransPartyUsers.PartyUser[cnt2].Life[1] = lpPartyMaster->smCharInfo.Life[1];
	TransPartyUsers.PartyUser[cnt2].Level = lpPartyMaster->smCharInfo.Level;
	TransPartyUsers.PartyUser[cnt2].x = lpPartyMaster->Position.x;
	TransPartyUsers.PartyUser[cnt2].z = lpPartyMaster->Position.z;
	LevelAvg = lpPartyMaster->smCharInfo.Level;
	cnt2++;


	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt] != lpPartyMaster)
		{
			TransPartyUsers.PartyUser[cnt2].dwObjectSerial = lpPartyPlayers[cnt]->dwObjectSerial;
			strcpy_s(TransPartyUsers.PartyUser[cnt2].szName, lpPartyPlayers[cnt]->smCharInfo.szName);
			strcpy_s(TransPartyUsers.PartyUser[cnt2].szModelName, lpPartyPlayers[cnt]->smCharInfo.szModelName);
			strcpy_s(TransPartyUsers.PartyUser[cnt2].szModelName2, lpPartyPlayers[cnt]->smCharInfo.szModelName2);
			TransPartyUsers.PartyUser[cnt2].Life[0] = lpPartyPlayers[cnt]->smCharInfo.Life[0];
			TransPartyUsers.PartyUser[cnt2].Life[1] = lpPartyPlayers[cnt]->smCharInfo.Life[1];
			TransPartyUsers.PartyUser[cnt2].Level = lpPartyPlayers[cnt]->smCharInfo.Level;
			TransPartyUsers.PartyUser[cnt2].x = lpPartyPlayers[cnt]->Position.x;
			TransPartyUsers.PartyUser[cnt2].z = lpPartyPlayers[cnt]->Position.z;
			LevelAvg += lpPartyPlayers[cnt]->smCharInfo.Level;
			cnt2++;
		}
	}

	PartyUserCount = cnt2;
	PartyLevelAverage = LevelAvg / cnt2;

	ZeroMemory(TransPartyUsers.dwTemp, sizeof(DWORD) * 8);

	TransPartyUsers.dwObjectSerial = dwObjectSerial;
	TransPartyUsers.PartyUserCount = cnt2;
	TransPartyUsers.size = sizeof(TRANS_PARTY_USERS) - ((PARTY_PLAYER_MAX - cnt2) * sizeof(_PARTY_USER));
	TransPartyUsers.code = OpCode::OPCODE_PARTY_UPDATE;

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock)
		{
			lpPartyPlayers[cnt]->lpsmSock->Send((char*)&TransPartyUsers, TransPartyUsers.size, TRUE);
		}
	}

	return TRUE;
}



int	rsPLAYINFO::UpdatePartyPlayInfo()
{
	int cnt, cnt2;
	int	LevelAvg;
	TRANS_PARTY_PLAYINFO TransPartyPlayInfo;

	cnt = 0;
	cnt2 = 0;

	PartyUpdateFlag = 0;


	TransPartyPlayInfo.PlayInfo[cnt2].dwObjectSerial = dwObjectSerial;
	TransPartyPlayInfo.PlayInfo[cnt2].Life[0] = smCharInfo.Life[0];
	TransPartyPlayInfo.PlayInfo[cnt2].Life[1] = smCharInfo.Life[1];
	TransPartyPlayInfo.PlayInfo[cnt2].Level = smCharInfo.Level;
	TransPartyPlayInfo.PlayInfo[cnt2].x = Position.x;
	TransPartyPlayInfo.PlayInfo[cnt2].z = Position.z;
	TransPartyPlayInfo.PlayInfo[cnt2].Mana[0] = lpPartyPlayers[cnt]->smCharInfo.Mana[0];
	TransPartyPlayInfo.PlayInfo[cnt2].Mana[1] = lpPartyPlayers[cnt]->smCharInfo.Mana[1];
	//TransPartyPlayInfo.PlayInfo[cnt2].JobCode = lpPartyPlayers[cnt]->smCharInfo.JOB_CODE;
	LevelAvg = smCharInfo.Level;
	cnt2++;


	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt] != this)
		{
			TransPartyPlayInfo.PlayInfo[cnt2].dwObjectSerial = lpPartyPlayers[cnt]->dwObjectSerial;
			TransPartyPlayInfo.PlayInfo[cnt2].Life[0] = lpPartyPlayers[cnt]->smCharInfo.Life[0];
			TransPartyPlayInfo.PlayInfo[cnt2].Life[1] = lpPartyPlayers[cnt]->smCharInfo.Life[1];
			TransPartyPlayInfo.PlayInfo[cnt2].Level = lpPartyPlayers[cnt]->smCharInfo.Level;
			TransPartyPlayInfo.PlayInfo[cnt2].x = lpPartyPlayers[cnt]->Position.x;
			TransPartyPlayInfo.PlayInfo[cnt2].z = lpPartyPlayers[cnt]->Position.z;
			TransPartyPlayInfo.PlayInfo[cnt2].Mana[0] = lpPartyPlayers[cnt]->smCharInfo.Mana[0];
			TransPartyPlayInfo.PlayInfo[cnt2].Mana[1] = lpPartyPlayers[cnt]->smCharInfo.Mana[1];
			//TransPartyPlayInfo.PlayInfo[cnt2].JobCode = lpPartyPlayers[cnt]->smCharInfo.JOB_CODE;
			LevelAvg += lpPartyPlayers[cnt]->smCharInfo.Level;
			cnt2++;
		}
	}

	PartyUserCount = cnt2;
	PartyLevelAverage = LevelAvg / cnt2;

	TransPartyPlayInfo.dwTemp = 0;

	TransPartyPlayInfo.dwObjectSerial = dwObjectSerial;
	TransPartyPlayInfo.PartyUserCount = cnt2;
	TransPartyPlayInfo.size = sizeof(TRANS_PARTY_PLAYINFO);
	TransPartyPlayInfo.code = OpCode::OPCODE_PARTY_PLAYUPDATE;

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock)
		{
			lpPartyPlayers[cnt]->lpsmSock->Send((char*)&TransPartyPlayInfo, TransPartyPlayInfo.size, TRUE);
		}
	}

	return TRUE;
}




int	rsPLAYINFO::UpdateServerPartyPlayer(TRANS_PARTY_PLAYINFO* lpTransPartyPlayInfo)
{
	int count = lpTransPartyPlayInfo->PartyUserCount;

	if (count < 0 || count >(PARTY_PLAYER_MAX - 1))
	{
		return FALSE;
	}

	int cnt = 0, cnt2 = 0;
	rsPLAYINFO* lpPlayInfo = nullptr;
	DWORD	dwPartyCode1 = 0, dwPartyCode2 = 0;

	int LevelAvg = 0;

	if (dwPartyInfo == PARTY_STATE_MASTER)
	{

		dwPartyCode1 = 0;
		dwPartyCode2 = 0;

		for (int i = 0; i < count; i++)
		{
			dwPartyCode1 += lpTransPartyPlayInfo->PlayInfo[i].dwObjectSerial;
		}

		cnt = 0;
		for (cnt2 = 0; cnt2 < PARTY_PLAYER_MAX; cnt2++)
		{
			if (lpPartyPlayers[cnt2])
			{
				dwPartyCode2 += lpPartyPlayers[cnt2]->dwObjectSerial;
				cnt++;
			}
		}

		if (cnt == count && dwPartyCode1 == dwPartyCode2)
		{

			return TRUE;

		}
	}



	if (dwPartyInfo == PARTY_STATE_MASTER)
	{
		for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
		{
			if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock)
			{
				lpPartyPlayers[cnt]->dwPartyInfo = PARTY_STATE_NONE;
				lpPartyPlayers[cnt]->lpPartyMaster = NULL;
			}
		}
	}

	ZeroMemory(lpPartyPlayers, sizeof(rsPLAYINFO*) * PARTY_PLAYER_MAX);

	for (cnt = 0; cnt < count; cnt++)
	{
		if (lpTransPartyPlayInfo->PlayInfo[cnt].dwObjectSerial == dwObjectSerial)
		{
			dwPartyInfo = PARTY_STATE_MASTER;
			lpPartyMaster = this;
			lpPartyPlayers[cnt] = this;
			LevelAvg += smCharInfo.Level;
		}
		else
		{
			lpPlayInfo = srFindUserFromSerial(lpTransPartyPlayInfo->PlayInfo[cnt].dwObjectSerial);
			if (lpPlayInfo)
			{
				lpPartyPlayers[cnt] = lpPlayInfo;
				lpPlayInfo->dwPartyInfo = PARTY_STATE_MEMBER;
				lpPlayInfo->lpPartyMaster = this;
				LevelAvg += lpPlayInfo->smCharInfo.Level;
			}
		}
	}


	PartyUserCount = count;
	if (PartyUserCount) PartyLevelAverage = LevelAvg / PartyUserCount;

	return TRUE;
}




int srGetTotalExp(int Exp, int Level);


float PartyExpTable[8][2] = {
	{ 1.f, 0 },       // 1 Player = 100%
	{ 0.84f, 0.84f }, // 2 Player = 140% 
	{ 0.72f, 0.72f }, // 3 Player = 180%
	{ 0.67f, 0.67f }, // 4 Player = 220%
	{ 0.60f, 0.60f }, // 5 Player = 260%
	{ 0.60f, 0.60f }, // 6 Player = 300%
	{ 0.22f, 0.22f },
	{ 0.20f, 0.20f }
};


int rsPLAYINFO::GetPartyExp(smCHAR* lpChar, rsPLAYINFO* lpPlayInfo)
{
	if (dwPartyInfo != PARTY_STATE_MASTER || !lpsmSock)
	{
		return FALSE;
	}

	int Sucess = 0;

	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = lpChar->dwObjectSerial;

	//
	int Exp = srGetTotalExp(lpChar->smMonsterInfo.GetExp, lpChar->smCharInfo.Level - PartyLevelAverage);
	Exp++;
	if (Exp)
	{
		int	PartyExp[2] = { 0,0 };

		PartyExp[0] = static_cast<int>(Exp * PartyExpTable[PartyUserCount - 1][0]);
		PartyExp[1] = static_cast<int>(Exp * PartyExpTable[PartyUserCount - 1][1]);


		for (int cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
		{
			if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock)
			{

				if (lpPartyPlayers[cnt] == lpPlayInfo)
				{
					smTransCommand.code = OpCode::OPCODE_ADDEXP;
					smTransCommand.WParam = PartyExp[0];
					Sucess++;
				}
				else
				{

					smTransCommand.code = OpCode::OPCODE_ADDEXP_PARTY;

					int x = (lpPlayInfo->Position.x - lpPartyPlayers[cnt]->Position.x) >> FLOATNS;
					int z = (lpPlayInfo->Position.z - lpPartyPlayers[cnt]->Position.z) >> FLOATNS;
					int dist = x * x + z * z;

					if (dist < PARTY_GETTING_DIST)
					{
						smTransCommand.WParam = PartyExp[1];
					}
					else
					{
						smTransCommand.WParam = 0;
					}
				}

				if (smTransCommand.WParam)
				{
					int ExpUp = 0;

					if (lpPartyPlayers[cnt]->dwTime_PrimeItem_ExpUp > 0)
					{
						switch (lpPartyPlayers[cnt]->dwPrimeItem_PackageCode)
						{
						case PRIME_ITEM_PACKAGE_NONE:							ExpUp += 30;							break;
						case PRIME_ITEM_PACKAGE_BRONZE:							ExpUp += 10;							break;
						case PRIME_ITEM_PACKAGE_SILVER:							ExpUp += 20;							break;
						case PRIME_ITEM_PACKAGE_GOLD:							ExpUp += 30;							break;
						case PRIME_ITEM_PACKAGE_ULTRA:							ExpUp += 50;							break;
						case PRIME_ITEM_PACKAGE_NONE_50_EXPUP:					ExpUp += 50;							break;
						case PRIME_ITEM_PACKAGE_NONE_100_EXPUP:					ExpUp += 100;							break;
						}
					}

					if (lpPartyPlayers[cnt]->Bl_RNo > 0)
					{
						ExpUp += 20;
					}

					if (lpPartyPlayers[cnt]->dwTime_PrimeItem_PhenixPet > 0)
					{
						ExpUp += 5;
					}

					if (rsServerConfig.ExpGameTimeMode)
					{
						smTransCommand.WParam = (smTransCommand.WParam * rsGetExp_GameTime(lpPartyPlayers[cnt])) / 100;
					}

					if (ExpUp)
					{
						smTransCommand.WParam += (smTransCommand.WParam * ExpUp) / 100;
					}

					lpPartyPlayers[cnt]->spEXP_Out += smTransCommand.WParam;
					smTransCommand.SParam = (smTransCommand.WParam * 3 + smTransCommand.LParam * 13) * 2002;
					smTransCommand.EParam = smTransCommand.SParam ^ lpPartyPlayers[cnt]->spEXP_Out;

					lpPartyPlayers[cnt]->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
				}
			}
		}
	}

	if (!Sucess)
	{
		return FALSE;
	}

	return TRUE;
}


int rsPLAYINFO::GetPartyMoney(sITEMINFO* lpDefItemInfo, rsPLAYINFO* lpPlayInfo)
{
	TRANS_ITEMINFO	TransItemInfo;
	int	PartyMoney[2];
	int	cnt;
	int x, z, dist;
	int Sucess = 0;

	if (dwPartyInfo != PARTY_STATE_MASTER || !lpsmSock) return FALSE;

	PartyMoney[1] = lpDefItemInfo->Money / PartyUserCount;
	PartyMoney[0] = PartyMoney[1] + (lpDefItemInfo->Money % PartyUserCount);


	TransItemInfo.code = OpCode::OPCODE_PUTITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	memcpy(&TransItemInfo.Item, lpDefItemInfo, sizeof(sITEMINFO));



	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock)
		{

			if (lpPartyPlayers[cnt] == lpPlayInfo)
			{
				wsprintf(TransItemInfo.Item.ItemName, sinGold, PartyMoney[0]);
				TransItemInfo.Item.Money = PartyMoney[0];
				ReformItem(&TransItemInfo.Item);
				Sucess++;
			}
			else
			{
				x = (lpPlayInfo->Position.x - lpPartyPlayers[cnt]->Position.x) >> FLOATNS;
				z = (lpPlayInfo->Position.z - lpPartyPlayers[cnt]->Position.z) >> FLOATNS;
				dist = x * x + z * z;
				if (dist < PARTY_GETTING_DIST)
				{
					wsprintf(TransItemInfo.Item.ItemName, sinGold, PartyMoney[1]);
					TransItemInfo.Item.Money = PartyMoney[1];
					ReformItem(&TransItemInfo.Item);
				}
				else
				{
					TransItemInfo.Item.Money = 0;
				}
			}

			if (TransItemInfo.Item.Money)
			{
				lpPartyPlayers[cnt]->spMoney_Out += TransItemInfo.Item.Money;

				TransItemInfo.x = dwPlayServTime;
				TransItemInfo.y = TransItemInfo.Item.ItemHeader.dwChkSum;
				TransItemInfo.z = lpPartyPlayers[cnt]->spMoney_Out ^ (TransItemInfo.x + TransItemInfo.y);

				rsRegist_ItemSecCode(lpPartyPlayers[cnt], &TransItemInfo, 0);

				lpPartyPlayers[cnt]->lpsmSock->Send((char*)&TransItemInfo, TransItemInfo.size, TRUE);
			}

		}
	}
	if (!Sucess)	return FALSE;

	return TRUE;
}


int rsPLAYINFO::PartyChatting(rsPLAYINFO* lpPlayInfo)
{
	int sLen, cnt;
	TRANS_CHATMESSAGE	TransChatMessage;


	sLen = lstrlen(lpPlayInfo->szChatMessage) + 1;
	TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(lpPlayInfo->szChatMessage);
	TransChatMessage.dwIP = 4;
	TransChatMessage.dwObjectSerial = lpPlayInfo->dwObjectSerial;
	memcpy(TransChatMessage.szMessage, lpPlayInfo->szChatMessage, sLen);

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock && lpPartyPlayers[cnt] != lpPlayInfo)
		{

			lpPartyPlayers[cnt]->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		}
	}


	return TRUE;
}



int	rsPLAYINFO::LeavePartyMaster(rsPLAYINFO* lpPlayInfo)
{
	int cnt;
	char szBuff[128];

	if (dwPartyInfo != PARTY_STATE_MASTER) return FALSE;
	if (lpPlayInfo == this) return FALSE;

	dwPartyInfo = PARTY_STATE_MEMBER;

	if (!lpPlayInfo)
	{

		for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
		{
			if (lpPartyPlayers[cnt] && lpPartyMaster != lpPartyPlayers[cnt])
			{
				lpPlayInfo = lpPartyPlayers[cnt];
				break;
			}
		}
	}

	if (!lpPlayInfo) return FALSE;
	if (!lpPlayInfo->lpsmSock) return FALSE;


	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt])
		{

			lpPartyPlayers[cnt]->lpPartyMaster = lpPlayInfo;
			lpPartyPlayers[cnt]->PartyMasterObjectCode = lpPlayInfo->dwObjectSerial;
			if (lpPartyPlayers[cnt] == lpPlayInfo)
			{
				lpPartyPlayers[cnt]->dwPartyInfo = PARTY_STATE_MASTER;
			}
		}
	}

	memcpy(lpPlayInfo->lpPartyPlayers, lpPartyPlayers, sizeof(rsPLAYINFO*) * PARTY_PLAYER_MAX);
	memcpy(lpPlayInfo->dwPartyObjectCode, dwPartyObjectCode, sizeof(DWORD) * PARTY_PLAYER_MAX);

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		lpPartyPlayers[cnt] = 0;
		dwPartyObjectCode[0] = 0;
	}

	lpPlayInfo->UpdatePartyPlayer();



	wsprintf(szBuff, srPartyMsg1, lpPlayInfo->smCharInfo.szName);
	lpPlayInfo->SendPartyMessage(szBuff, 2);

	return TRUE;
}


int	rsPLAYINFO::ReleaseParty()
{
	int cnt;
	smTRANS_COMMAND		TransCommand;

	if (lpPartyMaster != this) return FALSE;


	SendPartyMessage(srPartyMsg2, 2);

	dwPartyInfo = PARTY_STATE_NONE;

	TransCommand.code = OpCode::OPCODE_PARTY_RELEASE;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;


	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		if (lpPartyPlayers[cnt])
		{

			lpPartyPlayers[cnt]->dwPartyInfo = PARTY_STATE_NONE;
			lpPartyPlayers[cnt]->lpPartyMaster = NULL;

			if (lpPartyPlayers[cnt]->lpsmSock)
				lpPartyPlayers[cnt]->lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);

			lpPartyPlayers[cnt] = 0;
		}
	}


	return TRUE;
}



int	rsPLAYINFO::JoinParty(rsPLAYINFO* lpPlayMaster)
{
	char	szBuff[128];

	if (dwPartyInfo) return FALSE;

	if (lpPlayMaster && lpPlayMaster->lpsmSock && lpPlayMaster->dwPartyInfo == PARTY_STATE_MASTER)
	{


		if (lpPlayMaster->JoinPartyPlayer(this) == TRUE)
		{


			wsprintf(szBuff, srPartyMsg3, smCharInfo.szName);
			SendPartyMessage(szBuff, 2);
		}
		else
		{


			wsprintf(szBuff, srPartyMsg4);
			SendPartyMessage(szBuff, 2);
		}
	}

	return TRUE;
}



int	rsPLAYINFO::SecedeParty()
{
	char	szBuff[128];

	rsPLAYINFO* lpPlayInfo;


	if (dwPartyInfo && lpPartyMaster && lpPartyMaster->lpsmSock && lpPartyMaster->dwPartyInfo == PARTY_STATE_MASTER)
	{


		if (this == lpPartyMaster)
		{
			LeavePartyMaster(0);
		}

		lpPlayInfo = lpPartyMaster;

		if (lpPlayInfo->PartyUserCount <= 2)
		{

			wsprintf(szBuff, srPartyMsg5, smCharInfo.szName);
			lpPlayInfo->SendPartyMessage(szBuff, 2);


			lpPlayInfo->ReleaseParty();
			return TRUE;
		}

		if (lpPlayInfo->DeletePartyPlayer(this))
		{

			wsprintf(szBuff, srPartyMsg5, smCharInfo.szName);
			lpPlayInfo->SendPartyMessage(szBuff, 2);

			return TRUE;
		}
	}


	return FALSE;
}

rsPLAYINFO* LastDisPlayer;
rsPLAYINFO* LastDisPartyMaster;
DWORD		LastDisPartyInfo;


int	rsPLAYINFO::DisconnectPartyUser()
{
	char szBuff[128];
	rsPLAYINFO* pMaster;

	if (!lpPartyMaster || !dwPartyInfo) return NULL;

	LastDisPlayer = this;
	LastDisPartyMaster = lpPartyMaster;
	LastDisPartyInfo = dwPartyInfo;



	pMaster = lpPartyMaster;

	if (this == lpPartyMaster)
	{
		LeavePartyMaster(0);
	}



	wsprintf(szBuff, srPartyMsg5, smCharInfo.szName);
	lpPartyMaster->SendPartyMessage(szBuff, 2);

	if (lpPartyMaster->PartyUserCount <= 2)
	{
		lpPartyMaster->ReleaseParty();
		return TRUE;
	}


	lpPartyMaster->DeletePartyPlayer(this);


	lpPartyMaster = pMaster;

	return TRUE;
}







char* GetWhereParamString(int WareParam)
{
	char* lpString;

	lpString = "Unknow";

#ifdef _W_SERVER

	switch (WareParam)
	{

	case	WHERE_TRADE:
		lpString = "Trade";	break;
	case	WHERE_GIFT_EXPRESS:
		lpString = "GiftExpress";	break;
	case	WHERE_AGINGITEM:
		lpString = "AgingItem";	break;
	case	WHERE_CRAFTITEM:
		lpString = "CraftItem";	break;
	case	WHERE_FORECORB:
		lpString = "ForceOrb";	break;
	case	WHERE_BUY_ITEM:
		lpString = "BuyItem";	break;
	case	WHERE_BUY_POTION:
		lpString = "BuyPotion";	break;
	case	WHERE_SELL_ITEM:
		lpString = "SellItem";	break;
	case	WHERE_LOAD_PLAYER:
		lpString = "LoadPlayer";	break;
	case	WHERE_THROW_ITEM:
		lpString = "ThrowItem";	break;
	case	WHERE_GET_ITEM:
		lpString = "GetItem";	break;
	case	WHERE_STAR_POINT:
		lpString = "StarPoint";	break;
	case	WHERE_CLAN_MONEY:
		lpString = "ClanMoney";	break;
	case	WHERE_GIVE_MONEY:
		lpString = "GiveMoney";	break;
	case	WHERE_PERSONAL_SHOP:
		lpString = "PersonalShop";	break;
	case	WHERE_OPEN_WAREHOUES:
		lpString = "WareHouse";	break;
	}
#endif

	return lpString;
}


#define MAX_MONEY				1000000000
#define	CHK_SERVER_MONEY_MAX	1000000000
#define	CHK_SERVER_MONEY_MAX2	1000000000
#define	CHK_SERVER_MONEY_MIN	-150000000

int	rsPLAYINFO::AddServerMoney(int Money, int WhereParam)
{
	int money = ServerMoney;

	ServerMoney += Money;

	if ((money >= 0 && ServerMoney < 0) || Money<0 || Money>CHK_SERVER_MONEY_MAX)
	{


		smTRANS_COMMAND_EX	smTransCommandEx;

		char szStrBuff[128];
		wsprintf(szStrBuff, "*ADD_MONEY [%s]*", GetWhereParamString(WhereParam));

		smTransCommandEx.WParam = 8840;
		smTransCommandEx.WxParam = WhereParam;
		smTransCommandEx.LxParam = (int)szStrBuff;
		smTransCommandEx.LParam = money;
		smTransCommandEx.SParam = Money;
		smTransCommandEx.EParam = ServerMoney;
		RecordHackLogFile(this, &smTransCommandEx);

		if (ServerMoney < CHK_SERVER_MONEY_MIN)
			ServerMoney = CHK_SERVER_MONEY_MIN;

		return FALSE;
	}

	return TRUE;
}

int	rsPLAYINFO::SubServerMoney(int Money, int WhereParam)
{
	int money = ServerMoney;

	ServerMoney -= Money;

	if ((money >= 0 && ServerMoney < 0) || Money<0 || Money>CHK_SERVER_MONEY_MAX)
	{


		smTRANS_COMMAND_EX	smTransCommandEx;

		char szStrBuff[128];
		wsprintf(szStrBuff, "*SUB_MONEY [%s]*", GetWhereParamString(WhereParam));

		smTransCommandEx.WParam = 8840;
		smTransCommandEx.WxParam = WhereParam;
		smTransCommandEx.LxParam = (int)szStrBuff;
		smTransCommandEx.LParam = money;
		smTransCommandEx.SParam = Money;
		smTransCommandEx.EParam = ServerMoney;
		RecordHackLogFile(this, &smTransCommandEx);

		if (ServerMoney < CHK_SERVER_MONEY_MIN)
			ServerMoney = CHK_SERVER_MONEY_MIN;


		return FALSE;
	}

	return TRUE;
}

int	rsPLAYINFO::SetServerMoney(int Money, int WhereParam)
{
	ServerMoney = Money;

	if (Money > CHK_SERVER_MONEY_MAX || Money < 0)
	{


		smTRANS_COMMAND_EX	smTransCommandEx;

		char szStrBuff[128];
		wsprintf(szStrBuff, "*SET_MONEY [%s]*", GetWhereParamString(WhereParam));

		smTransCommandEx.WParam = 8840;
		smTransCommandEx.WxParam = WhereParam;
		smTransCommandEx.LxParam = (int)szStrBuff;
		smTransCommandEx.LParam = 0;
		smTransCommandEx.SParam = Money;
		smTransCommandEx.EParam = ServerMoney;
		RecordHackLogFile(this, &smTransCommandEx);

		if (ServerMoney < CHK_SERVER_MONEY_MIN)
			ServerMoney = CHK_SERVER_MONEY_MIN;

		if (ServerMoney > CHK_SERVER_MONEY_MAX2)
			ServerMoney = 0;

		return FALSE;
	}

	return TRUE;
}


int	rsPLAYINFO::CallBack_ClanMarkNum(int ClanMarkNum)
{
	if (ClanMarkNum == -1)
	{
		return TRUE;
	}

	smTRANS_COMMAND	smTransCommand;

	DWORD dwCode = GetClanCode(ClanMarkNum);

	if (dwClanCode != dwCode)
	{
		smTransCommand.WParam = 8870;
		smTransCommand.LParam = dwClanCode;
		smTransCommand.SParam = dwCode;
		smTransCommand.EParam = rsBlessCastle.dwMasterClan;


		SucessCheck_ClanCode = -1;

		return FALSE;
	}

	dwClanCode = dwCode;
	SucessCheck_ClanCode = TRUE;

	return TRUE;
}
