
#define MAX_CHAR_RECT_POSI			31 

#define POINT_STRENGTH				1
#define POINT_SPIRIT				2
#define POINT_TALENT				3
#define POINT_DEXTERITY				4
#define POINT_HEALTH				5


#define SIN_TEXT_COLOR_WHITE		0
#define SIN_TEXT_COLOR_RED			1
#define SIN_TEXT_COLOR_YELLOW		2
#define SIN_TEXT_COLOR_BLUE			3
#define SIN_TEXT_COLOR_GREEN		4
#define SIN_TEXT_COLOR_GOLD			5
#define SIN_TEXT_COLOR_ORANGE		6
#define SIN_TEXT_COLOR_PINK			7


struct sCHARRECTPOSI
{

	char Para[64];
	RECT Rect;

};

struct sDISPLAYSTATE
{
	short Damage[2];
	short PercentDamage[2];
	int   Absorb;
	int   Attack_Rate;
	int   Defense;
	DWORD   MaxTime;
	DWORD   Time;
	int   Flag;
};

class cCHARSTATUS
{

public:
	int OpenFlag;
	int MatStatus[4];

	LPDIRECT3DTEXTURE9    lpRegiBox[5];
	LPDIRECT3DTEXTURE9    lpChangeArrow[2];
	LPDIRECT3DTEXTURE9    lpSelectArrow[2];
	LPDIRECT3DTEXTURE9	lpStatusPoint;


public:
	cCHARSTATUS();
	~cCHARSTATUS();

	void Init();
	void Load();
	void Release();
	void Close();
	void Draw();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();

	void OtherStateShow();

	void DrawCharText();

	void CheckLevel();

	void BackUpsinCharState(smCHAR *pChar);

	int sinGetNowExp();

	int sinGetNextExp();

	int InitCharStatus(int kind = 0);

	int InitCharStatus_Attribute(int kind);

	int UseGravityScrool();

	int CheckChageStateDisplay();

};

extern cCHARSTATUS cCharStatus;

extern int sinMoveKindInter[MAX_SIN_KIND_INTER];

extern int OldLevel;
extern int sinLevelPoint;
extern int OldLevelTemp;

extern  int TempNewCharacterInit[5][6];
extern  int MorNewCharacterInit[5][6];
extern  sDISPLAYSTATE sDisplayState[10];

extern  int ChatKindIndexNum;
extern  int NoticeChatIndexNum;
extern  int NoticeChatIndex;

extern INT64 ExpLevelTable[];


