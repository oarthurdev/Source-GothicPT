


#define MONSTER_BAGON				1
#define MONSTER_SKELETON_WARRIOR	2
#define MONSTER_HEAD_CUTTER			3
#define MONSTER_ARMORED_BETTLE		4
#define MONSTER_SKELETON_RANGER		5
#define MONSTER_TITAN				6
#define MONSTER_MURPIN				7
#define MONSTER_DIREBEE				8
#define MONSTER_TYPOON				9
#define MONSTER_RATOO				10
#define MONSTER_GROTESQUE			11
#define MONSTER_IRONFIST			12
#define MONSTER_OMEGA				13
#define MONSTER_D_MACHINE			14
#define MONSTER_MOUNTAIN			15


#define MONSTER_SKELETON_KNIGHT     16 
#define MONSTER_SOLID_SNAIL         17 
#define MONSTER_THORN_CROWLER       18 
#define MONSTER_MUMMY               19 
#define MONSTER_DOOM_GUARD          20 
#define MONSTER_FIGON               21 
#define MONSTER_STONE_GIANT         22 
#define MONSTER_STONE_COLEM         23 
#define MONSTER_IRON_GUARD          24 
#define MONSTER_AVELLRIN            25 

#define MONSTER_AVELRISK_L          26 
#define MONSTER_BEEBUL              27 
#define MONSTER_ILLUSION_KNIGHT     28 
#define MONSTER_NIGHT_MARE          29 
#define MONSTER_WITCH               30 
#define MONSTER_HEAVY_GOBLIN        31 
#define MONSTER_DAWLIN              32 
#define MONSTER_STYGIAN             33 
#define MONSTER_INCUBUS             34 
#define MONSTER_CHAIN_GOLEM         35 
#define MONSTER_DARK_SPECTOR	    36 
#define MONSTER_METRON              37 

#define MONSTER_AVELRISK_LOAD       38 
#define MONSTER_DUSK                39 
#define MONSTER_SADNESS             40 


#define MONSTER_HOPY                41 
#define MONSTER_RABIE               42 
#define MONSTER_NORTHGOBLIN         43 
#define MONSTER_HOBGOBLIN           44 
#define MONSTER_CORRUPT             45 
#define MONSTER_SKELETON            46 
#define MONSTER_CYCLOPS             47 

#define MONSTER_FERRUMHEART         48 
#define MONSTER_ICE                 49 






#define QUESTBIT_LEVEL_30			1
#define QUESTBIT_LEVEL_55			2
#define QUESTBIT_LEVEL_70			4
#define QUESTBIT_LEVEL_80			8
#define QUESTBIT_LEVEL_85			16
#define QUESTBIT_LEVEL_90			32
#define QUESTBIT_LEVEL_80_2			64
#define QUESTBIT_LEVEL_90_2			128






#define SIN_QUEST_CODE_CHANGEJOB		0x0001
#define SIN_QUEST_CODE_CHANGEJOB2_NPC_M	0x0002
#define SIN_QUEST_CODE_CHANGEJOB2_NPC_D	0x0003
#define SIN_QUEST_CODE_CHANGEJOB3   	0x0004
#define SIN_QUEST_CODE_CHANGEJOB4   	0x0010


#define SIN_QUEST_CODE_LEVEL30			0x0005
#define SIN_QUEST_CODE_LEVEL55			0x0006
#define SIN_QUEST_CODE_LEVEL55_2		0x0007
#define SIN_QUEST_CODE_LEVEL70			0x0008
#define SIN_QUEST_CODE_LEVEL80			0x0009
#define SIN_QUEST_CODE_LEVEL85			0x000A
#define SIN_QUEST_CODE_LEVEL90			0x000B


#define SIN_QUEST_CODE_LEVEL80_2		0x000C 
#define SIN_QUEST_CODE_LEVEL90_2		0x000D 



#define SIN_QUEST_PROGRESS				1
#define SIN_QUEST_COMPLETE				2


struct sQUEST_CHANGEJOB
{
	DWORD CODE;
	DWORD BackUpCode;
	int Kind;
	int State;

};

struct sQUEST_CHANGEJOB3
{
	DWORD CODE;
	DWORD BackUpCode;
	int   Kind;
	int   State;
	short Monster[2];
	int   StartLevel;
	int   AgingCount;

};



struct sQUEST_WINGITEM
{
	DWORD CODE;
	int Kind;
	int State;

};


int sinCheckChageJob();



int sinLoadQuest(int CODE, void *Buff);
int sinSaveQuest(void *Buff);


int sinMorayionNpcChangeJob_Two();


int sinNpcChangeJob3();


int SetChangeJob3QuestItem(sITEMINFO *pItem, int Down = 0);


int CheckChangeJob3QuestItem(DWORD Monster_CODE);


int DeleteQuestItem(DWORD CODE);


int CheckChangeJob_QuestItem();


int sinCheckLevelQuest30();
int sinCheckLevelQuest55();
int sinCheckLevelQuest55_2();
int sinCheckLevelQuest70();
int sinCheckLevelQuest80();
int sinCheckLevelQuest85();
int sinCheckQuest85Die();
int sinCheckLevelQuest90();
int sinCheckLevelQuest80_2(int NpcNum = 0);
int sinCheckLevelQuest80_2Item();
int sinCheckLevelQuest90_2(int NpcNum = 0);

int sinSetSendItem80_2();

int CheckNowQuestState(DWORD CODE);

int ClearNowQuest();

int sinCheckChangeJobQuest4();
int sinSetQuestTimer(sQUEST_CHANGEJOB3 *pQuset, int UseTime = 0, int CheckTime = 0);

int sinChangeJob4MonSet(sQUEST_CHANGEJOB3 *pQuset);


int sinBattleNpcResult(int WinFlag);


char *sinGetMonsterName(int CODE);


int sinCompleteChangeJob4(int Index);



extern POINT QuestMessageBoxPosi2;
extern POINT QuestMessageBoxSize2;
extern int sinChangeJobButtonShow;
extern int sinChangeJobButtonShow2;
extern int sinChangeJobButtonShow3;
extern int sinChangeJobButtonShow4;

extern char *QuestFilePath[];
extern char *QuestFilePath3[];
extern int CheckQuestComplete;

extern int CheckQuestButtonShow1;
extern int CheckQuestButtonShow2;
extern int CheckQuestButtonShow3;



extern sQUEST_CHANGEJOB	sinQuest_ChangeJob;
extern sQUEST_CHANGEJOB	sinQuest_ChangeJob2;
extern sQUEST_CHANGEJOB3   sinQuest_ChangeJob3;
extern sQUEST_CHANGEJOB3   sinQuest_ChangeJob4;

extern char *WingQuestFilePath_a[];
extern char *WingQuestFilePath_b[];
extern char *WarpGateDoc[];
extern char *WarningInitPoint[];
extern char *HaWarpGateDoc[];

extern sITEM TempQuestItem;
extern int CheckQuestItemDownFlag;

extern char *BabelEventDoc;
extern char *NineTailFoxDoc;
extern char *StarDustDoc;
extern char *CristalEventDoc;


extern char *WatermelonDoc;

extern char *PumpkinDoc;

extern char *StarDoc;

extern char *ValentineDoc;

extern char *PristonAlphabetDoc;


extern char *CandydaysDoc;


extern char *MagicalGreenDoc;


extern char *TearOfKaraDoc;


extern char*Findinvestigator1_1Doc;
extern char*Findinvestigator1_2Doc;
extern char*Findinvestigator1_3Doc;
extern char*Findinvestigator2_1Doc;
extern char*Findinvestigator2_2Doc;
extern char*Findinvestigator3_1Doc;
extern char*Findinvestigator3_2Doc;

extern sQUEST_CHANGEJOB3   sinQuest_Level30;
extern sQUEST_CHANGEJOB3   sinQuest_Level55;
extern sQUEST_CHANGEJOB3   sinQuest_Level55_2;
extern sQUEST_CHANGEJOB3   sinQuest_Level70;
extern sQUEST_CHANGEJOB3   sinQuest_Level80;
extern sQUEST_CHANGEJOB3   sinQuest_Level85;
extern sQUEST_CHANGEJOB3   sinQuest_Level90;
extern DWORD sinQuest_levelLog;
extern sQUEST_CHANGEJOB3   sinQuest_Level80_2;
extern sQUEST_CHANGEJOB3   sinQuest_Level90_2;
extern char *QuestFilePath4[];
extern char szQuestMonsterName[64];
