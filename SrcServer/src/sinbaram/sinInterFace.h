


#define		RESTART_FEILD		1
#define		RESTART_TOWN		2
#define		RESTART_EXIT		3


#define     HA_DEFANCE			1
#define     HA_BLOCK			2
#define     HA_EVASION			3


struct sRUNCAMERAMAP
{

	int RunFlag;
	int CameraAutoFlag;
	int MapOnFlag;



};


struct sSHADOWSTATE
{
	int Flag;
	int Time;
	POINT Posi;
	POINT Size;
	DWORD Color;

};


class cINTERFACE
{

public:

	sRUNCAMERAMAP	sInterFlags;


	int MatMain;
	int MatMenu[2];
	int MatChatDefault[2];
	int MatChatSmall[2];
	int MatChatDoc[2];
	int MatExitMenu;
	int MatComPass;

	int MatLife;
	int MatMana;
	int MatStamina;

	DIRECTDRAWSURFACE    lpEXP;
	DIRECTDRAWSURFACE    lpMP;
	DIRECTDRAWSURFACE    lpLIFE;
	DIRECTDRAWSURFACE    lpSTM;
	DIRECTDRAWSURFACE    lpANGER;

	DIRECTDRAWSURFACE    lpLIFESpot;
	DIRECTDRAWSURFACE    lpSTMSpot;
	DIRECTDRAWSURFACE    lpMANASpot;

	DIRECTDRAWSURFACE    lpButton[6];
	DIRECTDRAWSURFACE    lpButton2[6];

	DIRECTDRAWSURFACE    lpMenuButton[3];

	DIRECTDRAWSURFACE    lpInfoBox[6];
	DIRECTDRAWSURFACE    lpWalk;

	DIRECTDRAWSURFACE    lpRunInfo;
	DIRECTDRAWSURFACE    lpWalkInfo;

	DIRECTDRAWSURFACE    lpCameraAutoInfo;
	DIRECTDRAWSURFACE    lpCameraHandInfo;
	DIRECTDRAWSURFACE    lpCameraFixInfo;

	DIRECTDRAWSURFACE    lpMapOnInfo;
	DIRECTDRAWSURFACE    lpMapOffInfo;

	DIRECTDRAWSURFACE    lpChatShowButton;

	DIRECTDRAWSURFACE    lpSun;
	DIRECTDRAWSURFACE    lpMoon;

	DIRECTDRAWSURFACE    lpGage[2];

	DIRECTDRAWSURFACE	lpBar_Anger;
	DIRECTDRAWSURFACE	lpBar_Time;
	DIRECTDRAWSURFACE	lpBar_Exp;
	DIRECTDRAWSURFACE	lpBar_ExpWon;

	DIRECTDRAWSURFACE	lpButton_Anger;

	DIRECTDRAWSURFACE	lpMapOnImage;
	DIRECTDRAWSURFACE	lpCameraImage[2];

	DIRECTDRAWSURFACE	lpReStartMain;
	DIRECTDRAWSURFACE	lpReStartButton[3];

	DIRECTDRAWSURFACE	lpSelectSkill_Main[2];
	DIRECTDRAWSURFACE	lpSelectChangeJob[2];

	DIRECTDRAWSURFACE	lpTime7;


	int MatClock;
	int ChatFlag;

public:
	cINTERFACE();
	~cINTERFACE();

	void Init();
	void Load();
	void Release();
	void Close();
	void Draw();
	void resize();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();


	void InitState();
	void CheckingState();
	void ShowParaState();

	void DrawInterText();

	void CheckAllBox(int ButtonFlag);

	int DrawClockArrow(int x, int y, int Angle);
	int DrawCompass(int x, int y, int Angle);


	int CheckExpPercentControl();




	int GetWordTimeDisplay();

	void ShowExpPercent();

	int  SetStringEffect(int);

};

extern cINTERFACE	cInterFace;

extern POINT InfoMessageBoxPos;


extern int sinChatEnter;
extern int SubChatHeight;
extern int sinChatDisplayMode;
extern int sinChatInputMode;


extern int sinFireShow;
extern int ExitButtonClick;

extern int ReStartFlag;
extern int ReStartOptionIndex;

extern int SkillNpcFlag;
extern int SkillMasterOptionIndex;

extern int RestartCheckExp;


extern int psDrawTexImage2(smTEXTUREHANDLE *hTexHandle, float *x, float *y, float fx, float fy, float fw, float fh, int Transp, int specular);

extern int NotUseSkillEffect[3];

extern int ChangeJobButtonclick;

extern int  ResetQuset3Flag;

extern int ReStartFlag;
extern POINT ReStartMainXY;
extern int ReStartIndex;
extern POINT ReStartTextXY;
extern char szReStartMsg[128];
extern char szReStartMsg2[128];


