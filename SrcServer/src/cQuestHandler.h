#pragma once

#include "Database/Database.h"
#include "sinbaram/sinLinkHeader.h"

class cQUESTHANDLER
{
public:
	void GetSpoilerInfo(rsPLAYINFO* lpPlayInfo, int SpoilerNum);
	void GetQuestInfo(rsPLAYINFO* lpPlayInfo, int QuestID, int QuestKind, int SpoilerNum);

	void StartQuest(rsPLAYINFO* lpPlayInfo, int QuestID, int QuestKind, int QuestType, int PartyFlag);
	void CancelQuest(rsPLAYINFO* lpPlayInfo, int QuestID, int QuestKind, int QuestType);
	void GetReward(rsPLAYINFO* lpPlayInfo, int QuestID, int QuestKind, int QuestType);
	bool inQuest(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar);
	void VerifyLevel(rsPLAYINFO* lpPlayInfo);

	struct sPROGRESS_INFO
	{
		int QuestID;
		int QuestKind;
		int QuestType;
	};

	bool KillMonster(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar, int PartyFlag);
};

extern cQUESTHANDLER cQuestHandler;