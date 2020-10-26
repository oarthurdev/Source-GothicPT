
#define MAX_TRADE_ITEM			20
#define MAX_CRAFTITEM_INFO		300
#define MAX_AGINGITEM_INFO		100
#define MAX_MAKEITEM_INFO		100

#define T_SET_BOX				0
#define T_MONEY_POSI			1
#define T_MONEY_TEXT_POSI		2
#define T_WEIGHT_TEXT_POSI		3
#define T_CHECK_POSI			4
#define T_CLOSE_POSI			5

#define MAX_SHELTOM				15	
#define MAX_AGING				20	
#define MAX_RUNE				15
#define MAX_RECIPE_KIND			5
#define MAX_RECIPE_ITEM			60	
#define MAX_HANDMADEITEM		40

#define MAX_SEEL_COUNT			14


struct sTRADE
{
	sITEM TradeItem[MAX_TRADE_ITEM];
	int Money;
	int Coin;
	int Weight;
	int CheckFlag;
	int CheckMoney;
};


struct sWAREHOUSE
{
	sITEM WareHouseItem[100];
	int Money;
	short Weight[2];
	int BuyAreaCount;
	int FakeMoney;


};


struct sCRAFTITEM
{
	sITEM CraftItem[15];
	int   SheltomIndex[12];

};


struct sCRAFTITEM_SERVER
{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesCraftItem;
	DWORD SheltomCode[12];
	DWORD Head[12];
	DWORD CheckSum[12];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};


struct sCRAFTITEM_INFO
{
	DWORD MainItemCode[10];
	int AddItem[14];
	int PlusElementCode[8];
	float AddElement[8];
	int ElementKind[8];
	char Doc[256];

};


struct sMIXTURE_RESET_ITEM
{
	sITEM MixtureResetItem[2];

	sMIXTURE_RESET_ITEM()
	{
		ZeroMemory(&MixtureResetItem, sizeof(MixtureResetItem));
	}
};


struct sMIXTURE_RESET_ITEM_SERVER
{
	int		size, code;
	int		DocIndex;
	int		Result;
	int		Index;

	sITEM	DesMixtureResetItem;

	DWORD	dwMixtureResetStoneItemCode;
	DWORD	dwMixtureResetStoneHead;
	DWORD	dwMixtureResetStoneCheckSum;

	sMIXTURE_RESET_ITEM_SERVER()
	{
		size = 0;
		code = 0;
		DocIndex = 0;
		Result = 0;
		Index = 0;

		dwMixtureResetStoneItemCode = 0;
		dwMixtureResetStoneHead = 0;
		dwMixtureResetStoneCheckSum = 0;
	}
};


struct sAGINGITEM
{
	sITEM AgingItem[15];

	sAGINGITEM()
	{
		ZeroMemory(&AgingItem, sizeof(AgingItem));
	}

};

struct sAGINGITEM_INFO
{
	DWORD MainItemCode;
	int PlusElementCode[8];
	float AddElement[8];
	int ElementKind[8];
	char Doc[128];

	sAGINGITEM_INFO()
	{
		MainItemCode = 0;
		ZeroMemory(&PlusElementCode, sizeof(PlusElementCode));
		ZeroMemory(&AddElement, sizeof(AddElement));
		ZeroMemory(&ElementKind, sizeof(ElementKind));
		ZeroMemory(Doc, sizeof(Doc));
	}
};


struct sMAKEITEM_INFO
{
	DWORD CODE[15];
	DWORD Result_CODE;
};

struct sPOSTBOX_ITEM
{
	char	szName[64];
	DWORD	CODE;


	sPOSTBOX_ITEM()
	{
		ZeroMemory(szName, sizeof(szName));
		CODE = 0;
	}
};


struct sRECON_ITEM
{
	DWORD  dwCODE;
	int	   iLevel[2];
	int	   iCount;
	int    iPrice;
};


struct SSmeltingItem
{
	sITEM SmeltingItem[5];
	int   SheltomIndex[12];
};


struct sSMELTINGITEM_SERVER
{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesSmeltingItem;
	DWORD SmeltingCode[5];
	DWORD Head[5];
	DWORD CheckSum[5];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};


struct SManufactureItem
{
	sITEM	ManufactureItem[4];
	int		RuneIndex[12];
};


struct SManufactureItem_Server
{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesManufactureItem;
	DWORD RuneCode[4];
	DWORD Head[4];
	DWORD CheckSum[4];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};


struct SManufacture_Rune
{
	int RecipeCode;
	int NeedRuneIndex[3];
};


struct SManufacture_CreateItemCode
{
	DWORD RecipeKind[2];
	DWORD CheckRuneCode[8][3];
	DWORD CreateItemCode[2][8];
};


struct SManufacture_ResultItemInfo
{
	DWORD ItemCode;
	int	Weight;
	int Price;
	char ItemName[32];
};


struct SManufacture_ResultItemInfo_Server
{
	smTRANS_COMMAND		smTransCommand;
	DWORD ItemCode[MAX_HANDMADEITEM];
	int Weight[MAX_HANDMADEITEM];
	int Price[MAX_HANDMADEITEM];
	char ItemName[MAX_HANDMADEITEM][32];
};

class cAGING
{
public:

	int OpenFlag;
	int AgingItemCheckSum;
	DIRECTDRAWSURFACE	lpGraySheltom[MAX_SHELTOM];

public:

	int  AginStoneKind;




public:

	int  AgingItem(int MakeItemFlag = 0);
	int  CancelAgingItem(int Flag = 0);
	int  CheckItem(sITEM *pItem);
	int  CheckAgingItemOk();

	int  SetAgingItemAreaCheck(sITEM *pItem);


	int  CheckAgingData();


	int sinSendAgingItem();
	int sinRecvAgingItem(sCRAFTITEM_SERVER *pCraftItem_Server);
	int sinRecvAgingItemResult(sCRAFTITEM_SERVER *pCraftItem_Server);
	bool isSheltomAreaEmpty(sITEM* Item, int Area);
	bool isAgeableItem(sITEM * pItem);
	bool isItemAreaEmpty();
	bool isStoneAreaEmpty();
};


class cMIXTURERESET
{
public:

	int	OpenFlag;
	int	MixtureResetItemCheckSum;
	int	HaveMixtureResetStone;

public:

	int	SetMixtureItemResetAreaCheck(sITEM *pItem);
	int PickUpMixtureResetItem(int x, int y, int PickUpFlag = 0, int Kind = 0);
	int LastSetMixtureResetItem(sITEM *pItem, int kind);
	int	CancelMixtureItemReset(int Flag = 0);
	int	CheckMixtureResetItemForm();
	int	ReformMixtureResetItem();



	int	MixtureItemReset();
	int	CheckItem();
	int	CheckMixtureItemResetOk();
	int	CheckMixtureItemData();



	int	sinSendMixtureItemReset();
	int	sinRecvMixtureItemReset(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem);
	int	sinRecvMixtureItemResetResult(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server);
};



class CSmeltingItem
{
public:
	int OpenFlag;
	int SmeltingItemCheckSum;
	int m_SmeltingPrice;
public:
	int CancelSmeltingItem();
	int SetSmeltingItemAreaCheck(sITEM *pItem, int Kind = 0);
	int LastSetSmeltingItem(sITEM *pItem, int Kind = 0);
	int CheckSmeltingItemForm();
	int ReFormSmeltingItem();
	int PickUpSmeltingItem(int x, int y, int PickUpFlag = 0, int Kind = 0);
	int sinSendSmeltingItem();
	int sinRecvSmeltingItem(sSMELTINGITEM_SERVER *pSmeltingItem_Server);
	int sinRecvSmeltingItemResult(sSMELTINGITEM_SERVER *pSmeltingItem_Server);
	int SmeltingCheckEmptyArea(sITEM *pItem);
	int GetSmeltingCheckEmptyArea();
	int CheckSmeltingPrice();
	int GetSheltomIndex(DWORD SmeltingItemCode);
};



class CManufacture
{
public:
	int m_OpenFlag;
	int m_ManufactureItemCheckSum;
	int m_ManufacturePrice;
	DIRECTDRAWSURFACE m_lpGrayRune[MAX_SHELTOM];
public:
	void RuneIndexInit();
	int CancelManufactureItem();
	int SetManufactureItemAreaCheck(sITEM *pItem);
	int LastSetManufactureItem(sITEM *pItem);
	int CheckManufactureItem();
	int ReFormManufactureItem();
	int PickUpManufactureItem(int x, int y, int PickUpFlag = 0);
	int sinSendManufactureItem();
	int sinRecvManufactureItem(SManufactureItem_Server *pManufactureItem_Server);
	int RecvManufactureItemResult(SManufactureItem_Server *pManufactureItem_Server);
	int ManufactureCheckEmptyArea(sITEM *pItem);
	int GetRecipeIndex(DWORD Code);
	int GetManufactureCheckEmptyArea();
	SManufacture_ResultItemInfo ManufactureCheckItem(sITEM *pItemCode, smCHAR_INFO *charInfo);
};


class cCRAFTITEM
{
public:
	int OpenFlag;
	int CraftItemCheckSum;
	int ForceFlag;
	int ForceItemPrice;
	int iReconItemFlag;
public:

	int SetCraftItemAreaCheck(sITEM *pItem, int Kind = 0);
	int LastSetCraftItem(sITEM *pItem, int Kind = 0);
	int PickUpCraftItem(int x, int y, int PickUpFlag = 0, int Kind = 0);


	int MixingItem();


	int CraftCheckEmptyArea(sITEM *pItem);
	int CancelMixItem();

	int CheckHackCraftItem();
	int CheckCraftItemForm();
	int ReFormCraftItem();

	int sinSendCraftItem();
	int sinRecvCraftItem(sCRAFTITEM_SERVER *pCraftItem_Server);


	int sinRecvCraftItemResult(sCRAFTITEM_SERVER *pCraftItem_Server);


	int CheckForceOrbPrice();
	int CheckForceOrbPrice(sITEM *pItem);


	int haCheckReconItem();
	int haSendReconItem();



	int GetCraftCheckEmptyArea();

	int haCraftSortItem(sCRAFTITEM *pCraftItem);

	bool isSheltomAreaEmpty(sITEM* Item, int Area);
	bool isMixableItem(sITEM* Item);

	bool isItemAreaEmpty();
	bool isStoneAreaEmpty();
};





class cWAREHOUSE
{
public:
	int OpenFlag;
	int WareHouseCheckSum;

public:

	int SetWareHouseItemAreaCheck(sITEM *pItem);
	int CrashWareHouseItem(RECT &desRect, int PassItemIndex = 0);
	int ChangeWareHouseItem(sITEM *pItem);
	int LastSetWareHouseItem(sITEM *pItem);
	int PickUpWareHouseItem(int x, int y, int PickUpFlag = 0);


	int GetWeight();


	int LoadWareHouseItemIamge();


	int BackUpInvenItem();

	int RestoreInvenItem();

	int CloseWareHouse();


	int ReFormWareHouse();
	int CheckWareHouseForm();


	int CopyItemNotPickUp(sITEM *pItem, int JumpIndex);
	int CheckCopyItem();
	int DeleteCopyItem();

};


class cTRADE
{

public:

	int OpenFlag;
	int MatTrade[4];
	int MatWareHouse[3];
	int MatTradebuttonMain;
	int MatTradebuttonCancel;

	DIRECTDRAWSURFACE lpbuttonCancel;

	DIRECTDRAWSURFACE lpbuttonCancelInfo;

	DIRECTDRAWSURFACE lpbuttonOk;
	DIRECTDRAWSURFACE lpCheck;

	DIRECTDRAWSURFACE lpCheck_Glay;
	DIRECTDRAWSURFACE lpCheckInfo;
	DIRECTDRAWSURFACE lpDelayCheck;

	DIRECTDRAWSURFACE lpCenterBox;

	sITEM CheckItem[100];
	sITEM CheckRecvItem[MAX_TRADE_ITEM];


	int   TradeRequestFlag;
	DWORD TradeCharCode;
	char  szTradeCharName[64];

	int   TradeItemCheckSum;



public:
	cTRADE();
	~cTRADE();

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

	void DrawTradeText();


	int SetTradeItemAreaCheck(sITEM *pItem);
	int CrashTradeItem(RECT &desRect, int PassItemIndex = 0, int Kind = 0);
	int InitTradeColorRect();
	int ChangeTradeItem(sITEM *pItem);
	int LastSetTradeItem(sITEM *pItem);
	int PickUpTradeItem(int x, int y, int PickUpFlag = 0);


	int CheckTradeItemSet();
	int TradeCheckEmptyArea(sITEM *pItem);
	int ChecketInvenItem(sITEM *pItem);


	int CheckOkTradeItem();
	int CancelTradeItem();
	int LoadTradeItemIamge();


	int CheckTradeButtonOk();


	int GetWeight();


	int CheckTradeItemForm();
	int ReFormTradeItem();


};

int ManufactureItemResultInfo(SManufacture_ResultItemInfo_Server *pResultItemInfo);

int CopyMixItemCheckDelete(sITEM *pItem);
int sinMakeItemCheck();
int sinPosBoxNpc();
extern SManufacture_ResultItemInfo g_Manufacture_ItemInfo[MAX_HANDMADEITEM];
extern cTRADE cTrade;
extern sTRADE sTrade;
extern sTRADE sTradeRecv;

extern int RequestTradeButtonFlag;

extern cWAREHOUSE cWareHouse;
extern sWAREHOUSE sWareHouse;
extern sITEM *BackUpInvenItem2;


extern cCRAFTITEM cCraftItem;

extern CSmeltingItem SmeltingItem;
extern SSmeltingItem S_smeltingItem;
extern sSMELTINGITEM_SERVER sSmeltingItem_Send;
extern sSMELTINGITEM_SERVER sSmeltingItem_Recv;

extern CManufacture ManufactureItem;
extern SManufactureItem g_sManufactureItem;
extern SManufactureItem_Server g_sManufactureItem_Send;
extern SManufactureItem_Server g_sManufactureItem_Recv;
extern SManufacture_Rune g_sManufacture_Rune[MAX_RECIPE_KIND];

extern sCRAFTITEM sCraftItem;
extern sCRAFTITEM_INFO sCraftItem_Info[MAX_CRAFTITEM_INFO];

extern sCRAFTITEM_SERVER sCraftItem_Send;
extern sCRAFTITEM_SERVER sCraftItem_Recv;

extern sCRAFTITEM_SERVER sAging_Send;
extern sCRAFTITEM_SERVER sAging_Recv;


extern int ShowItemCraftMessageFlag;
extern int ShowItemAgingMessageFlag;
extern int ShowItemSmeltingMessageFlag;
extern int ShowItemManufactureMessageFlag;
extern int ShowItemOverSpace;

extern int TempShowMoney;
extern int ItemPickUpFlag;
extern int WareHouseSaveFlag;


extern cAGING	cAging;
extern sAGINGITEM sAgingItem;
extern sAGINGITEM_INFO sAgingItem_Info[MAX_AGINGITEM_INFO];

extern int AgingLevelAttack[23];
extern int AgingLevelCritical[23];

extern char szAgingItemBuff[128];
extern POINT CraftItemMessageSize;

extern int AgingCheckSheltomFlag;
extern int AgingSheltomCnt2;
extern int MixItemNoCopyFlag;
extern int CheckMixItemCopyFlag;
extern sMAKEITEM_INFO sMakeItem_Info[MAX_MAKEITEM_INFO];


extern cMIXTURERESET cMixtureReset;
extern sMIXTURE_RESET_ITEM	sMixtureResetItem;
extern sMIXTURE_RESET_ITEM sMixtureResetItemBackUp;
extern int	MixtureResetCheckFlag;
extern sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Send;
extern sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Recv;

extern char *PostBoxDocFilePath[];

extern sPOSTBOX_ITEM sPostbox_Item[50];
extern int PostBoxIndexCnt;
extern DWORD ExpressItemCode;
extern char  szExpressItemName[64];

extern sCRAFTITEM_SERVER sWingItem_Send;
extern sCRAFTITEM_SERVER sWingItem_Recv;

extern int DownTradePosi[6][4];
extern DWORD SheltomCode2[];
extern DWORD MagicSheltomCode[];
extern DWORD BillingMagicSheltomCode[];
extern int ForceItemPrice2;
extern sRECON_ITEM sReconItem[MAX_SEEL_COUNT];
extern int		MixCancelButtonDelayFlag;
