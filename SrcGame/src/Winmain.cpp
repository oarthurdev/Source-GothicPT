#define _SINBARAM

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <ZMOUSE.H>
#include <process.h>
#include "cracker.h"

#include "smlib3d\\smd3d.h"
#include "smwsock.h"
#include "smreg.h"

#include "character.h"
#include "playmain.h"
#include "Sound\\dxwav.h"
#include "effectsnd.h"
#include "fileread.h"
#include "netplay.h"
#include "makeshadow.h"
#include "particle.h"
#include "field.h"
#include "hoBaram\\holinkheader.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"
#include "cQuestWindow.h"
#ifdef _SINBARAM
#include "sinbaram\\sinlinkheader.h"
#endif

#include "playsub.h"
#include "SkillSub.h"
#include "Resources\resource.h"

#include "TextMessage.h"		
#include "Language\\language.h"
#include "Language\\jts.h"		

#include "CurseFilter.h"		
#include "damage.h"
#include "AreaServer.h"

#include "BellatraFontEffect.h"

#include "actiongame.h"

#include "Settings\UI.h"
#include "Log\Log.h"



#define WM_CALLMEMMAP				WM_USER+3   

#ifdef PARKMENU
#include "TJBOY\\\\Park\\MicVolume.h"
extern BOOL bMic;
extern int vrunRuning;
extern int micInit;
#endif


#include "WinInt\\WinIntThread.h"
#include "FullZoomMap.h"
#include "FontImage.h"
#include "Dump\WinDump.h"


HWND hwnd;
HWND hTextWnd;
HWND hFocusWnd;
extern int sinChatDisplayMode;
extern int sinChatInputMode;

int quit = 0;
int QuitSave = 0;
int WinSizeX = 640;
int WinSizeY = 480;
int	WinColBit = 16;

float g_fWinSizeRatio_X;
float g_fWinSizeRatio_Y;

int TextMode;

int BrCtrl = 0;

DWORD	dwM_BlurTime = 0;


int MouseButton[3] = { 0,0,0 };
extern int TJwheel;
extern int keydownEnt;

int isChatBox(int x, int y)
{
	if (SubChatHeight) {
		if (x > 0 && x < 305 && y >(WinSizeY - 306) && y < WinSizeY)
			return TRUE;
	}
	else {
		if (x > 0 && x < 305 && y >(WinSizeY - 192) && y < WinSizeY)
			return TRUE;
	}

	return FALSE;
}

#pragma comment( lib, "imm32.lib" )


int InitD3D(HWND hWnd);
void CloseD3d();
int DrawGameState();
void smPlayD3D(int x, int y, int z, int ax, int ay, int az);



#include "ime.h"

ImeClass IMETest;
CStrClass sz;
LRESULT CALLBACK EditWndProc01(HWND, UINT, WPARAM, LPARAM);
WNDPROC		OldEditProc01;
char szIME_Buff[10][64];

extern int Width, Height;
extern int GetClick(DWORD x, DWORD y, DWORD L, DWORD A);
extern int iSave;
extern BOOL bDone;

extern void SaveConfig();
extern void Relog();
extern char ratio[4];
extern BOOL bIsWidescreen;

int MouseX, MouseY;
int MousemX, MousemY;
int angX = 0;
int angY = 0;
DWORD	dwLastMouseMoveTime;
DWORD	dwLastCharMoveTime;



int			iSettingsBg;
int			iSettingsButton[2];
int			iSettingsRelog;
int			iSettingsSave;
int			iSettingsCheckBox[2];

void ReadTexSettings()
{
	iSettingsBg = CreateTextureMaterial("game\\GUI\\Settings\\window.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iSettingsButton[0] = CreateTextureMaterial("game\\GUI\\Settings\\option.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iSettingsButton[1] = CreateTextureMaterial("game\\GUI\\Settings\\option_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iSettingsRelog = CreateTextureMaterial("game\\GUI\\Settings\\help_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iSettingsSave = CreateTextureMaterial("game\\GUI\\Settings\\save_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iSettingsCheckBox[0] = CreateTextureMaterial("game\\GUI\\Settings\\checkbox.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iSettingsCheckBox[1] = CreateTextureMaterial("game\\GUI\\Settings\\checkbox_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

int xPos, yPos;

POINT3D TraceCameraPosi;
POINT3D TraceTargetPosi;
int	PlayCameraMode = 1;
int AutoCameraFlag = FALSE;


LPDIRECT3DTEXTURE9 lpDDSMenu;

int DisplayDebug = 0;
int DispInterface = TRUE;
int	DebugPlayer = FALSE;
int	LastAttackDamage = 0;

int	HoMsgBoxMode = 0;


#define TRADEBUTTONMAIN_X		513
#define TRADEBUTTONMAIN_Y		3

POINT pHoPartyMsgBox = { TRADEBUTTONMAIN_X, TRADEBUTTONMAIN_Y };


char szExitInfo_URL[128] = { 0, };


#define ANX_NONE	-32768

int pX;
int pY;
int pZ;
int	dpX = 0;
int dpY = 0;
int dpZ = 0;

int whAnx = 48;
int anx = 48;
int	ViewAnx = 48;
int	ViewDist = 40;
int	PlayFloor = 0;
int any = 0;
int anz = 0;
int dist = 100;
int CaTarDist = 0;
int	CaMovAngle = 0;

int tX = 0;
int tY = 0;
int tZ = 0;


int	ImeChatLen = 0;
POINT	ImePositon;

int SetMousePlay(int flag);


int WaveCameraMode = FALSE;
POINT3D WaveCameraPosi;
int	WaveCameraFactor = 0;
int	WaveCameraTimeCount = 0;
int	WaveCameraDelay = 0;
BOOL WaveCameraFlag = FALSE;



int GameInit();

int GameClose();

int SetGameMode(int mode);


int	SetChatingLine(char *szMessage);

int GameMode = 0;


CRITICAL_SECTION	cDrawSection;


int HoInstallFont();
int HoUninstallFont();

HINSTANCE hinst;
BOOL WINAPI DllMain(HINSTANCE hinstDLL,
	DWORD fdwReason,
	LPVOID lpvReserved
)
{
	hinst = hinstDLL;

	return TRUE;
}

#define IDC_TEXT	101

BYTE VRKeyBuff[256];


LONG APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);
void PlayD3D();

HFONT hFont = 0;
int SetCreateFont();

CRITICAL_SECTION	cSection;


HIMC hImc;
HIMC hImcEdit;

extern rsRECORD_DBASE	rsRecorder;
extern INT WINAPI ServerWinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, INT nCmdShow);

char	szCmdLine[128];


extern int	CheckServerRecordData();


extern int RestoreBackupData(char *szListFile, char *BackupPath);


#ifndef _AC
#define _AC

#include "AntiCheat\AntiCheat.h"

#endif

extern AntiCheat * pcAntiCheat;


#ifdef _DEBUG


BOOL HookAPI(char* moduleName, char* apiName, void* callBack, void* backup = NULL)
{
	DWORD old = 0;

	void * pAPIHandle = GetProcAddress(GetModuleHandleA(moduleName), apiName);

	if (pAPIHandle == NULL)
		return FALSE;

	if (backup != NULL)
		MoveMemory(backup, pAPIHandle, 5);

	VirtualProtect(pAPIHandle, 5, PAGE_EXECUTE_READWRITE, &old);
	*(BYTE*)((DWORD)pAPIHandle) = 0xE9;
	*(DWORD*)((DWORD)pAPIHandle + 1) = (DWORD)callBack - (DWORD)pAPIHandle - 5;
	VirtualProtect(pAPIHandle, 5, old, &old);

	return TRUE;
}

LONG WINAPI RedirectedSetUnhandledExceptionFilter(EXCEPTION_POINTERS * p)
{
	return NULL;
}

#include <iostream>

extern "C" WINBASEAPI int WINAPI AllocConsole();

void allocConsole()
{

	AllocConsole();

	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);






	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

	SetUnhandledExceptionFilter(unhandled_handler);
	HookAPI("kernel32.dll", "SetUnhandledExceptionFilter", RedirectedSetUnhandledExceptionFilter);
}
#endif



INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef BMFONT
	void hooks();
	hooks();
#endif 

#ifndef _DEBUG


	// TRAVAR GAME NO LAUNCHER
	
	/*	if(strcmp(lpCmdLine, "/rpk_launcher") != 0)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		CreateProcess("Launcher.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
		exit(0);
	}
	
	// FIM*/

#endif

	
	#ifdef _DEBUG
		allocConsole();

	#endif
		

	pcAntiCheat = new AntiCheat();
	pcAntiCheat->AddNewThreadException(GetCurrentThreadId());
	pcAntiCheat->CheckThread();

	MSG msg;
	WNDCLASS wndclass;
	hinst = hInst;

	strcpy_s(szCmdLine, lpCmdLine);

	initSinCos();

	cSettings::GetInstance()->Load();

	InitializeCriticalSection(&cSection);
	InitializeCriticalSection(&cDrawSection);
	InitializeCriticalSection(&cSection_Main);

	srand(GetCurrentTime());

	InitDirectSound();

	WinSizeX = smScreenWidth;
	WinSizeY = smScreenHeight;
	WinColBit = cSettings::GetInstance()->cBPP;
	WindowMode = cSettings::GetInstance()->cWindowed;

	int sx = WinSizeX;
	int sy = WinSizeY;

	if (!cSettings::GetInstance()->cWindowed)
	{
		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);
	}

	if (!hPreInst)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInst;
		wndclass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_DEFAULT_ICON));
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = CreateSolidBrush(RGB(21, 17, 14));
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = szAppName;
		RegisterClass(&wndclass);
	}

	if (cSettings::GetInstance()->cWindowed)
	{
		RECT wrect;
		wrect.left = 0;
		wrect.top = 0;
		wrect.right = smScreenWidth;
		wrect.bottom = smScreenHeight;

		AdjustWindowRectEx(&wrect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE, 0);

		hwnd = CreateWindowEx(0,
			szAppName,
			szAppName,
			WS_OVERLAPPEDWINDOW,
			(GetSystemMetrics(SM_CXSCREEN) - sx) / 2,
			(GetSystemMetrics(SM_CYSCREEN) - sy) / 2,
			wrect.right - wrect.left,
			wrect.bottom - wrect.top,
			NULL,
			NULL,
			hInst,
			NULL);

	}
	else
	{
		hwnd = CreateWindow(szAppName, szAppName,
			WS_VISIBLE | WS_POPUP | WS_EX_TOPMOST, CW_USEDEFAULT,
			CW_USEDEFAULT, sx, sy, NULL, NULL,
			hInst, NULL);
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	ShowCursor(FALSE);

	if (InitD3D(hwnd) == NULL)
	{
		Log::getInstance()->output(LOG_ERROR, "Failed InitD3D()");
		return FALSE;
	}

	hTextWnd = CreateWindow("EDIT", "", WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_WANTRETURN, 10, 400, 500, 40, hwnd, (HMENU)IDC_TEXT, hInst, NULL);

	OldEditProc01 = (WNDPROC)SetWindowLong(hTextWnd, GWL_WNDPROC, (LONG)EditWndProc01);
	IMETest.SetHWND(hTextWnd);

	hImc = ImmGetContext(hwnd);
	hImcEdit = ImmGetContext(hTextWnd);

	SetIME_Mode(0);


	TextMode = 0;

	InitGameSocket();


	DeleteFile("ddd.txt");

	SetGameMode(1);
	CharacterName1[0] = 0;
	CharacterName2[0] = 0;

#ifdef BMFONT
	font[Weight::normal] = new Font();
	font[Weight::normal]->initialize("game\\Font\\normal.fnt", "game\\Font\\normal_0.tga");

	font[Weight::bold] = new Font();
	font[Weight::bold]->initialize("game\\Font\\bold.fnt", "game\\Font\\bold_0.tga");

	ReadTextures();
#endif

	SetTimer(hwnd, 0, GAME_WORLDTIME_MIN / 4, NULL);

#ifdef _LANGUAGE_WINDOW
	SetForegroundWindow(hwnd);
#endif

	while (1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			if (msg.message == WM_SYSKEYDOWN || msg.message == WM_SYSKEYUP)
			{
				if (msg.wParam != 0xF4 && msg.wParam != VK_F10)
					continue;
			}

			DispatchMessage(&msg);
		}
		else
		{
			EnterCriticalSection(&cSection_Main);

			RestoreDevice();

			PlayD3D();

			PlayRecvMessageQue();

			LeaveCriticalSection(&cSection_Main);
		}

		if (quit != 0 && !dwTradeMaskTime)
		{
			if (GameMode != 2)
				break;

			if (smWsockServer && !QuitSave)
			{
				if (cTrade.OpenFlag)
				{

					SendRequestTrade(cTrade.TradeCharCode, 3);
					cTrade.CancelTradeItem();
				}

				if (cWareHouse.OpenFlag)
				{

					cWareHouse.RestoreInvenItem();
				}

				cInvenTory.ResetMouseItem();

				SaveGameData();
				QuitSave = TRUE;
			}
			else
			{
				if (!smWsockServer || GetSaveResult() == TRUE)
					break;
				if ((dwPlayTime - rsRecorder.dwRecordTime) > 15000)
					break;
			}
		}
	}

	SetGameMode(0);

	if (pcAntiCheat)
	{
		delete pcAntiCheat;
		pcAntiCheat = nullptr;
	}

	CloseBindSock();
	CloseD3d();

#ifdef BMFONT

	for (int i = 0; i < 2; i++)
	{
		if (font[i])
		{
			delete font[i];
			font[i] = nullptr;
		}
	}
#endif

	if (fpNetLog)
		fclose(fpNetLog);

	if (szExitInfo_URL[0])
		ShellExecute(NULL, NULL, szExitInfo_URL, NULL, NULL, NULL);

	return msg.wParam;
}

int msX = 0, msY = 0;
int msXo = 0, msYo = 0;
int xPs;
int yPs;

POINT	pCursorPos;
POINT	pRealCursorPos;


DWORD GameWindowMessage(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam);
DWORD dwTimerCount = 0;


BOOL DisplayIME = FALSE;

int SetIME_Mode(BOOL mode)
{
	if (mode)
	{
		DisplayIME = TRUE;
		ImmSetOpenStatus(hImc, TRUE);
#ifdef	_LANGUAGE_JAPANESE


		ImmSetConversionStatus(hImc, IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE, IME_SMODE_PHRASEPREDICT);
		ImmSetConversionStatus(hImcEdit, IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE, IME_SMODE_PHRASEPREDICT);


#else

		ImmSetConversionStatus(hImc, IME_CMODE_NATIVE, IME_CMODE_NATIVE);
		ImmSetConversionStatus(hImcEdit, IME_CMODE_NATIVE, IME_CMODE_NATIVE);
#endif

	}
	else
	{
		ImmSetConversionStatus(hImc, IME_CMODE_ALPHANUMERIC, IME_CMODE_ALPHANUMERIC);
		ImmSetConversionStatus(hImcEdit, IME_CMODE_ALPHANUMERIC, IME_CMODE_ALPHANUMERIC);

		ImmSetOpenStatus(hImc, FALSE);
		DisplayIME = FALSE;
	}


	return TRUE;
}


int CheckCode_2Byte(char *Str)
{
#ifdef _LANGUAGE_ENGLISH


	return 1;
#endif

#ifdef _LANGUAGE_THAI
	if (CheckTHAI_ptr(Str, 0) == 1)
		return 1;
	else if (CheckTHAI_ptr(Str, 0) == 2)
		return 2;
	return 1;
#endif

#ifdef _LANGUAGE_JAPANESE

	if (CheckJTS_ptr(Str, 0) == 2)
		return 2;

#else

	if (Str[0] < 0)
		return 2;
#endif

	return 1;
}

LRESULT CALLBACK EditWndProc01(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	wmId = LOWORD(wParam);
	wmEvent = HIWORD(wParam);

	switch (message)
	{
	case WM_KEYDOWN:


#ifdef	_IME_ACTIVE
		IMETest.GetInfoPerTime();
#endif


		break;
	}
	return CallWindowProc(OldEditProc01, hWnd, message, wParam, lParam);
}

#ifdef	_LANGUAGE_JAPANESE

char g_bufEdit[256];
char g_bufFixed[256];

int WndProc_Japanese(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	HIMC	imc;
	static DWORD conv = IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE | IME_CMODE_ROMAN;
	static DWORD sent = IME_SMODE_PHRASEPREDICT;
	static BOOL setFont = FALSE;

	switch (messg)
	{

	case WM_IME_COMPOSITION:

		if ((imc = ImmGetContext(hWnd)))
		{
			if (lParam & GCS_RESULTSTR)
			{
				ZeroMemory(g_bufFixed, 256);
				ImmGetCompositionString(imc, GCS_RESULTSTR, g_bufFixed, 256);
			}
			else if (lParam & GCS_COMPSTR)
			{
				ZeroMemory(g_bufEdit, 256);
				ImmGetCompositionString(imc, GCS_COMPSTR, g_bufEdit, 256);
			}
			ImmReleaseContext(hWnd, imc);
		}
		break;

	case WM_IME_NOTIFY:
		switch (wParam)
		{
		case IMN_SETCONVERSIONMODE:
		case IMN_SETSENTENCEMODE:
			if ((imc = ImmGetContext(hWnd)))
			{
				ImmGetConversionStatus(imc, &conv, &sent);
				ImmReleaseContext(hWnd, imc);
			}
			break;

		case IMN_SETOPENSTATUS:
			if ((imc = ImmGetContext(hWnd)))
			{
				if (ImmGetOpenStatus(imc))
				{
					ImmSetConversionStatus(imc, conv, sent);
				}
				else
				{
					ImmGetConversionStatus(imc, &conv, &sent);
				}
				ImmReleaseContext(hWnd, imc);
			}

			if (!setFont && (imc = ImmGetContext(hWnd)))
			{
				LOGFONT lf;
				ZeroMemory(&lf, sizeof(LOGFONT));
				lf.lfHeight = 12;
				lf.lfItalic = FALSE;
				lf.lfUnderline = FALSE;
				lf.lfStrikeOut = FALSE;
				lf.lfCharSet = OEM_CHARSET;
				lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
				lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
				lf.lfQuality = DEFAULT_QUALITY;
				lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
				strcpy(lf.lfFaceName, _T("‚l‚r ‚oƒSƒVƒbƒN"));
				ImmSetCompositionFont(imc, &lf);
				ImmReleaseContext(hWnd, imc);
				setFont = TRUE;
			}
			break;

		case IMN_OPENCANDIDATE:
		case IMN_CHANGECANDIDATE:
			if ((imc = ImmGetContext(hWnd)))
			{
				CANDIDATEFORM cf;
				ZeroMemory(&cf, sizeof(CANDIDATEFORM));
				cf.dwStyle = CFS_CANDIDATEPOS;
				cf.ptCurrentPos.x = 100000;
				cf.ptCurrentPos.y = 100000;
				ImmSetCandidateWindow(imc, &cf);
				ImmReleaseContext(hWnd, imc);
			}
			break;
		}
		break;
	}

	return TRUE;
}
#endif

extern void clan_Mouse(int msg, WPARAM wParam);

BOOL bAdjustWindow = TRUE;

LONG APIENTRY WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	static bool mouse_left_click = false;
	static bool mouse_right_click = false;


	short zDelta;
	char strBuff[256];
	char strBuff2[256];
	char *lpString;
	int	len, CrCode;

	switch (messg)
	{

	case WM_SIZE:

		if (wParam == SIZE_MAXIMIZED && cSettings::GetInstance()->cAutoAdjust && cSettings::GetInstance()->cWindowed)
		{
			WinSizeX = LOWORD(lParam);
			WinSizeY = HIWORD(lParam);

			smScreenWidth = WinSizeX;
			smScreenHeight = WinSizeY;

			MidX = WinSizeX / 2;
			MidY = WinSizeY / 2;

			g_fWinSizeRatio_X = float(WinSizeX) / 800.f;
			g_fWinSizeRatio_Y = float(WinSizeY) / 600.f;

			viewdistZ = ((WinSizeY / 3) * 4);

			SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 4000.f);

			smRender.SMSHIFT_PERSPECTIVE_WIDTH = 0;
			smRender.SMMULT_PERSPECTIVE_HEIGHT = 0;

			if (d3ddev)
			{
				d3dpp.BackBufferWidth = WinSizeX;
				d3dpp.BackBufferHeight = WinSizeY;
				OnLostDevice();
				d3ddev->Reset(&d3dpp);
				InitRender();
				OnResetDevice();
			}
		}
		else
		{
			if (wParam == SIZE_RESTORED && cSettings::GetInstance()->cWindowed)
			{
				WinSizeX = LOWORD(lParam);
				WinSizeY = HIWORD(lParam);

				smScreenWidth = WinSizeX;
				smScreenHeight = WinSizeY;

				MidX = WinSizeX / 2;
				MidY = WinSizeY / 2;

				g_fWinSizeRatio_X = float(WinSizeX) / 800.f;
				g_fWinSizeRatio_Y = float(WinSizeY) / 600.f;

				viewdistZ = ((WinSizeY / 3) * 4);

				SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 4000.f);

				smRender.SMSHIFT_PERSPECTIVE_WIDTH = 0;
				smRender.SMMULT_PERSPECTIVE_HEIGHT = 0;

				if (d3ddev)
				{
					d3dpp.BackBufferWidth = WinSizeX;
					d3dpp.BackBufferHeight = WinSizeY;
					OnLostDevice();
					d3ddev->Reset(&d3dpp);
					InitRender();
					OnResetDevice();
				}
			}
		}
		break;

	case WM_CALLMEMMAP:
		void PacketParsing();
		PacketParsing();
		break;


	case WM_CREATE:
		break;

	case WM_CLOSE:

		QuitGame();
		break;

	case WSA_ACCEPT:
		WSAMessage_Accept(wParam, lParam);
		break;

	case WSA_READ:
		WSAMessage_Read(wParam, lParam);
		break;

	case SWM_RECVSUCCESS:


		RecvPlayData((smTHREADSOCK *)wParam);
		break;

	case SWM_MCONNECT:

		ConnectOtherPlayer(wParam);
		break;

	case SWM_MDISCONNECT:

		((smWINSOCK *)wParam)->CloseSocket();
		break;


	case WM_KEYDOWN:



		if (g_IsDxProjectZoomIn > 0)
		{
			if (KeyFullZoomMap(wParam))
			{
				VRKeyBuff[wParam] = 1;
				break;
			}
			else
			{
				SetFullZoomMap(0);
				pCursorPos.x = g_iFzmCursorPosX;
				pCursorPos.y = g_iFzmCursorPosY;

				if (wParam == VK_ESCAPE)
					break;
			}
		}





#ifdef PARKMENU


		if (wParam == 0x47)
		{
			if (vrunRuning == TRUE)
			{
				if (bMic == FALSE)
				{
					if (micInit == 0)
					{
						micInit = cmicvol.Init();
					}
					bMic = TRUE;
					void ParkSetMicOnOFF();
					ParkSetMicOnOFF();
				}
			}
		}

#endif


		if (!VRKeyBuff[VK_CONTROL] && wParam == VK_F12)
		{
			static bool fullscreen = false;

			if (!fullscreen)
			{
				LONG value = GetWindowLong(hWnd, GWL_STYLE);
				SetWindowLong(hWnd, GWL_STYLE, value & 0xDE33FFFF);

				value = GetWindowLong(hWnd, GWL_EXSTYLE);
				SetWindowLong(hWnd, GWL_STYLE, value & 0xFFFDFDFE);
				SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOOWNERZORDER);

				ShowWindow(hWnd, SW_SHOWMAXIMIZED);
				fullscreen = true;
				Sleep(200);
			}
			else
			{
				ShowWindow(hWnd, SW_SHOWDEFAULT);
				SetWindowLong(hWnd, GWL_STYLE, 0x94CF0008);
				SetWindowLong(hWnd, GWL_EXSTYLE, 0x100);

				fullscreen = false;
				Sleep(200);
			}
		}

		if (wParam == VK_F10)
		{
			if (!cSettings::GetInstance()->IsOpen())
			{
				cSettings::GetInstance()->Open();
			}
			else
			{
				cSettings::GetInstance()->Close();
			}
		}





		if (wParam == VK_RETURN)
		{
			keydownEnt = 1;
		}

		if (wParam == VK_CONTROL)
		{
			VRKeyBuff[wParam] = 1;
		}

		if (!hFocusWnd)
		{
			if (!VRKeyBuff[VK_SHIFT] && VRKeyBuff[VK_CONTROL] && !sinMessageBoxShowFlag && VRKeyBuff[wParam] == 0)
			{

				if (wParam == VK_F1 || wParam == VK_F2 || wParam == VK_F3 || wParam == VK_F4 || wParam == VK_F5 ||
					wParam == VK_F6 || wParam == VK_F7 || wParam == VK_F8 || wParam == VK_F9 || wParam == VK_F10)
				{
					SetChatingLine("");
				}
			}
		}

		if (hFocusWnd)
		{
			lpString = 0;
			CrCode = 0;

			if (!VRKeyBuff[VK_SHIFT] && VRKeyBuff[VK_CONTROL] && !sinMessageBoxShowFlag)
			{
				if (wParam == VK_F1 && szShotCutMessage[1][0]) lpString = szShotCutMessage[1];
				if (wParam == VK_F2 && szShotCutMessage[2][0]) lpString = szShotCutMessage[2];
				if (wParam == VK_F3 && szShotCutMessage[3][0]) lpString = szShotCutMessage[3];
				if (wParam == VK_F4 && szShotCutMessage[4][0]) lpString = szShotCutMessage[4];
				if (wParam == VK_F5 && szShotCutMessage[5][0]) lpString = szShotCutMessage[5];
				if (wParam == VK_F6 && szShotCutMessage[6][0]) lpString = szShotCutMessage[6];
				if (wParam == VK_F7 && szShotCutMessage[7][0]) lpString = szShotCutMessage[7];
				if (wParam == VK_F8 && szShotCutMessage[8][0]) lpString = szShotCutMessage[8];
				if (wParam == VK_F9 && szShotCutMessage[9][0]) lpString = szShotCutMessage[9];
				if (wParam == VK_F10 && szShotCutMessage[0][0]) lpString = szShotCutMessage[0];

				if (lpString)
				{
#ifdef	_LANGUAGE_VEITNAM
					GetWindowText(hFocusWnd, strBuff2, 80);
#else
					GetWindowText(hFocusWnd, strBuff2, 90);
#endif
					len = lstrlen(strBuff2) + lstrlen(lpString);
					if (len < 80)
					{
						lstrcat(strBuff2, lpString);
						if (strBuff2[len - 1] == 0x0D)
						{
							len--;
							strBuff2[len] = 0;
							CrCode = TRUE;
						}
						SetWindowText(hFocusWnd, strBuff2);
						SendMessage(hFocusWnd, EM_SETSEL, len, len);
					}
				}
			}
			if (!sinMessageBoxShowFlag &&
				((wParam == VK_RETURN && VRKeyBuff[wParam] == 0 && !VRKeyBuff[VK_CONTROL]) || CrCode == TRUE))
			{

#ifdef	_LANGUAGE_VEITNAM
				GetWindowText(hFocusWnd, strBuff2, 80);
#else
				GetWindowText(hFocusWnd, strBuff2, 90);
#endif
				cHelpPet.PetOnOff(strBuff2);

				if (strBuff2[0])
				{
					if (strBuff2[0] == '/' || (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && strBuff2[0] == '~') || strBuff2[0] == '`' || strBuff2[0] == '@')
						wsprintf(strBuff, "%s", strBuff2);
					else
					{
						switch (DispChatMode)
						{
						case 0:
						case 4:
#ifdef	_LANGUAGE_VEITNAM
							wsprintf(strBuff, "%s: %s", PlayerName, strBuff2);
#else
							wsprintf(strBuff, "%s: %s", PlayerName, strBuff2);
#endif
							break;
						case 1:
							wsprintf(strBuff, "/CLAN> %s", strBuff2);
							break;
						case 2:
							wsprintf(strBuff, "@%s", strBuff2);
							break;
						case 3:
							wsprintf(strBuff, "/TRADE> %s", strBuff2);
							break;
						}
					}


					if (GameMode == 2)
					{
						if (!usehFocus)
							SendChatMessageToServer(strBuff);

						if (chatlistSPEAKERflag() && lstrlen(strBuff) > LastWhisperLen)
						{
							SetClanChatting();
							if (szLastWhisperName[0])
							{

								szLastWhisperName[0] = 0;
							}
						}
						else
							if (szLastWhisperName[0] && lstrlen(strBuff) > LastWhisperLen)
							{

								WhisperPartyPlayer(szLastWhisperName);
							}
							else
							{
								SetWindowText(hFocusWnd, "");
								szLastWhisperName[0] = 0;
								LastWhisperLen = 0;
								InterfaceParty.chat_WhisperPartyPlayer_close();
								chatlistSPEAKERflagChg(0);
							}
					}
					else
					{
						hFocusWnd = 0;
					}
				}
				else
				{
					hFocusWnd = 0;
					if (GameMode == 2)
					{
						szLastWhisperName[0] = 0;
						LastWhisperLen = 0;
						InterfaceParty.chat_WhisperPartyPlayer_close();
						chatlistSPEAKERflagChg(0);
					}
				}
			}

			if (GameMode == 2)
			{
				if (wParam == VK_TAB && VRKeyBuff[wParam] == 0)
				{
					IsClanChatting();
					break;
				}

				if (wParam == VK_UP && VRKeyBuff[wParam] == 0 && !LastWhisperLen)
				{

					RecallSavedChatCommand(hFocusWnd, 1);

					break;
				}
				if (wParam == VK_DOWN && VRKeyBuff[wParam] == 0 && !LastWhisperLen)
				{
					RecallSavedChatCommand(hFocusWnd, 0);

					break;
				}
				if (wParam == VK_ESCAPE && VRKeyBuff[wParam] == 0)
				{
					if (SendMessage(hTextWnd, EM_GETLIMITTEXT, 78, 0) >= 78)
					{
						hFocusWnd = 0;
						cInterFace.ChatFlag = 0;
						szLastWhisperName[0] = 0;
						LastWhisperLen = 0;
						InterfaceParty.chat_WhisperPartyPlayer_close();
						chatlistSPEAKERflagChg(0);
					}

				}


				if (wParam == VK_NEXT && VRKeyBuff[wParam] == 0)
				{
					ChatScrollPoint -= DispChatMsgHeight;
				}
				if (wParam == VK_PRIOR && VRKeyBuff[wParam] == 0)
				{
					ChatScrollPoint += DispChatMsgHeight;
				}

				if (!hFocusWnd)
				{


					SetIME_Mode(0);
					ChatScrollPoint = 0;


				}
			}

			SendMessage(hFocusWnd, messg, wParam, lParam);
			break;
		}

		if (wParam == VK_ESCAPE && VRKeyBuff[wParam] == 0)
		{
			if (VRKeyBuff[VK_SHIFT])
				QuitGame();
			else
			{
				if (cInterFace.ChatFlag)
					cInterFace.ChatFlag = 0;
				else
				{
					if (cInvenTory.OpenFlag || cCharStatus.OpenFlag || cSkill.OpenFlag || ExitButtonClick)
					{
						cInterFace.CheckAllBox(SIN_ALL_CLOSE);
					}
					else
					{
						if (InterfaceParty.PartyPosState == PARTY_PROCESS)
						{
							InterfaceParty.PartyPosState = PARTY_END;
							InterfaceParty.qN_Pressf_CLEAR();
						}
						else
						{
							ExitButtonClick = 1;
						}
					}
				}
			}
		}


		if (GameMode == 2)
		{
			if (GameWindowMessage(hWnd, messg, wParam, lParam) == FALSE) break;
		}

		if (GameMode == 2 && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField] &&
			StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM)
		{


		}
		else
		{
			if (wParam == VK_HOME && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
			{
				CaptureOpening();
				chaSiege.bCaptureScreen = TRUE;
				chaSiege.dwTickScreen = GetTickCount();
				Capture(hwnd);
			}
		}

		VRKeyBuff[wParam] = 1;
		clan_Mouse(WM_KEYDOWN, wParam);

		break;


	case WM_KEYUP:


		if (g_IsDxProjectZoomIn > 0)
		{
			if (KeyFullZoomMap(wParam))
			{
				VRKeyBuff[wParam] = 0;
				break;
			}
		}



#ifdef PARKMENU




		if (wParam == 0x47)
		{
			if (vrunRuning == TRUE)
			{
				if (bMic == TRUE)
				{
					bMic = FALSE;
					void ParkSetMicOnOFF();
					ParkSetMicOnOFF();
				}
			}
		}

#endif

		if (hFocusWnd)
		{
			SendMessage(hFocusWnd, messg, wParam, lParam);
		}
		VRKeyBuff[wParam] = 0;
		clan_Mouse(WM_KEYUP, wParam);
		break;

	case WM_SYSKEYDOWN:
		if (wParam == VK_F10)
		{
			PostMessage(hWnd, WM_KEYDOWN, wParam, lParam);
			return FALSE;
		}
		if (hFocusWnd)
			SendMessage(hFocusWnd, messg, wParam, lParam);
		break;

	case WM_SYSKEYUP:
		if (wParam == VK_F10)
		{
			PostMessage(hWnd, WM_KEYUP, wParam, lParam);
			return FALSE;
		}
		if (hFocusWnd)
			SendMessage(hFocusWnd, messg, wParam, lParam);
		break;

	case WM_MOUSEMOVE:


		if (g_IsDxProjectZoomIn)
		{
			g_iFzmCursorPosX = LOWORD(lParam);
			g_iFzmCursorPosY = HIWORD(lParam);

			if (g_iFzmCursorPosX > 30 * g_fWinSizeRatio_X && g_iFzmCursorPosX < 350 * g_fWinSizeRatio_X &&
				g_iFzmCursorPosY > 338 * g_fWinSizeRatio_Y && g_iFzmCursorPosY < 578 * g_fWinSizeRatio_Y)
			{
				if (g_iFzmCursorFocusGame == 0)
				{
					g_iFzmCursorFocusGame = 1;

					xPs = pCursorPos.x = msXo = int(((float)g_iFzmCursorPosX - g_fZoomInAdd_x) * g_fZoomInDiv_x);
					yPs = pCursorPos.y = msYo = int(((float)g_iFzmCursorPosY - g_fZoomInAdd_y) * g_fZoomInDiv_y);
				}

				xPs = int(((float)g_iFzmCursorPosX - g_fZoomInAdd_x) * g_fZoomInDiv_x);
				yPs = int(((float)g_iFzmCursorPosY - g_fZoomInAdd_y) * g_fZoomInDiv_y);

				AutoMouse_Distance += abs(pCursorPos.x - xPs);
				AutoMouse_Distance += abs(pCursorPos.y - yPs);

				pCursorPos.x = xPs;
				pCursorPos.y = yPs;

				msX = msXo - xPs;
				msY = msYo - yPs;

				msXo = xPs;
				msYo = yPs;

				if ((wParam & MK_MBUTTON))
					SetMousePlay(3);
				else
				{
					if (wParam == MK_LBUTTON || TraceMode_DblClick)
						SetMousePlay(2);
					else if (wParam == MK_RBUTTON)
						SetMousePlay(4);
				}
				dwLastMouseMoveTime = dwPlayTime;
			}
			else
				g_iFzmCursorFocusGame = 0;
		}
		else
		{
			xPs = LOWORD(lParam);
			yPs = HIWORD(lParam);

			AutoMouse_Distance += abs(pCursorPos.x - xPs);
			AutoMouse_Distance += abs(pCursorPos.y - yPs);



			g_iFzmCursorPosX = pCursorPos.x = xPs;
			g_iFzmCursorPosY = pCursorPos.y = yPs;
			msX = msXo - xPs;
			msY = msYo - yPs;

			msXo = xPs;
			msYo = yPs;

			if ((wParam&MK_MBUTTON))
				SetMousePlay(3);
			else
			{
				if (wParam == MK_LBUTTON || TraceMode_DblClick)
					SetMousePlay(2);
				else
					if (wParam == MK_RBUTTON)
						SetMousePlay(4);
			}


		}


		dwLastMouseMoveTime = dwPlayTime;
		break;

	case WM_LBUTTONDBLCLK:
		MouseDblClick = TRUE;

		if (GameMode == 2)
		{

			if (GetFieldMapCursor() == TRUE && cInterFace.sInterFlags.MapOnFlag)
			{
				sinCheck_ShowHelpMap();
			}
			sinDoubleClick();

			dsMenuCursorPos(&pCursorPos, 2);
			if (StopCharMotion(pCursorPos.x, pCursorPos.y) != TRUE)
			{
				Moving_DblClick = TRUE;
				MousePos_DblClick.x = xPs;
				MousePos_DblClick.y = yPs;
				MousePos_DblClick.z = 0;
			}
			dsMenuCursorPos(&pCursorPos, 0);
		}
		break;

	case WM_LBUTTONDOWN:
	{


		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			SetMousePlay(1);
			sinLButtonDown();
			MouseButton[0] = TRUE;

			clan_Mouse(WM_LBUTTONDOWN, wParam);
		}
		else
			g_FzmMouseButton[0] = TRUE;




		if (GameMode == 2 && DisconnectFlag)
			quit = TRUE;

		extern bool clickable;
		clickable = true;
	}
	break;

	case WM_LBUTTONUP:
	{
		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame || MouseButton[0])
		{
			SetMousePlay(0);
			sinLButtonUp();

			MouseButton[0] = FALSE;
			MouseDblClick = FALSE;

			clan_Mouse(WM_LBUTTONUP, wParam);
		}
		else
		{
			MouseDblClick = FALSE;
			g_FzmMouseButton[0] = FALSE;
		}


		extern bool clickable;
		clickable = false;
	}
	break;

	case WM_RBUTTONDOWN:


		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			SetMousePlay(11);
			MouseButton[1] = TRUE;

			clan_Mouse(WM_RBUTTONDOWN, wParam);
		}
		else
			g_FzmMouseButton[1] = TRUE;


		break;

	case WM_RBUTTONUP:


		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			SetMousePlay(10);
			sinRButtonUp();
			MouseButton[1] = FALSE;

			clan_Mouse(WM_RBUTTONUP, wParam);
		}
		else
			g_FzmMouseButton[1] = FALSE;

		mouse_right_click = false;
		break;

	case WM_MBUTTONDOWN:


		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			MouseButton[2] = TRUE;

			clan_Mouse(WM_MBUTTONDOWN, wParam);
		}
		else
			g_FzmMouseButton[2] = TRUE;

		break;

	case WM_MBUTTONUP:


		if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
		{
			MouseButton[2] = FALSE;

			clan_Mouse(WM_MBUTTONUP, wParam);
		}
		else
			g_FzmMouseButton[2] = FALSE;


		break;

	case WM_MOUSEWHEEL:

		/*
		if (hFocusWnd)

		{
			if (((short)HIWORD(wParam)) / 120 > 0 && sinChatEnter)

			{
				if (ChatScrollPoint < 32 && ChatBuffCnt - ChatScrollPoint >= 14)
					ChatScrollPoint += 1;
			}
			if (((short)HIWORD(wParam)) / 120 < 0 && sinChatEnter)

			{
				if (ChatScrollPoint != 0)
					ChatScrollPoint -= 1;
			}
		} */

		zDelta = (short)HIWORD(wParam);

		if (RestaureWindow::GetInstance()->openFlag)
		{
			RestaureWindow::GetInstance()->MouseWheel(zDelta);
		}
		else if (cQuestWindow.OpenFlag)
		{
			cQuestWindow.MouseWheel(zDelta);
		}
		else if (isChatBox(pRealCursorPos.x, pRealCursorPos.y))
		{
			if (zDelta >= 0)
			{
				if ((ChatScrollPoint < ChatBuffCnt - 12) || (SubChatHeight && ChatScrollPoint < ChatBuffCnt - 8))
					ChatScrollPoint++;
			}
			else if (ChatScrollPoint > 0)
				ChatScrollPoint--;
		} else if (g_IsDxProjectZoomIn <= 0 && !Shop::GetInstance()->IsOpen() && !hFocusWnd && !TShop::GetInstance()->IsOpen() || g_iFzmCursorFocusGame && !Shop::GetInstance()->IsOpen() && !TShop::GetInstance()->IsOpen() && !hFocusWnd)
		{
			
			zDelta = (short)HIWORD(wParam);

			if (cSinHelp.sinGetScrollMove(-zDelta / 16) == TRUE) break;
			if (TJBscrollWheel(zDelta) == TRUE) break;

			if (whAnx == ANX_NONE) whAnx = anx + zDelta;
			else whAnx += zDelta;
			AutoCameraFlag = FALSE;
		}

		Shop::GetInstance()->ButtonScroll((short)(HIWORD(wParam)) / 120);
		TShop::GetInstance()->ButtonScroll((short)(HIWORD(wParam)) / 120);

		break;

	case WM_CHAR:
		if (wParam == 0x0D || wParam == 0x0A || (GameMode == 2 && wParam == VK_TAB)) return TRUE;
		if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR && wParam == 22 && lpCurPlayer->szChatMessage[0]) return TRUE;

	case WM_SYSCHAR:
	case WM_IME_CHAR:
	case WM_IME_COMPOSITION:



		if (g_IsDxProjectZoomIn > 0)
			break;

		if (hFocusWnd)
			SendMessage(hFocusWnd, messg, wParam, lParam);
		break;

	case WM_KILLFOCUS:
		SetFocus(hWnd);
		return TRUE;

	case WM_COMMAND:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	case WM_ACTIVATE:
		break;


	case WM_NCRBUTTONDOWN:
		break;


	case WM_NCACTIVATE:
#ifdef _WINMODE_DEBUG
		if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
#endif
#ifndef _LANGUAGE_WINDOW
			SetForegroundWindow(hwnd);
#endif


		if (GameMode == 2 && lpCurPlayer->dwObjectSerial)
		{

			CheckCracker();

			CheckCracker(NULL);

			CheckCharForm();
		}

		break;

	case WM_TIMER:
		if ((dwTimerCount & 3) == 0)
		{
			dwGameWorldTime++;

			dwGameHour = dwGameWorldTime + dwGameTimeOffset;
			dwGameHour = dwGameHour / 60;
			dwGameHour = dwGameHour - (((int)(dwGameHour / 24)) * 24);
			dwGameMin = dwGameWorldTime - (((int)(dwGameWorldTime / 60)) * 60);


		}

		if (smWsockServer && smWsockDataServer && smWsockUserServer)
		{
			smCheckWaitMessage();
		}

		dwTimerCount++;
		break;


	default:
		return DefWindowProc(hWnd, messg, wParam, lParam);
		break;
	}
	return 0L;

}

int MoveAngle(int step, int angY)
{
	int x, z;

	x = ((pX << 16) + GetSin[angY&ANGLE_MASK] * step) >> 16;
	z = ((pZ << 16) + GetCos[angY&ANGLE_MASK] * step) >> 16;

	pX = x;
	pZ = z;

	return TRUE;
}

#define CAMERA_MOVE_STEP		(8*fONE)

int TraceCameraMain()
{
	if (TraceCameraPosi.x < TraceTargetPosi.x)
	{
		TraceCameraPosi.x += CAMERA_MOVE_STEP;
		if (TraceCameraPosi.x > TraceTargetPosi.x)
			TraceCameraPosi.x = TraceTargetPosi.x;
	}
	if (TraceCameraPosi.x > TraceTargetPosi.x)
	{
		TraceCameraPosi.x -= CAMERA_MOVE_STEP;
		if (TraceCameraPosi.x < TraceTargetPosi.x)
			TraceCameraPosi.x = TraceTargetPosi.x;
	}

	if (TraceCameraPosi.y < TraceTargetPosi.y)
	{
		TraceCameraPosi.y += CAMERA_MOVE_STEP;
		if (TraceCameraPosi.y > TraceTargetPosi.y)
			TraceCameraPosi.y = TraceTargetPosi.y;
	}
	if (TraceCameraPosi.y > TraceTargetPosi.y)
	{
		TraceCameraPosi.y -= CAMERA_MOVE_STEP / 2;
		if (TraceCameraPosi.y < TraceTargetPosi.y)
			TraceCameraPosi.y = TraceTargetPosi.y;
	}


	if (TraceCameraPosi.z < TraceTargetPosi.z)
	{
		TraceCameraPosi.z += CAMERA_MOVE_STEP;
		if (TraceCameraPosi.z > TraceTargetPosi.z)
			TraceCameraPosi.z = TraceTargetPosi.z;
	}
	if (TraceCameraPosi.z > TraceTargetPosi.z)
	{
		TraceCameraPosi.z -= CAMERA_MOVE_STEP;
		if (TraceCameraPosi.z < TraceTargetPosi.z)
			TraceCameraPosi.z = TraceTargetPosi.z;
	}

	return TRUE;
}

int RendSightPos = 0;
int RendSightOffset = 0;


int SetRendSight()
{
	if (smRender.m_GameFieldView)
	{
		ViewPointLen = 38 * SizeMAPCELL + RendSightPos;
		ccDistZMin = ViewPointLen - (20 * SizeMAPCELL + RendSightPos / 4);

		return TRUE;
	}

	return FALSE;
}

int RendSightSub(int flag)
{
	if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldSight)
		RendSightOffset = StageField[lpCurPlayer->OnStageField]->FieldSight * SizeMAPCELL;
	else
	{
		RendSightOffset = smRender.m_GameFieldViewStep * SizeMAPCELL;
		if (flag) RendSightPos = RendSightOffset;
	}

	if (RendSightPos < RendSightOffset)
		RendSightPos += 4;
	else
		if (RendSightPos > RendSightOffset) RendSightPos -= 4;

	return TRUE;
}



#define	FPS_TIME		(1000/70)

DWORD FrameSkipTimer = 0;
int fps = 70;
int FpsTime;

#define AC_MOVE_STEP	4
#define AC_MOVE_MIN		256

int dsCameraRotation = 0;

int iTickCount = 0;
int iSeconds = 0;
int iSecondsInCity = 0;

void PlayMain()
{
	int mv = 0;

	if (ActionGameMode)
	{
		ActionGameMain();
	}
	else if (cSinHelp.sinGetHelpShowFlag() != TRUE)
	{
		if (cSettings::GetInstance()->cCamInv)
		{
			if (VRKeyBuff[VK_RIGHT])
			{
				any += 16; AutoCameraFlag = FALSE;
			}
			if (VRKeyBuff[VK_LEFT])
			{
				any -= 16; AutoCameraFlag = FALSE;
			}
		}
		else
		{
			if (VRKeyBuff[VK_RIGHT])
			{
				any -= 16; AutoCameraFlag = FALSE;
			}
			if (VRKeyBuff[VK_LEFT])
			{
				any += 16; AutoCameraFlag = FALSE;
			}
		}

		if (VRKeyBuff[VK_CONTROL])
		{
			if (VRKeyBuff[VK_UP])
			{
				anx -= 16;
				AutoCameraFlag = FALSE;
			}
			if (VRKeyBuff[VK_DOWN])
			{
				anx += 16;
				AutoCameraFlag = FALSE;
			}
		}
		else
		{
			if (VRKeyBuff[VK_UP])
			{
				dist -= 8;
				if (dist < 34)
				{
					if (anx <= 40)
					{
						if (dist < 40)
							dist = 40;
					}
					else
						dist = 34;

					CaTarDist = 0;
				}
			}

			if (VRKeyBuff[VK_DOWN])
			{
				dist += 8;
				if (dist > 600) { dist = 600; CaTarDist = 0; }
			}
		}

		if (VRKeyBuff[VK_NEXT])
		{
			anx -= 16; AutoCameraFlag = FALSE;
		}
		if (VRKeyBuff[VK_PRIOR])
		{
			anx += 16; AutoCameraFlag = FALSE;
		}
	}

	if (cInterFace.sInterFlags.CameraAutoFlag != 2)
	{

		if (pCursorPos.x >= 8 && pCursorPos.x <= WinSizeX - 8)
		{
			dsCameraRotation = 0;
		}

		if (pCursorPos.x < 8)
		{
			if (!dsCameraRotation)
			{
				dsCameraRotation = -512;
			}

			mv = dsCameraRotation / 16;

			if (mv < -16)
			{
				mv = -16;
			}

			any += mv;
			dsCameraRotation++;

			if (dsCameraRotation >= 0)
			{
				dsCameraRotation = 0;
				pCursorPos.x = 8;
			}
			AutoCameraFlag = FALSE;
		}

		if (pCursorPos.x > WinSizeX - 8)
		{
			if (!dsCameraRotation)
			{
				dsCameraRotation = 512;
			}

			mv = dsCameraRotation / 16;

			if (mv > 16)
			{
				mv = 16;
			}
			any += mv;

			dsCameraRotation--;
			if (dsCameraRotation <= 0)
			{
				dsCameraRotation = 0;
				pCursorPos.x = WinSizeX - 8;
			}
			AutoCameraFlag = FALSE;
		}
	}

	if (CaTarDist)
	{
		if (dist < CaTarDist)
		{
			dist += 12;

			if (dist >= CaTarDist)
			{
				dist = CaTarDist; CaTarDist = 0;
			}
		}
		else
		{
			if (dist > CaTarDist)
			{
				dist -= 12;

				if (dist <= CaTarDist)
				{
					dist = CaTarDist; CaTarDist = 0;
				}
			}
		}
	}

	if (CaMovAngle)
	{
		mv = CaMovAngle >> 4;

		if (CaMovAngle > 0)
		{
			if (mv > 32)
			{
				mv = 32;
			}

			any += mv; CaMovAngle -= mv;

			if (CaMovAngle < 0)
			{
				CaMovAngle = 0;
			}
		}
		else
		{
			if (mv < -32) mv = -32;
			any += mv; CaMovAngle -= mv;

			if (CaMovAngle > 0)
			{
				CaMovAngle = 0;
			}
		}

		if (mv == 0)
			CaMovAngle = 0;

		if (CaMovAngle == 0)
			AutoCameraFlag = TRUE;
		else
			AutoCameraFlag = FALSE;
	}

	if (whAnx != ANX_NONE)
	{

		if (anx < whAnx)
		{
			anx += 8;
			if (anx >= whAnx)
			{
				whAnx = ANX_NONE;
				AutoCameraFlag = TRUE;
			}
		}
		else
		{
			anx -= 8;
			if (anx <= whAnx)
			{
				whAnx = ANX_NONE;
				AutoCameraFlag = TRUE;
			}
		}
	}

	if (PlayFloor > 0)
	{
		if (ViewAnx < 500)
			ViewAnx += 8;

		if (ViewDist > 250)
			ViewDist -= 8;

		PlayFloor--;
	}
	else
	{
		if (ViewAnx < anx)
		{
			ViewAnx += 8;

			if (ViewAnx > anx)
			{
				ViewAnx = anx;
			}
		}
		if (ViewAnx > anx)
		{
			ViewAnx -= 8;

			if (ViewAnx < anx)
			{
				ViewAnx = anx;
			}
		}

		if (CaTarDist)
		{
			mv = 100;
		}
		else
		{
			mv = 8;
		}

		if (ViewDist < dist)
		{
			ViewDist += mv;

			if (ViewDist > dist)
			{
				ViewDist = dist;
			}
		}
		if (ViewDist > dist)
		{
			ViewDist -= mv;

			if (ViewDist < dist)
			{
				ViewDist = dist;
			}
		}
	}


	if (DebugPlayer)
	{
		if (dpX == 0 && dpZ == 0)
		{
			dpX = lpCurPlayer->pX;
			dpY = lpCurPlayer->pY;
			dpZ = lpCurPlayer->pZ;
		}

		if (VRKeyBuff[VK_SPACE])
		{
			GetMoveLocation(0, 0, fONE * 2, anx, any, 0);
			dpX += GeoResult_X;
			dpY += GeoResult_Y;
			dpZ += GeoResult_Z;
		}

		if (VRKeyBuff['Z'])
			anz -= 8;

		if (VRKeyBuff['X'])
			anz += 8;

		lpCurPlayer->pX = dpX;
		lpCurPlayer->pZ = dpZ;

		anx &= ANGCLIP;

		if (anx >= ANGLE_90 && anx < ANGLE_270)
		{
			if (anx < ANGLE_180)
				anx = ANGLE_90 - 32;
			else
				anx = ANGLE_270 + 32;
		}
		ViewAnx = anx;
		whAnx = ANX_NONE;

	}
	else
	{
		if (anx >= (ANGLE_90 - 48))
		{
			anx = (ANGLE_90 - 48);
			whAnx = ANX_NONE;
		}
		if (anx < 48)
		{
			anx = 48;
			whAnx = ANX_NONE;
		}
	}

	if (anx > 48 && dist < 34)
	{
		dist = 34;
		CaTarDist = 0;
	}



	int distance = 440;

	if (cSettings::GetInstance()->IsWideScreen())
	{
		distance = 600;
	}

	if (dist > 600)
	{
		dist = 600;
		CaTarDist = 0;
	}

	int ay;
	int astep;

	if (PlayCameraMode != cInterFace.sInterFlags.CameraAutoFlag)
	{
		if (cInterFace.sInterFlags.CameraAutoFlag == 2)
			any = ANGLE_45;
		PlayCameraMode = cInterFace.sInterFlags.CameraAutoFlag;

		if (!dwM_BlurTime)
		{
			dwM_BlurTime = dwPlayTime + 600;
		}
	}

	if (PlayCameraMode == 1 && AutoCameraFlag && any != lpCurPlayer->Angle.y && lpCurPlayer->MoveFlag)
	{
		ay = (any - lpCurPlayer->Angle.y) & ANGCLIP;

		if (ay >= ANGLE_180)
			ay = ay - ANGLE_360;

		if (abs(ay) < (ANGLE_90 + 180))
		{
			if (ay < 0)
			{
				astep = abs(ay) >> 6;
				if (astep < AC_MOVE_STEP)
					astep = AC_MOVE_STEP;

				if (ay < -AC_MOVE_MIN)
				{
					ay += astep;
					if (ay > 0)
						any = lpCurPlayer->Angle.y;
					else
						any = (any + astep) & ANGCLIP;
				}
			}
			else
			{
				astep = abs(ay) >> 6;
				if (astep < AC_MOVE_STEP) astep = AC_MOVE_STEP;

				if (ay > AC_MOVE_MIN)
				{
					ay -= astep;
					if (ay < 0)
						any = lpCurPlayer->Angle.y;
					else
						any = (any - astep) & ANGCLIP;
				}
			}
		}
	}

	NetWorkPlay();
	PlayPat3D();

	MainEffect();

	if (g_IsDxProjectZoomIn)
		MainFullZoomMap();

	dwMemError = dwMemError ^ dwPlayTime;
	dwPlayTime = GetCurrentTime();
	dwMemError = dwMemError ^ dwPlayTime;

	TraceCameraMain();

	RendSightSub(0);
}

POINT3D TargetPosi = { 0,0,0 };
POINT3D GeoResult = { 0,0,0 };

int timeg = 0;
int RenderCnt = 0;
int DispRender;
int	DispMainLoop;

DWORD	dwLastPlayTime = 0;
DWORD	dwLastOverSpeedCount = 0;
int		PlayTimerMax = 0;
int		MainLoopCount = 0;
DWORD	dwLastRenderTime = 0;


void showFPS()
{

}


void PlayD3D()
{
	DWORD dwTime = GetCurrentTime();

	if (dwLastPlayTime)
	{
		if (dwTime < dwLastPlayTime && dwLastOverSpeedCount>1000)
		{
			SendSetHackUser2(1200, dwLastPlayTime - dwTime);
			dwLastOverSpeedCount = 0;
		}
	}

	dwLastPlayTime = dwTime;

	if (FrameSkipTimer == 0)
	{
		FrameSkipTimer = dwTime;
		FpsTime = 1000 / fps;
	}

	if (((int)(dwTime - FrameSkipTimer)) > 5000)
		FrameSkipTimer = dwTime;

	if (FrameSkipTimer > dwTime)
	{
		Sleep(FrameSkipTimer - dwTime);
		dwTime = GetCurrentTime();
		dwLastPlayTime = dwTime;
	}

	pRealCursorPos.x = pCursorPos.x;
	pRealCursorPos.y = pCursorPos.y;


	while (1)
	{
		if (FrameSkipTimer >= dwTime)
			break;

		FrameSkipTimer += FPS_TIME;

		switch (GameMode)
		{
		case 1:
			if (MainOpening() == TRUE)
				SetGameMode(2);
			break;
		case 2:
			PlayMain();

#ifdef _SINBARAM

			if (g_IsDxProjectZoomIn <= 0)
			{
				dsMenuCursorPos(&pCursorPos, 1);
				sinMain();
				dsMenuCursorPos(&pCursorPos, 0);

				MainInterfaceParty(pHoPartyMsgBox.x, pHoPartyMsgBox.y);
			}
			else
				MainSub();

#endif
			if (BellatraEffectInitFlag)
				MainBellatraFontEffect();
			break;
		}

		MainLoopCount++;
		dwLastOverSpeedCount++;
	}

	if (ParkPlayMode)
	{
		if (ParkPlayMode < 0)
		{
			if ((smFlipCount & 1) == 0)
				return;
		}
		else
		{
			if (ParkPlayMode <= 1000)
			{
				if ((dwLastRenderTime + ParkPlayMode) > dwTime)
					return;
			}
		}

	}
	else
	{
		if (GetForegroundWindow() != hwnd)
		{

		}
	}

	dwLastRenderTime = dwTime;

	int i = GetCurrentTime();

	if (timeg < i)
	{
		timeg = i + 1000;
		DispRender = RenderCnt;
		RenderCnt = 0;
		DispMainLoop = MainLoopCount;
		MainLoopCount = 0;
	}

	RenderCnt++;


	if (GameMode == 1)
	{
		DrawOpening();
		showFPS();
		return;
	}

	showFPS();


	if (PlayCameraMode == 2)
	{
		if (cSettings::GetInstance()->IsWideScreen())
		{
			dist = 600;
		}
		else
		{
			dist = 440;
		}

		anx = ANGLE_45 - 128;
		ViewAnx = anx;
		ViewDist = dist;
	}

	any &= ANGCLIP;
	anx &= ANGCLIP;



	if (WaveCameraFlag && WaveCameraMode)
	{
		WaveCameraTimeCount++;

		if ((WaveCameraTimeCount > WaveCameraDelay))
		{
			WaveCameraTimeCount = 0;
			if (WaveCameraDelay > 1 && WaveCameraFactor < 40)
				WaveCameraFactor = -int((float)WaveCameraFactor / 10.f*9.f);
			else
				WaveCameraFactor = -int((float)WaveCameraFactor / 10.f*8.f);
			ViewDist += WaveCameraFactor;
		}

		if (abs(WaveCameraFactor) < 1)
		{
			WaveCameraFlag = FALSE;
			WaveCameraTimeCount = 0;
		}
	}
	else
	{
		WaveCameraFlag = FALSE;
	}

	GetMoveLocation(0, 0, -(ViewDist << FLOATNS), ViewAnx&ANGCLIP, any, 0);

	if (GeoResult_X == GeoResult.x && GeoResult_Y == GeoResult.y && GeoResult_Z == GeoResult.z)
	{
		pX += lpCurPlayer->pX - TargetPosi.x;
		pY += lpCurPlayer->pY - TargetPosi.y;
		pZ += lpCurPlayer->pZ - TargetPosi.z;
	}
	else
	{
		pX = lpCurPlayer->pX;
		pY = lpCurPlayer->pY;
		pZ = lpCurPlayer->pZ;

		pX += GeoResult_X;
		pZ += GeoResult_Z;
		pY += GeoResult_Y;

		GeoResult.x = GeoResult_X;
		GeoResult.y = GeoResult_Y;
		GeoResult.z = GeoResult_Z;
	}

	TargetPosi.x = lpCurPlayer->pX;
	TargetPosi.y = lpCurPlayer->pY;
	TargetPosi.z = lpCurPlayer->pZ;


	if (DebugPlayer)
	{
		lpCurPlayer->Angle.y = any;

		pX = dpX;
		pY = dpY;
		pZ = dpZ;


		any = lpCurPlayer->Angle.y;
	}
	else
	{
		anz = 0;
	}

	if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_SHIFT])
	{
		if (VRKeyBuff[VK_HOME])
			DarkLevel = 220;
		if (VRKeyBuff[VK_END])
			DarkLevel = 0;
	}


	LockSpeedProtect(lpCurPlayer);


	EnterCriticalSection(&cDrawSection);
	smEnterTextureCriticalSection();



	DWORD	dwSkilChkSum = 0;
	DWORD	dwChkSum;
	DWORD	dwLevelQuestSum;
	int		cnt, k;

	for (cnt = 0; cnt < SIN_MAX_USE_SKILL; cnt++)
	{
		k = (cnt + 5) << 2;
		dwSkilChkSum += sinSkill.UseSkill[cnt].UseSkillCount*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Point*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Mastery*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].GageLength*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[0] * k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[1] * k;
	}

	dwLevelQuestSum = sinQuest_levelLog & 0x576321cc;


	smPlayD3D(pX, pY, pZ, (ViewAnx&ANGCLIP), (any&ANGCLIP), (anz&ANGCLIP));

	dwChkSum = 0;
	for (cnt = 0; cnt < SIN_MAX_USE_SKILL; cnt++)
	{
		k = (cnt + 5) << 2;
		dwChkSum += sinSkill.UseSkill[cnt].UseSkillCount*k;
		dwChkSum += sinSkill.UseSkill[cnt].Point*k;
		dwChkSum += sinSkill.UseSkill[cnt].Mastery*k;
		dwChkSum += sinSkill.UseSkill[cnt].GageLength*k;
		dwChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[0] * k;
		dwChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[1] * k;
	}

	if (dwSkilChkSum != dwChkSum)
	{

		SendSetHackUser3(8540, dwSkilChkSum, dwChkSum);
	}

	if (dwLevelQuestSum != (sinQuest_levelLog & 0x576321cc))
	{

		SendSetHackUser3(8820, (dwLevelQuestSum & 0x576321cc), sinQuest_levelLog);
	}

	int mapY;
	int x, z, y;

	GetMoveLocation(0, 0, -(dist << FLOATNS), anx, any, 0);

	x = lpCurPlayer->pX + GeoResult_X;
	y = lpCurPlayer->pY + GeoResult_Y;
	z = lpCurPlayer->pZ + GeoResult_Z;

	PlayFloor = 0;
	y = 0;

	if (!DebugPlayer)
	{
		if (smGameStage[0])
		{
			mapY = (smGameStage[0]->GetHeight2(x, z));
			if (mapY > CLIP_OUT)
				y++;
		}

		if (smGameStage[1])
		{
			mapY = (smGameStage[1]->GetHeight2(x, z));
			if (mapY > CLIP_OUT)
				y++;
		}

		if (!y)
			PlayFloor = 64;
	}



	smLeaveTextureCriticalSection();
	LeaveCriticalSection(&cDrawSection);


	UnlockSpeedProtect(lpCurPlayer);

}

extern int DispPolyCnt;
extern int GetMouseMapPoint(int x, int y);

extern int xframe;

int GetPlayMouseAngle()
{
	int ax, az, ay;

	ax = xPs - (WinSizeX >> 1);
	az = yPs - (WinSizeY >> 1);
	ay = GetRadian2D(0, 0, ax, -az);

	return ay + any;
}

int GetActionGame_PlayMouseAngle()
{
	int ax, az, ay;

	ax = xPs - lpCurPlayer->RendPoint.x;
	az = yPs - lpCurPlayer->RendPoint.x;
	ay = GetRadian2D(0, 0, ax, -az);

	return ay;;
}

int SetMousePlay(int flag)
{
	int ax, az, ay;
	char szBuff[256];
	int	cnt;


	if (GameMode != 2) return TRUE;


	if (SettingsUI::getInstance()->getStatus())
	{
		return TRUE;
	}

	if (!lpCurPlayer->MotionInfo || dwNextWarpDelay || lpCurPlayer->PlayStunCount) return FALSE;

	if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD) return FALSE;


#ifdef _SINBARAM


	if (g_IsDxProjectZoomIn <= 0)
	{


		dsMenuCursorPos(&pCursorPos, 2);
		if (StopCharMotion(pCursorPos.x, pCursorPos.y) == TRUE)
		{
			if (lpCurPlayer->MotionInfo->State < 0x100 && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_STAND)
			{
				lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_STAND);
				lpCurPlayer->MoveFlag = FALSE;
			}
			flag = 0;

		}
		dsMenuCursorPos(&pCursorPos, 0);
	}

#endif

	switch (flag)
	{
	case 1:

#ifdef	_NEW_PARTRADE

		if (EachTradeButton && chrEachMaster)
		{
			cnt = GetPartyTradeButtonPos(xPs, yPs);
			if (cnt >= 0)
			{
				EachTradeButton = 0;
				switch (cnt)
				{
				case 0:

					if (GetTradeDistanceFromCode(chrEachMaster->dwObjectSerial) == TRUE)
					{

						SendRequestTrade(chrEachMaster->dwObjectSerial, 0);
						wsprintf(szBuff, mgRequestTrade, chrEachMaster->smCharInfo.szName);
					}
					else
					{
						wsprintf(szBuff, mgRequestTrade2, chrEachMaster->smCharInfo.szName);
					}
					return TRUE;

				case 1:

					wsprintf(szBuff, "//party %s", chrEachMaster->smCharInfo.szName);
					SendChatMessageToServer(szBuff);
					return TRUE;

				case 2:

					InterfaceParty.latest_Insert(chrEachMaster->smCharInfo.szName);
					InterfaceParty.friend_Insert(chrEachMaster->smCharInfo.szName);

					InterfaceParty.Main_menuSet(2);
					InterfaceParty.chat_changeMENU(1);
					if (InterfaceParty.PartyPosState == PARTY_NONE)	ShowParty();
					return TRUE;

				case 3:


					g_IsCheckClanMember(chrEachMaster);
					return TRUE;

				}
			}
		}


#else
		if (EachTradeButton == 2 && chrEachMaster)
		{
			EachTradeButton = 0;


			if (GetTradeDistanceFromCode(chrEachMaster->dwObjectSerial) == TRUE)
			{

				SendRequestTrade(chrEachMaster->dwObjectSerial, 0);

				wsprintf(szBuff, mgRequestTrade, chrEachMaster->smCharInfo.szName);
			}
			else
			{

				wsprintf(szBuff, mgRequestTrade2, chrEachMaster->smCharInfo.szName);
			}

			AddChatBuff(szBuff);
			break;
		}
#endif

		if (GetFieldMapCursor() == TRUE && cInterFace.sInterFlags.MapOnFlag)
		{
			if (lpCurPlayer->smCharInfo.Level < 20)
			{
				sinCheck_ShowHelpMap();
			}
			break;
		}

		if (!ActionGameMode)
		{


			if (lpCharSelPlayer || lpSelItem)
			{
				SelMouseButton = 1;
				TraceAttackPlay();
				AutoCameraFlag = FALSE;
			}
			else
			{
				if (MsTraceMode && !lpCharSelPlayer && !lpSelItem)
				{
					if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK &&
						lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_SKILL)
						lpCurPlayer->SetTargetPosi(0, 0);
					CancelAttack();
				}
				AutoCameraFlag = TRUE;
			}
		}
		else
		{
			ActionMouseClick[0] = 1;
		}

		AutoMouse_WM_Count++;


		if (SkillMasterFlag)
		{

			sinSkillMasterClose();
		}

		lpCurPlayer->MoveFlag = TRUE;
		DispEachMode = 0;

		if (hFocusWnd)
		{
			GetWindowText(hFocusWnd, szBuff, 240);
			if (szBuff[0] == 0)
			{
				hFocusWnd = 0;
				szLastWhisperName[0] = 0;
				LastWhisperLen = 0;
				InterfaceParty.chat_WhisperPartyPlayer_close();
				chatlistSPEAKERflagChg(0);
				SetIME_Mode(0);
				ChatScrollPoint = 0;


			}
		}
		break;

	case 0:


		if (Moving_DblClick)
		{
			TraceMode_DblClick = TRUE;
			Moving_DblClick = 0;
			lpCurPlayer->MoveFlag = TRUE;
			ActionMouseClick[0] = 2;

		}
		else
		{
			if (!lpCharMsTrace && !lpMsTraceItem)
			{
				lpCurPlayer->SetAction(0);
			}
		}
		return TRUE;

	case 11:
		if (hFocusWnd)
		{
			GetWindowText(hFocusWnd, szBuff, 240);
			if (szBuff[0] == 0)
			{
				hFocusWnd = 0;
				SetIME_Mode(0);
				ChatScrollPoint = 0;


			}
		}

		if (sinSkill.pRightSkill && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK &&
			lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_SKILL)
		{

			if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_EAT)
			{

				if (OpenPlaySkill(sinSkill.pRightSkill))
					break;
			}
		}

		if (!ActionGameMode)
		{
			if (lpCharSelPlayer)
			{
				SelMouseButton = 2;
				TraceAttackPlay();
				AutoCameraFlag = FALSE;
				lpCurPlayer->MoveFlag = TRUE;
				DispEachMode = 0;
			}
		}
		else
		{
			ActionMouseClick[1] = TRUE;
		}


		AutoMouse_WM_Count++;
		break;
	case 10:

		if (!lpCharMsTrace && !lpMsTraceItem)
		{
			lpCurPlayer->SetAction(0);
		}
		break;

	case 3:




		ay = msY * 4;
		ax = msX * 8;

		if (ay)
		{
			if (!CaTarDist) CaTarDist = dist;
			CaTarDist -= ay;


			if (CaTarDist < 100)
			{
				if (anx <= 40)
				{
					if (CaTarDist < 40)
						CaTarDist = 40;
				}
				else
					CaTarDist = 100;
			}

			if (CaTarDist > 440)
			{
				CaTarDist = 440;
			}

		}

		if (ax)
		{
			if (cSettings::GetInstance()->cCamInv)
			{
				ax = -ax;
			}

			az = ANGLE_45 >> 1;
			if (ax < -az) ax = -az;
			if (ax > az) ax = az;

			CaMovAngle += ax;
		}

		return TRUE;

	case 4:
		if (DebugPlayer)
		{


			ay = msY * 2;
			ax = msX * 2;

			any += ax;
			anx += ay;

			any &= ANGCLIP;
			anx &= ANGCLIP;

		}
		return TRUE;
	}

	if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_ATTACK ||
		lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_SKILL ||
		lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_YAHOO
		) return FALSE;


	if (lpCurPlayer->MoveFlag)
	{

		if (MsTraceMode)
		{
			lpCurPlayer->Angle.y = GetMouseSelAngle();

		}
		else
		{
			if (ActionGameMode)
				lpCurPlayer->Angle.y = GetActionGame_PlayMouseAngle();
			else
				lpCurPlayer->Angle.y = GetPlayMouseAngle();
		}
	}

	return TRUE;
}

extern int TestTraceMatrix();

int InitD3D(HWND hWnd)
{
	Log::getInstance()->output(LOG_DEBUG, "InitD3D() - WinSizeX(%d)   WinSizeY(%d)   WinColBit(%d)", WinSizeX, WinSizeY, WinColBit);
	hwnd = hWnd;

	MidX = WinSizeX / 2;
	MidY = WinSizeY / 2;
	MidY -= 59;

	int iHeightRatio = (WinSizeX / 4) * 3;
	if (iHeightRatio == WinSizeY)
		viewdistZ = WinSizeX;
	else
		viewdistZ = (WinSizeY / 3) * 4;




	viewdistZ = (smScreenHeight * 4) / 3;




	if (!CreateD3D())
	{
		Log::getInstance()->output(LOG_DEBUG, "CreateD3D() failed");
		return FALSE;
	}

	Log::getInstance()->output(LOG_DEBUG, "CreateD3D() success");

	if (!SetDisplayMode(hWnd, WinSizeX, WinSizeY, WinColBit))
	{
		Log::getInstance()->output(LOG_DEBUG, "SetDisplayMode() failed");
		return FALSE;
	}

	Log::getInstance()->output(LOG_DEBUG, "SetDisplayMode() success");

	TestTraceMatrix();

	InitRender();

	InitTexture();


	smSetTextureLevel(cSettings::GetInstance()->cTexture);

	Check_CodeSafe((DWORD)GameInit);

	InitSoundEffect(hwnd);
	InitPatterns();


	lpCurPlayer = InitRotPlayer();

	return Code_VRamBuffOpen();
}

void CloseD3d()
{
	CloseRotPlayer();

	CloseSoundEffect();

	CloseTexture();

	ReleaseD3D();
}

int GameInit()
{
	g_IsReadTextures = 1;

	dwPlayTime = GetCurrentTime();
	dwMemError = dwMemError ^ dwPlayTime;

	InitMaterial();
	smRender.SetMaterialGroup(smMaterialGroup);

	ReformCharForm();

	InitEffect();

	InitMotionBlur();
	InitBackGround();

	Check_CodeSafe((DWORD)CloseD3d);

	InitStage();
	InitPat3D();

	CreateItem2PassTexture();


	CheckCharForm();





#ifdef _SINBARAM
	lpDDSMenu = 0;
	sinInit();
#else
	lpDDSMenu = LoadDibSurfaceOffscreen(smConfig.szFile_Menu);
#endif


	g_fWinSizeRatio_X = float(WinSizeX) / 800.f;
	g_fWinSizeRatio_Y = float(WinSizeY) / 600.f;

	CreateBeforeFullZoomMap();
	CreateFontImage();

#ifdef BMFONT
	font[Weight::normal]->reset();
	font[Weight::bold]->reset();
#endif


	TraceCameraPosi.x = lpCurPlayer->pX;
	TraceCameraPosi.y = lpCurPlayer->pY;
	TraceCameraPosi.z = lpCurPlayer->pZ;

	TraceTargetPosi.x = lpCurPlayer->pX;
	TraceTargetPosi.y = lpCurPlayer->pY;
	TraceTargetPosi.z = lpCurPlayer->pZ;

	InitMessageBox();


	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;
	MidX = WinSizeX / 2;
	MidY = WinSizeY / 2;



	viewdistZ = (smScreenHeight * 4) / 3;



	g_IsReadTextures = 1;


	ReadTextures();

	CheckOftenMeshTextureSwap();


	if (cSettings::GetInstance()->cSound)
	{
		if (StageField[0])
			PlayBGM_Direct(StageField[0]->BackMusicCode);
		else
		{
			OpenBGM("game\\Audio\\bgm\\Field - Desert - Pilgrim.bgm");
			PlayBGM();
		}
	}
	CharPlaySound(lpCurPlayer);
	StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
	RestartPlayCount = 700;


	hFocusWnd = 0;
	szLastWhisperName[0] = 0;
	LastWhisperLen = 0;
	InterfaceParty.chat_WhisperPartyPlayer_close();
	chatlistSPEAKERflagChg(0);
	SendMessage(hTextWnd, EM_SETLIMITTEXT, 78, 0);

	MouseButton[0] = 0;
	MouseButton[1] = 0;
	MouseButton[2] = 0;




	smCHAR	*lpTempChar;
	lpTempChar = SelectRotPlayer(lpCurPlayer);
	if (lpTempChar)
	{
		lpCurPlayer = lpTempChar;
		sinChar = &lpCurPlayer->smCharInfo;
	}
	lpTempChar = SelectRotPlayer(lpCurPlayer);
	if (lpTempChar)
	{
		lpCurPlayer = lpTempChar;
		sinChar = &lpCurPlayer->smCharInfo;
	}


	SetIME_Mode(0);


	ReformSkillInfo();


	HoMsgBoxMode = 1;
	SetMessageFrameSelect(HoMsgBoxMode);



	CreateWinIntThread();


	return TRUE;
}


int GameClose()
{



	if (lpDDSMenu) lpDDSMenu->Release();




	ClosePat3D();
	CloseBackGround();
	CloseStage();

#ifdef _SINBARAM
	sinClose();
#endif
	CloseMaterial();



	DestroyWinIntThread();


	if (BellatraEffectInitFlag)
		DestroyBellatraFontEffect();

	return TRUE;
}


int DisplayLogoImage()
{
	LPDIRECT3DTEXTURE9 LogoImage = LoadDibSurfaceOffscreen("Image\\Logo.bmp");

	if (LogoImage)
	{


		BeginRender();

		DrawSprite(WinSizeX / 2 - 400, WinSizeY / 2 - 300, LogoImage, 0, 0, 800, 600);

		Sleep(1500);



		LogoImage->Release();

		EndRender();
	}

	return TRUE;
}

int SetGameMode(int mode)
{
	int OldMode = GameMode;
	GameMode = mode;


	sinChar = &lpCurPlayer->smCharInfo;


	switch (OldMode)
	{
	case 1:

		CloseOpening();
		CloseMaterial();
		smInitColorZClip(0, 0, 0);
		break;

	case 2:
		GameClose();
		break;
	}


	switch (GameMode)
	{
	case 1:
		SetDxProjection((PI / 4.4f), smScreenWidth, smScreenHeight, 20.f, 4000.f);


		smRender.CreateRenderBuff(cSettings::GetInstance()->cCamShake);


		InitMaterial();
		smRender.SetMaterialGroup(smMaterialGroup);
		InitEffect();

		DisplayLogoImage();

		InitOpening();



		if (cSettings::GetInstance()->IsWideScreen())
		{
			smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;
		}
		else
		{
			smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_WIDE_MULT_PERSPECTIVE_HEIGHT;
		}




		MidX = smScreenWidth / 2;
		MidY = smScreenHeight / 2;

		if (CheckCrackProcess(TRUE))
			quit = 1;

		dwM_BlurTime = 0;

		break;

	case 2:

		if (smRender.m_GameFieldView)
		{
			smRender.m_GameFieldViewStep = 22;
			smRender.SetGameFieldViewStep();
		}

		GameInit();


		if (CheckCrackProcess())
			quit = 1;
		break;
	}

	WaveCameraFlag = FALSE;

	return TRUE;
}

float xr = 0;

int jcnt = 0;

float brt = 1;
float bs = 0;


int ox = 0, oy = 0, oz = 0;

int GoText = 0;

char strBuff[240];
char strBuff2[256];


int NumPoly;
int Disp_tx, Disp_ty;
int Disp_rx, Disp_ry;


smCHAR	*lpCharMsgSort[OTHER_PLAYER_MAX];
int ChatMsgSortCnt;

extern int Debug_RecvCount1;
extern int Debug_RecvCount2;
extern int Debug_SendCount;
extern BUFF_KILL BuffKill[32];

int RestoreInterfaceTexture()
{
	int cnt;

	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;
	smRender.Color_A = 0;

	cnt = 0;

	d3ddev->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_MODULATE);
	d3ddev->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	d3ddev->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

	d3ddev->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	d3ddev->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	d3ddev->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	d3ddev->SetTexture(cnt, 0);

	for (cnt = 1; cnt < 8; cnt++)
	{
		d3ddev->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_DISABLE);
		d3ddev->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		d3ddev->SetTexture(cnt, 0);
	}

	return TRUE;
}

void VirtualDrawGameState(void)
{
	smRender.ClearLight();

	int BackDarkLevel;

	BackDarkLevel = DarkLevel;
	DarkLevel = 0;



	RestoreInterfaceTexture();


	if (DisconnectFlag)
	{

		if (DisconnectServerCode == 0)
			DrawMessage(MidX - 64, MidY, mgDiconnect, 36, BOX_ONE);

		if (DisconnectServerCode == 1)
			DrawMessage(MidX - 64, MidY, mgDiconnect1, 36, BOX_ONE);

		if (DisconnectServerCode == 2)
			DrawMessage(MidX - 64, MidY, mgDiconnect2, 36, BOX_ONE);

		if (DisconnectServerCode == 3)
			DrawMessage(MidX - 64, MidY, mgDiconnect3, 36, BOX_ONE);

		if (DisconnectServerCode == 4)
			DrawMessage(MidX - 64, MidY, mgDiconnect4, 36, BOX_ONE);


#ifdef	_WINMODE_DEBUG
		if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR && !quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime)
			quit = TRUE;
#else
		if (!quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime)
			quit = TRUE;
#endif
	}
	else
	{
		if (quit)
			DrawMessage(MidX - 40, MidY, mgCloseGame, 36, BOX_ONE);
		else
		{
			if (dwCloseBoxTime && dwCloseBoxTime > dwPlayTime)
			{
				DrawMessage(MidX - 100, MidY, mgCloseWindow, 36, BOX_ONE);
			}
			else
			{
				if (dwBattleQuitTime)
				{
					if ((dwBattleQuitTime + 5000) > dwPlayTime)
						DrawMessage(MidX - 40, MidY, mgCloseBattle, 36, BOX_ONE);
					else
						dwBattleQuitTime = 0;
				}
			}
		}
	}

	if (d3ddev)
	{

		DrawCursor();

	}

	DarkLevel = BackDarkLevel;
}

int DrawGameState()
{
	Shop::GetInstance()->coinsInvetario();

	int i;
	int cnt, cnt2;
	int	y, DispBar, DispMaster;
	smCHAR	*lpChar;
	scITEM	*lpItem;
	RECT	ddRect;
	int BackDarkLevel;
	DWORD	dwColor;

	int personagem = 0;

	ddRect.left = 0;
	ddRect.right = 800;
	ddRect.top = 0;
	ddRect.bottom = 150;

	if (lpDDSMenu)
	{
		DrawSprite(0, WinSizeY - 150, lpDDSMenu, 0, 0, 800, 150);
	}

	smRender.ClearLight();

	BackDarkLevel = DarkLevel;
	DarkLevel = 0;


	RestoreInterfaceTexture();

	if (lpCharMsTrace && lpCharMsTrace->RendSucess)
	{
		Disp_tx = lpCharMsTrace->RendPoint.x - 32;
		Disp_ty = lpCharMsTrace->RendPoint.y - 12;
	}

	if (lpCharSelPlayer && lpCharMsTrace != lpCharSelPlayer)
	{
		if (lpCharSelPlayer->RendSucess)
		{
			Disp_rx = lpCharSelPlayer->RendPoint.x - 32;
			Disp_ry = lpCharSelPlayer->RendPoint.y - 12;
		}
	}

	lpChar = 0;
	lpItem = 0;

	if (lpMsTraceItem)
		lpItem = lpMsTraceItem;
	else
		lpItem = lpSelItem;

	if (VRKeyBuff['A'])
	{
		for (cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
		{
			if (scItems[cnt].Flag && scItems[cnt].ItemCode != 0 && lpSelItem != &scItems[cnt] && CanViewDropItem(&scItems[cnt]))
			{
				if (scItems[cnt].RendPoint.z >= 32 * fONE && scItems[cnt].RendPoint.z < 64 * 12 * fONE)
				{
					DrawCharacterMessage(scItems[cnt].RendPoint.x, scItems[cnt].RendPoint.y, scItems[cnt].szName, 0, 0, 0, RGB(255, 255, 255));
				}
			}
		}
	}

	if (lpSelItem && !lpCharSelPlayer && !lpCharMsTrace)
	{

		Disp_tx = MsSelPos.x;
		Disp_ty = MsSelPos.y;

		DrawCharacterMessage(Disp_tx, Disp_ty, lpSelItem->szName, 0, 0, 0, RGB(180, 180, 180));

	}


	int	SelFlag;

	ChatMsgSortCnt = 0;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].RendSucess && chrOtherPlayer[cnt].smCharInfo.szName[0])
		{

			SelFlag = 0;
			if (chrOtherPlayer[cnt].RendPoint.z < 12 * 64 * fONE)
			{
				if (chrOtherPlayer[cnt].szChatMessage[0])
				{

					if (chrOtherPlayer[cnt].dwChatMessageTimer < dwPlayTime)
						chrOtherPlayer[cnt].szChatMessage[0] = 0;
					else
					{
						if (chrOtherPlayer[cnt].smCharInfo.State)
						{
							lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
							SelFlag++;
						}
					}
				}

				if (chrOtherPlayer[cnt].dwTradeMsgCode && !SelFlag)
				{
					lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
					SelFlag++;
				}
			}
			if (!SelFlag)
			{//Exibir Infos
				if (lpCharMsTrace == &chrOtherPlayer[cnt] || lpCharSelPlayer == &chrOtherPlayer[cnt] ||
					(chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_NPC && chrOtherPlayer[cnt].RendPoint.z < 12 * 64 * fONE) ||
					(chrOtherPlayer[cnt].smCharInfo.Life[0] > 0 && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY && chrOtherPlayer[cnt].smCharInfo.Brood == smCHAR_MONSTER_USER) ||
					(chrOtherPlayer[cnt].smCharInfo.ClassClan && chrOtherPlayer[cnt].smCharInfo.ClassClan == lpCurPlayer->smCharInfo.ClassClan) ||
					(HoMsgBoxMode && chrOtherPlayer[cnt].dwClanManageBit) || chrOtherPlayer[cnt].PartyFlag || chrOtherPlayer[cnt].PlayerGm || chrOtherPlayer[cnt].PlayCursePvP || chrOtherPlayer[cnt].PlayerTopLevel || chrOtherPlayer[cnt].PlayerBeta)
				{
					lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
				}
			}
		}
	}

	if (lpCurPlayer->szChatMessage[0])
	{
		if (lpCurPlayer->dwChatMessageTimer < dwPlayTime)
			lpCurPlayer->szChatMessage[0] = 0;
		else
			lpCharMsgSort[ChatMsgSortCnt++] = lpCurPlayer;
	}
	else
	{
		if (lpCurPlayer->dwTradeMsgCode)
			lpCharMsgSort[ChatMsgSortCnt++] = lpCurPlayer;
	}



	if (ChatMsgSortCnt)
	{
		for (cnt = 0; cnt < ChatMsgSortCnt; cnt++)
		{
			for (cnt2 = cnt + 1; cnt2 < ChatMsgSortCnt; cnt2++)
			{
				if (lpCharMsgSort[cnt]->RendPoint.z < lpCharMsgSort[cnt2]->RendPoint.z || lpCharMsgSort[cnt] == lpCharMsTrace || lpCharMsgSort[cnt] == lpCharSelPlayer)
				{
					lpChar = lpCharMsgSort[cnt];
					lpCharMsgSort[cnt] = lpCharMsgSort[cnt2];
					lpCharMsgSort[cnt2] = lpChar;
				}
			}
		}
	}

	LPDIRECT3DTEXTURE9 lpDDS_clanMark;
	char *szClanName;
	//char *szBoxMsg;
	BOOL  selectedBox;

	y = 8 + (ViewAnx >> 7);


	int BossCnt = 0;

	for (int cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State != smCHAR_STATE_NPC)
		{
			if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.Life[1] == 0 && chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_MOKOVA || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_MUNDO || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_SHY || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_TULLA || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_WLORD || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_DRAXOS || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_MIDRANDA || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_GREEDY || chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT)
			{
				BossCnt++;
			}
		}
	}

	if (!BossCnt) Battle::GetInstance()->Hide();

	if (StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_VILLAGE)
	{

		DrawDamage::GetInstance()->CurRenderDamage(lpCurPlayer);

		for (int cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State != smCHAR_STATE_NPC)
			{
				if (chrOtherPlayer[cnt].Flag)
				{
					DrawDamage::GetInstance()->RenderDamage(&chrOtherPlayer[cnt]);
				}
			}
		}
	}

	for (cnt = 0; cnt < ChatMsgSortCnt; cnt++)
	{
		dwColor = RGB(230, 255, 160);

		DispBar = FALSE;
		DispMaster = FALSE;
		selectedBox = FALSE;

		if (lpCharMsgSort[cnt]->PartyFlag)
		{
			dwColor = RGB(220, 255, 160);
			DispBar = TRUE;
		}
		else if (lpCharMsgSort[cnt]->smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			if (lpCharMsgSort[cnt]->smCharInfo.Brood == smCHAR_MONSTER_USER)
			{
				dwColor = RGB(220, 255, 160);


				if (lpCharMsgSort[cnt]->smCharInfo.Next_Exp == lpCurPlayer->dwObjectSerial || lpCharMsgSort[cnt]->smCharInfo.ClassClan)
					DispBar = TRUE;
				else
					DispMaster = TRUE;
			}
			else
				dwColor = RGB(255, 210, 210);
		}
		else if (lpCharMsgSort[cnt]->smCharInfo.State == smCHAR_STATE_NPC)
		{
			dwColor = RGB(180, 180, 255);
		}

		if (lpCharMsgSort[cnt] == lpCharMsTrace)
		{
			if (lpCharMsgSort[cnt]->smCharInfo.State == smCHAR_STATE_ENEMY && lpCharMsgSort[cnt]->smCharInfo.Brood != smCHAR_MONSTER_USER)
				dwColor = RGB(255, 230, 200);
			else {
				dwColor = RGB(255, 255, 255);
				personagem = 1;
			}

			selectedBox = TRUE;
		}
		else
		{
			if (lpCharMsgSort[cnt] == lpCharSelPlayer && lpCharMsgSort[cnt]->szChatMessage[0]) selectedBox = TRUE;
		}

		lpDDS_clanMark = 0;
		szClanName = 0;
		DWORD	dwClanMgrBit;

		char * MsgTopLevel;
		MsgTopLevel = 0;
		switch (lpCharMsgSort[cnt]->smCharInfo.JOB_CODE)
		{
		case 1:
			MsgTopLevel = "Guerreiro Imortal";
			break;

		case 2:
			MsgTopLevel = "Metaleiro";
			break;

		case 3:
			MsgTopLevel = "Sagitária";
			break;

		case 4:
			MsgTopLevel = "Lancelot";
			break;

		case 5:
			MsgTopLevel = "Valhala";
			break;

		case 6:
			MsgTopLevel = "Cavaleiro Santo";
			break;

		case 7:
			MsgTopLevel = "Bruxo";
			break;

		case 8:
			MsgTopLevel = "Celestial";
			break;
		case 9:
			MsgTopLevel = "Andarilha das Sombras";
			break;
		case 10:
			MsgTopLevel = "Coletor de Almas";
			break;
		}

		if (lpCharMsgSort[cnt]->smCharInfo.ClassClan)
		{
			if (lpCharMsgSort[cnt] == lpCurPlayer)
			{
				lpDDS_clanMark = cldata.hClanMark;
				szClanName = cldata.name;
			}
			else if (lpCharMsgSort[cnt]->ClanInfoNum >= 0)
			{
				lpDDS_clanMark = ClanInfo[lpCharMsgSort[cnt]->ClanInfoNum].hClanMark;
				szClanName = ClanInfo[lpCharMsgSort[cnt]->ClanInfoNum].ClanInfoHeader.ClanName;
			}
		}


		if (((lpCharMsgSort[cnt]->szChatMessage[0] || lpCharMsgSort[cnt]->dwTradeMsgCode) && lpCharMsgSort[cnt]->smCharInfo.State && lpCharMsgSort[cnt]->RendPoint.z < 12 * 64 * fONE) ||
			lpCharMsgSort[cnt] == lpCurPlayer)
		{
			if (szClanName && lpCharMsgSort[cnt] != lpCharMsTrace && lpCharMsgSort[cnt] != lpCharSelPlayer)
			{
				if (!lpCurPlayer->smCharInfo.ClassClan || lpCharMsgSort[cnt]->smCharInfo.ClassClan != lpCurPlayer->smCharInfo.ClassClan)
					szClanName = 0;
			}

			if (lpCharMsgSort[cnt]->szChatMessage[0])
			{
				DrawCharacterMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
					lpCharMsgSort[cnt]->szChatMessage, 30, lpDDS_clanMark, szClanName, dwColor, selectedBox);
			}
			else
			{
				if (lpCharMsgSort[cnt]->szTradeMessage[0])
				{
					DrawCharacterShopByeMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
						lpCharMsgSort[cnt]->szTradeMessage, 30, lpDDS_clanMark, dwColor, selectedBox);
				}
			}
		}
		else
		{
			if (DispMaster && !lpCharMsgSort[cnt]->smCharInfo.ClassClan)
			{

				wsprintf(strBuff, "(%s)", lpCharMsgSort[cnt]->smCharInfo.szModelName2 + 1);
				DrawTwoLineMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
					lpCharMsgSort[cnt]->smCharInfo.szName, strBuff, dwColor, RGB(255, 255, 200), 0, selectedBox);

			}
			else
			{
				if (HoMsgBoxMode)
					dwClanMgrBit = lpCharMsgSort[cnt]->dwClanManageBit;
				else
					dwClanMgrBit = 0;

				if (!VRKeyBuff['A'])
				{
					if (szClanName)
					{
						if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_CONTROL])
							wsprintf(strBuff, "%d/%d", lpCharMsgSort[cnt]->smCharInfo.ClassClan, lpCharMsgSort[cnt]->ClanInfoNum);
						else
							wsprintf(strBuff, "%s", szClanName);


						//Nenhum Atributo
						if ((!lpCharMsgSort[cnt]->PlayerGm) && (!lpCharMsgSort[cnt]->PlayCursePvP) && (!lpCharMsgSort[cnt]->PlayerTopLevel) && (!lpCharMsgSort[cnt]->PlayerBeta)) {
							DrawTwoLineMessageTitle(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
								strBuff, lpCharMsgSort[cnt]->smCharInfo.szName, "", RGB(150, 255, 200), RGB(255, 255, 255), RGB(198, 65, 0), lpDDS_clanMark, selectedBox, dwClanMgrBit);
						}
						//Somente GM
						else if ((lpCharMsgSort[cnt]->PlayerGm) && (!lpCharMsgSort[cnt]->PlayCursePvP) && (!lpCharMsgSort[cnt]->PlayerTopLevel)) {
							DrawTwoLineMessageTitle(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
								strBuff, "Administrador", lpCharMsgSort[cnt]->smCharInfo.szName, RGB(150, 255, 200), RGB(198, 65, 0), RGB(230, 255, 160), lpDDS_clanMark, selectedBox, dwClanMgrBit);
						}
						//Somente Chefe de Classe
						else if ((lpCharMsgSort[cnt]->PlayCursePvP) && (!lpCharMsgSort[cnt]->PlayerGm) && (!lpCharMsgSort[cnt]->PlayerTopLevel)) {
							DrawTwoLineMessageTitle(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
								strBuff, MsgTopLevel, lpCharMsgSort[cnt]->smCharInfo.szName, RGB(150, 255, 200), RGB(204, 153, 51), RGB(230, 255, 160), lpDDS_clanMark, selectedBox, dwClanMgrBit);
						}
						//GM + Chefe de Classe
						else if ((lpCharMsgSort[cnt]->PlayerGm) && (lpCharMsgSort[cnt]->PlayCursePvP) && (!lpCharMsgSort[cnt]->PlayerTopLevel)) {
							DrawTwoLineMessageTitle(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
								strBuff, "Administrador", lpCharMsgSort[cnt]->smCharInfo.szName, RGB(150, 255, 200), RGB(198, 65, 0), RGB(230, 255, 160), lpDDS_clanMark, selectedBox, dwClanMgrBit);
						}
						//Jogador Beta
						else if ((lpCharMsgSort[cnt]->PlayerBeta)) {
							DrawTwoLineMessageTitle(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
								strBuff, "Honor Member", lpCharMsgSort[cnt]->smCharInfo.szName, RGB(255, 255, 255), RGB(0, 191, 255), RGB(230, 255, 160), lpDDS_clanMark, selectedBox, dwClanMgrBit);
						}
					}
					else
					{

						if ((!lpCharMsgSort[cnt]->PlayerGm) && (!lpCharMsgSort[cnt]->PlayerTopLevel) && (!lpCharMsgSort[cnt]->PlayCursePvP) && (!lpCharMsgSort[cnt]->PlayerBeta)) 
						{
							if (lpCharMsgSort[cnt]->PlayerBeta) AddChatBuff("1");

							DrawCharacterMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
								lpCharMsgSort[cnt]->smCharInfo.szName, 50, lpDDS_clanMark, szClanName, RGB(230, 255, 160), selectedBox, dwClanMgrBit);
						}
						//Somente GM
						else if ((lpCharMsgSort[cnt]->PlayerGm) && (!lpCharMsgSort[cnt]->PlayerTopLevel) && (!lpCharMsgSort[cnt]->PlayCursePvP)) {
							DrawTwoLineMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
								"Administrador", lpCharMsgSort[cnt]->smCharInfo.szName, RGB(198, 65, 0), RGB(230, 255, 160), lpDDS_clanMark, selectedBox, dwClanMgrBit);
						}
						//Somente Chefe de Classe
						else if ((lpCharMsgSort[cnt]->PlayCursePvP) && (!lpCharMsgSort[cnt]->PlayerGm) && (!lpCharMsgSort[cnt]->PlayerTopLevel)) {
							DrawTwoLineMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
								MsgTopLevel, lpCharMsgSort[cnt]->smCharInfo.szName, RGB(204, 153, 51), RGB(230, 255, 160), lpDDS_clanMark, selectedBox, dwClanMgrBit);
						}
						//GM + Chefe de Classe
						else if ((lpCharMsgSort[cnt]->PlayCursePvP) && (lpCharMsgSort[cnt]->PlayerGm) && (!lpCharMsgSort[cnt]->PlayerTopLevel)) {
							DrawTwoLineMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
								"Administrador", lpCharMsgSort[cnt]->smCharInfo.szName, RGB(150, 255, 200), RGB(230, 255, 160), lpDDS_clanMark, selectedBox, dwClanMgrBit);
						}
						//Jogador Beta
						else if ((lpCharMsgSort[cnt]->PlayerBeta)) {
							DrawTwoLineMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
								"Honor Member", lpCharMsgSort[cnt]->smCharInfo.szName, RGB(0, 191, 255), RGB(230, 255, 160), lpDDS_clanMark, selectedBox, dwClanMgrBit);
						}
					}
				}
			}
		}

		if (DispBar)
		{

			lpCharMsgSort[cnt]->DrawStateBar2(lpCharMsgSort[cnt]->RendPoint.x - 30, lpCharMsgSort[cnt]->RendRect2D.top + y - 14);

		}
		else if (lpCharSelPlayer)
		{
			if (lpCharMsgSort[cnt]->smCharInfo.dwObjectSerial == lpCharSelPlayer->smCharInfo.dwObjectSerial && lpCharSelPlayer->smCharInfo.State == 1)
			{
				lpCharMsgSort[cnt]->DrawStateBar2(lpCharMsgSort[cnt]->RendPoint.x - 30, lpCharMsgSort[cnt]->RendRect2D.top + y - 14);
			}
		}
	}


	if (lpCurPlayer->AttackSkil)
	{
		switch (lpCurPlayer->AttackSkil & 0xFF)
		{
		case SKILL_PLAY_CHARGING_STRIKE:
			cnt = lpCurPlayer->frame - lpCurPlayer->MotionInfo->StartFrame * 160;
			if (lpCurPlayer->MotionInfo->EventFrame[0]<(DWORD)cnt && lpCurPlayer->MotionInfo->EventFrame[1]>(DWORD)cnt)
			{
				cnt -= (int)lpCurPlayer->MotionInfo->EventFrame[0];
				cnt2 = (int)(lpCurPlayer->MotionInfo->EventFrame[1] - lpCurPlayer->MotionInfo->EventFrame[0]);


				lpCurPlayer->DrawChargingBar(lpCurPlayer->RendPoint.x - 30, lpCurPlayer->RendRect2D.bottom, cnt, cnt2);

			}
			break;
		case SKILL_PLAY_PHOENIX_SHOT:

			cnt = lpCurPlayer->frame - lpCurPlayer->MotionInfo->StartFrame * 160;
			if (lpCurPlayer->MotionInfo->EventFrame[0]<(DWORD)cnt && lpCurPlayer->MotionInfo->EventFrame[1]>(DWORD)cnt)
			{
				cnt -= (int)lpCurPlayer->MotionInfo->EventFrame[0];
				cnt2 = (int)(lpCurPlayer->MotionInfo->EventFrame[1] - lpCurPlayer->MotionInfo->EventFrame[0]);


				lpCurPlayer->DrawChargingBar(lpCurPlayer->RendPoint.x - 30, lpCurPlayer->RendRect2D.bottom, cnt, cnt2);

			}
			break;
		}
	}

	if (DispInterface)
	{
		if (DispEachMode)
		{
			DrawEachPlayer(0.74f, 0.32f, 1);
		}
		else
		{
			DrawEachPlayer(0.92f, 0.1f, 0);

			dsDrawOffset_X = WinSizeX - 800;
			dsDrawOffset_Y = WinSizeY - 600;
			dsDrawOffsetArray = dsARRAY_RIGHT | dsARRAY_BOTTOM;
			dsMenuCursorPos(&pCursorPos, 3);

			DrawInterfaceParty();
			dsMenuCursorPos(&pCursorPos, 0);
			dsDrawOffsetArray = dsARRAY_TOP;
			dsDrawOffset_X = 0;
			dsDrawOffset_Y = 0;


			DrawInterfaceParty(pHoPartyMsgBox.x, pHoPartyMsgBox.y);
		}

		if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{
			extern int Debug_TalkZoomMode;
			if (Debug_TalkZoomMode && lpCurPlayer->TalkPattern)
			{
				extern void DrawTalkZoom(smCHAR *lpChar, smPAT3D *lpPattern, float fx, float fy);
				DrawTalkZoom(lpCurPlayer, lpCurPlayer->TalkPattern, 0.2f, 0.32f);
			}
		}
	}


#ifdef	_NEW_PARTRADE
	if (EachTradeButton && chrEachMaster)
	{

		DisplayPartyTradeButton();
	}
#endif



	DisplaySodScore();

#ifdef _SINBARAM

	RestoreInterfaceTexture();

	dsDrawOffset_X = WinSizeX - 800;
	dsDrawOffset_Y = WinSizeY - 600;

	if (DispInterface)
	{
		sinDraw();
	}

	dsDrawOffset_X = 0;
	dsDrawOffset_Y = 0;
#endif

	if (BellatraEffectInitFlag)
		DrawBellatraFontEffect();



#ifdef	_IME_ACTIVE

	char *ImeStr;

	int ImeY;

	if (DisplayIME)
	{

		SetBkColor(hdc, RGB(255, 255, 200));
		SetFontTextColor(RGB(0, 0, 0));

		if (sinChatDisplayMode == 1)
			ImeY = 442;
		else
			ImeY = 340;




		IMETest.GetImeInfo();
		ImeStr = IMETest.m_szTitle.GetBuffer(IMETest.m_szTitle.GetLength());
		if (ImeStr[0])

			dsTextLineOut(8, ImeY - 12, ImeStr, lstrlen(ImeStr));







		SetBkColor(hdc, RGB(255, 255, 255));

}

#endif



#ifdef _WINMODE_DEBUG

	int	rcv1, rcv2, snd1, snd2, arcv1, brcv1, arcv2, brcv2;
	int LineY;

	if (DisplayDebug)
	{
		rcv1 = 0;
		rcv2 = 0;
		snd1 = 0;
		snd2 = 0;
		arcv1 = 0;
		brcv1 = 0;
		arcv2 = 0;
		brcv2 = 0;

		if (smWsockServer)
		{
			rcv1 = smWsockServer->RecvPacketCount;
			snd1 = smWsockServer->SendPacketCount;
			arcv1 = smWsockServer->RecvPopCount;
			brcv1 = smWsockServer->RecvPopErrorCount;
		}
		else
		{
			rcv1 = 0; snd1 = 0;
		}

		if (smWsockUserServer)
		{
			rcv2 = smWsockUserServer->RecvPacketCount;
			snd2 = smWsockUserServer->SendPacketCount;
			arcv2 = smWsockUserServer->RecvPopCount;
			brcv2 = smWsockUserServer->RecvPopErrorCount;
		}
		else
		{
			rcv2 = 0; snd2 = 0;
		}

		wsprintf(strBuff, "%d(%d) %d x=%d z=%d y=%d VRAM=%d R1=%d(%d) R2=%d(%d) S1=%d S2=%d (%d/%d) (%d/%d) RcvTurb( %d )", DispRender, DispMainLoop, DispPolyCnt, lpCurPlayer->pX >> (FLOATNS), lpCurPlayer->pZ >> (FLOATNS), lpCurPlayer->pY >> (FLOATNS), (VramTotal / (1024 * 1024)),
			rcv1, Debug_RecvCount1, rcv2, Debug_RecvCount2, snd1, snd2, brcv1, arcv1, brcv2, arcv2, smTransTurbRcvMode);

		SetFontTextColor(RGB(0, 0, 0));
		dsTextLineOut(11, 11, strBuff, lstrlen(strBuff));
		SetFontTextColor(RGB(255, 255, 255));
		dsTextLineOut(10, 10, strBuff, lstrlen(strBuff));

		wsprintf(strBuff, "Stage : %s , %s", szGameStageName[0], szGameStageName[1]);
		SetFontTextColor(RGB(0, 0, 0));
		dsTextLineOut(11, 31, strBuff, lstrlen(strBuff));
		SetFontTextColor(RGB(255, 255, 255));
		dsTextLineOut(10, 30, strBuff, lstrlen(strBuff));

		wsprintf(strBuff, "World Time (%d:%d)", dwGameHour, dwGameMin);
		SetFontTextColor(RGB(0, 0, 0));
		dsTextLineOut((WinSizeX >> 1) + 1, 31, strBuff, lstrlen(strBuff));
		SetFontTextColor(RGB(255, 255, 255));
		dsTextLineOut((WinSizeX >> 1), 30, strBuff, lstrlen(strBuff));


		int cursorX = 0;
		int cursorY = 0;

		if (g_iFzmCursorPosX < 67)
		{
			cursorX = 100;
		}

		if (g_iFzmCursorPosY < 10)
		{
			cursorY = 10;
		}



		wsprintf(strBuff, "[%d:%d]", g_iFzmCursorPosX, g_iFzmCursorPosY);
		dsTextLineOut((g_iFzmCursorPosX - 65) + cursorX, (g_iFzmCursorPosY - 10) + cursorY, strBuff, lstrlen(strBuff));

		if (lpCurPlayer->PatLoading == FALSE)
		{
			if (AdminCharMode)
				wsprintf(strBuff, "%s", lpCurPlayer->smCharInfo.szName);
			else
				wsprintf(strBuff, "%s", lpCurPlayer->lpDinaPattern->szPatName);

			SetFontTextColor(RGB(0, 0, 0));
			dsTextLineOut((WinSizeX >> 1) + 1 + 120, 31, strBuff, lstrlen(strBuff));
			SetFontTextColor(RGB(255, 255, 255));
			dsTextLineOut((WinSizeX >> 1) + 120, 30, strBuff, lstrlen(strBuff));

			wsprintf(strBuff, "Damage : %d", LastAttackDamage);
			SetFontTextColor(RGB(0, 0, 0));
			dsTextLineOut(9, 48, strBuff, lstrlen(strBuff));
			SetFontTextColor(RGB(255, 255, 255));
			dsTextLineOut(8, 47, strBuff, lstrlen(strBuff));

			wsprintf(strBuff, "RcvDamage:(%d) [%d] %d %d", Record_TotalRecvDamageCount, Record_RecvDamageCount, Record_DefenceCount, Record_BlockCount);
			SetFontTextColor(RGB(0, 0, 0));
			dsTextLineOut(9, 62, strBuff, lstrlen(strBuff));
			SetFontTextColor(RGB(255, 255, 255));
			dsTextLineOut(8, 61, strBuff, lstrlen(strBuff));

			if (AreaServerMode)
			{
				if (lpWSockServer_Area[0])
				{
					wsprintf(strBuff, "Area Server[0]: (%s)", lpWSockServer_Area[0]->szIPAddr);
					SetFontTextColor(RGB(0, 0, 0));
					dsTextLineOut(9, 82, strBuff, lstrlen(strBuff));
					SetFontTextColor(RGB(255, 255, 255));
					dsTextLineOut(8, 81, strBuff, lstrlen(strBuff));
				}
				if (lpWSockServer_Area[1])
				{
					wsprintf(strBuff, "Area Server[1]: (%s)", lpWSockServer_Area[1]->szIPAddr);
					SetFontTextColor(RGB(0, 0, 0));
					dsTextLineOut(9, 96, strBuff, lstrlen(strBuff));
					SetFontTextColor(RGB(255, 255, 255));
					dsTextLineOut(8, 95, strBuff, lstrlen(strBuff));
				}

				if (lpWSockServer_DispArea[0])
				{
					wsprintf(strBuff, "Area Server[0]: (%s)", lpWSockServer_DispArea[0]->szIPAddr);
					SetFontTextColor(RGB(0, 0, 0));
					dsTextLineOut(209, 82, strBuff, lstrlen(strBuff));
					SetFontTextColor(RGB(255, 255, 255));
					dsTextLineOut(208, 81, strBuff, lstrlen(strBuff));
				}

				if (lpWSockServer_DispArea[1])
				{
					wsprintf(strBuff, "Area Server[1]: (%s)", lpWSockServer_DispArea[1]->szIPAddr);
					SetFontTextColor(RGB(0, 0, 0));
					dsTextLineOut(209, 96, strBuff, lstrlen(strBuff));
					SetFontTextColor(RGB(255, 255, 255));
					dsTextLineOut(208, 95, strBuff, lstrlen(strBuff));
				}

				wsprintf(strBuff, "AreaCount(%d) AreaConn(%d) AreaIP( [%d] %d %d ) Step(%d)",
					dwDebugAreaCount, dwDebugAreaConnCount,
					dwDebugAreaIP[0], dwDebugAreaIP[1], dwDebugAreaIP[2], dwDebugAreaStep);

				SetFontTextColor(RGB(0, 0, 0));
				dsTextLineOut(9, 108, strBuff, lstrlen(strBuff));
				SetFontTextColor(RGB(255, 255, 255));
				dsTextLineOut(8, 108, strBuff, lstrlen(strBuff));
			}
		}

		SetFontTextColor(RGB(255, 255, 255));

		LineY = 48;
		for (i = 0; i < OTHER_PLAYER_MAX; i++)
		{
			if (chrOtherPlayer[i].Flag && chrOtherPlayer[i].Pattern && chrOtherPlayer[i].smCharInfo.State == smCHAR_STATE_USER)
			{
				wsprintf(strBuff, "%s", chrOtherPlayer[i].smCharInfo.szName);
				SetFontTextColor(RGB(0, 0, 0));
				dsTextLineOut(WinSizeX - 220, LineY + 1, strBuff, lstrlen(strBuff));
				SetFontTextColor(RGB(255, 255, 255));
				dsTextLineOut(WinSizeX - 221, LineY, strBuff, lstrlen(strBuff));
				LineY += 16;
				if (LineY > 460)
					break;
			}
		}

		int	MonCharBuff[OTHER_PLAYER_MAX];
		int MonCharCnt = 0;
		int	MonCnt;

		for (i = 0; i < OTHER_PLAYER_MAX; i++)
		{
			if (chrOtherPlayer[i].Flag && chrOtherPlayer[i].Pattern && chrOtherPlayer[i].smCharInfo.State != smCHAR_STATE_USER)
				MonCharBuff[MonCharCnt++] = i;
		}

		LineY = 48;
		for (i = 0; i < MonCharCnt; i++)
		{
			if (MonCharBuff[i] >= 0)
			{
				MonCnt = 1;
				for (cnt = i + 1; cnt < MonCharCnt; cnt++)
				{
					if (MonCharBuff[cnt] >= 0 && lstrcmp(chrOtherPlayer[MonCharBuff[cnt]].smCharInfo.szName,
						chrOtherPlayer[MonCharBuff[i]].smCharInfo.szName) == 0)
					{
						MonCharBuff[cnt] = -1;
						MonCnt++;
					}
				}

				wsprintf(strBuff, "%s x %d", chrOtherPlayer[MonCharBuff[i]].smCharInfo.szName, MonCnt);
				SetFontTextColor(RGB(0, 0, 0));
				dsTextLineOut(WinSizeX - 380, LineY + 1, strBuff, lstrlen(strBuff));

				if (chrOtherPlayer[MonCharBuff[i]].smCharInfo.State == smCHAR_STATE_NPC)
					SetFontTextColor(RGB(192, 192, 255));
				else
					SetFontTextColor(RGB(255, 192, 192));
				dsTextLineOut(WinSizeX - 381, LineY, strBuff, lstrlen(strBuff));
				LineY += 16;
				if (LineY > 460) break;
			}
		}
	}
#endif



	if (DisconnectFlag)
	{

		if (DisconnectServerCode == 0)
			DrawMessage(MidX - 64, MidY, mgDiconnect, 36, BOX_ONE);

		if (DisconnectServerCode == 1)
			DrawMessage(MidX - 64, MidY, mgDiconnect1, 36, BOX_ONE);

		if (DisconnectServerCode == 2)
			DrawMessage(MidX - 64, MidY, mgDiconnect2, 36, BOX_ONE);

		if (DisconnectServerCode == 3)
			DrawMessage(MidX - 64, MidY, mgDiconnect3, 36, BOX_ONE);

		if (DisconnectServerCode == 4)
			DrawMessage(MidX - 64, MidY, mgDiconnect4, 36, BOX_ONE);


#ifdef	_WINMODE_DEBUG
		if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR && !quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime)
			quit = TRUE;
#else
		if (!quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime)
			quit = TRUE;
#endif
	}
	else
	{
		if (quit)
			DrawMessage(MidX - 40, MidY, mgCloseGame, 36, BOX_ONE);
		else
		{
			if (dwCloseBoxTime && dwCloseBoxTime > dwPlayTime)
			{
				DrawMessage(MidX - 100, MidY, mgCloseWindow, 36, BOX_ONE);
			}
			else
			{
				if (dwBattleQuitTime)
				{
					if ((dwBattleQuitTime + 5000) > dwPlayTime)
						DrawMessage(MidX - 40, MidY, mgCloseBattle, 36, BOX_ONE);
					else
						dwBattleQuitTime = 0;
				}
			}
		}
	}

	DarkLevel = BackDarkLevel;

	return TRUE;
}


void smPlayD3D(int x, int y, int z, int ax, int ay, int az)
{
	eCAMERA_TRACE	eTrace;
	int	ap;

	DispPolyCnt = 0;

	BeginRender();

	SetRendSight();


	if (smConfig.getSecurity() != AccountTypes::SEC_PLAYER && !smConfig.isSecurityAuth())
	{
		SendAdminMode(smConfig.getSecurity());
	}

	int Mapfl;
	int cy;
	int mapY;

	Mapfl = 0;
	cy = y + 16 * fONE;

	if (!DebugPlayer)
	{
		if (smGameStage[0])
		{
			mapY = (smGameStage[0]->GetHeight(x, z));
			if (y < mapY)
			{
				y = mapY;
				y += 8 << FLOATNS;
			}
			if (mapY > CLIP_OUT) Mapfl++;
		}
		if (smGameStage[1])
		{
			mapY = (smGameStage[1]->GetHeight(x, z));
			if (y < mapY)
			{
				y = mapY;
				y += 8 << FLOATNS;
			}
			if (mapY > CLIP_OUT)
				Mapfl++;
		}
	}

	Mix_CodeVram();

	smRender.Color_R = BrCtrl;
	smRender.Color_G = BrCtrl;
	smRender.Color_B = BrCtrl;
	smRender.Color_A = BrCtrl;

	smRender.Color_R = -DarkLevel + BackColor_R;
	smRender.Color_G = -DarkLevel + BackColor_G;
	smRender.Color_B = -DarkLevel + BackColor_B;


	if (dwM_BlurTime)
	{
		if (dwM_BlurTime < dwPlayTime)
		{
			dwM_BlurTime = 0;
		}
	}

	d3ddev->Clear(0, 0, 2, smBackColor, 1.0f, 0);

	y += (32 << FLOATNS);







	TraceTargetPosi.x = x;
	TraceTargetPosi.y = y;
	TraceTargetPosi.z = z;

	if (AutoCameraFlag)
	{

		TraceCameraMain();

		x = TraceCameraPosi.x;
		y = TraceCameraPosi.y;
		z = TraceCameraPosi.z;
	}


	int ey = lpCurPlayer->pY + (32 * fONE);







	ActionGameMode = FALSE;


	if (lpCurPlayer && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ACTION)
	{

		x = lpCurPlayer->pX;
		y = StageField[lpCurPlayer->OnStageField]->ActionCamera.FixPos.y + 80 * fONE;
		z = StageField[lpCurPlayer->OnStageField]->ActionCamera.FixPos.z*fONE;

		if (x < StageField[lpCurPlayer->OnStageField]->ActionCamera.LeftX*fONE) x = StageField[lpCurPlayer->OnStageField]->ActionCamera.LeftX*fONE;
		else if (x > StageField[lpCurPlayer->OnStageField]->ActionCamera.RightX*fONE) x = StageField[lpCurPlayer->OnStageField]->ActionCamera.RightX*fONE;

		MakeTraceMatrix(&eTrace, x, y, z, x, lpCurPlayer->pY, 326711 * fONE);

		ax = eTrace.AngX;
		ay = eTrace.AngY;
		smRender.OpenCameraPosi(x, y, z, &eTrace.eRotMatrix);

		ActionGameMode = TRUE;
	}
	else if (!DebugPlayer)
	{
		MakeTraceMatrix(&eTrace, x, y, z, lpCurPlayer->pX, ey, lpCurPlayer->pZ);

		ax = eTrace.AngX;
		ay = eTrace.AngY;
		smRender.OpenCameraPosi(x, y, z, &eTrace.eRotMatrix);
	}

	smRender.ClearLight();

	if (DarkLevel > 0)
	{
		ap = DarkLevel + (DarkLevel >> 2);

		if (StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_DUNGEON)
		{
			DarkLightRange = 400 * fONE;
			ap = DarkLevel;
		}
		else
			DarkLightRange = 260 * fONE;


		if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
		{


		}
		else
			smRender.AddDynamicLight(lpCurPlayer->pX, lpCurPlayer->pY + 32 * fONE, lpCurPlayer->pZ, ap, ap, ap, 0, DarkLightRange);
	}

	DynLightApply();

	DrawSky(x, y, z, ax, ay, az);

	smRender.DeviceRendMode = FALSE;


	if (smRender.m_FogIsRend && smRender.m_FogMode)
		d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE);

	smRender.bApplyRendObjLight = TRUE;
	DrawPat3D(x, y, z, ax, ay, az);

	smRender.bApplyRendObjLight = FALSE;
	NumPoly = DisplayStage(x, y, z, ax, ay, az);

	smRender.bApplyRendObjLight = TRUE;
	DrawPat3D_Alpha();

	smRender.ClearObjLight();

	if (smRender.m_FogIsRend && smRender.m_FogMode)
		d3ddev->SetRenderState(D3DRS_FOGENABLE, FALSE);

	smRender.ClearLight();
	smRender.Color_A = 0;
	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;


	DrawPatShadow(x, y, z, ax, ay, az);



	smRender.DeviceRendMode = TRUE;


	RestoreInterfaceTexture();

	DrawEffect(x, y, z, ax, ay, az);
	cSin3D.Draw(x, y, z, ax, ay, az);
	DrawPat2D(x, y, z, ax, ay, az);

	if (g_IsDxProjectZoomIn)
	{
		DrawFullZoomMap();
	}
	else
	{
		if (cInterFace.sInterFlags.MapOnFlag)
		{

			if (DispInterface)
			{
				DrawFieldMap();
			}
		}
	}

	if ((!MsTraceMode && MouseButton[0] == 0) || lpCurPlayer->smCharInfo.Stamina[0] > (lpCurPlayer->smCharInfo.Stamina[1] >> 2))
	{

		lpCurPlayer->MoveMode = cInterFace.sInterFlags.RunFlag;

		if (ActionGameMode)
			lpCurPlayer->MoveMode = ActionDashMode;
	}
	else
	{
		if (lpCurPlayer->smCharInfo.Stamina[0] == 0)
			lpCurPlayer->MoveMode = FALSE;
	}

	smRender.CloseCameraPosi();

	Disp_tx = MsSelPos.x - 32;
	Disp_ty = MsSelPos.y;

	if (g_IsDxProjectZoomIn <= 0)
		DrawGameState();
	else
		VirtualDrawGameState();

	EndRender();

	IncTextureFrame();
}

char *CompCmdStr(char *strCmdLine, char *strword)
{
	int len, len2;
	int cnt, cnt2;

	len = lstrlen(strCmdLine);
	len2 = lstrlen(strword);

	for (cnt = 0; cnt < len - len2; cnt++)
	{
		for (cnt2 = 0; cnt2 < len2; cnt2++)
		{
			if (strword[cnt2] != strCmdLine[cnt + cnt2]) break;
		}
		if (cnt2 == len2)
			return &strCmdLine[cnt + cnt2];
	}

	return NULL;
};



char *RegPath_3DMax = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\3D Studio MAX R3.1L";
char *RegPath_3DMax2 = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\3D Studio MAX R3.1";
char *RegPath_Photoshop = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Adobe Photoshop 6.0";
char *RegPath_ACDSee = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\ACDSee";



int	SetChatingLine(char *szMessage)
{

	cInterFace.ChatFlag = TRUE;
	hFocusWnd = hTextWnd;
	SetWindowText(hFocusWnd, szMessage);
	SetIME_Mode(1);




	return TRUE;
}


DWORD GameWindowMessage(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	int stm, cnt;

	switch (messg)
	{


	case WM_KEYDOWN:

		if (GameMode == 2)
		{

			if (wParam == VK_RETURN && VRKeyBuff[wParam] == 0 && !sinMessageBoxShowFlag &&
				!VRKeyBuff[VK_CONTROL])
			{

				SetChatingLine("");
			}

			if (wParam == VK_BACK && VRKeyBuff[wParam] == 0)
			{
				if (HoMsgBoxMode)
					HoMsgBoxMode = 0;
				else
					HoMsgBoxMode = 1;

				SetMessageFrameSelect(HoMsgBoxMode);
			}

			if (wParam == 'M' && VRKeyBuff[wParam] == 0)
			{

				sinCheck_ShowHelpMap();
			}

			if (dwYahooTime > dwPlayTime && dwYahooTime < (dwPlayTime + 60 * 1000))
			{
				if (wParam == VK_SPACE && VRKeyBuff[wParam] == 0)
				{
					if (lpCurPlayer && lpCurPlayer->MotionInfo)
					{
						stm = sinGetStamina();
						cnt = (lpCurPlayer->smCharInfo.Stamina[1] * 3) / 100;
						if (lpCurPlayer->MotionInfo->State<0x100 && stm>cnt)
						{
							if (lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_YAHOO))
							{

								if (cnt > 0) sinSetStamina(stm - cnt);
							}
						}
					}

					VRKeyBuff[wParam] = 1;
					return FALSE;
				}
			}



			if (smRender.m_GameFieldView && !VRKeyBuff[wParam])
			{
				if (wParam == VK_ADD)
				{
					if (smRender.m_GameFieldViewStep < 22)
					{
						smRender.m_GameFieldViewStep++;

						RendSightSub(1);
					}
				}
				else if (wParam == VK_SUBTRACT)
				{
					if (smRender.m_GameFieldViewStep > 1)
					{
						smRender.m_GameFieldViewStep--;

						RendSightSub(1);
					}
				}
			}




#ifdef _WINMODE_DEBUG

			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
			{

				if (wParam == VK_F9 && VRKeyBuff[VK_F9] == 0)
				{
					if (DisplayDebug) DisplayDebug = FALSE;
					else DisplayDebug = TRUE;
				}

				if (VRKeyBuff[VK_SHIFT] && !VRKeyBuff[VK_CONTROL])
				{

					if (wParam == VK_F5 && VRKeyBuff[VK_F5] == 0)
					{
						SkipNextField = 1;
					}
					if (wParam == VK_F6 && VRKeyBuff[VK_F6] == 0)
					{
						SkipNextField = 2;
					}


					if (wParam == VK_F7 && VRKeyBuff[VK_F7] == 0)
					{
						if (smRender.dwMatDispMask)
							smRender.dwMatDispMask = 0;
						else
							smRender.dwMatDispMask = sMATS_SCRIPT_NOTVIEW;
					}


					if (wParam == VK_F8 && VRKeyBuff[wParam] == 0)
					{

						if (ktj_imsiDRAWinfo) ktj_imsiDRAWinfo = 0;
						else ktj_imsiDRAWinfo = 1;
					}
				}

				if (VRKeyBuff[VK_CONTROL] && wParam == VK_F11 && VRKeyBuff[wParam] == 0)
				{
					DispInterface = !DispInterface;
				}



				if (AdminCharMode)
				{
					if (wParam == VK_INSERT && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
					{

						SendAdd_Npc(lpCurPlayer, 0);
					}
					if (wParam == VK_DELETE && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
					{

						if (lpCharSelPlayer)
						{

							SendDelete_Npc(lpCharSelPlayer);
						}
					}
				}
				else
				{
					if (wParam == VK_INSERT && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
					{

						SendAddStartPoint(lpCurPlayer->pX, lpCurPlayer->pZ);
					}

					if (wParam == VK_DELETE && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
					{

						if (lpSelItem)
						{
							SendDeleteStartPoint(lpSelItem->pX, lpSelItem->pZ);
						}
					}
				}
			}
#endif

		}
		break;
	}

	return TRUE;
}


#include "sinbaram\\HaQuestBoard.h"


int	StartQuest_Code(DWORD wCode)
{
	SetQuestBoard();


	if (InterfaceParty.PartyPosState == PARTY_NONE)
	{

		ShowQuest();
		InterfaceParty.quest_Sel_Progress();
	}

	return TRUE;
}


int EndQuest_Code(DWORD wCode)
{

	Record_LastQuest((WORD)wCode);
	SetQuestBoard();

	return TRUE;
}

int HoInstallFont()
{

#ifdef	_LANGUAGE_ENGLISH		
	AddFontResource("ptz.ttf");
#endif

#ifdef	_LANGUAGE_THAI		

	AddFontResource("ssee874.fon");

#endif




	OSVERSIONINFO vi;
	vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	char szKey[255];
	GetVersionEx(&vi);
	if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		strcpy(szKey, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");
	else
		strcpy(szKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Fonts");

#ifdef	_LANGUAGE_ENGLISH		
	SetRegString(HKEY_LOCAL_MACHINE, szKey, "ptz", "ptz.ttf");
#endif
#ifdef	_LANGUAGE_THAI	

	SetRegString(HKEY_LOCAL_MACHINE, szKey, "MS Sans Serif", "ssee874.fon");

#endif


	return TRUE;
}

int HoUninstallFont()
{

#ifdef	_LANGUAGE_ENGLISH		
	RemoveFontResource("ptz.ttf");
#endif
#ifdef	_LANGUAGE_THAI		

	RemoveFontResource("ssee874.fon");

#endif	


	OSVERSIONINFO vi;
	vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	char szKey[255];
	GetVersionEx(&vi);
	if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		strcpy(szKey, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");
	else
		strcpy(szKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Fonts");
	HKEY key;
	DWORD dwDisp;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisp);

#ifdef	_LANGUAGE_ENGLISH		
	RegDeleteValue(key, "ptz");
#endif
#ifdef	_LANGUAGE_THAI		

	RegDeleteValue(key, "MS Sans Serif");

#endif		

	RegCloseKey(key);

	return TRUE;
}
