

#include "sinLinkHeader.h"



char *EvnetDocFilePath[] = {
	"image\\Sinimage\\Event\\SmashTV.sin",


};

int sinShowEventSmashingTV()
{
	HelpBoxKindIndex = SIN_EVENT_SMASHTV;
	cSinHelp.sinShowHelp(SIN_HELP_KIND_SMASHTV, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), EvnetDocFilePath[0]);

	return TRUE;
}

int sinSendEventItem(int Send)
{
	int MessageFlag = 0;
	for(int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if(cInvenTory.InvenItem[i].Flag)
		{
			if((cInvenTory.InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinGP1)
			{
				if(Send)
				{
					SendUseItemCodeToServer(&cInvenTory.InvenItem[i].sItemInfo);
					cInvenTory.InvenItem[i].Flag = 0;
					cInvenTory.ReFormInvenItem();
					ResetInvenItemCode();
					MessageFlag = 1;
				}
				else return TRUE;
			}

		}
		if(cInvenTory.InvenItemTemp[i].Flag)
		{
			if((cInvenTory.InvenItemTemp[i].sItemInfo.CODE & sinITEM_MASK2) == sinGP1)
			{
				if(Send)
				{
					SendUseItemCodeToServer(&cInvenTory.InvenItemTemp[i].sItemInfo);
					cInvenTory.InvenItemTemp[i].Flag = 0;
					cInvenTory.ReFormInvenItem();
					ResetInvenItemCode();
					MessageFlag = 1;
				}
				else return TRUE;

			}
		}
	}
	if(Send)
	{
		if(MessageFlag)
		{
			cMessageBox.ShowMessage(MESSAGE_GYUNGFUM_OK);

		}
	}
	else return FALSE;

	return FALSE;
}

