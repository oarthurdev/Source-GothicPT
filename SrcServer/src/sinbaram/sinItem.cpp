

#include "sinLinkHeader.h"
#include "Language\\language.h"

cITEM cItem;

sITEM TempItem;
sITEM MouseItem;

sITEMREQUIRE sRequire;
POINT ItemBoxPosi;
POINT ItemBoxSize;
POINT TextSetPosi;


char	szInfoBuff[5000];
char    szInfoBuff2[5000];

int sinShowItemInfoFlag = 0;

int tWeaponClass = 0;
int AgingGageFlag = 0;
int AgingBarLenght = 0;

DWORD sinItemTime = 0;

int NotSell_Item_CODECnt = 0;
int NotSell_Item_MASKCnt = 0;
int NotSell_Item_KINDCnt = 0;

int NotDrow_Item_CODECnt = 0;
int NotDrow_Item_MASKCnt = 0;
int NotDrow_Item_KINDCnt = 0;

int NotSet_Item_CODECnt = 0;
int NotSet_Item_MASKCnt = 0;
int NotSet_Item_KINDCnt = 0;


DWORD NotSell_Item_CODE[] = { (sinQT1 | sin07),(sinQT1 | sin08),0 };
DWORD NotSell_Item_MASK[] = { 0 };
DWORD NotSell_Item_KIND[] = { ITEM_KIND_QUEST_WEAPON,0 };

DWORD NotDrow_Item_CODE[] = { (sinQT1 | sin07),(sinQT1 | sin08),0 };
DWORD NotDrow_Item_MASK[] = { 0 };
DWORD NotDrow_Item_KIND[] = { ITEM_KIND_QUEST_WEAPON,0 };

DWORD NotSet_Item_CODE[] = { (sinQT1 | sin07),(sinQT1 | sin08),0 };
DWORD NotSet_Item_MASK[] = { 0 };
DWORD NotSet_Item_KIND[] = { ITEM_KIND_QUEST_WEAPON,0 };




sITEM sItem[MAX_ITEM] = {
#include "items.h"
};

cITEM::cITEM()
{

}

cITEM::~cITEM()
{

}

void cITEM::Init()
{
	for(int cnt = 0; cnt < MAX_ITEM; cnt++)
	{
		sItem[cnt].sItemInfo.CODE = sItem[cnt].CODE;
	}

	MatItemInfoBox = CreateTextureMaterial("Image\\SinImage\\Items\\ItemInfoBox.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MatItemInfoBox_TopLeft = CreateTextureMaterial("Image\\SinImage\\Items\\ItemInfoBox\\BoxTopLeft.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatItemInfoBox_TopRight = CreateTextureMaterial("Image\\SinImage\\Items\\ItemInfoBox\\BoxTopRight.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatItemInfoBox_TopCenter = CreateTextureMaterial("Image\\SinImage\\Items\\ItemInfoBox\\BoxTopCenter.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MatItemInfoBox_BottomLeft = CreateTextureMaterial("Image\\SinImage\\Items\\ItemInfoBox\\BoxBottomLeft.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatItemInfoBox_BottomRight = CreateTextureMaterial("Image\\SinImage\\Items\\ItemInfoBox\\BoxBottomRight.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatItemInfoBox_BottomCenter = CreateTextureMaterial("Image\\SinImage\\Items\\ItemInfoBox\\BoxBottomCenter.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MatItemInfoBox_Left = CreateTextureMaterial("Image\\SinImage\\Items\\ItemInfoBox\\BoxLeft.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatItemInfoBox_Right = CreateTextureMaterial("Image\\SinImage\\Items\\ItemInfoBox\\BoxRight.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatItemInfoBox_Center = CreateTextureMaterial("Image\\SinImage\\Items\\ItemInfoBox\\BoxCenter.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Load();


	int CheckCount = 0;
	while(1)
	{

		if(NotSell_Item_CODE[NotSell_Item_CODECnt])
			NotSell_Item_CODECnt++;
		else
			CheckCount++;

		if(NotSell_Item_MASK[NotSell_Item_MASKCnt])
			NotSell_Item_MASKCnt++;
		else
			CheckCount++;

		if(NotSell_Item_KIND[NotSell_Item_KINDCnt])
			NotSell_Item_KINDCnt++;
		else
			CheckCount++;


		if(NotDrow_Item_CODE[NotDrow_Item_CODECnt])
			NotDrow_Item_CODECnt++;
		else
			CheckCount++;

		if(NotDrow_Item_MASK[NotDrow_Item_MASKCnt])
			NotDrow_Item_MASKCnt++;
		else
			CheckCount++;

		if(NotDrow_Item_KIND[NotDrow_Item_KINDCnt])
			NotDrow_Item_KINDCnt++;
		else
			CheckCount++;


		if(NotSet_Item_CODE[NotSet_Item_CODECnt])
			NotSet_Item_CODECnt++;
		else
			CheckCount++;

		if(NotSet_Item_MASK[NotSet_Item_MASKCnt])
			NotSet_Item_MASKCnt++;
		else
			CheckCount++;

		if(NotSet_Item_KIND[NotSet_Item_KINDCnt])
			NotSet_Item_KINDCnt++;
		else
			CheckCount++;

		if(CheckCount >= 9)
			break;

	}

	memset(g_Manufacture_ItemInfo, 0, sizeof(SManufacture_ResultItemInfo));
}

void cITEM::Load()
{
	AgingBar = LoadDibSurfaceOffscreen("image\\Sinimage\\shopall\\Aging\\Bar.bmp");
	AgingGage = LoadDibSurfaceOffscreen("image\\Sinimage\\shopall\\Aging\\Bar_.bmp");
	AgingBar2 = LoadDibSurfaceOffscreen("image\\Sinimage\\shopall\\Aging\\Aging.bmp");
}

void cITEM::Release()
{
	if(AgingBar)
	{
		AgingBar->Release();
		AgingBar = 0;
	}
	if(AgingGage)
	{
		AgingGage->Release();
		AgingGage = 0;
	}
	if(AgingBar2)
	{
		AgingBar2->Release();
		AgingBar2 = 0;
	}
}

void cITEM::Draw()
{
	int t = 0, i = 0;
	char TempBuff[64];
	int len = 0, len2 = 0;
	int tSetTextXposi = 0;
	int x, y;
	len = lstrlen(szInfoBuff);

	memset(&TempBuff, 0, sizeof(TempBuff));
	for(i = 0; i < len; i++)
	{
		if(szInfoBuff[i] == '\r')
		{
			memcpy(TempBuff, szInfoBuff, i);
			break;
		}

	}
	len2 = lstrlen(TempBuff);
	tSetTextXposi = (int)(ItemBoxPosi.x + (((ItemBoxSize.x * 16) / 2) - ((len2*5.5) / 2)) + (len2*5.5));

	if(MouseItem.Flag)
	{
		if(!MouseItem.lpItem)
			dsDrawColorBox(RGBA_MAKE(125, 125, 255, 125), MouseItem.x, MouseItem.y, MouseItem.w, MouseItem.h);

		x = pCursorPos.x - (MouseItem.w / 2);
		y = pCursorPos.y - (MouseItem.h / 2);

		dsDrawOffsetArray = dsARRAY_TOP;
		DrawSprite(x, y, MouseItem.lpItem, 0, 0, MouseItem.w, MouseItem.h);
		if((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 || (MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinPZ2)
		{
			if(MouseItem.sItemInfo.PotionCount == 2)
			{
				if(MouseItem.w == 44)
					DrawSprite(x, y, cInvenTory.lpPuzzlewidth, 0, 0, 44, 22);
				if(MouseItem.w == 22)
					DrawSprite(x, y, cInvenTory.lpPuzzleHeight, 0, 0, 22, 44);
			}
		}

		if(cMyShop.OpenFlag)
			dsDrawColorBox(RGBA_MAKE(0, 0, 128, 125), x, y, MouseItem.w, MouseItem.h);
	}

	if(sinShowItemInfoFlag)
	{
		

		if(sinShowItemInfoFlag == 1)dsDrawOffsetArray = dsARRAY_TOP;
		else dsDrawOffsetArray = dsARRAY_BOTTOM;
		for(i = 0; i < ItemBoxSize.x; i++)
		{
			for(int j = 0; j < ItemBoxSize.y; j++)
			{
				if(i == 0 && j == 0)
					dsDrawTexImage(MatItemInfoBox_TopLeft, ItemBoxPosi.x + (i * 16), ItemBoxPosi.y + (j * 16), 16, 16, 255);
				if(j == 0 && i != 0 && i + 1 < ItemBoxSize.x)
					dsDrawTexImage(MatItemInfoBox_TopCenter, ItemBoxPosi.x + (i * 16), ItemBoxPosi.y + (j * 16), 16, 16, 255);
				if(j == 0 && i + 1 == ItemBoxSize.x)
					dsDrawTexImage(MatItemInfoBox_TopRight, ItemBoxPosi.x + (i * 16), ItemBoxPosi.y + (j * 16), 16, 16, 255);
				if(i == 0 && j != 0 && j + 1 != ItemBoxSize.y)
					dsDrawTexImage(MatItemInfoBox_Left, ItemBoxPosi.x + (i * 16), ItemBoxPosi.y + (j * 16), 16, 16, 255);
				if(i != 0 && j != 0 && i + 1 != ItemBoxSize.x && j + 1 != ItemBoxSize.y)
					dsDrawTexImage(MatItemInfoBox_Center, ItemBoxPosi.x + (i * 16), ItemBoxPosi.y + (j * 16), 16, 16, 255);
				if(i + 1 == ItemBoxSize.x && j != 0 && j + 1 != ItemBoxSize.y)
					dsDrawTexImage(MatItemInfoBox_Right, ItemBoxPosi.x + (i * 16), ItemBoxPosi.y + (j * 16), 16, 16, 255);
				if(i == 0 && j + 1 == ItemBoxSize.y)
					dsDrawTexImage(MatItemInfoBox_BottomLeft, ItemBoxPosi.x + (i * 16), ItemBoxPosi.y + (j * 16), 16, 16, 255);
				if(i != 0 && j + 1 == ItemBoxSize.y && i + 1 != ItemBoxSize.x)
					dsDrawTexImage(MatItemInfoBox_BottomCenter, ItemBoxPosi.x + (i * 16), ItemBoxPosi.y + (j * 16), 16, 16, 255);
				if(j + 1 == ItemBoxSize.y && i + 1 == ItemBoxSize.x)
					dsDrawTexImage(MatItemInfoBox_BottomRight, ItemBoxPosi.x + (i * 16), ItemBoxPosi.y + (j * 16), 16, 16, 255);
			}
		}

		if(tWeaponClass == 1)
			DrawSprite(tSetTextXposi, ItemBoxPosi.y + 8, cInvenTory.lpShowWeaponClass[0], 0, 0, 18, 16);

		if(tWeaponClass == 2)
			DrawSprite(tSetTextXposi, ItemBoxPosi.y + 8, cInvenTory.lpShowWeaponClass[1], 0, 0, 18, 16);

		if(tWeaponClass == 3)
			DrawSprite(tSetTextXposi, ItemBoxPosi.y + 8, cInvenTory.lpShowWeaponClass[2], 0, 0, 18, 16);

		if(tWeaponClass == 4)
			DrawSprite(tSetTextXposi, ItemBoxPosi.y + 8, cInvenTory.lpShowWeaponClass[3], 0, 0, 18, 16);

		if(AgingGageFlag)
		{
			if(AgingGageFlag == 1)
				DrawSprite(ItemBoxPosi.x + 14, ItemBoxPosi.y + 30, AgingBar, 0, 0, 130, 19);
			if(AgingGageFlag == 2)
				DrawSprite(ItemBoxPosi.x + 14 + 53, ItemBoxPosi.y + 30, AgingBar2, 0, 0, 23, 19);
			if(AgingBarLenght)
				DrawSprite(ItemBoxPosi.x + 16, ItemBoxPosi.y + 37, AgingGage, 0, 0, AgingBarLenght, 4);
		}
	}
}

void cITEM::Main()
{

	sinShowItemInfoFlag = 0;
	if(MouseItem.Flag)
	{
		if(!sinMessageBoxShowFlag)
		{
			MouseItem.x = pCursorPos.x - (MouseItem.w / 2);
			MouseItem.y = pCursorPos.y - (MouseItem.h / 2);
		}

	}
	if(cMyShop.OpenFlag)
	{
		if(MyShopMouseItem.Flag)
		{
			MyShopMouseItem.x = pCursorPos.x - (MyShopMouseItem.w / 2);
			MyShopMouseItem.y = pCursorPos.y - (MyShopMouseItem.h / 2);
		}
	}

	CheckItemTable();

}

void cITEM::GetMousePos(int *MouseX, int *MouseY)
{
	if(MouseItem.Flag)
	{
		if(!sinMessageBoxShowFlag)
		{
			*MouseX = pCursorPos.x - (MouseItem.w / 2);
			*MouseY = pCursorPos.y - (MouseItem.h / 2);
		}
	}
	if(cMyShop.OpenFlag)
	{
		if(MyShopMouseItem.Flag)
		{
			*MouseX = pCursorPos.x - (MyShopMouseItem.w / 2);
			*MouseY = pCursorPos.y - (MyShopMouseItem.h / 2);
		}
	}

}

void cITEM::Close()
{

}

void cITEM::LButtonDown(int x, int y)
{

}

void cITEM::LButtonUp(int x, int y)
{

}

void cITEM::RButtonDown(int x, int y)
{
	if(!MouseItem.Flag)
		CursorClass = 1;
}

void cITEM::RButtonUp(int x, int y)
{

}

void cITEM::KeyDown()
{

}

int sinLineCount = 0;
int RedLine[10] = { 0,0,0,0,0,0,0,0,0,0 };
int SpecialItemLine = 0;
int CountSpecialName = 0;
int   ItemInfoCol = 0;
int UniFlag = 0;
DWORD sinItemKindFlag = 0;
sITEMINFO sInfo;
sITEMPRICE sinItemPrice;


int RequireLine[10] = { 0,0,0,0,0,0,0,0,0 };
int MixItemLine[10] = { 0,0,0,0,0,0,0,0,0,0 };
int AgingItemLine[10] = { 0,0,0,0,0,0,0,0,0,0 };
int AgingLevel4 = 0;
int QuestItemLine = 0;
int MyShopItemPriceLine = 0;


int cITEM::ShowItemInfo(sITEM *pItem, int Flag, int Index)
{
	int   cnt = 0;
	int   BlockRate = 0;
	int   sinSpeed = 0;
	int   sinAbsorb = 0;
	int   sinLeftSpot = 0;
	int   sinRightSpot = 0;
	int   sinRegen = 0;

	char	szTemp[64];
	char    szTemp2[64];
	tWeaponClass = 0;
	AgingGageFlag = 0;
	AgingBarLenght = 0;
	AgingLevel4 = 0;
	QuestItemLine = 0;

	int AgingCnt = 0;

	UniFlag = 0;
	sinItemKindFlag = 0;


	ItemInfoCol = 0;
	SpecialItemLine = 0;

	if(pItem->Class == ITEM_CLASS_WEAPON_ONE)
		tWeaponClass = 1;

	if(pItem->Class == ITEM_CLASS_WEAPON_TWO)
		tWeaponClass = 2;

	if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDA1)
		tWeaponClass = 3;
	if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDA2)
		tWeaponClass = 4;

	if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinOM1)
		tWeaponClass = 4;


	for(int t = 0; t < 10; t++)
	{
		RedLine[t] = 0;
		RequireLine[t] = 0;
	}
	for(int t = 0; t < 10; t++)
	{
		MixItemLine[t] = 0;
		AgingItemLine[t] = 0;

	}


	sRequire.rDexterity = 0;
	sRequire.rHealth = 0;
	sRequire.rLevel = 0;
	sRequire.rSpirit = 0;
	sRequire.rStrength = 0;
	sRequire.rTalent = 0;

	memset(&szTemp, 0, sizeof(szTemp));
	memset(&szTemp2, 0, sizeof(szTemp2));
	memset(&szInfoBuff, 0, sizeof(szInfoBuff));
	memset(&szInfoBuff2, 0, sizeof(szInfoBuff2));

	if(pItem->Class == ITEM_CLASS_WEAPON_TWO && pItem->ItemPosition)
	{
		memcpy(&sInfo, &cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo, sizeof(sITEMINFO));

	}
	else
		memcpy(&sInfo, &pItem->sItemInfo, sizeof(sITEMINFO));


#ifdef	_LANGUAGE_CHINESE 
	{
		if(sInfo.CODE == (sinWA1 | sin20))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[0]);
		}

		if(sInfo.CODE == (sinWC1 | sin20))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[1]);
		}

		if(sInfo.CODE == (sinWH1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[2]);
		}

		if(sInfo.CODE == (sinWM1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[7]);
		}

		if(sInfo.CODE == (sinWP1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[3]);
		}

		if(sInfo.CODE == (sinWS1 | sin22))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[4]);
		}

		if(sInfo.CODE == (sinWS2 | sin23))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[5]);
		}

		if(sInfo.CODE == (sinWT1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[6]);
		}

	}
#endif
#ifdef	_LANGUAGE_ENGLISH 
	{
		if(sInfo.CODE == (sinWA1 | sin20))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[0]);
		}

		if(sInfo.CODE == (sinWC1 | sin20))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[1]);
		}

		if(sInfo.CODE == (sinWH1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[2]);
		}

		if(sInfo.CODE == (sinWM1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[7]);
		}

		if(sInfo.CODE == (sinWP1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[3]);
		}

		if(sInfo.CODE == (sinWS1 | sin22))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[4]);
		}

		if(sInfo.CODE == (sinWS2 | sin23))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[5]);
		}

		if(sInfo.CODE == (sinWT1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[6]);
		}



	}
#endif
#ifdef	_LANGUAGE_VEITNAM 
	{
		if(sInfo.CODE == (sinWA1 | sin20))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[0]);
		}

		if(sInfo.CODE == (sinWC1 | sin20))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[1]);
		}

		if(sInfo.CODE == (sinWH1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[2]);
		}

		if(sInfo.CODE == (sinWM1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[7]);
		}

		if(sInfo.CODE == (sinWP1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[3]);
		}

		if(sInfo.CODE == (sinWS1 | sin22))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[4]);
		}

		if(sInfo.CODE == (sinWS2 | sin23))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[5]);
		}

		if(sInfo.CODE == (sinWT1 | sin21))
		{
			strcpy(sInfo.ItemName, ha100LVQuestItemName[6]);
		}

	}
#endif

	if(sInfo.UniqueItem)
		UniFlag = 1;
	if(sInfo.ItemKindCode)
		sinItemKindFlag = sInfo.ItemKindCode;


	if(sInfo.CODE == (sinQT1 | sin06))
	{
		sinItemKindFlag = 100;
	}



	if(tWeaponClass)
		wsprintf(szInfoBuff, "%s%s\r", sInfo.ItemName, "  ");
	else
		wsprintf(szInfoBuff, "%s\r", sInfo.ItemName);


	if((sInfo.CODE & sinITEM_MASK2) == sinPZ1 || (sInfo.CODE & sinITEM_MASK2) == sinPZ2)
	{
		if(sInfo.PotionCount <= 1)
		{
			wsprintf(szInfoBuff, "%s\r", sinLuckyBox);

		}
	}


	strcpy_s(szInfoBuff2, "\r");
	ItemInfoCol++;


	if(sInfo.ItemKindCode == ITEM_KIND_AGING)
	{
		if(sInfo.ItemAgingCount[1]) AgingGageFlag = 1;
		else AgingGageFlag = 2;

		lstrcat(szInfoBuff, "\r\r");
		lstrcat(szInfoBuff2, "\r\r");
		ItemInfoCol++;
		ItemInfoCol++;
		if(sInfo.ItemAgingCount[0])
		{
			AgingBarLenght = (int)((float)((float)125 * (((float)sInfo.ItemAgingCount[0] / (float)sInfo.ItemAgingCount[1]))));


		}
		AgingLevel4 = sInfo.ItemAgingNum[0];

	}
	if(sInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON && sInfo.ItemAgingNum[0] < 4 &&
		(sInfo.CODE & sinITEM_MASK2) != sinOR2)
	{
		lstrcat(szInfoBuff, "\r");
		lstrcat(szInfoBuff2, "\r");
		ItemInfoCol++;

		wsprintf(szTemp, "%s:%d/%d  \r", QuestMonsterName[sInfo.ItemAgingNum[1]], sInfo.ItemAgingCount[1] - sInfo.ItemAgingCount[0], sInfo.ItemAgingCount[1]);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		QuestItemLine = ItemInfoCol;

		lstrcat(szInfoBuff, "\r");
		lstrcat(szInfoBuff2, "\r");
		ItemInfoCol++;


	}



	if(pItem->CODE == (sinEC1 | sin01))
	{
		strcpy_s(szTemp, TownName[0]);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	if(pItem->CODE == (sinEC1 | sin02))
	{
		strcpy_s(szTemp, TownName[1]);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(pItem->CODE == (sinEC1 | sin04))
	{
		strcpy_s(szTemp, TownName[2]);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}





	if(pItem->CODE == (sinGP1 | sin10) || pItem->CODE == (sinGP1 | sin22))
	{
		strcpy_s(szTemp, ClanCristalName);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		for(cnt = 0; cnt < 10; cnt++)
		{
			if(!MixItemLine[cnt])
			{
				MixItemLine[cnt] = ItemInfoCol;
				break;
			}
		}
	}


	int len = lstrlen(pItem->sItemInfo.ItemName);
	char szLinkName[24];
	if(pItem->CODE == (sinEC1 | sin05))
	{
		strcpy_s(szTemp, LinkCoreName);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if(pItem->sItemInfo.ItemName[len + 1] != NULL)
		{

			lstrcat(szInfoBuff, "\r");
			lstrcat(szInfoBuff2, "\r");
			ItemInfoCol++;

			strcpy_s(szLinkName, &pItem->sItemInfo.ItemName[len + 1]);
			strcpy_s(szTemp, szLinkName);
			lstrcat(szInfoBuff, DesLinkCore);
			lstrcat(szInfoBuff, szTemp);
			strcpy_s(szTemp2, "\r");
			lstrcat(szInfoBuff, szTemp2);
			lstrcat(szInfoBuff2, szTemp2);
			ItemInfoCol++;

			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}

			}

		}
	}

	if(sInfo.ItemKindCode == 1) // Se esse itemKindCode for 1 é pq o item é mixado
	{
		lstrcat(szInfoBuff, "Mix \r");
		lstrcat(szInfoBuff2, "Item\r");
		ItemInfoCol++;
	}

	if(sInfo.Damage[0] || sInfo.Damage[1])
	{
		strcpy_s(szTemp, sinAbilityName[0]);
		wsprintf(szTemp2, "%d-%d\r", sInfo.Damage[0], sInfo.Damage[1]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_DAMAGE_MIN) != 0 ||
			(sInfo.ItemKindMask & SIN_ADD_DAMAGE_MAX) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}

			}
		}

		if(sInfo.ItemAgingNum[0])
		{
			if((sInfo.CODE & sinITEM_MASK2) == sinWA1 ||
				(sInfo.CODE & sinITEM_MASK2) == sinWC1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWH1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWM1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWP1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWS1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWS2 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWT1)

				AgingItemLine[AgingCnt++] = ItemInfoCol;

		}

	}

	if(sInfo.Attack_Speed)
	{
		strcpy_s(szTemp, sinAbilityName[1]);
		if(CheckQuestItemDownFlag && sInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON)
		{
			wsprintf(szTemp2, "%d\r", sInfo.Attack_Speed - 2);
			RedLine[9] = ItemInfoCol + 1;
		}
		else
		{
			wsprintf(szTemp2, "%d\r", sInfo.Attack_Speed);
		}
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_ATTACK_SPEED) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}

			}
		}

	}

	if(sInfo.Shooting_Range)
	{
		strcpy_s(szTemp, sinAbilityName[2]);
		wsprintf(szTemp2, "%d\r", sInfo.Shooting_Range);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;





	}
	if(sInfo.Critical_Hit)
	{
		strcpy_s(szTemp, sinAbilityName[3]);
		wsprintf(szTemp2, "%d%s\r", sInfo.Critical_Hit, "%");
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_CRITICAL) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}

		if(sInfo.ItemAgingNum[0])
		{
			if((sInfo.CODE & sinITEM_MASK2) == sinWC1 ||
				(sInfo.CODE & sinITEM_MASK2) == sinWP1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWS1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWT1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWS2)
				AgingItemLine[AgingCnt++] = ItemInfoCol;

		}
	}


	if(sInfo.Defence)
	{
		strcpy_s(szTemp, sinAbilityName[4]);
		wsprintf(szTemp2, "%d\r", sInfo.Defence);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_DEFENCE) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}


		if(sInfo.ItemAgingNum[0])
		{
			if((sInfo.CODE & sinITEM_MASK2) == sinOM1 ||
				(sInfo.CODE & sinITEM_MASK2) == sinDA1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDA2 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDB1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDG1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinOA2)
			{
				AgingItemLine[AgingCnt++] = ItemInfoCol;
			}

		}

	}

	if(sInfo.Attack_Rating)
	{
		strcpy_s(szTemp, sinAbilityName[5]);
		wsprintf(szTemp2, "%d\r", sInfo.Attack_Rating);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_ATTACK_RATE) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}

		if(sInfo.ItemAgingNum[0])
		{
			if((sInfo.CODE & sinITEM_MASK2) == sinWA1 ||
				(sInfo.CODE & sinITEM_MASK2) == sinWC1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWM1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWH1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWP1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWS2 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinOA2)
			{
				AgingItemLine[AgingCnt++] = ItemInfoCol;
			}
		}
	}

	if(sInfo.fAbsorb)
	{

		sinAbsorb = (int)(GetItemAbsorb(&sInfo)*10.001f);
		sinRightSpot = sinAbsorb % 10;
		sinLeftSpot = (sinAbsorb - sinRightSpot) / 10;
		strcpy_s(szTemp, sinAbilityName[6]);
		wsprintf(szTemp2, "%d.%d\r", sinLeftSpot, sinRightSpot);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_ABSORB) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}

		}
		if(sInfo.ItemAgingNum[0])
		{
			if((sInfo.CODE & sinITEM_MASK2) == sinOM1 ||
				(sInfo.CODE & sinITEM_MASK2) == sinDA1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDS1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDA2 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDB1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDG1)
			{
				AgingItemLine[AgingCnt++] = ItemInfoCol;
			}
		}
	}

	if(sInfo.fBlock_Rating)
	{
		BlockRate = (int)(sInfo.fBlock_Rating);
		strcpy_s(szTemp, sinAbilityName[7]);
		wsprintf(szTemp2, "%d%s\r", BlockRate, "%");
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

		if((sInfo.ItemKindMask & SIN_ADD_BLOCK_RATE) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}

			}
		}


		if(sInfo.ItemAgingNum[0])
		{
			if((sInfo.CODE & sinITEM_MASK2) == sinDS1)
				AgingItemLine[AgingCnt++] = ItemInfoCol;

		}


	}


	if(sInfo.fSpeed)
	{
		sinSpeed = (int)(sInfo.fSpeed *10.001f);
		sinRightSpot = sinSpeed % 10;
		sinLeftSpot = (sinSpeed - sinRightSpot) / 10;
		strcpy_s(szTemp, sinAbilityName[8]);
		wsprintf(szTemp2, "%d.%d\r", sinLeftSpot, sinRightSpot);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_MOVE_SPEED) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}

		}

	}

	if(sInfo.Durability[0] || sInfo.Durability[1])
	{
		strcpy_s(szTemp, sinAbilityName[9]);
		wsprintf(szTemp2, "%d/%d\r", sInfo.Durability[0], sInfo.Durability[1]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

		if(sInfo.ItemAgingNum[0])
		{
			if((sInfo.CODE & sinITEM_MASK2) == sinWA1 ||
				(sInfo.CODE & sinITEM_MASK2) == sinWH1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWS1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDS1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinOM1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDA1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDA2 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDB1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinDG1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinOA2)
			{
				AgingItemLine[AgingCnt++] = ItemInfoCol;
			}

		}

	}


	if(sInfo.Mana[0] || sInfo.Mana[1])
	{
		strcpy_s(szTemp, sinAbilityName[10]);
		wsprintf(szTemp2, "%d-%d\r", sInfo.Mana[0], sInfo.Mana[1]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.Life[0] || sInfo.Life[1])
	{
		strcpy_s(szTemp, sinAbilityName[11]);
		wsprintf(szTemp2, "%d-%d\r", sInfo.Life[0], sInfo.Life[1]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.Stamina[0] || sInfo.Stamina[1])
	{
		strcpy_s(szTemp, sinAbilityName[12]);
		wsprintf(szTemp2, "%d-%d\r", sInfo.Stamina[0], sInfo.Stamina[1]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}


	if(sInfo.Resistance[0])
	{
		strcpy_s(szTemp, sinAbilityName[13]);
		wsprintf(szTemp2, "%d\r", sInfo.Resistance[0]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_BIO) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}
	}
	if(sInfo.Resistance[1])
	{
		strcpy_s(szTemp, sinAbilityName[14]);
		wsprintf(szTemp2, "%d\r", sInfo.Resistance[1]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.Resistance[2])
	{
		strcpy_s(szTemp, sinAbilityName[15]);
		wsprintf(szTemp2, "%d\r", sInfo.Resistance[2]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_FIRE) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}

		}

	}

	if(sInfo.Resistance[3])
	{
		strcpy_s(szTemp, sinAbilityName[16]);
		wsprintf(szTemp2, "%d\r", sInfo.Resistance[3]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_ICE) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}
	}
	if(sInfo.Resistance[4])
	{
		strcpy_s(szTemp, sinAbilityName[17]);
		wsprintf(szTemp2, "%d\r", sInfo.Resistance[4]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_LIGHTNING) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}
	}
	if(sInfo.Resistance[5])
	{
		strcpy_s(szTemp, sinAbilityName[18]);
		wsprintf(szTemp2, "%d\r", sInfo.Resistance[5]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_POISON) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}
	}
	if(sInfo.Resistance[6])
	{
		strcpy_s(szTemp, sinAbilityName[19]);
		wsprintf(szTemp2, "%d\r", sInfo.Resistance[6]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.Resistance[7])
	{
		strcpy_s(szTemp, sinAbilityName[20]);
		wsprintf(szTemp2, "%d\r", sInfo.Resistance[7]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	if(sInfo.fLife_Regen && (sInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		sinRegen = (int)(sInfo.fLife_Regen*10.001f);
		sinRightSpot = sinRegen % 10;
		sinLeftSpot = (sinRegen - sinRightSpot) / 10;
		strcpy_s(szTemp, sinAbilityName[21]);
		wsprintf(szTemp2, "%d.%d\r", sinLeftSpot, sinRightSpot);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_LIFEREGEN) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}

	}

	if(sInfo.fMana_Regen && (sInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		sinRegen = (int)(sInfo.fMana_Regen*10.001f);
		sinRightSpot = sinRegen % 10;
		sinLeftSpot = (sinRegen - sinRightSpot) / 10;
		strcpy_s(szTemp, sinAbilityName[22]);
		wsprintf(szTemp2, "%d.%d\r", sinLeftSpot, sinRightSpot);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

		if((sInfo.ItemKindMask & SIN_ADD_MANAREGEN) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}

	}

	if(sInfo.fStamina_Regen && (sInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		sinRegen = (int)(sInfo.fStamina_Regen*10.001f);
		sinRightSpot = sinRegen % 10;
		sinLeftSpot = (sinRegen - sinRightSpot) / 10;
		strcpy_s(szTemp, sinAbilityName[23]);
		wsprintf(szTemp2, "%d.%d\r", sinLeftSpot, sinRightSpot);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_STAMINAREGEN) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}

	}
	int AddState;
	if(sInfo.fIncrease_Life)
	{
		AddState = (int)sInfo.fIncrease_Life;
		strcpy_s(szTemp, sinAbilityName[24]);
		wsprintf(szTemp2, "%d\r", AddState);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_LIFE) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}
	}
	if(sInfo.fIncrease_Mana)
	{
		AddState = (int)sInfo.fIncrease_Mana;
		strcpy_s(szTemp, sinAbilityName[25]);
		wsprintf(szTemp2, "%d\r", AddState);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_MANA) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}


		if(sInfo.ItemAgingNum[0])
		{
			if((sInfo.CODE & sinITEM_MASK2) == sinWM1 ||
				(sInfo.CODE & sinITEM_MASK2) == sinWS1 ||
			   (sInfo.CODE & sinITEM_MASK2) == sinWT1)
			{
				AgingItemLine[AgingCnt++] = ItemInfoCol;
			}

		}

	}
	if(sInfo.fIncrease_Stamina)
	{
		AddState = (int)sInfo.fIncrease_Stamina;
		strcpy_s(szTemp, sinAbilityName[26]);
		wsprintf(szTemp2, "%d\r", AddState);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		if((sInfo.ItemKindMask & SIN_ADD_STAMINA) != 0)
		{
			for(cnt = 0; cnt < 10; cnt++)
			{
				if(!MixItemLine[cnt])
				{
					MixItemLine[cnt] = ItemInfoCol;
					break;
				}
			}
		}

	}
	if(sInfo.Potion_Space)
	{
		strcpy_s(szTemp, sinAbilityName[27]);
		wsprintf(szTemp2, "%d\r", sInfo.Potion_Space);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	int i = 0;
	if(sInfo.Level)
	{
		strcpy_s(szTemp, sinAbilityName[28]);
		if((sInfo.CODE & sinITEM_MASK2) == sinFO1)
		{
			lstrcat(szInfoBuff, "\r");
			lstrcat(szInfoBuff2, "\r");
			ItemInfoCol++;

			for(i = 0; i < 12; i++)
			{
				if(((pItem->CODE&sinITEM_MASK3) == SheltomCode2[i]))
				{
					if(i <= 3)
					{
						wsprintf(szTemp2, "%d-%d\r", ForceOrbUseLevel[i][0], ForceOrbUseLevel[i][1]);
					}
					else
					{
						wsprintf(szTemp2, "%d+\r", ForceOrbUseLevel[i][0]);
					}
					break;
				}
				else if(((pItem->CODE&sinITEM_MASK3) == MagicSheltomCode[i]))
				{
					if(i <= 3)
					{
						wsprintf(szTemp2, "%d-%d\r", MagicForceOrbUseLevel[i][0], MagicForceOrbUseLevel[i][1]);
					}
					else
					{
						wsprintf(szTemp2, "%d+\r", MagicForceOrbUseLevel[i][0]);
					}
					break;
				}
				else if(((pItem->CODE&sinITEM_MASK3) == BillingMagicSheltomCode[i]))
				{
					wsprintf(szTemp2, "%d+\r", BillingMagicForceOrbUseLevel[i][0]);
					break;
				}
			}
			lstrcat(szInfoBuff, szTemp);
			lstrcat(szInfoBuff2, szTemp2);
			ItemInfoCol++;
			RequireLine[0] = ItemInfoCol;
			if(sinChar->Level < ForceOrbUseLevel[i][0] ||
			   sinChar->Level > ForceOrbUseLevel[i][1])
			{
				sRequire.rLevel = 1;
				RedLine[0] = ItemInfoCol;
			}

		}
		else
		{
			wsprintf(szTemp2, "%d\r", sInfo.Level);
			lstrcat(szInfoBuff, szTemp);
			lstrcat(szInfoBuff2, szTemp2);
			ItemInfoCol++;
			RequireLine[0] = ItemInfoCol;
			if(sInfo.Level > sinChar->Level)
			{
				sRequire.rLevel = 1;
				RedLine[0] = ItemInfoCol;
			}
		}
	}


	if((sInfo.CODE & sinITEM_MASK2) == sinFO1)
	{
		for(i = 0; i < 12; i++)
		{
			if((pItem->CODE&sinITEM_MASK3) == SheltomCode2[i])
			{
				strcpy_s(szTemp, sinAddDamageItem);
				wsprintf(szTemp2, "%d\r", ForceOrbDamage[i]);
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;

				if(i > 5 && i < 10)
				{
					strcpy_s(szTemp, AddPercentDamage3);
					wsprintf(szTemp2, "%d%s\r", 10, "%");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;
				}
				else if(i == 10)
				{
					strcpy_s(szTemp, AddPercentDamage3);
					wsprintf(szTemp2, "%d%s\r", 15, "%");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;
				}
				else if(i == 11)
				{
					strcpy_s(szTemp, AddPercentDamage3);
					wsprintf(szTemp2, "%d%s\r", 20, "%");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;
				}

				strcpy_s(szTemp, sinContinueTimeItem);
				wsprintf(szTemp2, "%d%s\r", ForceOrbUseTime[i], SecName);
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;
				break;
			}
			else if((pItem->CODE&sinITEM_MASK3) == MagicSheltomCode[i])
			{
				strcpy_s(szTemp, sinAddDamageItem);
				wsprintf(szTemp2, "%d\r", MagicForceOrbDamage[i]);
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;


				if(i > 5 && i < 10)
				{
					strcpy_s(szTemp, AddPercentDamage3);
					wsprintf(szTemp2, "%d%s\r", 10, "%");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;
				}
				else if(i == 10)
				{
					strcpy_s(szTemp, AddPercentDamage3);
					wsprintf(szTemp2, "%d%s\r", 15, "%");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;
				}
				else if(i == 11)
				{
					strcpy_s(szTemp, AddPercentDamage3);
					wsprintf(szTemp2, "%d%s\r", 20, "%");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;
				}

				strcpy_s(szTemp, sinContinueTimeItem);
				wsprintf(szTemp2, "%d%s\r", MagicForceOrbUseTime[i], SecName);
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;
				break;
			}
			else if((pItem->CODE&sinITEM_MASK3) == BillingMagicSheltomCode[i])
			{

				strcpy_s(szTemp, AddPercentDamage3);
				wsprintf(szTemp2, "%d%s\r", 15, "%");
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;

				strcpy_s(szTemp, sinContinueTimeItem);
				wsprintf(szTemp2, "%d%s\r", BillingMagicForceOrbUseTime[i], SecName);
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;
				break;
			}
		}
	}

	/*
	//Trajes
	if (pItem->sItemInfo.CODE == (sinCA1 | sin01) || pItem->sItemInfo.CODE == (sinCA1 | sin02) ||
		pItem->sItemInfo.CODE == (sinCA1 | sin03) || pItem->sItemInfo.CODE == (sinCA1 | sin04) ||
		pItem->sItemInfo.CODE == (sinCA1 | sin05) || pItem->sItemInfo.CODE == (sinCA1 | sin06) ||
		pItem->sItemInfo.CODE == (sinCA1 | sin08) ||
		pItem->sItemInfo.CODE == (sinCA1 | sin09) || pItem->sItemInfo.CODE == (sinCA1 | sin10) ||
		pItem->sItemInfo.CODE == (sinCA1 | sin11) || pItem->sItemInfo.CODE == (sinCA1 | sin12) ||
		pItem->sItemInfo.CODE == (sinCA2 | sin01) || pItem->sItemInfo.CODE == (sinCA2 | sin02) ||
		pItem->sItemInfo.CODE == (sinCA2 | sin03) || pItem->sItemInfo.CODE == (sinCA2 | sin04) ||
		pItem->sItemInfo.CODE == (sinCA2 | sin05) || pItem->sItemInfo.CODE == (sinCA2 | sin06) ||
		pItem->sItemInfo.CODE == (sinCA2 | sin08) ||
		pItem->sItemInfo.CODE == (sinCA2 | sin09) || pItem->sItemInfo.CODE == (sinCA2 | sin10) ||
		pItem->sItemInfo.CODE == (sinCA2 | sin11) || pItem->sItemInfo.CODE == (sinCA2 | sin12))
	{
		DWORD NowTime = GetPlayTime_T();
		//DWORD Time = (60 * 60) - (NowTime - pItem->sItemInfo.dwCreateTime);
		DWORD Time = (60 * 60 * 24 * 7) - (NowTime - pItem->sItemInfo.dwCreateTime);

		strcpy_s(szTemp, sinContinueTimeItem);

		if (DeleteEventItem_TimeOut(&pItem->sItemInfo) == TRUE)
		{
			cInvenTory.DeleteInvenItemToServer(pItem->sItemInfo.CODE, pItem->sItemInfo.ItemHeader.Head, pItem->sItemInfo.ItemHeader.dwChkSum);
			ResetInvenItemCode();
		}
		else
			//wsprintf(szTemp2, "%d%s\r", (Time / 60) % 60, sinMinute2);
			wsprintf(szTemp2, "%d%s%d%s%d%s\r", (Time / 60 / 60) / 24, sinDay4, (Time / 60 / 60) % 24, sinHour4, (Time / 60) % 60, sinMinute2);



		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
	}
	

	// Trajes
	if (pItem->sItemInfo.CODE == (sinCA1 | sin07) || pItem->sItemInfo.CODE == (sinCA2 | sin07))
	{
		DWORD NowTime = GetPlayTime_T();
		//DWORD Time = (60 * 60) - (NowTime - pItem->sItemInfo.dwCreateTime);
		DWORD Time = (60 * 60 * 23) - (NowTime - pItem->sItemInfo.dwCreateTime);

		strcpy_s(szTemp, sinContinueTimeItem);

		if (DeleteEventItem_TimeOut(&pItem->sItemInfo) == TRUE)
		{
			cInvenTory.DeleteInvenItemToServer(pItem->sItemInfo.CODE, pItem->sItemInfo.ItemHeader.Head, pItem->sItemInfo.ItemHeader.dwChkSum);
			ResetInvenItemCode();
		}
		else
			//wsprintf(szTemp2, "%d%s\r", (Time / 60) % 60, sinMinute2);
			wsprintf(szTemp2, "%d%s%d%s%d%s\r", (Time / 60 / 60) / 24, sinDay4, (Time / 60 / 60) % 24, sinHour4, (Time / 60) % 60, sinMinute2);



		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
	}
	*/
	// Caixa Gladiador
	if (pItem->sItemInfo.CODE == (sinBI2 | sin81))
	{
		DWORD NowTime = GetPlayTime_T();
		DWORD Time = (60 * 30) - (NowTime - pItem->sItemInfo.dwCreateTime);

		strcpy_s(szTemp, sinContinueTimeItem);

		if (DeleteEventItem_TimeOut(&pItem->sItemInfo) == TRUE)
		{
			cInvenTory.DeleteInvenItemToServer(pItem->sItemInfo.CODE, pItem->sItemInfo.ItemHeader.Head, pItem->sItemInfo.ItemHeader.dwChkSum);
			ResetInvenItemCode();
		}
		else
			wsprintf(szTemp2, "%d%s\r", (Time / 60) % 60, sinMinute2);



		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
	}
	

	if((sInfo.CODE & sinITEM_MASK2) == sinBI1)
	{
		for(int i = 0; i < 7; i++)
		{
			if(pItem->CODE == dwPremiumItemCode[i])
			{
				strcpy_s(szTemp, PremiumItemDoc[i][0]);
				wsprintf(szTemp2, "\r");
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;

				strcpy_s(szTemp, PremiumItemDoc[i][1]);
				wsprintf(szTemp2, "\r");
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;
				break;
			}
		}
	}

	if((sInfo.CODE & sinITEM_MASK2) == sinSE1)
	{
		for(int i = 0; i < MAX_SEEL_COUNT; i++)
		{
			if(pItem->CODE == sReconItem[i].dwCODE)
			{
				strcpy_s(szTemp, sinAbilityName[28]);
				wsprintf(szTemp2, "%d-%d\r", sReconItem[i].iLevel[0], sReconItem[i].iLevel[1]);
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;
			}
		}
	}


	if((sInfo.CODE & sinITEM_MASK2) == sinBC1)
	{
		for(i = 0; i < 16; i++)
		{
			if((pItem->CODE&sinITEM_MASK3) == dwCastlItemCODE[i])
			{

				if(i == 5 || i == 6 || i == 7)
				{
					strcpy_s(szTemp, CastlItemInfo[5]);
					wsprintf(szTemp2, "\r");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;

					strcpy_s(szTemp, CastlItemInfo2[5]);
					wsprintf(szTemp2, "\r");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;

					wsprintf(szTemp, AttributeTower[3], 60);
					wsprintf(szTemp2, "\r");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;

					strcpy_s(szTemp, AttributeTower[i - 5]);
					wsprintf(szTemp2, "\r");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;
					RedLine[1] = ItemInfoCol;

					break;
				}
				else if(i > 7)
				{
					strcpy_s(szTemp, CastlItemInfo[6]);
					wsprintf(szTemp2, "\r");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;

					strcpy_s(szTemp, CastlItemInfo2[6]);
					wsprintf(szTemp2, "\r");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;

					wsprintf(szTemp, AttributeTower[3], 60);
					wsprintf(szTemp2, "\r");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;

					strcpy_s(szTemp, CharClassTarget[i - 8]);
					wsprintf(szTemp2, "\r");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;
					RedLine[1] = ItemInfoCol;

					break;
				}
				else
				{
					strcpy_s(szTemp, CastlItemInfo[i]);
					wsprintf(szTemp2, "\r");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;

					strcpy_s(szTemp, CastlItemInfo2[i]);
					wsprintf(szTemp2, "\r");
					lstrcat(szInfoBuff, szTemp);
					lstrcat(szInfoBuff2, szTemp2);
					ItemInfoCol++;

					if(i < 3)
					{

						wsprintf(szTemp, AttributeTower[3], 30);
						wsprintf(szTemp2, "\r");
						lstrcat(szInfoBuff, szTemp);
						lstrcat(szInfoBuff2, szTemp2);
						ItemInfoCol++;
					}
					break;
				}
			}
		}

	}


	if((sInfo.CODE & sinITEM_MASK2) == sinBC1)
	{
		for(i = 0; i < 9; i++)
		{
			if((pItem->CODE&sinITEM_MASK3) == dwBoosterItemCode[i])
			{
				int m, n = 0;
				if(i >= 0 && i <= 2) m = 0;
				if(i >= 3 && i <= 5) m = 1;
				if(i >= 6 && i <= 8) m = 2;


				strcpy_s(szTemp, BoosterItemInfo[m]);
				wsprintf(szTemp2, "\r");
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;

				strcpy_s(szTemp, BoosterItemInfo2[m]);
				wsprintf(szTemp2, "\r");
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;

				if(i == 0 || i == 3 || i == 6) n = 0;
				if(i == 1 || i == 4 || i == 7) n = 1;
				if(i == 2 || i == 5 || i == 8) n = 2;
				wsprintf(szTemp, AttributeTower[3], BoosterItem_UseTime[n]);
				wsprintf(szTemp2, "\r");
				lstrcat(szInfoBuff, szTemp);
				lstrcat(szInfoBuff2, szTemp2);
				ItemInfoCol++;

				break;
			}

		}

	}

	if(sInfo.Strength)
	{
		strcpy_s(szTemp, sinAbilityName[29]);
		wsprintf(szTemp2, "%d\r", sInfo.Strength);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		RequireLine[1] = ItemInfoCol;
		if(sInfo.Strength > sinChar->Strength)
		{
			sRequire.rStrength = 1;
			RedLine[1] = ItemInfoCol;

		}

	}

	if(sInfo.Spirit && (sInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		strcpy_s(szTemp, sinAbilityName[30]);
		wsprintf(szTemp2, "%d\r", sInfo.Spirit);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		RequireLine[2] = ItemInfoCol;
		if(sInfo.Spirit > sinChar->Spirit)
		{
			sRequire.rSpirit = 1;
			RedLine[2] = ItemInfoCol;

		}

	}

	if(sInfo.Talent)
	{
		strcpy_s(szTemp, sinAbilityName[31]);
		wsprintf(szTemp2, "%d\r", sInfo.Talent);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		RequireLine[3] = ItemInfoCol;
		if(sInfo.Talent > sinChar->Talent)
		{
			sRequire.rTalent = 1;
			RedLine[3] = ItemInfoCol;

		}
	}

	if(sInfo.Dexterity)
	{
		strcpy_s(szTemp, sinAbilityName[32]);
		wsprintf(szTemp2, "%d\r", sInfo.Dexterity);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		RequireLine[4] = ItemInfoCol;
		if(sInfo.Dexterity > sinChar->Dexterity)
		{
			sRequire.rDexterity = 1;
			RedLine[4] = ItemInfoCol;

		}

	}
	if(sInfo.Health)
	{
		strcpy_s(szTemp, sinAbilityName[33]);
		wsprintf(szTemp2, "%d\r", sInfo.Health);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		RequireLine[5] = ItemInfoCol;
		if(sInfo.Health > sinChar->Health)
		{
			sRequire.rHealth = 1;
			RedLine[5] = ItemInfoCol;
		}

	}

	ShowItemInfo2(pItem, Flag, Index);
	return TRUE;
}

int cITEM::ShowItemInfo2(sITEM *pItem, int Flag, int Index)
{
	int   BlockRate = 0;
	int   sinSpeed = 0;
	int   sinAbsorb = 0;
	int   sinLeftSpot = 0;
	int   sinRightSpot = 0;
	int sinMagic_Mastery;

	int   sinRegen = 0;

	char	szTemp[64];
	char    szTemp2[64];

	sRequire.rDexterity = 0;
	sRequire.rHealth = 0;
	sRequire.rLevel = 0;
	sRequire.rSpirit = 0;
	sRequire.rStrength = 0;
	sRequire.rTalent = 0;

	memset(&szTemp, 0, sizeof(szTemp));
	memset(&szTemp2, 0, sizeof(szTemp2));



	if(sInfo.JobCodeMask && (sInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		SearchSpecialItemJob(sInfo.JobCodeMask);

	}

	if(sInfo.JobItem.Add_Attack_Speed)
	{
		strcpy_s(szTemp, sinSpecialName[0]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Attack_Speed);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Add_Critical_Hit)
	{
		strcpy_s(szTemp, sinSpecialName[1]);
		wsprintf(szTemp2, "%d%s\r", sInfo.JobItem.Add_Critical_Hit, "%");
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Add_Defence)
	{
		strcpy_s(szTemp, sinSpecialName[2]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Defence);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Add_fAbsorb)
	{
		sinAbsorb = (int)(sInfo.JobItem.Add_fAbsorb*10.001f);
		sinRightSpot = sinAbsorb % 10;
		sinLeftSpot = (sinAbsorb - sinRightSpot) / 10;
		strcpy_s(szTemp, sinSpecialName[3]);
		wsprintf(szTemp2, "%d.%d\r", sinLeftSpot, sinRightSpot);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Add_fBlock_Rating)
	{
		BlockRate = (int)(sInfo.JobItem.Add_fBlock_Rating);
		strcpy_s(szTemp, sinSpecialName[4]);
		wsprintf(szTemp2, "%d%s\r", BlockRate, "%");
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	if(sInfo.JobItem.Add_fMagic_Mastery)
	{
		sinMagic_Mastery = (int)(sInfo.JobItem.Add_fMagic_Mastery);
		strcpy_s(szTemp, sinSpecialName[5]);
		wsprintf(szTemp2, "%d\r", sinMagic_Mastery);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	if(sInfo.JobItem.Add_fSpeed)
	{
		sinSpeed = (int)(sInfo.JobItem.Add_fSpeed *10.001f);
		sinRightSpot = sinSpeed % 10;
		sinLeftSpot = (sinSpeed - sinRightSpot) / 10;
		strcpy_s(szTemp, sinSpecialName[6]);
		wsprintf(szTemp2, "%d.%d\r", sinLeftSpot, sinRightSpot);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	if(sInfo.JobItem.Add_Resistance[0])
	{
		strcpy_s(szTemp, sinSpecialName[7]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Resistance[0]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
	}
	if(sInfo.JobItem.Add_Resistance[1])
	{
		strcpy_s(szTemp, sinSpecialName[8]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Resistance[1]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
	}

	if(sInfo.JobItem.Add_Resistance[2])
	{
		strcpy_s(szTemp, sinSpecialName[9]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Resistance[2]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Add_Resistance[3])
	{
		strcpy_s(szTemp, sinSpecialName[10]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Resistance[3]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Add_Resistance[4])
	{
		strcpy_s(szTemp, sinSpecialName[11]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Resistance[4]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Add_Resistance[5])
	{
		strcpy_s(szTemp, sinSpecialName[12]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Resistance[5]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Add_Resistance[6])
	{
		strcpy_s(szTemp, sinSpecialName[13]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Resistance[6]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Add_Resistance[7])
	{
		strcpy_s(szTemp, sinSpecialName[14]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Resistance[7]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Lev_Damage[1])
	{
		strcpy_s(szTemp, sinSpecialName[15]);
		wsprintf(szTemp2, "LV/%d\r", sInfo.JobItem.Lev_Damage[1]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	if(sInfo.JobItem.Lev_Attack_Rating)
	{
		strcpy_s(szTemp, sinSpecialName[16]);
		wsprintf(szTemp2, "LV/%d\r", sInfo.JobItem.Lev_Attack_Rating);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	if(sInfo.JobItem.Add_Shooting_Range)
	{
		strcpy_s(szTemp, sinSpecialName[17]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Add_Shooting_Range);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	if(sInfo.JobItem.Lev_Attack_Resistance[0])
	{
		strcpy_s(szTemp, sinSpecialName[18]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Lev_Attack_Resistance[0]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Lev_Attack_Resistance[1])
	{
		strcpy_s(szTemp, sinSpecialName[19]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Lev_Attack_Resistance[1]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Lev_Attack_Resistance[2])
	{
		strcpy_s(szTemp, sinSpecialName[20]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Lev_Attack_Resistance[2]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Lev_Attack_Resistance[3])
	{
		strcpy_s(szTemp, sinSpecialName[21]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Lev_Attack_Resistance[3]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Lev_Attack_Resistance[4])
	{
		wsprintf(szTemp, sinSpecialName[22]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Lev_Attack_Resistance[4]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	if(sInfo.JobItem.Lev_Attack_Resistance[5])
	{
		strcpy_s(szTemp, sinSpecialName[23]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Lev_Attack_Resistance[5]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;


	}
	if(sInfo.JobItem.Lev_Attack_Resistance[6])
	{
		strcpy_s(szTemp, sinSpecialName[24]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Lev_Attack_Resistance[6]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Lev_Attack_Resistance[7])
	{
		strcpy_s(szTemp, sinSpecialName[25]);
		wsprintf(szTemp2, "%d\r", sInfo.JobItem.Lev_Attack_Resistance[7]);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Lev_Life)
	{
		strcpy_s(szTemp, sinSpecialName[26]);
		wsprintf(szTemp2, "LV/%d\r", sInfo.JobItem.Lev_Life);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Lev_Mana)
	{
		strcpy_s(szTemp, sinSpecialName[27]);
		wsprintf(szTemp2, "LV/%d\r", sInfo.JobItem.Lev_Mana);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	int sinPer_Regen;
	if(sInfo.JobItem.Per_Life_Regen && (sInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		sinPer_Regen = (int)(sInfo.JobItem.Per_Life_Regen *10.001f);
		sinRightSpot = sinPer_Regen % 10;
		sinLeftSpot = (sinPer_Regen - sinRightSpot) / 10;

		strcpy_s(szTemp, sinSpecialName[28]);
		wsprintf(szTemp2, "%d.%d\r", sinLeftSpot, sinRightSpot);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}
	if(sInfo.JobItem.Per_Mana_Regen && (sInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		sinPer_Regen = (int)(sInfo.JobItem.Per_Mana_Regen *10.001f);
		sinRightSpot = sinPer_Regen % 10;
		sinLeftSpot = (sinPer_Regen - sinRightSpot) / 10;
		strcpy_s(szTemp, sinSpecialName[29]);
		wsprintf(szTemp2, "%d.%d\r", sinLeftSpot, sinRightSpot);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	if(sInfo.JobItem.Per_Stamina_Regen && (sInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		sinPer_Regen = (int)(sInfo.JobItem.Per_Stamina_Regen *10.001f);
		sinRightSpot = sinPer_Regen % 10;
		sinLeftSpot = (sinPer_Regen - sinRightSpot) / 10;
		strcpy_s(szTemp, sinSpecialName[30]);
		wsprintf(szTemp2, "%d.%d\r", sinLeftSpot, sinRightSpot);
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}

	char szTemp7[64];
	memset(szTemp7, 0, sizeof(szTemp7));
	if(cShop.OpenFlag)
	{
		strcpy_s(szTemp, "\r");
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff, szTemp);
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

		if(sInfo.Price && pItem->CODE != (sinGF1 | sin01) && pItem->CODE != (sinGF1 | sin02))
		{
			if(Flag == 2)
			{
				sinItemPrice = cInvenTory.GetInvenItemPrice(pItem);
				pItem->SellPrice = sinItemPrice.SellPrice;
				strcpy_s(szTemp, sinSpecialName[31]);

				NumLineComa(pItem->SellPrice, szTemp7);
				strcpy_s(szTemp2, szTemp7);
				lstrcat(szTemp2, "\r");

			}
			if(Flag == 1)
			{
				strcpy_s(szTemp, sinSpecialName[32]);

			#ifdef HASIEGE_MODE

				NumLineComa(cShop.haShopItemPrice(sInfo.Price), szTemp7);
			#else
				NumLineComa(sInfo.Price, szTemp7);
			#endif


				strcpy_s(szTemp2, szTemp7);
				lstrcat(szTemp2, "\r");




			}

			lstrcat(szInfoBuff, szTemp);
			lstrcat(szInfoBuff2, szTemp2);
			ItemInfoCol++;
		}

	}
	MyShopItemPriceLine = 0;
	if(cMyShop.OpenFlag || cCharShop.OpenFlag)
	{
		if(Flag == 3)
		{
			strcpy_s(szTemp, "\r");
			strcpy_s(szTemp2, "\r");
			lstrcat(szInfoBuff, szTemp);
			lstrcat(szInfoBuff2, szTemp2);
			ItemInfoCol++;

			strcpy_s(szTemp, MyShopItemSell5);
			NumLineComa(MyShopItemSellMoney2, szTemp7);
			strcpy_s(szTemp2, szTemp7);
			lstrcat(szTemp2, "    \r");


			lstrcat(szInfoBuff, szTemp);
			lstrcat(szInfoBuff2, szTemp2);
			ItemInfoCol++;
			MyShopItemPriceLine = ItemInfoCol;

		}
	}
	if(pItem->CODE == (sinGF1 | sin01))
	{
		lstrcat(szInfoBuff, "\r");
		lstrcat(szInfoBuff2, "\r");
		ItemInfoCol++;

		wsprintf(szTemp, sinGold, sInfo.Price);
		lstrcat(szTemp, "\r");
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
	}


	if(pItem->sItemInfo.SpecialItemFlag[0] == CHECK_COPY_ITEM)
	{
		lstrcat(szInfoBuff, "\r");
		lstrcat(szInfoBuff2, "\r");
		ItemInfoCol++;

		strcpy_s(szTemp, sinCopyItem5);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		RedLine[6] = ItemInfoCol;

	}

	if(pItem->sItemInfo.SpecialItemFlag[0] == CHECK_GIVE_ITEM)
	{
		lstrcat(szInfoBuff, "\r");
		lstrcat(szInfoBuff2, "\r");
		ItemInfoCol++;

		strcpy_s(szTemp, sinGiveItem5);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		RedLine[7] = ItemInfoCol;

	}

	if(cItem.GetItemLimitTime(pItem) == FALSE)
	{

		lstrcat(szInfoBuff, "\r");
		lstrcat(szInfoBuff2, "\r");
		ItemInfoCol++;

		strcpy_s(szTemp, sinItemLimitTimeOverMsg);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;
		RedLine[8] = ItemInfoCol;

	}

	if(MyShopItemIndex[Index])
	{
		if(Flag == 2)
		{
			lstrcat(szInfoBuff, "\r");
			lstrcat(szInfoBuff2, "\r");
			ItemInfoCol++;

			wsprintf(szTemp, "%s", NowMyShopSell);
			lstrcat(szInfoBuff, szTemp);
			strcpy_s(szTemp2, "\r");
			lstrcat(szInfoBuff2, szTemp2);
			ItemInfoCol++;

			RedLine[9] = ItemInfoCol;
		}
	}

	if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_CONTROL])
	{

		wsprintf(szTemp, "%d\r", pItem->sItemInfo.ItemHeader.dwChkSum);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

		wsprintf(szTemp, "%d\r", pItem->sItemInfo.ItemHeader.Head);
		lstrcat(szInfoBuff, szTemp);
		strcpy_s(szTemp2, "\r");
		lstrcat(szInfoBuff2, szTemp2);
		ItemInfoCol++;

	}


	GetInfoBoxSize(pItem, ItemInfoCol);

	sinLineCount = ItemInfoCol;

	return TRUE;

}


int cITEM::GetInfoBoxSize(sITEM *pItem, int Col)
{
	int ty, tx;

	ItemBoxSize.x = 11;
	ItemBoxSize.y = Col + 1;

	ItemBoxPosi.x = (pItem->x + (pItem->w / 2)) - ((ItemBoxSize.x * 16) / 2);
	ItemBoxPosi.y = pItem->y - (ItemBoxSize.y * 16);


	ty = ItemBoxPosi.y + (ItemBoxSize.y * 16);
	tx = ItemBoxPosi.x + (ItemBoxSize.x * 16);


	if(ItemBoxPosi.y < 0)
		ItemBoxPosi.y = 0;
	if(ItemBoxPosi.x < 0)
		ItemBoxPosi.x = 0;

	if(ty > 600)
		ItemBoxPosi.y -= (ty - 600);
	if(tx > 800)
		ItemBoxPosi.x -= (tx - 800);

	return TRUE;
}

int cITEM::DrawItemText()
{

	if(!sinShowItemInfoFlag)return FALSE;
	if(sinShowItemInfoFlag == 1)dsDrawOffsetArray = dsARRAY_TOP;
	else dsDrawOffsetArray = dsARRAY_BOTTOM;
	HDC	hdc = NULL;


	int i, Count = 0;
	int len, len2;

	int TempLen = 0;
	int TempLen2 = 0;

	int Templen = 0;
	int TemplenNum = 0;

	int ImsiLen = 0;


	int Textlen = 0;
	int Textlen2 = 0;

	int SetTextXposi = 0;
	int SetTextXposi2 = 0;


	int CutLen = 0;
	int CutLen2 = 0;

	int j = 0;
	
	char *pItemInfo[40];
	char *pItemInfo2[40];

	int  BlodCheckFlag = 0;

	//renderDevice.lpDDSBack->GetDC(&hdc);
	SelectObject(hdc, sinFont);
	SetBkMode(hdc, TRANSPARENT);

	len = lstrlen(szInfoBuff);
	len2 = lstrlen(szInfoBuff2);

	char szInfoBuffBack[5000];
	char szInfoBuff2Back[5000];
	char szAgingNum[32];

	int  TempLen3 = 0;

	strcpy_s(szInfoBuffBack, szInfoBuff);
	strcpy_s(szInfoBuff2Back, szInfoBuff2);

	for(i = 0; i < len; i++)
	{
		for(j = 0; j < len2; j++)
		{
			if(szInfoBuffBack[i] == '\r')
			{
				if(szInfoBuff2Back[j] == '\r')
				{
					pItemInfo[Count] = &szInfoBuffBack[TempLen];
					pItemInfo2[Count] = &szInfoBuff2Back[TempLen2];

					szInfoBuffBack[i] = 0;
					szInfoBuff2Back[j] = 0;

					TempLen = i + 1;
					TempLen2 = j + 1;

					Textlen = lstrlen(pItemInfo[Count]);
					Textlen2 = lstrlen(pItemInfo2[Count]);

					SetTextXposi = (ItemBoxPosi.x + (158 / 2)) - (Textlen * 6);
					SetTextXposi2 = (ItemBoxPosi.x + (158 / 2));



					SetTextXposi += 20;
					SetTextXposi2 += 17;


					if(*pItemInfo2[Count] == ' ' || Textlen2 < 1)
					{
						SetTextXposi = (ItemBoxPosi.x + (158 / 2)) - (Textlen * 3);
					}

				#ifdef _LANGUAGE_BRAZIL
					char	test[1024];
					ZeroMemory(test, sizeof(char) * 1024);
					strcat(test, pItemInfo[Count]);
					strcat(test, pItemInfo2[Count]);

					SIZE sizecheck;
					GetTextExtentPoint32(hdc, test, lstrlen(test), &sizecheck);
					SetTextXposi = ItemBoxPosi.x + (((ItemBoxSize.x * 16) - sizecheck.cx) / 2);
				#endif


					SetTextColor(hdc, RGB(255, 255, 255));

					if(Count + 1 == 1)
					{
						if(UniFlag)
							SetTextColor(hdc, RGB(128, 255, 128));
						else
						{
							SetTextColor(hdc, RGB(222, 231, 255)); // Item name
							if(sinItemKindFlag)
							{
								switch(sinItemKindFlag)
								{
									case ITEM_KIND_CRAFT:

									SetTextColor(hdc, RGB(150, 255, 255));
									break;
									case ITEM_KIND_AGING:
									SetTextColor(hdc, RGB(255, 250, 0));
									break;
									case ITEM_KIND_QUEST_WEAPON:
									SetTextColor(hdc, RGB(132, 50, 254));
									break;
									case 100:
									SetTextColor(hdc, RGB(255, 100, 29));
									break;

								}

							}

						}

						SelectObject(hdc, sinBoldFont);
						SetBkMode(hdc, TRANSPARENT);

						dsTextLineOut(hdc, SetTextXposi - 3, ItemBoxPosi.y + 27 + ((Count - 1) * 14), pItemInfo[Count], Textlen);
						BlodCheckFlag = 1;

					}
					if(AgingGageFlag)
					{
						SetTextColor(hdc, RGB(0, 0, 0));
						SelectObject(hdc, sinFont);
						SetBkMode(hdc, TRANSPARENT);
						wsprintf(szAgingNum, "+%d", AgingLevel4);
						if(AgingLevel4 < 10)
							dsTextLineOut(hdc, ItemBoxPosi.x + 72, ItemBoxPosi.y + 34, szAgingNum, lstrlen(szAgingNum));
						else
							dsTextLineOut(hdc, ItemBoxPosi.x + 69, ItemBoxPosi.y + 34, szAgingNum, lstrlen(szAgingNum));

					}
					SetTextColor(hdc, RGB(230, 230, 230)); // Poder de Ataque, Speed etc.
					for(j = 0; j < 10; j++)
					{
						if(Count + 1 == MixItemLine[j])
							SetTextColor(hdc, RGB(110, 165, 250));
						if(AgingGageFlag)
						{
							if(Count + 1 == AgingItemLine[j])
								SetTextColor(hdc, RGB(119, 200, 254));
						}
					}

					if(sinItemKindFlag == 1)
					{
						if(sinItemKindFlag == Count)
						{
							SetTextColor(hdc, RGB(227, 170, 50)); // Item mix colour
						}
					}

					if(SpecialItemLine)
					{
						if(SpecialItemLine <= Count + 2)
						{
							SetTextColor(hdc, RGB(230, 220, 0)); // Spec colour adicional

						}
						if(SpecialItemLine == Count + 2 || (SpecialItemLine + (CountSpecialName - 1)) == Count + 2)
							SetTextColor(hdc, RGB(255, 165, 0)); // Spec colour adicional ( ex: Pike, Archer, Magician )

					}
					for(j = 0; j < 10; j++)
					{
						if(Count + 1 == RequireLine[j])
							SetTextColor(hdc, RGB(255, 220, 100)); // Required status true

						if(Count + 1 == RedLine[j])
							SetTextColor(hdc, RGB(133, 133, 133)); // Required status false

					}

					if(cShop.OpenFlag)
					{
						if(Count == sinLineCount - 1)
							SetTextColor(hdc, RGB(247, 243, 193));
					}

					SelectObject(hdc, sinFont);
					SetBkMode(hdc, TRANSPARENT);

					if(Count + 1 == QuestItemLine)
					{
						SelectObject(hdc, sinBoldFont);
						SetBkMode(hdc, TRANSPARENT);
						SetTextColor(hdc, RGB(125, 180, 175));

					}

					if(Count + 1 == MyShopItemPriceLine)
					{
						SelectObject(hdc, sinFont);
						SetBkMode(hdc, TRANSPARENT);
						SetTextColor(hdc, RGB(65, 177, 255));

					}

				#ifdef	_LANGUAGE_VEITNAM
					if(!BlodCheckFlag)
					{
						dsTextLineOut(hdc, SetTextXposi - TempLen3, ItemBoxPosi.y + 28 + ((Count - 1) * 14), test, Textlen + Textlen2);
					}
				#else
				#ifdef	_LANGUAGE_THAI
					if(!BlodCheckFlag)
					{
						dsTextLineOut(hdc, SetTextXposi - TempLen3, ItemBoxPosi.y + 28 + ((Count - 1) * 14), test, Textlen + Textlen2);
					}
				#else
				#ifdef _LANGUAGE_BRAZIL
					if(!BlodCheckFlag)
					{
						dsTextLineOut(hdc, SetTextXposi - TempLen3, ItemBoxPosi.y + 28 + ((Count - 1) * 14), test, Textlen + Textlen2);
					}
				#else

				#ifdef _LANGUAGE_ARGENTINA
					if(!BlodCheckFlag)
					{
						dsTextLineOut(hdc, SetTextXposi - TempLen3, ItemBoxPosi.y + 28 + ((Count - 1) * 14), test, Textlen + Textlen2);
					}
				#else

				#ifdef	_LANGUAGE_CHINESE
					if(!BlodCheckFlag)
					{
						dsTextLineOut(hdc, SetTextXposi - TempLen3, ItemBoxPosi.y + 28 + ((Count - 1) * 14), test, Textlen + Textlen2);
					}
				#else
				#ifdef	_LANGUAGE_ENGLISH
					if(!BlodCheckFlag)
					{
						dsTextLineOut(hdc, SetTextXposi - TempLen3, ItemBoxPosi.y + 28 + ((Count - 1) * 14), test, Textlen + Textlen2);
					}
				#else
					if(!BlodCheckFlag)
					{

						dsTextLineOut(hdc, SetTextXposi - TempLen3, ItemBoxPosi.y + 28 + ((Count - 1) * 14), pItemInfo[Count], Textlen);
						dsTextLineOut(hdc, SetTextXposi2 - TempLen3, ItemBoxPosi.y + 28 + ((Count - 1) * 14), pItemInfo2[Count], Textlen2);
						dsTextLineOut(hdc, SetTextXposi2 + 1 - TempLen3, ItemBoxPosi.y + 28 + ((Count - 1) * 14), pItemInfo2[Count], Textlen2);
					}
				#endif
				#endif
				#endif
				#endif
				#endif
				#endif	
					BlodCheckFlag = 0;

					Count++;
					break;
				}
			}

		}
	}




	//renderDevice.lpDDSBack->ReleaseDC(hdc);
	return TRUE;

}


int cITEM::SearchSpecialItemJob(DWORD SpecialJob_CODE)
{


	int cnt;

	char	szTemp[64];
	char    szTemp2[64];
	CountSpecialName = 0;

	cnt = 0;
	while(1)
	{
		if(JobDataBase[cnt].JobBitCode == 0)break;
		if(JobDataBase[cnt].JobBitCode == SpecialJob_CODE)
		{
			wsprintf(szTemp, SpecialName3, JobDataBase[cnt].szName2);
			strcpy_s(szTemp2, "  \r");
			lstrcat(szInfoBuff, szTemp);
			lstrcat(szInfoBuff2, szTemp2);
			ItemInfoCol++;
			SpecialItemLine = ItemInfoCol + 1;
			CountSpecialName++;
			SpecialItemLine -= (CountSpecialName - 1);

		}
		cnt++;
	}
	return FALSE;
}

int ItemTableCheckDelayTime = 0;

int cITEM::CheckItemTable()
{
	ItemTableCheckDelayTime++;
	if(ItemTableCheckDelayTime < 70 * 10)return FALSE;
	ItemTableCheckDelayTime = 0;


	DWORD CheckSumItemDataADD = 0;

	for(int j = 0; j < INVENTORY_MAX_POS; j++)
	{
		if(sInven[j].Position)
		{
			CheckSumItemDataADD += sInven[j].Position * j;
		}
	}

	for(int i = 0; i < MAX_ITEM; i++)
	{
		if(sItem[i].CODE)
		{
			CheckSumItemDataADD += sItem[i].CODE * i;
			CheckSumItemDataADD += sItem[i].h * i;
			CheckSumItemDataADD += sItem[i].w * i;
			CheckSumItemDataADD += sItem[i].Class * i;
			CheckSumItemDataADD += sItem[i].ItemPosition * i;
		}
	}
	const DWORD CheckSumItemData = 3977515816;

	// Checksum item table here




	return TRUE;
}


int cITEM::GetItemLimitTime(sITEM *pItem)
{


	return TRUE;
}
 