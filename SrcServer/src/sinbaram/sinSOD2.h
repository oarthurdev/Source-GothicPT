

#ifndef _SINSOD2_HEADER_

#define _SINSOD2_HEADER_
#include <vector>
#include <string>
#include <algorithm>

#define SIN_CLANSKILL_ABSORB			1
#define SIN_CLANSKILL_DAMAGE			2
#define SIN_CLANSKILL_EVASION			3

#define SIN_SODSKILL_GOLD			1
#define SIN_SODSKILL_SILVER			2
#define SIN_SODSKILL_BRONZE			3

#define SIN_GURAD_CRISTAL_ICE		    1
#define SIN_GURAD_CRISTAL_LIGHTNING		2
#define SIN_GURAD_CRISTAL_FIRE			3

#define SIN_CASTLEITEMSKILL_S_INVU         1    
#define SIN_CASTLEITEMSKILL_S_CRITICAL     2    
#define SIN_CASTLEITEMSKILL_S_EVASION      3    
#define SIN_CASTLEITEMSKILL_S_P_LIFE       4    
#define SIN_CASTLEITEMSKILL_S_RES          5    

#define SIN_CASTLEITEMSKILL_R_FIRE_C       6    
#define SIN_CASTLEITEMSKILL_R_ICE_C        7    
#define SIN_CASTLEITEMSKILL_R_LIGHTING_C   8    
#define SIN_CASTLEITEMSKILL_A_FIGHTER      9    
#define SIN_CASTLEITEMSKILL_A_MECHANICIAN  10   
#define SIN_CASTLEITEMSKILL_A_PIKEMAN      11   
#define SIN_CASTLEITEMSKILL_A_ARCHER       12   
#define SIN_CASTLEITEMSKILL_A_KNIGHT       13   
#define SIN_CASTLEITEMSKILL_A_ATALANTA     14   
#define SIN_CASTLEITEMSKILL_A_MAGICIAN     15   
#define SIN_CASTLEITEMSKILL_A_PRIESTESS    16   


class cSINSIEGE
{

public:
	int            TaxRate;
	int            TotalTax;
	int			   ExpectedTotalTax;
	int            Price;
public:
	short		   TowerType[6];
	int			   ClanSkill;
	unsigned char  MercenaryNum[4];
	int            TowerTypeDraw[6][2];
	int            MercenaryNumDraw;


public:
	cSINSIEGE()
	{
	};
	~cSINSIEGE()
	{
	};

	int GetTaxRate();
	int	SetTaxRate(int TempTaxRate);

	int GetTotalTax();
	int cSINSIEGE::GetTaxMoney(int Money);


};


struct sinMESSAGEBOX_NEW
{
	int Flag;
	int PosiX;
	int PosiY;
	int SizeW;
	int SizeH;



	int ButtonIndex;
	int ButtonNum;
	int ButtonintPosiX[3];
	int ButtonintPosiY[3];
	RECT ButtonRect[3];

};


class cSINSOD2
{

public:
	int UserType;
	int BoxIndex;
	char sinSod2Buff[65536];
	DIRECTDRAWSURFACE ClanMark[10];
	DIRECTDRAWSURFACE ClanMark_32;
	int  ClanMark_32Time;
	int  ClanMark_32Index;
	int  ClanMarkNum[10];
	int  ClanMarkIndex[10];
	int  ClanMarkLoadTime[10];
	int  TotalEMoney;
	int  Tax;
	int  TotalMoney;
	int  ClanImageNum;
	vector<string> sinClanRank;
	char szClanName[32];
	vector<string> sinClanMessage;

	int SendClanMoneyFlag;
	int RecvRemainMoney;
	char szClanMaster[24];
	int ClanMasterMessageBoxFlag;
	int ClanRankFlag;


	DWORD ClanMoney;

public:
	cSINSOD2()
	{
	};
	~cSINSOD2()
	{
	};

	void Init();
	void Load();
	void Release();
	void Draw();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
	void DrawText();
	void Close();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();


	void ShowSod2MessageBox();

	void CloseSod2MessageBox();

	void RecvWebDaTa();

	void RecvClanRank(char *szBuff);


	vector<string> Split_ClanRankDaTa(const string& s);


	vector<string> Split_ClanMessage(const string& s, const int Len[]);


	int RecvWebData(int Index, const string& s);


	vector<string> cSINSOD2::Split_Sod2DaTa(const string& s);

};


int ShowSinMessageBox_New(int PosiX, int PosiY, int SizeW, int SizeH, RECT *rect, int ButtonNum = 3);


int sinRecvClanMoney(int RemainMoney, int GetMoney);




int sinShowSeigeMessageBox();
int RecvSeigeWebData(int Index, char *string);



#define HASIEGE_MODE   


#define HASIEGE_TAXRATES    1  
#define HASIEGE_DEFENSE     2  



#define HACLAN_MAX    10   


struct sHACLANDATA
{
	int		Flag;
	int		Score;
	int     ClanInfoNum;
	char    ClanName[40];

	DWORD   CLANCODE;

	DIRECTDRAWSURFACE lpClanMark;
};

class cHASIEGE
{

public:

	int   ShowSiegeMenu(smTRANS_BLESSCASTLE *);
	int   ShowSiegeScore(rsUSER_LIST_TOP10 *);
	int   ShowExitMessage();
	int   ShowPlayTime(int);


	int   SetClanSkill(int);
	int   SetCastleItemSkill(int);

	int   SendServerSiegeData();
	int   SetCastleInit();
	int   SetCastleMenuInit();

	int	  ShowPickUserKillPoint(int x, int y, int KillCount);


	int   ShowCastlePlayMovie(char *szPath, char *TitleName, int Option);


public:

	cHASIEGE();
	~cHASIEGE();

	void init();
	void Main();
	void Draw();
	void KeyDown();
	void Release();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void DrawText();
	void ImageLoad();

public:
	DIRECTDRAWSURFACE  lpSiegeTax;
	DIRECTDRAWSURFACE  lpSiegeDefense;
	DIRECTDRAWSURFACE  lpCastleButton;
	DIRECTDRAWSURFACE  lpMercenary;


	DIRECTDRAWSURFACE  lpDefenseButton[2];
	DIRECTDRAWSURFACE  lpTax_Ok[2];

	DIRECTDRAWSURFACE  lpSiegeDefeseIcon_[3];
	DIRECTDRAWSURFACE  lpSiegeMercenaryIcon_[3];


	DIRECTDRAWSURFACE  lpSiegeDefeseIcon[3];
	DIRECTDRAWSURFACE  lpSiegeClanskillIcon[3];
	DIRECTDRAWSURFACE  lpSiegeMercenaryIcon[3];

	DIRECTDRAWSURFACE  lpSiegeTaxButton;
	DIRECTDRAWSURFACE  lpSiegeDefenseButton;
	DIRECTDRAWSURFACE  lpSiegeOkButton;
	DIRECTDRAWSURFACE  lpSiegeCancelButton;

	DIRECTDRAWSURFACE  lpCastleIcon[6];
	DIRECTDRAWSURFACE  lpTaxScroll[2];
	DIRECTDRAWSURFACE  lpTaxGraph;
	DIRECTDRAWSURFACE  lpDefenseRect[6];

	DIRECTDRAWSURFACE  lpTwoerImage;


	DIRECTDRAWSURFACE haPlayerButton_G[3];
	DIRECTDRAWSURFACE haPlayerButton[3];
	DIRECTDRAWSURFACE haPlayerButtonBox[3];
	DIRECTDRAWSURFACE haPlayerButtonDown[3];
};




extern cHASIEGE chaSiege;
extern int haSiegeMenuFlag;
extern int haMercenrayIndex;
extern int HaTestMoney;
extern int haMercenrayMoney[3];
extern int haSiegeBoardFlag;
extern int haSendTowerIndex;
extern int haTowerMoney;
extern int haMovieFlag;


extern cSINSOD2 cSinSod2;
extern sinMESSAGEBOX_NEW sinMessageBox_New;
extern DIRECTDRAWSURFACE	lpbltr_Button_OK;
extern DIRECTDRAWSURFACE	lpbltr_Button_OK_G;
extern int haCastleSkillUseFlag;
extern cSINSIEGE cSinSiege;

#endif

