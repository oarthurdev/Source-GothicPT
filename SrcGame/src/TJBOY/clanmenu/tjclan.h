#ifdef USE_PROSTONTALE		
#else
#include <windows.h>
#endif

#define CLANUSER					100		
#define CLANCHIP					101		
#define CLANNO_REGESTER				102		
#define CLAN_NOCONNECT				103		
#define CLAN_SUBCHIP				104		





#define CLAN_NPC_START 0 

#define CLANMESSAGEBUF_MAX 1024



#define CLAN_MAKE_is	1 
#define CLAN_MONEY_is	2 
#define CLAN_NAME_is	3 
#define CLAN_MARK_expl  4 
#define CLAN_INSPECTION_expl	5 
#define CLAN_NAME_BEING         6
#define CLAN_MAKE_FINISH        7
#define CLAN_CHIP_ReadDATA		8 
#define CLAN_NONAME	            9
#define CLAN_GO_MAKE			10
#define CLAN_GO_NPCSTART          11
#define CLAN_NotMake			254 
#define CLAN_AllEnd				255 
#define CLAN_ERROR				1000




#define CLAN_CHECK_CLANMARK		200
#define CLAN_READ_CLANMARK		201
#define CLAN_REAMMAKR_ERROR       202  
#define CLANMAKE_REAMMAKR_ERROR       203  

#define CLAN_USER_DATA           300 






#define CLAN_CHIP				20 
#define CLAN_WAREHOUSE			21 
#define CLAN_WAREHOUSE_RIGHT		22 
#define CLAN_MARK				23 
#define CLAN_MARK1				24
#define CLAN_MARK2				25
#define CLAN_MARK3				26
#define CLAN_REMOVE				27 
#define CLAN_RELEASE			28 
#define CLAN_HELP				29 
#define CLAN_NOMAKE				30		
#define CLAN_HELP_CONTENT		31
#define CLAN_REMOVE_RESULT		32
#define CLAN_RECONF_RELEASE       33
#define CLAN_FINISH_RELEASE       34
#define CLAN_REMOVE_SHORTCLANWON   35
#define CLAN_RELEASE_LOADING       36
#define CLAN_REMOVE_SHORTCLANWON_LOADING 37
#define CLAN_REMOVE_LOADING        38
#define CLAN_REMOVE_SHORTCLANWON_RESULT   39 



#define CLAN_USER				40 
#define CLAN_JOIN				41 
#define CLAN_SECESSION			42 
#define CLAN_USER_WAREHOUSE		43	
#define CLAN_USER_HELP			44
#define CLAN_USER_NOMAKE			45
#define CLAN_USER_HELP_CONTENT	46
#define CLAN_RECONF_SECESSION    47
#define CLAN_FINISH_SECESSION     48
#define CLAN_USER_NOMAKE_FLAG      49
#define CLAN_USER_FLAG            50
#define CLAN_USER_ReadDATA        51
#define CLAN_RECONF_SECESSION_LOADING     52

#define CLANUSER_RELEASEMESSAGE	53 
#define CLANUSER_GO_RELEASEMESSAGE 54
#define CLANUSER_RELEASE_FLAG		55



#define CHATLIST_END			901
#define CHATLIST_ERROR			902
#define CHATLIST_READDATA		903
#define CLAN_DISPLAY_OPEN		904
#define CLAN_DISPLAY_END			905
#define CLAN_DISPLAY_INFO         906
#define CLAN_DISPLAY_CLOSE			907
#define CLAN_CLOSE_END_BEFORE			908
#define CLAN_CLOSE_ENDING             909
#define CHATLIST_READ_CLANMARK       910
#define CLAN_DISPLAY_BEFORE		911


#define UPDATE_ISCLANMEMBER           1003
#define UPDATE_CLANWON				1004
#define ISPFLAG_USER				1005
#define ISPFLAG_CHIP				1006
#define CLAN_isCheckClanJang_LOADING   1007
#define CLANCHIP_DOWN6_CLANWON_MESSAGE 1008
#define CLANSERVER_INSPECT		    1009
#define CLANSERVER_INSPECT_BEFORE      1010
#define CLANINFO_READMARK			1011
#define CLANINFO_DOWNLOAD			1012
#define CLANINFO_END				1013
#define CLANMAKE_DOWN_INFO			1014
#define CLANMAKE_READ_CLANMARK		1015
#define CLAN_isCheckClanJang_Result	1016	
#define CLANMAKE_NOMONEY				1017
#define CLANUSER_JOIN				1018
#define CLANUSER_REMOVE				1019 
#define CLANUSER_AUTORELEASE			1020 
#define MYCLAN_UPDATE				1021
#define MYCLAN_CLANMARK_UPDATE		1022
#define CLANCHIP_GO_RELEASEMESSAGE		1023
#define CLANCHIP_RELEASEMESSAGE		1024
#define CLANCHIP_RELEASE_FLAG			1025
#define CLANUSER_CHECKPFLAG			1026
#define CLAN_CLANWONOVER				1027 
#define CLAN_ABILITYDOWN				1028
#define CLAN_NOLEVEL				1029
#define CLAN_NOTICE					1030
#define CLAN_DRAWNOTICE				1031
#define CLAN_DRAWNOTICE_END			1032

#define CLANCHIP_LEAVECLAN			1033
#define CLANCHIP_LEAVECLAN_NOMONEY		1034
#define CLANCHIP_LEAVECLAN_SUCESS		1035
#define CLANCHIP_LEAVECLAN_CONFIRM		1036
#define CLANCHIP_LEAVECLAN_RECONFIRM	1037
#define CLANCHIP_LEAVECLAN_NOLEVEL		1038
#define CLANCHIP_LEAVECLAN_DO			1039
#define CLANCHIP_NOLEAVECLAN			1040
#define CLANCHIP_LEAVECLAN_PFLAG		1041
#define CLANCHIP_LEAVECLAN_MESSAGE		1042
#define CLANUSER_LEAVECLAN_MESSAGE		1043
#define CLANCHIP_LEAVECLAN_MESSAGEEND	1044
#define CLANUSER_LEAVECLAN_MESSAGEEND	1045  
#define CLANCHIP_LEAVECLANDOWNLEVEL	1046  




#define CLANCHIP_SUBCHIP_LIST			1047  
#define CLANCHIP_RESUBCHIP_APPOINT		1048  
#define CLANCHIP_RESUBCHIP_APPOINT_END	1049  
#define CLANCHIP_RELEASESUBCHIP		1050  
#define CLANCHIP_RELEASESUBCHIP_END	1051  
#define CLANCHIP_APPOINTSUBCHIP_DO		1052  
#define CLANCHIP_RELEASESUBCHIP_DO		1053  

#define CLANCHIP_SUBCHIP_APPOINTMSG	1054  
#define CLANCHIP_SUBCHIP_RELEASEMSG	1055  
#define CLANUSER_SUBCHIP_APPOINTMSG	1056  
#define CLANUSER_SUBCHIP_RELEASEMSG	1057  
#define CLANCHIP_SUBCHIP_APPOINT_FLAG	1058  
#define CLANCHIP_SUBCHIP_RELEASE_FLAG	1059  

#define CLANCHIP_SUBCHIP_READMSG_FLAG	1060  
#define CLANUSER_SUBCHIP_READMSG_FLAG	1061  

#define CLANCHIP_SUBCHIP_LOAD			1062  
#define CLANCHIP_SUBCHIP_LOAD_DATA		1063
#define CLANCHIP_NOSUBCHIP			1064




#define CLANSUBCHIP_INSERTCLANWON		2000 

#define CLANWON_MAX					100








#define CLAN_JOIN_before			60

#define CLAN_JOIN_After			62

#define CLAN_JOIN_chip			63
#define CLAN_JOIN_chip_NO		64
#define CLAN_JOIN_chip_YES		65


#define CLAN_IS_CHECK_MEMBER		100
#define CLAN_IS_CHECK_MEMBER_END	101



#define CLAN_isClanWon			66

#define CLAN_MAKE_examination		67		
#define CLAN_isCheckClanJang      68       
#define CLAN_LOADING			69

#define CLANCHIP_MAKE_FIRSTMESSAGE     70    

#define CLANCHIP_DOWN6_CLANWON         71   
#define CLANCHIP_BREAKCLAN            72

#define CLANUSER_MAKE_FIRSTMESSAGE    73
#define CLANUSER_DOWN6_CLANWON_MESSAGE  74
#define CLANUSER_DOWN6_CLANWON         75





#define BUTTONBOX_WIDTH   68
#define BUTTONBOX_HEIGHT  27
#define BUTTONTEXT_WIDTH  32
#define BUTTONTEXT_HEIGHT 16

#define BOX_MAX_WIDTH (((4 * BOXCENTER_WIDTH) + (2*BOXCORNER_WIDTH) + 5) )

#define ICON_START       55
#define ICON_ADD		 20
#define SCROLLBAR_LEFT    236
#define SCROOBAR_TOP	54
#define DISPLAY_MAX		8


#define CLAN_NAME_POS_X     65
#define CLAN_NAME_POS_Y     8



#define CLANHELPICON_WIDTH   109
#define CLANHELPICON_HEIGHT   30
#define CLANHELPICON_CAP		 40
#define CLANHELPICON_START_Y   105
#define CLANHELPICON_DISPLAY_MAX		4
#define CLANHELPCONTENT_MARK_X   40
#define CLANHELPCONTENT_MARK_Y   40
#define CLANHELPCONTENT_X   100
#define CLANHELPCONTENT_Y   50
#define HELPWIDTH 256
#define HLEPDISPLAY_MAX		8
#define HELPCONTENT_X        19
#define HELPCONTENT_Y        56
#define HELPCONTENT_CAP      20
#define CLANCHIPHELPINF "image\\clanImage\\help\\ClanHelp.inf"
#define CLANUSERHELPINF "image\\clanImage\\help\\ClanUserHelp.inf"


#define SAVEDATA_DIR	"savedata"
#define CLANDATA_DIR   "savedata\\clanDATA"





#define BOXCORNER_WIDTH		64
#define BOXCORNER_HEIGHT		32
#define BOXCENTER_WIDTH		32
#define BOXCENTER_HEIGHT		32


#define CLANNAME_X			54  
#define CLANNAME_Y			12

#define CLANNAME_WIDTH		152
#define CLANNAME_HEIGHT		28

#define CLANNAMETEXT_X       128
#define CLANNAMETEXT_Y		20


#define CLANMARKBOX_X		93 
#define CLANMARKBOX_Y		47


#define CLANMARK_X		111
#define CLANMARK_Y		60


#define BUTTON1_BOX_X			104
#define BUTTON1_BOX_Y			222

#define BUTTON1_X				BUTTON1_BOX_X + 9
#define BUTTON1_Y				BUTTON1_BOX_Y + 4


#define BUTTON2_BOX_X			69
#define BUTTON2_BOX_Y			221

#define BUTTON2_X				BUTTON2_BOX_X + 9
#define BUTTON2_Y				BUTTON2_BOX_Y + 4

#define BUTTON3_BOX_X			139
#define BUTTON3_BOX_Y			221

#define BUTTON3_X				BUTTON3_BOX_X + 9
#define BUTTON3_Y				BUTTON3_BOX_Y + 4


#define CLANCHIPMENU_RELEASE_X	104
#define CLANCHIPMENU_RELEASE_y	62

#define CLANCHIPMENU_REMOVE_X		104
#define CLANCHIPMENU_REMOVE_Y		92


#define CLANCHIPMENU_LC_X		104
#define CLANCHIPMENU_LC_Y		122

#define CLANCHIPMENU_HELP_X		104
#define CLANCHIPMENU_HELP_Y		182

#define CLANCHIPMENU_SUBCHIP_X	104
#define CLANCHIPMENU_SUBCHIP_Y	152


#define CLANTITLE_X				68
#define CLANTITLE_Y				12


#define CLANHELPLIST_X			68
#define CLANHELPLIST_Y			76


#define CLANWONLIST_X			50
#define CLANWONLIST_Y			60


#define CLANUSER_SECESSION_X	64
#define CLANUSER_SECESSION_Y	127

#define CLANUSER_HELP_X			64
#define CLANUSER_HELP_Y			167


#define CLANMAKETEXT_X			25
#define CLANMAKETEXT_Y			40

#define LOADTEXT_X				70
#define LOADTEXT_Y				50


#define CLAN_RELEASE_X			60
#define CLAN_RELEASE_Y			80

#define CLAN_RECONF_RELEASE_X			30
#define CLAN_RECONF_RELEASE_Y			70

#define CLANNOMAKE_X		    30
#define CLANNOMAKE_Y		    60

#define CLANRELEASE_FINISH_X		50
#define CLANRELEASE_FINISH_Y		60

#define CLANUSERTEXT_X           45
#define CLANUSERTEXT_Y			60

#define CLANINPUTNAME_X			78
#define CLANINPUTNAME_Y			70







#define XCAP					20 
#define YDOWN					-2  
#define REMOVE_ICON				20 
#define WHR_ICON				30
#define HELP1					"image\\Sinimage\\chipbutton\\help1.txt"
#define HELPMSG_MAX				256
#define CLANMARK_TXT_X           34
#define CLANMARK_TXT_Y           10

#define CLANHELPTEXT_Y               25

#define CLANTEXT_IMAGE_X         68
#define CLANTEXT_IMAGE_Y          12
#define CLANTEXT_IMAGE_WIDTH         120
#define CLANTEXT_IMAGE_HEIGHT         30





#define CLANHELPICON_NUM		100




#define CHIP_BUTTON_X_MOVE		30
#define CHIP_BUTTON_Y_MOVE		20

#define MAKEMONEY 500000			
#define CLANCHIP_LEAVECLAN_MONEY	300000

#define ABILITY   10000 	        
#define CLAN_MAKELEVEL  40		


typedef struct
{
	int  ret_val;
	char ret_Buf[2048];


} ANSWERDATA;

typedef struct _tagMyClanInfoHeader
{
	char		ClanMark_Num[40];
	int		nClanMark;
	char		ClanName[40];
	char		ClanReport[90];
	char		Gserver[4];
	char		UniqueClaClanInfo_nNum[64];


}MYCLANINFOHEADER;


typedef struct
{
	HBITMAP hb;
	void *pixBuf;
	char fname[64];
} DIBSectionBUF;


typedef struct
{

	int  myPosition;

	int	 money;
	int  ability;






	char clanJoinID[64];
	char clanJoinCharID[64];
	int  clanJoinJob, clanJoinLevel;

	char chipCharID[64];


	char  szJoinClanName[64];
	char  szJoinClanChipName[64];



	char name[20];
	char explanation[128];


	char stats[2];
	char sec[30];
	char szRegiD[50];
	char  limitD[30];
	char  DelActive[10];
	char  gserver[30];
	char  szID[64];
	char  ChaName[64];
	char  ClanZang_ID[64];
	char  ClanZang_Name[64];
	char  ClanMark[64];

	int intClanMark;
	int nLastDay;
	BOOL bIsOneDay;
	int	nMinute;
	int	nHour;

	int nCurrentClanWon_Num;
	int nClanWon_Max;







	char  clanWon[CLANWON_MAX][30];
	int	 clanWonStrLen[41];
	char  szClanMarkName[50];
	int   nTotalClanWonCount;
	char  PFlag[5];
	char  LeaveClanFlag[5];
	int	 nKFlag;
	int   nKFlag_Count;
	char  OldChipChaName[64];
	char  SubChip[64];
	char	 OldSubChip[64];
	char	 isSubChip[2];


	smCHAR *TargetChar;


#ifdef USE_PROSTONTALE		
	LPDIRECT3DTEXTURE9	hClanMark;
	LPDIRECT3DTEXTURE9	hClanMark16;

#else
	HBITMAP				hClanMark;
	HBITMAP				hClanMark16;
#endif




	char  StartMessageFlag[1];



	DWORD CNFlag;
} CLANDATA;

typedef struct _tagClanWonList
{
	char  clanWon[CLANWON_MAX][30];

}CLANWONLIST;


typedef struct _tagHelpContent
{
	char szHelpContent[HELPWIDTH];
	BOOL bFlag;
}HELPCONTENTS;


typedef struct _tagClanHelpIcon
{
	char ImagePath[255];
	char ImagePath2[255];
	char ImagePath3[255];
	char TextFilePath[255];
}CLANHELPICON;

typedef struct _tagMenuBMP
{
	HBITMAP membmp;
}MENUBMP;

class CLAN_MENU
{
public:
	CLAN_MENU();
	~CLAN_MENU();




	int menu_joinOpen(char *chipCharID);
	int menu_joinOpen_Chip(int joinOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel);


	int IsCheckClanMember(smCHAR *pChar);



#ifdef USE_PROSTONTALE		
	int	MatPartyBackGround;

	int	hBox1, hBox2, hBox3, hBox4, hBox5, hBox6, hBox7, hBox8, hBox9;



	int	hScl_Bar_tj;
	int	hScl_icon_tj;





	char		szHelpMsg1[HELPMSG_MAX];
	char		szErrorMsg[256];

#else
	HBITMAP	hBox1, hBox2, hBox3, hBox4, hBox6, hBox7, hBox8, hBox9;

	HBITMAP	MatPartyBackGround;

	HBITMAP	hOk_Gray, hOk_Yellow;
	HBITMAP	hCancel_Gray, hCancel_Yellow;
	HBITMAP	hYes_Gray, hYes_Yellow;
	HBITMAP	hNo_Gray, hNo_Yellow;

	HBITMAP	hMark, hClanName;
	HBITMAP	hSecession[2];
	HBITMAP	hClose[2];
	HBITMAP	hIcon;
	HBITMAP   hIcon_Click;
	HBITMAP	hHelp1;
	HBITMAP	hClinetMark;
	HBITMAP	hServerMark;
	HBITMAP	hWareHouse[2];
	HBITMAP	hWHRight[2];
	HBITMAP	hClanMark[2];
	HBITMAP	hRemove[2];
	HBITMAP	hClanRelease[2];
	HBITMAP	hHelp[2];
	HBITMAP	hOut[2];
	HBITMAP	hButton_Box;
	HBITMAP	hClanTitle;
	HBITMAP	hRemoveToMenu[2];
	HBITMAP	hScl_Bar;
	HBITMAP	hScl_icon;
	HBITMAP   hClanHelpIcon[CLANHELPICON_NUM][4];

#ifndef _LANGUAGE_BRAZIL 
	HBITMAP   hTxt_Remove[2];
	HBITMAP   hTxt_Release[2];
#endif
	HBITMAP   hTxt_Mark[2];
	HBITMAP   hTxt_Help[2];
	HBITMAP   hTxt_Secession[2];


	char		szErrorMsg[256];

#endif


	int  nReleaseClanWon;


	int nScl_Bar;

	int g_HelpIconNumber;

	char szHelpContent[1024];




	char     szRemoveClanWonResultMsg[1024];
	char     szReconfReleaseMsg[2048];




	typedef struct _tagButtonClick
	{
		char szClanWon[20];
		BOOL bIsClick;
	}BUTTONCLICK;
	BUTTONCLICK buttonclick[30];
	BUTTONCLICK removeclick[30];
	int	nClanWon[40];

	char szRemoveClanWon[500];

	CLANHELPICON ClanHelpIcon[CLANHELPICON_NUM];

	MENUBMP *membmp;



	int MatTitle[4];

	int xLeft, xRight;


	RECT scrIconPos;

	void InitMenuSet(int menuN);
	int chk_readStrBuf(char *cmd, char *readbuf, char *retBuf);


	void Init();
	void NoticeMessage_Init();
	void Init2();
	void NoticeMessage_Init2();

	void Load();
	void Close();

	int	 Main(int sw);
	int	 Draw();
	int	 DrawBox(int x, int y, int x_width, int y_height);
	void menuInit(int num);
	void Draw_C_menuN();
	void Draw_C_Text(char *str, int x, int y, int sw);



	void RenderMenu();

	int chkMenu(int x, int y, RECT *r);
	int chkeckMenuN();
	void menuSet(int sw);



	int		nChkMark;



	int chkMark(char *clanName);

	void SetUserData(char* id, char* chaname, char* gserver, int money, int ability);

	void SetJoinData(char *joinclanname, char *joinclanchip);


	void clanCheckMark_main();

	void clanJoin_main();

	void Loading();

	void ClanJoin();

	void joinClanMember();





	void CLANmenu_INIT();
	int  CLANmenu_clanPOSITION();
	int  CLANmenu_meetNPC();

	void CLANmenu_ChatList(int sw);
	void CLANmenu_DeleteCha();


	void GuideHelpDraw();
};

typedef struct _tagClanMsg
{
	POINT pos;
	char szMsg[1024];
}CLANMSG;

void Draw_Text(int x, int y, char *str);
void Text_Out(HDC hdc, int x, int y, char *str);





#ifdef TJCLAN_CPP

CLAN_MENU	Interface_clanmenu;





ANSWERDATA ANSdata;

CLANDATA cldata;
CLANDATA chacldata[5];







CLANMSG clanMake1;
CLANMSG clanMake2;
CLANMSG clanMake3;
CLANMSG clanMake4;
CLANMSG clanMake5;
CLANMSG clanMake6;
CLANMSG clanMsg21;
CLANMSG clanMsg254;
CLANMSG clanMsg15;
CLANMSG clanJoin;
CLANMSG clanSecession;
CLANMSG clanServerConnectErrorMsg;
CLANMSG clanszError_Msg;
CLANMSG clanDeleteChaError;
CLANMSG clanCancelMakeClan;
CLANMSG clanClanNameError;
CLANMSG clanSecession6DownMsg;
CLANMSG clanClanJoinMsg;
CLANMSG clanClanJoinCancelMsg;
CLANMSG clanClanJoinsucesssMsg;
CLANMSG clanszReMoveClanWonMsg;
CLANMSG clanReMoveHeaderMsg;
CLANMSG clanszReConfReleaseMsg;
CLANMSG clanNoRecordReleaseMsg;
CLANMSG clanFinishReleaseMsg;
CLANMSG clanSecessionMsg;
CLANMSG clanFinishSecessionMsg;
CLANMSG clanisCheckClanJangErrorMsg;
CLANMSG clanMoneyErrorMsg;
CLANMSG clanAbilityErrorMsg;
CLANMSG clanszRemoveShortClanWonMsg;
CLANMSG clanNoName;
CLANMSG clanLoading;
CLANMSG clanMsg6;
CLANMSG clanMsg7;
CLANMSG clanClanWon6Down;
CLANMSG clanClanUserNoMakeMsg;
CLANMSG clanMakeFinishClanWon;
CLANMSG clanClanServerInspect;
CLANMSG clanClanUserRelease;
CLANMSG clanClanUserReleaseMsg;
CLANMSG clanClanMakedowninfo;
CLANMSG clanClanUserRemove;
CLANMSG clanClanWonOver;
CLANMSG clanNoLevel;
CLANMSG clanMakeFinishClan;
CLANMSG clanRemoveShowrtClanWonResultMsg;
CLANMSG clanRemoveSecond;
CLANMSG clanRemoveSecondResult;
CLANMSG LeaveClanConfirm;
CLANMSG LeaveClanNoMoney;
CLANMSG LeaveClanSuccess;
CLANMSG LeaveClanNoLevel;
CLANMSG LeaveClanReConfirm;
CLANMSG NoLeaveClan;
CLANMSG LeaveClanMessage;
CLANMSG LeaveClanDownLevel;
CLANMSG SubChipAppoint;
CLANMSG SubChipAppointEnd;
CLANMSG SubChipRelease;
CLANMSG SubChipReleaseEnd;
CLANMSG NoSubChip;


CLANMSG ClanIs4DayCheckMsg;


char szMsg1[CLANMESSAGEBUF_MAX];
char szMsg2[CLANMESSAGEBUF_MAX];
char szMsg21[CLANMESSAGEBUF_MAX];
char szMsg3[CLANMESSAGEBUF_MAX];
char szMsg4[CLANMESSAGEBUF_MAX];
char szMsg5[CLANMESSAGEBUF_MAX];
char szClanMakeFinishMsg[CLANMESSAGEBUF_MAX];
char szMsg254[CLANMESSAGEBUF_MAX];
char szMsg15[CLANMESSAGEBUF_MAX];
char szMark1[CLANMESSAGEBUF_MAX];
char szMark2[CLANMESSAGEBUF_MAX];
char szMark3[CLANMESSAGEBUF_MAX];
char szJoin[CLANMESSAGEBUF_MAX];
char szSecession[CLANMESSAGEBUF_MAX];
char szMsg6[CLANMESSAGEBUF_MAX];
char szServerConnectErrorMsg[CLANMESSAGEBUF_MAX];
char szReadClanMarkErrorMsg[CLANMESSAGEBUF_MAX];
char szCancelMakeClan[CLANMESSAGEBUF_MAX];
char szTranzationError[CLANMESSAGEBUF_MAX];
char szInsertClanWonError1[CLANMESSAGEBUF_MAX];
char szClanNameError[CLANMESSAGEBUF_MAX];
char sz100Error[CLANMESSAGEBUF_MAX];
char szDefaultError[CLANMESSAGEBUF_MAX];
char szReleseError[CLANMESSAGEBUF_MAX];
char szSecessionSuccess[CLANMESSAGEBUF_MAX];
char szSecession6DownMsg[CLANMESSAGEBUF_MAX];
char szSecessionChipMsg[CLANMESSAGEBUF_MAX];
char szSecession2ErrorMsg[CLANMESSAGEBUF_MAX];
char szClanJoinMsg[CLANMESSAGEBUF_MAX];
char szClanJoinError2Msg[CLANMESSAGEBUF_MAX];
char szClanJoinError3Msg[CLANMESSAGEBUF_MAX];
char szClanJoinError4Msg[CLANMESSAGEBUF_MAX];
char szClanJoinCancelMsg[CLANMESSAGEBUF_MAX];
char szClanJoinsucesssMsg[CLANMESSAGEBUF_MAX];
char szReMoveClanWonMsg[CLANMESSAGEBUF_MAX];
char szReMoveHeaderMsg[CLANMESSAGEBUF_MAX];
char szReConfReleaseMsg[CLANMESSAGEBUF_MAX];

char szNoRecordReleaseMsg[CLANMESSAGEBUF_MAX];
char szFinishReleaseMsg[CLANMESSAGEBUF_MAX];
char szSecessionMsg[CLANMESSAGEBUF_MAX];
char szFinishSecessionMsg[CLANMESSAGEBUF_MAX];
char szisCheckClanJangErrorMsg[CLANMESSAGEBUF_MAX];
char szMoneyErrorMsg[CLANMESSAGEBUF_MAX];
char szAbilityErrorMsg[CLANMESSAGEBUF_MAX];
char szRemoveShortClanWonMsg[CLANMESSAGEBUF_MAX];
char szRemoveShowrtClanWonResultMsg[CLANMESSAGEBUF_MAX];
char szNoName[CLANMESSAGEBUF_MAX];
char szLoading[CLANMESSAGEBUF_MAX];

char szDeleteChaReleaseBefore[CLANMESSAGEBUF_MAX];
char szDeleteChaReleaseFinish[CLANMESSAGEBUF_MAX];
char szDeleteChaSecessionBefore[CLANMESSAGEBUF_MAX];
char szDeleteChaSecessionFinish[CLANMESSAGEBUF_MAX];

char szDeleteChaError[CLANMESSAGEBUF_MAX];
char szMakeFinishClan[CLANMESSAGEBUF_MAX];
char szClanWon6Down[CLANMESSAGEBUF_MAX];
char szClanUserNoMakeMsg[CLANMESSAGEBUF_MAX];
char szMakeFinishClanWon[CLANMESSAGEBUF_MAX];
char ClanServerInspect[CLANMESSAGEBUF_MAX];
char szClanUserRelease[CLANMESSAGEBUF_MAX];
char Replay[CLANMESSAGEBUF_MAX];
char szClanMakedowninfo[CLANMESSAGEBUF_MAX];
char szClanUserReleaseMsg[CLANMESSAGEBUF_MAX];
char szClanUserRemove[CLANMESSAGEBUF_MAX];
char szClanWonOver[CLANMESSAGEBUF_MAX];
char szError_Msg[CLANMESSAGEBUF_MAX];
char szMsg7[CLANMESSAGEBUF_MAX];
char szNoLevel[CLANMESSAGEBUF_MAX];




int C_menuN;
int C_menuN2;
int CLAN_ERROR_ret;



int  nClanWon_Num;
POINT BackStartPos;
int g_HelpIconNumber;
HELPCONTENTS HelpContents[100];
int g_nClanIconNum;
int g_HelpDisPlay;
int g_HelpIConNumber;
RECT menuPos[30];
int		menuMouseOver[30];
int menuSu;
CLANHELPICON ClanHelpIcon[CLANHELPICON_NUM];
char szRemoveClanWonResult[5][64];
int keydownEnt = 0;
int TJwheel = 0;
int OpenFlag = 0;
char banisBuf1[64];
char banisBuf2[512];
int  banisCnt;

DIBSectionBUF Dback;
int joinAnswer;
BOOL bIsLoading = FALSE;
BOOL bOpenChatList = FALSE;
BOOL bIsReadData = FALSE;
int  ChatList_CmenuN = 0;
int	ChatList_CmenuN2 = 0;

int TJmb[3] = { 0,0,0 };
int TJmb2[3] = { 0,0,0 };

BOOL bCheckHostNameandPort = FALSE;
MYCLANINFOHEADER MyClanInfo;

CLANWONLIST ClanWonList;
BOOL		bcldataclanmark = FALSE;






int isDrawClanMenu = 0;

char  szChatClanWon[CLANWON_MAX][30];

#else	




extern BOOL		bcldataclanmark;
extern CLANWONLIST ClanWonList;
extern MYCLANINFOHEADER MyClanInfo;

extern BOOL bCheckHostNameandPort;
extern int TJmb[3];
extern int TJmb2[3];

extern int  ChatList_CmenuN;
extern int  ChatList_CmenuN2;
extern BOOL bIsReadData;
extern BOOL bOpenChatList;
extern BOOL bIsLoading;
extern int joinAnswer;
extern DIBSectionBUF Dback;







extern int TJwheel;
extern int menuSu;
extern HWND			g_hwnd;
extern POINT		pCursorPos;
extern HINSTANCE	g_hInst;

extern CLAN_MENU	Interface_clanmenu;
extern ANSWERDATA	ANSdata;
extern int OpenFlag;



extern    int C_menuN;
extern 	int C_menuN2;
extern 	int CLAN_ERROR_ret;
extern int  banisF[100];
extern char banisBuf1[64];
extern char banisBuf2[512];
extern int  banisCnt;
extern CLANDATA cldata;
extern CLANDATA chacldata[5];


extern int  nClanWon_Num;
extern POINT BackStartPos;
extern int g_HelpIconNumber;
extern HELPCONTENTS HelpContents[100];
extern int g_nClanIconNum;
extern int g_HelpDisPlay;
extern int g_HelpIConNumber;
extern RECT menuPos[30];
extern int		menuMouseOver[30];
extern int MouseButton[3];
extern CLANHELPICON ClanHelpIcon[CLANHELPICON_NUM];
extern char szRemoveClanWonResult[5][64];
#define MOUSE0() MouseButton[0]
extern int keydownEnt;



extern CLANMSG clanMake1;
extern CLANMSG clanMake2;
extern CLANMSG clanMake3;
extern CLANMSG clanMake4;
extern CLANMSG clanMake5;
extern CLANMSG clanMake6;


extern CLANMSG clanMsg21;
extern CLANMSG clanMsg254;
extern CLANMSG clanMsg15;
extern CLANMSG clanJoin;
extern CLANMSG clanSecession;
extern CLANMSG clanServerConnectErrorMsg;
extern CLANMSG clanszError_Msg;
extern CLANMSG clanDeleteChaError;
extern CLANMSG clanCancelMakeClan;
extern CLANMSG clanClanNameError;
extern CLANMSG clanSecession6DownMsg;
extern CLANMSG clanClanJoinMsg;
extern CLANMSG clanClanJoinCancelMsg;
extern CLANMSG clanClanJoinsucesssMsg;
extern CLANMSG clanszReMoveClanWonMsg;
extern CLANMSG clanReMoveHeaderMsg;
extern CLANMSG clanszReConfReleaseMsg;
extern CLANMSG clanNoRecordReleaseMsg;
extern CLANMSG clanFinishReleaseMsg;
extern CLANMSG clanSecessionMsg;
extern CLANMSG clanFinishSecessionMsg;
extern CLANMSG clanisCheckClanJangErrorMsg;
extern CLANMSG clanMoneyErrorMsg;
extern CLANMSG clanAbilityErrorMsg;
extern CLANMSG clanszRemoveShortClanWonMsg;
extern CLANMSG clanNoName;
extern CLANMSG clanLoading;
extern CLANMSG clanMsg6;
extern CLANMSG clanMsg7;
extern CLANMSG clanClanWon6Down;
extern CLANMSG clanClanUserNoMakeMsg;
extern CLANMSG clanMakeFinishClanWon;
extern CLANMSG clanClanServerInspect;
extern CLANMSG clanClanUserRelease;
extern CLANMSG clanClanUserReleaseMsg;
extern CLANMSG clanClanMakedowninfo;
extern CLANMSG clanClanUserRemove;
extern CLANMSG clanClanWonOver;
extern CLANMSG clanNoLevel;
extern CLANMSG clanMakeFinishClan;
extern CLANMSG clanRemoveShowrtClanWonResultMsg;
extern CLANMSG clanRemoveSecond;
extern CLANMSG clanRemoveSecondResult;
extern CLANMSG LeaveClanConfirm;
extern CLANMSG LeaveClanNoMoney;
extern CLANMSG LeaveClanSuccess;
extern CLANMSG LeaveClanNoLevel;
extern CLANMSG LeaveClanReConfirm;
extern CLANMSG NoLeaveClan;
extern CLANMSG LeaveClanMessage;
extern CLANMSG LeaveClanDownLevel;
extern CLANMSG SubChipAppoint;
extern CLANMSG SubChipAppointEnd;
extern CLANMSG SubChipRelease;
extern CLANMSG SubChipReleaseEnd;
extern CLANMSG NoSubChip;


extern CLANMSG ClanIs4DayCheckMsg;


extern char szMsg1[CLANMESSAGEBUF_MAX];
extern char szMsg2[CLANMESSAGEBUF_MAX];
extern char szMsg21[CLANMESSAGEBUF_MAX];
extern char szMsg3[CLANMESSAGEBUF_MAX];
extern char szMsg4[CLANMESSAGEBUF_MAX];
extern char szMsg5[CLANMESSAGEBUF_MAX];
extern char szMsg6[CLANMESSAGEBUF_MAX];
extern char sz100Error[CLANMESSAGEBUF_MAX];
extern char szAbilityErrorMsg[CLANMESSAGEBUF_MAX];
extern char szCancelMakeClan[CLANMESSAGEBUF_MAX];
extern char szMsg254[CLANMESSAGEBUF_MAX];
extern char szClanMakeFinishMsg[CLANMESSAGEBUF_MAX];
extern char szMsg15[CLANMESSAGEBUF_MAX];
extern char szMark1[CLANMESSAGEBUF_MAX];
extern char szMark2[CLANMESSAGEBUF_MAX];
extern char szMark3[CLANMESSAGEBUF_MAX];
extern char szJoin[CLANMESSAGEBUF_MAX];
extern char szSecession[CLANMESSAGEBUF_MAX];
extern char szServerConnectErrorMsg[CLANMESSAGEBUF_MAX];
extern char szReadClanMarkErrorMsg[CLANMESSAGEBUF_MAX];
extern char szTranzationError[CLANMESSAGEBUF_MAX];
extern char szInsertClanWonError1[CLANMESSAGEBUF_MAX];
extern char szClanNameError[CLANMESSAGEBUF_MAX];
extern char szDefaultError[CLANMESSAGEBUF_MAX];
extern char szReleseError[CLANMESSAGEBUF_MAX];
extern char szSecessionSuccess[CLANMESSAGEBUF_MAX];
extern char szSecession6DownMsg[CLANMESSAGEBUF_MAX];
extern char szSecessionChipMsg[CLANMESSAGEBUF_MAX];
extern char szSecession2ErrorMsg[CLANMESSAGEBUF_MAX];
extern char szClanJoinMsg[CLANMESSAGEBUF_MAX];
extern char szClanJoinError2Msg[CLANMESSAGEBUF_MAX];
extern char szClanJoinError3Msg[CLANMESSAGEBUF_MAX];
extern char szClanJoinError4Msg[CLANMESSAGEBUF_MAX];
extern char szClanJoinCancelMsg[CLANMESSAGEBUF_MAX];
extern char szClanJoinsucesssMsg[CLANMESSAGEBUF_MAX];
extern char szReMoveClanWonMsg[CLANMESSAGEBUF_MAX];
extern char szReMoveHeaderMsg[CLANMESSAGEBUF_MAX];
extern char szReConfReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szNoRecordReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szFinishReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szSecessionMsg[CLANMESSAGEBUF_MAX];
extern char szFinishSecessionMsg[CLANMESSAGEBUF_MAX];
extern char szisCheckClanJangErrorMsg[CLANMESSAGEBUF_MAX];
extern char szMoneyErrorMsg[CLANMESSAGEBUF_MAX];
extern char szRemoveShortClanWonMsg[CLANMESSAGEBUF_MAX];
extern char szRemoveShowrtClanWonResultMsg[CLANMESSAGEBUF_MAX];
extern char szClanUserNoMakeMsg[CLANMESSAGEBUF_MAX];
extern char szNoName[CLANMESSAGEBUF_MAX];
extern char szLoading[CLANMESSAGEBUF_MAX];

extern char szDeleteChaReleaseBefore[CLANMESSAGEBUF_MAX];
extern char szDeleteChaReleaseFinish[CLANMESSAGEBUF_MAX];
extern char szDeleteChaSecessionBefore[CLANMESSAGEBUF_MAX];
extern char szDeleteChaSecessionFinish[CLANMESSAGEBUF_MAX];

extern char szDeleteChaError[CLANMESSAGEBUF_MAX];
extern char szMakeFinishClan[CLANMESSAGEBUF_MAX];
extern char szClanWon6Down[CLANMESSAGEBUF_MAX];
extern char szMakeFinishClanWon[CLANMESSAGEBUF_MAX];
extern char ClanServerInspect[CLANMESSAGEBUF_MAX];
extern char szClanUserRelease[CLANMESSAGEBUF_MAX];
extern char Replay[CLANMESSAGEBUF_MAX];
extern char szClanMakedowninfo[CLANMESSAGEBUF_MAX];
extern char szClanUserReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szClanUserRemove[CLANMESSAGEBUF_MAX];
extern char szClanWonOver[CLANMESSAGEBUF_MAX];
extern char szError_Msg[CLANMESSAGEBUF_MAX];

extern char szMsg7[CLANMESSAGEBUF_MAX];
extern char szNoLevel[CLANMESSAGEBUF_MAX];

extern int ClanCharMove;
extern int ClanCLCharMove;




extern int isDrawClanMenu;



extern int ktj_imsiDRAWinfo;



extern char  szChatClanWon[CLANWON_MAX][30];


#endif


void ClanJoin(char *oneClanName, char *oneChipCharid);
void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID);
void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel);


void g_IsCheckClanMember(smCHAR *pChar);


void Updatecldata();




int ReadClanInfo(DWORD dwClanNum);
int ReadClanInfo_32X32(DWORD dwClanNum);









void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1);
void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1, int ticket);




void CLANmenu_DeleteCha_SetCharacter(char *id, char *gserver, char *chaname);



extern int usehFocus;




int TJBscrollWheel(int wheel);



int chatlistSPEAKERflag();
void chatlistSPEAKERflagChg(int flag);









int GetNoticeUrl(char *url);








#ifdef TJCLAN_CPP


#ifndef USE_PROSTONTALE		


extern HWND    g_hwnd;
/
	: 함수  명 : HBITMAP MakeDIBSection(char *Path)
	: 하는  일 :
: 인    자 : bmp파일을읽어서  DIB 섹션을 만들어 핸들을 리턴한다.
	: 반환  값 :

HBITMAP MakeDIBSection(DIBSectionBUF *Dibbuf)
{
	HANDLE hFile;
	DWORD FileSize, dwRead;
	BITMAPFILEHEADER fh;
	HBITMAP hBit;
	BITMAPINFO *ih;
	PVOID pRaster;


	hFile = CreateFile(Dibbuf->fname, GENERIC_READ, 0, NULL,
					   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}


	ReadFile(hFile, &fh, sizeof(BITMAPFILEHEADER), &dwRead, NULL);
	FileSize = fh.bfOffBits - sizeof(BITMAPFILEHEADER);
	ih = (BITMAPINFO *)malloc(FileSize);
	ReadFile(hFile, ih, FileSize, &dwRead, NULL);



	hBit = CreateDIBSection(NULL, ih, DIB_RGB_COLORS, &pRaster, NULL, 0);

	if(Dibbuf != NULL)
	{
		Dibbuf->hb = hBit;
		Dibbuf->pixBuf = (void *)pRaster;
	}



	ReadFile(hFile, pRaster, fh.bfSize - fh.bfOffBits, &dwRead, NULL);
	free(ih);
	CloseHandle(hFile);

	return hBit;
}

void window_renderINIT()
{
	static cnt = 0;
	if(cnt != 0) return;
	cnt = 1;

	Dback.hb = 0;
	Dback.pixBuf = 0;
	wsprintf(Dback.fname, "stg0.bmp");
	MakeDIBSection(&Dback);
}

void window_renderFLIP()
{
	HDC hdc, sorDC;
	hdc = GetDC(g_hwnd);
	sorDC = CreateCompatibleDC(hdc);
	SelectObject(sorDC, Dback.hb);


	BitBlt(hdc, 0, 0,
		   800, 600,
		   sorDC, 0, 0, SRCCOPY);

	DeleteDC(sorDC);

	ReleaseDC(g_hwnd, hdc);





}
#endif


#endif


void CheckMsgPos(CLANMSG* clanmsg, int width, int height);
void DebugMessage(char* msg, ...);
void InitHelp();
void GoNotice();
int GetNoticeUrl(char *url);

extern int GoNotice_chking;

