

#include "sinLinkHeader.h"

//#define AGING_MONEY_FREE 

cTRADE cTrade;
sTRADE sTrade;
sTRADE sTradeRecv;

cMIXTURERESET cMixtureReset;
sMIXTURE_RESET_ITEM	sMixtureResetItem;
sMIXTURE_RESET_ITEM sMixtureResetItemBackUp;
int	MixtureResetCheckFlag = 0;
sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Send;
sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Recv;

cAGING	cAging;
sAGINGITEM sAgingItem;
sAGINGITEM sAgingItemBackUp;


sCRAFTITEM_SERVER sAging_Send;
sCRAFTITEM_SERVER sAging_Recv;

cWAREHOUSE cWareHouse;
sWAREHOUSE sWareHouse;

int WareHouseSaveFlag = 0;
int CloseWareHouseCheckFlag2 = 0;
int CloseWareHouseCheckFlag3 = 0;

cCRAFTITEM cCraftItem;
sCRAFTITEM sCraftItem;
sCRAFTITEM sCraftItemBackUp;


CSmeltingItem SmeltingItem;
SSmeltingItem S_smeltingItem;
SSmeltingItem sSmeltingItemBackUp;
sSMELTINGITEM_SERVER sSmeltingItem_Send;
sSMELTINGITEM_SERVER sSmeltingItem_Recv;


CManufacture ManufactureItem;
SManufactureItem g_sManufactureItem;
SManufactureItem g_sManufactureItemBackUp;
SManufactureItem_Server g_sManufactureItem_Send;
SManufactureItem_Server g_sManufactureItem_Recv;
SManufacture_Rune g_sManufacture_Rune[MAX_RECIPE_KIND];
SManufacture_ResultItemInfo g_Manufacture_ItemInfo[MAX_HANDMADEITEM];


sCRAFTITEM_SERVER sCraftItem_Send;
sCRAFTITEM_SERVER sCraftItem_Recv;

sCRAFTITEM_SERVER sWingItem_Send;
sCRAFTITEM_SERVER sWingItem_Recv;

int MixItemNoCopyFlag = 0;


int CraftItemButtonIndex = 0;
int CraftItemSendServerIndex = 0;


int CheckMixItemCopyFlag = 0;

int ShowItemCraftMessageFlag = 0;
int ShowItemAgingMessageFlag = 0;
int ShowItemSmeltingMessageFlag = 0;
int ShowItemManufactureMessageFlag = 0;
int ShowItemOverSpace = 0;

char szAgingItemBuff[128];
char szCraftItemBuff[128];
POINT CraftItemMessageBoxPosi = { 0,0 };
POINT CraftItemMessageSize = { 0,0 };


sITEM *BackUpInvenItem2;
sITEM *BackUpInvenTempItem2;
sINVENTORY *BackUpsInven;
int   InvenGold = 0;
int   RealGold = 0;

int TradeCheckFlag = 0;

int CopyItemIndex7[10] = { 0,0,0,0,0,0,0,0,0,0 };

int TradeColorIndex = 0;
int	TradeCrashItemIndex[2] = { 0,0 };
RECT TradeColorRect = { 0,0,0,0 };
int  SelectTradeItemIndex = 0;
int RequestTradeButtonFlag = 0;

int ItemKindFlag = 0;


int CheckDelayFlag = 0;
int sinCancelFlag = 0;


int TempShowMoney = 0;



int CloseWareHouseFlag = 0;




int ItemPickUpFlag = 0;


sPOSTBOX_ITEM sPostbox_Item[50];
int PostBoxIndexCnt = 0;
DWORD ExpressItemCode = 0;
char  szExpressItemName[64];


char *PostBoxDocFilePath[] = {
	"image\\Sinimage\\shopall\\PostBox.sin",

};

sRECON_ITEM sReconItem[MAX_SEEL_COUNT] =
{

	{ (sinSE1 | sin01),{ 0, 105 }, 2, 100000 },
	{ (sinSE1 | sin02),{ 61, 100 }, 2, 50000 },
	{ (sinSE1 | sin03),{ 0, 60 }, 2, 2000 },
	{ (sinSE1 | sin04),{ 105, 150 }, 2, 70000 },
	{ (sinSE1 | sin05),{ 0, 150 }, 1, 10000 },
	{ (sinSE1 | sin06),{ 0, 150 }, 1, 10000 },
	{ (sinSE1 | sin07),{ 0, 150 }, 1, 10000 },
	{ (sinSE1 | sin08),{ 0, 150 }, 1, 10000 },
	{ (sinSE1 | sin09),{ 0, 150 }, 1, 10000 },
	{ (sinSE1 | sin10),{ 0, 150 }, 1, 10000 },
	{ (sinSE1 | sin11),{ 0, 150 }, 1, 10000 },
	{ (sinSE1 | sin12),{ 0, 150 }, 1, 10000 },
	{ (sinSE1 | sin13),{ 0, 150 }, 1, 10000 },
	{ (sinSE1 | sin14),{ 0, 150 }, 1, 10000 }
};

#define T_REVISION_Y			22*5



#define TRADEBUTTONMAIN_X		513
#define TRADEBUTTONMAIN_Y		3

#include "..\\nettype.h"


sCRAFTITEM_INFO sCraftItem_Info[MAX_CRAFTITEM_INFO] = {

#ifdef _W_SERVER
#include "sinCraftItem_Server.h"
#else
#include "sinCraftItem_Client.h"
#endif
};


sMAKEITEM_INFO sMakeItem_Info[MAX_MAKEITEM_INFO] = {
	#include "sinMakeItem.h"
};


DWORD sinTradeColor = RGBA_MAKE(0, 200, 255, 80);


int UpTradePosi[5][4] = {
	{21,136 + sinInterHeight2,21 + (22 * 9),136 + (22 * 4) + sinInterHeight2},
	{231,170 + sinInterHeight2,250,189 + sinInterHeight2},
	{251,120,326,137},
	{251,118,326,162},
	{252,221 + sinInterHeight2,252 + 26,221 + 26 + sinInterHeight2}

};

int DownTradePosi[6][4] = {
	{21,224 + 21 + sinInterHeight2,21 + (22 * 9),224 + 21 + (22 * 4) + sinInterHeight2},
	{225,205,250,226},
	{251,206,326,224},
	{251,232,326,250},
	{252 + 1,310 + sinInterHeight2,252 + 26,310 + 26 + sinInterHeight2},
	{305,314 + sinInterHeight2,304 + 20,314 + 20 + sinInterHeight2},
};


int TradeStartX = DownTradePosi[T_SET_BOX][0], TradeStartY = DownTradePosi[T_SET_BOX][1], TradeEndX = DownTradePosi[T_SET_BOX][2], TradeEndY = DownTradePosi[T_SET_BOX][3];

char szAgingMsgBuff[128];
char *SheltomName[MAX_SHELTOM] = { "·¯¾¾µð","½ê·¹³×¿À","ÆÄµ¥¿À","½ºÆÄÅ°","·¹ÀÌ´øÆ®","Æ®·£½ºÆÐ·Î","¸ÓÅ°","µ¥ºñ³×","½ì·¹½ºÅä","¹Ì¶óÁö","ÀÎÆä¸£³ª","ÀÌ´Ï±×¸¶","º§·ë" };


#ifdef __SIN_AGING_TEST


int AgingLevelAttack[21] = { 2,4,6,8,10,11,12,13,14,15,10,10,10,10,10,10,10,10,10,10,10 };


int AgingLevelCritical[21] = { 2,4,6,8,10,11,12,13,14,15,10,10,10,10,10,10,10,10,10,10,10 };


int AgingLevelBlock[21] = { 2,4,6,8,10,11,12,13,14,15,10,10,10,10,10,10,10,10,10,10,10 };


int AgingLevelHit[21] = { 2,4,6,8,10,11,12,13,14,15,10,10,10,10,10,10,10,10,10,10,10 };

int AgingLevelSheltom[20][12] = {
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},


	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},

	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},

};
int AgingOkPercent[20] = { 0,5,15,30,50,60,70,80,90,95,10,10,10,10,10,10,10,10,10,10 };


#else 


#ifdef _W_SERVER

int AgingLevelAttack[23] = { 100,130,169,219,284,369,479,622,808,1049,1362,1769,2297,2983,3874,5031,6534,8486,11021,14313,14313,14313 };
int AgingLevelCritical[23] = { 12,16,21,27,35,45,58,75,97,126,164,213,277,360,468,608,790,1026,1332,1730,1730,1730 };
int AgingLevelBlock[23] = { 15,19,25,32,42,55,71,92,119,155,201,261,339,440,571,742,964,1252,1626,2112,2112,2112 };
int AgingLevelHit[23] = { 45,58,75,97,126,164,213,277,360,468,608,790,1026,1332,1730,2247,2918,3790,4922,6392,6392,6392 };


// FALHA DO AGING
int AgingOkPercent[20] = { 0, 0, 0, 0, 0, 0, 0, 6, 9, 14, 18, 21, 25, 29, 32, 36, 40, 44, 49, 53 };
int AgingStoneAgingOkPercent[20] = { 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 10, 14, 18, 22, 26, 30, 33, 36, 38, };
int SuperAgingStoneAgingFailPercent[20] = { 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 10, 14, 18, 22, 26, 30, 43, 47, 48, };
int SuperAgingStone1_5AgingFailPercent[20] = { 0, 0, 0, 0, 0, 0, 0, 4, 8, 10, 13, 15, 18, 24, 28, 32, 36, 39, 42 };

//COM FALHA
//int AgingOkPercent[22] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 50, 70,0,0 };
//int AgingStoneAgingOkPercent[22] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 40,0,0 };
//int SuperAgingStoneAgingFailPercent[22] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 40,0,0 };
///int SuperAgingStone1_5AgingFailPercent[22] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 40,0,0 };

//FALHA DO AGING ORIGINAL
//int AgingOkPercent[18] = { 0, 0, 0, 0, 0, 5, 10, 15, 20, 30, 35, 40, 45, 50, 55, 65, 75, 85 };
//int AgingStoneAgingOkPercent[18] = { 0, 0, 0, 0, 0, 3, 5, 8, 11, 18, 21, 25, 29, 33, 38, 48, 60, 74 };
//int SuperAgingStoneAgingFailPercent[18] = { 0, 0, 0, 0, 0, 3, 5, 8, 11, 18, 21, 25, 29, 33, 38, 48, 60, 74 };
//int SuperAgingStone1_5AgingFailPercent[18] = { 0, 0, 0, 0, 0, 3, 7, 11, 14, 22, 26, 31, 35, 40, 45, 55, 67, 79 };


#else


int AgingLevelAttack[21] = { 200,400,800,1500,3000,5000,10000,15000,25000,50000,10,100,10,10,10,10,10,10,10,10,10 };


int AgingLevelCritical[21] = { 40,80,160,300,600,1000,2000,3000,5000,10000,10,100,10,10,10,10,10,10,10,10,10 };


int AgingLevelBlock[21] = { 40,80,160,300,600,1000,2000,3000,5000,10000,10,100,10,10,10,10,10,10,10,10,10 };


int AgingLevelHit[21] = { 100,200,300,750,1500,2500,5000,7500,12500,25000,10,100,10,10,10,10,10,10,10,10,10 };

int AgingOkPercent[20] = { 0, 0, 0, 0, 0, 5, 10, 15, 20, 30, 35, 40, 45, 50, 55, 65, 75, 85, 95, 95 };
int AgingStoneAgingOkPercent[20] = { 0, 0, 0, 0, 0, 3, 5, 8, 11, 18, 21, 25, 29, 33, 38, 48, 60, 74, 90, 90 };
int SuperAgingStoneAgingFailPercent[20] = { 0, 0, 0, 0, 0, 3, 5, 8, 11, 18, 21, 25, 29, 33, 38, 48, 60, 74, 90, 90 };

int SuperAgingStone1_5AgingFailPercent[20] = { 0, 0, 0, 0, 0, 3, 7, 11, 14, 22, 26, 31, 35, 40, 45, 55, 67, 79, 93, 93 };


#endif


int AgingLevelSheltom[22][12] = {
	{3,3,4,4,5,0,0,0,0,0,0,0},//+1
	{3,3,4,4,5,5,0,0,0,0,0,0},//+2
	{3,3,4,4,5,5,6,0,0,0,0,0},//+3
	{3,3,4,4,5,5,6,6,0,0,0,0},//+4
	{3,3,4,4,5,5,6,6,7,0,0,0},//+5
	{3,3,4,4,5,5,6,6,7,7,0,0},//+6
	{3,3,4,4,5,5,6,6,7,7,8,0},//+7
	{3,3,4,4,5,5,6,6,7,7,8,8},//+8
	{4,4,5,5,6,6,7,7,8,8,9,0},//+9
	{4,4,5,5,6,6,7,7,8,8,9,9},//+10
	{5,5,6,6,7,7,8 ,8 ,9 ,9 ,10,0 },//+11
	{5,5,6,6,7,7,8 ,8 ,9 ,9 ,10,10},//+12
	{6,6,7,7,8,8,9 ,9 ,10,10,11,0 },//+13
	{6,6,7,7,8,8,9 ,9 ,10,10,11,11},//+14
	{7,7,8,8,9,9,10,10,11,11,12,0 },//+15
	{7,7,8,8,9,9,10,10,11,11,12,12},//+16
	{8,8,9,9,10,10,11,11,12,12,13,0},//+17
	{8,8,9,9,10,10,11,11,12,12,13,13},//+18
	//{9,9,10,10,11,11,12,12,13,13,14,0},//+19
	//{9,9,10,10,11,11,12,12,13,13,14,14},//+20
	//{10,10,11,11,12,12,13,13,14,14,14,},//+21
	//{11,11,12,12,13,13,14,14,14,14,14},//+22
};




#endif

int AgingLevelSheltomIndex[4][3] = {
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0
};


int AgingCheckSheltomFlag = 0;
int AgingSheltomCnt2 = 0;



#define SIN_AGING_MASK	0x00101011


int AgingLevelMoney[20] = { 1000 ^ SIN_AGING_MASK,2000 ^ SIN_AGING_MASK,3000 ^ SIN_AGING_MASK,4000 ^ SIN_AGING_MASK,5000 ^ SIN_AGING_MASK,
							6000 ^ SIN_AGING_MASK,7000 ^ SIN_AGING_MASK,8000 ^ SIN_AGING_MASK,9000 ^ SIN_AGING_MASK,10000 ^ SIN_AGING_MASK,
							11000 ^ SIN_AGING_MASK,12000 ^ SIN_AGING_MASK,13000 ^ SIN_AGING_MASK,14000 ^ SIN_AGING_MASK,15000 ^ SIN_AGING_MASK,
							16000 ^ SIN_AGING_MASK,17000 ^ SIN_AGING_MASK,18000 ^ SIN_AGING_MASK,19000 ^ SIN_AGING_MASK,20000 ^ SIN_AGING_MASK//, 21000 ^ SIN_AGING_MASK,22000 ^ SIN_AGING_MASK
};

POINT AgingLevelSheltomXY[4][3] = {
	{{218,193 + sinInterHeight2}			,{218 + 22,193 + sinInterHeight2}		  ,{218 + 22 + 22,193 + sinInterHeight2}},
	{{218,193 + 22 + sinInterHeight2}		,{218 + 22,193 + 22 + sinInterHeight2}	  ,{218 + 22 + 22,193 + 22 + sinInterHeight2}},
	{{218,193 + 22 + 22 + sinInterHeight2}	,{218 + 22,193 + 22 + 22 + sinInterHeight2}   ,{218 + 22 + 22,193 + 22 + 22 + sinInterHeight2}},
	{{218,193 + 22 + 22 + 22 + sinInterHeight2} ,{218 + 22,193 + 22 + 22 + 22 + sinInterHeight2},{218 + 22 + 22,193 + 22 + 22 + 22 + sinInterHeight2}}

};


int ForceItemPrice2 = 0;
DIRECTDRAWSURFACE	lpForceMain;
DIRECTDRAWSURFACE	lpForceButtonInfo;
DIRECTDRAWSURFACE	lpForceTitle;



cTRADE::cTRADE()
{

}
cTRADE::~cTRADE()
{

}

void cTRADE::Init()
{


	memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
	memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));


	MatTradebuttonMain = CreateTextureMaterial("Image\\SinImage\\Shopall\\TradeButton\\TradeButtonMain.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatTradebuttonCancel = CreateTextureMaterial("Image\\SinImage\\Shopall\\TradeButton\\ButtonCancel.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	sWareHouse.Money += 2023;
	sWareHouse.Weight[0] += 500;
	sWareHouse.Weight[1] += 499;

	ManufactureItem.RuneIndexInit();
	Load();

}

void cTRADE::Load()
{
	char szTemp[256];

	lpCheck = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_Check.bmp");
	lpCheckInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_Check_Info.bmp");
	lpDelayCheck = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_Check_Delay.bmp");

	lpbuttonOk = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\TradeButton\\ButtonOk.bmp");

	lpbuttonCancel = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_Cancel.bmp");
	lpbuttonCancelInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_CancelInfo.bmp");

	lpCheck_Glay = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_Check_Glay.bmp");
	lpCenterBox = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Trade_0.bmp");

	for (int i = 0; i < MAX_SHELTOM; i++)
	{
		wsprintf(szTemp, "Image\\SinImage\\shopall\\Aging\\itos%d_.bmp", 100 + i + 1);
		cAging.lpGraySheltom[i] = LoadDibSurfaceOffscreen(szTemp);
	}


}

void cTRADE::Release()
{
	if (lpCheck)
	{
		lpCheck->Release();
		lpCheck = 0;
	}
	if (lpCheckInfo)
	{
		lpCheckInfo->Release();
		lpCheckInfo = 0;

	}
	if (lpDelayCheck)
	{
		lpDelayCheck->Release();
		lpDelayCheck = 0;

	}
	if (lpbuttonOk)
	{
		lpbuttonOk->Release();
		lpbuttonOk = 0;
	}
	if (lpbuttonCancel)
	{
		lpbuttonCancel->Release();
		lpbuttonCancel = 0;

	}
	if (lpbuttonCancelInfo)
	{
		lpbuttonCancelInfo->Release();
		lpbuttonCancelInfo = 0;

	}
	if (lpCheck_Glay)
	{
		lpCheck_Glay->Release();
		lpCheck_Glay = 0;
	}

}

DWORD TradeSpotTimer = 0;

void cTRADE::Draw()
{
	sinInterHeight2 = -50;

	int i = 0, j = 0;




	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);





	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_TRADE]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_TRADE]), 47, cShop.lpTitle_Trade, 0, 0, 111, 244);



	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 47, cShop.lpTitle_CraftItem, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 135 + sinInterHeight2, cShop.lpCraftItemMain, 0, 0, 320, 208);

	DrawSprite(200 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 314 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 98, 21);

	if (cCraftItem.ForceFlag)
	{
		if (!lpForceMain)
		{
			lpForceMain = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\shop_alchemy.bmp");
			lpForceButtonInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\Bt_alchemy.bmp");
			lpForceTitle = LoadDibSurfaceOffscreen("Image\\SinImage\\shopall\\title_alchemy.bmp");
		}
		DrawSprite(17 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 134 + sinInterHeight2, lpForceMain, 0, 0, 217, 208);
		DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 47, lpForceTitle, 0, 0, 111, 32);
	}



	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 47, cShop.lpTitle_Aging, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 135 + sinInterHeight2, cShop.lpCraftItemMain, 0, 0, 320, 208);
	DrawSprite(200 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 314 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 98, 21);


	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), 47, cShop.lpTitle_SmeltingItem, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), 135 + sinInterHeight2, cShop.lpSmeltingItemMain, 0, 0, 320, 208);
	DrawSprite(200 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), 314 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 98, 21);


	DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), 47, cShop.lpTitle_ManufactureItem, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), 135 + sinInterHeight2, cShop.lpManufactureItemMain, 0, 0, 320, 208);
	DrawSprite(200 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), 314 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 98, 21);


	//DrawSprite(0 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), 90 + sinInterHeight2, cShop.lpShopMain, 0, 0, 344, 264);
	DrawSprite(225 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), 47, cShop.lpMResetTitle, 0, 0, 111, 32);
	DrawSprite(18 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), 135 + sinInterHeight2, cShop.lpMResetMain, 0, 0, 320, 208);

	for (i = 0; i < 9; i++)
		DrawSprite(21 + (i * 22) - (256 + 128 - sinMoveKindInter[SIN_TRADE]), 224 + sinInterHeight2, lpCenterBox, 0, 0, 22, 21);

	if (sTrade.CheckFlag)
	{
		if (!CheckDelayFlag)
			DrawSprite(DownTradePosi[T_CHECK_POSI][0] - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_CHECK_POSI][1], lpCheck, 0, 0, 26, 26);
	}
	if (sTradeRecv.CheckFlag)
	{
		DrawSprite(UpTradePosi[T_CHECK_POSI][0] - (256 + 128 - sinMoveKindInter[SIN_TRADE]), UpTradePosi[T_CHECK_POSI][1], lpCheck, 0, 0, 26, 26);

	}
	if (TradeCheckFlag == T_CHECK_POSI)
	{
		DrawSprite(DownTradePosi[T_CHECK_POSI][0] - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_CHECK_POSI][1] - 27, lpCheckInfo, 0, 0, 47, 27);

	}
	if (TradeCheckFlag == T_CLOSE_POSI)
	{
		DrawSprite(DownTradePosi[T_CLOSE_POSI][0] - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_CLOSE_POSI][1], lpbuttonCancel, 0, 0, 20, 20);
		DrawSprite(DownTradePosi[T_CLOSE_POSI][0] - 27 - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_CLOSE_POSI][1] - 27, lpbuttonCancelInfo, 0, 0, 77, 27);

	}


	if (CheckDelayFlag)
	{

		DrawSprite(DownTradePosi[T_CHECK_POSI][0] - (256 + 128 - sinMoveKindInter[SIN_TRADE]), DownTradePosi[T_CHECK_POSI][1], lpCheck_Glay, 0, 0, 26, 26);



	}

	if (CloseWareHouseFlag)
	{
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 313 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);

	}


	if (cAging.OpenFlag)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (AgingLevelSheltomIndex[i][j])
				{
					DrawSprite(AgingLevelSheltomXY[i][j].x, AgingLevelSheltomXY[i][j].y, cAging.lpGraySheltom[AgingLevelSheltomIndex[i][j] - 1], 0, 0, 22, 22);
				}
			}
		}
	}


	if (SmeltingItem.OpenFlag)
	{
		int SheltomIndex = 0;
		if (S_smeltingItem.SmeltingItem[0].Flag)
		{
			SheltomIndex = SmeltingItem.GetSheltomIndex(S_smeltingItem.SmeltingItem[0].CODE);
			if (SheltomIndex)
			{

				DrawSprite(AgingLevelSheltomXY[0][0].x + 22, AgingLevelSheltomXY[0][0].y + 30,
					cAging.lpGraySheltom[SheltomIndex - 1], 0, 0, 22, 22);
			}
		}
	}




	switch (TradeColorIndex)
	{
	case SET_ITEM_CHECK_COLOR:
		if (MouseItem.Flag)
		{
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_TRADE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_AGING]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);

			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);

			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);

			dsDrawColorBox(sinInvenColor[0], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		}
		break;
	case OVERLAP_ITEM_COLOR:
		if (TradeCrashItemIndex[0])
		{
			dsDrawColorBox(sinInvenColor[1], sWareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].x - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]),
				sWareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].y, sWareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].w, sWareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].h);
		}

		break;
	case NOT_SETTING_COLOR:
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_TRADE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_AGING]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		break;

	case NOT_AGING_ITEM:
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_AGING]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);

	case NOT_USE_COLOR:
		dsDrawColorBox(sinInvenColor[2], TradeColorRect.left - (256 + 128 - sinMoveKindInter[SIN_TRADE]), TradeColorRect.top, TradeColorRect.right, TradeColorRect.bottom);
		break;

	case SELECT_ITEM_COLOR:
		for (i = 0; i < 10; i++)
		{
			if (CopyItemIndex7[i])
			{
				dsDrawColorBox(sinInvenColor[4], sWareHouse.WareHouseItem[CopyItemIndex7[i] - 1].x - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]),
					sWareHouse.WareHouseItem[CopyItemIndex7[i] - 1].y, sWareHouse.WareHouseItem[CopyItemIndex7[i] - 1].w, sWareHouse.WareHouseItem[CopyItemIndex7[i] - 1].h);
			}
		}
		if (!SelectTradeItemIndex)break;
		if (ItemKindFlag == 1)
		{
			dsDrawColorBox(sinInvenColor[4], sTrade.TradeItem[SelectTradeItemIndex - 1].x - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
				sTrade.TradeItem[SelectTradeItemIndex - 1].y, sTrade.TradeItem[SelectTradeItemIndex - 1].w, sTrade.TradeItem[SelectTradeItemIndex - 1].h);
		}

		if (ItemKindFlag == 2)
		{
			dsDrawColorBox(sinInvenColor[4], sTradeRecv.TradeItem[SelectTradeItemIndex - 1].x - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
				sTradeRecv.TradeItem[SelectTradeItemIndex - 1].y - T_REVISION_Y, sTradeRecv.TradeItem[SelectTradeItemIndex - 1].w, sTradeRecv.TradeItem[SelectTradeItemIndex - 1].h);
		}
		if (sWareHouse.WareHouseItem[SelectTradeItemIndex - 1].Flag)
			dsDrawColorBox(sinInvenColor[4], sWareHouse.WareHouseItem[SelectTradeItemIndex - 1].x - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]),
				sWareHouse.WareHouseItem[SelectTradeItemIndex - 1].y, sWareHouse.WareHouseItem[SelectTradeItemIndex - 1].w, sWareHouse.WareHouseItem[SelectTradeItemIndex - 1].h);
		if (sCraftItem.CraftItem[SelectTradeItemIndex - 1].Flag)
			dsDrawColorBox(sinInvenColor[4], sCraftItem.CraftItem[SelectTradeItemIndex - 1].x - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]),
				sCraftItem.CraftItem[SelectTradeItemIndex - 1].y, sCraftItem.CraftItem[SelectTradeItemIndex - 1].w, sCraftItem.CraftItem[SelectTradeItemIndex - 1].h);
		if (sAgingItem.AgingItem[SelectTradeItemIndex - 1].Flag)
			dsDrawColorBox(sinInvenColor[4], sAgingItem.AgingItem[SelectTradeItemIndex - 1].x - (256 + 128 - sinMoveKindInter[SIN_AGING]),
				sAgingItem.AgingItem[SelectTradeItemIndex - 1].y, sAgingItem.AgingItem[SelectTradeItemIndex - 1].w, sAgingItem.AgingItem[SelectTradeItemIndex - 1].h);

		if (S_smeltingItem.SmeltingItem[SelectTradeItemIndex - 1].Flag)
		{
			dsDrawColorBox(sinInvenColor[4], S_smeltingItem.SmeltingItem[SelectTradeItemIndex - 1].x - (256 + 128 - sinMoveKindInter[SIN_SMELTING]),
				S_smeltingItem.SmeltingItem[SelectTradeItemIndex - 1].y, S_smeltingItem.SmeltingItem[SelectTradeItemIndex - 1].w, S_smeltingItem.SmeltingItem[SelectTradeItemIndex - 1].h);
		}

		if (g_sManufactureItem.ManufactureItem[SelectTradeItemIndex - 1].Flag)
		{
			dsDrawColorBox(sinInvenColor[4], g_sManufactureItem.ManufactureItem[SelectTradeItemIndex - 1].x - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]),
				g_sManufactureItem.ManufactureItem[SelectTradeItemIndex - 1].y, g_sManufactureItem.ManufactureItem[SelectTradeItemIndex - 1].w, g_sManufactureItem.ManufactureItem[SelectTradeItemIndex - 1].h);
		}

		if (sMixtureResetItem.MixtureResetItem[SelectTradeItemIndex - 1].Flag)
		{
			dsDrawColorBox(sinInvenColor[4], sMixtureResetItem.MixtureResetItem[SelectTradeItemIndex - 1].x - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]),
				sMixtureResetItem.MixtureResetItem[SelectTradeItemIndex - 1].y, sMixtureResetItem.MixtureResetItem[SelectTradeItemIndex - 1].w, sMixtureResetItem.MixtureResetItem[SelectTradeItemIndex - 1].h);
		}

		break;

	}
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].Flag)
		{
			DrawSprite(sTrade.TradeItem[i].x - (256 + 128 - sinMoveKindInter[SIN_TRADE]), sTrade.TradeItem[i].y, sTrade.TradeItem[i].lpItem, 0, 0, sTrade.TradeItem[i].w, sTrade.TradeItem[i].h);
			if ((sTrade.TradeItem[i].CODE & sinITEM_MASK2) == sinFO1)
			{
				cInvenTory.DrawForceOrbEffect(sTrade.TradeItem[i].x - (256 + 128 - sinMoveKindInter[SIN_TRADE]), sTrade.TradeItem[i].y);
			}

		}
		if (sTradeRecv.TradeItem[i].Flag)
		{
			DrawSprite(sTradeRecv.TradeItem[i].x - (256 + 128 - sinMoveKindInter[SIN_TRADE]), sTradeRecv.TradeItem[i].y - T_REVISION_Y, sTradeRecv.TradeItem[i].lpItem, 0, 0, sTradeRecv.TradeItem[i].w, sTradeRecv.TradeItem[i].h);
			if ((sTradeRecv.TradeItem[i].CODE & sinITEM_MASK2) == sinFO1)
			{
				cInvenTory.DrawForceOrbEffect(sTradeRecv.TradeItem[i].x - (256 + 128 - sinMoveKindInter[SIN_TRADE]), sTradeRecv.TradeItem[i].y - T_REVISION_Y);
			}

		}
	}
	if (TradeRequestFlag)
	{
		TradeSpotTimer++;
		if (TradeSpotTimer > 15)
		{
			dsDrawColorBox(sinTradeColor, TRADEBUTTONMAIN_X + 5, TRADEBUTTONMAIN_Y + 5, 160, 53);
			if (TradeSpotTimer > 30)
				TradeSpotTimer = 0;

		}

		dsDrawTexImage(MatTradebuttonMain, TRADEBUTTONMAIN_X, TRADEBUTTONMAIN_Y, 256, 64, 255);
		if (RequestTradeButtonFlag == 1)
			DrawSprite(TRADEBUTTONMAIN_X + 140, TRADEBUTTONMAIN_Y + 11, lpbuttonOk, 0, 0, 23, 23);
		if (RequestTradeButtonFlag == 2)
			dsDrawTexImage(MatTradebuttonCancel, TRADEBUTTONMAIN_X + 144, TRADEBUTTONMAIN_Y + 37, 16, 16, 255);

	}


	for (i = 0; i < 100; i++)
	{
		if (sWareHouse.WareHouseItem[i].Flag)
		{
			DrawSprite(sWareHouse.WareHouseItem[i].x - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), sWareHouse.WareHouseItem[i].y, sWareHouse.WareHouseItem[i].lpItem, 0, 0, sWareHouse.WareHouseItem[i].w, sWareHouse.WareHouseItem[i].h);
			if ((sWareHouse.WareHouseItem[i].CODE & sinITEM_MASK2) == sinFO1)
			{
				cInvenTory.DrawForceOrbEffect(sWareHouse.WareHouseItem[i].x - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), sWareHouse.WareHouseItem[i].y);
			}

		}
	}

	DrawSprite(231 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 243 + sinInterHeight2, cShop.lpGoldEdit, 0, 0, 99, 24);
	DrawSprite(231 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 241 + sinInterHeight2, cShop.lpWeightEdit, 0, 0, 20, 20);
	DrawSprite(243 - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), 100, cShop.lpTitle_WareHouse, 0, 0, 79, 40);



	if (AgingCheckSheltomFlag)
	{

		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 222 + sinInterHeight2, cShop.lpCraftItemButton, 0, 0, 26, 26);

	}


	if (CraftItemButtonIndex == 1)
	{
		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 222 + sinInterHeight2, cShop.lpCraftItemButton, 0, 0, 26, 26);
		if (cCraftItem.ForceFlag)
		{
			DrawSprite(148 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]) - 27, 222 - 27 + sinInterHeight2, lpForceButtonInfo, 0, 0, 100, 27);
		}
		else
		{
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]) - 27, 222 - 27 + sinInterHeight2, cShop.lpCraftItemButtonInfo, 0, 0, 80, 27);
		}

		if (SmeltingItem.OpenFlag)
		{
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), 222 + sinInterHeight2, cShop.lpCraftItemButton, 0, 0, 26, 26);
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]) - 27, 222 - 27 + sinInterHeight2, cShop.lpSmeltingItemButtonInfo, 0, 0, 80, 27);
		}

		if (ManufactureItem.m_OpenFlag)
		{
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), 222 + sinInterHeight2, cShop.lpCraftItemButton, 0, 0, 26, 26);
			DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]) - 27, 222 - 27 + sinInterHeight2, cShop.lpManufactureItemButtonInfo, 0, 0, 80, 27);
		}

	}


	if (MixtureResetCheckFlag)
		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), 221 + sinInterHeight2, cShop.lpMResetButton, 0, 0, 26, 26);


	if (CraftItemButtonIndex == 1 && MixtureResetCheckFlag)
	{

		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]) - 27, 222 - 27 + sinInterHeight2, cShop.lpMResetButtonInfo, 0, 0, 80, 27);
	}

	if (CraftItemButtonIndex == 1 && AgingCheckSheltomFlag)
	{
		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_AGING]), 222 + sinInterHeight2, cShop.lpCraftItemButton, 0, 0, 26, 26);
		DrawSprite(158 - (256 + 128 - sinMoveKindInter[SIN_AGING]) - 27, 222 - 27 + sinInterHeight2, cShop.lpAging_Info, 0, 0, 80, 27);

	}

	if (CraftItemButtonIndex == 2)
	{
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_AGING]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_AGING]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);

		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_SMELTING]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);

		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);

		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]) + 2 - 2, 313 + 1 + sinInterHeight2, cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(304 - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]) - 2, 313 - 27 + sinInterHeight2, cInvenTory.lpExitInfo, 0, 0, 47, 27);
	}

	for (i = 0; i < 15; i++)
	{
		if (sCraftItem.CraftItem[i].Flag)
		{
			DrawSprite(sCraftItem.CraftItem[i].x - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), sCraftItem.CraftItem[i].y, sCraftItem.CraftItem[i].lpItem, 0, 0, sCraftItem.CraftItem[i].w, sCraftItem.CraftItem[i].h);

		}
	}

	for (i = 0; i < 15; i++)
	{
		if (sAgingItem.AgingItem[i].Flag)
		{
			DrawSprite(sAgingItem.AgingItem[i].x - (256 + 128 - sinMoveKindInter[SIN_AGING]), sAgingItem.AgingItem[i].y, sAgingItem.AgingItem[i].lpItem, 0, 0, sAgingItem.AgingItem[i].w, sAgingItem.AgingItem[i].h);

		}
	}


	for (i = 0; i < 2; i++)
	{
		if (sMixtureResetItem.MixtureResetItem[i].Flag)
		{
			DrawSprite(sMixtureResetItem.MixtureResetItem[i].x - (256 + 128 - sinMoveKindInter[SIN_MIXTURE_RESET]), sMixtureResetItem.MixtureResetItem[i].y,
				sMixtureResetItem.MixtureResetItem[i].lpItem, 0, 0, sMixtureResetItem.MixtureResetItem[i].w, sMixtureResetItem.MixtureResetItem[i].h);
		}
	}


	for (i = 0; i < 5; i++)
	{
		if (S_smeltingItem.SmeltingItem[i].Flag)
		{
			DrawSprite(S_smeltingItem.SmeltingItem[i].x - (256 + 128 - sinMoveKindInter[SIN_SMELTING]), S_smeltingItem.SmeltingItem[i].y, S_smeltingItem.SmeltingItem[i].lpItem, 0, 0, S_smeltingItem.SmeltingItem[i].w, S_smeltingItem.SmeltingItem[i].h);
		}
	}

	for (i = 0; i < 4; i++)
	{
		if (g_sManufactureItem.ManufactureItem[i].Flag)
		{
			DrawSprite(g_sManufactureItem.ManufactureItem[i].x - (256 + 128 - sinMoveKindInter[SIN_MANUFACTURE]), g_sManufactureItem.ManufactureItem[i].y, g_sManufactureItem.ManufactureItem[i].lpItem, 0, 0, g_sManufactureItem.ManufactureItem[i].w, g_sManufactureItem.ManufactureItem[i].h);
		}
	}



	CraftItemMessageBoxPosi.x = 230;
	CraftItemMessageBoxPosi.y = 200;

	if (ShowItemCraftMessageFlag || ShowItemAgingMessageFlag || ShowItemSmeltingMessageFlag || ShowItemManufactureMessageFlag || ShowItemOverSpace)
	{
		for (i = 0; i < CraftItemMessageSize.x; i++)
		{
			for (int j = 0; j < CraftItemMessageSize.y; j++)
			{
				if (i == 0 && j == 0)
					dsDrawTexImage(cItem.MatItemInfoBox_TopLeft, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (j == 0 && i != 0 && i + 1 < CraftItemMessageSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopCenter, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (j == 0 && i + 1 == CraftItemMessageSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopRight, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);

				if (i == 0 && j != 0 && j + 1 != CraftItemMessageSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Left, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (i != 0 && j != 0 && i + 1 != CraftItemMessageSize.x && j + 1 != CraftItemMessageSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Center, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (i + 1 == CraftItemMessageSize.x && j != 0 && j + 1 != CraftItemMessageSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Right, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);

				if (i == 0 && j + 1 == CraftItemMessageSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomLeft, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (i != 0 && j + 1 == CraftItemMessageSize.y && i + 1 != CraftItemMessageSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomCenter, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
				if (j + 1 == CraftItemMessageSize.y && i + 1 == CraftItemMessageSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomRight, CraftItemMessageBoxPosi.x + (i * 16), CraftItemMessageBoxPosi.y + (j * 16), 16, 16, 255);
			}
		}
	}
}

DWORD	dwTradeDelayTime = 0;
DWORD	dwTradeDelayTime2 = 0;
DWORD	dwTradeDelayTime3 = 0;
DWORD	dwTradeDelayTime4 = 0;

DWORD   dwCraftItemInfoDelayTime = 0;
DWORD   dwMixDelayTime = 0;
DWORD	dwMixItemColyTime = 0;
int		MixCancelButtonDelayFlag = 0;
DWORD   dwForceDelayTime = 0;

void cTRADE::Main()
{



	if (cCraftItem.ForceFlag)
	{
		if (MixItemNoCopyFlag)
		{
			dwForceDelayTime++;
			if (dwForceDelayTime > 70 * 5)
			{
				if (MixItemNoCopyFlag)MixItemNoCopyFlag = 0;
				dwForceDelayTime = 0;
			}
		}
		else dwForceDelayTime = 0;
	}



	if (CheckMixItemCopyFlag)
	{
		dwMixItemColyTime++;
		if (dwMixItemColyTime > 70 * 60 * 2)
		{
			dwMixItemColyTime = 0;
			CheckMixItemCopyFlag = 0;
		}
	}
	else
		dwMixItemColyTime = 0;


	if (MixCancelButtonDelayFlag)
	{
		dwMixDelayTime++;
		if (dwMixDelayTime > 70 * 10)
		{
			MixCancelButtonDelayFlag = 0;
			dwMixDelayTime = 0;
		}
	}
	else
	{
		dwMixDelayTime = 0;

	}


	cAging.CheckAgingData();
	int i, j = 0;
	CraftItemButtonIndex = 0;
	RequestTradeButtonFlag = 0;
	CloseWareHouseFlag = 0;
	TradeCheckFlag = 0;
	if (TradeRequestFlag)
	{
		if (pRealCursorPos.x >= TRADEBUTTONMAIN_X + 138 && pRealCursorPos.x <= TRADEBUTTONMAIN_X + 138 + 16 &&
			pRealCursorPos.y >= TRADEBUTTONMAIN_Y + 12 && pRealCursorPos.y <= TRADEBUTTONMAIN_Y + 12 + 16)
		{
			RequestTradeButtonFlag = 1;

		}
		if (pRealCursorPos.x >= TRADEBUTTONMAIN_X + 138 && pRealCursorPos.x <= TRADEBUTTONMAIN_X + 138 + 16 &&
			pRealCursorPos.y >= TRADEBUTTONMAIN_Y + 33 && pRealCursorPos.y <= TRADEBUTTONMAIN_Y + 33 + 16)
		{
			RequestTradeButtonFlag = 2;
		}
		dwTradeDelayTime3++;
		if (dwTradeDelayTime3 >= 70 * 10)
		{
			TradeRequestFlag = 0;
			dwTradeDelayTime3 = 0;

		}
	}

	if (OpenFlag)
	{



		if (pCursorPos.x >= DownTradePosi[T_CHECK_POSI][0] && pCursorPos.x <= DownTradePosi[T_CHECK_POSI][2] &&
			pCursorPos.y >= DownTradePosi[T_CHECK_POSI][1] && pCursorPos.y <= DownTradePosi[T_CHECK_POSI][3])
		{
			TradeCheckFlag = T_CHECK_POSI;
		}

		if (pCursorPos.x >= DownTradePosi[T_CLOSE_POSI][0] && pCursorPos.x <= DownTradePosi[T_CLOSE_POSI][2] &&
			pCursorPos.y >= DownTradePosi[T_CLOSE_POSI][1] && pCursorPos.y <= DownTradePosi[T_CLOSE_POSI][3])
		{
			TradeCheckFlag = T_CLOSE_POSI;
		}

		if (pCursorPos.x >= DownTradePosi[T_MONEY_POSI][0] + 10 && pCursorPos.x <= DownTradePosi[T_MONEY_POSI][2] + 10 &&
			pCursorPos.y >= DownTradePosi[T_MONEY_POSI][1] && pCursorPos.y <= DownTradePosi[T_MONEY_POSI][3])
		{
			TradeCheckFlag = T_MONEY_POSI;
		}

		PickUpTradeItem(pCursorPos.x, pCursorPos.y);
		if (MouseItem.Flag)
			SetTradeItemAreaCheck(&MouseItem);


		if (CheckDelayFlag)
		{
			dwTradeDelayTime++;
			if (dwTradeDelayTime >= 70 * 2)
			{
				CheckDelayFlag = 0;
				dwTradeDelayTime = 0;

			}


		}

		if (sTrade.CheckFlag && sTradeRecv.CheckFlag)
		{
			dwTradeDelayTime2++;
			if (dwTradeDelayTime2 >= 70 * 5)
			{
				dwTradeDelayTime2 = 0;
				sinCancelFlag = 1;

			}

		}
		else
			sinCancelFlag = 0;

		if (ItemPickUpFlag)
		{
			dwTradeDelayTime4++;
			if (dwTradeDelayTime4 > 70 * 2)
			{
				dwTradeDelayTime4 = 0;
				ItemPickUpFlag = 0;

			}
		}

	}


	if (cWareHouse.OpenFlag)
	{

		if (pCursorPos.x >= DownTradePosi[T_CLOSE_POSI][0] && pCursorPos.x <= DownTradePosi[T_CLOSE_POSI][2] &&
			pCursorPos.y >= DownTradePosi[T_CLOSE_POSI][1] && pCursorPos.y <= DownTradePosi[T_CLOSE_POSI][3])
		{
			CloseWareHouseFlag = 1;
		}
		cWareHouse.PickUpWareHouseItem(pCursorPos.x, pCursorPos.y);
		if (MouseItem.Flag)
		{
			cWareHouse.SetWareHouseItemAreaCheck(&MouseItem);

		}
		sWareHouse.BuyAreaCount = 10;
		sWareHouse.Weight[1] = (sWareHouse.BuyAreaCount * 100) + 2196;


		if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{
			for (i = 0; i < 10; i++)
			{
				CopyItemIndex7[i] = 0;

			}

			for (i = 0; i < 100; i++)
			{
				if (sWareHouse.WareHouseItem[i].Flag)
				{
					for (j = 0; j < 100; j++)
					{
						if (sWareHouse.WareHouseItem[j].Flag)
						{
							if (i == j)continue;
							if (CompareItems(&sWareHouse.WareHouseItem[i].sItemInfo, &sWareHouse.WareHouseItem[j].sItemInfo))
							{
								for (int k = 0; k < 10; k++)
								{
									if (!CopyItemIndex7[k])
									{
										CopyItemIndex7[k] = i + 1;
										CopyItemIndex7[k + 1] = j + 1;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag)
	{
		if (!MouseItem.Flag)
		{
			if (pCursorPos.x >= 158 && pCursorPos.x <= 158 + 26 &&
				pCursorPos.y >= 222 + sinInterHeight2 && pCursorPos.y <= 222 + 26 + sinInterHeight2)
			{
				if (!MixCancelButtonDelayFlag)
				{
					CraftItemButtonIndex = 1;
				}
			}

			if (pCursorPos.x >= DownTradePosi[T_CLOSE_POSI][0] && pCursorPos.x <= DownTradePosi[T_CLOSE_POSI][2] &&
				pCursorPos.y >= DownTradePosi[T_CLOSE_POSI][1] && pCursorPos.y <= DownTradePosi[T_CLOSE_POSI][3])
			{
				if (!MixCancelButtonDelayFlag)
				{
					CraftItemButtonIndex = 2;
				}
			}
			cCraftItem.PickUpCraftItem(pCursorPos.x, pCursorPos.y);
		}
		if (MouseItem.Flag)
		{
			if (cCraftItem.OpenFlag)
				cCraftItem.SetCraftItemAreaCheck(&MouseItem);

		}

	}

	if (cAging.OpenFlag)
	{
		if (MouseItem.Flag)
		{
			cAging.SetAgingItemAreaCheck(&MouseItem);
		}
		else
			cCraftItem.PickUpCraftItem(pCursorPos.x, pCursorPos.y, 0, 1);

	}

	if (SmeltingItem.OpenFlag)
	{
		if (MouseItem.Flag)
		{
			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinPR1 || (MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinPR2)
			{
				if (S_smeltingItem.SmeltingItem[0].Flag && S_smeltingItem.SmeltingItem[0].CODE != MouseItem.CODE)
				{
					return;
				}


				if (S_smeltingItem.SmeltingItem[0].Flag && S_smeltingItem.SmeltingItem[1].Flag && S_smeltingItem.SmeltingItem[2].Flag) return;

			}
			SmeltingItem.SetSmeltingItemAreaCheck(&MouseItem);
		}
		else
		{
			SmeltingItem.PickUpSmeltingItem(pCursorPos.x, pCursorPos.y);
		}
	}

	if (ManufactureItem.m_OpenFlag)
	{
		if (MouseItem.Flag)
		{
			ManufactureItem.SetManufactureItemAreaCheck(&MouseItem);
		}
		else
		{
			ManufactureItem.PickUpManufactureItem(pCursorPos.x, pCursorPos.y);
		}
	}


	if (cMixtureReset.OpenFlag)
	{
		if (MouseItem.Flag)
			cMixtureReset.SetMixtureItemResetAreaCheck(&MouseItem);
		else
			cMixtureReset.PickUpMixtureResetItem(pCursorPos.x, pCursorPos.y);
	}

	if (ShowItemCraftMessageFlag || ShowItemAgingMessageFlag || ShowItemSmeltingMessageFlag || ShowItemManufactureMessageFlag || ShowItemOverSpace)
	{
		dwCraftItemInfoDelayTime++;
		if (dwCraftItemInfoDelayTime >= 70 * 10)
		{
			ShowItemCraftMessageFlag = 0;
			ShowItemAgingMessageFlag = 0;
			dwCraftItemInfoDelayTime = 0;
			ShowItemSmeltingMessageFlag = 0;
			ShowItemManufactureMessageFlag = 0;
			ShowItemOverSpace = 0;

		}

	}

	if (cWareHouse.OpenFlag)
		CloseWareHouseCheckFlag2 = 1;


	if (!CloseWareHouseCheckFlag3 && !cWareHouse.OpenFlag && CloseWareHouseCheckFlag2 == 1)
	{
		cWareHouse.RestoreInvenItem();
		CloseWareHouseCheckFlag3 = 0;
		CloseWareHouseCheckFlag2 = 0;

	}

}

void cTRADE::Close()
{

}

void cTRADE::LButtonDown(int x, int y)
{
	if (LbuttonUpCheckFlag)return;

	int i, TempFlag = 0;
	if (TradeCheckFlag == T_CHECK_POSI)
	{
		if (!MouseItem.Flag)
		{
			if (!CheckDelayFlag)
			{
				if (!ItemPickUpFlag)
				{
					if (CheckTradeItemSet())
					{
						sTrade.CheckFlag = 1;
						SendTradeItem(TradeCharCode);
						CheckTradeButtonOk();
					}
				}
			}
		}
	}
	if (TradeCheckFlag == T_CLOSE_POSI)
	{
		if (!dwTradeMaskTime || sinCancelFlag)
		{
			SendRequestTrade(TradeCharCode, 3);
			cTrade.OpenFlag = 0;
			cInvenTory.OpenFlag = 0;
			CancelTradeItem();
			sinCancelFlag = 0;
		}

	}

	if (RequestTradeButtonFlag == 2)
	{

		TradeRequestFlag = 0;
		TradeCharCode = 0;
		dwTradeDelayTime3 = 0;

	}

	if (RequestTradeButtonFlag == 1)
	{
		if (!MouseItem.Flag)
		{

			if (GetTradeDistanceFromCode(TradeCharCode) == TRUE)
				SendRequestTrade(TradeCharCode, 1);
			TradeRequestFlag = 0;
			dwTradeDelayTime3 = 0;
		}
	}


	if (cTrade.OpenFlag)
	{
		if (MouseItem.Flag && !sTrade.CheckFlag)
		{
			cInvenTory.CheckRequireItemToSet(&MouseItem);
			if (TradeColorIndex == NO_BOX_COLOR || TradeColorIndex == NOT_SETTING_COLOR)return;
			if (!LastSetTradeItem(&MouseItem))
			{
			}
		}
		else
		{
			if (!TradeItemSucessFlag && !TradeSendSucessFlag && !sTrade.CheckFlag)
			{
				PickUpTradeItem(pCursorPos.x, pCursorPos.y, 1);
				if (TradeCheckFlag == T_MONEY_POSI && !sTrade.CheckFlag)
					cMessageBox.ShowMessage2(MESSAGE_MOVE_MONEY_TRADE);

			}

		}

	}


	if (CloseWareHouseFlag)
	{
		cWareHouse.CloseWareHouse();

	}
	if (cWareHouse.OpenFlag)
	{
		if (MouseItem.Flag)
		{

			cInvenTory.CheckRequireItemToSet(&MouseItem);
			if (TradeColorIndex == NO_BOX_COLOR || TradeColorIndex == NOT_SETTING_COLOR)return;
			if (!cWareHouse.ChangeWareHouseItem(&MouseItem))
				cWareHouse.LastSetWareHouseItem(&MouseItem);

		}
		else
			cWareHouse.PickUpWareHouseItem(pCursorPos.x, pCursorPos.y, 1);

		if (pCursorPos.x >= 231 && pCursorPos.x <= 231 + 20 &&
			pCursorPos.y >= 213 + sinInterHeight2 && pCursorPos.y <= 213 + 20 + sinInterHeight2)
		{
			cMessageBox.ShowMessage2(MESSAGE_MOVE_MONEY_RECV);
		}


	}

	int CloseButtonFlag = 0;
	int SheltomCount = 0;
	if (cCraftItem.OpenFlag)
	{
		if (MouseItem.Flag)
		{

			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinPM1 || (MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinPL1 ||
				(MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinPS1 || (MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinWR1 ||
				(MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinDR1 || (MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinGP1 ||
				(MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinCH1 ||




				(MouseItem.sItemInfo.CODE == (sinDA1 | sin31)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin31)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin32)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin32)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin33)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin33)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin34)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin34)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin35)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin35)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin36)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin36)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin37)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin37)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin38)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin38)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin39)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin39)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin40)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin40)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin41)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin41)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin42)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin42)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin43)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin43)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin44)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin44)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin45)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin45)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin46)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin46)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin48)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin48)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin54)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin54)) ||
				(MouseItem.sItemInfo.CODE == (sinDA1 | sin55)) || (MouseItem.sItemInfo.CODE == (sinDA2 | sin55)) ||
				(MouseItem.sItemInfo.CODE == (sinDB1 | sin33)) ||
				(MouseItem.sItemInfo.CODE == (sinOA2 | sin33)) ||
				(MouseItem.sItemInfo.CODE == (sinDB1 | sin34)) ||
				(MouseItem.sItemInfo.CODE == (sinOA2 | sin34)))

			{
				TradeColorIndex = NOT_SETTING_COLOR;
			}



			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinOR2)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin06 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin07 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin08 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin09 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin10 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin11 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin12 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin13 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin14 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin15 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin16 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin17 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin18 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin19 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin20 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin21 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin22 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin23 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin24 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin25 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin27 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin28 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin29 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin30 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin31 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin32 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin34 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin35)

					TradeColorIndex = NOT_SETTING_COLOR;
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinOA1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin32 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin33 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin34 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin35 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin38)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
				}
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinSP1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin34)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
				}
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinSP1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin15)
					TradeColorIndex = NOT_SETTING_COLOR;
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinSP1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin35)
					TradeColorIndex = NOT_SETTING_COLOR;
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinOR2)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin33)
					TradeColorIndex = NOT_SETTING_COLOR;
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinSP1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin27 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin28 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin29 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin30 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin31 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin32 ||
					(MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin33)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
				}
			}


			if (!cCraftItem.ForceFlag)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinOS1)
				{
					if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) >= sin21 && (MouseItem.sItemInfo.CODE & sinITEM_MASK3) <= sin34)
					{
						TradeColorIndex = NOT_SETTING_COLOR;
					}
				}
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinOA1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin36)
					TradeColorIndex = NOT_SETTING_COLOR;
			}



			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinSP1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin36)
					TradeColorIndex = NOT_SETTING_COLOR;
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinOA1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin37)
					TradeColorIndex = NOT_SETTING_COLOR;
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinSP1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin37 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin38)
					TradeColorIndex = NOT_SETTING_COLOR;
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinSP1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin39 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin42)
					TradeColorIndex = NOT_SETTING_COLOR;
			}


			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinGF1)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin07 || (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin08)
					TradeColorIndex = NOT_SETTING_COLOR;
			}




			if (!sCraftItem.CraftItem[0].Flag)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinSE1)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_RECONITEM);
					TradeColorIndex = NOT_SETTING_COLOR;
				}
			}
			if (TradeColorIndex != NO_BOX_COLOR || TradeColorIndex != NOT_SETTING_COLOR)
			{
				if (MouseItem.sItemInfo.ItemKindCode == ITEM_KIND_AGING || MouseItem.sItemInfo.ItemKindCode == ITEM_KIND_CRAFT || MouseItem.sItemInfo.UniqueItem)
				{
					if (!cCraftItem.ForceFlag)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_CRAFT_ITEM);
					}
				}
				else
				{

					if (TradeColorIndex == NOT_ENOUGH_MONEY)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
						return;

					}
					cInvenTory.CheckRequireItemToSet(&MouseItem);

					if (MouseItem.sItemInfo.CODE == (sinBI1 | sin90))
					{
						if (159 + 11 <= MouseItem.x + 22 && 159 + 11 > MouseItem.x && 268 + 11 + sinInterHeight2 < MouseItem.y + 22 && 268 + 11 + sinInterHeight2 > MouseItem.y)
						{
							TradeColorIndex = SET_ITEM_CHECK_COLOR;
						}
					}
					if (TradeColorIndex == NO_BOX_COLOR || TradeColorIndex == NOT_SETTING_COLOR)return;
					cCraftItem.LastSetCraftItem(&MouseItem);
				}
			}
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag && !CheckMixItemCopyFlag)
			{
				if (!sinCraftItemStartFlag2 && !MixItemNoCopyFlag)
				{
					cCraftItem.PickUpCraftItem(pCursorPos.x, pCursorPos.y, 1);
				}
				if (CraftItemButtonIndex == 2)
				{

					SheltomCount = 0;

					if (sCraftItem.CraftItem[0].Flag)
					{
						for (i = 0; i < sCraftItem.CraftItem[0].h / 22; i++)
						{
							SheltomCount += sCraftItem.CraftItem[0].w / 22;
						}
						if (!cCraftItem.CraftCheckEmptyArea(&sCraftItem.CraftItem[0]))
							SheltomCount = 100;

					}
					for (i = 1; i < 15; i++)
					{
						if (sCraftItem.CraftItem[i].Flag)
						{
							if (cCraftItem.CraftCheckEmptyArea(&sCraftItem.CraftItem[i]))
							{
								CloseButtonFlag = 0;
							}
							else
							{
								CloseButtonFlag = 1;
								break;
							}
							SheltomCount++;
						}
					}

					if (!CloseButtonFlag && SheltomCount <= cCraftItem.GetCraftCheckEmptyArea())
					{
						cCraftItem.CancelMixItem();
					}
					else
					{
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
					}
				}
				if (CraftItemButtonIndex == 1)
				{
					if (cCraftItem.ForceFlag)
					{
						SheltomCount = 0;
						for (i = 1; i < 15; i++)
						{
							if (sCraftItem.CraftItem[i].Flag)
								SheltomCount++;
						}
						if (SheltomCount <= cCraftItem.GetCraftCheckEmptyArea())
						{
							cCraftItem.sinSendCraftItem();
						}
						else
							cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
					}

					else if (cCraftItem.haCheckReconItem())
					{
						if (sCraftItem.CraftItem[0].Flag && !sCraftItem.CraftItem[0].sItemInfo.ItemKindCode)
						{
							for (i = 1; i < 15; i++)
							{
								if (sCraftItem.CraftItem[i].Flag)
								{
									CopyMixItemCheckDelete(&sCraftItem.CraftItem[i - 1]);
								}
							}

							if (cCraftItem.CraftCheckEmptyArea(&sCraftItem.CraftItem[0]))
							{
								if (!sinCraftItemStartFlag2)
								{
									sinCraftItemStartFlag = 1;
									SetInterEffectAging();

								}
							}
							else
							{
								cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
							}

						}
					}

					else
					{
						if (sCraftItem.CraftItem[0].Flag && !sCraftItem.CraftItem[0].sItemInfo.ItemKindCode)
						{

							for (i = 1; i < 15; i++)
							{
								if (sCraftItem.CraftItem[i].Flag)
								{
									CopyMixItemCheckDelete(&sCraftItem.CraftItem[i - 1]);
								}
							}
							for (i = 1; i < 15; i++)
							{
								if (sCraftItem.CraftItem[i].Flag)
								{
									if (cCraftItem.CraftCheckEmptyArea(&sCraftItem.CraftItem[0]) && !sCraftItem.CraftItem[14].Flag)
									{

										if (!sinCraftItemStartFlag2)
										{
											sinCraftItemStartFlag = 1;
											SetInterEffectAging();
											TempFlag = 1;
											MixCancelButtonDelayFlag = 1;
											CheckMixItemCopyFlag = 1;

										}

									}
									else
									{
										if (sCraftItem.CraftItem[14].Flag)
										{
											cMessageBox.ShowMessage(MESSAGE_CANNOT_RECONITEM);
										}
										else
											cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);

										TempFlag = 1;
									}

								}
							}
							if (!TempFlag)
								cMessageBox.ShowMessage(MESSAGE_NOT_CRAFT_ITEM);

						}
						else
						{
							cMessageBox.ShowMessage(MESSAGE_NOT_CRAFT_ITEM);
						}
					}
				}
			}
		}
	}


	if (cMixtureReset.OpenFlag)
	{
		if (MouseItem.Flag)
		{

			if (!sMixtureResetItem.MixtureResetItem[0].Flag)
			{
				if ((MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin89)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_STONE);
					TradeColorIndex = NOT_SETTING_COLOR;
				}
			}


			if (TradeColorIndex != NO_BOX_COLOR && TradeColorIndex != NOT_SETTING_COLOR)
			{
				if ((MouseItem.CODE & sinITEM_MASK2) == sinBI1 && (MouseItem.sItemInfo.CODE & sinITEM_MASK3) == sin89)
				{
					cMixtureReset.LastSetMixtureResetItem(&MouseItem, 1);
					MixtureResetCheckFlag = 1;
				}
				else if ((MouseItem.sItemInfo.ItemKindCode == ITEM_KIND_CRAFT) || (MouseItem.sItemInfo.ItemKindCode == ITEM_KIND_AGING))
					cMixtureReset.LastSetMixtureResetItem(&MouseItem, 2);
			}
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag)
			{
				if (!sinCraftItemStartFlag2)
					cMixtureReset.PickUpMixtureResetItem(pCursorPos.x, pCursorPos.y, 1);

				if (CraftItemButtonIndex == 2)
				{

					CloseButtonFlag = 0;
					if (sMixtureResetItem.MixtureResetItem[1].Flag)
						CloseButtonFlag = 1;

					if (CloseButtonFlag == 1)
						cMessageBox.ShowMessage(MESSAGE_NOT_CANCEL_RESET);
					else
					{
						if (sMixtureResetItem.MixtureResetItem[0].Flag)
						{
							if (!cCraftItem.CraftCheckEmptyArea(&sMixtureResetItem.MixtureResetItem[0]))
							{

								int LineCount = 0, Temp;
								ShowItemOverSpace = 1;
								strcpy_s(szCraftItemBuff, "°ø°£À» È®º¸ÇØ ÁÖ¼¼¿ä");

								strcat(szCraftItemBuff, "\r");
								Temp = lstrlen(szCraftItemBuff);
								for (i = 0; i < Temp; i++)
								{
									if (szCraftItemBuff[i] == '\r')
									{
										LineCount++;
									}
								}
								CraftItemMessageSize.x = 14;
								CraftItemMessageSize.y = ((LineCount) * 2) + 2;
								sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
							}
							else
								cMixtureReset.CancelMixtureItemReset();
						}
						else
							cMixtureReset.CancelMixtureItemReset();
					}
				}


				if (CraftItemButtonIndex == 1 && sMixtureResetItem.MixtureResetItem[1].Flag)
				{
					if (cCraftItem.CraftCheckEmptyArea(&sMixtureResetItem.MixtureResetItem[0]))
					{
						if (!sinCraftItemStartFlag2)
						{
							sinCraftItemStartFlag = 1;
							SetInterEffectMixtureReset();
							MixCancelButtonDelayFlag = 1;
							MixtureResetCheckFlag = 0;
						}
					}
					else
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
				}
			}
		}
	}

	if (cAging.OpenFlag)
	{
		if (MouseItem.Flag)
		{
			if (TradeColorIndex == NOT_AGING_ITEM)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_AGING_ITEM);
			}
			else
			{

				if (TradeColorIndex == NOT_ENOUGH_MONEY)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);

				}
				if (TradeColorIndex != NO_BOX_COLOR && TradeColorIndex != NOT_SETTING_COLOR && TradeColorIndex != NOT_ENOUGH_MONEY)
				{
					if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
						(MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinMA2)
					{
						cCraftItem.LastSetCraftItem(&MouseItem, 2);
						sinMakeItemCheck();

					}
					else if (MouseItem.sItemInfo.CODE == (sinBI1 | sin10) || MouseItem.sItemInfo.CODE == (sinBI1 | sin11) ||
						MouseItem.sItemInfo.CODE == (sinBI1 | sin60) || MouseItem.sItemInfo.CODE == (sinBI1 | sin61) ||
						MouseItem.sItemInfo.CODE == (sinBI1 | sin85))
					{
						if (!StartInterEffectAging2 && !sinCraftItemStartFlag)
							cCraftItem.LastSetCraftItem(&MouseItem, 3);
					}
					else
					{
						cCraftItem.LastSetCraftItem(&MouseItem, 1);
						cAging.CheckItem(&MouseItem);
					}
				}
			}
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag)
			{
				if (!sinCraftItemStartFlag2)
				{

					cCraftItem.PickUpCraftItem(pCursorPos.x, pCursorPos.y, 1, 1);

				}
				if (CraftItemButtonIndex == 2)
				{


					CloseButtonFlag = 0;
					for (int i = 1; i < 15; i++)
					{
						if (sAgingItem.AgingItem[i].Flag)
						{
							CloseButtonFlag = 1;
							break;
						}
					}
					if (CloseButtonFlag == 1)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_AGINGSHELTOM);

					}
					else
					{
						if (sAgingItem.AgingItem[0].Flag)
						{
							if (!cCraftItem.CraftCheckEmptyArea(&sAgingItem.AgingItem[0]))
							{


								int LineCount = 0, Temp;
								ShowItemOverSpace = 1;
								strcpy_s(szCraftItemBuff, InvenSpaceSecure);

								strcat(szCraftItemBuff, "\r");
								Temp = lstrlen(szCraftItemBuff);
								for (int j = 0; j < Temp; j++)
								{
									if (szCraftItemBuff[j] == '\r')
									{
										LineCount++;
									}
								}
								CraftItemMessageSize.x = 14;
								CraftItemMessageSize.y = ((LineCount) * 2) + 2;
								sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
							}
							else
							{
								cAging.CancelAgingItem();
							}
						}
						else
							cAging.CancelAgingItem();

					}
				}



				if (CraftItemButtonIndex == 1 && AgingCheckSheltomFlag)
				{
					if (cCraftItem.CraftCheckEmptyArea(&sAgingItem.AgingItem[0]))
					{
						if (!sinCraftItemStartFlag2)
						{

							sinCraftItemStartFlag = 1;
							SetInterEffectAging();
							MixCancelButtonDelayFlag = 1;
						}
					}
					else
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
				}

			}
		}

	}


	if (SmeltingItem.OpenFlag)
	{
		if (MouseItem.Flag)
		{
			if (TradeColorIndex == NO_BOX_COLOR || TradeColorIndex == NOT_SETTING_COLOR)
			{
				return;
			}
			if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinPR1 || (MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinPR2)
			{
				if (S_smeltingItem.SmeltingItem[0].Flag && S_smeltingItem.SmeltingItem[0].CODE != MouseItem.CODE)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_SAME_SMELTINGITEM);
					return;
				}


				if (S_smeltingItem.SmeltingItem[0].Flag && S_smeltingItem.SmeltingItem[1].Flag && S_smeltingItem.SmeltingItem[2].Flag) return;

			}
			if (TradeColorIndex == NOT_ENOUGH_MONEY)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				return;

			}
			SmeltingItem.LastSetSmeltingItem(&MouseItem);
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag && !CheckMixItemCopyFlag)
			{
				if (!sinCraftItemStartFlag2 && !MixCancelButtonDelayFlag)
				{
					SmeltingItem.PickUpSmeltingItem(pCursorPos.x, pCursorPos.y, 1);
				}

				if (CraftItemButtonIndex == 2)
				{
					for (i = 0; i < 5; i++)
					{
						if (S_smeltingItem.SmeltingItem[i].Flag)
						{
							if (SmeltingItem.SmeltingCheckEmptyArea(&S_smeltingItem.SmeltingItem[i]))
							{
								CloseButtonFlag = 0;
							}
							else
							{
								CloseButtonFlag = 1;
								break;
							}
							SheltomCount++;
						}

					}
					if (!CloseButtonFlag && SheltomCount <= SmeltingItem.GetSmeltingCheckEmptyArea())
					{
						SmeltingItem.CancelSmeltingItem();
					}
					else
					{

						int LineCount = 0, Temp;
						ShowItemOverSpace = 1;
						strcpy_s(szCraftItemBuff, InvenSpaceSecure);

						strcat(szCraftItemBuff, "\r");
						Temp = lstrlen(szCraftItemBuff);
						for (i = 0; i < Temp; i++)
						{
							if (szCraftItemBuff[i] == '\r')
							{
								LineCount++;
							}
						}
						CraftItemMessageSize.x = 14;
						CraftItemMessageSize.y = ((LineCount) * 2) + 2;
						sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
					}
				}


				else if (CraftItemButtonIndex == 1)
				{
					if (S_smeltingItem.SmeltingItem[0].Flag && !S_smeltingItem.SmeltingItem[0].sItemInfo.ItemKindCode &&
						S_smeltingItem.SmeltingItem[1].Flag && !S_smeltingItem.SmeltingItem[1].sItemInfo.ItemKindCode &&
						S_smeltingItem.SmeltingItem[2].Flag && !S_smeltingItem.SmeltingItem[2].sItemInfo.ItemKindCode)
					{

						sITEM temp;
						for (int i = 0; i < MAX_ITEM; i++)
						{
							if (sItem[i].CODE == (sinPR1 | sin01))
							{
								temp = sItem[i];
								if (cInvenTory.CheckInvenEmpty(&temp))
								{
									if (S_smeltingItem.SmeltingItem[4].Flag)
									{
										if (!sinCraftItemStartFlag2)
										{
											sinCraftItemStartFlag = 1;
											SetInterEffectSmelting();
											MixCancelButtonDelayFlag = 1;
										}
									}
								}
								else
								{
									cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
								}
								break;
							}
						}
					}
				}
			}
		}
	}


	if (ManufactureItem.m_OpenFlag)
	{
		if (MouseItem.Flag)
		{
			if (TradeColorIndex == NOT_SETTING_COLOR)
			{
				return;
			}
			else if (TradeColorIndex == NO_BOX_COLOR)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_NEED_RUNE);
				return;
			}
			else if (TradeColorIndex == NOT_ENOUGH_MONEY)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				return;
			}
			ManufactureItem.LastSetManufactureItem(&MouseItem);
		}
		else
		{
			if (!StartInterEffectAging2 && !sinCraftItemStartFlag && !CheckMixItemCopyFlag)
			{
				if (!sinCraftItemStartFlag2 && !MixCancelButtonDelayFlag)
				{
					ManufactureItem.PickUpManufactureItem(pCursorPos.x, pCursorPos.y, 1);
				}

				if (CraftItemButtonIndex == 2)
				{
					CloseButtonFlag = 0;
					for (i = 0; i < 4; i++)
					{
						if (g_sManufactureItem.ManufactureItem[i].Flag)
						{
							if (ManufactureItem.ManufactureCheckEmptyArea(&g_sManufactureItem.ManufactureItem[i]))
							{
								CloseButtonFlag = 0;
							}
							else
							{
								CloseButtonFlag = 1;
								break;
							}
							SheltomCount++;
						}
					}
					if (!CloseButtonFlag && SheltomCount <= ManufactureItem.GetManufactureCheckEmptyArea())
					{
						ManufactureItem.CancelManufactureItem();
					}
					else
					{

						int LineCount = 0, Temp;
						ShowItemOverSpace = 1;
						strcpy_s(szCraftItemBuff, InvenSpaceSecure);

						strcat(szCraftItemBuff, "\r");
						Temp = lstrlen(szCraftItemBuff);
						for (i = 0; i < Temp; i++)
						{
							if (szCraftItemBuff[i] == '\r')
							{
								LineCount++;
							}
						}
						CraftItemMessageSize.x = 14;
						CraftItemMessageSize.y = ((LineCount) * 2) + 2;
						sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
					}
				}
				else if (CraftItemButtonIndex == 1)
				{
					if (g_sManufactureItem.ManufactureItem[0].Flag && !g_sManufactureItem.ManufactureItem[0].sItemInfo.ItemKindCode)
					{
						if (g_sManufactureItem.ManufactureItem[1].Flag && g_sManufactureItem.ManufactureItem[2].Flag && g_sManufactureItem.ManufactureItem[3].Flag)
						{
							SManufacture_ResultItemInfo ResultItem;
							memset(&ResultItem, 0, sizeof(SManufacture_ResultItemInfo));
							sITEM temp;
							ResultItem = ManufactureItem.ManufactureCheckItem(g_sManufactureItem.ManufactureItem, sinChar);
							for (int cnt = 0; cnt < MAX_ITEM; cnt++)
							{
								if (sItem[cnt].CODE == ResultItem.ItemCode)
								{
									temp = sItem[cnt];
									if (cInvenTory.CheckInvenEmpty(&temp))
									{
										if (sinChar->Weight[0] + ResultItem.Weight <= sinChar->Weight[1])
										{
											if (ForceItemPrice2 <= sinChar->Money)
											{
												if (!sinCraftItemStartFlag2)
												{
													cMessageBox.ShowMessage3(MESSAGE_MANUFACTURE, ResultItem.ItemName);


												}
											}
											else
											{
												cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
											}
										}
										else
										{
											cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);

										}
									}
									else
									{
										cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);

									}
									break;
								}
							}
						}
					}
				}
			}
		}
	}

}

void cTRADE::LButtonUp(int x, int y)
{

}

void cTRADE::RButtonDown(int x, int y)
{

}

void cTRADE::RButtonUp(int x, int y)
{

}

void cTRADE::KeyDown()
{

}


void cTRADE::DrawTradeText()
{

	if (ShowItemAgingMessageFlag || ShowItemCraftMessageFlag || TradeRequestFlag || ShowItemSmeltingMessageFlag || ShowItemManufactureMessageFlag || ShowItemOverSpace || sinMoveKindInter[SIN_TRADE] ||
		sinMoveKindInter[SIN_CRAFTITEM] || sinMoveKindInter[SIN_WAREHOUSE] || sinMoveKindInter[SIN_AGING] || sinMoveKindInter[SIN_SMELTING] || sinMoveKindInter[SIN_MANUFACTURE])
	{


		int i;
		HDC	hdc = NULL;

		char strBuff[128];

		memset(strBuff, 0, sizeof(strBuff));
		//renderDevice.lpDDSBack->GetDC(&hdc);
		SelectObject(hdc, sinFont);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));

		if (TradeRequestFlag)
		{
			if (cTrade.szTradeCharName[0])
			{
				strcpy_s(strBuff, cTrade.szTradeCharName);
				dsTextLineOut(hdc, TRADEBUTTONMAIN_X + 38, TRADEBUTTONMAIN_Y + 17, strBuff, lstrlen(strBuff));

			}

		}

		if (cWareHouse.OpenFlag)
		{
			memset(strBuff, 0, sizeof(strBuff));
			NumLineComa(sWareHouse.Money - 2023, strBuff);

			dsTextLineOut(hdc, CheckEditSize(ShopGoldEdit[0][0], ShopGoldEdit[0][2], strBuff) - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), ShopGoldEdit[0][1],
				strBuff, lstrlen(strBuff));

			memset(strBuff, 0, sizeof(strBuff));
			wsprintf(strBuff, "%d/%d", sWareHouse.Weight[0] - 500, sWareHouse.Weight[1] - 499);
			dsTextLineOut(hdc, CheckEditSize(ShopGoldEdit[1][0], ShopGoldEdit[1][2], strBuff) - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), ShopGoldEdit[1][1],
				strBuff, lstrlen(strBuff));

			for (i = 0; i < 100; i++)
			{
				if (sWareHouse.WareHouseItem[i].Flag)
				{
					if (sWareHouse.WareHouseItem[i].Class == ITEM_CLASS_POTION)
					{
						wsprintf(strBuff, "%d", sWareHouse.WareHouseItem[i].sItemInfo.PotionCount);
						dsTextLineOut(hdc, sWareHouse.WareHouseItem[i].x - (256 + 128 - sinMoveKindInter[SIN_WAREHOUSE]), sWareHouse.WareHouseItem[i].y, strBuff, lstrlen(strBuff));
					}
				}
			}
		}

		if (OpenFlag)
		{

			strcpy_s(strBuff, cTrade.szTradeCharName);
			dsTextLineOut(hdc, CheckEditSize(229, 332, strBuff) - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
				94, strBuff, lstrlen(strBuff));

			if (sTradeRecv.Weight > 0)
			{
				wsprintf(strBuff, "%d", sTradeRecv.Weight);
				dsTextLineOut(hdc, CheckEditSize(251, 326, strBuff) - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
					152, strBuff, lstrlen(strBuff));
			}

			if (sTradeRecv.Money > 0)
			{
				memset(strBuff, 0, sizeof(strBuff));
				NumLineComa(sTradeRecv.Money - 193, strBuff);

				dsTextLineOut(hdc, CheckEditSize(251, 326, strBuff) - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
					127, strBuff, lstrlen(strBuff));
			}




			memset(strBuff, 0, sizeof(strBuff));
			wsprintf(strBuff, "%d", sTrade.Weight);
			dsTextLineOut(hdc, CheckEditSize(DownTradePosi[T_WEIGHT_TEXT_POSI][0], DownTradePosi[T_WEIGHT_TEXT_POSI][2], strBuff) - 2 - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
				DownTradePosi[T_WEIGHT_TEXT_POSI][1] + 5 + 2, strBuff, lstrlen(strBuff));

			memset(strBuff, 0, sizeof(strBuff));
			NumLineComa(TempShowMoney, strBuff);

			dsTextLineOut(hdc, CheckEditSize(DownTradePosi[T_MONEY_TEXT_POSI][0], DownTradePosi[T_MONEY_TEXT_POSI][2], strBuff) - 2 - (256 + 128 - sinMoveKindInter[SIN_TRADE]),
				DownTradePosi[T_MONEY_TEXT_POSI][1] + 5 + 2 + 2, strBuff, lstrlen(strBuff));



			for (int i = 0; i < MAX_TRADE_ITEM; i++)
			{
				if (sTrade.TradeItem[i].Flag)
				{
					if (sTrade.TradeItem[i].Class == ITEM_CLASS_POTION)
					{
						wsprintf(strBuff, "%d", sTrade.TradeItem[i].sItemInfo.PotionCount);
						dsTextLineOut(hdc, sTrade.TradeItem[i].x - (256 + 128 - sinMoveKindInter[SIN_TRADE]), sTrade.TradeItem[i].y, strBuff, lstrlen(strBuff));

					}
				}
				if (sTradeRecv.TradeItem[i].Flag)
				{
					if (sTradeRecv.TradeItem[i].Class == ITEM_CLASS_POTION)
					{
						wsprintf(strBuff, "%d", sTradeRecv.TradeItem[i].sItemInfo.PotionCount);
						dsTextLineOut(hdc, sTradeRecv.TradeItem[i].x - (256 + 128 - sinMoveKindInter[SIN_TRADE]), sTradeRecv.TradeItem[i].y - T_REVISION_Y, strBuff, lstrlen(strBuff));

					}
				}
			}
		}


		char szMoneyTemp[256];
		char szRate[256];

		if (sAgingItem.AgingItem[0].Flag)
		{


#ifdef AGING_MONEY_FREE
#ifdef HASIEGE_MODE

			wsprintf(szMoneyTemp, "%d", 0);
#else
			wsprintf(szMoneyTemp, "%d", 0);
#endif
#else
#ifdef HASIEGE_MODE

			wsprintf(szMoneyTemp, "%d", cShop.haShopItemPrice((sAgingItem.AgingItem[0].sItemInfo.Price + (sAgingItem.AgingItem[0].sItemInfo.Price*sAgingItem.AgingItem[0].sItemInfo.ItemAgingNum[0])) / 2));
#else
			wsprintf(szMoneyTemp, "%d", (sAgingItem.AgingItem[0].sItemInfo.Price + (sAgingItem.AgingItem[0].sItemInfo.Price*sAgingItem.AgingItem[0].sItemInfo.ItemAgingNum[0])) / 2);
#endif
#endif	
			if (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0] <= 12)
			{
				wsprintf(szRate, "Chance de Sucesso: 100%");
			}
			else
			{
				switch (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0])
				{
				case 13:
					wsprintf(szRate, "Chance de Sucesso: 90 %");
					break;
				case 14:
					wsprintf(szRate, "Chance de Sucesso: 78 %");
					break;
				case 15:
					wsprintf(szRate, "Chance de Sucesso: 74 %");
					break;
				case 16:
					wsprintf(szRate, "Chance de Sucesso: 52 %");
					break;
				case 17:
					wsprintf(szRate, "Chance de Sucesso: 44 %");
					break;
				case 18:
					wsprintf(szRate, "Chance de Sucesso: 28 %");
					break;
				case 19:
					wsprintf(szRate, "Chance de Sucesso: 20 %");
					break;
				}
			}

			dsTextLineOut(hdc, CheckEditSize(200, 275, szMoneyTemp), 323 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp));
			dsTextLineOut(CheckEditSize(200, 275, szRate), 318 + sinInterHeight2, szRate, lstrlen(szRate));

		}


		if (sCraftItem.CraftItem[0].Flag)
		{

#ifdef HASIEGE_MODE

			wsprintf(szMoneyTemp, "%d", cShop.haShopItemPrice(sCraftItem.CraftItem[0].sItemInfo.Price));
#else
			wsprintf(szMoneyTemp, "%d", sCraftItem.CraftItem[0].sItemInfo.Price);
#endif

			dsTextLineOut(hdc, CheckEditSize(200, 325, szMoneyTemp), 322 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp));

		}


		if (cCraftItem.ForceFlag)
		{

#ifdef HASIEGE_MODE

			wsprintf(szMoneyTemp, "%d", cShop.haShopItemPrice(ForceItemPrice2));
#else
			wsprintf(szMoneyTemp, "%d", ForceItemPrice2);
#endif

			dsTextLineOut(hdc, CheckEditSize(200, 325, szMoneyTemp) - (256 + 128 - sinMoveKindInter[SIN_CRAFTITEM]), 322 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp));

		}


		if (S_smeltingItem.SmeltingItem[0].Flag)
		{



			wsprintf(szMoneyTemp, "%d", ForceItemPrice2);

			dsTextLineOut(hdc, CheckEditSize(200, 325, szMoneyTemp), 322 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp));
		}

		if (g_sManufactureItem.ManufactureItem[0].Flag)
		{



			wsprintf(szMoneyTemp, "%d", ForceItemPrice2);

			dsTextLineOut(hdc, CheckEditSize(200, 325, szMoneyTemp), 322 + sinInterHeight2, szMoneyTemp, lstrlen(szMoneyTemp));
		}



		char *pCraftItemInfo[10];

		int len, Templen = 0, Textlen = 0;
		int Count = 0;
		int SetTextXposi = 0;
		char TempszCraftItemBuff[128];


		strcpy_s(TempszCraftItemBuff, szCraftItemBuff);

		if (ShowItemCraftMessageFlag || ShowItemAgingMessageFlag || ShowItemSmeltingMessageFlag || ShowItemManufactureMessageFlag || ShowItemOverSpace)
		{
			SetTextColor(hdc, RGB(222, 231, 255));
			SelectObject(hdc, sinBoldFont);
			SetBkMode(hdc, TRANSPARENT);
			if (ShowItemCraftMessageFlag)
				dsTextLineOut(hdc, CraftItemMessageBoxPosi.x + 53, CraftItemMessageBoxPosi.y + 13, MixResultTitle, lstrlen(MixResultTitle));


			if (ShowItemSmeltingMessageFlag)
			{
				dsTextLineOut(hdc, CraftItemMessageBoxPosi.x + 53, CraftItemMessageBoxPosi.y + 13, SmeltingResultTitle, lstrlen(SmeltingResultTitle));
			}

			if (ShowItemManufactureMessageFlag)
			{
				dsTextLineOut(hdc, CraftItemMessageBoxPosi.x + 53, CraftItemMessageBoxPosi.y + 13, ManufactureResultTitle, lstrlen(ManufactureResultTitle));
			}

			if (ShowItemOverSpace)
			{
				dsTextLineOut(hdc, CraftItemMessageBoxPosi.x + 53, CraftItemMessageBoxPosi.y + 13, InventoryFull, lstrlen("InventoryFull"));
			}
			SelectObject(hdc, sinFont);
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255, 255, 255));

			len = lstrlen(TempszCraftItemBuff);
			for (i = 0; i < len; i++)
			{
				if (TempszCraftItemBuff[i] == '\r')
				{
					pCraftItemInfo[Count] = &TempszCraftItemBuff[Templen];
					TempszCraftItemBuff[i] = 0;
					Templen = i + 1;
					Textlen = lstrlen(pCraftItemInfo[Count]);

					SetTextXposi = ((CraftItemMessageBoxPosi.x + ((CraftItemMessageSize.x * 16) / 2)) - ((Textlen / 2) * 11));
					if (Textlen <= 12)
						SetTextXposi -= 6;

					dsTextLineOut(hdc, SetTextXposi + 27, CraftItemMessageBoxPosi.y + 38 + ((Count) * 18), pCraftItemInfo[Count], Textlen);
					Count++;
				}

			}


		}


		//renderDevice.lpDDSBack->ReleaseDC(hdc);
	}

}




int cTRADE::SetTradeItemAreaCheck(sITEM *pItem)
{

	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	InitTradeColorRect();

	TradeStartX = DownTradePosi[T_SET_BOX][0];
	TradeStartY = DownTradePosi[T_SET_BOX][1];
	TradeEndX = DownTradePosi[T_SET_BOX][2];
	TradeEndY = DownTradePosi[T_SET_BOX][3];

	for (i = pItem->x + 11; i < pItem->x + pItem->w; i += 22)
	{
		for (j = pItem->y + 11; j < pItem->y + pItem->h; j += 22)
		{
			if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
			{
				TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
				TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
				TradeColorRect.right = pItem->w;
				TradeColorRect.bottom = pItem->h;
				if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
				{
					InitTradeColorRect();
					return FALSE;
				}

				pItem->SetX = TradeColorRect.left;
				pItem->SetY = TradeColorRect.top;
				pItem->ItemPosition = 0;
				TradeColorIndex = SET_ITEM_CHECK_COLOR;

				if (TradeCrashItemIndex[0] = CrashTradeItem(TradeColorRect))
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}


				if (pItem->sItemInfo.SpecialItemFlag[0] == CHECK_COPY_ITEM ||
					pItem->sItemInfo.SpecialItemFlag[0] == CHECK_GIVE_ITEM ||
					pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST ||
					(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
					(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA2 ||
					(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinQW1 ||

					(pItem->sItemInfo.CODE == (sinDA1 | sin31)) ||
					(pItem->sItemInfo.CODE == (sinDA2 | sin31)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin32)) ||
					(pItem->sItemInfo.CODE == (sinDA2 | sin32)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin33)) ||
					(pItem->sItemInfo.CODE == (sinDA2 | sin33)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin34)) || (pItem->sItemInfo.CODE == (sinDA2 | sin34)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin35)) || (pItem->sItemInfo.CODE == (sinDA2 | sin35)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin36)) || (pItem->sItemInfo.CODE == (sinDA2 | sin36)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin37)) || (pItem->sItemInfo.CODE == (sinDA2 | sin37)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin38)) || (pItem->sItemInfo.CODE == (sinDA2 | sin38)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin39)) || (pItem->sItemInfo.CODE == (sinDA2 | sin39)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin40)) || (pItem->sItemInfo.CODE == (sinDA2 | sin40)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin41)) || (pItem->sItemInfo.CODE == (sinDA2 | sin41)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin42)) || (pItem->sItemInfo.CODE == (sinDA2 | sin42)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin43)) || (pItem->sItemInfo.CODE == (sinDA2 | sin43)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin44)) || (pItem->sItemInfo.CODE == (sinDA2 | sin44)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin45)) || (pItem->sItemInfo.CODE == (sinDA2 | sin45)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin46)) || (pItem->sItemInfo.CODE == (sinDA2 | sin46)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin54)) || (pItem->sItemInfo.CODE == (sinDA2 | sin54)) ||
					(pItem->sItemInfo.CODE == (sinDA1 | sin55)) || (pItem->sItemInfo.CODE == (sinDA2 | sin55)) ||

					pItem->sItemInfo.CODE == (sinGF1 | sin01) || (pItem->sItemInfo.CODE == (sinOR2 | sin33)) ||

					(pItem->sItemInfo.CODE == (sinOA1 | sin36)) ||
					(pItem->sItemInfo.CODE == (sinOA1 | sin37)) ||
					(pItem->sItemInfo.CODE == (sinDB1 | sin33)) ||
					(pItem->sItemInfo.CODE == (sinOA2 | sin33)) ||
					(pItem->sItemInfo.CODE == (sinBI1 | sin84)) ||
					(pItem->sItemInfo.CODE == (sinDB1 | sin34)) ||
					(pItem->sItemInfo.CODE == (sinOA2 | sin34)) ||
					pItem->sItemInfo.CODE == (sinGF1 | sin07) ||
					pItem->sItemInfo.CODE == (sinGF1 | sin08) ||
					pItem->ItemPosition)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;

				}

				int kk = 0;

				for (kk = 0; kk < NotSet_Item_CODECnt; kk++)
				{
					if (NotSet_Item_CODE[kk] == pItem->sItemInfo.CODE)
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}

				}
				for (kk = 0; kk < NotSet_Item_MASKCnt; kk++)
				{
					if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotSet_Item_MASK[kk])
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}
				}
				for (kk = 0; kk < NotSet_Item_KINDCnt; kk++)
				{
					if (NotSet_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}
				}




				return TRUE;
			}

		}

	}

	return TRUE;
}

int cTRADE::InitTradeColorRect()
{
	TradeColorRect.left = 0;
	TradeColorRect.top = 0;
	TradeColorRect.right = 0;
	TradeColorRect.bottom = 0;
	return TRUE;

}

int cTRADE::CrashTradeItem(RECT &desRect, int PassItemIndex, int Kind)
{

	RECT rect;
	int i;
	if (Kind == 0)
	{
		for (i = 0; i < MAX_TRADE_ITEM; i++)
		{
			if (sTrade.TradeItem[i].Flag)
			{
				if (PassItemIndex != 0)
					if (PassItemIndex == i + 1)continue;
				rect.left = sTrade.TradeItem[i].x;
				rect.right = sTrade.TradeItem[i].x + sTrade.TradeItem[i].w;
				rect.top = sTrade.TradeItem[i].y;
				rect.bottom = sTrade.TradeItem[i].y + sTrade.TradeItem[i].h;

				if (desRect.left > rect.left - desRect.right  && desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom && desRect.top < rect.bottom)
				{
					return i + 1;
				}
			}
		}
	}
	if (Kind == 1)
	{
		for (i = 0; i < 100; i++)
		{
			if (sWareHouse.WareHouseItem[i].Flag)
			{
				if (PassItemIndex != 0)
					if (PassItemIndex == i + 1)continue;
				rect.left = sWareHouse.WareHouseItem[i].x;
				rect.right = sWareHouse.WareHouseItem[i].x + sWareHouse.WareHouseItem[i].w;
				rect.top = sWareHouse.WareHouseItem[i].y;
				rect.bottom = sWareHouse.WareHouseItem[i].y + sWareHouse.WareHouseItem[i].h;

				if (desRect.left > rect.left - desRect.right  && desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom && desRect.top < rect.bottom)
				{
					return i + 1;
				}
			}
		}

	}
	if (Kind == 2)
	{
		for (i = 0; i < 15; i++)
		{
			if (sCraftItem.CraftItem[i].Flag)
			{
				if (PassItemIndex != 0)
					if (PassItemIndex == i + 1)continue;
				rect.left = sCraftItem.CraftItem[i].x;
				rect.right = sCraftItem.CraftItem[i].x + sCraftItem.CraftItem[i].w;
				rect.top = sCraftItem.CraftItem[i].y;
				rect.bottom = sCraftItem.CraftItem[i].y + sCraftItem.CraftItem[i].h;

				if (desRect.left > rect.left - desRect.right  && desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom && desRect.top < rect.bottom)
				{
					return i + 1;
				}
			}
		}
	}
	if (Kind == 3)
	{
		for (i = 0; i < 15; i++)
		{
			if (sAgingItem.AgingItem[i].Flag)
			{
				if (PassItemIndex != 0)
					if (PassItemIndex == i + 1)continue;
				rect.left = sAgingItem.AgingItem[i].x;
				rect.right = sAgingItem.AgingItem[i].x + sAgingItem.AgingItem[i].w;
				rect.top = sAgingItem.AgingItem[i].y;
				rect.bottom = sAgingItem.AgingItem[i].y + sAgingItem.AgingItem[i].h;

				if (desRect.left > rect.left - desRect.right  && desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom && desRect.top < rect.bottom)
				{
					return i + 1;
				}
			}
		}
	}

	if (Kind == 4)
	{
		for (i = 0; i < 5; i++)
		{
			if (S_smeltingItem.SmeltingItem[i].Flag)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1) continue;
				}
				rect.left = S_smeltingItem.SmeltingItem[i].x;
				rect.right = S_smeltingItem.SmeltingItem[i].x + S_smeltingItem.SmeltingItem[i].w;
				rect.top = S_smeltingItem.SmeltingItem[i].y;
				rect.bottom = S_smeltingItem.SmeltingItem[i].y + S_smeltingItem.SmeltingItem[i].h;

				if (desRect.left > rect.left - desRect.right && desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom && desRect.top < rect.bottom)
				{
					return i + 1;
				}
			}
		}
	}

	if (Kind == 5)
	{
		for (i = 0; i < 4; i++)
		{
			if (g_sManufactureItem.ManufactureItem[i].Flag)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1) continue;
				}
				rect.left = g_sManufactureItem.ManufactureItem[i].x;
				rect.right = g_sManufactureItem.ManufactureItem[i].x + g_sManufactureItem.ManufactureItem[i].w;
				rect.top = g_sManufactureItem.ManufactureItem[i].y;
				rect.bottom = g_sManufactureItem.ManufactureItem[i].y + g_sManufactureItem.ManufactureItem[i].h;

				if (desRect.left > rect.left - desRect.right && desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom && desRect.top < rect.bottom)
				{
					return i + 1;
				}
			}
		}
	}


	if (Kind == 6)
	{
		for (i = 0; i < 2; i++)
		{
			if (sMixtureResetItem.MixtureResetItem[i].Flag)
			{
				if (PassItemIndex != 0)
				{
					if (PassItemIndex == i + 1)
						continue;
				}


				rect.left = sMixtureResetItem.MixtureResetItem[i].x;
				rect.right = sMixtureResetItem.MixtureResetItem[i].x + sMixtureResetItem.MixtureResetItem[i].w;
				rect.top = sMixtureResetItem.MixtureResetItem[i].y;
				rect.bottom = sMixtureResetItem.MixtureResetItem[i].y + sMixtureResetItem.MixtureResetItem[i].h;

				if (desRect.left > rect.left - desRect.right && desRect.left < rect.right &&
					desRect.top > rect.top - desRect.bottom && desRect.top < rect.bottom)
				{
					return i + 1;
				}
			}
		}
	}

	return FALSE;

}




int cTRADE::LastSetTradeItem(sITEM *pItem)
{
	CheckTradeItemForm();

	for (int j = 0; j < MAX_TRADE_ITEM; j++)
	{
		if (!sTrade.TradeItem[j].Flag)
		{
			if (!CheckTrade((void *)&sTrade))
				CancelTradeItem();

			memcpy(&sTrade.TradeItem[j], pItem, sizeof(sITEM));
			sTrade.TradeItem[j].x = pItem->SetX;
			sTrade.TradeItem[j].y = pItem->SetY;
			pItem->Flag = 0;
			sTrade.CheckFlag = 0;
			sinPlaySound(sTrade.TradeItem[j].SoundIndex);
			ReformTrade((void *)&sTrade);
			GetWeight();
			SendTradeItem(TradeCharCode);
			ReFormTradeItem();
			return TRUE;

		}
	}
	cMessageBox.ShowMessage(MESSAGE_TRADE_OVER_NUM);
	ReFormTradeItem();
	return FALSE;
}

int cTRADE::PickUpTradeItem(int x, int y, int PickUpFlag)
{
	int i = 0;
	SelectTradeItemIndex = 0;
	ItemKindFlag = 0;
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].Flag)
		{
			if (sTrade.TradeItem[i].x < x  && sTrade.TradeItem[i].x + sTrade.TradeItem[i].w > x  &&
				sTrade.TradeItem[i].y < y  && sTrade.TradeItem[i].y + sTrade.TradeItem[i].h > y)
			{
				if (PickUpFlag)
				{
					CheckTradeItemForm();
					if (!CheckTrade((void *)&sTrade))
						CancelTradeItem();
					memcpy(&MouseItem, &sTrade.TradeItem[i], sizeof(sITEM));
					sTrade.TradeItem[i].Flag = 0;
					sinPlaySound(sTrade.TradeItem[i].SoundIndex);
					TradeColorIndex = 0;
					CheckDelayFlag = 1;
					sTrade.CheckFlag = 0;
					ReformTrade((void *)&sTrade);
					GetWeight();
					SendTradeItem(TradeCharCode);
					ReFormTradeItem();
					return TRUE;
				}
				else
				{
					SelectTradeItemIndex = i + 1;
					TradeColorIndex = SELECT_ITEM_COLOR;
					ItemKindFlag = 1;
					sinShowItemInfoFlag = 1;
					cItem.ShowItemInfo(&sTrade.TradeItem[i], 2);
				}
			}
		}
	}
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTradeRecv.TradeItem[i].Flag)
		{
			if (sTradeRecv.TradeItem[i].x < x  && sTradeRecv.TradeItem[i].x + sTradeRecv.TradeItem[i].w > x  &&
				sTradeRecv.TradeItem[i].y - T_REVISION_Y < y  && sTradeRecv.TradeItem[i].y - T_REVISION_Y + sTradeRecv.TradeItem[i].h > y)
			{
				SelectTradeItemIndex = i + 1;
				TradeColorIndex = SELECT_ITEM_COLOR;
				ItemKindFlag = 2;
				sinShowItemInfoFlag = 1;
				sTradeRecv.TradeItem[i].y -= T_REVISION_Y;
				cItem.ShowItemInfo(&sTradeRecv.TradeItem[i], 2);
				sTradeRecv.TradeItem[i].y += T_REVISION_Y;
				return TRUE;

			}
		}
	}

	return FALSE;
}



int cTRADE::CheckTradeItemSet()
{
	int i = 0;
	int TempWeight = 0;

	memcpy(&CheckItem, &cInvenTory.InvenItem, sizeof(sITEM) * 100);
	memcpy(&CheckRecvItem, &sTradeRecv.TradeItem, sizeof(sITEM)*MAX_TRADE_ITEM);


	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (CheckRecvItem[i].Flag)
		{
			if (CheckRecvItem[i].Class == ITEM_CLASS_POTION)
				TempWeight += CheckRecvItem[i].sItemInfo.PotionCount;
			else
				TempWeight += CheckRecvItem[i].sItemInfo.Weight;
		}
	}
	if (TempWeight + sinChar->Weight[0] > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;

	}
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (CheckRecvItem[i].Flag)
		{
			if (!TradeCheckEmptyArea(&CheckRecvItem[i]))
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
				return FALSE;
			}
		}
	}


	if (sTradeRecv.Money > 0)
	{
		if (!cInvenTory.CheckMoneyLimit(sTradeRecv.Money - 193))
			return FALSE;

	}

	return TRUE;
}


int cTRADE::TradeCheckEmptyArea(sITEM *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect = { 0,0,0,0 };
	int		flag = 0;

	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->w;
	cy = (22 * INVENTORY_BOX_COL) - pItem->h;


	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (CheckItem[i].Flag)
				{
					rect.left = CheckItem[i].x;
					rect.right = CheckItem[i].x + CheckItem[i].w;
					rect.top = CheckItem[i].y;
					rect.bottom = CheckItem[i].y + CheckItem[i].h;

					if (cntx > rect.left - pItem->w && cntx< rect.right &&
						cnty > rect.top - pItem->h && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->SetX = cntx;
				pItem->SetY = cnty;
				pItem->ItemPosition = 0;
				if (ChecketInvenItem(pItem))
					return TRUE;

			}
		}
	}

	return FALSE;

}

int cTRADE::ChecketInvenItem(sITEM *pItem)
{
	for (int j = 0; j < INVENTORY_MAXITEM; j++)
		if (CheckItem[j].Flag == 0)
		{
			memcpy(&CheckItem[j], pItem, sizeof(sITEM));
			CheckItem[j].x = pItem->SetX;
			CheckItem[j].y = pItem->SetY;
			pItem->Flag = 0;
			return TRUE;

		}

	return FALSE;
}


int cTRADE::CheckOkTradeItem()
{
	int i = 0;
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTradeRecv.TradeItem[i].Flag)
		{
			if (cInvenTory.CheckRequireItemToSet(&sTradeRecv.TradeItem[i]))
			{
				if (!cInvenTory.AutoSetInvenItem(&sTradeRecv.TradeItem[i]))
				{
					if (sinThrowItemToFeild(&sTradeRecv.TradeItem[i]))
					{
						sTradeRecv.TradeItem[i].Flag = 0;
					}

				}
			}
		}
	}
	if (sTradeRecv.Money > 0)
	{
		CheckCharForm();

		sinPlusMoney(sTradeRecv.Money - 193);
		ReformCharForm();
		SendSaveMoney();
		sinPlaySound(SIN_SOUND_COIN);
	}
	cTrade.OpenFlag = FALSE;
	TempShowMoney = 0;
	ItemPickUpFlag = 0;

	cInvenTory.CheckWeight();

	return TRUE;
}



int cTRADE::CancelTradeItem()
{
	int sArrowPosi = 0;

	if (TradeItemSucessFlag)
	{
		memset(&sTrade, 0, sizeof(sTRADE));
		memset(&sTradeRecv, 0, sizeof(sTRADE));

	}
	int i = 0;
	for (i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].Flag)
		{
			if (cInvenTory.CheckRequireItemToSet(&sTrade.TradeItem[i]))
			{
				if (!cInvenTory.AutoSetInvenItem(&sTrade.TradeItem[i]))
				{

					if (ArrowState[0] == 0)sArrowPosi = 2;
					else sArrowPosi = 1;
					sinButtonFlag = sArrowPosi;
					SelectInvenItemIndex = 0;
					cInvenTory.ChangeABItem(sArrowPosi);

					if (!cInvenTory.AutoSetInvenItem(&sTrade.TradeItem[i]))
					{
						if (sinThrowItemToFeild(&sTrade.TradeItem[i]))
						{
							sTrade.TradeItem[i].Flag = 0;
						}
					}



					if (sinThrowItemToFeild(&sTrade.TradeItem[i]))
					{
						sTrade.TradeItem[i].Flag = 0;
					}
				}
			}
		}
	}

	if (sTrade.Money > 0)
	{
		CheckCharForm();

		sinPlusMoney(sTrade.Money - 193);
		ReformCharForm();
		SendSaveMoney();
		sinPlaySound(SIN_SOUND_COIN);
	}



	if (MouseItem.Flag)
	{
		if (cInvenTory.CheckRequireItemToSet(&MouseItem))
		{
			if (!cInvenTory.AutoSetInvenItem(&MouseItem))
			{
				if (sinThrowItemToFeild(&MouseItem))
				{
					MouseItem.Flag = 0;
				}
			}
		}

	}



	if (sinMessageBoxShowFlag)
	{
		if (sMessageBox2[MESSAGE_MOVE_MONEY_TRADE].Flag)
		{
			sMessageBox2[MESSAGE_MOVE_MONEY_TRADE].Flag = 0;
			sinMessageBoxShowFlag = 0;
		}
	}


	cTrade.OpenFlag = FALSE;
	cMessageBox.ShowMessage(MESSAGE_TRADE_CANCEL);

	memset(&sTrade, 0, sizeof(sTRADE));
	memset(&sTradeRecv, 0, sizeof(sTRADE));
	TempShowMoney = 0;
	ItemPickUpFlag = 0;

	CloseEachPlayer();
	cInvenTory.CheckWeight();
	return TRUE;
}


int cTRADE::LoadTradeItemIamge()
{

	char szFilePath[256];
	int  cnt = 0;
	for (int i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTradeRecv.TradeItem[i].Flag)
		{
			for (int j = 0; j < MAX_ITEM; j++)
			{
				if (sTradeRecv.TradeItem[i].sItemInfo.CODE == sItem[j].CODE)
				{
					wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);

					if (!sItem[j].lpTempItem)
						sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);


					if ((sTradeRecv.TradeItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 || (sTradeRecv.TradeItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ2)
					{
						sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
						if (sTradeRecv.TradeItem[i].sItemInfo.PotionCount <= 1)
						{

							for (cnt = 0; cnt < MAX_ITEM; cnt++)
							{
								if (sItem[cnt].sItemInfo.CODE == (sinPZ1 | sin00))
								{
									break;
								}
							}
							wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[cnt].ItemFilePath, sItem[cnt].LastCategory);
							sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
						}
					}
					sTradeRecv.TradeItem[i].lpItem = sItem[j].lpTempItem;
					break;
				}
			}
		}
	}
	return TRUE;
}

int cTRADE::CheckTradeButtonOk()
{

	if (!TradeSendSucessFlag && sTrade.CheckFlag && sTradeRecv.CheckFlag)
	{
		SendTradeCheckItem(TradeCharCode);
		TradeSendSucessFlag = TRUE;
	}

	return TRUE;
}


int cTRADE::GetWeight()
{
	sTrade.Weight = 0;
	for (int i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].Flag)
		{
			if (sTrade.TradeItem[i].Class == ITEM_CLASS_POTION)
				sTrade.Weight += sTrade.TradeItem[i].sItemInfo.PotionCount;
			else
				sTrade.Weight += sTrade.TradeItem[i].sItemInfo.Weight;

		}

	}

	return TRUE;
}





int cWAREHOUSE::SetWareHouseItemAreaCheck(sITEM *pItem)
{
	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	TradeStartX = 21;
	TradeStartY = 136 + sinInterHeight2;
	TradeEndX = TradeStartX + (22 * 9);
	TradeEndY = TradeStartY + (22 * 9);

	for (i = pItem->x + 11; i < pItem->x + pItem->w; i += 22)
	{
		for (j = pItem->y + 11; j < pItem->y + pItem->h; j += 22)
		{
			if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
			{
				TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
				TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
				TradeColorRect.right = pItem->w;
				TradeColorRect.bottom = pItem->h;
				if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
				{
					cTrade.InitTradeColorRect();
					return FALSE;
				}

				if (pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST ||
					(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
					(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA2 ||
					(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinQW1 ||
					pItem->sItemInfo.CODE == (sinGF1 | sin01))
				{


					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
				int kk = 0;

				for (kk = 0; kk < NotSet_Item_CODECnt; kk++)
				{
					if (NotSet_Item_CODE[kk] == pItem->sItemInfo.CODE)
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}

				}
				for (kk = 0; kk < NotSet_Item_MASKCnt; kk++)
				{
					if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotSet_Item_MASK[kk])
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}

				}
				for (kk = 0; kk < NotSet_Item_KINDCnt; kk++)
				{
					if (NotSet_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}
				}

				if (pItem->sItemInfo.ItemKindCode == ITEM_KIND_EVENT)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;

				}
				if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinCH1)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}



				pItem->SetX = TradeColorRect.left;
				pItem->SetY = TradeColorRect.top;
				pItem->ItemPosition = 0;
				TradeColorIndex = SET_ITEM_CHECK_COLOR;

				if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 1))
				{

					if (!CopyItemNotPickUp(&sWareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1], TradeCrashItemIndex[0] - 1))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						TradeCrashItemIndex[0] = 0;
						TradeCrashItemIndex[1] = 0;
						return FALSE;

					}
					if (TradeCrashItemIndex[1] = cTrade.CrashTradeItem(TradeColorRect, TradeCrashItemIndex[0], 1))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						TradeCrashItemIndex[1] = 0;
						return FALSE;
					}
					TradeColorIndex = OVERLAP_ITEM_COLOR;

				}

				return TRUE;
			}

		}

	}

	return TRUE;
}



int cWAREHOUSE::LastSetWareHouseItem(sITEM *pItem)
{
	CheckWareHouseForm();

	for (int j = 0; j < 100; j++)
	{
		if (!sWareHouse.WareHouseItem[j].Flag)
		{
			memcpy(&sWareHouse.WareHouseItem[j], pItem, sizeof(sITEM));
			sWareHouse.WareHouseItem[j].x = pItem->SetX;
			sWareHouse.WareHouseItem[j].y = pItem->SetY;
			pItem->Flag = 0;
			sinPlaySound(sWareHouse.WareHouseItem[j].SoundIndex);
			GetWeight();
			ReFormWareHouse();
			return TRUE;

		}
	}
	ReFormWareHouse();
	return FALSE;
}


int cWAREHOUSE::CloseWareHouse()
{
	int RestoreFlag = 1;

	CloseWareHouseCheckFlag3 = 1;
	cWareHouse.OpenFlag = 0;
	if (WareHouseSaveFlag)
	{
		if (!SaveWareHouse(&sWareHouse))
		{
			cWareHouse.RestoreInvenItem();
			cMessageBox.ShowMessage(MESSAGE_OVER_ITEM_NUM);
			RestoreFlag = 0;
		}
		else
		{
			if (BackUpInvenItem2)
			{
				delete BackUpInvenItem2;
				BackUpInvenItem2 = 0;

			}
			if (BackUpInvenTempItem2)
			{
				delete BackUpInvenTempItem2;
				BackUpInvenTempItem2 = 0;

			}
			if (BackUpsInven)
			{
				delete BackUpsInven;
				BackUpsInven = 0;

			}

		}

	}
	WareHouseSaveFlag = 0;
	ResetInvenItemCode();
	ResetInvenMoney();
	return RestoreFlag;
}




int cWAREHOUSE::PickUpWareHouseItem(int x, int y, int PickUpFlag)
{
	int i = 0;
	SelectTradeItemIndex = 0;
	for (i = 0; i < 100; i++)
	{
		if (sWareHouse.WareHouseItem[i].Flag)
		{
			if (sWareHouse.WareHouseItem[i].x < x  && sWareHouse.WareHouseItem[i].x + sWareHouse.WareHouseItem[i].w > x  &&
				sWareHouse.WareHouseItem[i].y < y  && sWareHouse.WareHouseItem[i].y + sWareHouse.WareHouseItem[i].h > y)
			{
				if (PickUpFlag)
				{




					sITEM TempItem;
					TempItem.w = ITEMSIZE * 2;
					TempItem.h = ITEMSIZE * 4;
					TempItem.Flag = 1;
					if (cInvenTory.CheckSetEmptyArea(&TempItem))
					{

						if (CopyItemNotPickUp(&sWareHouse.WareHouseItem[i], i))
						{
							CheckWareHouseForm();
							memcpy(&MouseItem, &sWareHouse.WareHouseItem[i], sizeof(sITEM));
							sWareHouse.WareHouseItem[i].Flag = 0;
							sinPlaySound(sWareHouse.WareHouseItem[i].SoundIndex);
							TradeColorIndex = 0;
							GetWeight();
							ReFormWareHouse();
							return TRUE;
						}
					}
					else
					{
						cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
						break;
					}


					if (CopyItemNotPickUp(&sWareHouse.WareHouseItem[i], i))
					{
						CheckWareHouseForm();
						memcpy(&MouseItem, &sWareHouse.WareHouseItem[i], sizeof(sITEM));
						sWareHouse.WareHouseItem[i].Flag = 0;
						sinPlaySound(sWareHouse.WareHouseItem[i].SoundIndex);
						TradeColorIndex = 0;
						GetWeight();
						ReFormWareHouse();
						return TRUE;
					}

				}
				else
				{
					SelectTradeItemIndex = i + 1;
					TradeColorIndex = SELECT_ITEM_COLOR;
					sinShowItemInfoFlag = 1;
					cItem.ShowItemInfo(&sWareHouse.WareHouseItem[i], 2);
				}
			}
		}
	}
	return FALSE;
}


int cWAREHOUSE::ChangeWareHouseItem(sITEM *pItem)
{
	if (pItem->Class == ITEM_CLASS_POTION)
	{
		cMessageBox.ShowMessage(MESSAGE_POTION_NOT_SETTING);
		return TRUE;

	}
	if (pItem->sItemInfo.Weight + (sWareHouse.Weight[0] - 500) > sWareHouse.Weight[1] - 499)
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return TRUE;

	}

	CheckWareHouseForm();

	if (TradeCrashItemIndex[0])
	{
		if (sWareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].Class == ITEM_CLASS_POTION)
		{
			if (sWareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].CODE == pItem->CODE)
			{
				sWareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].sItemInfo.PotionCount += pItem->sItemInfo.PotionCount;
				pItem->Flag = 0;
				GetWeight();
				ReFormWareHouse();
				return TRUE;

			}
		}
		memcpy(&TempItem, &sWareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1], sizeof(sITEM));
		sWareHouse.WareHouseItem[TradeCrashItemIndex[0] - 1].Flag = 0;
		TempItem.x = pItem->x;
		TempItem.y = pItem->y;
		ReFormWareHouse();
		LastSetWareHouseItem(pItem);
		memcpy(pItem, &TempItem, sizeof(sITEM));
		GetWeight();
		ReFormWareHouse();
		return TRUE;

	}
	ReFormWareHouse();
	return FALSE;
}


int cWAREHOUSE::GetWeight()
{
	sWareHouse.Weight[0] = 500;
	for (int i = 0; i < 100; i++)
	{
		if (sWareHouse.WareHouseItem[i].Flag)
		{
			if (sWareHouse.WareHouseItem[i].Class == ITEM_CLASS_POTION)
				sWareHouse.Weight[0] += sWareHouse.WareHouseItem[i].sItemInfo.PotionCount;
			else
				sWareHouse.Weight[0] += sWareHouse.WareHouseItem[i].sItemInfo.Weight;

		}

	}
	WareHouseSaveFlag = 1;

	return TRUE;
}


int cWAREHOUSE::LoadWareHouseItemIamge()
{

	char szFilePath[256];
	int  cnt = 0;
	for (int i = 0; i < 100; i++)
	{
		if (sWareHouse.WareHouseItem[i].Flag)
		{
			for (int j = 0; j < MAX_ITEM; j++)
			{
				if (sWareHouse.WareHouseItem[i].sItemInfo.CODE == sItem[j].CODE)
				{
					sWareHouse.WareHouseItem[i].w = sItem[j].w;
					sWareHouse.WareHouseItem[i].h = sItem[j].h;
					wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);
					if (!sItem[j].lpTempItem)
						sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);

					if ((sWareHouse.WareHouseItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 || (sWareHouse.WareHouseItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ2)
					{
						if (sWareHouse.WareHouseItem[i].sItemInfo.PotionCount == 2)
						{
							wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);
							sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
							sWareHouse.WareHouseItem[i].w = sItem[j].w;
							sWareHouse.WareHouseItem[i].h = sItem[j].h;

						}
						else
						{

							for (cnt = 0; cnt < MAX_ITEM; cnt++)
							{
								if (sItem[cnt].sItemInfo.CODE == (sinPZ1 | sin00))
								{
									break;
								}
							}
							wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[cnt].ItemFilePath, sItem[cnt].LastCategory);
							sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
							sWareHouse.WareHouseItem[i].w = sItem[cnt].w;
							sWareHouse.WareHouseItem[i].h = sItem[cnt].h;
						}

					}
					sWareHouse.WareHouseItem[i].lpItem = sItem[j].lpTempItem;
					break;
				}
			}
		}
	}

	cInterFace.CheckAllBox(SIN_WAREHOUSE);





	return TRUE;
}


int cWAREHOUSE::BackUpInvenItem()
{

	BackUpInvenItem2 = 0;
	BackUpInvenTempItem2 = 0;
	BackUpsInven = 0;

	BackUpInvenItem2 = new sITEM[100];
	BackUpInvenTempItem2 = new sITEM[100];
	BackUpsInven = new sINVENTORY[INVENTORY_MAX_POS];

	memcpy(BackUpInvenItem2, &cInvenTory.InvenItem, sizeof(sITEM) * 100);
	memcpy(BackUpInvenTempItem2, &cInvenTory.InvenItemTemp, sizeof(sITEM) * 100);
	memcpy(BackUpsInven, &sInven, sizeof(sINVENTORY)*INVENTORY_MAX_POS);

	InvenGold = sinChar->Money + 2023;

	RealGold = InvenGold * 3;

	return TRUE;
}



int cWAREHOUSE::RestoreInvenItem()
{

	sinSetCharItem(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE, cInvenTory.InvenItem[sInven[0].ItemIndex - 1].SetModelPosi, FALSE);
	sinSetCharItem(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE, cInvenTory.InvenItem[sInven[1].ItemIndex - 1].SetModelPosi, FALSE);
	sinSetCharItem(cInvenTory.InvenItem[sInven[2].ItemIndex - 1].CODE, cInvenTory.InvenItem[sInven[2].ItemIndex - 1].SetModelPosi, FALSE);

	memcpy(&cInvenTory.InvenItem, BackUpInvenItem2, sizeof(sITEM) * 100);
	memcpy(&cInvenTory.InvenItemTemp, BackUpInvenTempItem2, sizeof(sITEM) * 100);
	memcpy(&sInven, BackUpsInven, sizeof(sINVENTORY)*INVENTORY_MAX_POS);


	if (MouseItem.Flag)
		MouseItem.Flag = 0;

	if (BackUpInvenItem2)
	{
		delete BackUpInvenItem2;
		BackUpInvenItem2 = 0;

	}
	if (BackUpInvenTempItem2)
	{
		delete BackUpInvenTempItem2;
		BackUpInvenTempItem2 = 0;

	}
	if (BackUpsInven)
	{
		delete BackUpsInven;
		BackUpsInven = 0;

	}

	if (sInven[0].ItemIndex)
	{
		sinSetCharItem(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE, cInvenTory.InvenItem[sInven[0].ItemIndex - 1].SetModelPosi, TRUE);

	}

	if (sInven[1].ItemIndex)
	{
		sinSetCharItem(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE, cInvenTory.InvenItem[sInven[1].ItemIndex - 1].SetModelPosi, TRUE);

	}

	if (sInven[2].ItemIndex)
	{
		sinSetCharItem(cInvenTory.InvenItem[sInven[2].ItemIndex - 1].CODE, cInvenTory.InvenItem[sInven[2].ItemIndex - 1].SetModelPosi, TRUE);

	}
	if ((InvenGold - 2023) == (RealGold / 3) - 2023)
	{
		CheckCharForm();
		sinChar->Money = InvenGold - 2023;
		ReformCharForm();

	}
	else
	{
		SendSetHackUser(6);

	}
	InvenGold = 0;
	RealGold = 0;

	cInvenTory.SetItemToChar();
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();

	return TRUE;
}





int cCRAFTITEM::SetCraftItemAreaCheck(sITEM *pItem, int Kind)
{

	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();


	if (pItem->sItemInfo.CODE == (sinBI1 | sin90))
	{
		int ReconStoneX = 159 + 11, ReconStoneY = 268 + 11 + sinInterHeight2;
		TradeColorIndex = 0;
		if (ReconStoneX <= pItem->x + 22 && ReconStoneX > pItem->x && ReconStoneY < pItem->y + 22 && ReconStoneY > pItem->y)
		{
			pItem->SetX = ReconStoneX + (((pItem->x + 22 - ReconStoneX) / 22) * 22) - 11;
			pItem->SetY = ReconStoneY + (((pItem->y + 22 - ReconStoneY) / 22) * 22) - 11;
			pItem->ItemPosition = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;
			if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
			{
				cTrade.InitTradeColorRect();
				return FALSE;
			}
			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 2))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			return TRUE;
		}
	}

	if ((pItem->CODE & sinITEM_MASK2) == sinOS1 || (pItem->CODE & sinITEM_MASK2) == sinSE1)
	{
		TradeStartX = 218;
		TradeStartY = 193 + sinInterHeight2;
		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);

		for (i = pItem->x + 11; i < pItem->x + pItem->w; i += 22)
		{
			for (j = pItem->y + 11; j < pItem->y + pItem->h; j += 22)
			{
				if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
				{
					TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
					TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
					TradeColorRect.right = pItem->w;
					TradeColorRect.bottom = pItem->h;
					if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
					{
						cTrade.InitTradeColorRect();
						return FALSE;
					}

					pItem->SetX = TradeColorRect.left;
					pItem->SetY = TradeColorRect.top;
					pItem->ItemPosition = 0;
					TradeColorIndex = SET_ITEM_CHECK_COLOR;


					if (cCraftItem.ForceFlag)
					{


#ifdef HASIEGE_MODE

						if (cShop.haBuyMoneyCheck(cCraftItem.CheckForceOrbPrice(pItem)) == 0)
						{
#else
						if (sinChar->Money < cCraftItem.CheckForceOrbPrice(pItem))
						{
#endif

							TradeColorIndex = NOT_ENOUGH_MONEY;
							return FALSE;
						}

#ifdef	_LANGUAGE_JAPANESE


						if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
						{


							if (((pItem->sItemInfo.CODE & sinITEM_MASK3) >= sin11) && ((pItem->sItemInfo.CODE & sinITEM_MASK3) <= sin14))
							{
								TradeColorIndex = NOT_SETTING_COLOR;
								return FALSE;
							}
						}
#else

						if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
						{
							if ((pItem->sItemInfo.CODE & sinITEM_MASK3) >= sin12)
							{
								TradeColorIndex = NOT_SETTING_COLOR;
								return FALSE;
							}
						}
#endif



					}


					if (pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA2 ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinQW1 ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ2 ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinFO1 ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinSP1 ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWR1 ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDR1 ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinGP1 ||
						(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinCH1 ||
						(pItem->sItemInfo.CODE >= (sinOR2 | sin06) && pItem->sItemInfo.CODE <= (sinOR2 | sin25)) ||
						pItem->sItemInfo.SpecialItemFlag[0] == CHECK_GIVE_ITEM ||
						pItem->sItemInfo.CODE == (sinGF1 | sin01) ||
						pItem->sItemInfo.CODE == (sinGF1 | sin02) ||
						pItem->sItemInfo.CODE == (sinGF1 | sin03) ||
						pItem->sItemInfo.CODE == (sinGF1 | sin04) ||
						pItem->sItemInfo.CODE == (sinGF1 | sin05) ||
						pItem->sItemInfo.CODE == (sinGF1 | sin06) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin27) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin28) ||
						pItem->sItemInfo.CODE == (sinOA1 | sin33) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin29) ||
						pItem->sItemInfo.CODE == (sinOA1 | sin34) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin30) ||
						pItem->sItemInfo.CODE == (sinOA1 | sin35) ||
						pItem->sItemInfo.CODE == (sinOA2 | sin32) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin15) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin27) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin28) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin29) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin30) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin31) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin32) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin33) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin31) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin32) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin35) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin33) ||
						pItem->sItemInfo.CODE == (sinOA1 | sin36) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin36) ||
						pItem->sItemInfo.CODE == (sinOA1 | sin37) ||
						pItem->sItemInfo.CODE == (sinOA2 | sin33) ||
						pItem->sItemInfo.CODE == (sinDB1 | sin33) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin34) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin37) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin38) ||
						pItem->sItemInfo.CODE == (sinBI1 | sin84) ||
						pItem->sItemInfo.CODE == (sinDB1 | sin34) ||
						pItem->sItemInfo.CODE == (sinOA2 | sin34) ||
						pItem->sItemInfo.CODE == (sinSP1 | sin39) ||
						pItem->sItemInfo.CODE == (sinGF1 | sin07) ||
						pItem->sItemInfo.CODE == (sinGF1 | sin08) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin36) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin37) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin38) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin39) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin40) ||
						pItem->sItemInfo.CODE == (sinOA1 | sin39) ||
						pItem->sItemInfo.CODE == (sinOA1 | sin40) ||
						pItem->sItemInfo.CODE == (sinOA1 | sin41) ||
						pItem->sItemInfo.CODE == (sinOA1 | sin42) ||
						pItem->sItemInfo.CODE == (sinOA1 | sin38) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin34) ||
						pItem->sItemInfo.CODE == (sinOR2 | sin35))


					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;

					}


					if (!cCraftItem.ForceFlag)
					{
						if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinOS1)
						{
							if ((pItem->sItemInfo.CODE & sinITEM_MASK3) >= sin21 && (pItem->sItemInfo.CODE & sinITEM_MASK3) <= sin34)
							{
								TradeColorIndex = NOT_SETTING_COLOR;
								return FALSE;
							}
						}
					}

					int kk = 0;

					for (kk = 0; kk < NotSet_Item_CODECnt; kk++)
					{
						if (NotSet_Item_CODE[kk] == pItem->sItemInfo.CODE)
						{
							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;
						}

					}
					for (kk = 0; kk < NotSet_Item_MASKCnt; kk++)
					{
						if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotSet_Item_MASK[kk])
						{
							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;
						}

					}
					for (kk = 0; kk < NotSet_Item_KINDCnt; kk++)
					{
						if (NotSet_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)
						{
							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;
						}
					}



					if (Kind == 0)
					{
						if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 2))
						{
							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;

						}
						return TRUE;

					}
					if (Kind == 1)
					{
						if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
						{
							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;

						}
						return TRUE;

					}
				}

			}

		}
	}
	else
	{

		if (cCraftItem.ForceFlag)return FALSE;
		TradeColorIndex = 0;
		TradeCrashItemIndex[0] = 0;
		cTrade.InitTradeColorRect();

		TradeStartX = 58;
		TradeStartY = 193 + sinInterHeight2;
		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);
		if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
		{
			TradeColorRect.left = TradeStartX;
			TradeColorRect.top = TradeStartY;
			TradeColorRect.right = TradeEndX - TradeStartX;
			TradeColorRect.bottom = TradeEndY - TradeStartY;


			pItem->SetX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->w) / 2;
			pItem->SetY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->h) / 2;
			pItem->ItemPosition = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;

			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 2))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;

			}



#ifdef HASIEGE_MODE

			if (cShop.haBuyMoneyCheck(pItem->sItemInfo.Price) == 0)
			{
#else
			if (sinChar->Money < pItem->sItemInfo.Price)
			{
#endif

				TradeColorIndex = NOT_ENOUGH_MONEY;
				return FALSE;
			}

			if (pItem->sItemInfo.SpecialItemFlag[0] == CHECK_COPY_ITEM ||
				pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA2 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinQW1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ2 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinFO1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinSP1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWR1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDR1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinGP1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinCH1 ||
				(pItem->sItemInfo.CODE >= (sinOR2 | sin06) && pItem->sItemInfo.CODE <= (sinOR2 | sin25)) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin01) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin02) ||


				pItem->sItemInfo.CODE == (sinGF1 | sin05) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin06) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin27) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin28) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin29) ||
				pItem->sItemInfo.CODE == (sinOA1 | sin34) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin30) ||
				pItem->sItemInfo.CODE == (sinOA1 | sin35) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin15) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin27) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin28) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin29) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin30) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin31) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin32) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin33) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin35) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin33) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin31) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin32) ||
				pItem->sItemInfo.CODE == (sinOA1 | sin36) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin36) ||
				pItem->sItemInfo.CODE == (sinOA1 | sin37) ||
				pItem->sItemInfo.CODE == (sinOA2 | sin33) ||
				pItem->sItemInfo.CODE == (sinDB1 | sin33) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin34) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin37) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin38) ||
				pItem->sItemInfo.CODE == (sinBI1 | sin84) ||
				pItem->sItemInfo.CODE == (sinDB1 | sin34) ||
				pItem->sItemInfo.CODE == (sinOA2 | sin34) ||
				pItem->sItemInfo.CODE == (sinSP1 | sin39) ||
				pItem->sItemInfo.CODE == (sinDA1 | sin54) || pItem->sItemInfo.CODE == (sinDA2 | sin54) ||
				pItem->sItemInfo.CODE == (sinDA1 | sin55) || pItem->sItemInfo.CODE == (sinDA2 | sin55) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin36) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin37) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin38) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin39) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin40) ||
				pItem->sItemInfo.CODE == (sinOA1 | sin39) ||
				pItem->sItemInfo.CODE == (sinOA1 | sin40) ||
				pItem->sItemInfo.CODE == (sinOA1 | sin41) ||
				pItem->sItemInfo.CODE == (sinOA1 | sin42) ||
				pItem->sItemInfo.CODE == (sinOA1 | sin38) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin34) ||
				pItem->sItemInfo.CODE == (sinOR2 | sin35)
				)

			{

				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}


			if (!cCraftItem.ForceFlag)
			{
				if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinOS1)
				{
					if ((pItem->sItemInfo.CODE & sinITEM_MASK3) >= sin21 && (pItem->sItemInfo.CODE & sinITEM_MASK3) <= sin34)
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}
				}
			}

			int kk = 0;

			for (kk = 0; kk < NotSet_Item_CODECnt; kk++)
			{
				if (NotSet_Item_CODE[kk] == pItem->sItemInfo.CODE)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}

			}
			for (kk = 0; kk < NotSet_Item_MASKCnt; kk++)
			{
				if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotSet_Item_MASK[kk])
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}

			}
			for (kk = 0; kk < NotSet_Item_KINDCnt; kk++)
			{
				if (NotSet_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}

			}



			return TRUE;
		}

	}
	return TRUE;
}



int ForceOrbPriceIndex[] = { 200,500,1000,2000,4000,5000,10000,20000,30000,40000,50000,60000,70000,80000 };

int MagicForceOrbPriceIndex[] = { 200,500,1000,2000,4000,5000,10000,20000,30000,40000,50000,60000,70000,80000 };

DWORD SheltomCode2[] = { sin01,sin02,sin03,sin04,sin05,sin06,sin07,sin08,sin09,sin10,sin11,sin12,sin13,sin14 };


DWORD MagicSheltomCode[] = { sin21,sin22,sin23,sin24,sin25,sin26,sin27,sin28,sin29,sin30,sin31,sin32, sin33, sin34 };


DWORD BillingMagicSheltomCode[] = { sin35, sin36, sin37 };

int cCRAFTITEM::CheckForceOrbPrice()
{
	ForceItemPrice = 0;
	for (int j = 1; j < 15; j++)
	{
		if (sCraftItem.CraftItem[j].Flag)
		{
			for (int t = 0; t < 14; t++)
			{
				if ((sCraftItem.CraftItem[j].sItemInfo.CODE & sinITEM_MASK3) <= sin20)
				{
					if ((sCraftItem.CraftItem[j].sItemInfo.CODE & sinITEM_MASK3) == SheltomCode2[t])
					{
						ForceItemPrice += ForceOrbPriceIndex[t];
						break;
					}
				}
				else
				{
					if ((sCraftItem.CraftItem[j].sItemInfo.CODE & sinITEM_MASK3) == MagicSheltomCode[t])
					{
						ForceItemPrice += MagicForceOrbPriceIndex[t];
						break;
					}
				}

			}
		}
	}
	ForceItemPrice2 = ForceItemPrice;
	return TRUE;
}
int cCRAFTITEM::CheckForceOrbPrice(sITEM *pItem)
{

	int TempPrice = 0;
	for (int j = 1; j < 15; j++)
	{
		if (sCraftItem.CraftItem[j].Flag)
		{
			for (int t = 0; t < 12; t++)
			{
				if ((sCraftItem.CraftItem[j].sItemInfo.CODE & sinITEM_MASK3) == SheltomCode2[t])
				{
					TempPrice += ForceOrbPriceIndex[t];
					break;
				}

				else if ((sCraftItem.CraftItem[j].sItemInfo.CODE & sinITEM_MASK3) == MagicSheltomCode[t])
				{
					TempPrice += MagicForceOrbPriceIndex[t];
					break;
				}
			}
		}
	}

	for (int t = 0; t < 12; t++)
	{
		if ((pItem->sItemInfo.CODE & sinITEM_MASK3) == SheltomCode2[t])
		{
			return TempPrice + ForceOrbPriceIndex[t];

		}

		if ((pItem->sItemInfo.CODE & sinITEM_MASK3) == MagicSheltomCode[t])
		{
			return TempPrice + MagicForceOrbPriceIndex[t];
		}
	}
	return FALSE;
}
int cCRAFTITEM::LastSetCraftItem(sITEM *pItem, int Kind)
{
	int TempLevel = 0;
	int TempLevel2 = 0;
	if (Kind == 0)
	{
		CheckCraftItemForm();
		if ((pItem->CODE & sinITEM_MASK2) == sinOS1)
		{
			for (int j = 1; j < 15; j++)
			{
				if (!sCraftItem.CraftItem[j].Flag)
				{
					// Colocar shelton no mix
					memcpy(&sCraftItem.CraftItem[j], pItem, sizeof(sITEM));
					sCraftItem.CraftItem[j].x = pItem->SetX;
					sCraftItem.CraftItem[j].y = pItem->SetY;
					pItem->Flag = 0;
					sinPlaySound(sCraftItem.CraftItem[j].SoundIndex);
					ReFormCraftItem();
					CheckForceOrbPrice();
					return TRUE;
				}
			}
		}

		else if ((pItem->CODE & sinITEM_MASK2) == sinSE1)
		{
			if (sCraftItem.CraftItem[0].Flag)
			{
				TempLevel = sCraftItem.CraftItem[0].sItemInfo.Level;
				for (int k = 0; k < MAX_SEEL_COUNT; k++)
				{
					if (pItem->CODE == sReconItem[k].dwCODE)
					{
						if (!(TempLevel >= sReconItem[k].iLevel[0] && TempLevel <= sReconItem[k].iLevel[1]))
						{
							cMessageBox.ShowMessage(MESSAGE_NOT_RECONITEM);
							return FALSE;
						}
					}
				}
			}
			for (int j = 1; j < 15; j++)
			{
				if (!sCraftItem.CraftItem[j].Flag)
				{
					memcpy(&sCraftItem.CraftItem[j], pItem, sizeof(sITEM));
					sCraftItem.CraftItem[j].x = pItem->SetX;
					sCraftItem.CraftItem[j].y = pItem->SetY;
					pItem->Flag = 0;
					sinPlaySound(sCraftItem.CraftItem[j].SoundIndex);
					ReFormCraftItem();
					return TRUE;
				}
			}

		}


		else if ((pItem->CODE & sinITEM_MASK2) == sinBI1)
		{
			if ((pItem->CODE & sinITEM_MASK3) == sin90)
			{
				if (!sCraftItem.CraftItem[14].Flag)
				{
					memcpy(&sCraftItem.CraftItem[14], pItem, sizeof(sITEM));
					sCraftItem.CraftItem[14].x = pItem->SetX;
					sCraftItem.CraftItem[14].y = pItem->SetY;
					pItem->Flag = 0;
					sinPlaySound(sCraftItem.CraftItem[14].SoundIndex);
					return TRUE;
				}
			}
		}
		else
		{
			if (!sCraftItem.CraftItem[0].Flag)
			{
				// Colocar item no mix
				memcpy(&sCraftItem.CraftItem[0], pItem, sizeof(sITEM));
				sCraftItem.CraftItem[0].x = pItem->SetX;
				sCraftItem.CraftItem[0].y = pItem->SetY;
				pItem->Flag = 0;
				sinPlaySound(sCraftItem.CraftItem[0].SoundIndex);
				ReFormCraftItem();
				return TRUE;
			}

		}
	}

	else if (Kind == 1)
	{
		if ((pItem->CODE & sinITEM_MASK2) == sinOS1)
		{
			for (int j = 1; j < 15; j++)
			{
				if (!sAgingItem.AgingItem[j].Flag)
				{
					// Colocar shelton na janela de aging
					memcpy(&sAgingItem.AgingItem[j], pItem, sizeof(sITEM));
					sAgingItem.AgingItem[j].x = pItem->SetX;
					sAgingItem.AgingItem[j].y = pItem->SetY;
					pItem->Flag = 0;
					sinPlaySound(sAgingItem.AgingItem[j].SoundIndex);

					return TRUE;
				}
			}
		}
		else
		{
			if (!sAgingItem.AgingItem[0].Flag)
			{
				memcpy(&sAgingItem.AgingItem[0], pItem, sizeof(sITEM));
				sAgingItem.AgingItem[0].x = pItem->SetX;
				sAgingItem.AgingItem[0].y = pItem->SetY;
				pItem->Flag = 0;
				sinPlaySound(sAgingItem.AgingItem[0].SoundIndex);

				return TRUE;
			}

		}

	}
	else if (Kind == 2)
	{
		for (int j = 0; j < 15; j++)
		{
			if (!sAgingItem.AgingItem[j].Flag)
			{
				memcpy(&sAgingItem.AgingItem[j], pItem, sizeof(sITEM));
				sAgingItem.AgingItem[j].x = pItem->SetX;
				sAgingItem.AgingItem[j].y = pItem->SetY;
				pItem->Flag = 0;
				sinPlaySound(sAgingItem.AgingItem[j].SoundIndex);
				return TRUE;
			}
		}
	}
	else if (Kind == 3)
	{
		if (!sAgingItem.AgingItem[14].Flag)
		{
			memcpy(&sAgingItem.AgingItem[14], pItem, sizeof(sITEM));
			sAgingItem.AgingItem[14].x = pItem->SetX;
			sAgingItem.AgingItem[14].y = pItem->SetY;
			pItem->Flag = 0;
			sinPlaySound(sAgingItem.AgingItem[14].SoundIndex);
			return TRUE;
		}
	}

	return TRUE;

}


int cCRAFTITEM::PickUpCraftItem(int x, int y, int PickUpFlag, int Kind)
{

	int i = 0;
	SelectTradeItemIndex = 0;
	if (Kind == 0)
	{
		for (i = 0; i < 15; i++)
		{
			if (sCraftItem.CraftItem[i].Flag)
			{
				if (sCraftItem.CraftItem[i].x < x  && sCraftItem.CraftItem[i].x + sCraftItem.CraftItem[i].w > x  &&
					sCraftItem.CraftItem[i].y < y  && sCraftItem.CraftItem[i].y + sCraftItem.CraftItem[i].h > y)
				{
					if (PickUpFlag)
					{

						int cnt = 0;
						for (cnt = 1; cnt < 15; cnt++)
						{
							if (i == 0 && sCraftItem.CraftItem[cnt].Flag)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_AGINGPICKUP);
								cnt = 100;
								break;
							}
						}
						if (cnt == 100) break;

						CheckCraftItemForm();
						// Tirar shelton do mix
						memcpy(&MouseItem, &sCraftItem.CraftItem[i], sizeof(sITEM));
						sCraftItem.CraftItem[i].Flag = 0;
						haCraftSortItem(&sCraftItem);


						sinPlaySound(sCraftItem.CraftItem[i].SoundIndex);
						TradeColorIndex = 0;
						ReFormCraftItem();
						if (ForceFlag)
							CheckForceOrbPrice();

						if (i == 0)
						{
							for (int i = 1; i < 15; i++)
							{
								if (sCraftItem.CraftItem[i].Flag)
								{
									if ((sCraftItem.CraftItem[i].CODE & sinITEM_MASK2) == sinSE1)
									{
										if (!cInvenTory.AutoSetInvenItem(&sCraftItem.CraftItem[i]))
										{
											sinThrowItemToFeild(&sCraftItem.CraftItem[i]);
											sCraftItem.CraftItem[i].Flag = 0;
											memset(&sCraftItem.CraftItem[i], 0, sizeof(sCRAFTITEM));
										}
									}
								}
							}
						}
						return TRUE;
					}
					else
					{
						SelectTradeItemIndex = i + 1;
						TradeColorIndex = SELECT_ITEM_COLOR;
						sinShowItemInfoFlag = 1;
						cItem.ShowItemInfo(&sCraftItem.CraftItem[i], 2);
					}
				}
			}
		}
	}
	if (Kind == 1)
	{
		for (i = 0; i < 15; i++)
		{
			if (sAgingItem.AgingItem[i].Flag)
			{
				if (sAgingItem.AgingItem[i].x < x  && sAgingItem.AgingItem[i].x + sAgingItem.AgingItem[i].w > x  &&
					sAgingItem.AgingItem[i].y < y  && sAgingItem.AgingItem[i].y + sAgingItem.AgingItem[i].h > y)
				{
					if (PickUpFlag)
					{

						int cnt = 0;
						for (cnt = 1; cnt < 15; cnt++)
						{
							if (i == 0 && sAgingItem.AgingItem[cnt].Flag)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_AGINGPICKUP);
								cnt = 100;
								break;
							}
						}
						if (cnt == 100) break;


						memcpy(&MouseItem, &sAgingItem.AgingItem[i], sizeof(sITEM));
						sAgingItem.AgingItem[i].Flag = 0;
						sinPlaySound(sAgingItem.AgingItem[i].SoundIndex);

						if (sAgingItem.AgingItem[i].sItemInfo.CODE == (sinBI1 | sin10) ||
							sAgingItem.AgingItem[i].sItemInfo.CODE == (sinBI1 | sin11) ||
							sAgingItem.AgingItem[i].sItemInfo.CODE == (sinBI1 | sin60) ||
							sAgingItem.AgingItem[i].sItemInfo.CODE == (sinBI1 | sin61) ||
							sAgingItem.AgingItem[i].sItemInfo.CODE == (sinBI1 | sin85)) break;
						TradeColorIndex = 0;

						if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
							(MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinMA2)
						{
							sinMakeItemCheck();

						}
						else
						{
							if (i == 0)
							{
								for (int y = 0; y < 4; y++)
								{
									for (int h = 0; h < 3; h++)
									{
										AgingLevelSheltomIndex[y][h] = 0;
										AgingCheckSheltomFlag = 0;
										AgingSheltomCnt2 = 0;
										cAging.CancelAgingItem(1);
									}
								}
							}
							else
							{
								if (AgingSheltomCnt2)
								{
									AgingSheltomCnt2--;
									AgingCheckSheltomFlag = 0;
								}
							}
						}
						return TRUE;
					}
					else
					{
						SelectTradeItemIndex = i + 1;
						TradeColorIndex = SELECT_ITEM_COLOR;
						sinShowItemInfoFlag = 1;
						cItem.ShowItemInfo(&sAgingItem.AgingItem[i], 2);
					}
				}
			}
		}
	}
	return FALSE;
}

DWORD SheltomCode[14] = { sin01,sin02,sin03,sin04,sin05,sin06,sin07,sin08,sin09,sin10,sin11,sin12,sin13,sin14 };

int cCRAFTITEM::MixingItem()
{
	int i, j, t, k, CheckFlag = 0, Temp = 0, LineCount = 0;
	DWORD TempCode2 = 0;
	int  ReConCnt = 0;
	if (sCraftItem_Recv.DocIndex == 2000)
	{
		for (i = 0; i < 12; i++)
		{
			if (sCraftItem_Recv.SheltomCode[i])
			{
				TempCode2 = sCraftItem_Recv.SheltomCode[i];
				break;
			}
		}
		for (j = 0; j < MAX_SEEL_COUNT; j++)
		{
			if (sReconItem[j].dwCODE == TempCode2)
			{
				ReConCnt = sReconItem[j].iCount;
			}
		}
		if (!ReConCnt)
		{
			sCraftItem_Recv.Result = FALSE;
			return FALSE;
		}
		for (i = 0; i < ReConCnt; i++)
		{
			if (sCraftItem_Recv.SheltomCode[i])
			{
				if (TempCode2 != sCraftItem_Recv.SheltomCode[i])
				{
					sCraftItem_Recv.Result = FALSE;
					return FALSE;
				}
			}
		}
		sCraftItem_Recv.Result = TRUE;
		return 2000;
	}


	for (j = 0; j < 12; j++)
	{
		if ((sCraftItem_Recv.SheltomCode[j] & sinITEM_MASK2) == sinSE1)
		{
			sCraftItem_Recv.Result = FALSE;
			return FALSE;
		}
	}




	for (j = 0; j < 14; j++)
		sCraftItem.SheltomIndex[j] = 0;



	for (i = 0; i < 14; i++)
	{
		if (sCraftItem_Recv.SheltomCode[i] & sinITEM_MASK2)
		{
			for (j = 0; j < 14; j++)
			{
				if ((sCraftItem_Recv.SheltomCode[i] & sinITEM_MASK3) == SheltomCode[j])
				{
					sCraftItem.SheltomIndex[j]++;
					break;
				}
			}
		}
	}



	for (i = 0; i < MAX_CRAFTITEM_INFO; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (sCraftItem_Recv.DesCraftItem.Flag)
			{



				if ((sCraftItem_Info[i].MainItemCode[j] & sinITEM_MASK2) ==
					(sCraftItem_Recv.DesCraftItem.sItemInfo.CODE & sinITEM_MASK2))
				{
					for (t = 0; t < 14; t++)
					{
						if (sCraftItem_Info[i].AddItem[t] != sCraftItem.SheltomIndex[t])
						{
							CheckFlag = 1;
							break;
						}
						CheckFlag = 0;

					}


					if (!CheckFlag)
					{

						for (k = 0; k < 14; k++)
						{

							if (sCraftItem.SheltomIndex[k])
								sCraftItem_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0] = k + 1;

							if (sCraftItem_Info[i].PlusElementCode[k])
							{
								switch (sCraftItem_Info[i].PlusElementCode[k])
								{
								case SIN_ADD_FIRE:
									sCraftItem_Recv.DesCraftItem.sItemInfo.Resistance[sITEMINFO_FIRE] += (int)sCraftItem_Info[i].AddElement[k];
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_FIRE;

									break;
								case SIN_ADD_ICE:
									sCraftItem_Recv.DesCraftItem.sItemInfo.Resistance[sITEMINFO_ICE] += (int)sCraftItem_Info[i].AddElement[k];
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_ICE;
									break;
								case SIN_ADD_LIGHTNING:
									sCraftItem_Recv.DesCraftItem.sItemInfo.Resistance[sITEMINFO_LIGHTING] += (int)sCraftItem_Info[i].AddElement[k];
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_LIGHTNING;
									break;

								case SIN_ADD_POISON:
									sCraftItem_Recv.DesCraftItem.sItemInfo.Resistance[sITEMINFO_POISON] += (int)sCraftItem_Info[i].AddElement[k];
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_POISON;
									break;
								case SIN_ADD_BIO:
									sCraftItem_Recv.DesCraftItem.sItemInfo.Resistance[sITEMINFO_BIONIC] += (int)sCraftItem_Info[i].AddElement[k];
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_BIO;
									break;
								case SIN_ADD_CRITICAL:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.Critical_Hit += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.Critical_Hit += (sCraftItem_Recv.DesCraftItem.sItemInfo.Critical_Hit*((int)sCraftItem_Info[i].AddElement[k])) / 100;

									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_CRITICAL;
									break;
								case SIN_ADD_ATTACK_RATE:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.Attack_Rating += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.Attack_Rating += (sCraftItem_Recv.DesCraftItem.sItemInfo.Attack_Rating*((int)sCraftItem_Info[i].AddElement[k])) / 100;

									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_ATTACK_RATE;
									break;
								case SIN_ADD_DAMAGE_MIN:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.Damage[0] += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.Damage[0] += (sCraftItem_Recv.DesCraftItem.sItemInfo.Damage[0] * ((int)sCraftItem_Info[i].AddElement[k])) / 100;

									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MIN;
									break;

								case SIN_ADD_DAMAGE_MAX:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.Damage[1] += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.Damage[1] += (sCraftItem_Recv.DesCraftItem.sItemInfo.Damage[1] * ((int)sCraftItem_Info[i].AddElement[k])) / 100;

									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MAX;
									break;
								case SIN_ADD_ATTACK_SPEED:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.Attack_Speed += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.Attack_Speed += (sCraftItem_Recv.DesCraftItem.sItemInfo.Attack_Speed*((int)sCraftItem_Info[i].AddElement[k])) / 100;

									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_ATTACK_SPEED;
									break;
								case SIN_ADD_ABSORB:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.fAbsorb += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.fAbsorb += (GetItemAbsorb(&sCraftItem_Recv.DesCraftItem.sItemInfo)*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_ABSORB;
									break;
								case SIN_ADD_DEFENCE:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.Defence += (int)sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.Defence += (sCraftItem_Recv.DesCraftItem.sItemInfo.Defence*((int)sCraftItem_Info[i].AddElement[k])) / 100;

									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_DEFENCE;
									break;
								case SIN_ADD_BLOCK_RATE:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.fBlock_Rating += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.fBlock_Rating += (sCraftItem_Recv.DesCraftItem.sItemInfo.fBlock_Rating*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_BLOCK_RATE;
									break;
								case SIN_ADD_MOVE_SPEED:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.fSpeed += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.fSpeed += (sCraftItem_Recv.DesCraftItem.sItemInfo.fSpeed*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_MOVE_SPEED;
									break;

								case SIN_ADD_LIFE:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.fIncrease_Life += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.fIncrease_Life += (sCraftItem_Recv.DesCraftItem.sItemInfo.fIncrease_Life*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_LIFE;
									break;

								case SIN_ADD_MANA:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.fIncrease_Mana += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.fIncrease_Mana += (sCraftItem_Recv.DesCraftItem.sItemInfo.fIncrease_Mana*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_MANA;
									break;
								case SIN_ADD_STAMINA:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.fIncrease_Stamina += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.fIncrease_Stamina += (sCraftItem_Recv.DesCraftItem.sItemInfo.fIncrease_Stamina*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_STAMINA;
									break;
								case SIN_ADD_LIFEREGEN:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.fLife_Regen += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.fLife_Regen += (sCraftItem_Recv.DesCraftItem.sItemInfo.fLife_Regen*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_LIFEREGEN;
									break;
								case SIN_ADD_MANAREGEN:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.fMana_Regen += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.fMana_Regen += (sCraftItem_Recv.DesCraftItem.sItemInfo.fMana_Regen*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_MANAREGEN;

									break;
								case SIN_ADD_STAMINAREGEN:
									if (sCraftItem_Info[i].ElementKind[k] == SIN_ADD_NUM)
										sCraftItem_Recv.DesCraftItem.sItemInfo.fStamina_Regen += sCraftItem_Info[i].AddElement[k];
									else
										sCraftItem_Recv.DesCraftItem.sItemInfo.fStamina_Regen += (sCraftItem_Recv.DesCraftItem.sItemInfo.fStamina_Regen*(sCraftItem_Info[i].AddElement[k] / 100));
									sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindMask |= SIN_ADD_STAMINAREGEN;

									break;

								}
							}
						}


						ReformItem(&sCraftItem_Recv.DesCraftItem.sItemInfo);


						if (!CheckMixItem(&sCraftItem_Recv.DesCraftItem.sItemInfo))
						{
							SendSetHackUser(50);
							return FALSE;
						}


						sCraftItem_Recv.DesCraftItem.sItemInfo.ItemKindCode = ITEM_KIND_CRAFT;
						ReformMixItem(&sCraftItem_Recv.DesCraftItem.sItemInfo);

						sCraftItem_Recv.DocIndex = i;
						sCraftItem_Recv.Result = TRUE;





						return TRUE;

					}
				}
			}
		}
	}


	sCraftItem_Recv.Result = FALSE;






	return FALSE;
}


int cCRAFTITEM::CraftCheckEmptyArea(sITEM *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->w;
	cy = (22 * INVENTORY_BOX_COL) - pItem->h;


	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (cInvenTory.InvenItem[i].Flag)
				{
					rect.left = cInvenTory.InvenItem[i].x;
					rect.right = cInvenTory.InvenItem[i].x + cInvenTory.InvenItem[i].w;
					rect.top = cInvenTory.InvenItem[i].y;
					rect.bottom = cInvenTory.InvenItem[i].y + cInvenTory.InvenItem[i].h;

					if (cntx > rect.left - pItem->w && cntx< rect.right &&
						cnty > rect.top - pItem->h && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->SetX = cntx;
				pItem->SetY = cnty;
				pItem->ItemPosition = 0;
				return TRUE;
			}
		}
	}

	return FALSE;

}


int cCRAFTITEM::CancelMixItem()
{
	if (MixItemNoCopyFlag)return FALSE;
	for (int i = 0; i < 15; i++)
	{
		if (sCraftItem.CraftItem[i].Flag)
		{
			if (!cInvenTory.AutoSetInvenItem(&sCraftItem.CraftItem[i]))
			{
				sinThrowItemToFeild(&sCraftItem.CraftItem[i]);
				sCraftItem.CraftItem[i].Flag = 0;
			}
		}
	}

	cCraftItem.OpenFlag = 0;
	memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
	ResetInvenItemCode();

	memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));
	memset(&sCraftItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	ForceFlag = 0;
	ForceItemPrice = 0;
	ForceItemPrice2 = 0;
	return TRUE;
}

int CraftItemCheckDelayTime = 0;


int cCRAFTITEM::CheckHackCraftItem()
{

	CraftItemCheckDelayTime++;
	if (CraftItemCheckDelayTime < 70 * 10)return FALSE;
	CraftItemCheckDelayTime = 0;


	unsigned int AddItemCheckSum = 0;
	unsigned int CheckAddItemData = 2774094026;

	for (int i = 0; i < MAX_CRAFTITEM_INFO; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			AddItemCheckSum += (int)((j + 1)*sCraftItem_Info[i].AddElement[j]);
			AddItemCheckSum += (j + 1)*sCraftItem_Info[i].AddItem[j];
			AddItemCheckSum += (j + 1)*sCraftItem_Info[i].ElementKind[j];
			AddItemCheckSum += (j + 1)*sCraftItem_Info[i].PlusElementCode[j];
			AddItemCheckSum += (j + 1)*sCraftItem_Info[i].MainItemCode[j];

		}

	}
	if (CheckAddItemData != AddItemCheckSum)
	{
		SendSetHackUser(8);

	}

	return TRUE;
}


int cCRAFTITEM::CheckCraftItemForm()
{
	int TempCheckDataSum = 0;

	if (!cCraftItem.ForceFlag)
	{
		for (int i = 0; i < 15; i++)
		{
			if (sCraftItem.CraftItem[i].Flag)
			{
				TempCheckDataSum += (i + 1)*sCraftItem.CraftItem[i].x;
				TempCheckDataSum += (i + 1)*sCraftItem.CraftItem[i].y;
				TempCheckDataSum += sCraftItem.CraftItem[i].sItemInfo.ItemHeader.dwChkSum;
				TempCheckDataSum += sCraftItem.CraftItem[i].sItemInfo.ItemHeader.Head;

			}
		}


	}
	return TRUE;

}

int cCRAFTITEM::ReFormCraftItem()
{

	CraftItemCheckSum = 0;
	for (int i = 0; i < 15; i++)
	{
		if (sCraftItem.CraftItem[i].Flag)
		{
			CraftItemCheckSum += (i + 1)*sCraftItem.CraftItem[i].x;
			CraftItemCheckSum += (i + 1)*sCraftItem.CraftItem[i].y;
			CraftItemCheckSum += sCraftItem.CraftItem[i].sItemInfo.ItemHeader.dwChkSum;
			CraftItemCheckSum += sCraftItem.CraftItem[i].sItemInfo.ItemHeader.Head;

		}
	}

	return TRUE;
}




int cTRADE::CheckTradeItemForm()
{
	int TempCheckDataSum = 0;
	for (int i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].Flag)
		{
			TempCheckDataSum += (i + 1)*sTrade.TradeItem[i].x;
			TempCheckDataSum += (i + 1)*sTrade.TradeItem[i].y;
			TempCheckDataSum += sTrade.TradeItem[i].sItemInfo.ItemHeader.dwChkSum;
			TempCheckDataSum += sTrade.TradeItem[i].sItemInfo.ItemHeader.Head;

		}
	}
	if (TempCheckDataSum != TradeItemCheckSum)
		SendSetHackUser(10);

	return TRUE;

}

int cTRADE::ReFormTradeItem()
{

	TradeItemCheckSum = 0;
	for (int i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].Flag)
		{
			TradeItemCheckSum += (i + 1)*sTrade.TradeItem[i].x;
			TradeItemCheckSum += (i + 1)*sTrade.TradeItem[i].y;
			TradeItemCheckSum += sTrade.TradeItem[i].sItemInfo.ItemHeader.dwChkSum;
			TradeItemCheckSum += sTrade.TradeItem[i].sItemInfo.ItemHeader.Head;

		}
	}
	return TRUE;
}




int cWAREHOUSE::CheckWareHouseForm()
{
	int TempCheckDataSum = 0;
	for (int i = 0; i < 100; i++)
	{
		if (sWareHouse.WareHouseItem[i].Flag)
		{
			TempCheckDataSum += (i + 1)*sWareHouse.WareHouseItem[i].x;
			TempCheckDataSum += (i + 1)*sWareHouse.WareHouseItem[i].y;
			TempCheckDataSum += sWareHouse.WareHouseItem[i].sItemInfo.ItemHeader.dwChkSum;
			TempCheckDataSum += sWareHouse.WareHouseItem[i].sItemInfo.ItemHeader.Head;

		}
	}
	if (TempCheckDataSum != WareHouseCheckSum)
		SendSetHackUser(11);

	return TRUE;

}

int cWAREHOUSE::ReFormWareHouse()
{

	WareHouseCheckSum = 0;
	for (int i = 0; i < 100; i++)
	{
		if (sWareHouse.WareHouseItem[i].Flag)
		{
			WareHouseCheckSum += (i + 1)*sWareHouse.WareHouseItem[i].x;
			WareHouseCheckSum += (i + 1)*sWareHouse.WareHouseItem[i].y;
			WareHouseCheckSum += sWareHouse.WareHouseItem[i].sItemInfo.ItemHeader.dwChkSum;
			WareHouseCheckSum += sWareHouse.WareHouseItem[i].sItemInfo.ItemHeader.Head;

		}
	}
	return TRUE;
}




int cAGING::AgingItem(int MakeItemFlag)
{

	int ResultCount = 0;
	int ResultCountCheck = 0;
	DWORD TempCODE[16] = { 0, };
	int  i = 0;

	if (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0] >= 20)
	{
		sAging_Recv.Result = FALSE;
		return FALSE;
	}

	if (sAging_Recv.A_StoneItemCode == (sinBI1 | sin10))
		cAging.AginStoneKind = 1;
	else if (sAging_Recv.A_StoneItemCode == (sinBI1 | sin11))
		cAging.AginStoneKind = 2;
	else if (sAging_Recv.A_StoneItemCode == (sinBI1 | sin60))
		cAging.AginStoneKind = 3;
	else if (sAging_Recv.A_StoneItemCode == (sinBI1 | sin61))
		cAging.AginStoneKind = 4;
	else if (sAging_Recv.A_StoneItemCode == (sinBI2 | sin39))
		cAging.AginStoneKind = 5;
	else if (sAging_Recv.A_StoneItemCode == (sinBI2 | sin38))
		cAging.AginStoneKind = 6;
	else
		cAging.AginStoneKind = 0;

	if (sAging_Recv.DesCraftItem.sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON)
	{
		if (SetChangeJob3QuestItem(&sAging_Recv.DesCraftItem.sItemInfo))
		{
			ReformMixItem(&sAging_Recv.DesCraftItem.sItemInfo);
			sAging_Recv.Result = 100 + sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			return TRUE;
		}
		sAging_Recv.Result = FALSE;
		return FALSE;
	}

	for (int i = 0; i < MAX_MAKEITEM_INFO; i++)
	{

		TempCODE[0] = sAging_Recv.DesCraftItem.sItemInfo.CODE;
		for (int p = 0; p < 15; p++)
		{
			if (sAging_Recv.SheltomCode[p])
				TempCODE[p + 1] = sAging_Recv.SheltomCode[p];
		}
		for (int j = 0; j < 15; j++)
		{
			if (sMakeItem_Info[i].CODE[j])
			{
				ResultCount++;
				for (int k = 0; k < 15; k++)
				{
					if (sAging_Recv.SheltomCode[k] && TempCODE[k])
					{
						if (TempCODE[k] == sMakeItem_Info[i].CODE[j])
						{
							TempCODE[k] = -1;
							ResultCountCheck++;
						}
					}
				}
				if (sAging_Recv.DesCraftItem.sItemInfo.CODE == sMakeItem_Info[i].CODE[j])
				{
					ResultCountCheck++;

				}
			}
		}
		if (ResultCount && ResultCountCheck && ResultCount == ResultCountCheck)
		{
			sAging_Recv.DesCraftItem.sItemInfo.CODE = sMakeItem_Info[i].Result_CODE;
			sAging_Recv.Result = TRUE;


			return TRUE;
		}
		else AgingCheckSheltomFlag = 0;
		ResultCount = 0;
		ResultCountCheck = 0;

	}


	if (MakeItemFlag > 0)return FALSE;
	int DestroyPersent = 0;






	DWORD SheltomCODE[MAX_SHELTOM] = { sinOS1 | sin01,sinOS1 | sin02,sinOS1 | sin03,sinOS1 | sin04,sinOS1 | sin05,sinOS1 | sin06,sinOS1 | sin07,sinOS1 | sin08,sinOS1 | sin09,sinOS1 | sin10,sinOS1 | sin11,sinOS1 | sin12,sinOS1 | sin13, sinOS1 | sin14,sinOS1 | sin15 };
	DWORD CheckSheltomCODE[12] = { 0, };
	DWORD CheckSheltomCODE2[12] = { 0, };


	DWORD ItemCode[] = { sinOA1,sinOR1,sinOS1 };
	int Cnt = 0;
	while (1)
	{
		if (!ItemCode[Cnt])break;
		if ((sAging_Recv.DesCraftItem.sItemInfo.CODE & sinITEM_MASK2) == ItemCode[Cnt])
		{
			sAging_Recv.Result = FALSE;
			return FALSE;
		}
		Cnt++;
	}


	int   AgingLevel = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];

	for (int g = 0; g < 12; g++)
	{
		if (AgingLevelSheltom[AgingLevel][g])
		{
			CheckSheltomCODE[g] = SheltomCODE[AgingLevelSheltom[AgingLevel][g] - 1];
			CheckSheltomCODE2[g] = sAging_Recv.SheltomCode[g];

		}
	}


	DWORD Temp = 0;
	for (int i = 11; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (CheckSheltomCODE[j] < CheckSheltomCODE[j + 1])
			{
				Temp = CheckSheltomCODE[j + 1];
				CheckSheltomCODE[j + 1] = CheckSheltomCODE[j];
				CheckSheltomCODE[j] = Temp;
			}
			if (CheckSheltomCODE2[j] < CheckSheltomCODE2[j + 1])
			{
				Temp = CheckSheltomCODE2[j + 1];
				CheckSheltomCODE2[j + 1] = CheckSheltomCODE2[j];
				CheckSheltomCODE2[j] = Temp;
			}

		}
	}

	for (int i = 0; i < 12; i++)
	{

		if (CheckSheltomCODE[i])
		{
			if (CheckSheltomCODE2[i] != CheckSheltomCODE[i])
			{
				return FALSE;
			}
		}
	}


	sITEM* pItem = &sAging_Recv.DesCraftItem;

	if (!sinCheckAgingItemHack(pItem))
	{
		sAging_Recv.Result = FALSE;
		return FALSE;
	}

	if (MakeItemFlag == -1)
		DestroyPersent = 100; //100;
	else
		DestroyPersent = GetRandomPos(0, 100);

	int AgingKind = 0;


	int   PlusAgingPercent[20] = { 30, 25, 20, 10, 10, 10, 10, 5, 5, 5, 5, 4, 4, 3, 3, 2, 2, 2, 0 ,0 };

	// Padrão = 3
	int AgingItemFaildNum = 3;

	int DownPersent = GetRandomPos(0, 100);
	int PlusPersent = GetRandomPos(0, 100);


#ifdef __SIN_AGING_TEST


	if (80 < DestroyPersent)
	{
		switch (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0])
		{
		case 4:
			if (DownPersent < 90)
				AgingItemFaildNum = 1;
			else AgingItemFaildNum = 2;
			break;
		case 5:
			if (DownPersent < 90)
				AgingItemFaildNum = 1;
			else AgingItemFaildNum = 2;
			break;
		case 6:
			if (DownPersent < 90)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 90 && DownPersent < 90)
				AgingItemFaildNum = 2;
			else AgingItemFaildNum = 1;
			break;
		case 7:
			if (DownPersent < 90)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 90 && DownPersent < 90)
				AgingItemFaildNum = 2;
			else AgingItemFaildNum = 1;
			break;
		case 8:
			if (DownPersent < 90)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 90 && DownPersent < 90)
				AgingItemFaildNum = 2;
			else AgingItemFaildNum = 0;
			break;
		case 9:
			if (DownPersent < 90)
				AgingItemFaildNum = 1;
			else if (DownPersent >= 90 && DownPersent < 90)
				AgingItemFaildNum = 2;
			else AgingItemFaildNum = 1;
			break;

		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
			if (DownPersent < 100)
				AgingItemFaildNum = 1;
			else AgingItemFaildNum = 1;
			break;
		}
	}
	else
	{
		if (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0] < 10)
		{
			if (PlusAgingPercent[sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0]] > PlusPersent)
			{
				sinSetAgingItemIncreState(&sAging_Recv.DesCraftItem.sItemInfo);
				AgingItemFaildNum = 4;
			}
		}
}
#else

	if (cAging.AginStoneKind == 1)
	{

		if (AgingStoneAgingOkPercent[sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0]] > DestroyPersent)
		{
			switch (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0])
			{

			case 8:
				if (DownPersent < 70)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 70 && DownPersent < 85)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 9:
				if (DownPersent < 60)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 60 && DownPersent < 80)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 10:
				if (DownPersent < 50)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 50 && DownPersent < 70)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 11:
				if (DownPersent < 40)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 40 && DownPersent < 60)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 12:
				if (DownPersent < 30)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 30 && DownPersent < 50)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 13:
				if (DownPersent < 30)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 30 && DownPersent < 40)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 14:
				if (DownPersent < 20)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 20 && DownPersent < 30)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
				if (DownPersent < 10)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 10 && DownPersent < 20)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			}
		}
		else
		{
			if (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0] < 10)
			{
				if ((PlusAgingPercent[sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0]] * 2) > PlusPersent)
				{
					sinSetAgingItemIncreState(&sAging_Recv.DesCraftItem.sItemInfo);
					AgingItemFaildNum = 4;
				}
			}
		}
	}




	else if (cAging.AginStoneKind == 4)
	{
		if (SuperAgingStoneAgingFailPercent[sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0]] > DestroyPersent)
		{
			switch (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0])
			{

			case 8:
				if (DownPersent < 70)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 70 && DownPersent < 85)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 9:
				if (DownPersent < 60)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 60 && DownPersent < 80)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 10:
				if (DownPersent < 50)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 50 && DownPersent < 70)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 11:
				if (DownPersent < 40)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 40 && DownPersent < 60)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 12:
				if (DownPersent < 30)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 30 && DownPersent < 50)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 13:
				if (DownPersent < 30)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 30 && DownPersent < 40)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 14:
				if (DownPersent < 20)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 20 && DownPersent < 30)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
				if (DownPersent < 10)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 10 && DownPersent < 20)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			}
		}
	}


	else if (cAging.AginStoneKind == 5)
	{
		if (SuperAgingStone1_5AgingFailPercent[sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0]] > DestroyPersent)
		{
			switch (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0])
			{

			case 8:
				if (DownPersent < 70)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 70 && DownPersent < 85)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 9:
				if (DownPersent < 60)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 60 && DownPersent < 80)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 10:
				if (DownPersent < 50)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 50 && DownPersent < 70)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 11:
				if (DownPersent < 40)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 40 && DownPersent < 60)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 12:
				if (DownPersent < 30)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 30 && DownPersent < 50)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 13:
				if (DownPersent < 30)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 30 && DownPersent < 40)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 14:
				if (DownPersent < 20)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 20 && DownPersent < 30)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
				if (DownPersent < 10)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 10 && DownPersent < 20)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			}
		}
	}

	else
	{

		if (AgingOkPercent[sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0]] > DestroyPersent)
		{
			switch (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0])
			{
			case 8:
				if (DownPersent < 70)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 70 && DownPersent < 85)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 9:
				if (DownPersent < 60)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 60 && DownPersent < 80)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 10:
				if (DownPersent < 50)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 50 && DownPersent < 70)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 11:
				if (DownPersent < 40)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 40 && DownPersent < 60)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 12:
				if (DownPersent < 30)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 30 && DownPersent < 50)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 13:
				if (DownPersent < 30)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 30 && DownPersent < 40)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 14:
				if (DownPersent < 20)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 20 && DownPersent < 30)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
				if (DownPersent < 10)
					AgingItemFaildNum = 1;
				else if (DownPersent >= 10 && DownPersent < 20)
					AgingItemFaildNum = 2;
				else AgingItemFaildNum = 0;
				break;
			}
		}
		else
		{
			if (sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0] < 10)
			{
				if (PlusAgingPercent[sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0]] > PlusPersent)
				{
					sinSetAgingItemIncreState(&sAging_Recv.DesCraftItem.sItemInfo);
					AgingItemFaildNum = 4;
				}
			}
		}

		if (cAging.AginStoneKind == 2 ||
			cAging.AginStoneKind == 3 ||
			cAging.AginStoneKind == 4 ||
			cAging.AginStoneKind == 5)
		{
			if (AgingItemFaildNum == 0)
			{
				if (rand() % 100 < 81)
					AgingItemFaildNum = 1;
				else
					AgingItemFaildNum = 2;
			}
		}
	}
#endif


	if (AgingItemFaildNum == 0)
	{
		if (cAging.AginStoneKind == 2 ||
			cAging.AginStoneKind == 3 ||
			cAging.AginStoneKind == 4 ||
			cAging.AginStoneKind == 5)

		{
			if (rand() % 100 < 81)
				AgingItemFaildNum = 1;
			else
				AgingItemFaildNum = 2;
		}
	}

	if (!AgingItemFaildNum)
	{
		sAging_Recv.Result = FALSE;
		return FALSE;
	}



	if (AgingItemFaildNum == 1 || AgingItemFaildNum == 2)
	{
		sinAgingItemInit(&pItem->sItemInfo, AgingItemFaildNum);

	}



	if ((pItem->CODE & sinITEM_MASK2) == sinWC1 ||
		(pItem->CODE & sinITEM_MASK2) == sinWS2 ||
		(pItem->CODE & sinITEM_MASK2) == sinWD1 ||
		(pItem->CODE & sinITEM_MASK2) == sinWP1)
	{
		pItem->sItemInfo.ItemAgingCount[1] = AgingLevelCritical[pItem->sItemInfo.ItemAgingNum[0]];
		if (AgingItemFaildNum <= 2)
			pItem->sItemInfo.ItemAgingCount[0] = pItem->sItemInfo.ItemAgingCount[1] / 2;

	}


	if ((pItem->CODE & sinITEM_MASK2) == sinWA1 ||
		(pItem->CODE & sinITEM_MASK2) == sinWH1 ||
		(pItem->CODE & sinITEM_MASK2) == sinWM1 ||
		(pItem->CODE & sinITEM_MASK2) == sinWN1 ||
		(pItem->CODE & sinITEM_MASK2) == sinWS1 ||
		(pItem->CODE & sinITEM_MASK2) == sinWT1)
	{
		pItem->sItemInfo.ItemAgingCount[1] = AgingLevelAttack[pItem->sItemInfo.ItemAgingNum[0]];
		if (AgingItemFaildNum <= 2)
			pItem->sItemInfo.ItemAgingCount[0] = pItem->sItemInfo.ItemAgingCount[1] / 2;

	}




	if ((pItem->CODE & sinITEM_MASK2) == sinDS1)
	{
		pItem->sItemInfo.ItemAgingCount[1] = AgingLevelBlock[pItem->sItemInfo.ItemAgingNum[0]];
		if (AgingItemFaildNum <= 2)
			pItem->sItemInfo.ItemAgingCount[0] = pItem->sItemInfo.ItemAgingCount[1] / 2;

	}



	if ((pItem->CODE & sinITEM_MASK2) == sinDA1 ||
		(pItem->CODE & sinITEM_MASK2) == sinDA2 ||
		(pItem->CODE & sinITEM_MASK2) == sinOM1 ||
		(pItem->CODE & sinITEM_MASK2) == sinDB1 ||
		(pItem->CODE & sinITEM_MASK2) == sinDG1 ||
		(pItem->CODE & sinITEM_MASK2) == sinOA2)
	{
		pItem->sItemInfo.ItemAgingCount[1] = AgingLevelHit[pItem->sItemInfo.ItemAgingNum[0]];
		if (AgingItemFaildNum <= 2)
			pItem->sItemInfo.ItemAgingCount[0] = pItem->sItemInfo.ItemAgingCount[1] / 2;

	}

	if (pItem->CODE == (sinOR2 | sin01))
	{
		pItem->sItemInfo.ItemAgingCount[1] = 60 * 20;

	}

	pItem->sItemInfo.ItemAgingNum[1] = 1;
	pItem->sItemInfo.ItemKindCode = ITEM_KIND_AGING;
	if (AgingItemFaildNum >= 3)
		pItem->sItemInfo.ItemAgingCount[0] = 0;












	memcpy(&sAging_Recv.DesCraftItem, pItem, sizeof(sITEM));
	ReformMixItem(&sAging_Recv.DesCraftItem.sItemInfo);
	sAging_Recv.Result = AgingItemFaildNum;


	return TRUE;
}


int cAGING::CancelAgingItem(int Flag)
{
	if (MixItemNoCopyFlag)return FALSE;

	for (int i = 0; i < 15; i++)
	{
		if (sAgingItem.AgingItem[i].Flag)
		{
			if (!cInvenTory.AutoSetInvenItem(&sAgingItem.AgingItem[i]))
			{
				sinThrowItemToFeild(&sAgingItem.AgingItem[i]);
			}

			sAgingItem.AgingItem[i].Flag = 0;
		}
	}

	for (int y = 0; y < 4; y++)
	{
		for (int h = 0; h < 3; h++)
		{
			AgingLevelSheltomIndex[y][h] = 0;
		}

	}

	AgingCheckSheltomFlag = 0;
	AgingSheltomCnt2 = 0;
	if (!Flag)
		cAging.OpenFlag = 0;

	ResetInvenItemCode();
	return TRUE;
}


int cAGING::CheckItem(sITEM *pItem)
{
	int k = 0;
	int SheltomCnt = 0;
	if ((pItem->CODE & sinITEM_MASK2) == sinOS1)
	{
		AgingSheltomCnt2++;

	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				AgingLevelSheltomIndex[i][j] = AgingLevelSheltom[pItem->sItemInfo.ItemAgingNum[0]][k++];

			}

		}

	}
	if (AgingSheltomCnt2)
	{
		if (sAgingItem.AgingItem[0].Flag)
		{
			for (int h = 0; h < 12; h++)
			{
				if (AgingLevelSheltom[sAgingItem.AgingItem[0].sItemInfo.ItemAgingNum[0]][h])
					SheltomCnt++;
			}

		}
		if (AgingSheltomCnt2 == SheltomCnt)
			AgingCheckSheltomFlag = 1;
		else
			AgingCheckSheltomFlag = 0;

	}

	return FALSE;

}


DWORD AgingItemCode3[17] = { sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWD1,sinWN1,sinWS1,sinWS2,sinWT1,sinDA1,sinDS1,sinOM1,sinDA2,sinDB1,sinDG1,sinOA2 };

int cAGING::SetAgingItemAreaCheck(sITEM *pItem)
{

	DWORD SheltomCODE[MAX_SHELTOM] = { sin01,sin02,sin03,sin04,sin05,sin06,sin07,sin08,sin09,sin10,sin11,sin12,sin13,sin14 };
	int SheltomIndex2 = 0;
	int i, j;

	if (pItem->sItemInfo.CODE == (sinBI1 | sin10) || pItem->sItemInfo.CODE == (sinBI1 | sin11) ||
		pItem->sItemInfo.CODE == (sinBI1 | sin60) || pItem->sItemInfo.CODE == (sinBI1 | sin61) ||
		pItem->sItemInfo.CODE == (sinBI1 | sin85))
	{
		cAging.AginStoneKind = 0;
		int AgingStoneX = 159 + 11, AgingStoneY = 268 + 11 + sinInterHeight2;
		TradeColorIndex = 0;
		cTrade.InitTradeColorRect();
		if (AgingStoneX <= pItem->x + 22 && AgingStoneX > pItem->x &&AgingStoneY< pItem->y + 22 && AgingStoneY > pItem->y)
		{
			pItem->SetX = AgingStoneX + (((pItem->x + 22 - AgingStoneX) / 22) * 22) - 11;
			pItem->SetY = AgingStoneY + (((pItem->y + 22 - AgingStoneY) / 22) * 22) - 11;
			pItem->ItemPosition = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;
			if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
			{
				cTrade.InitTradeColorRect();
				return FALSE;
			}
			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			return TRUE;
		}
	}

	if (pItem->sItemInfo.CODE == (sinBI1 | sin61))
	{
		cAging.AginStoneKind = 4;
		int AgingStoneX = 159 + 11, AgingStoneY = 268 + 11 + sinInterHeight2;
		TradeColorIndex = 0;
		cTrade.InitTradeColorRect();
		if (AgingStoneX <= pItem->x + 22 && AgingStoneX > pItem->x &&AgingStoneY< pItem->y + 22 && AgingStoneY > pItem->y)
		{
			pItem->SetX = AgingStoneX + (((pItem->x + 22 - AgingStoneX) / 22) * 22) - 11;
			pItem->SetY = AgingStoneY + (((pItem->y + 22 - AgingStoneY) / 22) * 22) - 11;
			pItem->ItemPosition = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;
			if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
			{
				cTrade.InitTradeColorRect();
				return FALSE;
			}
			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			return TRUE;
		}
	}



	if (pItem->sItemInfo.CODE == (sinBI1 | sin85))
	{
		cAging.AginStoneKind = 5;
		int AgingStoneX = 159 + 11, AgingStoneY = 268 + 11 + sinInterHeight2;
		TradeColorIndex = 0;
		cTrade.InitTradeColorRect();
		if (AgingStoneX <= pItem->x + 22 && AgingStoneX > pItem->x &&AgingStoneY< pItem->y + 22 && AgingStoneY > pItem->y)
		{
			pItem->SetX = AgingStoneX + (((pItem->x + 22 - AgingStoneX) / 22) * 22) - 11;
			pItem->SetY = AgingStoneY + (((pItem->y + 22 - AgingStoneY) / 22) * 22) - 11;
			pItem->ItemPosition = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;
			if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
			{
				cTrade.InitTradeColorRect();
				return FALSE;
			}
			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			return TRUE;
		}
	}



	if ((pItem->sItemInfo.CODE  & sinITEM_MASK2) == sinMA2)
	{
		if (sAgingItem.AgingItem[0].Flag && (sAgingItem.AgingItem[0].sItemInfo.CODE & sinITEM_MASK2) == sinMA1)
		{
			TradeColorIndex = 0;
			TradeCrashItemIndex[0] = 0;
			cTrade.InitTradeColorRect();
			TradeStartX = 218;
			TradeStartY = 193 + sinInterHeight2;
			TradeEndX = TradeStartX + (3 * 22);
			TradeEndY = TradeStartY + (4 * 22);

			for (i = pItem->x + 11; i < pItem->x + pItem->w; i += 22)
			{
				for (j = pItem->y + 11; j < pItem->y + pItem->h; j += 22)
				{
					if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
					{
						TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
						TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
						TradeColorRect.right = pItem->w;
						TradeColorRect.bottom = pItem->h;
						if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
						{
							cTrade.InitTradeColorRect();
							return FALSE;
						}

						pItem->SetX = TradeColorRect.left;
						pItem->SetY = TradeColorRect.top;
						pItem->ItemPosition = 0;
						TradeColorIndex = SET_ITEM_CHECK_COLOR;

						if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
						{
							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;
						}
						return TRUE;

					}

				}

			}
		}

	}

	if ((pItem->sItemInfo.CODE  & sinITEM_MASK2) == sinMA1)
	{
		TradeColorIndex = 0;
		TradeCrashItemIndex[0] = 0;
		cTrade.InitTradeColorRect();

		TradeStartX = 58;
		TradeStartY = 193 + sinInterHeight2;
		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);
		if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
		{
			TradeColorRect.left = TradeStartX;
			TradeColorRect.top = TradeStartY;
			TradeColorRect.right = TradeEndX - TradeStartX;
			TradeColorRect.bottom = TradeEndY - TradeStartY;


			pItem->SetX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->w) / 2;
			pItem->SetY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->h) / 2;
			pItem->ItemPosition = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;
			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;

			}
			return TRUE;
		}
	}


	for (int y = 0; y < MAX_SHELTOM; y++)
	{
		if (SheltomCODE[y] == (pItem->sItemInfo.CODE & sinITEM_MASK3))
		{
			SheltomIndex2 = y + 1;
			break;
		}
	}

	int AgingOkWeaponGroupFlag = 0;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	if ((pItem->CODE & sinITEM_MASK2) == sinOS1)
	{





		for (int p = 0; p < 4; p++)
		{
			for (int m = 0; m < 3; m++)
			{
				if (AgingLevelSheltomIndex[p][m] == SheltomIndex2)
				{
					TradeStartX = AgingLevelSheltomXY[p][m].x;
					TradeStartY = AgingLevelSheltomXY[p][m].y;
					TradeEndX = TradeStartX + 22;
					TradeEndY = TradeStartY + 22;
					for (i = pItem->x + 11; i < pItem->x + pItem->w; i += 22)
					{
						for (j = pItem->y + 11; j < pItem->y + pItem->h; j += 22)
						{
							if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
							{
								TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
								TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
								TradeColorRect.right = pItem->w;
								TradeColorRect.bottom = pItem->h;
								if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
								{
									cTrade.InitTradeColorRect();
									return FALSE;
								}

								pItem->SetX = TradeColorRect.left;
								pItem->SetY = TradeColorRect.top;
								pItem->ItemPosition = 0;
								if ((pItem->CODE & sinITEM_MASK3) > sin20)
								{
									TradeColorIndex = NOT_SETTING_COLOR;
								}
								else
									TradeColorIndex = SET_ITEM_CHECK_COLOR;

								if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
								{
									TradeColorIndex = NOT_SETTING_COLOR;
									return FALSE;

								}
								return TRUE;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		TradeColorIndex = 0;
		TradeCrashItemIndex[0] = 0;
		cTrade.InitTradeColorRect();

		TradeStartX = 58;
		TradeStartY = 193 + sinInterHeight2;
		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);
		if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
		{
			TradeColorRect.left = TradeStartX;
			TradeColorRect.top = TradeStartY;
			TradeColorRect.right = TradeEndX - TradeStartX;
			TradeColorRect.bottom = TradeEndY - TradeStartY;


			pItem->SetX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->w) / 2;
			pItem->SetY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->h) / 2;
			pItem->ItemPosition = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;

			for (int i = 0; i < 15; i++)
			{
				if ((pItem->CODE &  sinITEM_MASK2) == AgingItemCode3[i])
				{
					AgingOkWeaponGroupFlag = 1;

				}
			}


			if (pItem->sItemInfo.CODE == (sinOR2 | sin01))AgingOkWeaponGroupFlag = 1;


			if (!AgingOkWeaponGroupFlag || pItem->sItemInfo.ItemAgingNum[0] >= MAX_AGING)
			{
				TradeColorIndex = NOT_AGING_ITEM;
				return FALSE;
			}


			if (pItem->sItemInfo.UniqueItem || pItem->sItemInfo.ItemKindCode == ITEM_KIND_CRAFT || MouseItem.sItemInfo.ItemAgingNum[1] == 1 ||
				pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST ||
				pItem->sItemInfo.SpecialItemFlag[0] == CHECK_GIVE_ITEM ||
				pItem->sItemInfo.CODE == (sinGF1 | sin01) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin02) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin07) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin08) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin05) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin06) ||

				((pItem->sItemInfo.CODE == (sinDA1 | sin31))) ||
				((pItem->sItemInfo.CODE == (sinDA2 | sin31))) ||
				((pItem->sItemInfo.CODE == (sinDA1 | sin32))) ||
				((pItem->sItemInfo.CODE == (sinDA2 | sin32))) ||
				((pItem->sItemInfo.CODE == (sinDA1 | sin33))) ||
				((pItem->sItemInfo.CODE == (sinDA2 | sin33))) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin34)) || (pItem->sItemInfo.CODE == (sinDA2 | sin34)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin35)) || (pItem->sItemInfo.CODE == (sinDA2 | sin35)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin36)) || (pItem->sItemInfo.CODE == (sinDA2 | sin36)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin37)) || (pItem->sItemInfo.CODE == (sinDA2 | sin37)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin38)) || (pItem->sItemInfo.CODE == (sinDA2 | sin38)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin39)) || (pItem->sItemInfo.CODE == (sinDA2 | sin39)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin40)) || (pItem->sItemInfo.CODE == (sinDA2 | sin40)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin41)) || (pItem->sItemInfo.CODE == (sinDA2 | sin41)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin42)) || (pItem->sItemInfo.CODE == (sinDA2 | sin42)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin43)) || (pItem->sItemInfo.CODE == (sinDA2 | sin43)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin44)) || (pItem->sItemInfo.CODE == (sinDA2 | sin44)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin45)) || (pItem->sItemInfo.CODE == (sinDA2 | sin45)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin46)) || (pItem->sItemInfo.CODE == (sinDA2 | sin46)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin48)) || (pItem->sItemInfo.CODE == (sinDA2 | sin48)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin54)) || (pItem->sItemInfo.CODE == (sinDA2 | sin54)) ||
				(pItem->sItemInfo.CODE == (sinDA1 | sin55)) || (pItem->sItemInfo.CODE == (sinDA2 | sin55)) ||
				(pItem->sItemInfo.CODE == (sinOR2 | sin33)) || (pItem->sItemInfo.CODE == (sinSP1 | sin35)) ||
				(pItem->sItemInfo.CODE == (sinOA1 | sin36)) ||
				(pItem->sItemInfo.CODE == (sinOA1 | sin37)) || (pItem->sItemInfo.CODE == (sinSP1 | sin36)) ||
				(pItem->sItemInfo.CODE == (sinOA2 | sin33)) ||
				(pItem->sItemInfo.CODE == (sinDB1 | sin33)) ||
				(pItem->sItemInfo.CODE == (sinSP1 | sin37)) || (pItem->sItemInfo.CODE == (sinSP1 | sin38)) ||
				(pItem->sItemInfo.CODE == (sinBI1 | sin84)) ||
				(pItem->sItemInfo.CODE == (sinDB1 | sin34)) ||
				(pItem->sItemInfo.CODE == (sinOA2 | sin34)) ||
				(pItem->sItemInfo.CODE == (sinSP1 | sin42))

				)
			{
				TradeColorIndex = NOT_AGING_ITEM;
				return FALSE;
			}
			int kk = 0;

			for (kk = 0; kk < NotSet_Item_CODECnt; kk++)
			{
				if (NotSet_Item_CODE[kk] == pItem->sItemInfo.CODE)
				{
					TradeColorIndex = NOT_AGING_ITEM;
					return FALSE;
				}

			}
			for (kk = 0; kk < NotSet_Item_MASKCnt; kk++)
			{
				if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotSet_Item_MASK[kk])
				{
					TradeColorIndex = NOT_AGING_ITEM;
					return FALSE;
				}

			}
			for (kk = 0; kk < NotSet_Item_KINDCnt; kk++)
			{
				if (NotSet_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)
				{
					TradeColorIndex = NOT_AGING_ITEM;
					return FALSE;
				}

			}



			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 3))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;

			}

#ifdef AGING_MONEY_FREE 

#else
#ifdef HASIEGE_MODE

			if (cShop.haBuyMoneyCheck((pItem->sItemInfo.Price + (pItem->sItemInfo.Price*pItem->sItemInfo.ItemAgingNum[0])) / 2) == 0)
			{
#else
			if (sinChar->Money < (pItem->sItemInfo.Price + (pItem->sItemInfo.Price*pItem->sItemInfo.ItemAgingNum[0])) / 2)
			{
#endif

				TradeColorIndex = NOT_ENOUGH_MONEY;
				return FALSE;
			}
#endif
			return TRUE;
		}

	}


	return TRUE;
}


int AgingItemCheckDelayTime = 0;


int cAGING::CheckAgingData()
{


	return TRUE;
}


int cWAREHOUSE::CopyItemNotPickUp(sITEM *pItem, int JumpIndex)
{
	int i;
	if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)return TRUE;
	for (i = 0; i < 100; i++)
	{
		if (sWareHouse.WareHouseItem[i].Flag)
		{
			if (JumpIndex == i)continue;
			if (CompareItems(&pItem->sItemInfo, &sWareHouse.WareHouseItem[i].sItemInfo))
			{
				CopyItemIndex7[i] = i + 1;
				return FALSE;

			}

		}

	}

	return TRUE;
}

int SendServerFlag7 = 0;

int cWAREHOUSE::CheckCopyItem()
{
	int i, j;
	if (SendServerFlag7)return FALSE;
	for (i = 0; i < 100; i++)
	{
		if (sWareHouse.WareHouseItem[i].Flag)
		{
			for (j = 0; j < 100; j++)
			{
				if (i != j && sWareHouse.WareHouseItem[j].Flag)
				{
					if (CompareItems(&sWareHouse.WareHouseItem[i].sItemInfo, &sWareHouse.WareHouseItem[j].sItemInfo))
					{
						SendSetHackUser2(1010, sWareHouse.WareHouseItem[i].CODE);
						SendServerFlag7 = 1;
						break;
					}
				}
			}
		}
	}



	return TRUE;
}
int CheckCraftMoney = 0;


int cCRAFTITEM::sinSendCraftItem()
{

	if (MixItemNoCopyFlag)return FALSE;
	int i = 0;



	memcpy(&sCraftItemBackUp, &sCraftItem, sizeof(sCRAFTITEM));

	MixItemNoCopyFlag = 1;

	if (ForceFlag)
	{
		memset(&sCraftItem_Send.DesCraftItem, 0, sizeof(sITEM));
		memset(&sCraftItemBackUp, 0, sizeof(sCRAFTITEM));
		sCraftItem_Send.DesCraftItem.CODE = 1000;
		sCraftItem_Send.Money = ForceItemPrice;

	}

	if (cCraftItem.iReconItemFlag)
	{
		memset(&sCraftItem_Send.DesCraftItem, 0, sizeof(sITEM));
		memset(&sCraftItemBackUp, 0, sizeof(sCRAFTITEM));
		sCraftItem_Send.DocIndex = 2000;

	}

	if (sCraftItem.CraftItem[0].Flag)
	{
		sCraftItem_Send.DesCraftItem = sCraftItem.CraftItem[0];
		sCraftItem_Send.Money = sCraftItem.CraftItem[0].sItemInfo.Price;
	}
	for (i = 0; i < 12; i++)
	{
		if (sCraftItem.CraftItem[i + 1].Flag)
		{
			sCraftItem_Send.SheltomCode[i] = sCraftItem.CraftItem[i + 1].CODE;
			sCraftItem_Send.CheckSum[i] = sCraftItem.CraftItem[i + 1].sItemInfo.ItemHeader.dwChkSum;
			sCraftItem_Send.Head[i] = sCraftItem.CraftItem[i + 1].sItemInfo.ItemHeader.Head;
		}
	}


	if (sCraftItem.CraftItem[14].Flag)
	{
		sCraftItem_Send.A_StoneItemCode = sCraftItem.CraftItem[14].CODE;
		sCraftItem_Send.A_StoneCheckSum = sCraftItem.CraftItem[14].sItemInfo.ItemHeader.dwChkSum;
		sCraftItem_Send.A_StoneHead = sCraftItem.CraftItem[14].sItemInfo.ItemHeader.Head;
	}

	CheckCraftMoney = sCraftItem_Send.Money;

	CraftItemSendServerIndex++;
	sCraftItem_Send.Index = CraftItemSendServerIndex;

	cCraftItem.iReconItemFlag = 0;

	if (ForceFlag)
	{
		SendWingItemToServer(&sCraftItem_Send);
	}
	else
	{
		SendCraftItemToServer(&sCraftItem_Send);
	}

	return TRUE;
}

int cAGING::sinSendAgingItem()
{
	int i = 0;

	memcpy(&sAgingItemBackUp, &sAgingItem, sizeof(sAGINGITEM));

	MixItemNoCopyFlag = 1;
	if (sAgingItem.AgingItem[0].Flag)
	{
		sAging_Send.DesCraftItem = sAgingItem.AgingItem[0];
	}
	for (i = 0; i < 12; i++)
	{
		if (sAgingItem.AgingItem[i + 1].Flag)
		{
			sAging_Send.SheltomCode[i] = sAgingItem.AgingItem[i + 1].CODE;
			sAging_Send.CheckSum[i] = sAgingItem.AgingItem[i + 1].sItemInfo.ItemHeader.dwChkSum;
			sAging_Send.Head[i] = sAgingItem.AgingItem[i + 1].sItemInfo.ItemHeader.Head;
		}
	}

	if (sAgingItem.AgingItem[14].Flag)
	{
		sAging_Send.A_StoneItemCode = sAgingItem.AgingItem[14].CODE;
		sAging_Send.A_StoneCheckSum = sAgingItem.AgingItem[14].sItemInfo.ItemHeader.dwChkSum;
		sAging_Send.A_StoneHead = sAgingItem.AgingItem[14].sItemInfo.ItemHeader.Head;
	}

#ifdef AGING_MONEY_FREE 
	sAging_Send.Money = 0;
	CheckCraftMoney = sAging_Send.Money;
#else
	sAging_Send.Money = sAgingItem.AgingItem[0].sItemInfo.Price;
	CheckCraftMoney = sAging_Send.Money;
#endif

	CraftItemSendServerIndex++;
	sAging_Send.Index = CraftItemSendServerIndex;


	SendAgingItemToServer(&sAging_Send);



#ifdef AGING_MONEY_FREE 
	int Price = 0;
#else
	int Price = ((sAgingItem.AgingItem[0].sItemInfo.ItemAgingNum[0] + 1)*sAgingItem.AgingItem[0].sItemInfo.Price) / 2;
#endif


	CheckCharForm();
	sinMinusMoney(Price, 1);
	ReformCharForm();
	SendSaveMoney();
	return TRUE;
}

int cCRAFTITEM::sinRecvCraftItem(sCRAFTITEM_SERVER *pCraftItem_Server)
{
	memcpy(&sCraftItem_Recv, pCraftItem_Server, sizeof(sCRAFTITEM_SERVER));

	return TRUE;
}


int cAGING::sinRecvAgingItem(sCRAFTITEM_SERVER *pCraftItem_Server)
{
	memcpy(&sAging_Recv, pCraftItem_Server, sizeof(sCRAFTITEM_SERVER));

	return TRUE;
}


int cAGING::sinRecvAgingItemResult(sCRAFTITEM_SERVER *pCraftItem_Server)
{


	if (pCraftItem_Server->DesCraftItem.sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON)
	{
		if (pCraftItem_Server->Result)
		{
			cInvenTory.DeleteInvenItemToServer(TempQuestItem.sItemInfo.CODE, TempQuestItem.sItemInfo.ItemHeader.Head, TempQuestItem.sItemInfo.ItemHeader.dwChkSum);
			memset(&TempQuestItem, 0, sizeof(sITEM));

			pCraftItem_Server->DesCraftItem.sItemInfo.ItemAgingCount[0] = pCraftItem_Server->DesCraftItem.sItemInfo.ItemAgingCount[1];
			if (cInvenTory.AutoSetInvenItem(&pCraftItem_Server->DesCraftItem))
			{
				cMessageBox.ShowMessage(MESSAGE_QUEST_ITEM_AGING);
				sinPlaySound(SIN_SOUND_EAT_POTION2);
				StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_AGING);
				sinQuest_ChangeJob3.Monster[0] = pCraftItem_Server->DesCraftItem.sItemInfo.ItemAgingNum[0];
				StartQuest_Code(sinQuest_ChangeJob3.CODE);

			}

			if (pCraftItem_Server->DesCraftItem.sItemInfo.ItemAgingNum[0] == 4)
			{
				sinQuest_ChangeJob3.State = 4;
			}
		}
		else
		{

			cInvenTory.AutoSetInvenItem(&TempQuestItem);

		}
		memset(&sAging_Recv, 0, sizeof(sCRAFTITEM_SERVER));
		memset(&sAging_Send, 0, sizeof(sCRAFTITEM_SERVER));
		NotChangeSetItemFlag = 0;
		return TRUE;

	}

	if (!cAging.OpenFlag)
	{
		AgingCheckSheltomFlag = 0;
		AgingSheltomCnt2 = 0;
		MixItemNoCopyFlag = 0;
		memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));
		memset(&sCraftItem_Send, 0, sizeof(sCRAFTITEM_SERVER));
		MixCancelButtonDelayFlag = 0;
		return FALSE;
	}

	if (pCraftItem_Server->Result)
	{
		if ((pCraftItem_Server->DesCraftItem.sItemInfo.CODE & sinITEM_MASK2) == sinQT1)
		{
			sinSetQuestItem(&pCraftItem_Server->DesCraftItem.sItemInfo);
		}
		else
		{
			if (!cInvenTory.AutoSetInvenItem(&pCraftItem_Server->DesCraftItem))
			{
				sinThrowItemToFeild(&pCraftItem_Server->DesCraftItem);

			}
			CheckCharForm();
			switch (pCraftItem_Server->Result)
			{
			case 1:
				cMessageBox.ShowMessage(MESSAGE_AGING_LEVEL_DOWN1);
				sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
				break;
			case 2:
				cMessageBox.ShowMessage(MESSAGE_AGING_LEVEL_DOWN2);
				sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
				break;
			case 3:
				cMessageBox.ShowMessage(MESSAGE_AGING_LEVEL_PLUS);
				sinPlaySound(SIN_SOUND_EAT_POTION2);
				break;
			case 4:
				cMessageBox.ShowMessage(MESSAGE_AGING_LEVEL_PLUS2);
				sinPlaySound(SIN_SOUND_EAT_POTION2);
				break;
			}
			SendSaveMoney();
			ReformCharForm();
		}
	}
	else
	{
		sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
		cMessageBox.ShowMessage(MESSAGE_FAILD_AGING_ITEM);

	}

	for (int y = 0; y < 4; y++)
	{
		for (int h = 0; h < 3; h++)
		{
			AgingLevelSheltomIndex[y][h] = 0;
		}

	}

	for (int i = 0; i < 15; i++)
	{
		if (sAgingItemBackUp.AgingItem[i].Flag)
		{
			cInvenTory.DeleteInvenItemToServer(sAgingItemBackUp.AgingItem[i].sItemInfo.CODE,
				sAgingItemBackUp.AgingItem[i].sItemInfo.ItemHeader.Head,
				sAgingItemBackUp.AgingItem[i].sItemInfo.ItemHeader.dwChkSum);
		}

	}


	memset(&sAgingItem, 0, sizeof(sAGINGITEM));
	memset(&sAgingItemBackUp, 0, sizeof(sAGINGITEM));
	cAging.OpenFlag = 0;
	AgingCheckSheltomFlag = 0;
	AgingSheltomCnt2 = 0;
	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;
	memset(&sAging_Recv, 0, sizeof(sCRAFTITEM_SERVER));
	memset(&sAging_Send, 0, sizeof(sCRAFTITEM_SERVER));
	cInvenTory.CheckDamage();
	return TRUE;
}

bool cAGING::isAgeableItem(sITEM * pItem)
{
	if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinBI1)
	{
		if ((pItem->sItemInfo.CODE & sinITEM_MASK3) == sin10 ||
			(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin11 ||
			(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin60 ||
			(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin61 ||
			(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin85)
		{
			return true;
		}
		return false;
	}
	else if ((pItem->sItemInfo.CODE  & sinITEM_MASK2) == sinMA2 ||
		(pItem->sItemInfo.CODE  & sinITEM_MASK2) == sinMA2)
	{
		return true;
	}
	else if ((pItem->sItemInfo.CODE & sinITEM_MASK2) != sinOS1)
	{
		bool isAgeable = false;
		for (int i = 0; i < 15; i++)
		{
			if ((pItem->CODE &  sinITEM_MASK2) == AgingItemCode3[i])
			{
				isAgeable = true;
				break;
			}
		}

		if (pItem->sItemInfo.CODE == (sinOR2 | sin01))
			isAgeable = false;

		if (!isAgeable || pItem->sItemInfo.ItemAgingNum[0] >= MAX_AGING)
		{
			return false;
		}

		if (pItem->sItemInfo.CODE == (sinDA1 | sin51) ||
			pItem->sItemInfo.CODE == (sinDA2 | sin51))
			return false;

		if (pItem->sItemInfo.UniqueItem || pItem->sItemInfo.ItemKindCode == ITEM_KIND_CRAFT || pItem->sItemInfo.ItemAgingNum[1] > 0 ||
			pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST ||
			pItem->sItemInfo.SpecialItemFlag[0] == CHECK_GIVE_ITEM ||
			pItem->sItemInfo.CODE == (sinGF1 | sin01) ||
			pItem->sItemInfo.CODE == (sinGF1 | sin02) ||
			pItem->sItemInfo.CODE == (sinGF1 | sin07) ||
			pItem->sItemInfo.CODE == (sinGF1 | sin08) ||
			pItem->sItemInfo.CODE == (sinGF1 | sin05) ||
			pItem->sItemInfo.CODE == (sinGF1 | sin06) ||
			((pItem->sItemInfo.CODE == (sinDA1 | sin31))) ||
			((pItem->sItemInfo.CODE == (sinDA2 | sin31))) ||
			((pItem->sItemInfo.CODE == (sinDA1 | sin32))) ||
			((pItem->sItemInfo.CODE == (sinDA2 | sin32))) ||
			((pItem->sItemInfo.CODE == (sinDA1 | sin33))) ||
			((pItem->sItemInfo.CODE == (sinDA2 | sin33))) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin34)) || (pItem->sItemInfo.CODE == (sinDA2 | sin34)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin35)) || (pItem->sItemInfo.CODE == (sinDA2 | sin35)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin36)) || (pItem->sItemInfo.CODE == (sinDA2 | sin36)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin37)) || (pItem->sItemInfo.CODE == (sinDA2 | sin37)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin38)) || (pItem->sItemInfo.CODE == (sinDA2 | sin38)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin39)) || (pItem->sItemInfo.CODE == (sinDA2 | sin39)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin40)) || (pItem->sItemInfo.CODE == (sinDA2 | sin40)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin41)) || (pItem->sItemInfo.CODE == (sinDA2 | sin41)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin42)) || (pItem->sItemInfo.CODE == (sinDA2 | sin42)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin43)) || (pItem->sItemInfo.CODE == (sinDA2 | sin43)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin44)) || (pItem->sItemInfo.CODE == (sinDA2 | sin44)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin45)) || (pItem->sItemInfo.CODE == (sinDA2 | sin45)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin46)) || (pItem->sItemInfo.CODE == (sinDA2 | sin46)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin48)) || (pItem->sItemInfo.CODE == (sinDA2 | sin48)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin54)) || (pItem->sItemInfo.CODE == (sinDA2 | sin54)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin55)) || (pItem->sItemInfo.CODE == (sinDA2 | sin55)) ||
			(pItem->sItemInfo.CODE == (sinOR2 | sin33)) || (pItem->sItemInfo.CODE == (sinSP1 | sin35)) ||
			(pItem->sItemInfo.CODE == (sinOA1 | sin36)) ||
			(pItem->sItemInfo.CODE == (sinOA1 | sin37)) || (pItem->sItemInfo.CODE == (sinSP1 | sin36)) ||
			(pItem->sItemInfo.CODE == (sinOA2 | sin33)) ||
			(pItem->sItemInfo.CODE == (sinDB1 | sin33)) ||
			(pItem->sItemInfo.CODE == (sinSP1 | sin37)) || (pItem->sItemInfo.CODE == (sinSP1 | sin38)) ||
			(pItem->sItemInfo.CODE == (sinBI1 | sin84)) ||
			(pItem->sItemInfo.CODE == (sinDB1 | sin34)) ||
			(pItem->sItemInfo.CODE == (sinOA2 | sin34)) ||
			(pItem->sItemInfo.CODE == (sinSP1 | sin42))
			)
		{
			return false;
		}
		int kk = 0;
		for (kk = 0; kk < NotSet_Item_CODECnt; kk++)
		{
			if (NotSet_Item_CODE[kk] == pItem->sItemInfo.CODE)
			{
				return false;
			}
		}
		for (kk = 0; kk < NotSet_Item_MASKCnt; kk++)
		{
			if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotSet_Item_MASK[kk])
			{
				return false;
			}
		}
		for (kk = 0; kk < NotSet_Item_KINDCnt; kk++)
		{
			if (NotSet_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)
			{
				return false;
			}
		}
	}

	return true;
}

bool cAGING::isItemAreaEmpty()
{
	return sAgingItem.AgingItem[0].Flag == 0;
}

bool cAGING::isStoneAreaEmpty()
{
	return sAgingItem.AgingItem[14].Flag == 0;

}

bool cAGING::isSheltomAreaEmpty(sITEM * Item, int Area)
{
	DWORD SheltomCODE[MAX_SHELTOM] = { sin01,sin02,sin03,sin04,sin05,sin06,sin07,sin08,sin09,sin10,sin11,sin12,sin13,sin14 };

	int SheltomIndex = 0;
	for (int i = 0; i < MAX_SHELTOM; i++)
	{
		if (SheltomCODE[i] == (Item->CODE & sinITEM_MASK3))
		{
			SheltomIndex = i + 1;
			break;
		}
	}

	if (AgingLevelSheltomIndex[Area / 3][Area % 3] == SheltomIndex)
	{
		int CheckX = 218 + ((Area % 3) * 22);
		int CheckY = (193 + sinInterHeight2) + ((Area / 3) * 22);

		for (int i = 1; i < 15; i++)
		{
			if (sAgingItem.AgingItem[i].Flag && sAgingItem.AgingItem[i].CODE == Item->CODE)
			{
				if (sAgingItem.AgingItem[i].x >= CheckX && sAgingItem.AgingItem[i].x < CheckX + 22)
					if (sAgingItem.AgingItem[i].y >= CheckY && sAgingItem.AgingItem[i].y < CheckY + 22)
						return false;
			}
		}
		return true;
	}

	return false;
}


int cCRAFTITEM::sinRecvCraftItemResult(sCRAFTITEM_SERVER *pCraftItem_Server)
{
	CheckMixItemCopyFlag = 0;
	if (!cCraftItem.OpenFlag)
	{
		MixItemNoCopyFlag = 0;
		memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
		memset(&sCraftItemBackUp, 0, sizeof(sCRAFTITEM));
		memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));
		memset(&sCraftItem_Send, 0, sizeof(sCRAFTITEM_SERVER));
		MixCancelButtonDelayFlag = 0;
		return FALSE;

	}

	int i, LineCount = 0, Temp;



	if (pCraftItem_Server->Result)
	{
		if (pCraftItem_Server->DocIndex == 2000)
		{

			sITEM TempItem;
			if (LoadItemImage(&pCraftItem_Server->DesCraftItem.sItemInfo, &TempItem))
			{
				if (cInvenTory.CheckRequireItemToSet(&TempItem))
				{

					if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
					{
						sinThrowItemToFeild(&pCraftItem_Server->DesCraftItem);
						memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
						cCraftItem.OpenFlag = 0;
						return FALSE;
					}

				}

			}
			cMessageBox.ShowMessage(MESSAGE_RECONITEM_OK);
		}
		else
		{
			ShowItemCraftMessageFlag = 1;
			strcpy_s(szCraftItemBuff, sCraftItem_Info[pCraftItem_Server->DocIndex].Doc);

			Temp = lstrlen(szCraftItemBuff);
			for (i = 0; i < Temp; i++)
			{
				if (szCraftItemBuff[i] == '\r')
				{
					LineCount++;
				}
			}

			CraftItemMessageSize.x = 14;
			CraftItemMessageSize.y = ((LineCount) * 2) + 2;


			sinAgingSuccessFlag2 = 1;











			if (!cInvenTory.AutoSetInvenItem(&pCraftItem_Server->DesCraftItem))
			{
				sinThrowItemToFeild(&pCraftItem_Server->DesCraftItem);
			}



			if (sCraftItemBackUp.CraftItem[0].Flag)
			{
				cInvenTory.DeleteInvenItemToServer(sCraftItemBackUp.CraftItem[0].sItemInfo.CODE,
					sCraftItemBackUp.CraftItem[0].sItemInfo.ItemHeader.Head,
					sCraftItemBackUp.CraftItem[0].sItemInfo.ItemHeader.dwChkSum);
			}


		}
		cCraftItem.OpenFlag = 0;
		CheckCharForm();
		sinMinusMoney(sCraftItem.CraftItem[0].sItemInfo.Price, 1);
		ReformCharForm();
		SendSaveMoney();
		SaveGameData();
	}
	else
	{



		if (!cInvenTory.AutoSetInvenItem(&sCraftItem.CraftItem[0]))
		{
			sinThrowItemToFeild(&sCraftItem.CraftItem[0]);
		}




		CheckCharForm();
		sinMinusMoney(sCraftItem.CraftItem[0].sItemInfo.Price, 1);
		ReformCharForm();
		SendSaveMoney();

		cCraftItem.OpenFlag = 0;
		cMessageBox.ShowMessage(MESSAGE_FAILD_CRAFT_ITEM);
		sinPlaySound(SIN_SOUND_FAILD_MIXITEM);


	}


	for (i = 1; i < 15; i++)
	{
		if (sCraftItemBackUp.CraftItem[i].Flag)
		{
			cInvenTory.DeleteInvenItemToServer(sCraftItemBackUp.CraftItem[i].sItemInfo.CODE,
				sCraftItemBackUp.CraftItem[i].sItemInfo.ItemHeader.Head,
				sCraftItemBackUp.CraftItem[i].sItemInfo.ItemHeader.dwChkSum);
		}

	}
	memset(&sCraftItem, 0, sizeof(sCRAFTITEM));
	memset(&sCraftItemBackUp, 0, sizeof(sCRAFTITEM));
	memset(&sCraftItem_Recv, 0, sizeof(sCRAFTITEM_SERVER));
	memset(&sCraftItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;
	return TRUE;
}


int cWAREHOUSE::DeleteCopyItem()
{
	int i, j;
	for (i = 0; i < 100; i++)
	{
		if (sWareHouse.WareHouseItem[i].Flag)
		{
			for (j = 0; j < 100; j++)
			{
				if (i != j && sWareHouse.WareHouseItem[j].Flag)
				{
					if (CompareItems(&sWareHouse.WareHouseItem[i].sItemInfo, &sWareHouse.WareHouseItem[j].sItemInfo))
					{


						sWareHouse.WareHouseItem[j].Flag = 0;
						cWareHouse.ReFormWareHouse();
						break;
					}
				}
			}
		}
	}
	return TRUE;
}


int CopyMixItemCheckDelete(sITEM *pItem)
{
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (cInvenTory.InvenItem[i].Flag)
		{
			if (CompareItems(&cInvenTory.InvenItem[i].sItemInfo, &pItem->sItemInfo))
			{
				cInvenTory.InvenItem[i].Flag = 0;
			}
		}
		if (cInvenTory.InvenItemTemp[i].Flag)
		{
			if (CompareItems(&cInvenTory.InvenItemTemp[i].sItemInfo, &pItem->sItemInfo))
			{
				cInvenTory.InvenItemTemp[i].Flag = 0;
			}
		}
	}
	return TRUE;
}


int sinMakeItemCheck()
{
	int ResultCount = 0;
	int ResultCountCheck = 0;
	DWORD TempCODE[15] = { 0, };
	int  i = 0;

	for (i = 0; i < MAX_MAKEITEM_INFO; i++)
	{
		for (int p = 0; p < 15; p++)
		{
			if (sAgingItem.AgingItem[p].Flag)
				TempCODE[p] = sAgingItem.AgingItem[p].CODE;
		}

		for (int j = 0; j < 15; j++)
		{
			if (sMakeItem_Info[i].CODE[j])
			{
				ResultCount++;
				for (int k = 0; k < 15; k++)
				{
					if (sAgingItem.AgingItem[k].Flag && TempCODE[k])
					{
						if (TempCODE[k] == sMakeItem_Info[i].CODE[j])
						{
							ResultCountCheck++;
							TempCODE[k] = -1;
						}
					}
				}
			}
		}
		if (ResultCount && ResultCountCheck && (ResultCount == ResultCountCheck))
		{
			AgingCheckSheltomFlag = 1;
			return TRUE;
		}
		else AgingCheckSheltomFlag = 0;
		ResultCount = 0;
		ResultCountCheck = 0;

	}

	return TRUE;
}


int sinPosBoxNpc()
{






	HelpBoxKindIndex = SIN_POST_BOX;
	cSinHelp.sinShowHelp(SIN_HELP_KIND_POSTBOX, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, RGBA_MAKE(0, 15, 128, 125), PostBoxDocFilePath[0]);
	cInvenTory.OpenFlag = 1;
	cInterFace.CheckAllBox(SIN_INVENTORY);
	return TRUE;
}

int cCRAFTITEM::haCheckReconItem()
{
	int cnt[MAX_SEEL_COUNT] = { 0 };
	int CheckNotReconItem = 0;
	int CheckBlockCount = 0;
	cCraftItem.iReconItemFlag = 0;


	for (int k = 1; k < 14; k++)
	{
		if (sCraftItem.CraftItem[k].Flag)
		{
			if ((sCraftItem.CraftItem[k].CODE & sinITEM_MASK2) == sinSE1)
				CheckBlockCount++;
			else
				CheckNotReconItem++;
		}
		else
			memset(&sCraftItem.CraftItem[k], 0, sizeof(sITEM));
	}

	for (int i = 1; i < 14; i++)
	{
		if ((sCraftItem.CraftItem[i].CODE & sinITEM_MASK2) == sinSE1 && sCraftItem.CraftItem[i].Flag)
		{
			for (int k = 0; k < MAX_SEEL_COUNT; k++)
			{
				if (sCraftItem.CraftItem[i].CODE == sReconItem[k].dwCODE)
				{
					cnt[k]++;
					if (sReconItem[k].iCount == cnt[k] && CheckNotReconItem < 1 && CheckBlockCount == cnt[k])
					{
						cCraftItem.iReconItemFlag = 1;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

int cCRAFTITEM::haCraftSortItem(sCRAFTITEM *pCraftItem)
{

	int i;
	for (i = 1; i < 13; i++)
	{
		if (!pCraftItem->CraftItem[i].Flag)
		{
			pCraftItem->CraftItem[i] = pCraftItem->CraftItem[i + 1];
			pCraftItem->CraftItem[i + 1].Flag = 0;
		}
	}
	return TRUE;
}

bool cCRAFTITEM::isSheltomAreaEmpty(sITEM * Item, int Area)
{
	int CheckX = 218 + ((Area % 3) * 22);
	int CheckY = (193 + sinInterHeight2) + ((Area / 3) * 22);

	for (int i = 1; i < 15; i++)
	{
		if (sCraftItem.CraftItem[i].Flag)
		{
			if (sCraftItem.CraftItem[i].x >= CheckX && sCraftItem.CraftItem[i].x < CheckX + 22)
			{
				if (sCraftItem.CraftItem[i].y >= CheckY && sCraftItem.CraftItem[i].y < CheckY + 22)
				{
					return false;
				}
			}
		}
	}

	return true;

}

bool cCRAFTITEM::isMixableItem(sITEM* pItem)
{
	static DWORD MixItemCode[17] = { sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinDA1,sinDS1,sinOM1,sinDA2,sinDG1,sinDB1,sinOA2, sinOA1, sinOR1 };

	if ((pItem->sItemInfo.CODE & sinITEM_MASK2) != sinOS1 && (pItem->sItemInfo.CODE & sinITEM_MASK2) != sinSE1)
	{
		bool isMixable = false;
		for (int i = 0; i < sizeof(MixItemCode) / sizeof(DWORD); i++)
		{
			if ((pItem->CODE & sinITEM_MASK2) == MixItemCode[i])
			{
				isMixable = true;
				break;
			}
		}

		if (pItem->sItemInfo.CODE == (sinOR2 | sin01))
			isMixable = false;

		if (!isMixable)
			return false;

		if (pItem->sItemInfo.CODE == (sinDA1 | sin51) ||
			pItem->sItemInfo.CODE == (sinDA2 | sin51))
			return false;

		if (pItem->sItemInfo.UniqueItem || pItem->sItemInfo.ItemKindCode == ITEM_KIND_CRAFT || pItem->sItemInfo.ItemKindCode == ITEM_KIND_AGING ||
			pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST ||
			pItem->sItemInfo.SpecialItemFlag[0] == CHECK_GIVE_ITEM ||
			pItem->sItemInfo.CODE == (sinGF1 | sin01) ||
			pItem->sItemInfo.CODE == (sinGF1 | sin02) ||
			pItem->sItemInfo.CODE == (sinGF1 | sin07) ||
			pItem->sItemInfo.CODE == (sinGF1 | sin08) ||
			pItem->sItemInfo.CODE == (sinGF1 | sin05) ||
			pItem->sItemInfo.CODE == (sinGF1 | sin06) ||
			((pItem->sItemInfo.CODE == (sinDA1 | sin31))) ||
			((pItem->sItemInfo.CODE == (sinDA2 | sin31))) ||
			((pItem->sItemInfo.CODE == (sinDA1 | sin32))) ||
			((pItem->sItemInfo.CODE == (sinDA2 | sin32))) ||
			((pItem->sItemInfo.CODE == (sinDA1 | sin33))) ||
			((pItem->sItemInfo.CODE == (sinDA2 | sin33))) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin34)) || (pItem->sItemInfo.CODE == (sinDA2 | sin34)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin35)) || (pItem->sItemInfo.CODE == (sinDA2 | sin35)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin36)) || (pItem->sItemInfo.CODE == (sinDA2 | sin36)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin37)) || (pItem->sItemInfo.CODE == (sinDA2 | sin37)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin38)) || (pItem->sItemInfo.CODE == (sinDA2 | sin38)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin39)) || (pItem->sItemInfo.CODE == (sinDA2 | sin39)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin40)) || (pItem->sItemInfo.CODE == (sinDA2 | sin40)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin41)) || (pItem->sItemInfo.CODE == (sinDA2 | sin41)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin42)) || (pItem->sItemInfo.CODE == (sinDA2 | sin42)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin43)) || (pItem->sItemInfo.CODE == (sinDA2 | sin43)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin44)) || (pItem->sItemInfo.CODE == (sinDA2 | sin44)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin45)) || (pItem->sItemInfo.CODE == (sinDA2 | sin45)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin46)) || (pItem->sItemInfo.CODE == (sinDA2 | sin46)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin48)) || (pItem->sItemInfo.CODE == (sinDA2 | sin48)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin54)) || (pItem->sItemInfo.CODE == (sinDA2 | sin54)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin55)) || (pItem->sItemInfo.CODE == (sinDA2 | sin55)) ||
			(pItem->sItemInfo.CODE == (sinOR2 | sin33)) || (pItem->sItemInfo.CODE == (sinSP1 | sin35)) ||
			(pItem->sItemInfo.CODE == (sinOA1 | sin36)) ||
			(pItem->sItemInfo.CODE == (sinOA1 | sin37)) || (pItem->sItemInfo.CODE == (sinSP1 | sin36)) ||
			(pItem->sItemInfo.CODE == (sinOA2 | sin33)) ||
			(pItem->sItemInfo.CODE == (sinDB1 | sin33)) ||
			(pItem->sItemInfo.CODE == (sinSP1 | sin37)) || (pItem->sItemInfo.CODE == (sinSP1 | sin38)) ||
			(pItem->sItemInfo.CODE == (sinBI1 | sin84)) ||
			(pItem->sItemInfo.CODE == (sinDB1 | sin34)) ||
			(pItem->sItemInfo.CODE == (sinOA2 | sin34)) ||
			(pItem->sItemInfo.CODE == (sinSP1 | sin42))
			)
		{
			return false;
		}

		int kk = 0;
		for (kk = 0; kk < NotSet_Item_CODECnt; kk++)
		{
			if (NotSet_Item_CODE[kk] == pItem->sItemInfo.CODE)
			{
				return false;
			}
		}
		for (kk = 0; kk < NotSet_Item_MASKCnt; kk++)
		{
			if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotSet_Item_MASK[kk])
			{
				return false;
			}
		}
		for (kk = 0; kk < NotSet_Item_KINDCnt; kk++)
		{
			if (NotSet_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)
			{
				return false;
			}
		}
	}

	return true;
}


bool cCRAFTITEM::isItemAreaEmpty()
{
	return sCraftItem.CraftItem[0].Flag == 0;
}

bool cCRAFTITEM::isStoneAreaEmpty()
{
	return sCraftItem.CraftItem[14].Flag == 0;

}

int cCRAFTITEM::GetCraftCheckEmptyArea()
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - 22;
	cy = (22 * INVENTORY_BOX_COL) - 22;

	int count = 0;

	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (cInvenTory.InvenItem[i].Flag)
				{
					rect.left = cInvenTory.InvenItem[i].x;
					rect.right = cInvenTory.InvenItem[i].x + cInvenTory.InvenItem[i].w;
					rect.top = cInvenTory.InvenItem[i].y;
					rect.bottom = cInvenTory.InvenItem[i].y + cInvenTory.InvenItem[i].h;

					if (cntx > rect.left - 22 && cntx< rect.right &&
						cnty > rect.top - 22 && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				count++;
			}
		}
	}
	if (count)
		return count;
	else
		return 0;
}


int cMIXTURERESET::SetMixtureItemResetAreaCheck(sITEM *pItem)
{
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	if ((pItem->CODE & sinITEM_MASK2) == sinBI1)
	{

		if ((pItem->sItemInfo.CODE & sinITEM_MASK3) != sin89)
			return FALSE;


		TradeStartX = AgingLevelSheltomXY[0][0].x + 23;
		TradeStartY = AgingLevelSheltomXY[0][0].y + 31;
		TradeEndX = TradeStartX + 22;
		TradeEndY = TradeStartY + 22;

		int i, j;
		for (i = pItem->x + 11; i < pItem->x + pItem->w; i += 22)
		{
			for (j = pItem->y + 11; j < pItem->y + pItem->h; j += 22)
			{
				if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
				{

					TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
					TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
					TradeColorRect.right = pItem->w;
					TradeColorRect.bottom = pItem->h;

					if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
					{
						cTrade.InitTradeColorRect();
						return FALSE;
					}


					pItem->SetX = TradeColorRect.left;
					pItem->SetY = TradeColorRect.top;
					pItem->ItemPosition = 0;

					TradeColorIndex = SET_ITEM_CHECK_COLOR;


					if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 6))
					{
						TradeColorIndex = NOT_SETTING_COLOR;
						return FALSE;

					}

					return TRUE;
				}
			}
		}
	}
	else
	{
		if (pItem->sItemInfo.ItemKindCode == ITEM_KIND_CRAFT || pItem->sItemInfo.ItemKindCode == ITEM_KIND_AGING)
		{
			TradeColorIndex = 0;
			TradeCrashItemIndex[0] = 0;
			cTrade.InitTradeColorRect();


			TradeStartX = 58;
			TradeStartY = 193 + sinInterHeight2;
			TradeEndX = TradeStartX + (3 * 22);
			TradeEndY = TradeStartY + (4 * 22);


			if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
			{
				TradeColorRect.left = TradeStartX;
				TradeColorRect.top = TradeStartY;
				TradeColorRect.right = TradeEndX - TradeStartX;
				TradeColorRect.bottom = TradeEndY - TradeStartY;


				pItem->SetX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->w) / 2;
				pItem->SetY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->h) / 2;
				pItem->ItemPosition = 0;
				TradeColorIndex = SET_ITEM_CHECK_COLOR;


				if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 6))
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;

				}

				return TRUE;
			}
		}
		else
		{
			TradeStartX = 58;
			TradeStartY = 193 + sinInterHeight2;
			TradeEndX = TradeStartX + (3 * 22);
			TradeEndY = TradeStartY + (4 * 22);
			if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
			{
				TradeColorRect.left = TradeStartX;
				TradeColorRect.top = TradeStartY;
				TradeColorRect.right = TradeEndX - TradeStartX;
				TradeColorRect.bottom = TradeEndY - TradeStartY;


				pItem->SetX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->w) / 2;
				pItem->SetY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->h) / 2;
				pItem->ItemPosition = 0;
				TradeColorIndex = SET_ITEM_CHECK_COLOR;

				if (pItem->sItemInfo.ItemKindCode != ITEM_KIND_CRAFT)
				{
					TradeColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}

			}


		}
	}

	return TRUE;
}


int cMIXTURERESET::CheckMixtureResetItemForm()
{
	int TempCheckDataSum = 0;

	for (int i = 0; i < 2; i++)
	{
		if (sMixtureResetItem.MixtureResetItem[i].Flag)
		{
			TempCheckDataSum += (i + 1) * sMixtureResetItem.MixtureResetItem[i].x;
			TempCheckDataSum += (i + 1) * sMixtureResetItem.MixtureResetItem[i].y;
			TempCheckDataSum += sMixtureResetItem.MixtureResetItem[i].sItemInfo.ItemHeader.dwChkSum;
			TempCheckDataSum += sMixtureResetItem.MixtureResetItem[i].sItemInfo.ItemHeader.Head;

		}
	}
	return TRUE;
}


int cMIXTURERESET::ReformMixtureResetItem()
{
	MixtureResetItemCheckSum = 0;

	for (int i = 0; i < 2; i++)
	{
		if (sMixtureResetItem.MixtureResetItem[i].Flag)
		{
			MixtureResetItemCheckSum += (i + 1) * sMixtureResetItem.MixtureResetItem[i].x;
			MixtureResetItemCheckSum += (i + 1) * sMixtureResetItem.MixtureResetItem[i].y;
			MixtureResetItemCheckSum += sMixtureResetItem.MixtureResetItem[i].sItemInfo.ItemHeader.dwChkSum;
			MixtureResetItemCheckSum += sMixtureResetItem.MixtureResetItem[i].sItemInfo.ItemHeader.Head;

		}
	}

	return TRUE;
}


int cMIXTURERESET::PickUpMixtureResetItem(int x, int y, int PickUpFlag, int Kind)
{
	int i = 0;
	SelectTradeItemIndex = 0;

	if (Kind == 0)
	{
		for (i = 0; i < 2; i++)
		{
			if (sMixtureResetItem.MixtureResetItem[i].Flag)
			{
				if (sMixtureResetItem.MixtureResetItem[i].x < x  && sMixtureResetItem.MixtureResetItem[i].x + sMixtureResetItem.MixtureResetItem[i].w > x  &&
					sMixtureResetItem.MixtureResetItem[i].y < y  && sMixtureResetItem.MixtureResetItem[i].y + sMixtureResetItem.MixtureResetItem[i].h > y)
				{
					if (PickUpFlag)
					{
						if (i == 1)
							MixtureResetCheckFlag = 0;


						if (sMixtureResetItem.MixtureResetItem[1].Flag && i == 0)
						{
							cMessageBox.ShowMessage(MESSAGE_NOT_MIXTURE_RESET_ITEM);
							return FALSE;
						}

						CheckMixtureResetItemForm();
						memcpy(&MouseItem, &sMixtureResetItem.MixtureResetItem[i], sizeof(sITEM));
						sMixtureResetItem.MixtureResetItem[i].Flag = 0;
						memset(&sMixtureResetItem.MixtureResetItem[i], 0, sizeof(sITEM));

						sinPlaySound(sMixtureResetItem.MixtureResetItem[i].SoundIndex);
						TradeColorIndex = 0;
						ReformMixtureResetItem();

						return TRUE;
					}
					else
					{
						SelectTradeItemIndex = i + 1;
						TradeColorIndex = SELECT_ITEM_COLOR;
						sinShowItemInfoFlag = 1;
						cItem.ShowItemInfo(&sMixtureResetItem.MixtureResetItem[i], 2);
					}
				}
			}
		}
	}

	return FALSE;
}


int cMIXTURERESET::LastSetMixtureResetItem(sITEM *pItem, int kind)
{


	if (kind == 1)
	{

		if (sMixtureResetItem.MixtureResetItem[0].Flag && !sMixtureResetItem.MixtureResetItem[1].Flag)
		{
			memcpy(&sMixtureResetItem.MixtureResetItem[1], pItem, sizeof(sITEM));
			sMixtureResetItem.MixtureResetItem[1].x = pItem->SetX;
			sMixtureResetItem.MixtureResetItem[1].y = pItem->SetY;
			pItem->Flag = 0;
			sinPlaySound(sMixtureResetItem.MixtureResetItem[1].SoundIndex);

			return TRUE;
		}
	}
	else if (kind == 2)
	{

		if (!sMixtureResetItem.MixtureResetItem[0].Flag)
		{
			memcpy(&sMixtureResetItem.MixtureResetItem[0], pItem, sizeof(sITEM));
			sMixtureResetItem.MixtureResetItem[0].x = pItem->SetX;
			sMixtureResetItem.MixtureResetItem[0].y = pItem->SetY;
			pItem->Flag = 0;
			sinPlaySound(sMixtureResetItem.MixtureResetItem[0].SoundIndex);

			return TRUE;
		}
	}

	return TRUE;
}


int cMIXTURERESET::CancelMixtureItemReset(int Flag)
{

	if (MixItemNoCopyFlag)
		return FALSE;


	if (sMixtureResetItem.MixtureResetItem[0].Flag)
	{
		if (!cInvenTory.AutoSetInvenItem(&sMixtureResetItem.MixtureResetItem[0]))
			sinThrowItemToFeild(&sMixtureResetItem.MixtureResetItem[0]);

		sMixtureResetItem.MixtureResetItem[0].Flag = 0;
	}

	MixtureResetCheckFlag = 0;


	if (!Flag)
		cMixtureReset.OpenFlag = 0;

	ResetInvenItemCode();

	return TRUE;
}


int cMIXTURERESET::sinSendMixtureItemReset()
{
	if (MixItemNoCopyFlag)
		return FALSE;

	memcpy(&sMixtureResetItemBackUp, &sMixtureResetItem, sizeof(sMIXTURE_RESET_ITEM));
	MixItemNoCopyFlag = 1;
	memset(&sMixtureReset_Send, 0, sizeof(sMIXTURE_RESET_ITEM_SERVER));


	if (sMixtureResetItem.MixtureResetItem[0].Flag)
		sMixtureReset_Send.DesMixtureResetItem = sMixtureResetItem.MixtureResetItem[0];


	if (sMixtureResetItem.MixtureResetItem[1].Flag)
	{
		sMixtureReset_Send.dwMixtureResetStoneItemCode = sMixtureResetItem.MixtureResetItem[1].CODE;
		sMixtureReset_Send.dwMixtureResetStoneCheckSum = sMixtureResetItem.MixtureResetItem[1].sItemInfo.ItemHeader.dwChkSum;
		sMixtureReset_Send.dwMixtureResetStoneHead = sMixtureResetItem.MixtureResetItem[1].sItemInfo.ItemHeader.Head;
	}


	CraftItemSendServerIndex++;
	sMixtureReset_Send.Index = CraftItemSendServerIndex;


	SendMixtureResetItemToServer(&sMixtureReset_Send);


	return TRUE;
}


int	cMIXTURERESET::sinRecvMixtureItemReset(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem)
{
	memcpy(&sMixtureReset_Recv, pMixtureResetItem, sizeof(sMIXTURE_RESET_ITEM_SERVER));

	return TRUE;
}


int cMIXTURERESET::sinRecvMixtureItemResetResult(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server)
{
	CheckMixItemCopyFlag = 0;


	if (!cMixtureReset.OpenFlag)
	{
		MixItemNoCopyFlag = 0;
		memset(&sMixtureResetItem, 0, sizeof(sMIXTURE_RESET_ITEM));
		memset(&sMixtureResetItemBackUp, 0, sizeof(sMIXTURE_RESET_ITEM));
		memset(&sMixtureReset_Recv, 0, sizeof(sMIXTURE_RESET_ITEM_SERVER));
		memset(&sMixtureReset_Send, 0, sizeof(sMIXTURE_RESET_ITEM_SERVER));
		MixCancelButtonDelayFlag = 0;

		return FALSE;
	}

	int i, LineCount = 0, Temp;

	if (pMixtureResetItem_Server->Result)
	{
		sITEM TempItem;
		if (LoadItemImage(&pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo, &TempItem))
		{
			strcpy_s(szCraftItemBuff, pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemName);
			strcat(szCraftItemBuff, "\r");

			Temp = lstrlen(szCraftItemBuff);
			for (i = 0; i < Temp; i++)
			{
				if (szCraftItemBuff[i] == '\r')
				{
					LineCount++;
				}
			}

			CraftItemMessageSize.x = 14;
			CraftItemMessageSize.y = ((LineCount) * 2) + 2;

			if (cInvenTory.CheckRequireItemToSet(&TempItem))
			{

				if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
				{
					sinThrowItemToFeild(&pMixtureResetItem_Server->DesMixtureResetItem);
				}
			}

		}

		cMessageBox.ShowMessage(MESSAGE_OK_MIXTURE_RESET_ITEM);

		CheckCharForm();
		ReformCharForm();
		SendSaveMoney();
		SaveGameData();
		cMixtureReset.OpenFlag = 0;
	}
	else
	{
		CheckCharForm();
		ReformCharForm();
		SendSaveMoney();
		cMixtureReset.OpenFlag = 0;
		cMessageBox.ShowMessage(MESSAGE_FAIL_MIXTURE_RESET_ITEM);
	}


	for (i = 0; i < 2; i++)
	{
		if (sMixtureResetItemBackUp.MixtureResetItem[i].Flag)
		{
			cInvenTory.DeleteInvenItemToServer(sMixtureResetItemBackUp.MixtureResetItem[i].sItemInfo.CODE,
				sMixtureResetItemBackUp.MixtureResetItem[i].sItemInfo.ItemHeader.Head,
				sMixtureResetItemBackUp.MixtureResetItem[i].sItemInfo.ItemHeader.dwChkSum);
		}

	}

	memset(&sMixtureResetItem, 0, sizeof(sMIXTURE_RESET_ITEM));
	memset(&sMixtureResetItemBackUp, 0, sizeof(sMIXTURE_RESET_ITEM));
	memset(&sMixtureReset_Recv, 0, sizeof(sMIXTURE_RESET_ITEM_SERVER));
	memset(&sMixtureReset_Send, 0, sizeof(sMIXTURE_RESET_ITEM_SERVER));

	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;


	return TRUE;
}


int CSmeltingItem::CancelSmeltingItem()
{

	for (int i = 0; i < 5; i++)
	{
		if (S_smeltingItem.SmeltingItem[i].Flag)
		{
			if (!cInvenTory.AutoSetInvenItem(&S_smeltingItem.SmeltingItem[i]))
			{
				sinThrowItemToFeild(&S_smeltingItem.SmeltingItem[i]);
				S_smeltingItem.SmeltingItem[i].Flag = 0;
			}
		}
	}

	SmeltingItem.OpenFlag = 0;
	m_SmeltingPrice = 0;
	ForceItemPrice2 = 0;
	memset(&S_smeltingItem, 0, sizeof(SSmeltingItem));
	ResetInvenItemCode();

	memset(&sSmeltingItem_Recv, 0, sizeof(sSMELTINGITEM_SERVER));
	memset(&sSmeltingItem_Send, 0, sizeof(sSMELTINGITEM_SERVER));

	return TRUE;
}


int CSmeltingItem::SetSmeltingItemAreaCheck(sITEM *pItem, int Kind)
{

	int SmeltingPriceIndexOre = 25000;


	int SmeltingPriceIndexCrystal = 50000;


	DWORD SmeltingCode[] = { sin01, sin02, sin03, sin04, sin05, sin06, sin07, sin08, sin09, sin10, sin11, sin12, sin13, sin14 };

	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	if ((pItem->CODE & sinITEM_MASK2) == sinOS1)
	{
		int SmeltingSheltomIndex = 0;
		SmeltingSheltomIndex = GetSheltomIndex(S_smeltingItem.SmeltingItem[0].CODE);
		int Smelting_SheltomIndex = 0;
		DWORD SheltomAray[MAX_SHELTOM] = { sin01, sin02, sin03, sin04, sin05, sin06, sin07, sin08, sin09, sin10, sin11, sin12, sin13, sin14 };

		for (int q = 0; q < MAX_SHELTOM; q++)
		{
			if (SheltomAray[q] == (pItem->sItemInfo.CODE & sinITEM_MASK3))
			{
				Smelting_SheltomIndex = q + 1;
				break;
			}
		}

		{

			{
				if (SmeltingSheltomIndex == Smelting_SheltomIndex)
				{
					TradeStartX = AgingLevelSheltomXY[0][0].x + 22;
					TradeStartY = AgingLevelSheltomXY[0][0].y + 30;
					TradeEndX = TradeStartX + 22;
					TradeEndY = TradeStartY + 22;
					for (i = pItem->x + 11; i < pItem->x + pItem->w; i += 22)
					{
						for (j = pItem->y + 11; j < pItem->y + pItem->h; j += 22)
						{
							if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
							{
								TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
								TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
								TradeColorRect.right = pItem->w;
								TradeColorRect.bottom = pItem->h;
								if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
								{
									cTrade.InitTradeColorRect();
									return FALSE;
								}

								pItem->SetX = TradeColorRect.left;
								pItem->SetY = TradeColorRect.top;
								pItem->ItemPosition = 0;

								TradeColorIndex = SET_ITEM_CHECK_COLOR;
								if (!S_smeltingItem.SmeltingItem[0].Flag)
								{
									TradeColorIndex = NOT_SETTING_COLOR;
									return FALSE;
								}

								if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 4))
								{
									TradeColorIndex = NOT_SETTING_COLOR;
									return FALSE;

								}
								return TRUE;
							}
						}
					}
				}
			}
		}
	}
	else if ((pItem->CODE & sinITEM_MASK2) == sinPR1 || (pItem->CODE & sinITEM_MASK2) == sinPR2)
	{





		TradeColorIndex = 0;
		TradeCrashItemIndex[0] = 0;
		cTrade.InitTradeColorRect();






		TradeStartX = 69;
		TradeStartY = 212 + sinInterHeight2;
		TradeEndX = TradeStartX + (2 * 18);
		TradeEndY = TradeStartY + (2 * 18);
		for (i = pItem->x + 11; i < pItem->x + pItem->w; i += 22)
		{
			for (j = pItem->y + 11; j < pItem->y + pItem->h; j += 22)
			{
				if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
				{
					if (!(80 <= pCursorPos.x && 101 >= pCursorPos.x && 143 <= pCursorPos.y && 164 >= pCursorPos.y))
					{
						TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
						TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
						TradeColorRect.right = pItem->w;
						TradeColorRect.bottom = pItem->h;
						if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
						{
							cTrade.InitTradeColorRect();
							return FALSE;
						}

						pItem->SetX = TradeColorRect.left;
						pItem->SetY = TradeColorRect.top;
						pItem->ItemPosition = 0;
						TradeColorIndex = SET_ITEM_CHECK_COLOR;

						if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 4))
						{
							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;
						}


						for (int i = 0; i < 7; i++)
						{

							if ((pItem->CODE & sinITEM_MASK2) == sinPR1)
							{
								if ((pItem->sItemInfo.CODE & sinITEM_MASK3) == SmeltingCode[i])
								{
									if (sinChar->Money < SmeltingPriceIndexOre)
									{
										TradeColorIndex = NOT_ENOUGH_MONEY;
										return FALSE;
									}
								}
							}
						}

						for (int i = 0; i < 14; i++)
						{

							if ((pItem->CODE & sinITEM_MASK2) == sinPR2)
							{
								if ((pItem->sItemInfo.CODE & sinITEM_MASK3) == SmeltingCode[i])
								{
									if (sinChar->Money < SmeltingPriceIndexCrystal)
									{
										TradeColorIndex = NOT_ENOUGH_MONEY;
										return FALSE;
									}
								}
							}
						}


						if (pItem->sItemInfo.SpecialItemFlag[0] == CHECK_COPY_ITEM ||
							pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST ||
							(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
							(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA2 ||
							(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinQW1 ||
							(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 ||
							(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ2 ||
							(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinFO1 ||
							pItem->sItemInfo.CODE == (sinGF1 | sin01) ||
							pItem->sItemInfo.CODE == (sinGF1 | sin02) ||
							pItem->sItemInfo.CODE == (sinGF1 | sin03) ||
							pItem->sItemInfo.CODE == (sinGF1 | sin04) ||
							pItem->sItemInfo.CODE == (sinGF1 | sin05) ||
							pItem->sItemInfo.CODE == (sinGF1 | sin06) ||
							pItem->sItemInfo.CODE == (sinGF1 | sin07) ||
							pItem->sItemInfo.CODE == (sinGF1 | sin08))
						{

							TradeColorIndex = NOT_SETTING_COLOR;
							return FALSE;
						}
						return TRUE;
					}

				}
			}
		}
	}
	return TRUE;
}


int CSmeltingItem::LastSetSmeltingItem(sITEM *pItem, int Kind)
{
	if (Kind == 0)
	{
		CheckSmeltingItemForm();
		if ((pItem->CODE & sinITEM_MASK2) == sinOS1)
		{













			if (!S_smeltingItem.SmeltingItem[4].Flag)
			{
				memcpy(&S_smeltingItem.SmeltingItem[4], pItem, sizeof(sITEM));
				S_smeltingItem.SmeltingItem[4].x = pItem->SetX;
				S_smeltingItem.SmeltingItem[4].y = pItem->SetY;
				pItem->Flag = 0;
				sinPlaySound(S_smeltingItem.SmeltingItem[4].SoundIndex);
				ReFormSmeltingItem();
				return TRUE;
			}

		}
		else
		{
			int k = 3;









			for (int i = 0; i < k; i++)
			{
				if (!S_smeltingItem.SmeltingItem[i].Flag)
				{
					memcpy(&S_smeltingItem.SmeltingItem[i], pItem, sizeof(sITEM));
					S_smeltingItem.SmeltingItem[i].x = pItem->SetX;
					S_smeltingItem.SmeltingItem[i].y = pItem->SetY;
					pItem->Flag = 0;
					sinPlaySound(sCraftItem.CraftItem[i].SoundIndex);
					ReFormSmeltingItem();
					CheckSmeltingPrice();
					return TRUE;
				}
			}
		}
	}
	return TRUE;
}


int CSmeltingItem::CheckSmeltingItemForm()
{
	int TempCheckDataSum = 0;



	for (int i = 0; i < 5; i++)
	{
		if (S_smeltingItem.SmeltingItem[i].Flag)
		{
			TempCheckDataSum += (i + 1)*S_smeltingItem.SmeltingItem[i].x;
			TempCheckDataSum += (i + 1)*S_smeltingItem.SmeltingItem[i].y;
			TempCheckDataSum += S_smeltingItem.SmeltingItem[i].sItemInfo.ItemHeader.dwChkSum;
			TempCheckDataSum += S_smeltingItem.SmeltingItem[i].sItemInfo.ItemHeader.Head;

		}
	}
	return TRUE;
}


int CSmeltingItem::ReFormSmeltingItem()
{

	SmeltingItemCheckSum = 0;
	for (int i = 0; i < 5; i++)
	{
		if (S_smeltingItem.SmeltingItem[i].Flag)
		{
			SmeltingItemCheckSum += (i + 1)*S_smeltingItem.SmeltingItem[i].x;
			SmeltingItemCheckSum += (i + 1)*S_smeltingItem.SmeltingItem[i].y;
			SmeltingItemCheckSum += S_smeltingItem.SmeltingItem[i].sItemInfo.ItemHeader.dwChkSum;
			SmeltingItemCheckSum += S_smeltingItem.SmeltingItem[i].sItemInfo.ItemHeader.Head;

		}
	}

	return TRUE;
}


int CSmeltingItem::PickUpSmeltingItem(int x, int y, int PickUpFlag, int Kind)
{
	int i = 0;
	SelectTradeItemIndex = 0;
	if (Kind == 0)
	{
		for (i = 0; i < 5; i++)
		{
			if (S_smeltingItem.SmeltingItem[i].Flag)
			{
				if (S_smeltingItem.SmeltingItem[i].x < x  && S_smeltingItem.SmeltingItem[i].x + S_smeltingItem.SmeltingItem[i].w > x  &&
					S_smeltingItem.SmeltingItem[i].y < y  && S_smeltingItem.SmeltingItem[i].y + S_smeltingItem.SmeltingItem[i].h > y)
				{
					if (PickUpFlag)
					{
						if (i < 4 && S_smeltingItem.SmeltingItem[4].Flag)
						{
							cMessageBox.ShowMessage(MESSAGE_NOT_SMELTING);
							return FALSE;
						}
						CheckSmeltingItemForm();
						memcpy(&MouseItem, &S_smeltingItem.SmeltingItem[i], sizeof(sITEM));
						S_smeltingItem.SmeltingItem[i].Flag = 0;
						memset(&S_smeltingItem.SmeltingItem[i], 0, sizeof(sITEM));

						sinPlaySound(S_smeltingItem.SmeltingItem[i].SoundIndex);
						TradeColorIndex = 0;
						ReFormSmeltingItem();
						return TRUE;
					}
					else
					{
						SelectTradeItemIndex = i + 1;
						TradeColorIndex = SELECT_ITEM_COLOR;
						sinShowItemInfoFlag = 1;
						cItem.ShowItemInfo(&S_smeltingItem.SmeltingItem[i], 2);
					}
				}
			}
		}
	}
	return FALSE;
}


int CSmeltingItem::sinSendSmeltingItem()
{
	if (MixItemNoCopyFlag)
	{
		return FALSE;
	}

	int i = 0;


	memcpy(&sSmeltingItemBackUp, &S_smeltingItem, sizeof(SSmeltingItem));
	MixItemNoCopyFlag = 1;
	memset(&sSmeltingItem_Send.DesSmeltingItem, 0, sizeof(sITEM));

	sSmeltingItem_Send.Money = m_SmeltingPrice;

	for (i = 0; i < 5; i++)
	{
		if (S_smeltingItem.SmeltingItem[i].Flag)
		{
			sSmeltingItem_Send.SmeltingCode[i] = S_smeltingItem.SmeltingItem[i].CODE;
			sSmeltingItem_Send.CheckSum[i] = S_smeltingItem.SmeltingItem[i].sItemInfo.ItemHeader.dwChkSum;
			sSmeltingItem_Send.Head[i] = S_smeltingItem.SmeltingItem[i].sItemInfo.ItemHeader.Head;
		}
	}

	CheckCraftMoney = sSmeltingItem_Send.Money;

	CraftItemSendServerIndex++;
	sSmeltingItem_Send.Index = CraftItemSendServerIndex;



	SendSmeltingItemToServer(&sSmeltingItem_Send);

	return TRUE;
}

int CSmeltingItem::sinRecvSmeltingItem(sSMELTINGITEM_SERVER *pSmeltingItem_Server)
{
	memcpy(&sSmeltingItem_Recv, pSmeltingItem_Server, sizeof(sSMELTINGITEM_SERVER));

	return TRUE;
}


int CSmeltingItem::sinRecvSmeltingItemResult(sSMELTINGITEM_SERVER *pSmeltingItem_Server)
{
	CheckMixItemCopyFlag = 0;
	if (!SmeltingItem.OpenFlag)
	{
		MixItemNoCopyFlag = 0;
		memset(&S_smeltingItem, 0, sizeof(SSmeltingItem));
		memset(&sSmeltingItemBackUp, 0, sizeof(SSmeltingItem));
		memset(&sSmeltingItem_Recv, 0, sizeof(sSMELTINGITEM_SERVER));
		memset(&sSmeltingItem_Send, 0, sizeof(sSMELTINGITEM_SERVER));
		MixCancelButtonDelayFlag = 0;
		return FALSE;

	}

	int i, LineCount = 0, Temp;


	if (pSmeltingItem_Server->Result)
	{
		ShowItemSmeltingMessageFlag = 1;

		sITEM TempItem;
		if (LoadItemImage(&pSmeltingItem_Server->DesSmeltingItem.sItemInfo, &TempItem))
		{
			strcpy_s(szCraftItemBuff, pSmeltingItem_Server->DesSmeltingItem.sItemInfo.ItemName);

			strcat(szCraftItemBuff, "\r");
			Temp = lstrlen(szCraftItemBuff);
			for (i = 0; i < Temp; i++)
			{
				if (szCraftItemBuff[i] == '\r')
				{
					LineCount++;
				}
			}
			CraftItemMessageSize.x = 14;
			CraftItemMessageSize.y = ((LineCount) * 2) + 2;

			if (cInvenTory.CheckRequireItemToSet(&TempItem))
			{

				if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
				{
					sinThrowItemToFeild(&pSmeltingItem_Server->DesSmeltingItem);
				}
			}

		}

		CheckCharForm();
		sinMinusMoney(m_SmeltingPrice);
		ReformCharForm();
		SendSaveMoney();
		SaveGameData();
		SmeltingItem.OpenFlag = 0;
	}
	else
	{
		CheckCharForm();
		sinMinusMoney(m_SmeltingPrice);
		ReformCharForm();
		SendSaveMoney();
		SmeltingItem.OpenFlag = 0;
		cMessageBox.ShowMessage(MESSAGE_FAILD_SMELTING_ITEM);
	}


	for (i = 0; i < 5; i++)
	{
		if (sSmeltingItemBackUp.SmeltingItem[i].Flag)
		{
			cInvenTory.DeleteInvenItemToServer(sSmeltingItemBackUp.SmeltingItem[i].sItemInfo.CODE,
				sSmeltingItemBackUp.SmeltingItem[i].sItemInfo.ItemHeader.Head,
				sSmeltingItemBackUp.SmeltingItem[i].sItemInfo.ItemHeader.dwChkSum);
		}

	}
	memset(&S_smeltingItem, 0, sizeof(SSmeltingItem));
	memset(&sSmeltingItemBackUp, 0, sizeof(SSmeltingItem));
	memset(&sSmeltingItem_Recv, 0, sizeof(sSMELTINGITEM_SERVER));
	memset(&sSmeltingItem_Send, 0, sizeof(sSMELTINGITEM_SERVER));

	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;
	m_SmeltingPrice = 0;
	ForceItemPrice2 = 0;
	return TRUE;
}


int CSmeltingItem::SmeltingCheckEmptyArea(sITEM *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->w;
	cy = (22 * INVENTORY_BOX_COL) - pItem->h;


	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (cInvenTory.InvenItem[i].Flag)
				{
					rect.left = cInvenTory.InvenItem[i].x;
					rect.right = cInvenTory.InvenItem[i].x + cInvenTory.InvenItem[i].w;
					rect.top = cInvenTory.InvenItem[i].y;
					rect.bottom = cInvenTory.InvenItem[i].y + cInvenTory.InvenItem[i].h;

					if (cntx > rect.left - pItem->w && cntx< rect.right &&
						cnty > rect.top - pItem->h && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 1)
			{
				pItem->SetX = cntx;
				pItem->SetY = cnty;
				pItem->ItemPosition = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}

int CSmeltingItem::GetSmeltingCheckEmptyArea()
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - 22;
	cy = (22 * INVENTORY_BOX_COL) - 22;

	int count = 0;

	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (cInvenTory.InvenItem[i].Flag)
				{
					rect.left = cInvenTory.InvenItem[i].x;
					rect.right = cInvenTory.InvenItem[i].x + cInvenTory.InvenItem[i].w;
					rect.top = cInvenTory.InvenItem[i].y;
					rect.bottom = cInvenTory.InvenItem[i].y + cInvenTory.InvenItem[i].h;

					if (cntx > rect.left - 22 && cntx< rect.right &&
						cnty > rect.top - 22 && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 1)
			{
				count++;
			}
		}
	}
	if (count)
		return count;
	else
		return 0;
}


int CSmeltingItem::CheckSmeltingPrice()
{

	int SmeltingPriceIndexOre = 25000;



	int SmeltingPriceIndexCrystal = 50000;




	m_SmeltingPrice = 0;
	if (S_smeltingItem.SmeltingItem[0].Flag)
	{
		if ((S_smeltingItem.SmeltingItem[0].sItemInfo.CODE & sinITEM_MASK2) == sinPR1)
		{

			m_SmeltingPrice = SmeltingPriceIndexOre;
			ForceItemPrice2 = m_SmeltingPrice;
			return TRUE;
		}
		else if ((S_smeltingItem.SmeltingItem[0].sItemInfo.CODE & sinITEM_MASK2) == sinPR2)
		{

			m_SmeltingPrice = SmeltingPriceIndexCrystal;
			ForceItemPrice2 = m_SmeltingPrice;
			return TRUE;
		}
	}
	return TRUE;
}


int CManufacture::CancelManufactureItem()
{

	for (int i = 0; i < 4; i++)
	{
		if (g_sManufactureItem.ManufactureItem[i].Flag)
		{
			if (!cInvenTory.AutoSetInvenItem(&g_sManufactureItem.ManufactureItem[i]))
			{
				sinThrowItemToFeild(&g_sManufactureItem.ManufactureItem[i]);
				g_sManufactureItem.ManufactureItem[i].Flag = 0;
			}
		}
	}

	ManufactureItem.m_OpenFlag = 0;
	m_ManufacturePrice = 0;
	ForceItemPrice2 = 0;
	memset(&g_sManufactureItem, 0, sizeof(SManufactureItem));
	ResetInvenItemCode();

	memset(&g_sManufactureItem_Recv, 0, sizeof(SManufactureItem_Server));
	memset(&g_sManufactureItem_Send, 0, sizeof(SManufactureItem_Server));

	return TRUE;
}


int CManufacture::SetManufactureItemAreaCheck(sITEM *pItem)
{







	POINT ManufactureRuneXY[3] = { {240, 159},  {215, 190}, {265, 190} };

	int i, j;
	TradeColorIndex = 0;
	TradeCrashItemIndex[0] = 0;
	cTrade.InitTradeColorRect();

	if ((pItem->CODE & sinITEM_MASK2) == sinPR3 || (pItem->CODE & sinITEM_MASK2) == sinPR4)
	{

		int RuneItemIndex = 0;
		DWORD RuneAray[MAX_RUNE] = { sin01, sin02, sin03, sin04 ,sin05, sin06, sin07, sin08, sin09, sin10, sin11, sin12, sin13, sin14, sin15 };
		for (int q = 0; q < MAX_RUNE; q++)
		{
			if (RuneAray[q] == (pItem->sItemInfo.CODE & sinITEM_MASK3))
			{
				RuneItemIndex = q + 1;
				break;
			}
		}
		int RecipeIndex = 0;
		RecipeIndex = ManufactureItem.GetRecipeIndex(g_sManufactureItem.ManufactureItem[0].CODE & sinITEM_MASK3);
		for (int p = 0; p < 3; p++)
		{

			{
				for (int r = 0; r < MAX_RECIPE_KIND; r++)
				{
					if (g_sManufacture_Rune[r].RecipeCode == RecipeIndex)
					{
						if (g_sManufacture_Rune[r].NeedRuneIndex[p] == RuneItemIndex)
						{
							TradeStartX = ManufactureRuneXY[p].x;
							TradeStartY = ManufactureRuneXY[p].y;
							TradeEndX = TradeStartX + 22;
							TradeEndY = TradeStartY + 22;
							for (i = pItem->x + 11; i < pItem->x + pItem->w; i += 22)
							{
								for (j = pItem->y + 11; j < pItem->y + pItem->h; j += 22)
								{
									if (TradeStartX <= i && TradeEndX > i && TradeStartY <= j && TradeEndY > j)
									{
										TradeColorRect.left = TradeStartX + (((i - TradeStartX) / 22) * 22);
										TradeColorRect.top = TradeStartY + (((j - TradeStartY) / 22) * 22);
										TradeColorRect.right = pItem->w;
										TradeColorRect.bottom = pItem->h;
										if (TradeEndX < (TradeColorRect.left + TradeColorRect.right) - 11 || TradeEndY < (TradeColorRect.top + TradeColorRect.bottom) - 11)
										{
											cTrade.InitTradeColorRect();
											return FALSE;
										}

										pItem->SetX = TradeColorRect.left;
										pItem->SetY = TradeColorRect.top;
										pItem->ItemPosition = 0;

										TradeColorIndex = SET_ITEM_CHECK_COLOR;

										if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 5))
										{
											TradeColorIndex = NOT_SETTING_COLOR;
											return FALSE;
										}

										return TRUE;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if ((pItem->CODE & sinITEM_MASK2) == sinWR1 || (pItem->CODE & sinITEM_MASK2) == sinDR1)
	{
		TradeColorIndex = 0;
		TradeCrashItemIndex[0] = 0;
		cTrade.InitTradeColorRect();

		TradeStartX = 58;
		TradeStartY = 193 + sinInterHeight2;
		TradeEndX = TradeStartX + (3 * 22);
		TradeEndY = TradeStartY + (4 * 22);
		if (TradeStartX <= pCursorPos.x && TradeEndX > pCursorPos.x && TradeStartY <= pCursorPos.y && TradeEndY > pCursorPos.y)
		{
			TradeColorRect.left = TradeStartX;
			TradeColorRect.top = TradeStartY;
			TradeColorRect.right = TradeEndX - TradeStartX;
			TradeColorRect.bottom = TradeEndY - TradeStartY;


			pItem->SetX = TradeStartX + ((TradeEndX - TradeStartX) - pItem->w) / 2;
			pItem->SetY = TradeStartY + ((TradeEndY - TradeStartY) - pItem->h) / 2;
			pItem->ItemPosition = 0;
			TradeColorIndex = SET_ITEM_CHECK_COLOR;

			if (TradeCrashItemIndex[0] = cTrade.CrashTradeItem(TradeColorRect, 0, 5))
			{
				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;

			}




			if (sinChar->Money < pItem->sItemInfo.Price)
			{
				TradeColorIndex = NOT_ENOUGH_MONEY;
				return FALSE;
			}

			if (pItem->sItemInfo.SpecialItemFlag[0] == CHECK_COPY_ITEM ||
				pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA2 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinQW1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ2 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinFO1 ||
				pItem->sItemInfo.CODE == (sinGF1 | sin01) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin02) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin03) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin04) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin05) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin06) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin07) ||
				pItem->sItemInfo.CODE == (sinGF1 | sin08))
			{

				TradeColorIndex = NOT_SETTING_COLOR;
				return FALSE;

			}
			return TRUE;
		}
	}
	return TRUE;
}


int CManufacture::LastSetManufactureItem(sITEM *pItem)
{
	CheckManufactureItem();
	if ((pItem->CODE & sinITEM_MASK2) == sinPR3 || (pItem->CODE & sinITEM_MASK2) == sinPR4)
	{

		for (int j = 1; j < 4; j++)
		{
			if (!g_sManufactureItem.ManufactureItem[j].Flag)
			{
				memcpy(&g_sManufactureItem.ManufactureItem[j], pItem, sizeof(sITEM));
				g_sManufactureItem.ManufactureItem[j].x = pItem->SetX;
				g_sManufactureItem.ManufactureItem[j].y = pItem->SetY;
				pItem->Flag = 0;
				sinPlaySound(g_sManufactureItem.ManufactureItem[j].SoundIndex);
				ReFormManufactureItem();
				return TRUE;
			}
		}
	}
	else
	{
		if (!g_sManufactureItem.ManufactureItem[0].Flag)
		{
			memcpy(&g_sManufactureItem.ManufactureItem[0], pItem, sizeof(sITEM));
			g_sManufactureItem.ManufactureItem[0].x = pItem->SetX;
			g_sManufactureItem.ManufactureItem[0].y = pItem->SetY;
			pItem->Flag = 0;
			sinPlaySound(g_sManufactureItem.ManufactureItem[0].SoundIndex);
			ReFormManufactureItem();
			return TRUE;
		}
	}
	return TRUE;

}


int CManufacture::CheckManufactureItem()
{
	int TempCheckDataSum = 0;

	for (int i = 0; i < 4; i++)
	{
		if (g_sManufactureItem.ManufactureItem[i].Flag)
		{
			TempCheckDataSum += (i + 1)*g_sManufactureItem.ManufactureItem[i].x;
			TempCheckDataSum += (i + 1)*g_sManufactureItem.ManufactureItem[i].y;
			TempCheckDataSum += g_sManufactureItem.ManufactureItem[i].sItemInfo.ItemHeader.dwChkSum;
			TempCheckDataSum += g_sManufactureItem.ManufactureItem[i].sItemInfo.ItemHeader.Head;
		}
	}
	return TRUE;
}


int CManufacture::ReFormManufactureItem()
{

	m_ManufactureItemCheckSum = 0;
	for (int i = 0; i < 4; i++)
	{
		if (g_sManufactureItem.ManufactureItem[i].Flag)
		{
			m_ManufactureItemCheckSum += (i + 1)*g_sManufactureItem.ManufactureItem[i].x;
			m_ManufactureItemCheckSum += (i + 1)*g_sManufactureItem.ManufactureItem[i].y;
			m_ManufactureItemCheckSum += g_sManufactureItem.ManufactureItem[i].sItemInfo.ItemHeader.dwChkSum;
			m_ManufactureItemCheckSum += g_sManufactureItem.ManufactureItem[i].sItemInfo.ItemHeader.Head;
		}
	}
	return TRUE;
}


int CManufacture::PickUpManufactureItem(int x, int y, int PickUpFlag)
{
	int i = 0;
	SelectTradeItemIndex = 0;

	for (i = 0; i < 4; i++)
	{
		if (g_sManufactureItem.ManufactureItem[i].Flag)
		{
			if (g_sManufactureItem.ManufactureItem[i].x < x  && g_sManufactureItem.ManufactureItem[i].x + g_sManufactureItem.ManufactureItem[i].w > x  &&
				g_sManufactureItem.ManufactureItem[i].y < y  && g_sManufactureItem.ManufactureItem[i].y + g_sManufactureItem.ManufactureItem[i].h > y)
			{
				if (PickUpFlag)
				{
					int cnt = 0;
					for (cnt = 1; cnt < 4; cnt++)
					{
						if (i == 0 && g_sManufactureItem.ManufactureItem[cnt].Flag)
						{
							cMessageBox.ShowMessage(MESSAGE_NOT_MANUFACTURE);
							return FALSE;
						}
					}

					CheckManufactureItem();
					memcpy(&MouseItem, &g_sManufactureItem.ManufactureItem[i], sizeof(sITEM));
					g_sManufactureItem.ManufactureItem[i].Flag = 0;
					memset(&g_sManufactureItem.ManufactureItem[i], 0, sizeof(sITEM));

					sinPlaySound(g_sManufactureItem.ManufactureItem[i].SoundIndex);
					TradeColorIndex = 0;
					ReFormManufactureItem();
					return TRUE;
				}
				else
				{
					SelectTradeItemIndex = i + 1;
					TradeColorIndex = SELECT_ITEM_COLOR;
					sinShowItemInfoFlag = 1;
					cItem.ShowItemInfo(&g_sManufactureItem.ManufactureItem[i], 2);
				}
			}
		}
	}
	return FALSE;
}



int CManufacture::ManufactureCheckEmptyArea(sITEM *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->w;
	cy = (22 * INVENTORY_BOX_COL) - pItem->h;


	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (cInvenTory.InvenItem[i].Flag)
				{
					rect.left = cInvenTory.InvenItem[i].x;
					rect.right = cInvenTory.InvenItem[i].x + cInvenTory.InvenItem[i].w;
					rect.top = cInvenTory.InvenItem[i].y;
					rect.bottom = cInvenTory.InvenItem[i].y + cInvenTory.InvenItem[i].h;

					if (cntx > rect.left - pItem->w && cntx< rect.right &&
						cnty > rect.top - pItem->h && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->SetX = cntx;
				pItem->SetY = cnty;
				pItem->ItemPosition = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}

int CManufacture::sinSendManufactureItem()
{
	if (MixItemNoCopyFlag)
	{
		return FALSE;
	}

	int i = 0;


	memcpy(&g_sManufactureItemBackUp, &g_sManufactureItem, sizeof(SManufactureItem));
	MixItemNoCopyFlag = 1;
	memset(&g_sManufactureItem_Send.DesManufactureItem, 0, sizeof(sITEM));

	g_sManufactureItem_Send.Money = m_ManufacturePrice;




	for (i = 0; i < 4; i++)
	{
		if (g_sManufactureItem.ManufactureItem[i].Flag)
		{
			g_sManufactureItem_Send.RuneCode[i] = g_sManufactureItem.ManufactureItem[i].CODE;
			g_sManufactureItem_Send.CheckSum[i] = g_sManufactureItem.ManufactureItem[i].sItemInfo.ItemHeader.dwChkSum;
			g_sManufactureItem_Send.Head[i] = g_sManufactureItem.ManufactureItem[i].sItemInfo.ItemHeader.Head;
		}
	}

	CheckCraftMoney = g_sManufactureItem_Send.Money;

	CraftItemSendServerIndex++;
	g_sManufactureItem_Send.Index = CraftItemSendServerIndex;


	SendManufactureItemToServer(&g_sManufactureItem_Send);

	return TRUE;
}


int CManufacture::sinRecvManufactureItem(SManufactureItem_Server *pManufactureItem_Server)
{
	memcpy(&g_sManufactureItem_Recv, pManufactureItem_Server, sizeof(SManufactureItem_Server));
	return TRUE;
}


void CManufacture::RuneIndexInit()
{

	for (int i = 0; i < MAX_RECIPE_KIND; i++)
	{
		memset(&g_sManufacture_Rune[i], 0, sizeof(SManufacture_Rune));
	}

	g_sManufacture_Rune[0].RecipeCode = EXTREME_RECIPE;
	g_sManufacture_Rune[0].NeedRuneIndex[0] = 1;
	g_sManufacture_Rune[0].NeedRuneIndex[1] = 2;
	g_sManufacture_Rune[0].NeedRuneIndex[2] = 3;



	g_sManufacture_Rune[1].RecipeCode = ANCIENT_RECIPE;
	g_sManufacture_Rune[1].NeedRuneIndex[0] = 4;
	g_sManufacture_Rune[1].NeedRuneIndex[1] = 5;
	g_sManufacture_Rune[1].NeedRuneIndex[2] = 6;



	g_sManufacture_Rune[2].RecipeCode = MINOTAUR_RECIPE;
	g_sManufacture_Rune[2].NeedRuneIndex[0] = 7;
	g_sManufacture_Rune[2].NeedRuneIndex[1] = 8;
	g_sManufacture_Rune[2].NeedRuneIndex[2] = 9;



	g_sManufacture_Rune[3].RecipeCode = DOOM_RECIPE;
	g_sManufacture_Rune[3].NeedRuneIndex[0] = 10;
	g_sManufacture_Rune[3].NeedRuneIndex[1] = 11;
	g_sManufacture_Rune[3].NeedRuneIndex[2] = 12;



	g_sManufacture_Rune[4].RecipeCode = SALAMANDER_RECIPE;
	g_sManufacture_Rune[4].NeedRuneIndex[0] = 13;
	g_sManufacture_Rune[4].NeedRuneIndex[1] = 14;
	g_sManufacture_Rune[4].NeedRuneIndex[2] = 15;

}


int CManufacture::GetRecipeIndex(DWORD Code)
{
	int RecipeIndex = -1;

	switch (Code)
	{
	case sin01:
		RecipeIndex = EXTREME_RECIPE;
		break;
	case sin02:
		RecipeIndex = ANCIENT_RECIPE;
		break;
	case sin03:
		RecipeIndex = MINOTAUR_RECIPE;
		break;
	case sin04:
		RecipeIndex = DOOM_RECIPE;
		break;
	case sin05:
		RecipeIndex = SALAMANDER_RECIPE;
		break;
	}

	return RecipeIndex;
}


int CManufacture::RecvManufactureItemResult(SManufactureItem_Server *pManufactureItem_Server)
{
	CheckMixItemCopyFlag = 0;
	if (!ManufactureItem.m_OpenFlag)
	{
		MixItemNoCopyFlag = 0;
		memset(&g_sManufactureItem, 0, sizeof(SManufactureItem));
		memset(&g_sManufactureItemBackUp, 0, sizeof(SManufactureItem));
		memset(&g_sManufactureItem_Recv, 0, sizeof(SManufactureItem_Server));
		memset(&g_sManufactureItem_Send, 0, sizeof(SManufactureItem_Server));
		MixCancelButtonDelayFlag = 0;
		return FALSE;

	}

	int i, LineCount = 0, Temp;


	if (pManufactureItem_Server->Result)
	{
		ShowItemManufactureMessageFlag = 1;

		sITEM TempItem;
		if (LoadItemImage(&pManufactureItem_Server->DesManufactureItem.sItemInfo, &TempItem))
		{
			strcpy_s(szCraftItemBuff, pManufactureItem_Server->DesManufactureItem.sItemInfo.ItemName);

			strcat(szCraftItemBuff, "\r");
			Temp = lstrlen(szCraftItemBuff);
			for (i = 0; i < Temp; i++)
			{
				if (szCraftItemBuff[i] == '\r')
				{
					LineCount++;
				}
			}
			CraftItemMessageSize.x = 14;
			CraftItemMessageSize.y = ((LineCount) * 2) + 2;

			if (cInvenTory.CheckRequireItemToSet(&TempItem))
			{

				if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
				{
					sinThrowItemToFeild(&pManufactureItem_Server->DesManufactureItem);
				}
			}

		}

		CheckCharForm();
		sinMinusMoney(m_ManufacturePrice);
		ReformCharForm();
		SendSaveMoney();
		SaveGameData();
		ManufactureItem.m_OpenFlag = 0;
	}
	else
	{
		CheckCharForm();
		sinMinusMoney(m_ManufacturePrice);
		ReformCharForm();
		SendSaveMoney();
		ManufactureItem.m_OpenFlag = 0;
		cMessageBox.ShowMessage(MESSAGE_FAILD_MANUFACTURE_ITEM);
	}


	for (i = 0; i < 4; i++)
	{
		if (g_sManufactureItemBackUp.ManufactureItem[i].Flag)
		{
			cInvenTory.DeleteInvenItemToServer(g_sManufactureItemBackUp.ManufactureItem[i].sItemInfo.CODE,
				g_sManufactureItemBackUp.ManufactureItem[i].sItemInfo.ItemHeader.Head,
				g_sManufactureItemBackUp.ManufactureItem[i].sItemInfo.ItemHeader.dwChkSum);
		}

	}
	memset(&g_sManufactureItem, 0, sizeof(SManufactureItem));
	memset(&g_sManufactureItemBackUp, 0, sizeof(SManufactureItem));
	memset(&g_sManufactureItem_Recv, 0, sizeof(SManufactureItem_Server));
	memset(&g_sManufactureItem_Send, 0, sizeof(SManufactureItem_Server));

	MixItemNoCopyFlag = 0;
	MixCancelButtonDelayFlag = 0;
	m_ManufacturePrice = 0;
	ForceItemPrice2 = 0;
	return TRUE;
}

int CManufacture::GetManufactureCheckEmptyArea()
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;
	int StartX = 23;
	int StartY = 436;

	cx = (22 * INVENTORY_BOX_ROW) - 22;
	cy = (22 * INVENTORY_BOX_COL) - 22;

	int count = 0;

	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (cInvenTory.InvenItem[i].Flag)
				{
					rect.left = cInvenTory.InvenItem[i].x;
					rect.right = cInvenTory.InvenItem[i].x + cInvenTory.InvenItem[i].w;
					rect.top = cInvenTory.InvenItem[i].y;
					rect.bottom = cInvenTory.InvenItem[i].y + cInvenTory.InvenItem[i].h;

					if (cntx > rect.left - 22 && cntx< rect.right &&
						cnty > rect.top - 22 && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				count++;
			}
		}
	}
	if (count)
		return count;
	else
		return 0;
}


int CSmeltingItem::GetSheltomIndex(DWORD SmeltingItemCode)
{
	DWORD SmeltingItemAray[] = { (sinPR1 | sin01), (sinPR1 | sin02), (sinPR1 | sin03), (sinPR1 | sin04), (sinPR1 | sin05), (sinPR1 | sin06), (sinPR1 | sin07), (sinPR1 | sin08),
								 (sinPR2 | sin01), (sinPR2 | sin02), (sinPR2 | sin03), (sinPR2 | sin04), (sinPR2 | sin05), (sinPR2 | sin06), (sinPR2 | sin07), (sinPR2 | sin08),
								 (sinPR2 | sin09), (sinPR2 | sin10), (sinPR2 | sin11), (sinPR2 | sin12), (sinPR2 | sin13), (sinPR2 | sin14) };
	int SheltomAray[] = { 6, 7, 8, 9, 10, 11, 12, 13,
						  7, 8, 9, 10, 11, 12, 13, 14,
							3, 4, 5, 3, 4, 5 };
	for (int i = 0; i < 22; i++)
	{
		if (SmeltingItemCode == SmeltingItemAray[i])
		{
			return SheltomAray[i];
		}
	}
	return FALSE;
}


SManufacture_ResultItemInfo CManufacture::ManufactureCheckItem(sITEM *pItemCode, smCHAR_INFO *charInfo)
{
	int RuneCnt = 0;
	SManufacture_ResultItemInfo Result;
	memset(&Result, 0, sizeof(SManufacture_ResultItemInfo));
	DWORD Arm_Armor_Code[MAX_RECIPE_KIND] = { sin01, sin02, sin03, sin04, sin05 };
	DWORD CheckRuneCode[MAX_HANDMADEITEM][5][3] = { {
			//Shelton 1
			{ (sinPR3 | sin01), (sinPR3 | sin02), (sinPR3 | sin03) },},
			//Shelton 2
{			{ (sinPR3 | sin04), (sinPR3 | sin05), (sinPR3 | sin06) },},
			//Shelton 3
{			{ (sinPR3 | sin07), (sinPR3 | sin08), (sinPR3 | sin09) },},
			//Shelton 4
{			{ (sinPR3 | sin10), (sinPR4 | sin11), (sinPR3 | sin12) },},
			//Shelton 5
			{ (sinPR3 | sin13), (sinPR3 | sin14), (sinPR3 | sin15) }, };

	DWORD	dwItem = 0;

	DWORD CreateItemCode[2][MAX_HANDMADEITEM][10] = {
									(sinOA2 | sin31), (sinOA2 | sin31), (sinOA2 | sin31), (sinOA2 | sin31), (sinOA2 | sin31), (sinOA2 | sin31), (sinOA2 | sin31), (sinOA2 | sin31),
									(sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19),
									(sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20),
									(sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21),
									(sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22),
	};

	if ((pItemCode[0].CODE & sinITEM_MASK2) == sinWR1)
	{
		for (int i = 0; i < MAX_RECIPE_KIND; i++)
		{
			if (Arm_Armor_Code[i] == (pItemCode[0].CODE & sinITEM_MASK3))
			{
				for (int j = 0; j < MAX_RUNE; j++)
				{
					RuneCnt = 0;
					for (int x = 0; x < 3; x++)
					{
						for (int y = 0; y < 3; y++)
						{
							if (CheckRuneCode[i][j][x] == pItemCode[y + 1].CODE)
							{
								RuneCnt++;
								break;
							}
						}
						if (RuneCnt == 3)
						{
							for (int c = 0; c < MAX_HANDMADEITEM; c++)
							{
								if (CreateItemCode[0][i][j] == g_Manufacture_ItemInfo[c].ItemCode)
								{
									Result.ItemCode = g_Manufacture_ItemInfo[c].ItemCode;
									strcpy_s(Result.ItemName, g_Manufacture_ItemInfo[c].ItemName);
									Result.Weight = g_Manufacture_ItemInfo[c].Weight;
									Result.Price = g_Manufacture_ItemInfo[c].Price / 3;
									ForceItemPrice2 = Result.Price;
									m_ManufacturePrice = Result.Price;
								}
							}
							return Result;
						}
					}
				}
			}
		}
	}	
	return Result;
}


int ManufactureItemResultInfo(SManufacture_ResultItemInfo_Server *pResultItemInfo)
{
	for (int i = 0; i < MAX_HANDMADEITEM; i++)
	{
		g_Manufacture_ItemInfo[i].ItemCode = pResultItemInfo->ItemCode[i];
		strcpy_s(g_Manufacture_ItemInfo[i].ItemName, pResultItemInfo->ItemName[i]);
		g_Manufacture_ItemInfo[i].Weight = pResultItemInfo->Weight[i];
		g_Manufacture_ItemInfo[i].Price = pResultItemInfo->Price[i];
	}
	return TRUE;
}