
#ifndef	_SINSUBMAIN_HEADER_

#define _SINSUBMAIN_HEADER_



#define SIN_OPEN		1
#define SIN_CLOSE		0


#define MAX_SIN_KIND_INTER		13  

#define SIN_CHARSTATUS	0
#define SIN_INVENTORY	1
#define SIN_SHOP		2
#define SIN_SKILL		3
#define SIN_TRADE		4
#define SIN_WAREHOUSE	5			
#define SIN_CRAFTITEM	6			
#define SIN_AGING		7			
#define SIN_MYSHOP		8			
#define SIN_CHARSHOP	9			
#define SIN_SMELTING	10			
#define SIN_MANUFACTURE 11			
#define	SIN_MIXTURE_RESET	12		
#define SIN_SYSTEM		13


#define SIN_ALL_CLOSE	100



#define SIN_AGING_ATTACK			100
#define SIN_AGING_CRITICAL			101
#define SIN_AGING_BLOCK				102
#define SIN_AGING_DEFENSE_ORB		103		
#define SIN_AGING_DEFENSE_ARMOR		104		
#define SIN_AGING_DEFENSE_BOOTS		105		
#define SIN_AGING_DEFENSE_GLOVES	106		
#define SIN_AGING_DEFENSE_ARMLETS	107		


#define PRORATE_USER		1
#define FREE_USER			2
#define VIP_USER			4
#define BIRTHDAY_USER		8



#define SIN_WINGRESULT_CRISTAL		0x101


void InitSub();

void MainSub();

void DrawSub();

void CloseSub();

void InitCursor();

void DrawCursor();

int sinRecvMessage(DWORD dwCode, void *RecvBuff);

void DrawSprite(int winX, int winY, DIRECTDRAWSURFACE pdds, int x, int y, int width, int height, int Bltflag = 1);

int sinGetItemInfo(DWORD CODE, char *szImagePath);

int sinUsePotion();

int sinSetInvenItem(sITEMINFO *sItemInfo);



int sinGetAccuracy(int desLV, int desDefense);

int sinGetMonsterAccuracy(int MonsterLV, int MonsterAttack_Rating);

int sinGetPVPAccuracy(int MyLevel, int MyAttack_Rating, int DesLevel, int DesDefense);

int sinGetCritical(int desLV);

int sinGetBlockRating(int desLV);

int sinGetAbsorb(int Type = 0);


void sinRegen();
void sinUseStamina();
void sinSetRegen();




void sinLButtonUp();

void sinLButtonDown();

void sinRButtonUp();

int StopCharMotion(int x, int y);

void sinReload();


int sinGetMouseButton(int num);
void sinMouseMain();

int sinGetKeyClick(int num);
void sinKeyClickMain();

void ShowInterFace();

int sinCreatFont();

extern int CheckEditSize(int x, int lx, char *String);




int LoadItemImage(sITEMINFO *sItemInfo, sITEM *TempItem);

int sinUsePotion();

int StopCharMotion(int x, int y);


int sinSetShopItem(sITEMINFO *pItem, int ItemCount, int ItemKind);



void sinTestDrawText();


void sinTestKey();


int sinRequestTrade(DWORD CODE, char *CharName);



int sinSkillMaster(int ChangeJob = 0);

int sinSkillMasterClose();


int ShowParty();


int ShowQuest();




short sinGetLife();
short sinGetMana();
short sinGetStamina();

void sinSetLife(short Life);
void sinSetMana(short Mana);
void sinSetStamina(short Stamina);


int sinCheckAgingLevel(int Kind, bool bBillingUse);




int sinSetQuestItem(sITEMINFO *sItemInfo);
extern int ChangeJobButonCheck2;


int sinMinusMoney(int Money, int Kind = 0);
int sinPlusMoney(int Money);

int sinMinusMoney2(int Money);
int sinPlusMoney2(int Money);

int sinGetElement(smCHAR *pChar);



int sinRecvAgingIncreStateItem(sITEMINFO *pItem);
int sinSetAgingItemIncreState(sITEMINFO *pItem);
int sinAgingItemInit(sITEMINFO *pItem, int Down);


int sinSetDurabilityAging(sITEMINFO *pItem);
int sinSetDamageAging(sITEMINFO *pItem);
int sinSetDefenseAging(sITEMINFO *pItem, int Percent);
int sinSetAttackRateAging(sITEMINFO *pItem, int AddNum);
int sinSetAbsorbAging(sITEMINFO *pItem, float Percent);
int sinSetCriticalAging(sITEMINFO *pItem);
int sinSetBlockRateAging(sITEMINFO *pItem);



int sinDownDurabilityAging(sITEMINFO *pItem);
int sinDownDamageAging(sITEMINFO *pItem, int Level = 0);
int sinDownDefenseAging(sITEMINFO *pItem, int Percent);
int sinDownAttackRateAging(sITEMINFO *pItem, int AddNum);
int sinDownAbsorbAging(sITEMINFO *pItem, float Percent, int Level = 0);
int sinDownCriticalAging(sITEMINFO *pItem);
int sinDownBlockRateAging(sITEMINFO *pItem);



int sinCheckAgingItemHack(sITEM *pItem);



DWORD sinWingItemQuestServer(sCRAFTITEM_SERVER *pWingItem, smCHAR_INFO *pChar_Info);
int SendWingQuestItem();
int RecvWingItem(sCRAFTITEM_SERVER *pWingItem);
int AgingRing();


int sinSetSpecialItemCode(sITEMINFO *pItemInfo);


int NumLineComa(int Num, char *pBuff);


int sinSaveGame(DWORD CODE, int Count);


int OverDay_Item_Delete(sITEM *pItem);


int sinCloseInterFace();


int sinCheck_ShowHelpMap();


int sinRecvForceOrb(sITEMINFO *pItemInfo, int Count);


int sinDoubleClick();


extern int ReformItem(sITEMINFO *lpItemInfo);
extern int CheckItemForm(sITEMINFO *lpItemInfo);

extern int ReformCharForm();
extern int CheckCharForm();

extern int sinSetCharItem(DWORD CODE, DWORD Posi, BOOL SetFlag);

extern int sinThrowItemToFeild(sITEM *pItem);

extern int sinActionPotion();

extern int CompareItems(sITEMINFO *lpItemInfo1, sITEMINFO *lpItemInfo2);




extern HFONT sinFont;
extern HFONT sinMessageFont;
extern HFONT sinBoldFont;

extern int sinTestFlag;
extern int MouseButtonUpEvent;

extern int CursorClass;

extern int Accuracy_Table[][2];

extern int sinSecretFlag;


extern int ItemIndex1[3];
extern int ItemIndex2[3];

extern int ItemImageNotExitFlag;

extern int OverDay_Item_Flag;

extern int SummonSkillCodeIndex[10];

extern int haSiegeBoardTempFlag;

#endif
