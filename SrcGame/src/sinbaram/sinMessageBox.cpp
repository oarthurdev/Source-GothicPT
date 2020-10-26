

#include "sinLinkHeader.h"
#include "..\\skillsub.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\clan_Enti.h"
#include "..\\field.h"
#include "ConfirmationBox\ConfirmationBox.h"
#include "cQuestWindow.h"

#define MAX_MONEY 1000000000

#define SMASHTV_MONEY	300

sITEM MessageBoxItem;
sITEM *pMessageItem;
sITEM *pMessageItem2;

cMESSAGEBOX cMessageBox;
int MessageTimeCount = 0;

int sinMessageBoxShowFlag = 0;

int MessageArrowPosi = 0;
int MessageButtonPosi = 0;

int CountTemp = 0;

int CheckCountSize[10] = { 0,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000 };
int MoneyWeight = 10000;

int ExpressItemFlag = 0;

int sinSkillPontInitButtonFlag = 0;
int sinGiveMoneyCheckFlag = 0;
int sinGiveMoneyAmount = 0;
char szGiveMoneyBuff[32];

int sinInitPointFlag7 = 0;
int sinInitPointPassFlag = 0;


sMESSAGEBOX_RECVITEM sMessageBox_RecvItem;

LPDIRECT3DTEXTURE9 lpButtonYes07;
LPDIRECT3DTEXTURE9 lpButtonYesGlay07;
LPDIRECT3DTEXTURE9 lpButtonNo07;
LPDIRECT3DTEXTURE9 lpButtonNoGlay07;
LPDIRECT3DTEXTURE9 lpButtonBox07;


LPDIRECT3DTEXTURE9 lpStarIcon;

LPDIRECT3DTEXTURE9 lpStarShopClose_;
LPDIRECT3DTEXTURE9 lpStarShopClose;



sSTAR_SHOP sStarShop;


sLOST_ITEM sLost_Item;
int GiftPrice = 0;
int MatMyShopPRBoxLine = 0;
extern bool bcanadd;

cMESSAGEBOX::cMESSAGEBOX()
{

}
cMESSAGEBOX::~cMESSAGEBOX()
{

}

void cMESSAGEBOX::Init()
{

	MatBoxLeft = CreateTextureMaterial("Image\\SinImage\\MessageBox\\CutBox\\BoxLeft.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatBoxRight = CreateTextureMaterial("Image\\SinImage\\MessageBox\\CutBox\\BoxRight.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatBoxCenter = CreateTextureMaterial("Image\\SinImage\\MessageBox\\CutBox\\BoxCenter.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MatBoxMain = CreateTextureMaterial("Image\\SinImage\\MessageBox\\BoxMain.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);


	MatMyShopPRBoxLine = CreateTextureMaterial("game\\GUI\\Inventory\\PR_Box.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Load();
}

void cMESSAGEBOX::Load()
{

	lpButtonYes07 = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Yes_Yellow.bmp");
	lpButtonYesGlay07 = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Yes_Glay.bmp");
	lpButtonNo07 = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_No_Yellow.bmp");
	lpButtonNoGlay07 = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_No_Glay.bmp");
	lpButtonBox07 = LoadDibSurfaceOffscreen("image\\Sinimage\\Help\\box-test-title2.bmp");

	lpArrowUpDown[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\Arrow_Up.bmp");
	lpArrowUpDown[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\Arrow_Down.bmp");

	lpButtonNo[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\Button_No_Glay.bmp");
	lpButtonNo[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\Button_No_Yellow.bmp");

	lpButtonYes[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\Button_Yes_Glay.bmp");
	lpButtonYes[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\Button_Yes_Yellow.bmp");

	lpButtonOk[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\Button_Ok_Glay.bmp");
	lpButtonOk[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\Button_Ok_Yellow.bmp");

	lpButtonCancel[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\Button_Cancel_Glay.bmp");
	lpButtonCancel[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\Button_Cancel_Yellow.bmp");

	lpCount = LoadDibSurfaceOffscreen("Image\\SinImage\\MessageBox\\COUNT.bmp");


	lpStarIcon = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Star.bmp");
	lpStarShopClose = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\c.bmp");
	lpStarShopClose_ = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\c1.bmp");

}

void cMESSAGEBOX::Release()
{
	if (lpArrowUpDown[0])
	{
		lpArrowUpDown[0]->Release();
		lpArrowUpDown[0] = 0;

	}
	if (lpArrowUpDown[1])
	{
		lpArrowUpDown[1]->Release();
		lpArrowUpDown[1] = 0;

	}
	if (lpButtonNo[0])
	{
		lpButtonNo[0]->Release();
		lpButtonNo[0] = 0;

	}
	if (lpButtonNo[1])
	{
		lpButtonNo[1]->Release();
		lpButtonNo[1] = 0;

	}
	if (lpButtonYes[0])
	{
		lpButtonYes[0]->Release();
		lpButtonYes[0] = 0;

	}
	if (lpButtonYes[1])
	{
		lpButtonYes[1]->Release();
		lpButtonYes[1] = 0;
	}

	if (lpButtonOk[0])
	{
		lpButtonOk[0]->Release();
		lpButtonOk[0] = 0;
	}
	if (lpButtonOk[1])
	{
		lpButtonOk[1]->Release();
		lpButtonOk[1] = 0;
	}
	if (lpButtonCancel[0])
	{
		lpButtonCancel[0]->Release();
		lpButtonCancel[0] = 0;
	}
	if (lpButtonCancel[1])
	{
		lpButtonCancel[1]->Release();
		lpButtonCancel[1] = 0;
	}

}

void cMESSAGEBOX::Draw()
{
	int i = 0;
	int x = 0, y = 0;


	if (sLost_Item.Flag)
	{
		Interface_clanmenu.DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);

		if (sLost_Item.LostItem[0].CODE)
		{
			x = (60 - sLost_Item.LostItem[0].w) / 2;
			y = (80 - sLost_Item.LostItem[0].h) / 2;

			DrawSprite(BackStartPos.x + 20 + x, BackStartPos.y + 80 + y, sLost_Item.LostItem[0].lpItem, 0, 0, sLost_Item.LostItem[0].w, sLost_Item.LostItem[0].h);
		}
		if (sLost_Item.LostItem[1].CODE)
		{
			x = (60 - sLost_Item.LostItem[0].w) / 2;
			y = (80 - sLost_Item.LostItem[0].h) / 2;

			DrawSprite(BackStartPos.x + 20 + x + 50, BackStartPos.y + 80 + y + 22, sLost_Item.LostItem[1].lpItem, 0, 0, sLost_Item.LostItem[1].w, sLost_Item.LostItem[1].h);
		}

		DrawSprite(BackStartPos.x + BUTTON2_BOX_X + 35, BackStartPos.y + BUTTON2_BOX_Y, lpButtonBox07, 0, 0, 48, 23, 1);
		if (sLost_Item.BuyOk)
		{
			DrawSprite(BackStartPos.x + BUTTON2_X + 35, BackStartPos.y + BUTTON2_BOX_Y + 4, lpButtonOk[1], 0, 0, 32, 16, 1);
		}
		else DrawSprite(BackStartPos.x + BUTTON2_X + 35, BackStartPos.y + BUTTON2_BOX_Y + 4, lpButtonOk[0], 0, 0, 32, 16, 1);

	}

	if (sStarShop.Flag)
	{
		Interface_clanmenu.DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);

		DrawSprite(BackStartPos.x + 60, BackStartPos.y + 60, lpStarIcon, 0, 0, 32, 32, 1);
		DrawSprite(BackStartPos.x + BUTTON2_BOX_X + 35, BackStartPos.y + BUTTON2_BOX_Y, lpButtonBox07, 0, 0, 48, 23, 1);
		if (sStarShop.ButtonClose)
			DrawSprite(BackStartPos.x + BUTTON2_X + 35, BackStartPos.y + BUTTON2_Y, lpStarShopClose_, 0, 0, 32, 16, 1);
		else DrawSprite(BackStartPos.x + BUTTON2_X + 35, BackStartPos.y + BUTTON2_Y, lpStarShopClose, 0, 0, 32, 16, 1);

		DrawSprite(BackStartPos.x + BUTTON2_BOX_X + 35, BackStartPos.y + 160, lpButtonBox07, 0, 0, 48, 23, 1);
		if (sStarShop.BuyOk)
		{
			DrawSprite(BackStartPos.x + BUTTON2_X + 35, BackStartPos.y + 163, lpButtonYes07, 0, 0, 32, 16, 1);
		}
		else DrawSprite(BackStartPos.x + BUTTON2_X + 35, BackStartPos.y + 163, lpButtonYesGlay07, 0, 0, 32, 16, 1);
	}



	if (sMessageBox_RecvItem.Flag)
	{
		Interface_clanmenu.DrawBox(BackStartPos.x, BackStartPos.y, 4, 5);
		DrawSprite(BackStartPos.x + BUTTON2_BOX_X, BackStartPos.y + BUTTON2_BOX_Y, lpButtonBox07, 0, 0, 48, 23, 1);
		DrawSprite(BackStartPos.x + BUTTON3_BOX_X, BackStartPos.y + BUTTON3_BOX_Y, lpButtonBox07, 0, 0, 48, 23, 1);

		if (sMessageBox_RecvItem.ButtonYes)
			DrawSprite(BackStartPos.x + BUTTON2_X, BackStartPos.y + BUTTON2_Y, lpButtonYes07, 0, 0, 32, 16, 1);
		else DrawSprite(BackStartPos.x + BUTTON2_X, BackStartPos.y + BUTTON2_Y, lpButtonYesGlay07, 0, 0, 32, 16, 1);
		if (sMessageBox_RecvItem.ButtonNo)
			DrawSprite(BackStartPos.x + BUTTON3_X, BackStartPos.y + BUTTON3_Y, lpButtonNo07, 0, 0, 32, 16, 1);
		else DrawSprite(BackStartPos.x + BUTTON3_X, BackStartPos.y + BUTTON3_Y, lpButtonNoGlay07, 0, 0, 32, 16, 1);

		if (sMessageBox_RecvItem.RecvItem.CODE)
		{
			x = (60 - sMessageBox_RecvItem.RecvItem.w) / 2;
			y = (80 - sMessageBox_RecvItem.RecvItem.h) / 2;

			DrawSprite(BackStartPos.x + 20 + x, BackStartPos.y + 80 + y, sMessageBox_RecvItem.RecvItem.lpItem, 0, 0, sMessageBox_RecvItem.RecvItem.w, sMessageBox_RecvItem.RecvItem.h);
		}
	}
	for (i = 0; i < MESSAGE3_MAX; i++)
	{
		if (sMessageBox3[i].Flag)
		{
			dsDrawTexImage(MatBoxMain, sMessageBox3[i].x, sMessageBox3[i].y, 256, 128, 255);
			DrawSprite(sMessageBox3[i].x + 40, sMessageBox3[i].y + 95, lpButtonOk[0], 0, 0, 32, 16);
			DrawSprite(sMessageBox3[i].x + 94, sMessageBox3[i].y + 95, lpButtonCancel[0], 0, 0, 32, 16);

			if (MessageButtonPosi == 1)
				DrawSprite(sMessageBox3[i].x + 40, sMessageBox3[i].y + 95, lpButtonOk[1], 0, 0, 32, 16);
			if (MessageButtonPosi == 2)
				DrawSprite(sMessageBox3[i].x + 94, sMessageBox3[i].y + 95, lpButtonCancel[1], 0, 0, 32, 16);
		}
	}

	for (i = 0; i < 20; i++)
	{
		if (sMessageBox2[i].Flag)
		{
			dsDrawTexImage(MatBoxMain, sMessageBox2[i].x, sMessageBox2[i].y, 290, 128, 255);
			DrawSprite(sMessageBox2[i].x + 34, sMessageBox2[i].y + 64, lpCount, 0, 0, 109, 25);
			if (i != MESSAGE_BUY_STAR)
			{
				DrawSprite(sMessageBox2[i].x + 40, sMessageBox2[i].y + 95, lpButtonOk[0], 0, 0, 32, 16);
				DrawSprite(sMessageBox2[i].x + 94, sMessageBox2[i].y + 95, lpButtonCancel[0], 0, 0, 32, 16);
				if (MessageButtonPosi == 1)
					DrawSprite(sMessageBox2[i].x + 40, sMessageBox2[i].y + 95, lpButtonOk[1], 0, 0, 32, 16);
				if (MessageButtonPosi == 2)
					DrawSprite(sMessageBox2[i].x + 94, sMessageBox2[i].y + 95, lpButtonCancel[1], 0, 0, 32, 16);
			}
			if (MessageArrowPosi == 1)
				DrawSprite(sMessageBox2[i].x + 124, sMessageBox2[i].y + 62, lpArrowUpDown[0], 0, 0, 19, 13);
			if (MessageArrowPosi == 2)
				DrawSprite(sMessageBox2[i].x + 124, sMessageBox2[i].y + 75, lpArrowUpDown[1], 0, 0, 19, 13);

			if (i == MESSAGE_BUY_STAR)
			{
				DrawSprite(sMessageBox2[i].x + 40, sMessageBox2[i].y + 95, lpButtonYes[0], 0, 0, 32, 16);
				DrawSprite(sMessageBox2[i].x + 94, sMessageBox2[i].y + 95, lpButtonNo[0], 0, 0, 32, 16);
				if (MessageButtonPosi == 1)
					DrawSprite(sMessageBox2[i].x + 40, sMessageBox2[i].y + 95, lpButtonYes[1], 0, 0, 32, 16);
				if (MessageButtonPosi == 2)
					DrawSprite(sMessageBox2[i].x + 94, sMessageBox2[i].y + 95, lpButtonNo[1], 0, 0, 32, 16);
			}
		}
	}

	for (i = 0; i < 100; i++)
	{
		if (sMessageBox[i].Flag)
		{
			dsDrawTexImage(MatBoxLeft, sMessageBox[i].x, sMessageBox[i].y, 32, 64, 255);
			int j = 0;
			for (j = 0; j < sMessageBox[i].Line; j++)
			{
				dsDrawTexImage(MatBoxCenter, sMessageBox[i].x + 32 + (j * 16), sMessageBox[i].y, 16, 64, 255);
			}
			dsDrawTexImage(MatBoxRight, sMessageBox[i].x + 32 + (j * 16), sMessageBox[i].y, 32, 64, 255);

		}
	}
}

void cMESSAGEBOX::Main()
{

	MessageArrowPosi = 0;
	MessageButtonPosi = 0;

	int i = 0;
	for (i = 0; i < 100; i++)
	{
		if (sMessageBox[i].Flag)
		{
			MessageTimeCount++;
			if (i == MESSAGE_MOVE_TRADE_ITEM)
			{
				if (MessageTimeCount > 70 * 5)
				{
					sMessageBox[i].Flag = 0;
					MessageTimeCount = 0;
				}
			}
			else
			{

				if (i == MESSAGE_SCORE)
				{
					if (MessageTimeCount > 70 * 6)
					{
						sMessageBox[i].Flag = 0;
						MessageTimeCount = 0;
					}

				}
				else
				{
					if (MessageTimeCount > 70 * 3)
					{
						sMessageBox[i].Flag = 0;
						MessageTimeCount = 0;
					}
				}
			}
		}
	}

	if (sLost_Item.Flag)
	{
		BackStartPos.x = 101;
		BackStartPos.y = 114;
		sLost_Item.BuyOk = 0;
		if (pCursorPos.x > BackStartPos.x + BUTTON2_X + 35 && pCursorPos.x < BackStartPos.x + BUTTON2_X + 35 + 32 &&
			pCursorPos.y >BackStartPos.y + BUTTON2_BOX_Y && pCursorPos.y < BackStartPos.y + BUTTON2_BOX_Y + 16)
			sLost_Item.BuyOk = 1;

	}


	if (sStarShop.Flag)
	{
		BackStartPos.x = 101;
		BackStartPos.y = 114;
		sStarShop.ButtonClose = 0;
		if (!sinMessageBoxShowFlag)
		{
			if (pCursorPos.x > BackStartPos.x + BUTTON2_X + 35 && pCursorPos.x < BackStartPos.x + BUTTON2_X + 35 + 32 &&
				pCursorPos.y >BackStartPos.y + BUTTON2_Y && pCursorPos.y < BackStartPos.y + BUTTON2_Y + 16)
				sStarShop.ButtonClose = 1;

			sStarShop.BuyOk = 0;
			if (pCursorPos.x > BackStartPos.x + BUTTON2_X + 35 && pCursorPos.x < BackStartPos.x + BUTTON2_X + 35 + 32 &&
				pCursorPos.y >BackStartPos.y + 160 && pCursorPos.y < BackStartPos.y + 160 + 16)
				sStarShop.BuyOk = 1;
		}
	}


	if (sMessageBox_RecvItem.Flag)
	{
		BackStartPos.x = 101;
		BackStartPos.y = 114;
		sMessageBox_RecvItem.ButtonYes = 0;
		sMessageBox_RecvItem.ButtonNo = 0;
		if (pCursorPos.x > BackStartPos.x + BUTTON2_X && pCursorPos.x < BackStartPos.x + BUTTON2_X + 32 &&
			pCursorPos.y >BackStartPos.y + BUTTON2_Y && pCursorPos.y < BackStartPos.y + BUTTON2_Y + 16)
			sMessageBox_RecvItem.ButtonYes = 1;

		if (pCursorPos.x > BackStartPos.x + BUTTON3_X && pCursorPos.x < BackStartPos.x + BUTTON3_X + 32 &&
			pCursorPos.y >BackStartPos.y + BUTTON3_Y && pCursorPos.y < BackStartPos.y + BUTTON3_Y + 16)
			sMessageBox_RecvItem.ButtonNo = 1;
	}

	for (i = 0; i < 20; i++)
	{
		if (sMessageBox2[i].Flag)
		{
			if (pCursorPos.x > sMessageBox2[i].x + 124 && pCursorPos.x < sMessageBox2[i].x + 124 + 19 &&
				pCursorPos.y >sMessageBox2[i].y + 62 && pCursorPos.y < sMessageBox2[i].y + 62 + 13)
				MessageArrowPosi = 1;

			if (pCursorPos.x > sMessageBox2[i].x + 124 && pCursorPos.x < sMessageBox2[i].x + 124 + 19 &&
				pCursorPos.y >sMessageBox2[i].y + 75 && pCursorPos.y < sMessageBox2[i].y + 75 + 13)
				MessageArrowPosi = 2;

			if (pCursorPos.x > sMessageBox2[i].x + 40 && pCursorPos.x < sMessageBox2[i].x + 40 + 32 &&
				pCursorPos.y >sMessageBox2[i].y + 95 && pCursorPos.y < sMessageBox2[i].y + 98 + 16)
				MessageButtonPosi = 1;

			if (pCursorPos.x > sMessageBox2[i].x + 94 && pCursorPos.x < sMessageBox2[i].x + 94 + 32 &&
				pCursorPos.y >sMessageBox2[i].y + 95 && pCursorPos.y < sMessageBox2[i].y + 95 + 16)
				MessageButtonPosi = 2;
		}

	}
	for (i = 0; i < MESSAGE3_MAX; i++)
	{
		if (sMessageBox3[i].Flag)
		{
			if (pCursorPos.x > sMessageBox3[i].x + 40 && pCursorPos.x < sMessageBox3[i].x + 40 + 32 &&
				pCursorPos.y >sMessageBox3[i].y + 95 && pCursorPos.y < sMessageBox3[i].y + 98 + 16)
				MessageButtonPosi = 1;

			if (pCursorPos.x > sMessageBox3[i].x + 94 && pCursorPos.x < sMessageBox3[i].x + 94 + 32 &&
				pCursorPos.y >sMessageBox3[i].y + 95 && pCursorPos.y < sMessageBox3[i].y + 95 + 16)
				MessageButtonPosi = 2;
		}

	}


	if (sinGiveMoneyCheckFlag)
	{
		sinGiveMoneyCheckFlag = 0;
		cMessageBox.ShowMessage3(MESSAGE_GIVE_MONEY_CHECK, szGiveMoneyBuff);

	}

}

void cMESSAGEBOX::Close()
{
	Release();
}

void cMESSAGEBOX::LButtonDown(int x, int y)
{

	int i = 0;

	if (sLost_Item.Flag)
	{
		if (sLost_Item.BuyOk)
		{
			memset(&sLost_Item, 0, sizeof(sLOST_ITEM));
			isDrawClanMenu = 0;
			OverDay_Item_Flag = 0;
		}
	}


	if (sStarShop.Flag)
	{
		if (sStarShop.ButtonClose)
		{
			sStarShop.Flag = 0;
			isDrawClanMenu = 0;
		}
		if (sStarShop.BuyOk)
		{
			sStarShop.BuyOk = 0;


			cMessageBox.ShowMessage2(MESSAGE_BUY_STAR);

		}

	}


	if (sMessageBox_RecvItem.Flag)
	{
		if (sMessageBox_RecvItem.ButtonYes)
		{
			if (cInvenTory.CheckInvenEmpty(&sMessageBox_RecvItem.RecvItem))
			{
				if (sMessageBox_RecvItem.Param[0])
				{
					cMessageBox.ShowMessage3(MESSAGE_SECRET_NUM, SecretNumName);
					isDrawClanMenu = 0;
				}
				else
				{
					if (sMessageBox_RecvItem.RecvItem.CODE == (sinGG1 | sin01))
					{
						if (!cInvenTory.CheckMoneyLimit(sMessageBox_RecvItem.RecvItem.SellPrice))
						{
							cMessageBox.ShowMessage(MESSAGE_OVER_MONEY);
							isDrawClanMenu = 0;
							sMessageBox_RecvItem.Flag = 0;
						}
						else
						{
							SendItemExpress(sMessageBox_RecvItem.RecvItem.CODE);
							isDrawClanMenu = 0;
							sMessageBox_RecvItem.Flag = 0;
						}
					}
					else
					{
						SendItemExpress(sMessageBox_RecvItem.RecvItem.CODE);
						isDrawClanMenu = 0;
						sMessageBox_RecvItem.Flag = 0;
					}

				}
			}
			else
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
				isDrawClanMenu = 0;
				sMessageBox_RecvItem.Flag = 0;
			}

		}
		if (sMessageBox_RecvItem.ButtonNo)
		{
			sMessageBox_RecvItem.Flag = 0;
			isDrawClanMenu = 0;
		}
	}


	for (i = 0; i < MESSAGE3_MAX; i++)
	{
		if (sMessageBox3[i].Flag)
		{
			if (MessageButtonPosi == 1)
			{
				CheckOkMessageBox2(i);

			}
			if (MessageButtonPosi == 2)
			{
				if (i == MESSAGE_QUEST_100LVITEMOK)
				{
					chaQuest.sHaQuest100LV.State--;
					chaQuest.showFuryQuestItem(1);
				}
				if (i == MESSAGE_CHANGE_JOB4_2)
				{
					if (sinChar->JOB_CODE <= 4 || sinChar->JOB_CODE == 9)
						WarpField2(START_FIELD_NUM);
					else
						WarpField2(START_FIELD_MORYON);
				}
				if (i == MESSAGE_SELL_HIGHRANK_ITEM)
				{
					MouseItem.Flag = 1;
					ResetInvenItemCode();
					cInvenTory.AutoSetInvenItem(&MouseItem);

				}

				if (i == MESSAGE_EVENT_GYUNGFUM)
				{
					if (sinChar->wVersion[1] == 1)
					{
						sinSkillPontInitButtonFlag = 0;
					}
					else sinSkillPontInitButtonFlag = 1;

				}

				if (i == MESSAGE_WARP)
				{
					WingWarpGate_Field(-1);

				}
				if (i == MESSAGE_SECRET_NUM)
				{
					hFocusWnd = 0;
					cInterFace.ChatFlag = 0;
					SetWindowText(hFocusWnd, "");
					sinChatEnter = 0;
				}

				if (i == MESSAGE_QUEST_100LVITEMOK)
				{
					chaQuest.iFuryQuestIndex[1] = 0;
				}

				if (i == MESSAGE_CONFIRMATION_BOX)
					_ConfirmationBox.CheckFlag(false);

				sinMessageBoxShowFlag = 0;
				sMessageBox3[i].Flag = 0;
				ShowSkillUpInfo = 0;
				sinInitPointFlag7 = 0;
			}
		}
	}

	for (i = 0; i < 20; i++)
	{
		if (sMessageBox2[i].Flag)
		{
			if (MessageArrowPosi == 1)
			{
				if (i != MESSAGE_BUY_ITEM_DEFALT)
					sMessageBox2[i].Count++;
				if (i == 3 || i == MESSAGE_MOVE_MONEY_TRADE || i == MESSAGE_MOVE_MONEY_MOVE || i == MESSAGE_GIVE_MONEY)
				{
					if (sinChar->Money < sMessageBox2[i].Count)
					{
						sMessageBox2[i].Count = sinChar->Money;
					}
				}

				if (i == MESSAGE_MOVE_COIN_TRADE)
				{
					if (Shop::GetInstance()->GetCoin() < sMessageBox2[i].Count)
					{
						sMessageBox2[i].Count = Shop::GetInstance()->GetCoin();
					}
				}

				if (i == MESSAGE_SOD2_GET_MONEY)
				{
					if (cInvenTory.CheckMoneyLimit(sMessageBox2[i].Count))
					{
						if (sMessageBox2[i].Count > (int)cSinSod2.ClanMoney)
						{
							sMessageBox2[i].Count = (int)cSinSod2.ClanMoney;
						}
					}
					else
						sMessageBox2[i].Count /= 10;
				}
				if (i == MESSAGE_SIEGE_SET_MERCENRAY)
				{







					if ((sinChar->Money - (haMercenrayMoney[haMercenrayIndex - 1])*sMessageBox2[i].Count) < 0)
					{

						sMessageBox2[i].Count -= 1;
						cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
						break;
					}
					if (cSinSiege.MercenaryNum[haMercenrayIndex - 1] + sMessageBox2[i].Count > 20)
					{
						sMessageBox2[i].Count -= 1;
						ShowMessage(MESSAGE_MERCENRAY_OVER);
						break;
					}
					if (sinChar->Money <= sMessageBox2[i].Count*(int)1)
					{
						sMessageBox2[i].Count -= 1;
						ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);

					}

				}
				if (i == MESSAGE_MYSHOP_POTION || i == MESSAGE_SIEGE_GET_MONEY)
				{

					if (sinChar->Money <= sMessageBox2[i].Count*(int)MyShopPotion.ItemHeader.dwVersion)
					{
						sMessageBox2[i].Count = sinChar->Money / (int)MyShopPotion.ItemHeader.dwVersion;
					}

					if (sinChar->Weight[0] + sMessageBox2[i].Count > sinChar->Weight[1])
					{
						sMessageBox2[i].Count = sinChar->Weight[1] - sinChar->Weight[0];

					}

					if ((int)MyShopPotion.PotionCount < sMessageBox2[i].Count)
					{
						sMessageBox2[i].Count = (int)MyShopPotion.PotionCount;

					}

				}

				if (i == MESSAGE_BUY_STAR)
				{




					sMessageBox2[i].Count = 0;
				}

				if (i == MESSAGE_MOVE_MONEY_MOVE)
				{
					if (sinChar->Money < sMessageBox2[i].Count)
					{
						sMessageBox2[i].Count = sinChar->Money;
					}

					if ((sWareHouse.Money - 2023) + sMessageBox2[i].Count > MAX_MONEY)
					{
						sMessageBox2[i].Count -= ((sWareHouse.Money - 2023) + sMessageBox2[i].Count) - MAX_MONEY;
					}

				}

				if (i == MESSAGE_MOVE_MONEY_RECV)
				{
					if (sWareHouse.Money - 2023 < sMessageBox2[i].Count)
						sMessageBox2[i].Count = sWareHouse.Money - 2023;
					if (sinChar->Level <= 10)
					{
						if (sinChar->Money + sMessageBox2[i].Count > 200000)
						{
							sMessageBox2[i].Count = 200000 - sinChar->Money;
							if (sMessageBox2[i].Count < 0) sMessageBox2[i].Count = 0;

						}
					}
					else
					{
						switch (sinChar->ChangeJob)
						{
						case 0:
							if ((sinChar->Money + sMessageBox2[i].Count) > (sinChar->Level * 200000) - 1800000)
							{
								sMessageBox2[i].Count = (sinChar->Level * 200000) - 1800000 - sinChar->Money;
								if (sMessageBox2[i].Count < 0) sMessageBox2[i].Count = 0;

							}
							break;

						case 1:
							if ((sinChar->Money + sMessageBox2[i].Count) > 10000000)
							{
								sMessageBox2[i].Count = 10000000 - sinChar->Money;
								if (sMessageBox2[i].Count < 0) sMessageBox2[i].Count = 0;
							}
							break;
						case 2:
							if ((sinChar->Money + sMessageBox2[i].Count) > 50000000)
							{
								sMessageBox2[i].Count = 50000000 - sinChar->Money;
								if (sMessageBox2[i].Count < 0) sMessageBox2[i].Count = 0;
							}
							break;

						case 3:
							if ((sinChar->Money + sMessageBox2[i].Count) > MAX_MONEY)
							{
								sMessageBox2[i].Count = MAX_MONEY - sinChar->Money;
								if (sMessageBox2[i].Count < 0) sMessageBox2[i].Count = 0;
							}


							break;


						}
					}

				}

				if (i == MESSAGE_EVENT_SMASHTV)
				{
					if (sinChar->Money < sMessageBox2[i].Count)
					{
						sMessageBox2[i].Count = sinChar->Money;
						if (sMessageBox2[i].Count < (sinChar->Level * SMASHTV_MONEY))
						{
							ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
							CloseMessage();


						}
					}
					if (sMessageBox2[i].Count > (sinChar->Level * SMASHTV_MONEY))
					{
						sMessageBox2[i].Count = (sinChar->Level * SMASHTV_MONEY);
					}
				}

				if (i == 2 || i == 1)
				{
					if (pMessageItem->sItemInfo.PotionCount < sMessageBox2[i].Count)
					{
						sMessageBox2[i].Count = pMessageItem->sItemInfo.PotionCount;
					}
				}
				if (i == 0)
				{
					CountTemp = sMessageBox2[i].Count*pMessageItem->sItemInfo.Price;
					if (CountTemp > sinChar->Money)
					{
						ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
						for (int k = 0; k < CountTemp; k++)
						{
							if ((CountTemp - k) <= sinChar->Money)
							{
								sMessageBox2[i].Count = (CountTemp - k) / pMessageItem->sItemInfo.Price;
								break;
							}

						}

					}
					CountTemp = (sMessageBox2[i].Count*pMessageItem->sItemInfo.Weight) + sinChar->Weight[0];
					if (sinChar->Weight[1] < CountTemp)
					{
						ShowMessage(MESSAGE_OVER_WEIGHT);
						for (int p = 0; p < CountTemp; p++)
						{
							if ((CountTemp - p) <= sinChar->Weight[1])
							{
								sMessageBox2[i].Count -= p;
								break;
							}
						}
					}
				}
			}
			if (MessageArrowPosi == 2)
			{
				if (i != MESSAGE_BUY_ITEM_DEFALT)
				{
					sMessageBox2[i].Count--;
					if (sMessageBox2[i].Count < 0)
					{
						sMessageBox2[i].Count = 0;
					}
				}
			}
			if (MessageButtonPosi == 1)
			{
				CheckOkMessageBox(i);
			}
			if (MessageButtonPosi == 2)
			{
				sinMessageBoxShowFlag = 0;
				sMessageBox2[i].Flag = 0;
				cSinSod2.ClanMasterMessageBoxFlag = 0;
				if (i == MESSAGE_MOVE_MONEY_TRADE)
					sTrade.Money = 0;
				if (i == MESSAGE_MOVE_COIN_TRADE)
					sTrade.Coin = 0;


			}
		}
	}
}

void cMESSAGEBOX::LButtonUp(int x, int y)
{


	if (sinSkillPontInitButtonFlag)
	{
		sinSkillPontInitButtonFlag = 0;
		cMessageBox.ShowMessage3(MESSAGE_INIT_SKILL_POINT, sinSkillPointName);
	}

}

void cMESSAGEBOX::RButtonDown(int x, int y)
{

}

void cMESSAGEBOX::RButtonUp(int x, int y)
{

}

void cMESSAGEBOX::KeyDown()
{
	int i = 0;

	char szKeyBuffPad[10] = { VK_NUMPAD0,VK_NUMPAD1,VK_NUMPAD2,VK_NUMPAD3,VK_NUMPAD4,
		VK_NUMPAD5,VK_NUMPAD6,VK_NUMPAD7,VK_NUMPAD8,VK_NUMPAD9 };
	char szKeyBuff[10] = { '0','1','2','3','4','5','6','7','8','9' };

	for (i = 0; i < 20; i++)
	{
		if (sMessageBox2[i].Flag)
		{
			for (int j = 0; j < 10; j++)
			{
				if (sinGetKeyClick(szKeyBuff[j]) || sinGetKeyClick(szKeyBuffPad[j]))
				{
					if (i == 3 || i == MESSAGE_MOVE_MONEY_TRADE || i == MESSAGE_MOVE_MONEY_MOVE || i == MESSAGE_GIVE_MONEY)
					{
						sMessageBox2[i].szCount[sMessageBox2[i].Line] = szKeyBuff[j];
						sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);
						if (sinChar->Money < sMessageBox2[i].Count)
						{
							sMessageBox2[i].Count = sinChar->Money;
						}
					}

					if (i == MESSAGE_MOVE_COIN_TRADE)
					{
						sMessageBox2[i].szCount[sMessageBox2[i].Line] = szKeyBuff[j];
						sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);

						if (Shop::GetInstance()->GetCoin() < sMessageBox2[i].Count)
						{
							sMessageBox2[i].Count = Shop::GetInstance()->GetCoin();
						}
					}

					if (i == MESSAGE_SIEGE_GET_MONEY)
					{
						sMessageBox2[i].szCount[sMessageBox2[i].Line] = szKeyBuff[j];
						sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);

						if ((int)cSinSiege.TotalTax <= 0)
						{
							cMessageBox.ShowMessage(MESSAGE_NOT_CASTLE_TOTALMONEY);
							break;
						}
						if (cInvenTory.CheckMoneyLimit(sMessageBox2[i].Count))
						{
							if (sMessageBox2[i].Count > (int)cSinSiege.TotalTax)
							{
								sMessageBox2[i].Count = (int)cSinSiege.TotalTax;
							}
						}
						else

							sMessageBox2[i].Count /= 10;

					}



					if (i == MESSAGE_SOD2_GET_MONEY)
					{
						sMessageBox2[i].szCount[sMessageBox2[i].Line] = szKeyBuff[j];
						sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);
						if (cInvenTory.CheckMoneyLimit(sMessageBox2[i].Count))
						{
							if (sMessageBox2[i].Count > (int)cSinSod2.ClanMoney)
							{
								sMessageBox2[i].Count = (int)cSinSod2.ClanMoney;
							}
						}
						else
							sMessageBox2[i].Count /= 10;
					}

					if (i == MESSAGE_MYSHOP_POTION)
					{
						sMessageBox2[i].szCount[sMessageBox2[i].Line] = szKeyBuff[j];
						sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);


						if (sinChar->Money <= sMessageBox2[i].Count*(int)MyShopPotion.ItemHeader.dwVersion)
						{
							sMessageBox2[i].Count = sinChar->Money / (int)MyShopPotion.ItemHeader.dwVersion;
						}

						if (sinChar->Weight[0] + sMessageBox2[i].Count > sinChar->Weight[1])
						{
							sMessageBox2[i].Count = sinChar->Weight[1] - sinChar->Weight[0];

						}

						if ((int)MyShopPotion.PotionCount < sMessageBox2[i].Count)
						{
							sMessageBox2[i].Count = (int)MyShopPotion.PotionCount;

						}


					}

					if (i == MESSAGE_BUY_STAR)
					{




						sMessageBox2[i].Count = 0;
					}

					if (i == MESSAGE_MOVE_MONEY_MOVE)
					{
						if (sinChar->Money < sMessageBox2[i].Count)
						{
							sMessageBox2[i].Count = sinChar->Money;
						}

						if ((sWareHouse.Money - 2023) + sMessageBox2[i].Count > MAX_MONEY)
						{
							sMessageBox2[i].Count -= ((sWareHouse.Money - 2023) + sMessageBox2[i].Count) - MAX_MONEY;
						}

					}

					if (i == MESSAGE_MYSHOP_ITEM)
					{
						sMessageBox2[i].szCount[sMessageBox2[i].Line] = szKeyBuff[j];
						sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);

						if (MyShopMouseItem.Class == ITEM_CLASS_POTION)
						{
							if (!cInvenTory.CheckMoneyLimit(cMyShop.GetTotalMyShopItemMoney() + (sMessageBox2[i].Count*MyShopMouseItem.sItemInfo.PotionCount)))
							{
								while (1)
								{
									sMessageBox2[i].Count /= 10;
									if (cInvenTory.CheckMoneyLimit(cMyShop.GetTotalMyShopItemMoney() + (sMessageBox2[i].Count*MyShopMouseItem.sItemInfo.PotionCount)))
									{
										ShowMessage(MESSAGE_OVER_MONEY);
										break;
									}
									if (sMessageBox2[i].Count <= 0)
									{
										sMessageBox2[i].Count = 0;
										ShowMessage(MESSAGE_OVER_MONEY);
										break;
									}
								}
							}
						}
						else
						{
							if (!cInvenTory.CheckMoneyLimit(cMyShop.GetTotalMyShopItemMoney() + sMessageBox2[i].Count))
							{
								while (1)
								{
									sMessageBox2[i].Count /= 10;
									if (cInvenTory.CheckMoneyLimit(cMyShop.GetTotalMyShopItemMoney() + sMessageBox2[i].Count))
									{
										ShowMessage(MESSAGE_OVER_MONEY);
										break;
									}
									if (sMessageBox2[i].Count <= 0)
									{
										sMessageBox2[i].Count = 0;
										ShowMessage(MESSAGE_OVER_MONEY);
										break;
									}
								}
							}

						}
					}


					if (i == MESSAGE_MOVE_MONEY_RECV)
					{
						sMessageBox2[i].szCount[sMessageBox2[i].Line] = szKeyBuff[j];
						sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);
						if (sWareHouse.Money - 2023 < sMessageBox2[i].Count)
							sMessageBox2[i].Count = sWareHouse.Money - 2023;
						if (sinChar->Level <= 10)
						{
							if (sinChar->Money + sMessageBox2[i].Count > 200000)
							{
								sMessageBox2[i].Count = 200000 - sinChar->Money;
								if (sMessageBox2[i].Count < 0) sMessageBox2[i].Count = 0;

							}
						}
						else
						{
							switch (sinChar->ChangeJob)
							{
							case 0:
								if ((sinChar->Money + sMessageBox2[i].Count) > (sinChar->Level * 200000) - 1800000)
								{
									sMessageBox2[i].Count = (sinChar->Level * 200000) - 1800000 - sinChar->Money;
									if (sMessageBox2[i].Count < 0) sMessageBox2[i].Count = 0;

								}
								break;
							case 1:
								if ((sinChar->Money + sMessageBox2[i].Count) > 10000000)
								{
									sMessageBox2[i].Count = 10000000 - sinChar->Money;
									if (sMessageBox2[i].Count < 0) sMessageBox2[i].Count = 0;
								}
								break;
							case 2:
								if ((sinChar->Money + sMessageBox2[i].Count) > 50000000)
								{
									sMessageBox2[i].Count = 50000000 - sinChar->Money;
									if (sMessageBox2[i].Count < 0) sMessageBox2[i].Count = 0;
								}
								break;

							case 3:
								if ((sinChar->Money + sMessageBox2[i].Count) > MAX_MONEY)
								{
									sMessageBox2[i].Count = MAX_MONEY - sinChar->Money;
									if (sMessageBox2[i].Count < 0) sMessageBox2[i].Count = 0;
								}
								break;

							}

						}

					}

					if (i == MESSAGE_EVENT_SMASHTV)
					{
						sMessageBox2[i].szCount[sMessageBox2[i].Line] = szKeyBuff[j];
						sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);
						if (sinChar->Money < sMessageBox2[i].Count)
						{
							sMessageBox2[i].Count = sinChar->Money;
							if (sMessageBox2[i].Count < (sinChar->Level * SMASHTV_MONEY))
							{
								ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
								CloseMessage();
							}
						}
						if (sMessageBox2[i].Count > (sinChar->Level * SMASHTV_MONEY))
						{
							sMessageBox2[i].Count = (sinChar->Level * SMASHTV_MONEY);

						}

					}

					if (i == 2 || i == 1)
					{
						sMessageBox2[i].szCount[sMessageBox2[i].Line] = szKeyBuff[j];
						sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);
						if (pMessageItem && sMessageBox2[i].Count >= pMessageItem->sItemInfo.PotionCount)
							sMessageBox2[i].Count = pMessageItem->sItemInfo.PotionCount;
					}
					if (i == 0)
					{
						sMessageBox2[i].szCount[sMessageBox2[i].Line] = szKeyBuff[j];
						sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);
						CountTemp = sMessageBox2[i].Count*pMessageItem->sItemInfo.Price;
						if (CountTemp > sinChar->Money)
						{
							for (int k = 0; k < CountTemp; k++)
							{
								if ((CountTemp - k) <= sinChar->Money)
								{
									sMessageBox2[i].Count = (CountTemp - k) / pMessageItem->sItemInfo.Price;
									break;
								}
							}
						}

						CountTemp = (sMessageBox2[i].Count*pMessageItem->sItemInfo.Weight) + sinChar->Weight[0];
						if (sinChar->Weight[1] < CountTemp)
						{
							for (int p = 0; p < CountTemp; p++)
							{
								if ((CountTemp - p) <= sinChar->Weight[1])
								{
									sMessageBox2[i].Count -= p;
									break;
								}
							}
						}
					}
				}
			}
			if (sinGetKeyClick(VK_BACK))
			{
				if (i != MESSAGE_BUY_ITEM_DEFALT)
				{
					if (sMessageBox2[i].Count <= 0)break;
					sMessageBox2[i].szCount[sMessageBox2[i].Line - 1] = 0;
					sMessageBox2[i].Count = atoi(sMessageBox2[i].szCount);
				}
			}
			if (sinGetKeyClick(VK_RETURN))
			{
				CheckOkMessageBox(i);
			}
		}

	}
	if (sinGetKeyClick(VK_ESCAPE))
	{
		for (int i = 0; i < 20; i++)
		{
			if (sMessageBox2[i].Flag)
			{
				sMessageBox2[i].Flag = 0;
				sinMessageBoxShowFlag = 0;

			}

		}
		cSinSod2.ClanMasterMessageBoxFlag = 0;




	}

	for (i = 0; i < MESSAGE3_MAX; i++)
	{
		if (sMessageBox3[i].Flag)
		{
			if (sinGetKeyClick(VK_RETURN))
			{
				CheckOkMessageBox2(i);

			}

		}
	}
}

int cMESSAGEBOX::ShowMessageEvent(char *Msg)
{
	for (int i = 0; i < 49; i++)
	{
		if (sMessageBox[i].Flag)
			sMessageBox[i].Flag = 0;
	}

	sMessageBox[49].Flag = 1;
	strcpy_s(sMessageBox[49].MessageDoc, Msg);
	sMessageBox[49].len = lstrlen(Msg);
	sMessageBox[49].x = smScreenWidth / 2 - ((sMessageBox[49].len * 10) / 2) + 40;
	sMessageBox[49].y = 5;
	sMessageBox[49].Line = (sMessageBox[49].len * 10 / 16) - 6;
#ifdef _LANGUAGE_ENGLISH
	sMessageBox[49].Line = (sMessageBox[49].len * 10 / 16) - 3;
#endif
#ifdef _LANGUAGE_JAPANESE
	sMessageBox[49].Line = (sMessageBox[49].len * 10 / 16) - 4;
#endif
	return TRUE;
}

int cMESSAGEBOX::ShowMessage(int Kind)
{
	for (int i = 0; i < 100; i++)
	{
		if (sMessageBox[i].Flag)
			sMessageBox[i].Flag = 0;
	}
	sMessageBox[Kind].Flag = 1;
	if (Kind == MESSAGE_100LVITEM_OK)
	{

		strcpy_s(sMessageBox[Kind].MessageDoc2, ha100LVQuestItemName[chaQuest.iFuryQuestIndex[1] - 1]);
		lstrcat(sMessageBox[Kind].MessageDoc2, sMessageBox[Kind].MessageDoc);
		sMessageBox[Kind].len = lstrlen(sMessageBox[Kind].MessageDoc2);
	}
	else
		sMessageBox[Kind].len = lstrlen(sMessageBox[Kind].MessageDoc);
	if (Kind == MESSAGE_MOVE_TRADE_ITEM || Kind == MESSAGE_NOTEXIT_ITEMIMAGE)
	{
		sMessageBox[Kind].x = smScreenWidth / 2 - ((sMessageBox[Kind].len * 10) / 2) + 40;
		sMessageBox[Kind].y = smScreenHeight / 2 - (64 / 2);
		sMessageBox[Kind].Line = (sMessageBox[Kind].len * 10 / 16) - 3;

	}
	else
	{
		sMessageBox[Kind].x = smScreenWidth / 2 - ((sMessageBox[Kind].len * 10) / 2) + 40;
		sMessageBox[Kind].y = 5;
		sMessageBox[Kind].Line = (sMessageBox[Kind].len * 10 / 16) - 3;
	}

	return TRUE;
}

int cMESSAGEBOX::ShowMessage(const char * message)
{
	for (int i = 0; i < 49; i++)
	{
		if (sMessageBox[i].Flag)
			sMessageBox[i].Flag = 0;
	}

	sMessageBox[49].Flag = 1;
	strcpy_s(sMessageBox[49].MessageDoc, message);
	sMessageBox[49].len = lstrlen(message);
	sMessageBox[49].x = smScreenWidth / 2 - ((sMessageBox[49].len * 10) / 2) + 40;
	sMessageBox[49].y = 5;
	sMessageBox[49].Line = (sMessageBox[49].len * 10 / 16) - 3;

	return TRUE;
}

int cMESSAGEBOX::ShowMessage1(const char* message)
{
	for (int i = 0; i < 49; i++)
	{
		if (sMessageBox[i].Flag)
			sMessageBox[i].Flag = 0;
	}

	sMessageBox[49].Flag = 1;
	strcpy_s(sMessageBox[49].MessageDoc, message);
	sMessageBox[49].len = lstrlen(message);
	sMessageBox[49].x = smScreenWidth / 2 - ((sMessageBox[49].len * 10) / 2);
	sMessageBox[49].y = 5;
	sMessageBox[49].Line = (sMessageBox[49].len * 7 / 16) - 3;

	return TRUE;
}

int cMESSAGEBOX::ShowMessage2(int Kind)
{

	for (int i = 0; i < 20; i++)
	{
		if (sMessageBox2[i].Flag)
			sMessageBox2[i].Flag = 0;
	}


	sMessageBox2[Kind].Flag = 1;
	memset(sMessageBox2[Kind].szCount, 0, sizeof(sMessageBox2[Kind].szCount));
	if (Kind == MESSAGE_BUY_ITEM_DEFALT)
		sMessageBox2[Kind].Count = 1;
	else if (Kind == 1)
		sMessageBox2[Kind].Count = pMessageItem->sItemInfo.PotionCount;

	else
		sMessageBox2[Kind].Count = 0;

	if (MESSAGE_MYSHOP_ITEM == Kind)
	{
		if (MyShopMouseItem.Class == ITEM_CLASS_POTION)
		{
			strcpy_s(sMessageBox2[Kind].MessageDoc1, PotionCntDoc2);
		}
		else
		{
			strcpy_s(sMessageBox2[Kind].MessageDoc1, ItemPrice7);

		}
	}

	sMessageBox2[Kind].x = 300;
	sMessageBox2[Kind].y = 200;
	sMessageBox2[Kind].Line = 1;
	sinMessageBoxShowFlag = 1;
	hFocusWnd = 0;


	if (Kind == MESSAGE_MOVE_MONEY_TRADE)
	{
		if (sTrade.Money)
		{
			if (!CheckTrade((void *)&sTrade))
				cTrade.CancelTradeItem();
			CheckCharForm();
			TempShowMoney = 0;

			sinPlusMoney(sTrade.Money - 193);
			sTrade.Money = 0;
			ReformCharForm();
			SendSaveMoney();
			ReformTrade((void *)&sTrade);
			SendTradeItem(cTrade.TradeCharCode);
		}
	}

	if (Kind == MESSAGE_MOVE_COIN_TRADE)
	{
		if (sTrade.Coin)
		{
			if (!CheckTrade((void *)&sTrade))
				cTrade.CancelTradeItem();
			CheckCharForm();
			TempShowCoin = 0;
			Shop::GetInstance()->PlusCoin(sTrade.Coin);
			sTrade.Coin = 0;
			ReformCharForm();
			ReformTrade((void *)&sTrade);
			SendTradeItem(cTrade.TradeCharCode);
		}
	}

	return TRUE;
}


int cMESSAGEBOX::ShowMessage3(int Kind, char *Doc)
{
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		if (sMessageBox2[i].Flag)
			sMessageBox2[i].Flag = 0;
	}
	for (i = 0; i < MESSAGE3_MAX; i++)
	{
		if (sMessageBox3[i].Flag)
			sMessageBox3[i].Flag = 0;
	}
	sMessageBox3[Kind].Flag = 1;
	sMessageBox3[Kind].x = 300;
	sMessageBox3[Kind].y = 200;
	sinMessageBoxShowFlag = 1;
	strcpy_s(sMessageBox3[Kind].RecvMessage, sizeof(sMessageBox3[Kind].RecvMessage), Doc);


	if (Kind == MESSAGE_TRADE_BPEXP)
		lstrcpy(sMessageBox3[Kind].MessageDoc1, "Deseja confirmar a troca?");

	if (Kind == MESSAGE_FALLGAME)
	{
		sMessageBox3[Kind].x += 120;
		sMessageBox3[Kind].y += 100;
	}
	if (Kind == MESSAGE_INIT_SKILL_POINT)
	{
		sMessageBox3[Kind].x += 10;

	}
	if (Kind == MESSAGE_EVENT_GYUNGFUM)
	{
		sMessageBox3[Kind].x += 10;

		sinInitPointFlag7 = 1;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_INITPOINT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x - 3, QuestMessageBoxSize2.y - 1, D3DCOLOR_RGBA(0, 15, 128, 125), WarningInitPoint[0]);
	}
	if (Kind == MESSAGE_SECRET_NUM)
	{
		hFocusWnd = hTextWnd;
		SetWindowText(hFocusWnd, "");
		cInterFace.ChatFlag = 0;

	}

	if (Kind == MESSAGE_TELEPORT_DUNGEON)
	{
		sMessageBox3[Kind].x += 120;
		sMessageBox3[Kind].y += 100;
	}

	if (Kind == MESSAGE_CONFIRMATION_BOX)
	{
		strcpy_s(sMessageBox3[Kind].MessageDoc1, _ConfirmationBox.GetDoc1());
		strcpy_s(sMessageBox3[Kind].MessageDoc2, _ConfirmationBox.GetDoc2());
	}




	return TRUE;
}


int cMESSAGEBOX::CloseMessage()
{
	for (int i = 0; i < 20; i++)
	{
		if (sMessageBox2[i].Flag)
		{
			sMessageBox2[i].Flag = 0;
			memset(sMessageBox2[i].szCount, 0, sizeof(sMessageBox2[i].szCount));
			sMessageBox2[i].Count = 0;
		}
	}
	sinMessageBoxShowFlag = 0;


	return TRUE;
}


void cMESSAGEBOX::DrawMessageText()
{


	HDC	hdc = NULL;
	int TempFlag = 0;
	char szTemp2[256];
	for (int i = 0; i < 100; i++)
	{
		if (sMessageBox[i].Flag)
		{
			TempFlag = 1;
		}
	}


	int len = 0;
	int XPosi = 0;
	char szBuffDoc[128];
	char szBuffDoc2[128];
	int Yposi = 0;
	int PassNum = 0;





	char HoldStarNum[32];

	if (sStarShop.Flag)
	{

		SetFontTextColor(RGB(222, 231, 255));
		dsTextLineOut(BackStartPos.x + 48, BackStartPos.y + 35, HoldStarNumDoc, lstrlen(HoldStarNumDoc));

		wsprintf(HoldStarNum, "%s", "x");
		dsTextLineOut(BackStartPos.x + 120, BackStartPos.y + 75, HoldStarNum, lstrlen(HoldStarNum));

		wsprintf(HoldStarNum, "%d", sStarShop.Count);
		dsTextLineOut(BackStartPos.x + 160, BackStartPos.y + 75, HoldStarNum, lstrlen(HoldStarNum));

		dsTextLineOut(BackStartPos.x + 83, BackStartPos.y + 140, StarItemBuy7, lstrlen(StarItemBuy7));

		SetFontTextColor(RGB(222, 231, 25));
		dsTextLineOut(BackStartPos.x + 53, BackStartPos.y + 120, ChangeMoney7, lstrlen(ChangeMoney7));


	}

	char szTempBuff5[128];
	if (sLost_Item.Flag)
	{

		SetFontTextColor(RGB(128, 255, 128));
		if (OverDay_Item_Flag)
		{
			wsprintf(szTempBuff5, "%s %s", sLost_Item.szDoc, ItemName87);
			dsTextLineOut(BackStartPos.x + 110, BackStartPos.y + 90, szTempBuff5, lstrlen(szTempBuff5));

		}
		else
		{
			dsTextLineOut(BackStartPos.x + 110, BackStartPos.y + 90, Quset3ItemDoc15, lstrlen(Quset3ItemDoc15));

		}


		//SelectObject(hdc, sinMessageFont);

		SetFontTextColor(RGB(255, 255, 255));
		dsTextLineOut(BackStartPos.x + 110, BackStartPos.y + 120, Quset3ItemDoc16, lstrlen(Quset3ItemDoc16));


	}

	if (sMessageBox_RecvItem.Flag)
	{

		//SelectObject(hdc, sinBoldFont);

		SetFontTextColor(RGB(222, 231, 255));
		memset(szBuffDoc, 0, sizeof(szBuffDoc));
		memset(szBuffDoc2, 0, sizeof(szBuffDoc2));

		len = lstrlen(sMessageBox_RecvItem.szDoc);
		if ((len * 7) > 256)
		{
			if ((BYTE)sMessageBox_RecvItem.szDoc[256 / 7] & 0x80)
				PassNum = 0;
			else
				PassNum = 1;

			memcpy(szBuffDoc, sMessageBox_RecvItem.szDoc, (256 / 7) + PassNum);
			strcpy_s(szBuffDoc2, &sMessageBox_RecvItem.szDoc[(256 / 7) + PassNum]);
			dsTextLineOut(BackStartPos.x + 10, BackStartPos.y + 25, szBuffDoc, lstrlen(szBuffDoc));
			dsTextLineOut(BackStartPos.x + 10, BackStartPos.y + 40, szBuffDoc2, lstrlen(szBuffDoc2));
		}
		else
		{
			XPosi = ((256 - (len * 6)) / 2);
			if (XPosi < 10)XPosi = 10;
			dsTextLineOut(BackStartPos.x + XPosi, BackStartPos.y + 30, sMessageBox_RecvItem.szDoc, lstrlen(sMessageBox_RecvItem.szDoc));
		}



		if (sMessageBox_RecvItem.RecvItem.SellPrice)
		{

			//SelectObject(hdc, sinMessageFont);

			SetFontTextColor(RGB(128, 255, 128));
			wsprintf(szBuffDoc, "%d", sMessageBox_RecvItem.RecvItem.SellPrice);
			dsTextLineOut(BackStartPos.x + 120, BackStartPos.y + 90, szBuffDoc, lstrlen(szBuffDoc));



			//SelectObject(hdc, sinMessageFont);

			SetFontTextColor(RGB(255, 255, 255));
			dsTextLineOut(BackStartPos.x + 130, BackStartPos.y + 120, Money5, lstrlen(Money5));



		}

		else if (sMessageBox_RecvItem.RecvItem.OldX)
		{

			//SelectObject(hdc, sinMessageFont);

			SetFontTextColor(RGB(128, 255, 128));
			wsprintf(szBuffDoc, "%d", sMessageBox_RecvItem.RecvItem.OldX);
			dsTextLineOut(BackStartPos.x + 120, BackStartPos.y + 90, szBuffDoc, lstrlen(szBuffDoc));



			//SelectObject(hdc, sinMessageFont);

			SetFontTextColor(RGB(255, 255, 255));
			dsTextLineOut(BackStartPos.x + 120, BackStartPos.y + 120, Exp5, lstrlen(Exp5));


		}

		else if (sMessageBox_RecvItem.RecvItem.PotionCount)
		{

			//SelectObject(hdc, sinMessageFont);

			SetFontTextColor(RGB(128, 255, 128));
			wsprintf(szBuffDoc, "%d", sMessageBox_RecvItem.RecvItem.PotionCount);
			dsTextLineOut(BackStartPos.x + 120, BackStartPos.y + 90, szBuffDoc, lstrlen(szBuffDoc));



			//SelectObject(hdc, sinMessageFont);

			SetFontTextColor(RGB(255, 255, 255));
			dsTextLineOut(BackStartPos.x + 120, BackStartPos.y + 120, RecvPotion7, lstrlen(RecvPotion7));



		}

		else
		{

			//SelectObject(hdc, sinMessageFont);

			SetFontTextColor(RGB(128, 255, 128));
			dsTextLineOut(BackStartPos.x + 110, BackStartPos.y + 90, sMessageBox_RecvItem.szItem, lstrlen(sMessageBox_RecvItem.szItem));



			//SelectObject(hdc, sinMessageFont);

			SetFontTextColor(RGB(255, 255, 255));
			dsTextLineOut(BackStartPos.x + 120, BackStartPos.y + 120, Itemul, lstrlen(Itemul));

		}


		//SelectObject(hdc, sinMessageFont);

		SetFontTextColor(RGB(255, 255, 255));
		dsTextLineOut(BackStartPos.x + 110, BackStartPos.y + 140, ItemRecvOk, lstrlen(ItemRecvOk));


	}

	if (sinMessageBoxShowFlag || TempFlag)
	{


		int i = 0;
		int TempLenght = 0;

		SetFontTextColor(RGB(255, 255, 255));
		char szBuff5[128];
		memset(szBuff5, 0, sizeof(szBuff5));


		for (i = 0; i < 100; i++)
		{
			if (sMessageBox[i].Flag)
			{
				if (i == MESSAGE_100LVITEM_OK)
				{

					dsTextLineOut(sMessageBox[i].x + 43, sMessageBox[i].y + 17, sMessageBox[i].MessageDoc2, sMessageBox[i].len);
				}
				else
					dsTextLineOut(sMessageBox[i].x + 43, sMessageBox[i].y + 17, sMessageBox[i].MessageDoc, sMessageBox[i].len);
			}
		}

		char szBuff[128];
		char szBuff15[128];
		int len2 = 0;
		memset(szBuff, 0, sizeof(szBuff));
		memset(szBuff15, 0, sizeof(szBuff15));

		for (i = 0; i < 20; i++)
		{
			if (sMessageBox2[i].Flag)
			{
				dsTextLineOut(sMessageBox2[i].x + 45, sMessageBox2[i].y + 15, sMessageBox2[i].MessageDoc1, lstrlen(sMessageBox2[i].MessageDoc1));
				dsTextLineOut(sMessageBox2[i].x + 45, sMessageBox2[i].y + 40, sMessageBox2[i].MessageDoc2, lstrlen(sMessageBox2[i].MessageDoc2));
				wsprintf(sMessageBox2[i].szCount, "%d", sMessageBox2[i].Count);
				NumLineComa(sMessageBox2[i].Count, szBuff5);
				for (int t = 0; t < 10; t++)
				{
					if (CheckCountSize[t] > sMessageBox2[i].Count)
					{
						sMessageBox2[i].Line = t;
						break;
					}
				}
				if (i == MESSAGE_MYSHOP_POTION)
				{
					NumLineComa(sMyShop_Server.Price*sMessageBox2[i].Count, szBuff);
					len2 = lstrlen(szBuff);

					sMessageBox2[i].TextSetX = (int)(((sMessageBox2[i].x + 60)) - (((sMessageBox2[i].Line) * 6.5) / 2));

					wsprintf(szBuff15, "%s %s", BuyPotionKind, szBuff5);
					len2 = lstrlen(szBuff15);
					dsTextLineOut(sMessageBox2[i].TextSetX - (len2), sMessageBox2[i].y + 58, szBuff15, lstrlen(szBuff15));

					wsprintf(szBuff15, "%s %d", BuyPotionMoney, sMyShop_Server.Price*sMessageBox2[i].Count);
					len2 = lstrlen(szBuff15);
					dsTextLineOut(sMessageBox2[i].TextSetX - (len2), sMessageBox2[i].y + 72, szBuff15, lstrlen(szBuff15));




				}
				else
				{
					len2 = lstrlen(szBuff5);
					sMessageBox2[i].TextSetX = (int)((sMessageBox2[i].x + 85 - (len2)) - (((sMessageBox2[i].Line) * 6.5) / 2));

					dsTextLineOut(sMessageBox2[i].TextSetX, sMessageBox2[i].y + 72, szBuff5, lstrlen(szBuff5));
				}
			}
		}
		for (i = 0; i < MESSAGE3_MAX; i++)
		{
			if (sMessageBox3[i].Flag)
			{
				TempLenght = (int)((172 - (lstrlen(sMessageBox3[i].RecvMessage)*5.5)) / 2 - 5);
				//SelectObject(hdc, sinBoldFont);

				SetFontTextColor(RGB(222, 231, 255));
				dsTextLineOut(sMessageBox3[i].x + TempLenght, sMessageBox3[i].y + 20, sMessageBox3[i].RecvMessage, lstrlen(sMessageBox3[i].RecvMessage));
				//SelectObject(hdc, sinFont);

				SetFontTextColor(RGB(255, 255, 255));
				TempLenght = (int)((172 - (lstrlen(sMessageBox3[i].MessageDoc1)*5.5)) / 2 - 5);
				dsTextLineOut(sMessageBox3[i].x + TempLenght, sMessageBox3[i].y + 35 + 8, sMessageBox3[i].MessageDoc1, lstrlen(sMessageBox3[i].MessageDoc1));
				if (i == MESSAGE_EVENT_SMASHTV)
				{
					wsprintf(szTemp2, "%d%s", sinChar->Level*SMASHTV_MONEY, sMessageBox3[i].MessageDoc2);
					dsTextLineOut(sMessageBox3[i].x + 48, sMessageBox3[i].y + 55 + 5, szTemp2, lstrlen(szTemp2));
				}
				else if (i == MESSAGE_SECRET_NUM)
				{
					sinChatEnter = 0;
					cInterFace.ChatFlag = 0;
					hFocusWnd = hTextWnd;
					GetWindowText(hFocusWnd, sMessageBox3[i].MessageDoc2, 15);
					dsTextLineOut(sMessageBox3[i].x + 48, sMessageBox3[i].y + 55 + 5, sMessageBox3[i].MessageDoc2, lstrlen(sMessageBox3[i].MessageDoc2));

				}
				else
				{
					TempLenght = (int)((172 - (lstrlen(sMessageBox3[i].MessageDoc2)*5.5)) / 2 - 5);
					dsTextLineOut(sMessageBox3[i].x + TempLenght + 2, sMessageBox3[i].y + 55 + 5, sMessageBox3[i].MessageDoc2, lstrlen(sMessageBox3[i].MessageDoc2));
				}
			}
		}

	}

}
int sinTeleportIndexArray[4] = { 0,18,7,12 };

int cMESSAGEBOX::CheckOkMessageBox2(int Kind)
{

	int Temp = 0;
	int TempTalent = 0;
	sITEM TempItem;

	switch (Kind)
	{
	case MESSAGE_MASTER_SKILL:
		if (pMasterSkill)
		{

#ifdef HASIEGE_MODE

			if (cShop.haBuyMoneyCheck(sinMasterSkill_Money[pMasterSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pMasterSkill->Skill_Info.SkillNum] * (pMasterSkill->Point))))
			{
#else
			if (0 <= (sinChar->Money - (sinMasterSkill_Money[pMasterSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pMasterSkill->Skill_Info.SkillNum] * (pMasterSkill->Point)))))
			{
#endif

				CheckCharForm();


				SendPaymentMoneyToServer((sinMasterSkill_Money[pMasterSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pMasterSkill->Skill_Info.SkillNum] * (pMasterSkill->Point))) +
					((sinMasterSkill_Money[pMasterSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pMasterSkill->Skill_Info.SkillNum] * (pMasterSkill->Point)))*cSinSiege.GetTaxRate()) / 100, 1);


				sinMinusMoney(sinMasterSkill_Money[pMasterSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pMasterSkill->Skill_Info.SkillNum] * (pMasterSkill->Point)), 1);
				cSkill.CheckSkillPointForm(pMasterSkill);
				pMasterSkill->Point++;
				cSkill.ReformSkillPointForm(pMasterSkill);


				if (Skill4ButtonIndex > 13)
				{
					sinSkill.SkillPoint4--;
				}

				if (Skill4ButtonIndex <= 13)
				{
					sinSkill.SkillPoint--;
				}

				ReformCharForm();
				SendSaveMoney();
				sinPlaySound(SIN_SOUND_COIN);
				switch (pMasterSkill->CODE)
				{
				case SKILL_POISON_ATTRIBUTE:
					pUseSkill = pMasterSkill;
					pUseSkill->Skill_Info.FuncPointer();
					break;
				case SKILL_MELEE_MASTERY:
					pUseSkill = pMasterSkill;
					pUseSkill->Skill_Info.FuncPointer();
					break;
				case SKILL_FIRE_ATTRIBUTE:
					pUseSkill = pMasterSkill;
					pUseSkill->Skill_Info.FuncPointer();
					break;
				case SKILL_ICE_ATTRIBUTE:
					pUseSkill = pMasterSkill;
					pUseSkill->Skill_Info.FuncPointer();
					break;
				case SKILL_SHOOTING_MASTERY:
					pUseSkill = pMasterSkill;
					pUseSkill->Skill_Info.FuncPointer();
					break;
				case SKILL_MAXIMIZE:
					pUseSkill = pMasterSkill;
					pUseSkill->Skill_Info.FuncPointer();
					break;
				case SKILL_WEAPONE_DEFENCE_MASTERY:
					pUseSkill = pMasterSkill;
					pUseSkill->Skill_Info.FuncPointer();
					break;
				case SKILL_DIONS_EYE:
					pUseSkill = pMasterSkill;
					pUseSkill->Skill_Info.FuncPointer();
					break;
				case SKILL_PHYSICAL_TRANING:
					cInvenTory.SetItemToChar();
					break;
				case SKILL_FIRE_JAVELIN:
					cInvenTory.SetItemToChar();
					break;
				case SKILL_MEDITATION:
					cInvenTory.SetItemToChar();
					break;
				case SKILL_MENTAL_MASTERY:
					cInvenTory.SetItemToChar();
					break;
				case SKILL_THROWING_MASTERY:
					cInvenTory.SetItemToChar();
					break;
				case SKILL_MECHANIC_WEAPON:
					cInvenTory.SetItemToChar();
					break;
				case SKILL_CRITICAL_MASTERY:
					cInvenTory.SetItemToChar();
					break;
				case SKILL_SWORD_MASTERY:
					cInvenTory.SetItemToChar();
					break;
				case SKILL_BOOST_HEALTH:
					cInvenTory.SetItemToChar();
					break;
				case SKILL_EVASION_MASTERY:
					cInvenTory.SetItemToChar();
					break;

				};
				cInvenTory.CheckDamage();
				LearnSkillEffect(0);
				TempTalent = (int)(sinChar->Talent / 3);
				if (TempTalent > 50)TempTalent = 50;
				Temp = 10000 - (TempTalent * 100);

				if (Temp >= pMasterSkill->UseSkillCount)
					pMasterSkill->UseSkillCount /= 2;
				else
					pMasterSkill->UseSkillCount = Temp / 2;
				SaveGameData();

			}
			else
				ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);

		}

		break;
	case MESSAGE_CHANGE_JOB:
		if (sinQuest_ChangeJob3.CODE)
		{
			TempItem.CODE = (sinOR2 | sin02);
			if (!cInvenTory.CheckInvenEmpty(&TempItem))
			{
				ShowMessage(MESSAGE_OVER_SPACE);
				break;
			}

		}

		sinChar->ChangeJob++;
		cSkill.OpenFlag = 1;
		cInterFace.CheckAllBox(SIN_SKILL);
		SkillMasterFlag = 1;

		if (sinQuest_ChangeJob.CODE)
		{
			DeleteQuestItem((sinQT1 | sin01));
			DeleteQuestItem((sinQT1 | sin02));
			DeleteQuestItem((sinQT1 | sin03));

			sinQuest_ChangeJob.State = SIN_QUEST_COMPLETE;
			sinJobList = GetJobDataCode(sinChar->JOB_CODE, sinChar->ChangeJob);
			strcpy_s(cInvenTory.JobName, sinJobList->szName2);

			sinQuest_ChangeJob.BackUpCode = sinQuest_ChangeJob.CODE;
			sinQuest_ChangeJob.CODE = 0;
			sinChar->wVersion[1] = 0;
			EndQuest_Code(sinQuest_ChangeJob.BackUpCode);

			cInvenTory.ReFormInvenItem();
			sinSkillPontInitButtonFlag = 1;
		}
		if (FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_M) || FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_D))
		{
			sinJobList = GetJobDataCode(sinChar->JOB_CODE, sinChar->ChangeJob);
			strcpy_s(cInvenTory.JobName, sinJobList->szName2);
			sinSkillPontInitButtonFlag = 1;

			sinQuest_ChangeJob2.CODE = 0;

		}
		if (sinQuest_ChangeJob3.CODE)
		{

			sinJobList = GetJobDataCode(sinChar->JOB_CODE, sinChar->ChangeJob);
			strcpy_s(cInvenTory.JobName, sinJobList->szName2);
			sinSkillPontInitButtonFlag = 1;




			sinQuest_ChangeJob3.State = 5;
			StartQuest_Code(sinQuest_ChangeJob3.CODE);
		}


		SaveGameData();
		ChangeJobFace();
		break;
	case MESSAGE_QUEST:
		sinQuest_ChangeJob.CODE = SIN_QUEST_CODE_CHANGEJOB;
		sinQuest_ChangeJob.State = SIN_QUEST_PROGRESS;
		SaveGameData();
		StartQuest_Code(sinQuest_ChangeJob.CODE);
		break;
	case MESSAGE_QUEST_CHANGEJOB_MORAYOIN:
		sinQuest_ChangeJob2.State = SIN_QUEST_PROGRESS;


		SaveGameData();
		StartQuest_Code(sinQuest_ChangeJob2.CODE);
		switch (sinQuest_ChangeJob2.Kind)
		{
		case 1:
			sinQuest_ChangeJob2.CODE = SIN_QUEST_CODE_CHANGEJOB2_NPC_M;
			break;
		case 2:
			sinQuest_ChangeJob2.CODE = SIN_QUEST_CODE_CHANGEJOB2_NPC_D;
			break;
		}
		SaveGameData();
		StartQuest_Code(sinQuest_ChangeJob2.CODE);

		cInvenTory.ClearQuestItem();
		break;
	case MESSAGE_QUEST_CHANGEJOB3:
		sinQuest_ChangeJob3.CODE = SIN_QUEST_CODE_CHANGEJOB3;
		sinQuest_ChangeJob3.State = 1;
		SaveGameData();
		StartQuest_Code(sinQuest_ChangeJob3.CODE);
		break;

	case MESSAGE_INIT_SKILL_POINT:
		cSkill.InitSkillPoint();
		break;
	case MESSAGE_EVENT_GYUNGFUM:
		cCharStatus.InitCharStatus();
		cInvenTory.SetItemToChar();
		if (sinChar->Life[1] < sinGetLife())
		{
			sinSetLife(sinChar->Life[1]);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		sinInitPointFlag7 = 0;


		break;

	case MESSAGE_EVENT_SMASHTV:
		if (sinChar->Money < (sinChar->Level * SMASHTV_MONEY))
		{
			CloseMessage();
			ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
			break;

		}
		CheckCharForm();

		sinMinusMoney((sinChar->Level * SMASHTV_MONEY));
		ReformCharForm();
		SendCollectMoney((sinChar->Level * SMASHTV_MONEY));
		sinPlaySound(SIN_SOUND_COIN);



		break;
	case MESSAGE_POSTBOX:





		break;
	case MESSAGE_LINKCORE:

		cInvenTory.UnionCoreParticle2(UnionCorePosi.x, UnionCorePosi.y);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
		SendLinkCoreToServer(&TempLinkCoreItem);

		break;
	case MESSAGE_RECVITEM:
		SendWingQuestItem();
		sinbaram_Stop = 1;


		break;

	case MESSAGE_WARP:
		if (sSinWarpGate.GateUseIndex > 2 && sSinWarpGate.MoveFieldNum > 1 && !sSinWarpGate.SameAreaFlag)
		{
			CheckCharForm();

			SendPaymentMoneyToServer(WarpGateUseCost[sSinWarpGate.GateUseIndex - 4] + ((WarpGateUseCost[sSinWarpGate.GateUseIndex - 4] * cSinSiege.GetTaxRate()) / 100), 2);
			sinMinusMoney(WarpGateUseCost[sSinWarpGate.GateUseIndex - 4], 1);
			ReformCharForm();
		}
		if (sHaWarpGate.GateUseIndex > 0 && sHaWarpGate.MoveFieldNum > 0 && !sSinWarpGate.SameAreaFlag)
		{
			CheckCharForm();

			SendPaymentMoneyToServer(WarpGateUseCost[sSinWarpGate.GateUseIndex - 4] + ((WarpGateUseCost[sSinWarpGate.GateUseIndex - 4] * cSinSiege.GetTaxRate()) / 100), 2);
			sinMinusMoney(WarpGateUseCost[sSinWarpGate.GateUseIndex - 4], 1);
			ReformCharForm();
			WingWarpGate_Field(haWarpGateCODE[sHaWarpGate.MoveFieldNum - 1]);
		}
		else
			WingWarpGate_Field(sinWarpGateCODE[sSinWarpGate.MoveFieldNum]);

		SendSaveMoney();

		break;
	case MESSAGE_SECRET_NUM:
		SendItemExpress(sMessageBox_RecvItem.RecvItem.CODE, sMessageBox3[Kind].MessageDoc2);
		isDrawClanMenu = 0;
		sMessageBox_RecvItem.Flag = 0;
		hFocusWnd = hTextWnd;
		SetWindowText(hFocusWnd, "");
		cInterFace.ChatFlag = 0;
		break;
	case MESSAGE_GIFT_TICKET:

		SendStarPointToServer(GiftPrice, 0);
		DeleteGiftItem();
		StarShopNPC();
		break;
	case MESSAGE_SELL_HIGHRANK_ITEM:
		MouseItem.Flag = 1;
		ResetInvenItemCode();
		cShop.SellItemToShop(&MouseItem);

		break;
	case MESSAGE_GIVE_MONEY_CHECK:
		CheckCharForm();
		sinMinusMoney2(sinGiveMoneyAmount);
		ReformCharForm();

		SendGiveMoneyToServer(sinGiveMoneyAmount);
		sinPlaySound(SIN_SOUND_COIN);
		sinGiveMoneyAmount = 0;

		break;
	case MESSAGE_PUZZLE_SEND:
		if (cInvenTory.CheckSendPuzzle())
		{
			SendWingQuestItem();
		}
		break;
	case MESSAGE_MYSHOP_ITEM_BUY:
		if (cCharShop.OpenFlag)
		{
			Send_PersonalShopItem(sRecvMyShop.CHAR_CODE, &sMyShop_Server);
		}
		break;
	case MESSAGE_MYSHOP_ITEM_CANCEL:
		MyShopItemIndex[MyShopItemCancelIndex[0] - 1] = 0;
		cMyShop.MyShopItem[MyShopItemCancelIndex[1] - 1].Flag = 0;
		memset(&cMyShop.MyShopItem[MyShopItemCancelIndex[1] - 1], 0, sizeof(sITEM));
		break;
	case MESSAGE_EVENTITEM_SEND:
		if (cInvenTory.SendEventItem())
		{
			SendWingQuestItem();
		}
		break;
	case MESSAGE_FOXEVENTITEM_SEND:
		if (cInvenTory.SendFoxEventItem())
		{
			SendWingQuestItem();
		}
	case MESSAGE_QUEST_LEVEL30:
		sinQuest_Level30.CODE = SIN_QUEST_CODE_LEVEL30;
		sinQuest_Level30.State = 1;
		sinQuest_Level30.Monster[1] = 20;
		SaveGameData();
		StartQuest_Code(sinQuest_Level30.CODE);
		break;
	case MESSAGE_QUEST_LEVEL55:
		sinQuest_Level55.CODE = SIN_QUEST_CODE_LEVEL55;
		sinQuest_Level55.State = 1;
		sinQuest_Level55.Monster[1] = 20;
		SaveGameData();
		StartQuest_Code(sinQuest_Level55.CODE);
		break;
	case MESSAGE_QUEST_LEVEL55_2:
		sinQuest_Level55_2.CODE = SIN_QUEST_CODE_LEVEL55_2;
		sinQuest_Level55_2.State = 1;
		sinQuest_Level55_2.Monster[1] = 20;
		SaveGameData();
		StartQuest_Code(sinQuest_Level55_2.CODE);
		break;

	case MESSAGE_QUEST_LEVEL70:
		sinQuest_Level70.CODE = SIN_QUEST_CODE_LEVEL70;
		sinQuest_Level70.State = 1;
		sinQuest_Level70.Monster[1] = 10;
		SaveGameData();
		StartQuest_Code(sinQuest_Level70.CODE);

		break;
	case MESSAGE_QUEST_LEVEL80:
		sinQuest_Level80.CODE = SIN_QUEST_CODE_LEVEL80;
		sinQuest_Level80.State = 1;
		sinQuest_Level80.Monster[1] = 5;
		SaveGameData();
		StartQuest_Code(sinQuest_Level80.CODE);

		break;
	case MESSAGE_QUEST_LEVEL85:
		sinQuest_Level85.CODE = SIN_QUEST_CODE_LEVEL85;
		sinQuest_Level85.State = 2;
		sinQuest_Level85.Monster[1] = 10;
		SaveGameData();
		StartQuest_Code(sinQuest_Level85.CODE);
		if (!cInvenTory.SearchItemCode(sinQT1 | sin08))
		{
			SendQuestCommandToServer(SIN_QUEST_CODE_LEVEL85, 0, 0, 0);
		}

		break;
	case MESSAGE_QUEST_LEVEL90:
		sinQuest_Level90.CODE = SIN_QUEST_CODE_LEVEL90;
		sinQuest_Level90.State = 1;
		sinQuest_Level90.Monster[1] = 10;
		SaveGameData();
		StartQuest_Code(sinQuest_Level90.CODE);
		break;
	case MESSAGE_QUEST_LEVEL80_2:
		sinQuest_Level80_2.CODE = SIN_QUEST_CODE_LEVEL80_2;
		sinQuest_Level80_2.State = 1;
		SaveGameData();
		StartQuest_Code(sinQuest_Level80_2.CODE);
		break;
	case MESSAGE_QUEST_LEVEL90_2:
		sinQuest_Level90_2.CODE = SIN_QUEST_CODE_LEVEL90_2;
		sinQuest_Level90_2.State = 1;
		SaveGameData();
		StartQuest_Code(sinQuest_Level90_2.CODE);
		break;

	case MESSAGE_TELEPORT:
		CheckCharForm();

		SendPaymentMoneyToServer(TeleportUseCose[sinTeleportMoneyIndex - 1] + ((TeleportUseCose[sinTeleportMoneyIndex - 1] * cSinSiege.GetTaxRate()) / 100), 2);

		sinMinusMoney(TeleportUseCose[sinTeleportMoneyIndex - 1], 1);
		WarpField2(sinTeleportIndexArray[sinTeleportMoneyIndex - 1]);
		sinPlaySound(SIN_SOUND_COIN);
		ReformCharForm();
		break;
	case MESSAGE_CHANGE_JOB4:
		sinQuest_ChangeJob4.CODE = SIN_QUEST_CODE_CHANGEJOB4;
		sinQuest_ChangeJob4.State = 1;
		StartQuest_Code(sinQuest_ChangeJob4.CODE);
		sinChangeJob4MonSet(&sinQuest_ChangeJob4);
		SaveGameData();
		break;
	case MESSAGE_CHANGE_JOB4_2:

		sinChar->ChangeJob++;
		cSkill.OpenFlag = 1;
		cInterFace.CheckAllBox(SIN_SKILL);
		SkillMasterFlag = 1;
		sinQuest_ChangeJob4.State = 0;
		sinJobList = GetJobDataCode(sinChar->JOB_CODE, sinChar->ChangeJob);
		strcpy_s(cInvenTory.JobName, sinJobList->szName2);

		sinQuest_ChangeJob4.BackUpCode = sinQuest_ChangeJob4.CODE;
		sinQuest_ChangeJob4.CODE = 0;
		sinChar->wVersion[1] = 0;
		EndQuest_Code(sinQuest_ChangeJob4.BackUpCode);

		cInvenTory.ReFormInvenItem();
		sinSkillPontInitButtonFlag = 1;
		SaveGameData();

		ChangeJobFace();
		if (sinChar->JOB_CODE <= 4 || sinChar->JOB_CODE == 9)
			WarpField2(START_FIELD_NUM);
		else
			WarpField2(START_FIELD_MORYON);

		break;
	case MESSAGE_CRISTALEVENTITEM_SEND:
		if (cInvenTory.SendCristalEventItem())
		{
			SendWingQuestItem();
		}
		break;
	case MESSAGE_WATERMELON_EVENTITEM:
		if (cInvenTory.SendWatermelonEventItem())
		{
			SendWingQuestItem();
		}
		break;
	case MESSAGE_VALENTINE_EVENTITEM:
		if (cInvenTory.SendValentineEventItem())
		{
			SendWingQuestItem();
		}
		break;
	case MESSAGE_PRISTON_ALPHABET_EVENTITEM:
		if (cInvenTory.SendPristonAlphabetEventItem())
		{
			SendWingQuestItem();
		}
		break;

	case MESSAGE_CANDYDAYS_EVENTITEM:
		if (cInvenTory.SendCandydaysEventItem())
		{
			SendWingQuestItem();
		}
		break;

	case MESSAGE_MAGICALGREEN_EVENTITEM:
		if (cInvenTory.SendMagicalGreenEventItem())
		{
			SendWingQuestItem();
		}
		break;

	case MESSAGE_MAGICALGREEN_EVENTITEM_EMERALD:
		if (cInvenTory.SendMagicalGreenEmeraldEventItem())
		{
			SendWingQuestItem();
		}
		break;

	case MESSAGE_TEAROFKARA_EVENTITEM:
		if (cInvenTory.SendTearOfKaraEventItem())
		{
			SendWingQuestItem();
		}
		break;

	case MESSAGE_FIND_EVENTITEM:
		if (cInvenTory.SendFindinvestigatorNineEventItem())
		{
			SendWingQuestItem();
		}
		break;

	case MESSAGE_FINDKAMIU_EVENTITEM:
		if (cInvenTory.SendFindinvestigatorTaleEventItem())
		{
			SendWingQuestItem();
		}
		break;

	case MESSAGE_FINDETO_EVENTITEM:
		if (cInvenTory.SendFindinvestigatorTaleEtoEventItem())
		{
			SendWingQuestItem();
		}
		break;

	case MESSAGE_CASTLE_TELEPORT:
		CheckCharForm();

		WarpField2(33);
		sinMinusMoney(haC_TeleportMoney);
		sinPlaySound(SIN_SOUND_COIN);
		ReformCharForm();





		break;
	case MESSAGE_CASTLE_BUYTOWER:
		if ((sinChar->Money - haTowerMoney) < 0)
		{
			cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
			break;
		}
		for (int i = 0; i < 6; i++)
		{
			if (cSinSiege.TowerTypeDraw[i][0])
			{
				cSinSiege.TowerTypeDraw[i][1] = haSendTowerIndex;
			}

		}

		cSinSiege.Price = haTowerMoney;
		sinMinusMoney(haTowerMoney);

		chaSiege.SendServerSiegeData();


		sinPlaySound(SIN_SOUND_COIN);


		break;

	case MESSAGE_QUEST_ElementaryA:
		chaQuest.sHaQuestElementary[Quest_A].CODE = HAQUEST_CODE_ELEMENTARY_A;
		chaQuest.sHaQuestElementary[Quest_A].State = 1;
		if (!cInvenTory.SearchItemCode(sinQT1 | sin15))
		{
			SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_A, 1, 0, 0);
		}
		SaveGameData();
		StartQuest_Code(chaQuest.sHaQuestElementary[Quest_A].CODE);
		break;

	case MESSAGE_QUEST_ElementaryB:
		chaQuest.sHaQuestElementary[Quest_B].CODE = HAQUEST_CODE_ELEMENTARY_B;
		chaQuest.sHaQuestElementary[Quest_B].State = 1;
		chaQuest.haElementaryQuest_B();
		SaveGameData();
		StartQuest_Code(chaQuest.sHaQuestElementary[Quest_B].CODE);
		break;

	case MESSAGE_QUEST_ElementaryC:
		chaQuest.sHaQuestElementary[Quest_C].CODE = HAQUEST_CODE_ELEMENTARY_C;
		chaQuest.sHaQuestElementary[Quest_C].State = 1;
		if (!cInvenTory.SearchItemCode(sinQT1 | sin14))
		{
			SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_C, 1, 0, 0);
		}
		SaveGameData();
		StartQuest_Code(chaQuest.sHaQuestElementary[Quest_C].CODE);
		break;

	case MESSAGE_QUEST_ElementaryD:
		chaQuest.sHaQuestElementary[Quest_D].CODE = HAQUEST_CODE_ELEMENTARY_D;
		chaQuest.sHaQuestElementary[Quest_D].State = 1;
		chaQuest.haElementaryQuest_D();
		SaveGameData();
		StartQuest_Code(chaQuest.sHaQuestElementary[Quest_D].CODE);
		break;

	case MESSAGE_QUEST_ElementaryE:
		chaQuest.sHaQuestElementary[Quest_E].CODE = HAQUEST_CODE_ELEMENTARY_E;
		chaQuest.sHaQuestElementary[Quest_E].State = 1;
		chaQuest.haElementaryQuest_E();
		SaveGameData();
		StartQuest_Code(chaQuest.sHaQuestElementary[Quest_E].CODE);
		break;

	case MESSAGE_QUEST_ElementaryF:
		chaQuest.sHaQuestElementary[Quest_F].CODE = HAQUEST_CODE_ELEMENTARY_F;
		chaQuest.sHaQuestElementary[Quest_F].State = 1;
		chaQuest.haElementaryQuest_F();
		SaveGameData();
		StartQuest_Code(chaQuest.sHaQuestElementary[Quest_F].CODE);
		break;

	case MESSAGE_QUEST_ElementaryG:
		chaQuest.sHaQuestElementary[Quest_G].CODE = HAQUEST_CODE_ELEMENTARY_G;
		chaQuest.sHaQuestElementary[Quest_G].State = 1;
		SaveGameData();
		StartQuest_Code(chaQuest.sHaQuestElementary[Quest_G].CODE);
		break;
	case  MESSAGE_EVENT_ITEMOK:
		chaPremiumitem.UsePremiumItem(cInvenTory.iEventBuyItemKind);
		break;

	case MESSAGE_QUEST_100LV:
		chaQuest.sHaQuest100LV.CODE = HAQUEST_CODE_FURYOFPHANTOM;
		chaQuest.sHaQuest100LV.State = 1;
		StartQuest_Code(chaQuest.sHaQuest100LV.CODE);
		chaQuest.showFuryQuest();
		SaveGameData();
		break;

	case MESSAGE_QUEST_100LVITEMOK:
	{
		sITEM TempItem;
		TempItem.w = ITEMSIZE * 2;
		TempItem.h = ITEMSIZE * 4;
		TempItem.sItemInfo.Weight = 60;
		TempItem.Flag = 1;

		if (sinChar->Weight[0] + TempItem.sItemInfo.Weight > sinChar->Weight[1])
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			chaQuest.sHaQuest100LV.State = 12;
			chaQuest.iFuryQuestIndex[1] = 0;
			break;
		}

		if (cInvenTory.CheckSetEmptyArea(&TempItem))
		{
			SendQuestCommandToServer(HAQUEST_CODE_FURYOFPHANTOM, 2, chaQuest.iFuryQuestIndex[1], 0);
			haElementaryQuestLog |= QUESTBIT_FURYOFPHANTOM;
			chaQuest.sHaQuest100LV.State = 100;
			chaQuest.sHaQuest100LV.BackUpCode = chaQuest.sHaQuest100LV.CODE;
			chaQuest.sHaQuest100LV.CODE = 0;
			EndQuest_Code(chaQuest.sHaQuest100LV.BackUpCode);
			cMessageBox.ShowMessage(MESSAGE_100LVITEM_OK);
			SaveGameData();
		}
		else
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
			chaQuest.sHaQuest100LV.State = 12;
			chaQuest.iFuryQuestIndex[1] = 0;
			break;
		}
		chaQuest.iFuryQuestIndex[1] = 0;
		SaveGameData();
	}
	break;

	case MESSAGE_QUEST_START:
		if (cQuestWindow.OpenFlag)
			cQuestWindow.pSelectedSpoiler->StartQuest(true);
		break;

	case MESSAGE_QUEST_CANCEL:
		if (cQuestWindow.OpenFlag)
			cQuestWindow.pSelectedSpoiler->CancelQuest(true);
		break;

	case MESSAGE_QUEST_100LVBATTLEOK:
		if (chaQuest.sHaQuest100LV.State == 3 ||
			chaQuest.sHaQuest100LV.State == 8 ||
			chaQuest.sHaQuest100LV.State == 10)
			chaQuest.sHaQuest100LV.State++;
		Start_QuestArena(HAQUEST_CODE_FURYOFPHANTOM, chaQuest.sHaQuest100LV.State / 5 + 1, 0);
		SetQuestBoard();
		break;
	case MESSAGE_TELEPORT_CORE:
		chaPremiumitem.Using_ItemKind = 0;
		chaPremiumitem.UseTeleportScrollItem(chaPremiumitem.TelePortCore.ItemIndex);
		break;

	case MESSAGE_FALLGAME:
		WarpField2(39);
		break;

	case MESSAGE_COIN_SHOP:
	{
		SHOP_BUY packet;
		CopyMemory(&packet.item, &selectitem, sizeof(SHOP_ITEM));
		packet.size = sizeof(SHOP_BUY);
		if (Shop::GetInstance()->IsOpen())
			packet.code = PACKET_SEND_ITEM_SERVER;
		else if (TShop::GetInstance()->IsOpen())
			packet.code = TPACKET_SEND_ITEM_SERVER;
		if (smWsockUserServer)
			smWsockUserServer->Send((char *)&packet, packet.size, TRUE);
	}
	break;



	case MESSAGE_BATTLE_ARENA:
	{
		smTRANS_COMMAND packet;

		Battle::GetInstance()->Close();
		packet.size = sizeof(smTRANS_COMMAND);
		packet.code = smTRANSCODE_ENTER_BATTLE_ARENA;
		if (smWsockUserServer)
			smWsockUserServer->Send((char*)& packet, packet.size, TRUE);
	}
	break;


	case MESSAGE_QUEST_DIARY:
	{
		smTRANS_COMMAND packet;
		packet.size = sizeof(smTRANS_COMMAND);
		packet.code = smTRANSCODE_REQUEST_DIARY;
		if (smWsockUserServer)
			smWsockUserServer->Send((char *)&packet, packet.size, TRUE);

	}
	break;

	case VALE_LEVEL:
	{
		char CharLevel[32];
		setexp();
		AddExp(((ExpLevelTable[lpCurPlayer->smCharInfo.Level] - ExpLevelTable[lpCurPlayer->smCharInfo.Level - 1]) * 100) / 100);
		wsprintf(CharLevel, "VocÍ alcancou o level %d!", sinChar->Level);
		cMessageBox.ShowMessageEvent(CharLevel);
	}
	break;


	case MESSAGE_TRADE_BPEXP:
	{
		if (lpCurPlayer->sBlessCastle_Damage[1] >= 50)
		{

			if ((lpCurPlayer->smCharInfo.Level >= 80) && (lpCurPlayer->smCharInfo.Level < 100))
			{
				bcanadd = true;
				AddExp(((ExpLevelTable[lpCurPlayer->smCharInfo.Level] - ExpLevelTable[lpCurPlayer->smCharInfo.Level - 1]) * 10) / 100);
				cMessageBox.ShowMessageEvent("VocÍ trocou 50 pontos de batalha por 10%.");
			}
			else if ((lpCurPlayer->smCharInfo.Level >= 100) && (lpCurPlayer->smCharInfo.Level < 120))
			{
				bcanadd = true;
				AddExp(((ExpLevelTable[lpCurPlayer->smCharInfo.Level] - ExpLevelTable[lpCurPlayer->smCharInfo.Level - 1]) * 5) / 100);
				cMessageBox.ShowMessageEvent("VocÍ trocou 50 pontos de batalha por 5%.");
			}
			else if ((lpCurPlayer->smCharInfo.Level >= 120) && (lpCurPlayer->smCharInfo.Level < 140))
			{
				bcanadd = true;
				AddExp(((ExpLevelTable[lpCurPlayer->smCharInfo.Level] - ExpLevelTable[lpCurPlayer->smCharInfo.Level - 1]) * 2) / 100);
				cMessageBox.ShowMessageEvent("VocÍ trocou 50 pontos de batalha por 2%.");
			}
			else if ((lpCurPlayer->smCharInfo.Level >= 140) && (lpCurPlayer->smCharInfo.Level < 150))
			{
				bcanadd = true;
				AddExp(((ExpLevelTable[lpCurPlayer->smCharInfo.Level] - ExpLevelTable[lpCurPlayer->smCharInfo.Level - 1]) * 1) / 100);
				cMessageBox.ShowMessageEvent("VocÍ trocou 50 pontos de batalha por 1%.");
			}

			smTRANS_COMMAND smPacket;
			smPacket.code = OpCode::UPDATE_BATTLE_POINTS;
			smPacket.WParam = lpCurPlayer->sBlessCastle_Damage[1];
			smPacket.EParam = 2;
			smPacket.size = sizeof(smPacket);

			smWsockDataServer->Send((char *)&smPacket, smPacket.size, TRUE);

			lpCurPlayer->sBlessCastle_Damage[1] -= 50;

			ZeroMemory(&smPacket, sizeof(smTRANS_COMMAND));
		}
		else
			cMessageBox.ShowMessageEvent("… necess·rio 50 pontos de batalha para realizar a troca!");
	}

	break;

	case MESSAGE_MANUFACTURE:
		sinCraftItemStartFlag = 1;
		SetInterEffectManufacture();
		MixCancelButtonDelayFlag = 1;
		break;

	case MESSAGE_TELEPORT_DUNGEON:
		cSinHelp.NPCTeleportFlag = 0;
		WarpField2(40);
		break;

	case MESSAGE_CONFIRMATION_BOX:
		_ConfirmationBox.CheckFlag(true);
		break;
	}
	sinMessageBoxShowFlag = 0;
	sinInitPointFlag7 = 0;
	sMessageBox3[Kind].Flag = 0;
	ShowSkillUpInfo = 0;

	return TRUE;
}



int cMESSAGEBOX::CheckOkMessageBox(int Kind)
{
	int j = 0;

	if (sMessageBox2[Kind].Count <= 0)
	{
		sinMessageBoxShowFlag = 0;
		sMessageBox2[Kind].Flag = 0;
		cSinSod2.ClanMasterMessageBoxFlag = 0;
		return FALSE;
	}

	memset(&MessageBoxItem, 0, sizeof(sITEM));
	switch (Kind)
	{
	case MESSAGE_BUY_ITEM:
		if (!BuyItemServerFlag)
		{
			cShop.SendBuyItemToServer(pMessageItem, sMessageBox2[Kind].Count);
			pMessageItem = 0;
			cInvenTory.CheckWeight();

		}

		break;
	case MESSAGE_SELL_ITEM:
		memcpy(&MessageBoxItem, pMessageItem, sizeof(sITEM));
		if (sMessageBox2[Kind].Count >= pMessageItem->sItemInfo.PotionCount)
		{
			cShop.SellItemToShop(&MessageBoxItem, MessageBoxItem.sItemInfo.PotionCount);
			pMessageItem->Flag = 0;
			sInven[pMessageItem->ItemPosition - 1].ItemIndex = 0;
		}
		else
		{
			pMessageItem->sItemInfo.PotionCount -= sMessageBox2[Kind].Count;
			MessageBoxItem.sItemInfo.PotionCount = sMessageBox2[Kind].Count;
			cShop.SellItemToShop(&MessageBoxItem, MessageBoxItem.sItemInfo.PotionCount);
		}
		pMessageItem = 0;
		cInvenTory.CheckWeight();

		break;
	case MESSAGE_THROW_ITEM:
		if (cMixtureReset.OpenFlag)break;
		if (cWareHouse.OpenFlag)break;
		if (cTrade.OpenFlag)break;
		if (cAging.OpenFlag)break;
		if (cCraftItem.OpenFlag)break;
		if (sSinWarpGate.ShowFlag)break;
		if (!pMessageItem)break;

		if (SmeltingItem.OpenFlag)
		{
			break;
		}

		if (ManufactureItem.m_OpenFlag)
		{
			break;
		}

		memcpy(&MessageBoxItem, pMessageItem, sizeof(sITEM));
		if (sMessageBox2[Kind].Count >= pMessageItem->sItemInfo.PotionCount)
		{
			if (sinThrowItemToFeild(&MessageBoxItem))
			{
				sinPlaySound(MessageBoxItem.SoundIndex);
				pMessageItem->Flag = 0;
				sInven[pMessageItem->ItemPosition - 1].ItemIndex = 0;
				sinSaveGame(MessageBoxItem.sItemInfo.CODE, sMessageBox2[Kind].Count);
			}
		}
		else
		{
			pMessageItem->sItemInfo.PotionCount -= sMessageBox2[Kind].Count;
			MessageBoxItem.sItemInfo.PotionCount = sMessageBox2[Kind].Count;

			if (sinThrowItemToFeild(&MessageBoxItem))
			{
				sinPlaySound(MessageBoxItem.SoundIndex);
				sinSaveGame(MessageBoxItem.sItemInfo.CODE, sMessageBox2[Kind].Count);

			}

		}
		pMessageItem = 0;
		cInvenTory.CheckWeight();
		cInvenTory.ReFormPotionNum();
		break;
	case MESSAGE_THROW_MONEY:
		if (cMixtureReset.OpenFlag)break;
		if (cWareHouse.OpenFlag)break;
		if (cTrade.OpenFlag)break;
		if (cAging.OpenFlag)break;
		if (cCraftItem.OpenFlag)break;
		if (sSinWarpGate.ShowFlag)break;

		if (SmeltingItem.OpenFlag)
		{
			break;
		}

		if (ManufactureItem.m_OpenFlag)
		{
			break;
		}
		memset(&MessageBoxItem, 0, sizeof(sITEM));
		MessageBoxItem.sItemInfo.CODE = sinGG1 | sin01;
		for (j = 0; j < MAX_ITEM; j++)
		{
			if (sItem[j].CODE == MessageBoxItem.sItemInfo.CODE)
			{
				memcpy(&MessageBoxItem, &sItem[j], sizeof(sITEM));
				break;
			}
		}
		if (sMessageBox2[Kind].Count > sinChar->Money)
		{
			SendSetHackUser2(4100, 1);
			sMessageBox2[Kind].Count = sinChar->Money;

		}
		MessageBoxItem.sItemInfo.Money = sMessageBox2[Kind].Count;
		wsprintf(MessageBoxItem.sItemInfo.ItemName, sinGold, MessageBoxItem.sItemInfo.Money);
		ReformItem(&MessageBoxItem.sItemInfo);
		if (sinThrowItemToFeild(&MessageBoxItem))
		{
			sinPlaySound(MessageBoxItem.SoundIndex);
			CheckCharForm();

			sinMinusMoney(MessageBoxItem.sItemInfo.Money);
			ReformCharForm();
			SendSaveMoney();
		}
		break;
	case  MESSAGE_MOVE_MONEY_TRADE:
		if (!CheckTrade((void *)&sTrade))
			cTrade.CancelTradeItem();
		CheckCharForm();
		if (sinChar->Money - sMessageBox2[Kind].Count < 0)
		{
			SendSetHackUser2(4100, 2);
			sMessageBox2[Kind].Count = sinChar->Money;

		}

		sinMinusMoney(sMessageBox2[Kind].Count);
		ReformCharForm();
		SendSaveMoney();
		sTrade.Money = sMessageBox2[Kind].Count;
		TempShowMoney = sTrade.Money;
		sTrade.Money = sTrade.Money + 193;
		sinPlaySound(SIN_SOUND_COIN);
		ReformTrade((void *)&sTrade);
		sTrade.CheckFlag = 0;
		SendTradeItem(cTrade.TradeCharCode);

		break;

	case MESSAGE_MOVE_COIN_TRADE:
		if (!CheckTrade((void *)&sTrade))
			cTrade.CancelTradeItem();
		CheckCharForm();
		if (Shop::GetInstance()->GetCoin() - sMessageBox2[Kind].Count < 0)
		{
			SendSetHackUser2(4100, 2);
			sMessageBox2[Kind].Count = Shop::GetInstance()->GetCoin();
		}
		Shop::GetInstance()->MinusCoin(sMessageBox2[Kind].Count);
		ReformCharForm();
		sTrade.Coin = sMessageBox2[Kind].Count;
		TempShowCoin = sTrade.Coin;
		sinPlaySound(SIN_SOUND_COIN);
		ReformTrade((void *)&sTrade);
		sTrade.CheckFlag = 0;
		SendTradeItem(cTrade.TradeCharCode);
		break;

	case MESSAGE_MOVE_MONEY_MOVE:
		if (sinChar->Money - sMessageBox2[Kind].Count < 0)
		{
			SendSetHackUser2(4100, 3);
			sMessageBox2[Kind].Count = sinChar->Money;

		}

		CheckCharForm();

		sinMinusMoney2(sMessageBox2[Kind].Count);
		ReformCharForm();

		sWareHouse.Money += sMessageBox2[Kind].Count;
		sinPlaySound(SIN_SOUND_COIN);
		WareHouseSaveFlag = 1;

		break;

	case MESSAGE_MOVE_MONEY_RECV:
		if ((sWareHouse.Money - 2023) - sMessageBox2[Kind].Count < 0)
		{
			SendSetHackUser2(4100, 4);
			sMessageBox2[Kind].Count = sWareHouse.Money - 2023;

		}

		CheckCharForm();

		sinPlusMoney2(sMessageBox2[Kind].Count);
		ReformCharForm();

		sWareHouse.Money -= sMessageBox2[Kind].Count;
		sinPlaySound(SIN_SOUND_COIN);
		WareHouseSaveFlag = 1;

		break;
	case MESSAGE_BUY_ITEM_DEFALT:
		if (!BuyItemServerFlag)
		{
			cShop.SendBuyItemToServer(pMessageItem, sMessageBox2[Kind].Count);
			cInvenTory.CheckWeight();

		}

		break;
	case MESSAGE_BUY_STAR:
		SendStarPointToServer(sMessageBox2[Kind].Count * 100000, 1);
		CheckCharForm();
		sinMinusMoney2(sMessageBox2[Kind].Count * 100000);
		sinPlaySound(SIN_SOUND_COIN);
		ReformCharForm();
		StarShopNPC();
		break;

	case MESSAGE_GIVE_MONEY:
		sinGiveMoneyCheckFlag = 1;
		sinGiveMoneyAmount = sMessageBox2[Kind].Count;
		wsprintf(szGiveMoneyBuff, "%d", sinGiveMoneyAmount);



		break;
	case MESSAGE_MYSHOP_ITEM:
		if (cInvenTory.CheckMoneyLimit(sMessageBox2[Kind].Count))
		{
			MyShopMouseItem.sItemInfo.Money = sMessageBox2[Kind].Count;
			cMyShop.LastSetMyShopItem(&MyShopMouseItem);
		}


		break;
	case MESSAGE_MYSHOP_POTION:
		if (cCharShop.OpenFlag)
		{
			sMyShop_Server.sTime = sMessageBox2[Kind].Count;
			sMyShop_Server.Price *= sMessageBox2[Kind].Count;
			Send_PersonalShopItem(sRecvMyShop.CHAR_CODE, &sMyShop_Server);
		}
		break;
	case MESSAGE_SOD2_GET_MONEY:
		if (sinMessageBox_New.Flag && cSinSod2.BoxIndex == 1 && sMessageBox2[Kind].Count)
		{
			if (cSinSod2.UserType == 6)
			{
				SendClanMoneyToServer(sMessageBox2[Kind].Count, 0);
			}
		}
		cSinSod2.ClanMasterMessageBoxFlag = 0;



		break;
	case MESSAGE_SIEGE_GET_MONEY:
		if (haSiegeMenuFlag)
		{
			if ((cSinSiege.TotalTax >= sMessageBox2[Kind].Count) &&
				(cSinSiege.ExpectedTotalTax >= sMessageBox2[Kind].Count))
			{
				cSinSiege.ExpectedTotalTax = cSinSiege.ExpectedTotalTax - sMessageBox2[Kind].Count;
				SendClanMoneyToServer(sMessageBox2[Kind].Count, 0, 1);
			}
		}
		break;
	case MESSAGE_SIEGE_SET_MERCENRAY:

		if (haSiegeMenuFlag)
		{

			if (haMercenrayIndex)
			{
				cSinSiege.MercenaryNum[haMercenrayIndex - 1] += sMessageBox2[Kind].Count;
				cSinSiege.Price = haMercenrayMoney[haMercenrayIndex - 1] * sMessageBox2[Kind].Count;
				chaSiege.SendServerSiegeData();
				cSinSiege.Price = 0;
			}
		}

		sinMinusMoney(haMercenrayMoney[haMercenrayIndex - 1] * sMessageBox2[Kind].Count);
		sinPlaySound(SIN_SOUND_COIN);
		break;



	}
	sinMessageBoxShowFlag = 0;
	sMessageBox2[Kind].Flag = 0;
	memset(&MessageBoxItem, 0, sizeof(sITEM));
	cInvenTory.ReFormPotionNum();
	return TRUE;
}


int StarShopNPC()
{

	SendStarPointToServer(0, 0);
	sITEM *pItem = 0;
	GiftPrice = 0;
	sStarShop.Flag = 1;
	for (int i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else
		{
			if (!cInvenTory.InvenItemTemp[i - 100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i - 100];
		}
		if (pItem->sItemInfo.CODE == (sinGF1 | sin01))
		{
			GiftPrice += pItem->sItemInfo.Price;
		}
	}
	if (GiftPrice)
	{
		cMessageBox.ShowMessage3(MESSAGE_GIFT_TICKET, "ªÛ«∞±«¿∏∑Œ");
	}
	return TRUE;
}


int sinStarPoint(int Point)
{
	sStarShop.Count = Point;
	return TRUE;
}


int DeleteGiftItem()
{
	sITEM *pItem = 0;
	for (int i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else
		{
			if (!cInvenTory.InvenItemTemp[i - 100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i - 100];
		}
		if (pItem->sItemInfo.CODE == (sinGF1 | sin01))
		{
			pItem->Flag = 0;

		}
	}
	cInvenTory.ReFormInvenItem();
	ReformCharForm();
	return TRUE;

}
