

#define SIN_MAX_HELP_NUMBER		10		
#define SIN_HELP_KIND_NORMAL		1		
#define SIN_HELP_KIND_QUEST			2		
#define SIN_HELP_KIND_SMASHTV		3		
#define SIN_HELP_KIND_POSTBOX		4		
#define SIN_HELP_KIND_SOD			5		
#define SIN_HELP_KIND_QUEST_WING	6		
#define SIN_HELP_KIND_WARPGATE		7		
#define SIN_HELP_KIND_INITPOINT		8		
#define SIN_HELP_KIND_BABEL			9		
#define SIN_HELP_KIND_Q_LEVEL30		10		
#define SIN_HELP_KIND_Q_LEVEL55		11		
#define SIN_HELP_KIND_Q_LEVEL55_2	12		
#define SIN_HELP_KIND_Q_LEVEL70		13		
#define SIN_HELP_KIND_Q_LEVEL80		14		
#define SIN_HELP_KIND_Q_LEVEL85		15		
#define SIN_HELP_KIND_Q_LEVEL90		16		
#define SIN_HELP_KIND_TELEPORT		17		
#define SIN_HELP_KIND_Q_LEVEL80_2	18		
#define SIN_HELP_KIND_Q_LEVEL90_2	19		
#define SIN_HELP_KIND_C_TELEPORT    20      
#define SIN_HELP_KIND_RESEARCH      21      
#define SIN_HELP_KIND_TELEPORT_SCROLL   22      
#define SIN_HELP_KIND_TELEPORT_MILTER	23	
#define SIN_HELP_KIND_TRADEBPEXP 27
#define SIN_HELP_KIND_BATTLE_ARENA 28
#define SIN_HELP_KIND_QUEST_DIARY 29



#define SIN_HELP_COLOR_RED		1		
#define SIN_HELP_COLOR_YELLOW	2
#define SIN_HELP_COLOR_GREEN	3
#define SIN_HELP_COLOR_BLUE		4


#define TONY_TGA				1
#define TONY_BMP				2



#define SIN_MESSAGE_DEFAULT		98
#define SIN_HELP				99	
#define SIN_CHANGEJOB_MESSAGE	100
#define SIN_EVENT_SMASHTV		101
#define SIN_POST_BOX			102
#define SIN_SOD					103




struct sSINHELP_BOX
{
	int Mat;
	float x, y, w, h;
	float surW, surH;
	float tLeft, tTop, tRight, tBottom;
	int Transp;

};

struct sSINHELP
{
	int KindFlag;
	int PosiX, PosiY;
	int SizeW, SizeH;
	DWORD BackColor;
	sSINHELP_BOX *sHelp_Box[20][20];
	int MatFlag[20][20];


	int LineCnt;
	char *szDocBuff[100];


	int		ScrollFlag;
	POINT	ScrollButton;
	POINT	ScrollMousePosi;
	int		ScrollMAXPosiY_UP;
	int		ScrollMAXPosiY_DOWN;
	int		ScrollMouseDownFlag;


	POINT	TitlePosi;
	int		ButtonOkFlag;
	POINT	ButtonPosi;
	int		ButtonShowFlag;


	int    Code;

};

struct sTONY_TEST_IMAGE
{
	int Flag;
	char ImageFileName[64];
	POINT	Posi;
	POINT	Size;
	DWORD   BackColor;
	POINT	BackPosi;
	POINT	BackSize;
	int		FileFormat;

	int		Mat;
	LPDIRECT3DTEXTURE9 lpTony;

};

struct sSOD_RANK
{
	int		Flag;
	int		Job;
	char	Name[64];
	int		Score;
	int		KillNum;

};

struct shaResearch
{
	int   Result[10];
	int   Index;
	int   Value[10];
	int   Number;
	BYTE  bSendPollingData[10];
	POINT ButtonPosi;
	int   ButtonShowFlag;
};

class cSINHELP
{

public:
	int MatHelpCorner;
	int MatHelpLine;

	int MatScrollBar;
	int MatScrollButton;

	LPDIRECT3DTEXTURE9	lpHelpTitle;
	LPDIRECT3DTEXTURE9	lpChangeJobTitle;
	LPDIRECT3DTEXTURE9	lpHelpOk;
	LPDIRECT3DTEXTURE9	lpSodMenu;
	LPDIRECT3DTEXTURE9	lpSodLine;
	LPDIRECT3DTEXTURE9	lpSodJobFace[10];

	DWORD dwQuestWindowImage;



public:
	int                     ScrollLineCount;
	int                     NPCTeleportFlag;

public:

	cSINHELP();
	~cSINHELP();

	void Init();
	void Load();
	void Release();
	void Draw();
	void DrawText();
	void Close();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();


	int sinShowHelp(int Kind, int PosiX, int PosiY, int SizeW, int SizeH, DWORD BackColor, char *File);

	int sinReadFileData(char *name);


	int sinReadFileDataDivide(char *SaveBuf, int Linelen, int Size);


	int TonyGetFileData();


	int sinGetScrollMove(int Num);
	int sinGetKeyScrollDown();


	int sinGetHelpShowFlag();


	int ShowSodRanking(TRANS_SOD_RESULT *SodResult, int MyGame = 0);


	int GetSodRankBoxState();



	int ShowResearchMenu(int Kind, int Flag);


	int SendResearch();


	int sinGetHelpShowFlagNum();
};
int TeleportDungeon();
int haShowCastleTeleportMap();
int sinShowTeleportMap();
int sinShowHelp();
int sinDrawTexImage(int Mat, float x, float y, float w, float h, float surW = 0.0f, float surH = 0.0f, float tLeft = 0.0f, float tTop = 0.0f, float tRight = 0.0f, float tBottom = 0.0f, int Transp = 255);
extern sSINHELP sSinHelp[SIN_MAX_HELP_NUMBER];
extern cSINHELP cSinHelp;
extern int HelpBoxKindIndex;
extern int WingItemQuestIndex;
extern int MatHelpBoxImage[10];
extern int sinTeleportIndex;
extern int sinTeleportMoneyIndex;
extern int TeleportUseCose[];
extern int haC_TeleportMoney;
extern char *haC_Not_TeleportFilePath;
extern int haTeleport_PageIndex;


