
#define _EVENT_GAME_







#ifdef _EVENT_GAME_

#define NPC_NUM			2
#define REVEDUSER_MAX	5000

static int rsFlag_rsFiltChatMsg = 0;

struct rsEVENT_REVEDUSER
{
	DWORD	dwIDCode;
	char	szID[ACCOUNT_SIZE];
};

static int rsHopeEventNpcPos[][3] = {


	{ 3 , 2419 , -16324 },
	{ 0 , 0 , 0 },
	{ 0,0,0 }

};



extern char *StateInitEvent1;
extern char *StateInitEvent2;
extern char *StateInitEvent3;
extern char *StateInitEvent4;




#ifdef _EVENT_GAME_STATE_INIT
extern char *szEvent_HopeMsg_StateInit;

rsEVENT_REVEDUSER rsEventUser_RecedList_StateInit[REVEDUSER_MAX];
int rsEventUser_RecvedCount_StateInit = 0;
#endif



#endif



int sveFiltChatMsg(rsPLAYINFO *lpPlayInfo, char *szMsg, int len)
{
#ifdef _EVENT_GAME_

	int x = 0;
	int z = 0;
	int dist = 0;
	int cnt = 0;


#ifdef _EVENT_GAME_STATE_INIT  
	cnt = 0;
	while(1)
	{
		if(rsHopeEventNpcPos[cnt][0] == 0) break;
		if(lpPlayInfo->Position.Area == rsHopeEventNpcPos[cnt][0])
		{
			x = abs(lpPlayInfo->Position.x / fONE - rsHopeEventNpcPos[cnt][1]);
			z = abs(lpPlayInfo->Position.z / fONE - rsHopeEventNpcPos[cnt][2]);
			dist = x*x + z*z;
			if(dist < 150 * 150)
			{
				if(strstr(szMsg, szEvent_HopeMsg_StateInit) > 0)
				{
					smTRANS_COMMAND smTransCommand;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.code = OpCode::OPCODE_EVENT_GAME;
					smTransCommand.WParam = smCODE_EVENT_STATE_INIT;
					smTransCommand.SParam = lpPlayInfo->Position.Area;
					smTransCommand.LParam = rsServerConfig.ServerCode;
					rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
					break;
				}
			}
		}
		cnt++;
	}
#endif 





#endif

	return TRUE;
}





int rsEventGame_State_Init(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
#ifdef _EVENT_GAME_STATE_INIT

	SYSTEMTIME	st;
	GetLocalTime(&st);


	TRANS_CHATMESSAGE	TransChatMessage;
	int cnt;

	if(rsEventUser_RecvedCount_StateInit >= REVEDUSER_MAX)
	{

		wsprintf(TransChatMessage.szMessage, "%s", StateInitEvent1);
		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 1;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
		return FALSE;
	}


	for(cnt = 0; cnt < rsEventUser_RecvedCount_StateInit; cnt++)
	{
		if(lpPlayInfo->dwCode_ID == rsEventUser_RecedList_StateInit[cnt].dwIDCode && lstrcmpi(lpPlayInfo->szID, rsEventUser_RecedList_StateInit[cnt].szID) == 0)
		{


			wsprintf(TransChatMessage.szMessage, "%s", StateInitEvent2);
			TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
			TransChatMessage.dwIP = 1;
			TransChatMessage.dwObjectSerial = 0;
			lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

			return FALSE;
		}
	}


	if(!lpPlayInfo->lpPostBoxItem) rsLoadPostBox(lpPlayInfo);

	if(lpPlayInfo->lpPostBoxItem && lpPlayInfo->lpPostBoxItem->ItemCounter > POST_ITEM_MAX - 1) return FALSE;


	rsPOST_BOX_ITEM		*lpPostBox = new rsPOST_BOX_ITEM;
	if(!lpPostBox) return FALSE;

	ZeroMemory(lpPostBox, sizeof(rsPOST_BOX_ITEM));


	lpPostBox->PostItem[0].dwItemCode = (sinBI1 | sin02);
	lpPostBox->PostItem[0].Flag++;
	strcpy_s(lpPostBox->PostItem[0].szCharName, "***");
	strcpy_s(lpPostBox->PostItem[0].szDoc, StateInitEvent3);

	strcpy_s(lpPostBox->PostItem[0].szFormCode, "0");
	strcpy_s(lpPostBox->PostItem[0].szItemCode, "BI102");
	strcpy_s(lpPostBox->PostItem[0].szSpeJob, "0");


	if(lpPlayInfo->lpPostBoxItem)
	{
		memcpy(&lpPostBox->PostItem[1], &lpPlayInfo->lpPostBoxItem->PostItem[0], sizeof(_POST_BOX_ITEM)*lpPlayInfo->lpPostBoxItem->ItemCounter);
		lpPostBox->ItemCounter = lpPlayInfo->lpPostBoxItem->ItemCounter + 1;
		lpPostBox->dwHead = lpPlayInfo->lpPostBoxItem->dwHead;

		delete lpPlayInfo->lpPostBoxItem;
		lpPlayInfo->lpPostBoxItem = lpPostBox;
	}
	else
	{
		lpPostBox->ItemCounter = 1;
		lpPlayInfo->lpPostBoxItem = lpPostBox;
	}


	rsEventUser_RecedList_StateInit[rsEventUser_RecvedCount_StateInit].dwIDCode = lpPlayInfo->dwCode_ID;
	strcpy_s(rsEventUser_RecedList_StateInit[rsEventUser_RecvedCount_StateInit].szID, lpPlayInfo->szID);
	rsEventUser_RecvedCount_StateInit++;




	wsprintf(TransChatMessage.szMessage, "%s", StateInitEvent4);
	TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 1;
	TransChatMessage.dwObjectSerial = 0;
	lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);


	smTRANS_COMMAND smTransCommand;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_YAHOO_MOTION;
	lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

#endif

	return TRUE;


}

