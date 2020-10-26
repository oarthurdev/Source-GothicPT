#pragma once
#ifndef __CE_CHATTING_HPP__
#define __CE_CHATTING_HPP__

#include <windows.h>
#include "clan_Enti.h"


#define BOX_X                 656
#define MOVE_X                 400
#define MOVE_Y                 0



#ifdef USE_PROSTONTALE		

#define CHATING_DISPLAY_MAX       8

#define CHATING_CLANWON_LIST_X    620
#define CHATING_CLANWON_LIST_Y    204 
#define CHATING_CLANWON_LIST_CAP  20



#define CHATICON_X               625
#define CHATCLOSE_X              740
#define CHATICON_Y               375


#define CHATLIST_SBAR_X	         770
#define CHATLIST_SBAR_Y           193
#define CHATLIST_MENU                     150

#else						

#define CHATING_DISPLAY_MAX       8
#define CHATING_CLANWON_LIST_X    620
#define CHATING_CLANWON_LIST_Y    130
#define CHATING_CLANWON_LIST_CAP   23

#define CHATICON_X               640
#define CHATCLOSE_X              730
#define CHATICON_Y               325
#define CHATLIST_SBAR_X	         770
#define CHATLIST_SBAR_Y           140
#define CHATLIST_MENU                     105

#endif						


#define CHATLIST_CLANCHIP                 1
#define CHATLIST_CLANUSER				2
#define CHATLIST_CLANNO_REGESTER			3				
#define CHATLIST_BOX_Y					147








typedef struct _tagCHATLIST
{
	int MyPositon;
	char  clanWon[CLANWON_MAX][30];
	char  szUserID[40];
	char  szGameServer[40];
	char  szChaName[40];
	char  szClanZang_Name[40];
}CHATLIST;

class CLANEntity_chatting : public CLANEntity
{
public:


	void chat_WhisperPartyPlayer2(int num);
	void chat_WhisperPartyPlayer(int num);
	void chat_WhisperPartyPlayer_close();

	char szFile_hMark[128];

	CLANEntity_chatting();
	~CLANEntity_chatting();

	int Init(int Life);
	void Close();


	void Main();
	void Draw();
	void InitClanWon();
	void InitClanChatList();
	void MoveClose();


	void menuInit(int num);
	void SortClanWonList();
	void Load();
	void Load2();









	void DrawBox();
	void Draw_C_menuN();
	void NoScroll();

	int  chkMenu(int x, int y, RECT *r);
	int  chkeckMenuN();
	void DoubleClick(int i);





	void ChatListParsigClanWon(char* data);
	void ChatListUserData(char *id, char *gserver, char *chaid);
	void ChatListParsingIsClanMember(char* data);
	void SetBoxDraw(BOOL bFlag)
	{
		bIsBox = bFlag;
	}
	void SetOpenChatList(BOOL bFlag)
	{
		bIsClose = bFlag;
	}
	void DisplayInfo();
public:
#ifdef USE_PROSTONTALE		
	int	hChatListBoxLine;

	int	hChatListBoxTitle2;


	DIRECTDRAWSURFACE	hChatListBoxTitle;
	DIRECTDRAWSURFACE	hChatIcon[2];
	DIRECTDRAWSURFACE	hButtonClose[2];
	DIRECTDRAWSURFACE	hClanWon[2];
	DIRECTDRAWSURFACE	hChatClanWon;

#ifdef PARKMENU
	DIRECTDRAWSURFACE	hMicOption[2];
	DIRECTDRAWSURFACE	hMicOptToolTip;
	int	hChatMicOpt;
	DIRECTDRAWSURFACE	hMicOptTitle;
	DIRECTDRAWSURFACE	hMicSortLine;
	DIRECTDRAWSURFACE	hMicONBack;
	DIRECTDRAWSURFACE	hMicONChk;
	DIRECTDRAWSURFACE	hMicVolBar;
	DIRECTDRAWSURFACE	hMicVOLUPDOWN[2];

#endif

	DIRECTDRAWSURFACE	hClanChatToolTip;
	DIRECTDRAWSURFACE	hBtnCloseToolTip;

#else
	HBITMAP  hChatListBoxLine;
	HBITMAP  hChatListBoxTitle;
	HBITMAP  hChatIcon[2];
	HBITMAP  hButtonClose[2];
	HBITMAP  hClanWon[2];
	HBITMAP hChatListParty;
	HBITMAP hChatListFriend;
	HBITMAP hChatClanWon;

#ifdef PARKMENU
	HBITMAP	hMicOption[2];
	HBITMAP	hMicOptTitle;
	HBITMAP	hMicSortLine;
	HBITMAP	hMicONBack;
	HBITMAP	hMicONChk;
	HBITMAP	hMicVolBar;
	HBITMAP	hMicVOLUPDOWN[2];
	HBITMAP	hMicOptToolTip;
#endif
	HBITMAP	hClanChatToolTip;
	HBITMAP	hBtnCloseToolTip;
#endif

	int nScl_Bar;
	RECT scrIconPos;
	int nScl_Save;
	int nTotalClanWon;
	int nRest_Num;
	CHATLIST   ClanChatList;
	BOOL bIsBox;
	char szErrorMsg[255];
	int nBoxMove;
	BOOL bIsClose;
	BOOL bIsDrawBoxFinish;
	int OCcnt;
	int ChatListBoxX;
	int ChatListBoxY;

	int cnt;
	int AddSize;
	RECT ChatList_menuPos[30];
	int ChatList_menuSu;



	int Chatting_button;


#ifdef PARKMENU
	int MicOpt_button;
	int nVol;
#endif


	int nSaveClanWonPos;
	int nDoublClick;

};


#endif 





#ifdef CE_CHATLIST_CPP

class CLANEntity_chatting cClanChatting;

#else

extern class CLANEntity_chatting cClanChatting;

#endif
