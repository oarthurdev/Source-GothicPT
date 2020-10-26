
#ifndef	_SINITEM_HEADER_

#define _SINITEM_HEADER_

#include "smLib3d\\smDsx.h"

#define MAX_ITEM 4200


#define ITEMSIZE					22   

#define CHECK_COPY_ITEM				1
#define CHECK_GIVE_ITEM				2


#define INVENTORY_POS_BOX			    0x00000001  
#define INVENTORY_POS_LHAND				0x00000002 
#define INVENTORY_POS_RHAND				0x00000004 
#define INVENTORY_POS_ARMOR				0x00000008 
#define INVENTORY_POS_BOOTS				0x00000010 
#define INVENTORY_POS_GLOVES			0x00000020 
#define INVENTORY_POS_LRING				0x00000040 
#define INVENTORY_POS_RRING				0x00000080 
#define INVENTORY_POS_SHELTOM			0x00000100 
#define INVENTORY_POS_AMULET			0x00000200 
#define INVENTORY_POS_ARMLET			0x00000800
#define INVENTORY_POS_TWO_HAND			0x00001000
#define INVENTORY_POS_POTION			0x00002000
#define INVENTORY_POS_COSTUME			0x00004000
#define INVENTORY_POS_EARRINGSL			0x00008000
#define INVENTORY_POS_EARRINGSR			0x00010000




#define ITEM_CLASS_WEAPON_ONE			INVENTORY_POS_RHAND 
#define ITEM_CLASS_WEAPON_TWO			(INVENTORY_POS_RHAND |INVENTORY_POS_LHAND) 
#define ITEM_CLASS_ARMOR				INVENTORY_POS_ARMOR 
#define ITEM_CLASS_BOOTS				INVENTORY_POS_BOOTS 
#define ITEM_CLASS_GLOVES				INVENTORY_POS_GLOVES 
#define ITEM_CLASS_SHIELDS				INVENTORY_POS_LHAND
#define ITEM_CLASS_RING					(INVENTORY_POS_LRING | INVENTORY_POS_RRING)
#define ITEM_CLASS_SHELTOM				INVENTORY_POS_SHELTOM 
#define ITEM_CLASS_AMULET				INVENTORY_POS_AMULET 
#define ITEM_CLASS_ARMLET				INVENTORY_POS_ARMLET 
#define ITEM_CLASS_MAGICIAL_STUFFS		INVENTORY_POS_LHAND
#define ITEM_CLASS_POTION				INVENTORY_POS_POTION
#define ITEM_CLASS_COSTUME              INVENTORY_POS_COSTUME
#define ITEM_CLASS_ECORE				INVENTORY_POS_BOX
#define ITEM_CLASS_QUEST				INVENTORY_POS_BOX
#define ITEM_CLASS_FORCEORB				INVENTORY_POS_BOX
#define ITEM_CLASS_SEEL					INVENTORY_POS_BOX
#define ITEM_CLASS_EARRRINGS			(INVENTORY_POS_EARRINGSL|INVENTORY_POS_EARRINGSR)


#define ITEM_WEAPONCLASS_NOT_SHOOTING	1 
#define ITEM_WEAPONCLASS_SHOOTING		2 
#define ITEM_WEAPONCLASS_CASTING		3 



#define sinWA1			0x01010000	
#define sinWC1			0x01020000	
#define sinWH1			0x01030000	
#define sinWM1			0x01040000	
#define sinWP1			0x01050000	
#define sinWS1			0x01060000	
#define sinWS2			0x01070000	
#define sinWT1			0x01080000	
#define sinWN1			0x01090000	
#define sinWD1			0x010A0000


#define sinDA1			0x02010000	
#define sinDA3			0x02120000
#define sinDB1			0x02020000	
#define sinDG1			0x02030000	
#define sinDS1			0x02040000	
#define sinDA2			0x02050000
#define sinDA4			0x02130000
#define sinCA1			0x02100000  
#define sinCA2			0x02200000	



#define sinOA1			0x03010000	
#define sinOA2			0x03020000	
#define sinOM1			0x03030000	
#define sinOR1			0x03040000	
#define sinOR2			0x03050000	
#define sinOS1			0x02350000	
#define sinFO1			0x03060000  
#define sinSE1			0x03070000  
#define sinPR1			0x03080000  
#define sinPR2			0x03090000  
#define sinPR3			0x03100000  
#define sinPR4			0x03110000  
#define sinOE1			0x030A0000

#define sinPM1			0x04010000  
#define sinPL1			0x04020000  
#define sinPS1			0x04030000  


#define sinGG1			0x05010000 
#define sinGB1			0x05020000 


#define sinEC1			0x06010000



#define sinQT1			0x07010000



#define sinSP1			0x08010000 
#define sinGP1			0x08020000		
#define sinQW1			0x08030000		
#define sinGF1			0x08040000		
#define sinPZ1			0x08060000		
#define sinPZ2			0x08070000		
#define sinCH1			0x08080000		
#define sinSD2			0x08090000		
#define sinBC1          0x080A0000      
#define sinBI1          0x080B0000      
#define sinBI2          0x080C0000      
#define sinGP2			0x080D0000		



#define sinMA1			0x09010000 
#define sinMA2			0x09020000




#define sinWR1			0x0A010000 
#define sinDR1			0x0A020000 

#define EXTREME_RECIPE		1		
#define ANCIENT_RECIPE		2		
#define	MINOTAUR_RECIPE		3		
#define DOOM_RECIPE			4		
#define SALAMANDER_RECIPE	5		
#define WYVERN_RECIPE		6		
#define PHOENIX_RECIPE		7		
#define FRENZY_RECIPE		8		
#define HEAVENS_RECIPE		9		
#define SNOW_RECIPE			10		
#define MEMORY_RECIPE		11		


#define sin00			0x00000000	
#define sin01			0x00000100	
#define sin02			0x00000200
#define sin03			0x00000300
#define sin04			0x00000400
#define sin05			0x00000500
#define sin06			0x00000600
#define sin07			0x00000700
#define sin08			0x00000800
#define sin09			0x00000900
#define sin10			0x00000A00
#define sin11			0x00000B00
#define sin12			0x00000C00
#define sin13			0x00000D00
#define sin14			0x00000E00
#define sin15			0x00000F00
#define sin16			0x00001000
#define sin17			0x00001100
#define sin18			0x00001200
#define sin19			0x00001300
#define sin20			0x00001400
#define sin21			0x00001500
#define sin22			0x00001600
#define sin23			0x00001700
#define sin24			0x00001800
#define sin25			0x00001900 
#define sin26			0x00002A00
#define sin27			0x00002B00
#define sin28			0x00002C00
#define sin29			0x00002D00
#define sin30			0x00002E00
#define sin31			0x00002F00
#define sin32			0x00003000
#define sin33			0x00003100
#define sin34			0x00003200
#define sin35			0x00003300
#define sin36			0x00003400
#define sin37			0x00003500
#define sin38			0x00003600
#define sin39			0x00003700
#define sin40			0x00003800
#define sin41			0x00003900
#define sin42			0x00003A00
#define sin43			0x00003B00
#define sin44			0x00003C00
#define sin45			0x00003D00
#define sin46			0x00003E00
#define sin47			0x00003F00
#define sin48			0x00004000	
#define sin49			0x00004100	
#define sin50			0x00004200	
#define sin51			0x00004300	
#define sin52			0x00004400
#define sin53			0x00004500
#define sin54			0x00004600
#define sin55			0x00004700
#define sin56			0x00004800
#define sin57			0x00004900
#define sin58			0x00004A00
#define sin59			0x00004B00
#define sin60			0x00004C00  
#define sin61			0x00004D00  
#define sin62			0x00004E00
#define sin63			0x00004F00
#define sin64			0x00005000
#define sin65			0x00005100
#define sin66			0x00005200
#define sin67			0x00005300
#define sin68			0x00005400
#define sin69			0x00005500
#define sin70			0x00005600
#define sin71			0x00005700
#define sin72			0x00005800
#define sin73			0x00005900 
#define sin74			0x00005A00 
#define sin75			0x00005B00 
#define sin76			0x00005C00 
#define sin77			0x00005D00 
#define sin78			0x00005E00 
#define sin79			0x00005F00 
#define sin80			0x00006000 
#define sin81			0x00006100 
#define sin82			0x00006200 
#define sin83			0x00006300 
#define sin84			0x00006400 
#define sin85			0x00006500
#define sin86			0x00006600 
#define sin87			0x00006700 
#define sin88			0x00006800 
#define sin89			0x00006900 
#define sin90			0x00006A00 
#define sin91			0x00006B00 
#define sin92			0x00006C00 
#define sin93			0x00006D00 
#define sin94			0x00006E00 
#define sin95			0x00006F00 
#define sin96			0x00007000 
#define sin97			0x00007100 
#define sin98			0x00007200 




#define		SIN_SOUND_AXES				1
#define		SIN_SOUND_CLAWS				2
#define		SIN_SOUND_HAMMER			3
#define		SIN_SOUND_MAGICIAL		 	4
#define		SIN_SOUND_POLES				5
#define		SIN_SOUND_SHOOTERS			6
#define		SIN_SOUND_SWORDS			7
#define		SIN_SOUND_THROWING			8
#define		SIN_SOUND_ARMOR				9
#define		SIN_SOUND_BOOTS				10
#define		SIN_SOUND_GLOVES			11
#define		SIN_SOUND_SHIELDS			12
#define		SIN_SOUND_AMULET			13
#define		SIN_SOUND_Armlet			14
#define		SIN_SOUND_RING				15
#define     SIN_SOUND_SHELTOM			16
#define     SIN_SOUND_POTION			17
#define     SIN_SOUND_COIN				18
#define     SIN_SOUND_STAFF				19
#define		SIN_SOUND_EAT_POTION		20
#define		SIN_SOUND_SHOW_INTER		21
#define		SIN_SOUND_REPAIR_ITEM		22
#define		SIN_SOUND_FAILD_MIXITEM		23
#define		SIN_SOUND_ARMOR2			24
#define		SIN_SOUND_EAT_POTION2		25



#define   sITEMINFO_BIONIC			0	
#define   sITEMINFO_EARTH			1	
#define   sITEMINFO_FIRE			2	
#define	  sITEMINFO_ICE				3	
#define   sITEMINFO_LIGHTING		4	
#define   sITEMINFO_POISON			5	
#define   sITEMINFO_WATER			6	
#define   sITEMINFO_WIND			7	
#define	  sITEMINFO_NONE			15	


#define ITEM_KIND_NORMAL			0   
#define ITEM_KIND_CRAFT				1   
#define ITEM_KIND_AGING				2   
#define ITEM_KIND_QUEST				3	
#define ITEM_KIND_EVENT				4	
#define ITEM_KIND_MAKE_MAIN			5	
#define ITEM_KIND_MAKE_ELEMENT		6	
#define ITEM_KIND_QUEST_WEAPON		7	
#define ITEM_KIND_SPECIAL			8	


#define   SIN_ADD_FIRE				0x00000001	
#define   SIN_ADD_ICE				0x00000002	
#define   SIN_ADD_LIGHTNING			0x00000004	
#define   SIN_ADD_POISON			0x00000008	
#define   SIN_ADD_BIO				0x00000010	
#define   SIN_ADD_CRITICAL			0x00000020	
#define   SIN_ADD_ATTACK_RATE		0x00000040	
#define   SIN_ADD_DAMAGE_MIN		0x00000080	
#define   SIN_ADD_DAMAGE_MAX		0x00000100	
#define   SIN_ADD_ATTACK_SPEED		0x00000200	
#define   SIN_ADD_ABSORB			0x00000400	
#define   SIN_ADD_DEFENCE			0x00000800	
#define   SIN_ADD_BLOCK_RATE		0x00001000	
#define   SIN_ADD_MOVE_SPEED		0x00002000	
#define   SIN_ADD_LIFE				0x00004000	
#define   SIN_ADD_MANA				0x00008000	
#define   SIN_ADD_STAMINA			0x00010000	
#define   SIN_ADD_LIFEREGEN			0x00020000  
#define   SIN_ADD_MANAREGEN			0x00040000  
#define   SIN_ADD_STAMINAREGEN		0x00080000  



struct	sITEM_CREATE
{
	DWORD	Head;
	DWORD	dwVersion;
	DWORD	dwTime;
	DWORD	dwChkSum;
};

struct sITEM_SPECIAL
{

	float	Add_fAbsorb;
	int     Add_Defence;
	float   Add_fSpeed;
	float   Add_fBlock_Rating;
	int     Add_Attack_Speed;
	int     Add_Critical_Hit;
	int     Add_Shooting_Range;
	float   Add_fMagic_Mastery;
	short	Add_Resistance[8];



	short	Lev_Attack_Resistance[8];
	int		Lev_Mana;
	int		Lev_Life;
	int     Lev_Attack_Rating;
	short	Lev_Damage[2];

	float	Per_Mana_Regen;
	float	Per_Life_Regen;
	float	Per_Stamina_Regen;



	DWORD	dwTemp[32];
};

struct sITEMINFO
{

	DWORD	dwSize;

	sITEM_CREATE	ItemHeader;

	short	Durability[2];




	DWORD	CODE;
	char	ItemName[32];


	int     Weight;
	int     Price;


	int		Index;
	int		PotionCount;



	short	Resistance[8];


	int		Sight;

	DWORD	Temp0;


	short	Damage[2];
	int     Shooting_Range;
	int     Attack_Speed;
	int     Attack_Rating;
	int     Critical_Hit;



	float	fAbsorb;
	int     Defence;
	float   fBlock_Rating;


	float     fSpeed;



	int		Potion_Space;


	float   fMagic_Mastery;
	float   fMana_Regen;
	float   fLife_Regen;
	float   fStamina_Regen;
	float   fIncrease_Life;
	float   fIncrease_Mana;
	float   fIncrease_Stamina;



	int     BattleLevel;
	int     Level;
	int     Strength;
	int     Spirit;
	int     Talent;
	int     Dexterity;
	int     Health;


	short   Mana[2];
	short   Life[2];
	short   Stamina[2];


	int		Money;
	int     NotUseFlag;

	DWORD	BackUpKey;
	DWORD	BackUpChkSum;

	short   ScaleBlink[2];
	DWORD	UniqueItem;
	short	EffectBlink[2];
	short	EffectColor[4];

	DWORD	DispEffect;




	DWORD			JobCodeMask;
	sITEM_SPECIAL	JobItem;

	DWORD   ItemKindCode;
	DWORD   ItemKindMask;

	short   ItemAgingNum[2];
	short   ItemAgingCount[2];
	short   ItemAgingProtect[2];

	short   SpecialItemFlag[2];

	DWORD	dwCreateTime;
	DWORD	dwTemp[9];

};


struct sITEM
{
	DWORD	CODE;
	char	ItemNameIndex[32];


	char	LastCategory[16];
	int		w;
	int     h;
	char	ItemFilePath[64];
	DWORD	Class;
	char    DorpItem[64];
	DWORD   SetModelPosi;
	int		SoundIndex;
	int     WeaponClass;




	int Flag;
	int x, y;
	int SetX, SetY;

	DIRECTDRAWSURFACE lpItem;
	int		ItemPosition;

	int     PotionCount;
	int     NotUseFlag;
	int     SellPrice;

	int     OldX, OldY;
	DIRECTDRAWSURFACE	lpTempItem;


	sITEMINFO sItemInfo;

	sITEM()
	{
		CODE = 0;
		ZeroMemory(ItemNameIndex, sizeof(ItemNameIndex));
		ZeroMemory(LastCategory, sizeof(LastCategory));
		w = 0;
		h = 0;
		ZeroMemory(ItemFilePath, sizeof(ItemFilePath));
		Class = 0;
		ZeroMemory(DorpItem, sizeof(DorpItem));
		SetModelPosi = 0;
		SoundIndex = 0;
		WeaponClass = 0;
		Flag = 0;
		x = 0;
		y = 0;
		SetX = 0;
		SetY = 0;

		lpItem = NULL;
		ItemPosition = 0;

		PotionCount = 0;
		NotUseFlag = 0;
		SellPrice = 0;

		OldX = 0;
		OldY = 0;
		lpTempItem = NULL;

	}
	sITEM(DWORD CODE, const char* ItemNameIndex, const char* LastCategory, int w, int h, const char* ItemFilePath, int Class,
		  const char* DorpItem, DWORD SetModelPosi, int SoundIndex, int WeaponClass = 0)
	{
		this->CODE = CODE;
		strcpy_s(this->ItemNameIndex, sizeof(this->ItemNameIndex), ItemNameIndex);
		strcpy_s(this->LastCategory, sizeof(this->LastCategory), LastCategory);
		this->w = w;
		this->h = h;
		strcpy_s(this->ItemFilePath, sizeof(this->ItemFilePath), ItemFilePath);
		this->Class = Class;
		strcpy_s(this->DorpItem, sizeof(this->DorpItem), DorpItem);
		this->SetModelPosi = SetModelPosi;
		this->SoundIndex = SoundIndex;
		this->WeaponClass = WeaponClass;
		this->Flag = 0;
		this->x = 0;
		this->y = 0;
		this->SetX = 0;
		this->SetY = 0;

		this->lpItem = NULL;
		this->ItemPosition = 0;

		this->PotionCount = 0;
		this->NotUseFlag = 0;
		this->SellPrice = 0;

		this->OldX = 0;
		this->OldY = 0;
		this->lpTempItem = NULL;

	}

};

struct sITEMPRICE
{
	int PureSellPrice;
	int SellPrice;
	int RepairCost;
};


struct sITEMREQUIRE
{
	int     rLevel;
	int     rStrength;
	int     rSpirit;
	int     rTalent;
	int     rDexterity;
	int     rHealth;
};


class cITEM
{
public:
	char *DropItemPath;
	char *CharSetItemPath;

	int MatItemInfoBox;

	int MatItemInfoBox_TopLeft;
	int MatItemInfoBox_TopRight;
	int MatItemInfoBox_TopCenter;

	int MatItemInfoBox_BottomLeft;
	int MatItemInfoBox_BottomRight;
	int MatItemInfoBox_BottomCenter;

	int MatItemInfoBox_Left;
	int MatItemInfoBox_Right;
	int MatItemInfoBox_Center;


	DIRECTDRAWSURFACE	AgingBar;
	DIRECTDRAWSURFACE	AgingGage;
	DIRECTDRAWSURFACE	AgingBar2;

public:
	cITEM();
	~cITEM();

	void Init();
	void Load();
	void Release();
	void Close();
	void Draw();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();

	int ShowItemInfo(sITEM *pItem, int Flag, int Index = 0);

	int ShowItemInfo2(sITEM *pItem, int Flag, int Index = 0);

	int DrawItemText();

	POINT SetTextXY(int x, int y, int len);

	int SearchSpecialItemJob(DWORD SpecialJob_CODE);

	int GetInfoBoxSize(sITEM *pItem, int Col);


	int CheckItemTable();


	int GetItemLimitTime(sITEM *pItem);


	void GetMousePos(int *MouseX, int *MouseY);


	void SetItemInfo(char *Buff);
};

extern cITEM cItem;
extern sITEM sItem[MAX_ITEM];

extern sITEM TempItem;
extern sITEM MouseItem;

extern int sinShowItemInfoFlag;
extern DWORD sinItemTime;

extern int NotSell_Item_CODECnt;
extern int NotSell_Item_MASKCnt;
extern int NotSell_Item_KINDCnt;

extern int NotDrow_Item_CODECnt;
extern int NotDrow_Item_MASKCnt;
extern int NotDrow_Item_KINDCnt;

extern int NotSet_Item_CODECnt;
extern int NotSet_Item_MASKCnt;
extern int NotSet_Item_KINDCnt;

extern DWORD NotSell_Item_CODE[];
extern DWORD NotSell_Item_MASK[];
extern DWORD NotSell_Item_KIND[];

extern DWORD NotDrow_Item_CODE[];
extern DWORD NotDrow_Item_MASK[];
extern DWORD NotDrow_Item_KIND[];

extern DWORD NotSet_Item_CODE[];
extern DWORD NotSet_Item_MASK[];
extern DWORD NotSet_Item_KIND[];







#endif