#include "RestaureWindow.h"
#include "ConfirmationBox\\ConfirmationBox.h"
#include "sinbaram\\sinLinkHeader.h"

FailedItemsPckg failedItems;
RestaureWindow restaureWindow;

extern int sinGetKeyClick(int num);
extern bool isMousePos(int x, int y, int w, int h);

int totalYR = 0;
int Plusx = 0;
int Plusy = 0;
int totalItems = 0;

INT RestaureWindow::getFailedItems()
{
	smTRANS_COMMAND getFailedItems;
	getFailedItems.code = GET_FAILED_ITEMS;
	getFailedItems.size = sizeof(smTRANS_COMMAND);
	getFailedItems.WParam = 0;
	getFailedItems.LParam = 0;
	getFailedItems.SParam = 0;

	if (smWsockServer)
		smWsockServer->Send((char*)&getFailedItems, getFailedItems.size, TRUE);

	return TRUE;
}

INT RecoverItem(int ItemHead, int ItemChkSum)
{
	smTRANS_COMMAND getFailedItems;
	getFailedItems.code = RECOVER_AGING_ITEM;
	getFailedItems.size = sizeof(smTRANS_COMMAND);
	getFailedItems.WParam = ItemHead;
	getFailedItems.LParam = ItemChkSum;
	getFailedItems.SParam = 0;

	if (smWsockServer)
		smWsockServer->Send((char*)&getFailedItems, getFailedItems.size, TRUE);

	return TRUE;
}


int restaureItem(std::string title, int ItemHead, int ItemChkSum)
{
	_ConfirmationBox.SetTitle(title);
	_ConfirmationBox.SetText("Deseja recuperar", "Este Item?");
	_ConfirmationBox.SetCallback([ItemHead, ItemChkSum](bool confirmed)
		{
			if (confirmed)
				RecoverItem(ItemHead, ItemChkSum);
			else
				return FALSE;
		});

	_ConfirmationBox.Start();

	return FALSE;
}


INT RestaureWindow::ReceiveFailedItems(FailedItemsPckg* FailedItems)
{
	FailedItemsPckg getItems;
	ZeroMemory(&failedItems, sizeof(FailedItemsPckg));
	ZeroMemory(&getItems, sizeof(FailedItemsPckg));
	CopyMemory(&getItems, FailedItems, sizeof(FailedItemsPckg));
	int y = 0;

	for (int x = 0; x < getItems.total; x++)
	{
		failedItems.FailedItems[y] = getItems.FailedItems[x];
		y++;
		totalItems++;
	}

	failedItems.price = getItems.price;

	return TRUE;
}
void RestaureWindow::Init()
{
	Window[0] = CreateTextureMaterial("game\\GUI\\Restaure\\Window.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Window[1] = CreateTextureMaterial("game\\GUI\\Restaure\\Close.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void RestaureWindow::OpenWindow()
{
	openFlag = true;
}

void RestaureWindow::CloseWindow()
{
	openFlag = false;
	totalItems = 0;
}

void RestaureWindow::MouseWheel(short zDelta)
{
	if (!openFlag)
		return;

	if (zDelta >= 0)
	{
		if (ScrollList < 0)
			ScrollList += 5;
	}
	else
	{
		int iBotLimit = BaseY + 300;

		if (totalYR > iBotLimit)
			ScrollList -= 5;
	}
}


void RestaureWindow::LButtonDown()
{
	if (!openFlag)
		return;

	if (totalItems)
	{
		int iX = BaseX + 33;
		int iY = BaseY + 130 + ScrollList - 80;

		for (int x = 0; x < totalItems; x++)
		{
			if (failedItems.FailedItems[x].ItemHead)
			{		
				if (isMousePos(iX, iY, 215, 20))
				{
					restaureItem(failedItems.FailedItems[x].ItemName, failedItems.FailedItems[x].ItemHead, failedItems.FailedItems[x].ItemChkSum);
					openFlag = false;
					break;
				}

				iY += 24;
			}

		}
	}

	if (isMousePos(BaseX + 350, BaseY + 310, 20, 20))
	{
		CloseWindow();
	}

}
void RestaureWindow::OpenNpc()
{
	if (!openFlag)
		return;

	BaseX = (WinSizeX - 445) / 2;
	BaseY = (WinSizeY - 445) / 2;

	dsDrawTexImage(Window[0], BaseX, BaseY, 400, 350, 255);
	dsDrawTexImage(Window[1], BaseX + 350, BaseY  + 310, 19, 18, 255);

	if (totalItems)
	{
		int iX = BaseX + 33;
		int iY = (BaseY + 130 + ScrollList) - 80;

		int iTopLimit = BaseY + 50;
		int iBotLimit = BaseY + 300;

		for (int x = 0; x < totalItems; x++)
		{
			if (failedItems.FailedItems[x].ItemHead && (iY < iBotLimit))
			{
				SetFontTextColor(RGB(192, 192, 255));

				if (isMousePos(iX + 10, iY, 215, 20))
					SetFontTextColor(RGB(255, 255, 0));

				char itemAging[20] = { 0 };
				sprintf_s(itemAging, sizeof(itemAging), "Aging: + %d", failedItems.FailedItems[x].AgingNum);
				dsTextLineOut(iX + 10, iTopLimit > iY ? iTopLimit : iY, itemAging, lstrlen(itemAging));
				dsTextLineOut(iX + 80, iTopLimit > iY ? iTopLimit : iY, failedItems.FailedItems[x].ItemName, lstrlen(failedItems.FailedItems[x].ItemName));

				char date[64] = { 0 };
				sprintf_s(date, sizeof(date), "%02d/%02d/%02d", failedItems.FailedItems[x].Date.wDay, failedItems.FailedItems[x].Date.wMonth, failedItems.FailedItems[x].Date.wYear);
				dsTextLineOut(iX + 210, iTopLimit > iY ? iTopLimit : iY, date, lstrlen(date));

				char price[32] = { 0 };
				sprintf_s(price, sizeof(price), "%d Coins", failedItems.price);
				dsTextLineOut(iX + 280, iTopLimit > iY ? iTopLimit : iY, price, lstrlen(price));

				SetFontTextColor(RGB(192, 192, 255));
				//dsTextLineOut(iX + 10, iY - 70, "___________________________", lstrlen("___________________________"));

				iY += 24;
			}

			totalYR = iY;
		}
	}
}
