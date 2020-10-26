

#define		 SINLBUTTONDOWN			10
#define		 SINLBUTTONUP 			11
#define		 SINRBUTTONDOWN			110
#define		 SINRBUTTONUP 			111

#define		 SINMOUSEMOVE			2
#define		 SINKEYDOWN				3

#define		 SIN_CURSOR_DEFAULT		1
#define		 SIN_CURSOR_SELL		2
#define		 SIN_CURSOR_BUY			3
#define		 SIN_CURSOR_REPAIR		4
#define		 SIN_CURSOR_ALLREPAIR	5
#define		 SIN_CURSOR_ATTACK		6
#define		 SIN_CURSOR_GETITEM1	7
#define		 SIN_CURSOR_GETITEM2	8
#define		 SIN_CURSOR_TALK		9





void sinInit();

void sinMain();

void sinDraw();

void sinDrawText();


void sinClose();

void sinProc(int Message);



class cSINBARAM_UI
{

public:
	int OpenFlag;

public:
	cSINBARAM_UI();
	~cSINBARAM_UI();

	void Init();
	void Load();
	void Release();
	void Draw();
	void Close();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();
};

extern int	 quit;
extern int	 MouseButton[3];
extern BYTE  VRKeyBuff[256];
extern POINT pCursorPos;
extern POINT pRealCursorPos;

extern HWND  hFocusWnd;

extern int WinSizeX;
extern int WinSizeY;
extern HWND hwnd;

extern smCHAR_INFO *sinChar;
extern smCHAR_INFO sinCharDisplay;
extern int sinbaram_Stop;
