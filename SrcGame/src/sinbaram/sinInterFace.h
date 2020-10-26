


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

	LPDIRECT3DTEXTURE9    lpEXP;
	LPDIRECT3DTEXTURE9    lpMP;
	LPDIRECT3DTEXTURE9    lpLIFE;
	LPDIRECT3DTEXTURE9    lpSTM;
	LPDIRECT3DTEXTURE9    lpANGER;

	LPDIRECT3DTEXTURE9    lpLIFESpot;
	LPDIRECT3DTEXTURE9    lpSTMSpot;
	LPDIRECT3DTEXTURE9    lpMANASpot;

	LPDIRECT3DTEXTURE9    lpButton[6];
	LPDIRECT3DTEXTURE9    lpButton2[6];

	LPDIRECT3DTEXTURE9    lpMenuButton[3];

	LPDIRECT3DTEXTURE9    lpInfoBox[6];
	LPDIRECT3DTEXTURE9    lpWalk;

	LPDIRECT3DTEXTURE9    lpRunInfo;
	LPDIRECT3DTEXTURE9    lpWalkInfo;

	LPDIRECT3DTEXTURE9    lpCameraAutoInfo;
	LPDIRECT3DTEXTURE9    lpCameraHandInfo;
	LPDIRECT3DTEXTURE9    lpCameraFixInfo;

	LPDIRECT3DTEXTURE9    lpMapOnInfo;
	LPDIRECT3DTEXTURE9    lpMapOffInfo;

	LPDIRECT3DTEXTURE9    lpChatShowButton;

	LPDIRECT3DTEXTURE9    lpSun;
	LPDIRECT3DTEXTURE9    lpMoon;

	LPDIRECT3DTEXTURE9    lpGage[2];

	LPDIRECT3DTEXTURE9	lpBar_Anger;
	LPDIRECT3DTEXTURE9	lpBar_Time;
	LPDIRECT3DTEXTURE9	lpBar_Exp;
	LPDIRECT3DTEXTURE9	lpBar_ExpWon;

	LPDIRECT3DTEXTURE9	lpButton_Anger;

	LPDIRECT3DTEXTURE9	lpMapOnImage;
	LPDIRECT3DTEXTURE9	lpCameraImage[2];

	LPDIRECT3DTEXTURE9	lpReStartMain;
	LPDIRECT3DTEXTURE9	lpReStartButton[3];

	LPDIRECT3DTEXTURE9	lpSelectSkill_Main[2];
	LPDIRECT3DTEXTURE9	lpSelectChangeJob[2];

	LPDIRECT3DTEXTURE9	lpTime7;


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


