#pragma once

#include "sinMessageBox.h"

#define INVENTORY_MAXITEM		100 
#define INVENTORY_BOX_SIZE		22  
#define INVENTORY_BOX_COL		6   
#define INVENTORY_BOX_ROW		12  

#define INVENTORY_MAX_POS		16   
#define MAX_WINGQUEST			10  


#define		NO_BOX_COLOR				0
#define		SET_ITEM_CHECK_COLOR		1
#define		OVERLAP_ITEM_COLOR			2
#define		NOT_SETTING_COLOR			3
#define		OVERLAP_BOX_COLOR           4
#define		SELECT_ITEM_COLOR			5
#define     NOT_USE_COLOR				6
#define		NOT_AGING_ITEM				7
#define     NOT_ENOUGH_MONEY			8	


#define     MAX_USESKILL                17 

struct sINVENTORY
{
	DWORD  Position;
	RECT   Rect;
	int    ItemIndex;
	int    WeaponClass;

};

#define		MAX_INVEN_PARTICLE		200

#define		SIN_EFFECT_SHOW_INVEN		1
#define		SIN_EFFECT_SHOW_WAREHOUSE	2
#define		SIN_EFFECT_SHOW_TRADE		3
#define		SIN_EFFECT_SHOW_GYUNGFUM	10





struct sELEMENT_ATTACK
{
	int Bio[2];
	int Fire[2];
	int Ice[2];
	int Lighting[2];
	int Posion[2];
};


struct sINVENTORY_EFFECT
{
	smFACE2D InvenFace;
	int Time;
	int Max_Time;
	POINT Speed;
	int Direction;
	int AniCount;
	int FadeType;
	int Kind;
	int Flag;
	POINT DesPosi;
	POINT Posi;

};


struct sUNIONCORE_EFFECT
{
	int Flag;
	int Time;
	int Max_Time;
	int MatNum;
	int x;
	int y;
	int Alpha;
	int w;
	int h;

};

struct sWINGQUEST
{
	DWORD NeedItemCode[6];
	int   Money;
	DWORD ChangeItemCode;

};

class cINVENTORY
{

public:

	int OpenFlag;
	int CostumeFlag;
	int CostumeChangeFlag;
	unsigned int CostumeTimer;

	sITEM InvenItem[INVENTORY_MAXITEM];

	sITEM InvenItemTemp[INVENTORY_MAXITEM];
	sITEM BackUpInvenItemTemp[INVENTORY_MAXITEM];


	char JobName[32];

	LPDIRECT3DTEXTURE9	lpInvenArrow[2];
	LPDIRECT3DTEXTURE9	lpCoverSmall;
	LPDIRECT3DTEXTURE9	lpCoverMiddle;
	LPDIRECT3DTEXTURE9	lpCoverLarge;
	LPDIRECT3DTEXTURE9	lpMyShopIcon;
	LPDIRECT3DTEXTURE9	lpMyShopIcon_T;



	LPDIRECT3DTEXTURE9	lpPotionBack;
	LPDIRECT3DTEXTURE9	lpChangeABInfo[2];
	LPDIRECT3DTEXTURE9	lpExitInfo;
	LPDIRECT3DTEXTURE9	lpWeightInfo;
	LPDIRECT3DTEXTURE9	lpItemABInfo[2];

	LPDIRECT3DTEXTURE9	lpShowWeaponClass[4];

	LPDIRECT3DTEXTURE9	lpIndiShopIcon;


	LPDIRECT3DTEXTURE9   lpPuzzleInven;
	LPDIRECT3DTEXTURE9   lpPuzzlewidth;
	LPDIRECT3DTEXTURE9   lpPuzzleHeight;




	int MatInven[4];
	int MatInvenParticle[5];

	DWORD InvenDataCheckSum;


	int ViewDamagePercent;
	int ViewDamageNum;


	int iEventBuyItemKind;

public:
	cINVENTORY();
	~cINVENTORY();

	void Init();
	void Load();
	void Release();
	void Draw();
	void Close();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();

	bool setCostumer()
	{
		if(GetTickCount() - CostumeTimer < 0)
		{
			extern cMESSAGEBOX cMessageBox;
			cMessageBox.ShowMessageEvent("Aguarde 5 segundos para poder equipar o traje novamente!");
			return false;
		}
		else
		{
			CostumeFlag = !CostumeFlag;
			CostumeChangeFlag = TRUE;
			CostumeTimer = GetTickCount();

			return true;
		}
	}


	int LoadItemInfo();
	int AutoSetInvenItem(sITEM *pItem, int PostBox = 0);

	int InvenEmptyAearCheck(sITEM *pItem);

	int SetItemToChar(int CheckHackFlag = 0);
	int LastSetInvenItem(sITEM *pItem, int AutoSet = 0);

	int PickUpInvenItem(int x, int y, int PickUpFlag = 0);

	int ChangeInvenItem(sITEM *pItem);

	int CrashInvenItem(RECT &desRect, int PassItemIndex = 0);



	void InvenItemLoad();
	void InvenItemRelease();



	int CheckRequireItem();
	void CheckWeight();
	int CheckRequireItemToSet(sITEM *pItem);

	int InvenNotOpenCheck(sITEM *pItem);



	int SetTwoHandItem(sITEM *pItem);
	int PickUpTwoHandItem(sITEM *pItem);
	int OverlapTwoHandItem(sITEM *pItem);
	int OverlapTwoHandSwitch(sITEM *pItem);
	int ClearTwoHandPosiAndItem(sITEM *pItem);



	int AutoSetPotion(sITEM *pItem);
	int MouseSetPotion(sITEM *pItem);
	int AutoSetPotionToBox(sITEM *pItem);
	int cINVENTORY::ReSettingPotion();
	int UsePotion(int x, int y);
	int CheckOverlapItem(sITEM *pItem, int PassItemIndex);


	int SearchJobAndSetting();
	void LoadCharState();


	int ChangeABItem(int Posi);
	int ChangeACItem(bool Costume);


	int DrawInvenText();

	int SetInvenItemAreaCheck(sITEM *pItem);
	int InitColorRect();
	int CheckInvenPos(int x, int y, int lx, int ly, RECT &rect);



	int ThrowInvenItemToField(sITEM *pItem);
	int NoSettingThrowItem(sITEM *pItem, int Flag = 0);


	sITEMPRICE GetInvenItemPrice(sITEM *pItem);
	int RepairInvenItem(sITEM *pItem, int RepairCost);

	int CheckSetOk(sITEM *pItem, int AutoFlag = 0);


	int CopyItemClear(sITEM *pItem);
	POINT CheckImageSize(LPDIRECT3DTEXTURE9 lpdd);
	int ImsiCheckItemImageSize();


	int ReSetPotionXY(sITEM *pItem, int kind = 0);


	int UseEcore(sITEM *pItem);


	int ResetMouseItem();


	int CheckInvenItemForm();
	int ReFormInvenItem();


	int CheckMoneyLimit(int Money);


	int CheckPotionNumForm();
	int ReFormPotionNum();


	int CheckSpecialItem(sITEM *pItem);


	int ShowInvenEffectParticle();
	int SetInvenParticle(int x, int y, int Kind);
	int sinDrawInvenTexImage(smFACE2D *Face);
	int MoveInvenParticle();



	int CheckSetEmptyArea(sITEM *pItem);


	int ResetInvenItemToServer(DWORD CODE, DWORD Head, DWORD CheckSum, DWORD Time);
	int DeleteInvenItemToServer(DWORD CODE, DWORD Head, DWORD CheckSum);



	int EatSongPyeun(sITEM *pItem);



	int CharOnlySetItem(sITEM *pItem);


	int HackCharStateCheck(smCHAR_INFO *pChar_Info, smCHAR_INFO *desChar_Info);


	int CheckResetInvenItem();


	int SearchItemCode(DWORD CODE, int KindFlag = 0);


	int CheckDamage();


	int ClearQuestItem();


	int RecvLinkCore(sITEMINFO *pItem);


	int CheckMousePotionNumForm();


	int ReFormMousePotionNum();


	int SetUnionCoreEffect(int x, int y);
	int UnionCoreParticleProcess();
	int UnionCoreParticle(int x, int y);
	int UnionCoreParticle2(int x, int y, int Flag = 0);


	int CheckInvenEmpty(sITEM *pItem);


	int SetInvenToItemInfo(sITEMINFO *pItemInfo);


	int LoadMoneyExpImage(sITEM *pItem);


	int sinWingQuestNpc();

	int SendWingQuestItem(int Index);


	int CheckRequireItemToSet2(sITEM *pItem);


	int SetSpecialItem(sITEM *pItem);


	int ChangeSpecialItem(int Flag = 0);


	int CheckSpecialItemPosi();


	int SearchItemIndex(DWORD CODE, int KindFlag);


	int ChangePuzzle(sITEM *pItem);


	int CheckPuzzle();


	int CheckSendPuzzle();


	int SendPuzzleNpc();


	int IncreViewDamage(int Persent, int Num = 0);


	int SendEventItem();


	int CheckEventItem();


	int DrawForceOrbEffect(int x, int y);


	int UseForceOrb(sITEM *pItem, int Flag = 0);


	int UseMagicForceOrb(sITEM *pItem, int Flag = 0);


	int UseBillingMagicForceOrb(sITEM *pItem, int Flag = 0);


	int SetForceOrb(DWORD ItemCODE, int Time);


	int SetMagicForceOrb(DWORD ItemCODE, int Time);


	int SetBillingMagicForceOrb(DWORD ItemCODE, int Time);


	int UseCapsuleItem(sITEM *pItem);





	int CheckFoxEventItem();

	int SendFoxEventItem();

	int CheckChristMasEventItem();

	int SendChristmasEventItem();

	int ReSetQuestItemPosi();

	int CheckCristalEventItem();

	int SendCristalEventItem();


	int CheckWatermelonEventItem();

	int SendWatermelonEventItem();

	int CheckItemCount(DWORD CODE);


	int CheckValentineEventItem();

	int SendValentineEventItem();

	int CheckValentineItemCount(DWORD CODE);


	int CheckPristonAlphabetEventItem();

	int SendPristonAlphabetEventItem();


	int CheckCandydaysEventItem();

	int SendCandydaysEventItem();

	int CheckCandyItemCount(DWORD CODE);


	int CheckMagicalGreenEventItem();

	int SendMagicalGreenEventItem();
	int SendMagicalGreenEmeraldEventItem();

	int CheckMagicalGreenItemCount(DWORD CODE);
	int CheckMagicalGreenItemEmeraldCount(DWORD CODE);


	int CheckTearOfKaraEventItem();

	int SendTearOfKaraEventItem();

	int CheckTearOfKaraItemCount(DWORD CODE);


	int UseSoccerBallPotionItem(sITEM *pItem);


	int CheckFindinvestigatorEventItem();
	int CheckFindinvestigatorKamiuEventItem();
	int CheckFindinvestigatorEtoEventItem();
	int SendFindinvestigatorNineEventItem();
	int SendFindinvestigatorTaleEventItem();
	int SendFindinvestigatorTaleEtoEventItem();
	int CheckFindinvestigatorNineItemCount(DWORD CODE);
	int CheckFindinvestigatorTaleItemCount(DWORD CODE);




	int DeleteCoupleRing();


	char szDoc[128];
	char szSendDoc[128];


};

extern cINVENTORY	cInvenTory;

extern sINVENTORY sInven[INVENTORY_MAX_POS];

extern DWORD sinInvenColor[7];

extern sITEM *pUsePotion;

extern int sinLoadOK;

extern int LbuttonUpCheckFlag;

extern int sinChangeSetFlag;

extern int SelectInvenItemIndex;

extern int CrashItemIndex[2];

extern int 	AutoSetItemIndex;

extern int SelectPotionIndex;

extern int ArrowState[2];

extern int InvenArrowPosi;

extern int sinButtonFlag;

extern sINVENTORY_EFFECT	sInven_Effect[MAX_INVEN_PARTICLE];

extern int ArrowState[2];

extern int InvenArrowPosi;

extern int sinUndeadAbsorb;

extern float   sinAdd_fMagic_Mastery;
extern int	   sinInterHeight2;

extern sELEMENT_ATTACK	sElement_Attack;
extern int sinTempDamage2[2];
extern int sinTempAbsorb;
extern int sinTempBlock;

extern int SendCheckItemToServer(sITEMINFO *lpItem);

extern sITEMINFO TempLinkCoreItem;

extern POINT UnionCorePosi;

extern LPDIRECT3DTEXTURE9   lpGold7;
extern LPDIRECT3DTEXTURE9   lpExp7;

extern sWINGQUEST sWingQuest[MAX_WINGQUEST];
extern int   sinOverWeightCnt;

extern int SpecialItemShowFlag;
extern sITEM MyShopMouseItem;
extern int sinMyShopItemPass;
extern int NotChangeSetItemFlag;
extern int MatInterEffectAging[5];
extern int MatInterEffectAging2[4];
extern int MatSuccessEffectAging;
extern int ForceOrbUseTime[];
extern int ForceOrbDamage[];
extern int MagicForceOrbDamage[];
extern int BillingMagicForceOrbDamage[];
extern int MagicForceOrbUseTime[];
extern int BillingMagicForceOrbUseTime[];
extern int ForceOrbUseLevel[][2];
extern int MagicForceOrbUseLevel[][2];
extern int BillingMagicForceOrbUseLevel[][2];

extern int BoosterItem_UseTime[];
extern int BoosterItem_DataPercent[];

extern int nSkillDelay_UseTime[];


extern int nName;


extern DWORD CristalEventCODE[12];


extern DWORD WatermelonEventCODE;


extern DWORD ValentineEventCODE;


extern DWORD PristonAlphabetEventCODE[7];


extern DWORD CandydaysEventCODE;


extern DWORD MagicalGreenEventCODE[2];


extern DWORD TeatOfKaraEventCODE;


extern DWORD FindinvestigatorEventCODE[2];


extern DWORD dwCastlItemCODE[];
extern DWORD dwPremiumItemCode[];


extern DWORD dwBoosterItemCode[];


extern DWORD dwSkillDelayItemCode[];
