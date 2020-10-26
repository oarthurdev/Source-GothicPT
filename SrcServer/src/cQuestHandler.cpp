#include "cQuestHandler.h"
#include <iostream>
#include "Shop.h"

using namespace std;

extern int DefaultItemCount;
extern sDEF_ITEMINFO DefaultItems[3200];
cQUESTHANDLER cQuestHandler;

int isRightMonster(int questID, char mosterName2[32]) {
	shared_ptr<Database> db = Database::GetConnection(DATABASEID_QuestDB);

	char monsterName[32];

	if (db->Open())
	{
		char* szBuff = "SELECT * FROM QuestMonster WHERE QuestID=?";
		if (db->Prepare(szBuff))
		{
			db->BindInputParameter(&questID, 1, PARAMTYPE_String);

			if (db->Execute())
			{
				db->GetData(monsterName, 32, 3, PARAMTYPE_String);

				if (lstrcmpi(monsterName, mosterName2) == 0) {
					db->Close();
					return TRUE;
				}
				else {
					db->Close();
					return FALSE;
				}
			}
		}

	}
}


void cQUESTHANDLER::GetSpoilerInfo(rsPLAYINFO* lpPlayInfo, int SpoilerNum)
{
	shared_ptr<Database> db = Database::GetConnection(DATABASEID_QuestDB);

	smTRANS_QUEST_INFO info = {};
	info.code = OpCode::OPCODE_SPOILER_INFO;
	info.SpoilerNum = SpoilerNum;
	info.size = sizeof(smTRANS_QUEST_INFO);
	info.QuestCount = -1;
	lpPlayInfo->lpsmSock->Send((char*)&info, info.size, TRUE);

	switch (SpoilerNum)
	{
	case 7:
		if (db->Open())
		{
			map<int, bool> vTypes;

			if (db->Prepare("SELECT * FROM Progress WHERE QuestKind=? AND PlayerName=?"))
			{
				char playerName[32];
				wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());
				db->BindInputParameter(&SpoilerNum, 1, PARAMTYPE_Integer);
				db->BindInputParameter(playerName, 2, PARAMTYPE_String);
				if (db->Execute(false))
				{
					while (db->NextRow())
					{
						int value = -1;
						db->GetData(&value, 4, 3, PARAMTYPE_Integer);

						map<int, bool>::iterator it = vTypes.find(value);

						if (it == vTypes.end())
							vTypes.insert(std::pair<int, bool>(value, true));
					}
				}
			}

			if (db->Prepare("SELECT * FROM Complete WHERE QuestKind=? AND PlayerName=? AND DAY(GETDATE()) <= DAY(EndDate) AND MONTH(GETDATE())=MONTH(EndDate)")) // GETDATE() < DATEADD(day, 1, EndDate)
			{
				char playerName[32];
				wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());
				db->BindInputParameter(&SpoilerNum, 1, PARAMTYPE_Integer);
				db->BindInputParameter(playerName, 2, PARAMTYPE_String);
				if (db->Execute(false))
				{
					while (db->NextRow())
					{
						int value = -1;
						db->GetData(&value, 4, 3, PARAMTYPE_Integer);

						map<int, bool>::iterator it = vTypes.find(value);

						if (it == vTypes.end())
							vTypes.insert(std::pair<int, bool>(value, true));
					}
				}
			}

			if (db->Prepare("SELECT * FROM DailyQuest WHERE LevelMin <= ? AND LevelMax >= ? ORDER BY QuestName ASC"))
			{
				db->BindInputParameter(&lpPlayInfo->smCharInfo.Level, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&lpPlayInfo->smCharInfo.Level, 2, PARAMTYPE_Integer);
				if (db->Execute(false))
				{
					smTRANS_QUEST_INFO TransQuestInfo = {};

					TransQuestInfo.code = OpCode::OPCODE_SPOILER_INFO;
					TransQuestInfo.SpoilerNum = SpoilerNum;

					while (db->NextRow())
					{
						int cnt = TransQuestInfo.QuestCount;
						int type = 0;

						db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestID, 4, 1, PARAMTYPE_Integer);
						db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestName, 128, 2, PARAMTYPE_String);
						TransQuestInfo.QuestInfo[cnt].QuestKind = SpoilerNum;
						TransQuestInfo.QuestInfo[cnt].QuestActive = true;

						db->GetData(&type, 4, 8, PARAMTYPE_Integer);

						map<int, bool>::iterator it = vTypes.find(type);

						if (it != vTypes.end())
						{
							TransQuestInfo.QuestInfo[cnt].QuestActive = false;
						}

						TransQuestInfo.QuestCount++;

						if (TransQuestInfo.QuestCount == 58)
						{
							TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
							lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);

							TransQuestInfo.QuestCount = 0;
							ZeroMemory(&TransQuestInfo.QuestInfo, sizeof(sNEW_QUEST_INFO) * 58);
						}
					}

					TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
					lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);
				}
			}

			if (db->Prepare("SELECT * FROM DailyQuest WHERE LevelMin > ? OR LevelMax < ? ORDER BY QuestName ASC"))
			{
				db->BindInputParameter(&lpPlayInfo->smCharInfo.Level, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&lpPlayInfo->smCharInfo.Level, 2, PARAMTYPE_Integer);
				if (db->Execute(false))
				{
					smTRANS_QUEST_INFO TransQuestInfo = {};

					TransQuestInfo.code = OpCode::OPCODE_SPOILER_INFO;
					TransQuestInfo.SpoilerNum = SpoilerNum;

					while (db->NextRow())
					{
						int cnt = TransQuestInfo.QuestCount;

						db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestID, 4, 1, PARAMTYPE_Integer);
						db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestName, 128, 2, PARAMTYPE_String);
						TransQuestInfo.QuestInfo[cnt].QuestKind = SpoilerNum;
						TransQuestInfo.QuestInfo[cnt].QuestActive = false;

						TransQuestInfo.QuestCount++;

						if (TransQuestInfo.QuestCount == 58)
						{
							TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
							lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);

							TransQuestInfo.QuestCount = 0;
							ZeroMemory(&TransQuestInfo.QuestInfo, sizeof(sNEW_QUEST_INFO) * 58);
						}
					}

					TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
					lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);
				}
			}
			db->Close();
		}
		break;

	case 9:
		if (db->Open())
		{
			map<int, bool> vTypes;

			if (db->Prepare("SELECT * FROM Progress WHERE QuestKind=? AND PlayerName=?"))
			{
				char playerName[32];
				wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());
				db->BindInputParameter(&SpoilerNum, 1, PARAMTYPE_Integer);
				db->BindInputParameter(playerName, 2, PARAMTYPE_String);
				if (db->Execute(false))
				{
					while (db->NextRow())
					{
						int value = -1;
						db->GetData(&value, 4, 3, PARAMTYPE_Integer);

						map<int, bool>::iterator it = vTypes.find(value);

						if (it == vTypes.end())
							vTypes.insert(std::pair<int, bool>(value, true));
					}
				}
			}

			if (db->Prepare("SELECT * FROM Complete WHERE QuestKind=? AND PlayerName=?"))
			{
				char playerName[32];
				wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());
				db->BindInputParameter(&SpoilerNum, 1, PARAMTYPE_Integer);
				db->BindInputParameter(playerName, 2, PARAMTYPE_String);
				if (db->Execute(false))
				{
					while (db->NextRow())
					{
						int value = -1;
						db->GetData(&value, 4, 3, PARAMTYPE_Integer);

						map<int, bool>::iterator it = vTypes.find(value);

						if (it == vTypes.end())
							vTypes.insert(std::pair<int, bool>(value, true));
					}
				}
			}

			if (db->Prepare("SELECT * FROM SingleQuest WHERE LevelMin <= ? AND LevelMax >= ? ORDER BY QuestName ASC"))
			{
				db->BindInputParameter(&lpPlayInfo->smCharInfo.Level, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&lpPlayInfo->smCharInfo.Level, 2, PARAMTYPE_Integer);
				if (db->Execute(false))
				{
					smTRANS_QUEST_INFO TransQuestInfo = {};

					TransQuestInfo.code = OpCode::OPCODE_SPOILER_INFO;
					TransQuestInfo.SpoilerNum = SpoilerNum;

					while (db->NextRow())
					{
						int cnt = TransQuestInfo.QuestCount;
						int type = 0;

						db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestID, 4, 1, PARAMTYPE_Integer);
						db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestName, 128, 2, PARAMTYPE_String);
						TransQuestInfo.QuestInfo[cnt].QuestKind = SpoilerNum;
						TransQuestInfo.QuestInfo[cnt].QuestActive = true;

						db->GetData(&type, 4, 8, PARAMTYPE_Integer);

						map<int, bool>::iterator it = vTypes.find(type);

						if (it != vTypes.end())
						{
							TransQuestInfo.QuestInfo[cnt].QuestActive = false;
						}

						TransQuestInfo.QuestCount++;

						if (TransQuestInfo.QuestCount == 58)
						{
							TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
							lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);

							TransQuestInfo.QuestCount = 0;
							ZeroMemory(&TransQuestInfo.QuestInfo, sizeof(sNEW_QUEST_INFO) * 58);
						}
					}

					TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
					lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);
				}
			}

			if (db->Prepare("SELECT * FROM SingleQuest WHERE LevelMin > ? OR LevelMax < ? ORDER BY QuestName ASC"))
			{
				db->BindInputParameter(&lpPlayInfo->smCharInfo.Level, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&lpPlayInfo->smCharInfo.Level, 2, PARAMTYPE_Integer);
				if (db->Execute(false))
				{
					smTRANS_QUEST_INFO TransQuestInfo = {};

					TransQuestInfo.code = OpCode::OPCODE_SPOILER_INFO;
					TransQuestInfo.SpoilerNum = SpoilerNum;

					while (db->NextRow())
					{
						int cnt = TransQuestInfo.QuestCount;

						db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestID, 4, 1, PARAMTYPE_Integer);
						db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestName, 128, 2, PARAMTYPE_String);
						TransQuestInfo.QuestInfo[cnt].QuestKind = SpoilerNum;
						TransQuestInfo.QuestInfo[cnt].QuestActive = false;

						TransQuestInfo.QuestCount++;

						if (TransQuestInfo.QuestCount == 58)
						{
							TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
							lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);

							TransQuestInfo.QuestCount = 0;
							ZeroMemory(&TransQuestInfo.QuestInfo, sizeof(sNEW_QUEST_INFO) * 58);
						}
					}

					TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
					lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);
				}
			}
			db->Close();
		}
		break;

	case 10:
		if (db->Open())
		{
			vector<sPROGRESS_INFO> vProgress;

			if (db->Prepare("SELECT * FROM Progress WHERE PlayerName=?"))
			{
				char playerName[32];
				wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());

				db->BindInputParameter(playerName, 1, PARAMTYPE_String);
				if (db->Execute(false))
				{
					while (db->NextRow())
					{
						int QuestID, QuestKind, QuestType;

						db->GetData(&QuestID, 4, 1, PARAMTYPE_Integer);
						db->GetData(&QuestKind, 4, 2, PARAMTYPE_Integer);
						db->GetData(&QuestType, 4, 3, PARAMTYPE_Integer);

						vProgress.push_back({ QuestID, QuestKind, QuestType });
					}
				}
			}

			smTRANS_QUEST_INFO TransQuestInfo = {};
			TransQuestInfo.code = OpCode::OPCODE_SPOILER_INFO;
			TransQuestInfo.SpoilerNum = SpoilerNum;

			for (auto Progress : vProgress)
			{
				switch (Progress.QuestKind)
				{
				case 7:
					if (db->Prepare("SELECT * FROM DailyQuest WHERE QuestID=? AND QuestType=? ORDER BY QuestName ASC"))
					{
						db->BindInputParameter(&Progress.QuestID, 1, PARAMTYPE_Integer);
						db->BindInputParameter(&Progress.QuestType, 2, PARAMTYPE_Integer);
						if (db->Execute(false))
						{
							while (db->NextRow())
							{
								int cnt = TransQuestInfo.QuestCount;

								db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestID, 4, 1, PARAMTYPE_Integer);
								db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestName, 128, 2, PARAMTYPE_String);
								TransQuestInfo.QuestInfo[cnt].QuestKind = Progress.QuestKind;
								TransQuestInfo.QuestInfo[cnt].QuestActive = true;

								TransQuestInfo.QuestCount++;

								if (TransQuestInfo.QuestCount == 58)
								{
									TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
									lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);

									TransQuestInfo.QuestCount = 0;
									ZeroMemory(&TransQuestInfo.QuestInfo, sizeof(sNEW_QUEST_INFO) * 58);
								}
							}
						}
					}
					break;

				case 9:
					if (db->Prepare("SELECT * FROM SingleQuest WHERE QuestID=? AND QuestType=? ORDER BY QuestName ASC"))
					{
						db->BindInputParameter(&Progress.QuestID, 1, PARAMTYPE_Integer);
						db->BindInputParameter(&Progress.QuestType, 2, PARAMTYPE_Integer);
						if (db->Execute(false))
						{
							while (db->NextRow())
							{
								int cnt = TransQuestInfo.QuestCount;

								db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestID, 4, 1, PARAMTYPE_Integer);
								db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestName, 128, 2, PARAMTYPE_String);
								TransQuestInfo.QuestInfo[cnt].QuestKind = Progress.QuestKind;
								TransQuestInfo.QuestInfo[cnt].QuestActive = true;

								TransQuestInfo.QuestCount++;

								if (TransQuestInfo.QuestCount == 58)
								{
									TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
									lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);

									TransQuestInfo.QuestCount = 0;
									ZeroMemory(&TransQuestInfo.QuestInfo, sizeof(sNEW_QUEST_INFO) * 58);
								}
							}
						}
					}
					break;
				}
			}

			//if (TransQuestInfo.QuestCount)
			//{
			TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
			lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);
			//}

			db->Close();
		}
		break;

	case 11:
		if (db->Open())
		{
			vector<sPROGRESS_INFO> vProgress;

			if (db->Prepare("SELECT * FROM Complete WHERE PlayerName=?"))
			{
				char playerName[32];
				wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());

				db->BindInputParameter(playerName, 1, PARAMTYPE_String);
				if (db->Execute(false))
				{
					while (db->NextRow())
					{
						int QuestID, QuestKind, QuestType;

						db->GetData(&QuestID, 4, 1, PARAMTYPE_Integer);
						db->GetData(&QuestKind, 4, 2, PARAMTYPE_Integer);
						db->GetData(&QuestType, 4, 3, PARAMTYPE_Integer);

						vProgress.push_back({ QuestID, QuestKind, QuestType });
					}
				}
			}

			smTRANS_QUEST_INFO TransQuestInfo = {};
			TransQuestInfo.code = OpCode::OPCODE_SPOILER_INFO;
			TransQuestInfo.SpoilerNum = SpoilerNum;

			for (auto Progress : vProgress)
			{
				switch (Progress.QuestKind)
				{
				case 7:
					if (db->Prepare("SELECT * FROM DailyQuest WHERE QuestID=? AND QuestType=? ORDER BY QuestName ASC"))
					{
						db->BindInputParameter(&Progress.QuestID, 1, PARAMTYPE_Integer);
						db->BindInputParameter(&Progress.QuestType, 2, PARAMTYPE_Integer);
						if (db->Execute(false))
						{
							while (db->NextRow())
							{
								int cnt = TransQuestInfo.QuestCount;

								db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestID, 4, 1, PARAMTYPE_Integer);
								db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestName, 128, 2, PARAMTYPE_String);
								TransQuestInfo.QuestInfo[cnt].QuestKind = Progress.QuestKind;
								TransQuestInfo.QuestInfo[cnt].QuestActive = false;

								TransQuestInfo.QuestCount++;

								if (TransQuestInfo.QuestCount == 58)
								{
									TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
									lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);

									TransQuestInfo.QuestCount = 0;
									ZeroMemory(&TransQuestInfo.QuestInfo, sizeof(sNEW_QUEST_INFO) * 58);
								}
							}
						}
					}
					break;

				case 9:
					if (db->Prepare("SELECT * FROM SingleQuest WHERE QuestID=? AND QuestType=? ORDER BY QuestName ASC"))
					{
						db->BindInputParameter(&Progress.QuestID, 1, PARAMTYPE_Integer);
						db->BindInputParameter(&Progress.QuestType, 2, PARAMTYPE_Integer);
						if (db->Execute(false))
						{
							while (db->NextRow())
							{
								int cnt = TransQuestInfo.QuestCount;

								db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestID, 4, 1, PARAMTYPE_Integer);
								db->GetData(&TransQuestInfo.QuestInfo[cnt].QuestName, 128, 2, PARAMTYPE_String);
								TransQuestInfo.QuestInfo[cnt].QuestKind = Progress.QuestKind;
								TransQuestInfo.QuestInfo[cnt].QuestActive = false;

								TransQuestInfo.QuestCount++;

								if (TransQuestInfo.QuestCount == 58)
								{
									TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
									lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);

									TransQuestInfo.QuestCount = 0;
									ZeroMemory(&TransQuestInfo.QuestInfo, sizeof(sNEW_QUEST_INFO) * 58);
								}
							}
						}
					}
					break;
				}
			}

			//if (TransQuestInfo.QuestCount)
			//{
			TransQuestInfo.size = sizeof(smTRANS_QUEST_INFO);
			lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);
			//}

			db->Close();
		}
		break;
	}
}

#include "Server/onserver.h"

void cQUESTHANDLER::GetQuestInfo(rsPLAYINFO* lpPlayInfo, int QuestID, int QuestKind, int SpoilerNum)
{
	smTRANS_QUEST_FULL TransQuestInfo = {};
	shared_ptr<Database> db = Database::GetConnection(DATABASEID_QuestDB);

	TransQuestInfo.code = OpCode::OPCODE_QUEST_INFO;
	TransQuestInfo.size = sizeof(smTRANS_QUEST_FULL);
	TransQuestInfo.QuestKind = SpoilerNum;

	switch (QuestKind)
	{
	case 7:
		if (db->Open())
		{
			char playerName[32];
			wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());

			if (db->Prepare("SELECT * FROM DailyQuest WHERE QuestID=?"))
			{
				db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
				if (db->Execute())
				{
					db->GetData(&TransQuestInfo.QuestID, 4, 1, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.QuestName, 128, 2, PARAMTYPE_String);
					db->GetData(&TransQuestInfo.QuestTitle, 128, 3, PARAMTYPE_String);
					db->GetData(&TransQuestInfo.LevelMin, 4, 4, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.LevelMax, 4, 5, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.PartyFlag, 4, 6, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.QuestDesc, 500, 7, PARAMTYPE_String);
					db->GetData(&TransQuestInfo.QuestType, 4, 8, PARAMTYPE_Integer);
				}
			}

			if (db->Prepare("SELECT * FROM QuestMonsters WHERE QuestID=? AND QuestKind=? AND QuestType=?"))
			{
				db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
				db->BindInputParameter(&TransQuestInfo.QuestType, 3, PARAMTYPE_Integer);
				if (db->Execute(false))
				{
					while (db->NextRow() && TransQuestInfo.MonsterCount < 4)
					{
						int i = TransQuestInfo.MonsterCount;

						db->GetData(TransQuestInfo.MonsterNames[i], 32, 3, PARAMTYPE_String);
						db->GetData(&TransQuestInfo.MonsterCounts[i], 4, 4, PARAMTYPE_Integer);
						db->GetData(&TransQuestInfo.MonsterMaps[i], 4, 6, PARAMTYPE_Integer);
						TransQuestInfo.MonsterCount++;
					}
				}
			}

			if (TransQuestInfo.MonsterCount)
			{
				for (int i = 0; i < TransQuestInfo.MonsterCount; i++)
				{
					if (db->Prepare("SELECT * FROM MonsterKilled WHERE PlayerName=? AND MonsterName=? AND QuestType=? AND QuestKind=? AND QuestID=? AND QuestMap=?"))
					{
						db->BindInputParameter(playerName, 1, PARAMTYPE_String);
						db->BindInputParameter(TransQuestInfo.MonsterNames[i], 2, PARAMTYPE_String);
						db->BindInputParameter(&TransQuestInfo.QuestType, 3, PARAMTYPE_Integer);
						db->BindInputParameter(&QuestKind, 4, PARAMTYPE_Integer);
						db->BindInputParameter(&QuestID, 5, PARAMTYPE_Integer);
						db->BindInputParameter(&TransQuestInfo.MonsterMaps[i], 6, PARAMTYPE_Integer);
						if (db->Execute())
						{
							db->GetData(&TransQuestInfo.MonsterKilled[i], 4, 2, PARAMTYPE_Integer);
						}
					}
				}
			}

			if (db->Prepare("SELECT * FROM Rewards WHERE QuestID=? AND QuestKind=? AND QuestType=?"))
			{
				db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
				db->BindInputParameter(&TransQuestInfo.QuestType, 3, PARAMTYPE_Integer);
				if (db->Execute())
				{
					db->GetData(&TransQuestInfo.RewardGold, 4, 3, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.RewardExp, 8, 4, PARAMTYPE_Int64);
					db->GetData(&TransQuestInfo.RewardCoin, 4, 6, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.RewardTCoin, 4, 7, PARAMTYPE_Integer);
				}
			}

			if (db->Prepare("SELECT * FROM ItemRewards WHERE QuestID=? AND QuestKind=? AND QuestType=?"))
			{
				db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
				db->BindInputParameter(&TransQuestInfo.QuestType, 3, PARAMTYPE_Integer);
				if (db->Execute(false))
				{
					while (db->NextRow() && TransQuestInfo.RewardCount < 4)
					{
						int i = TransQuestInfo.RewardCount;

						char szCode[32];
						db->GetData(szCode, 32, 3, PARAMTYPE_String);
						db->GetData(&TransQuestInfo.RewardCounts[i], 4, 4, PARAMTYPE_Integer);

						for (int cnt = 0; cnt < MAX_ITEM; cnt++)
						{
							if (!lstrcmpi(szCode, sItem[cnt].LastCategory))
							{
								for (int cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
								{
									if (sItem[cnt].CODE == DefaultItems[cnt2].Item.CODE)
									{
										lstrcpy(TransQuestInfo.RewardNames[i], DefaultItems[cnt2].Item.ItemName);
										break;
									}
								}
								break;
							}
						}

						TransQuestInfo.RewardCount++;
					}
				}
			}

			if (db->Prepare("SELECT * FROM Complete WHERE QuestType=? AND QuestKind=7 AND PlayerName=? ORDER BY EndDate DESC"))
			{
				db->BindInputParameter(&TransQuestInfo.QuestType, 1, PARAMTYPE_Integer);
				db->BindInputParameter(playerName, 2, PARAMTYPE_String);
				if (db->Execute())
				{
					db->GetData(&TransQuestInfo.EndTime, sizeof(SYSTEMTIME), 5, PARAMTYPE_Time);
				}
			}

			db->Close();
		}
		break;

	case 9:
		if (db->Open())
		{
			if (db->Prepare("SELECT * FROM SingleQuest WHERE QuestID=?"))
			{
				db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
				if (db->Execute())
				{
					db->GetData(&TransQuestInfo.QuestID, 4, 1, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.QuestName, 128, 2, PARAMTYPE_String);
					db->GetData(&TransQuestInfo.QuestTitle, 128, 3, PARAMTYPE_String);
					db->GetData(&TransQuestInfo.LevelMin, 4, 4, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.LevelMax, 4, 5, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.PartyFlag, 4, 6, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.QuestDesc, 500, 7, PARAMTYPE_String);
					db->GetData(&TransQuestInfo.QuestType, 4, 8, PARAMTYPE_Integer);
				}
			}

			if (db->Prepare("SELECT * FROM QuestMonsters WHERE QuestID=? AND QuestKind=? AND QuestType=?"))
			{
				db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
				db->BindInputParameter(&TransQuestInfo.QuestType, 3, PARAMTYPE_Integer);
				if (db->Execute(false))
				{
					while (db->NextRow() && TransQuestInfo.MonsterCount < 4)
					{
						int i = TransQuestInfo.MonsterCount;

						db->GetData(TransQuestInfo.MonsterNames[i], 32, 3, PARAMTYPE_String);
						db->GetData(&TransQuestInfo.MonsterCounts[i], 4, 4, PARAMTYPE_Integer);
						db->GetData(&TransQuestInfo.MonsterMaps[i], 4, 6, PARAMTYPE_Integer);
						TransQuestInfo.MonsterCount++;
					}
				}
			}

			if (TransQuestInfo.MonsterCount)
			{
				for (int i = 0; i < TransQuestInfo.MonsterCount; i++)
				{
					if (db->Prepare("SELECT * FROM MonsterKilled WHERE PlayerName=? AND MonsterName=? AND QuestType=? AND QuestKind=? AND QuestID=? AND QuestMap=?"))
					{
						char playerName[32];
						wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());

						db->BindInputParameter(playerName, 1, PARAMTYPE_String);
						db->BindInputParameter(TransQuestInfo.MonsterNames[i], 2, PARAMTYPE_String);
						db->BindInputParameter(&TransQuestInfo.QuestType, 3, PARAMTYPE_Integer);
						db->BindInputParameter(&QuestKind, 4, PARAMTYPE_Integer);
						db->BindInputParameter(&QuestID, 5, PARAMTYPE_Integer);
						db->BindInputParameter(&TransQuestInfo.MonsterMaps[i], 6, PARAMTYPE_Integer);
						if (db->Execute())
						{
							db->GetData(&TransQuestInfo.MonsterKilled[i], 4, 2, PARAMTYPE_Integer);
						}
					}
				}
			}

			if (db->Prepare("SELECT * FROM Rewards WHERE QuestID=? AND QuestKind=? AND QuestType=?"))
			{
				db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
				db->BindInputParameter(&TransQuestInfo.QuestType, 3, PARAMTYPE_Integer);
				if (db->Execute())
				{
					db->GetData(&TransQuestInfo.RewardGold, 4, 3, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.RewardExp, 8, 4, PARAMTYPE_Int64);
					db->GetData(&TransQuestInfo.RewardCoin, 4, 6, PARAMTYPE_Integer);
					db->GetData(&TransQuestInfo.RewardTCoin, 4, 7, PARAMTYPE_Integer);
				}
			}

			if (db->Prepare("SELECT * FROM ItemRewards WHERE QuestID=? AND QuestKind=? AND QuestType=?"))
			{
				db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
				db->BindInputParameter(&TransQuestInfo.QuestType, 3, PARAMTYPE_Integer);
				if (db->Execute(false))
				{
					while (db->NextRow() && TransQuestInfo.RewardCount < 4)
					{
						int i = TransQuestInfo.RewardCount;

						char szCode[32];
						db->GetData(szCode, 32, 3, PARAMTYPE_String);
						db->GetData(&TransQuestInfo.RewardCounts[i], 4, 4, PARAMTYPE_Integer);

						for (int cnt = 0; cnt < MAX_ITEM; cnt++)
						{
							if (!lstrcmpi(szCode, sItem[cnt].LastCategory))
							{
								for (int cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
								{
									if (sItem[cnt].CODE == DefaultItems[cnt2].Item.CODE)
									{
										lstrcpy(TransQuestInfo.RewardNames[i], DefaultItems[cnt2].Item.ItemName);
										break;
									}
								}
								break;
							}
						}

						TransQuestInfo.RewardCount++;
					}
				}
			}

			char playerName[32];
			wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());

			if (db->Prepare("SELECT * FROM Complete WHERE QuestType=? AND QuestKind=9 AND PlayerName=? ORDER BY EndDate DESC"))
			{
				db->BindInputParameter(&TransQuestInfo.QuestType, 1, PARAMTYPE_Integer);
				db->BindInputParameter(playerName, 2, PARAMTYPE_String);
				if (db->Execute())
				{
					db->GetData(&TransQuestInfo.EndTime, sizeof(SYSTEMTIME), 5, PARAMTYPE_Time);
				}
			}

			db->Close();
		}
		break;
	}

	if (lpPlayInfo->lpsmSock)
		lpPlayInfo->lpsmSock->Send((char*)&TransQuestInfo, TransQuestInfo.size, TRUE);
}

void cQUESTHANDLER::StartQuest(rsPLAYINFO* lpPlayInfo, int QuestID, int QuestKind, int QuestType, int PartyFlag)
{
	shared_ptr<Database> db = Database::GetConnection(DATABASEID_QuestDB);

	switch (QuestKind)
	{
	case 7:
		if (db->Open())
		{
			if (db->Prepare("IF EXISTS(SELECT * FROM DailyQuest WHERE QuestID=?) BEGIN INSERT INTO Progress VALUES (?, ?, ?, ?, GETDATE()) END"))
			{
				char playerName[32];
				wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());

				db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestID, 2, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestKind, 3, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestType, 4, PARAMTYPE_Integer);
				db->BindInputParameter(playerName, 5, PARAMTYPE_String);
				if (db->Execute(false))
				{
					char MonsterName[4][32];
					int MonsterCounts[4];
					int MonsterMaps[4];
					int MonsterCount = 0;

					if (db->Prepare("SELECT * FROM QuestMonsters WHERE QuestID=? AND QuestKind=? AND QuestType=?"))
					{
						db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
						db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
						db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);

						if (db->Execute(false))
						{
							while (db->NextRow())
							{
								if (MonsterCount >= 4)
									break;

								db->GetData(&MonsterName[MonsterCount], 32, 3, PARAMTYPE_String);
								db->GetData(&MonsterCounts[MonsterCount], 4, 4, PARAMTYPE_Integer);
								db->GetData(&MonsterMaps[MonsterCount], 4, 6, PARAMTYPE_Integer);

								MonsterCount++;
							}
						}
					}

					if (MonsterCount)
					{
						for (int i = 0; i < MonsterCount; i++)
						{
							if (isRightMonster(QuestID, MonsterName[MonsterCount])) {
								if (db->Prepare("INSERT INTO MonsterKilled VALUES (?,0,?,?,?,?,?,?,?)"))
								{
									    db->BindInputParameter(&MonsterName[i], 1, PARAMTYPE_String);
										db->BindInputParameter(&MonsterCounts[i], 2, PARAMTYPE_Integer);
										db->BindInputParameter(&QuestID, 3, PARAMTYPE_Integer);
										db->BindInputParameter(&QuestKind, 4, PARAMTYPE_Integer);
										db->BindInputParameter(&QuestType, 5, PARAMTYPE_Integer);
										db->BindInputParameter(playerName, 6, PARAMTYPE_String);
										db->BindInputParameter(&PartyFlag, 7, PARAMTYPE_Integer);
										db->BindInputParameter(&MonsterMaps[i], 8, PARAMTYPE_Integer);

										db->Execute(false);
								}
							}
						}
					}
				}
			}
			db->Close();
		}
		break;

	case 9:
		if (db->Open())
		{
			if (db->Prepare("IF EXISTS(SELECT * FROM SingleQuest WHERE QuestID=?) BEGIN INSERT INTO Progress VALUES (?, ?, ?, ?, GETDATE()) END"))
			{
				char playerName[32];
				wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());

				db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestID, 2, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestKind, 3, PARAMTYPE_Integer);
				db->BindInputParameter(&QuestType, 4, PARAMTYPE_Integer);
				db->BindInputParameter(playerName, 5, PARAMTYPE_String);
				if (db->Execute(false))
				{
					char MonsterName[4][32] = {};
					int MonsterCounts[4];
					int MonsterMaps[4];
					int MonsterCount = 0;

					if (db->Prepare("SELECT * FROM QuestMonsters WHERE QuestID=? AND QuestKind=? AND QuestType=?"))
					{
						db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
						db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
						db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);

						if (db->Execute(false))
						{
							while (db->NextRow())
							{
								if (MonsterCount >= 4)
									break;

								db->GetData(&MonsterName[MonsterCount], 32, 3, PARAMTYPE_String);
								db->GetData(&MonsterCounts[MonsterCount], 4, 4, PARAMTYPE_Integer);
								db->GetData(&MonsterMaps[MonsterCount], 4, 6, PARAMTYPE_Integer);

								MonsterCount++;
							}
						}
					}

					if (MonsterCount)
					{
						for (int i = 0; i < MonsterCount; i++)
						{
							if (db->Prepare("INSERT INTO MonsterKilled VALUES (?,0,?,?,?,?,?,?,?)"))
							{
								db->BindInputParameter(&MonsterName[i], 1, PARAMTYPE_String);
								db->BindInputParameter(&MonsterCounts[i], 2, PARAMTYPE_Integer);
								db->BindInputParameter(&QuestID, 3, PARAMTYPE_Integer);
								db->BindInputParameter(&QuestKind, 4, PARAMTYPE_Integer);
								db->BindInputParameter(&QuestType, 5, PARAMTYPE_Integer);
								db->BindInputParameter(playerName, 6, PARAMTYPE_String);
								db->BindInputParameter(&PartyFlag, 7, PARAMTYPE_Integer);
								db->BindInputParameter(&MonsterMaps[i], 8, PARAMTYPE_Integer);
								db->Execute(false);
							}
						}
					}
				}
			}
			db->Close();
		}
		break;
	}

	GetSpoilerInfo(lpPlayInfo, QuestKind);
	if (QuestKind != 10)
		GetSpoilerInfo(lpPlayInfo, 10);
}

void cQUESTHANDLER::CancelQuest(rsPLAYINFO* lpPlayInfo, int QuestID, int QuestKind, int QuestType)
{
	shared_ptr<Database> db = Database::GetConnection(DATABASEID_QuestDB);

	if (db->Open())
	{
		char playerName[32];
		wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());
		if (db->Prepare("DELETE FROM Progress WHERE QuestID=? AND QuestKind=? AND QuestType=? AND PlayerName=?"))
		{
			db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
			db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
			db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);
			db->BindInputParameter(playerName, 4, PARAMTYPE_String);
			db->Execute();
		}

		if (db->Prepare("DELETE FROM MonsterKilled WHERE QuestID=? AND QuestKind=? AND QuestType=? AND PlayerName=?"))
		{
			db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
			db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
			db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);
			db->BindInputParameter(playerName, 4, PARAMTYPE_String);
			db->Execute();
		}
		db->Close();
	}

	GetSpoilerInfo(lpPlayInfo, QuestKind);
	if (QuestKind != 10)
		GetSpoilerInfo(lpPlayInfo, 10);
}

void SendPostBox(char* szID, char* szItemCode, int spec)
{
	char szFileName[255];
	char strBuff[255];
	DWORD dwAcess = 0;
	GetPostBoxFile(szID, szFileName);
	HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	else
	{
		int FileLength = GetFileSize(hFile, NULL);
		SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);

		sprintf_s(strBuff, "* %s %d \"Quest\"\r\n", szItemCode, spec);
		WriteFile(hFile, strBuff, lstrlen(strBuff), &dwAcess, NULL);
		CloseHandle(hFile);
	}
}

void cQUESTHANDLER::GetReward(rsPLAYINFO* lpPlayInfo, int QuestID, int QuestKind, int QuestType)
{
	shared_ptr<Database> db = Database::GetConnection(DATABASEID_QuestDB);

	if (db->Open())
	{
		if (db->Prepare("SELECT * FROM Progress WHERE QuestID=? AND QuestKind=? AND QuestType=? AND PlayerName=?"))
		{
			char playerName[32];
			wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());

			db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
			db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
			db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);
			db->BindInputParameter(playerName, 4, PARAMTYPE_String);
			if (db->Execute())
			{
				//char MonsterName[4][32] = {};
				int MonsterKilled[4] = {};
				int MonsterCounts[4] = {};
				int MonsterCount = 0;

				if (db->Prepare("SELECT * FROM MonsterKilled WHERE QuestID=? AND QuestKind=? AND QuestType=? AND PlayerName=?"))
				{
					db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
					db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
					db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);
					db->BindInputParameter(playerName, 4, PARAMTYPE_String);
					if (db->Execute(false))
					{
						while (db->NextRow())
						{
							//db->GetData(&MonsterName[MonsterCount], 32, 1, PARAMTYPE_String);
							db->GetData(&MonsterKilled[MonsterCount], 4, 2, PARAMTYPE_Integer);
							db->GetData(&MonsterCounts[MonsterCount], 4, 3, PARAMTYPE_Integer);
							MonsterCount++;
						}
					}
				}

				if (MonsterCount)
				{
					bool isComplete = true;
					for (int i = 0; i < MonsterCount; i++)
					{
						if (MonsterKilled[i] != MonsterCounts[i])
							isComplete = false;
					}

					if (isComplete)
					{
						char playerID[32];
						wsprintf(playerID, "%s", lpPlayInfo->getAccount().c_str());

						if (db->Prepare("DELETE FROM Progress WHERE QuestID=? AND QuestKind=? AND QuestType=? AND PlayerName=?"))
						{
							db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);
							db->BindInputParameter(playerName, 4, PARAMTYPE_String);
							db->Execute();
						}

						if (db->Prepare("DELETE FROM MonsterKilled WHERE QuestID=? AND QuestKind=? AND QuestType=? AND PlayerName=?"))
						{
							db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);
							db->BindInputParameter(playerName, 4, PARAMTYPE_String);
							db->Execute();
						}

						if (db->Prepare("IF NOT EXISTS(SELECT * FROM Complete WHERE QuestID=? AND QuestKind=? AND QuestType=? AND PlayerName=?) BEGIN INSERT INTO Complete VALUES (?,?,?,?,GETDATE()) END ELSE BEGIN UPDATE Complete SET EndDate=GETDATE() WHERE QuestID=? AND QuestKind=? AND QuestType=? AND PlayerName=? END"))
						{
							db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);
							db->BindInputParameter(playerName, 4, PARAMTYPE_String);
							db->BindInputParameter(&QuestID, 5, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestKind, 6, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestType, 7, PARAMTYPE_Integer);
							db->BindInputParameter(playerName, 8, PARAMTYPE_String);
							db->BindInputParameter(&QuestID, 9, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestKind, 10, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestType, 11, PARAMTYPE_Integer);
							db->BindInputParameter(playerName, 12, PARAMTYPE_String);
							db->Execute();
						}

						if (db->Prepare("SELECT * FROM Rewards WHERE QuestID=? AND QuestKind=? AND QuestType=?"))
						{
							db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);
							if (db->Execute())
							{
								int Gold = 0;
								INT64 Exp = 0;
								int Coin = 0, TCoin = 0;

								db->GetData(&Gold, 4, 3, PARAMTYPE_Integer);
								db->GetData(&Exp, 8, 4, PARAMTYPE_Int64);
								db->GetData(&Coin, 4, 6, PARAMTYPE_Integer);
								db->GetData(&TCoin, 4, 7, PARAMTYPE_Integer);

								if (Exp)
								{
									smTRANS_COMMAND_QWORD smTransCommandQ = {};

									smTransCommandQ.code = OpCode::OPCODE_NEW_ADDEXP;
									smTransCommandQ.size = sizeof(smTRANS_COMMAND_QWORD);
									smTransCommandQ.WParam = Exp;

									lpPlayInfo->lpsmSock->Send((char*)&smTransCommandQ, smTransCommandQ.size, TRUE);
								}

								if (Gold)
								{
									SendPostBox(playerID, "GG101", Gold);
								}

								if (Coin)
								{
									//Shop::GetInstance()->AddPlayerCoin(lpPlayInfo, Coin);
								}
							}
						}

						if (db->Prepare("SELECT * FROM ItemRewards WHERE QuestID=? AND QuestKind=? AND QuestType=?"))
						{
							db->BindInputParameter(&QuestID, 1, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestKind, 2, PARAMTYPE_Integer);
							db->BindInputParameter(&QuestType, 3, PARAMTYPE_Integer);
							if (db->Execute(false))
							{
								char szItemCode[4][32];
								int ItemCounts[4];
								int ItemCount = 0;

								while (db->NextRow())
								{
									db->GetData(&szItemCode[ItemCount], 32, 3, PARAMTYPE_String);
									db->GetData(&ItemCounts[ItemCount], 4, 4, PARAMTYPE_Integer);
									ItemCount++;
								}

								if (ItemCount)
								{
									for (int i = 0; i < ItemCount; i++)
									{
										if (szItemCode[i][0] == 'P' || szItemCode[i][0] == 'p' || szItemCode[i][0] == 'G' || szItemCode[i][0] == 'g')
											SendPostBox(playerID, szItemCode[i], ItemCounts[i]);
										else
										{
											for (int j = 0; j < ItemCounts[i]; j++)
												SendPostBox(playerID, szItemCode[i], lpPlayInfo->smCharInfo.JOB_CODE);
										}
									}

									TRANS_CHATMESSAGE Message = {};
									Message.code = OpCode::OPCODE_MESSAGEBOX;
									wsprintf(Message.szMessage, "Itens enviados ao Distribuidor.");
									Message.size = lstrlen(Message.szMessage) + 32;
									lpPlayInfo->lpsmSock->Send((char*)&Message, Message.size, TRUE);
								}
							}
						}
					}
				}

			}
		}
		db->Close();
	}

	GetSpoilerInfo(lpPlayInfo, QuestKind);
	if (QuestKind != 10)
		GetSpoilerInfo(lpPlayInfo, 10);
	if (QuestKind != 11)
		GetSpoilerInfo(lpPlayInfo, 11);
}

bool cQUESTHANDLER::inQuest(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar)
{
	shared_ptr<Database> db = Database::GetConnection(DATABASEID_QuestDB);
	bool result = false;
	if (db->Open())
	{
		if (db->Prepare("SELECT * FROM MonsterKilled WHERE PlayerName=? AND (MonsterName=? OR QuestMap=?) AND PartyFlag=1"))
		{
			char playerName[32];
			wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());

			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			db->BindInputParameter(lpChar->smCharInfo.szName, 2, PARAMTYPE_String);
			db->BindInputParameter(&lpPlayInfo->Position.Area, 3, PARAMTYPE_Integer);
			if (db->Execute())
			{
				result = true;
			}
		}
		db->Close();
	}
	return result;
}

void cQUESTHANDLER::VerifyLevel(rsPLAYINFO* lpPlayInfo)
{
	struct quest { int QuestID, QuestKind, QuestType; };
	shared_ptr<Database> db = Database::GetConnection(DATABASEID_QuestDB);
	vector<quest> vQuests;

	if (db->Open())
	{
		if (db->Prepare("SELECT * FROM Progress WHERE PlayerName=?"))
		{
			char playerName[32];
			wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());
			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			if (db->Execute(false))
			{
				while (db->NextRow())
				{
					int QuestID, QuestKind, QuestType;
					db->GetData(&QuestID, 4, 1, PARAMTYPE_Integer);
					db->GetData(&QuestKind, 4, 2, PARAMTYPE_Integer);
					db->GetData(&QuestType, 4, 3, PARAMTYPE_Integer);

					vQuests.push_back({ QuestID, QuestKind, QuestType });
				}
			}
		}

		for (vector<quest>::iterator it = vQuests.begin(); it < vQuests.end(); it++)
		{
			char buff[255] = {};
			quest* pq = &(*it);
			switch (pq->QuestKind)
			{
			case 7:
				wsprintf(buff, "SELECT * FROM DailyQuest WHERE QuestID=? AND QuestType=? AND (LevelMin > ? OR LevelMax < ?)");
				break;

			case 9:
				wsprintf(buff, "SELECT * FROM SingleQuest WHERE QuestID=? AND QuestType=? AND (LevelMin > ? OR LevelMax < ?)");
				break;
			}

			if (db->Prepare(buff))
			{
				db->BindInputParameter(&pq->QuestID, 1, PARAMTYPE_Integer);
				db->BindInputParameter(&pq->QuestType, 2, PARAMTYPE_Integer);
				db->BindInputParameter(&lpPlayInfo->smCharInfo.Level, 3, PARAMTYPE_Integer);
				db->BindInputParameter(&lpPlayInfo->smCharInfo.Level, 4, PARAMTYPE_Integer);
				if (db->Execute(false))
				{
					if (!db->NextRow())
					{
						vQuests.erase(it);
						it--;
					}
				}
			}
		}
		db->Close();
	}

	for (auto q : vQuests)
	{
		CancelQuest(lpPlayInfo, q.QuestID, q.QuestKind, q.QuestType);
	}
}


bool cQUESTHANDLER::KillMonster(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar, int PartyFlag)
{
	shared_ptr<Database> db = Database::GetConnection(DATABASEID_QuestDB);

	if (db->Open())
	{
		char playerName[32];
		char monsterName[32];
		wsprintf(playerName, "%s", lpPlayInfo->getName().c_str());

		char* szBuff = "SELECT * FROM MonsterKilled WHERE PlayerName=? AND ((MonsterName=? AND QuestMap=-1) OR (QuestMap=?)) AND Killed < Count";
		if (PartyFlag)
			szBuff = "SELECT * FROM MonsterKilled WHERE PlayerName=? AND ((MonsterName=? AND QuestMap=-1) OR (QuestMap=?)) AND PartyFlag=1 AND Killed < Count AND QuestKind!=8";

		if (db->Prepare(szBuff))
		{
			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			db->BindInputParameter(lpChar->smCharInfo.szName, 2, PARAMTYPE_String);
			db->BindInputParameter(&lpPlayInfo->Position.Area, 3, PARAMTYPE_Integer);
			if (db->Execute(false))
			{
				while (db->NextRow())
				{
					TRANS_CHATMESSAGE TransChatMessage;

					int killed = 0, count = 0;

					db->GetData(monsterName, 32, 1, PARAMTYPE_String);
					db->GetData(&killed, 4, 2, PARAMTYPE_Integer);
					db->GetData(&count, 4, 3, PARAMTYPE_Integer);

					if (lstrcmpi(monsterName, lpChar->smCharInfo.szName) == 0) {
						TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
						wsprintf(TransChatMessage.szMessage, "> %s killed %d/%d", lpChar->smCharInfo.szName, killed + 1, count);
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwIP = 9;
						TransChatMessage.dwObjectSerial = 0;

						lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
					}
					else {
						return true;
					}
				}
			}
		}

		szBuff = "UPDATE MonsterKilled SET Killed+=1 WHERE PlayerName=? AND ((MonsterName=? AND QuestMap=-1) OR (QuestMap=?)) AND Killed < Count";

		if (PartyFlag)
			szBuff = "UPDATE MonsterKilled SET Killed+=1 WHERE PlayerName=? AND ((MonsterName=? AND QuestMap=-1) OR (QuestMap=?)) AND PartyFlag=1 AND Killed < Count AND QuestKind != 8";

		if (db->Prepare(szBuff))
		{
			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			db->BindInputParameter(lpChar->smCharInfo.szName, 2, PARAMTYPE_String);
			db->BindInputParameter(&lpPlayInfo->Position.Area, 3, PARAMTYPE_Integer);

			db->Execute(false);
		}

		db->Close();
	}
	return true;
}
