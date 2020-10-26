#pragma once

#include <vector>
#include <basetsd.h>
#include <minwinbase.h>

class cQUESTWINDOW;

struct sOBJECT
{
	int ID;
	int Mat;
	int Mat_;
	int x;
	int y;
	int w;
	int h;
	int Opacity;
};

struct sFULL_INFO
{
	char QuestName[128];
	char QuestTitle[128];
	int LevelMin, LevelMax;
	int ClanLevelMin, ClanLevelMax;
	int PartyFlag;
	char QuestDesc[500];
	int QuestType;

	int MonsterCount;
	char MonsterNames[4][32];
	int MonsterCounts[4];
	int MonsterKilled[4];
	int MonsterMaps[4];

	int RewardCount;
	char RewardNames[4][32];
	int RewardCounts[4];
	int RewardGold;
	INT64 RewardExp;
	int RewardCoin;
	int RewardTCoin;
	INT64 RewardClanExp;

	SYSTEMTIME EndTime;
};

struct sQUEST
{
	int ID;
	int Kind;
	char szTitle[64];
	bool Selected;
	bool Complete = false;
	bool Active = true;

	sFULL_INFO QuestInfo;
};

class sSPOILER
{
public:
	int ID;
	int Mat;
	bool State;
	std::vector<sQUEST*> vQuests;
	sQUEST* pSelectedQuest;
	cQUESTWINDOW* pQuestWindow;
	bool ResetQuests = false;

	void AddQuest(int ID, int Kind, char* szTitle, bool Active);
	bool SetQuest(sQUEST* pQuest);
	void StartQuest(bool ok = false);
	void CancelQuest(bool ok = false);
	void GetReward();
	void DrawQuest(int BaseX, int BaseY);
};

struct sTAB
{
	int ID;
	int Mat[2];
	int x, y, w, h;
	bool Selected;
	std::vector<sSPOILER*> vSpoilers;
};

class cQUESTWINDOW
{
public:
	void Init();

	void AddObject(int ID, int Mat, int Mat_, int x, int y, int w, int h, int Opacity);
	sTAB* AddTab(int ID, int Mat, int Mat_, int x, int y, int w, int h, bool Selected);

	void AddSpoiler(sTAB* pTab, int ID, int Mat);
	void SwitchSpoiler(sSPOILER* pSpoiler);
	sSPOILER* GetSpoiler(int ID);
	void handlePacket(smTRANS_QUEST_INFO* pTransQuestInfo);
	void handlePacket(smTRANS_QUEST_FULL* pTransQuestInfo);
	sSPOILER* pSelectedSpoiler;

	void SelectTab(int TabID);
	void Open();
	void Close();
	void Draw();
	void KeyDown();
	void LButtonDown();

	void MouseWheel(short zDelta);

	bool OpenFlag;
	int BaseX, BaseY;
	int ScrollList;

	enum IMG
	{
		BG,
		CLOSE,
		PROGRESS_TAB,
		PROGRESS_TAB_,
		LIST_TAB,
		LIST_TAB_,
		BG_TAB,
		SPOILER_DAILY,
		SPOILER_QUESTS = 9,
		SPOILER_PROGRESS,
		SPOILER_FINALIZED,
		SPOILER_OPEN,
		SPOILER_CLOSE,
		ACCEPT_QUEST,
		ACCEPT_QUEST_,
		CANCEL_QUEST,
		CANCEL_QUEST_,
		GET_REWARD,
		GET_REWARD_,
		MAX_MAT,
	};

	int Mat[MAX_MAT];

	std::vector<sOBJECT*> vObjects;
	std::vector<sTAB*> vTabs;

	sTAB* pCurrentTab;
};

extern cQUESTWINDOW cQuestWindow;