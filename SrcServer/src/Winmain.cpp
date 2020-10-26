#define _SINBARAM

// STL INCLUDES
#include <memory>
#include <vector>


#include <windows.h>
#include <iostream>
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


#ifdef _W_SERVER
#include "Database\Database.h"
#include "GameMasters\GameMasters.h"
#include "Dump\WinDump.h"
#endif


using namespace std;

HWND hwnd;
HWND hTextWnd;
HWND hFocusWnd;

extern int sinChatDisplayMode;
extern int sinChatInputMode;

HDC hdc = NULL;
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



int InitD3D(HWND hWnd);
void CloseD3d();
void smPlayD3D(int x, int y, int z, int ax, int ay, int az);



#include "ime.h"

ImeClass IMETest;
CStrClass sz;
LRESULT CALLBACK EditWndProc01(HWND, UINT, WPARAM, LPARAM);
WNDPROC		OldEditProc01;
char szIME_Buff[10][64];

int MouseX, MouseY;
int MousemX, MousemY;
int angX = 0;
int angY = 0;
DWORD	dwLastMouseMoveTime;
DWORD	dwLastCharMoveTime;

int xPos, yPos;

POINT3D TraceCameraPosi;
POINT3D TraceTargetPosi;
int	PlayCameraMode = 1;
int AutoCameraFlag = FALSE;


DIRECTDRAWSURFACE lpDDSMenu;

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

int whAnx = 64;
int anx = 64;
int	ViewAnx = 64;
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


int WaveCameraMode = TRUE;
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


#define IDC_TEXT	101

BYTE VRKeyBuff[256];


void PlayD3D();

HFONT hFont = 0;
int SetCreateFont();


CRITICAL_SECTION	cSection;


HIMC hImc;
HIMC hImcEdit;

extern rsRECORD_DBASE	rsRecorder;
extern int ServerWinMain();

extern int	CheckServerRecordData();


extern int RestoreBackupData(char *szListFile, char *BackupPath);


extern std::vector<std::shared_ptr<Database>> vSQLConnection;

void CreateSQLConnection(EDatabaseID eDatabaseID)
{
	std::shared_ptr<Database> pcSQL = std::make_shared<Database>();

	if(pcSQL->Init(eDatabaseID))
	{
		vSQLConnection.push_back(pcSQL);
	}
	else
	{
		cerr << "Falha ao conectar-se ao banco de dados! Log: SQL.txt" << endl;
		Sleep(5000);
		exit(0);
	}
}



BOOL HookAPI(char* moduleName, char* apiName, void* callBack, void* backup = NULL)
{
	DWORD old = 0;

	void * pAPIHandle = GetProcAddress(GetModuleHandleA(moduleName), apiName);

	if(pAPIHandle == NULL)
		return FALSE;

	if(backup != NULL)
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


int main(int argv, char* argc[])
{
	SetUnhandledExceptionFilter(unhandled_handler);
	HookAPI("kernel32.dll", "SetUnhandledExceptionFilter", RedirectedSetUnhandledExceptionFilter);

	SetConsoleTitle("Priston - Servidor");

	initSinCos();
	srand(GetCurrentTime());

	InitializeCriticalSection(&cSection);
	InitializeCriticalSection(&cDrawSection);
	InitializeCriticalSection(&cSection_Main);



	cout << "Conectando-se ao Banco de Dados: AccountDB" << endl;
	CreateSQLConnection(DATABASEID_AccountDB);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: BillingDB" << endl;
	CreateSQLConnection(DATABASEID_BillingDB);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: BillingLogDB" << endl;
	CreateSQLConnection(DATABASEID_BillingLogDB);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: ClanDB" << endl;
	CreateSQLConnection(DATABASEID_ClanDB);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: GameLogDB" << endl;
	CreateSQLConnection(DATABASEID_GameLogDB);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: ItemLogDB" << endl;
	CreateSQLConnection(DATABASEID_ItemLogDB);
	cout << "Conectado com sucesso" << endl;
	
	cout << "Conectando-se ao Banco de Dados: LogDB" << endl;
	CreateSQLConnection(DATABASEID_LogDB);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: PCRoom" << endl;
	CreateSQLConnection(DATABASEID_PCRoom);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: PCRoomLog" << endl;
	CreateSQLConnection(DATABASEID_PCRoomLog);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: rPTDB" << endl;
	CreateSQLConnection(DATABASEID_rPTDB);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: SoD2DB" << endl;
	CreateSQLConnection(DATABASEID_SoD2DB);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: SodDB" << endl;
	CreateSQLConnection(DATABASEID_SodDB);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: PristonDB" << endl;
	CreateSQLConnection(DATABASEID_PristonDB);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: PT" << endl;
	CreateSQLConnection(DATABASEID_Priston);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: QuestDB" << endl;
	CreateSQLConnection(DATABASEID_QuestDB);
	cout << "Conectado com sucesso" << endl;


	GameMasters::getInstance()->readFromDatabase();

	return ServerWinMain();
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
	return TRUE;
}


int CheckCode_2Byte(char *Str)
{
#ifdef _LANGUAGE_ENGLISH


	return 1;
#endif

#ifdef _LANGUAGE_THAI
	if(CheckTHAI_ptr(Str, 0) == 1)
		return 1;
	else if(CheckTHAI_ptr(Str, 0) == 2)
		return 2;
	return 1;
#endif

#ifdef _LANGUAGE_JAPANESE

	if(CheckJTS_ptr(Str, 0) == 2)
		return 2;

#else

	if(Str[0] < 0)
		return 2;
#endif

	return 1;
}

LRESULT CALLBACK EditWndProc01(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	wmId = LOWORD(wParam);
	wmEvent = HIWORD(wParam);

	switch(message)
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

	switch(messg)
	{

	case WM_IME_COMPOSITION:

		if((imc = ImmGetContext(hWnd)))
		{
			if(lParam & GCS_RESULTSTR)
			{
				ZeroMemory(g_bufFixed, 256);
				ImmGetCompositionString(imc, GCS_RESULTSTR, g_bufFixed, 256);
			}
			else if(lParam & GCS_COMPSTR)
			{
				ZeroMemory(g_bufEdit, 256);
				ImmGetCompositionString(imc, GCS_COMPSTR, g_bufEdit, 256);
			}
			ImmReleaseContext(hWnd, imc);
		}
		break;

	case WM_IME_NOTIFY:
		switch(wParam)
		{
		case IMN_SETCONVERSIONMODE:
		case IMN_SETSENTENCEMODE:
			if((imc = ImmGetContext(hWnd)))
			{
				ImmGetConversionStatus(imc, &conv, &sent);
				ImmReleaseContext(hWnd, imc);
			}
			break;

		case IMN_SETOPENSTATUS:
			if((imc = ImmGetContext(hWnd)))
			{
				if(ImmGetOpenStatus(imc))
				{
					ImmSetConversionStatus(imc, conv, sent);
				}
				else
				{
					ImmGetConversionStatus(imc, &conv, &sent);
				}
				ImmReleaseContext(hWnd, imc);
			}

			if(!setFont && (imc = ImmGetContext(hWnd)))
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
			if((imc = ImmGetContext(hWnd)))
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

BOOL bAdjustWindow = FALSE;

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
	if(TraceCameraPosi.x < TraceTargetPosi.x)
	{
		TraceCameraPosi.x += CAMERA_MOVE_STEP;
		if(TraceCameraPosi.x > TraceTargetPosi.x)
			TraceCameraPosi.x = TraceTargetPosi.x;
	}
	if(TraceCameraPosi.x > TraceTargetPosi.x)
	{
		TraceCameraPosi.x -= CAMERA_MOVE_STEP;
		if(TraceCameraPosi.x < TraceTargetPosi.x)
			TraceCameraPosi.x = TraceTargetPosi.x;
	}

	if(TraceCameraPosi.y < TraceTargetPosi.y)
	{
		TraceCameraPosi.y += CAMERA_MOVE_STEP;
		if(TraceCameraPosi.y > TraceTargetPosi.y)
			TraceCameraPosi.y = TraceTargetPosi.y;
	}
	if(TraceCameraPosi.y > TraceTargetPosi.y)
	{
		TraceCameraPosi.y -= CAMERA_MOVE_STEP / 2;
		if(TraceCameraPosi.y < TraceTargetPosi.y)
			TraceCameraPosi.y = TraceTargetPosi.y;
	}


	if(TraceCameraPosi.z < TraceTargetPosi.z)
	{
		TraceCameraPosi.z += CAMERA_MOVE_STEP;
		if(TraceCameraPosi.z > TraceTargetPosi.z)
			TraceCameraPosi.z = TraceTargetPosi.z;
	}
	if(TraceCameraPosi.z > TraceTargetPosi.z)
	{
		TraceCameraPosi.z -= CAMERA_MOVE_STEP;
		if(TraceCameraPosi.z < TraceTargetPosi.z)
			TraceCameraPosi.z = TraceTargetPosi.z;
	}

	return TRUE;
}

int RendSightPos = 0;
int RendSightOffset = 0;


int SetRendSight()
{
	if(smRender.m_GameFieldView)
	{
		ViewPointLen = 38 * SizeMAPCELL + RendSightPos;
		ccDistZMin = ViewPointLen - (20 * SizeMAPCELL + RendSightPos / 4);

		return TRUE;
	}

	return FALSE;
}

int RendSightSub(int flag)
{
	if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldSight)
		RendSightOffset = StageField[lpCurPlayer->OnStageField]->FieldSight * SizeMAPCELL;
	else
	{
		RendSightOffset = smRender.m_GameFieldViewStep * SizeMAPCELL;
		if(flag) RendSightPos = RendSightOffset;
	}

	if(RendSightPos < RendSightOffset)
		RendSightPos += 4;
	else
		if(RendSightPos > RendSightOffset) RendSightPos -= 4;

	return TRUE;
}



#define	FPS_TIME		(1000/70)

DWORD FrameSkipTimer = 0;
int fps = 70;
int FpsTime;

#define AC_MOVE_STEP	4
#define AC_MOVE_MIN		256

int dsCameraRotation = 0;

void PlayMain(){}

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


void showFPS(){}


void PlayD3D(){}

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

int SetMousePlay(int flag){
	return NULL;
}

extern int TestTraceMatrix();

int InitD3D(HWND hWnd){
	return NULL;
}

void CloseD3d(){
}

int GameInit(){
	return NULL;
}


int GameClose(){
	return NULL;
}


int DisplayLogoImage()
{
	LPDIRECTDRAWSURFACE4 LogoImage = LoadDibSurfaceOffscreen("Image\\Logo.bmp");

	if(LogoImage)
	{
		LogoImage->SetColorKey(DDCKEY_COLORSPACE, 0);

		renderDevice.BeginScene();
		renderDevice.ClearViewport(D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET);

		DrawSprite(WinSizeX / 2 - 400, WinSizeY / 2 - 300, LogoImage, 0, 0, 800, 600);

		renderDevice.Flip();

		Sleep(1500);

		renderDevice.EndScene();

		LogoImage->Release();
	}

	return TRUE;
}

int SetGameMode(int mode){
	return NULL;
}

float xr = 0;

int jcnt = 0;

float brt = 1;
float bs = 0;


int ox = 0, oy = 0, oz = 0;

int GoText = 0;

char strBuff[240];
char strBuff2[256];

int RestoreFlag = 0;

char *szRestore = "Now load the estuary very hard to picture data. Jjogeum only wait!";

int RestoreAll()
{
	HDC hdc = NULL;


	DDBLTFX bltFx;
	ZeroMemory(&bltFx, sizeof(DDBLTFX));
	bltFx.dwSize = sizeof(DDBLTFX);
	bltFx.dwFillColor = 0;


	renderDevice.Blt(renderDevice.lpDDSPrimary, NULL, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &bltFx);

	VramTotal = 0;

	renderDevice.lpDDSPrimary->GetDC(&hdc);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);
	dsTextLineOut(hdc, 16, WinSizeY - 32, szRestore, lstrlen(szRestore));
	renderDevice.lpDDSPrimary->ReleaseDC(hdc);

	RestoreTextures();
	if(lpDDSMenu)
	{
		lpDDSMenu->Release();
		lpDDSMenu = LoadDibSurfaceOffscreen(smConfig.szFile_Menu);
	}

	sinReload();

	return TRUE;

}

int NumPoly;
int Disp_tx, Disp_ty;
int Disp_rx, Disp_ry;


smCHAR	*lpCharMsgSort[OTHER_PLAYER_MAX];
int ChatMsgSortCnt;

extern int Debug_RecvCount1;
extern int Debug_RecvCount2;
extern int Debug_SendCount;


int RestoreInterfaceTexture()
{
	int cnt;

	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;
	smRender.Color_A = 0;

	cnt = 0;

	renderDevice.SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_MODULATE);
	renderDevice.SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	renderDevice.SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

	renderDevice.SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	renderDevice.SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	renderDevice.SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	renderDevice.SetTexture(cnt, 0);

	for(cnt = 1; cnt < 8; cnt++)
	{
		renderDevice.SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_DISABLE);
		renderDevice.SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		renderDevice.SetTexture(cnt, 0);
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


	if(DisconnectFlag)
	{

		if(DisconnectServerCode == 0)
			DrawMessage(MidX - 64, MidY, mgDiconnect, 36, BOX_ONE);

		if(DisconnectServerCode == 1)
			DrawMessage(MidX - 64, MidY, mgDiconnect1, 36, BOX_ONE);

		if(DisconnectServerCode == 2)
			DrawMessage(MidX - 64, MidY, mgDiconnect2, 36, BOX_ONE);

		if(DisconnectServerCode == 3)
			DrawMessage(MidX - 64, MidY, mgDiconnect3, 36, BOX_ONE);

		if(DisconnectServerCode == 4)
			DrawMessage(MidX - 64, MidY, mgDiconnect4, 36, BOX_ONE);


#ifdef	_WINMODE_DEBUG
		if(smConfig.getSecurity() < AccountTypes::SEC_MODERATOR && !quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime)
			quit = TRUE;
#else
		if(!quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime)
			quit = TRUE;
#endif
	}
	else
	{
		if(quit)
			DrawMessage(MidX - 40, MidY, mgCloseGame, 36, BOX_ONE);
		else
		{
			if(dwCloseBoxTime && dwCloseBoxTime > dwPlayTime)
			{
				DrawMessage(MidX - 100, MidY, mgCloseWindow, 36, BOX_ONE);
			}
			else
			{
				if(dwBattleQuitTime)
				{
					if((dwBattleQuitTime + 5000) > dwPlayTime)
						DrawMessage(MidX - 40, MidY, mgCloseBattle, 36, BOX_ONE);
					else
						dwBattleQuitTime = 0;
				}
			}
		}
	}

	if(renderDevice.IsDevice())
	{
		renderDevice.BeginScene();
		DrawCursor();
		renderDevice.EndScene();
	}

	DarkLevel = BackDarkLevel;
	if(renderDevice.Flip() == FALSE)
	{
		DisconnectFlag = dwPlayTime;
		quit = 1;
	}
}

int DrawGameState()
{
	int i;
	HDC	hdc = NULL;
	int cnt, cnt2;
	int	y, DispBar, DispMaster;
	smCHAR	*lpChar;
	scITEM	*lpItem;
	RECT	ddRect;
	int BackDarkLevel;
	DWORD	dwColor;

	ddRect.left = 0;
	ddRect.right = 800;
	ddRect.top = 0;
	ddRect.bottom = 150;

	if(lpDDSMenu)
	{
		i = renderDevice.BltFast(renderDevice.lpDDSBack, 0, WinSizeY - 150, lpDDSMenu, &ddRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	}

	smRender.ClearLight();

	BackDarkLevel = DarkLevel;
	DarkLevel = 0;


	RestoreInterfaceTexture();

	if(lpCharMsTrace && lpCharMsTrace->RendSucess)
	{
		Disp_tx = lpCharMsTrace->RendPoint.x - 32;
		Disp_ty = lpCharMsTrace->RendPoint.y - 12;
	}

	if(lpCharSelPlayer && lpCharMsTrace != lpCharSelPlayer)
	{
		if(lpCharSelPlayer->RendSucess)
		{
			Disp_rx = lpCharSelPlayer->RendPoint.x - 32;
			Disp_ry = lpCharSelPlayer->RendPoint.y - 12;
		}
	}

	lpChar = 0;
	lpItem = 0;

	if(lpMsTraceItem)
		lpItem = lpMsTraceItem;
	else
		lpItem = lpSelItem;

	if(VRKeyBuff['A'])
	{
		for(cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
		{
			if(scItems[cnt].Flag && scItems[cnt].ItemCode != 0 && lpSelItem != &scItems[cnt])
			{
				if(scItems[cnt].RendPoint.z >= 32 * fONE && scItems[cnt].RendPoint.z < 64 * 12 * fONE)
				{
					DrawCharacterMessage(scItems[cnt].RendPoint.x, scItems[cnt].RendPoint.y, scItems[cnt].szName, 0, 0, 0, RGB(110, 110, 110));
				}
			}
		}
	}

	if(lpSelItem && !lpCharSelPlayer && !lpCharMsTrace)
	{

		Disp_tx = MsSelPos.x;
		Disp_ty = MsSelPos.y;

		DrawCharacterMessage(Disp_tx, Disp_ty, lpSelItem->szName, 0, 0, 0, RGB(180, 180, 180));

	}


	int	SelFlag;

	ChatMsgSortCnt = 0;

	for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if(chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].RendSucess && chrOtherPlayer[cnt].smCharInfo.szName[0])
		{
			SelFlag = 0;
			if(chrOtherPlayer[cnt].RendPoint.z < 12 * 64 * fONE)
			{
				if(chrOtherPlayer[cnt].szChatMessage[0])
				{

					if(chrOtherPlayer[cnt].dwChatMessageTimer < dwPlayTime)
						chrOtherPlayer[cnt].szChatMessage[0] = 0;
					else
					{
						if(chrOtherPlayer[cnt].smCharInfo.State)
						{
							lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
							SelFlag++;
						}
					}
				}

				if(chrOtherPlayer[cnt].dwTradeMsgCode && !SelFlag)
				{
					lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
					SelFlag++;
				}
			}

			if(!SelFlag)
			{
				if(lpCharMsTrace == &chrOtherPlayer[cnt] || lpCharSelPlayer == &chrOtherPlayer[cnt] ||
					(chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_NPC && chrOtherPlayer[cnt].RendPoint.z < 12 * 64 * fONE) ||
					(chrOtherPlayer[cnt].smCharInfo.Life[0] > 0 && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY && chrOtherPlayer[cnt].smCharInfo.Brood == smCHAR_MONSTER_USER) ||
					(chrOtherPlayer[cnt].smCharInfo.ClassClan && chrOtherPlayer[cnt].smCharInfo.ClassClan == lpCurPlayer->smCharInfo.ClassClan) ||
					(HoMsgBoxMode && chrOtherPlayer[cnt].dwClanManageBit) ||
					chrOtherPlayer[cnt].PartyFlag)
				{
					lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
				}
			}
		}
	}

	if(lpCurPlayer->szChatMessage[0])
	{
		if(lpCurPlayer->dwChatMessageTimer < dwPlayTime)
			lpCurPlayer->szChatMessage[0] = 0;
		else
			lpCharMsgSort[ChatMsgSortCnt++] = lpCurPlayer;
	}
	else
	{
		if(lpCurPlayer->dwTradeMsgCode)
			lpCharMsgSort[ChatMsgSortCnt++] = lpCurPlayer;
	}



	if(ChatMsgSortCnt)
	{
		for(cnt = 0; cnt < ChatMsgSortCnt; cnt++)
		{
			for(cnt2 = cnt + 1; cnt2 < ChatMsgSortCnt; cnt2++)
			{
				if(lpCharMsgSort[cnt]->RendPoint.z < lpCharMsgSort[cnt2]->RendPoint.z || lpCharMsgSort[cnt] == lpCharMsTrace || lpCharMsgSort[cnt] == lpCharSelPlayer)
				{
					lpChar = lpCharMsgSort[cnt];
					lpCharMsgSort[cnt] = lpCharMsgSort[cnt2];
					lpCharMsgSort[cnt2] = lpChar;
				}
			}
		}
	}

	DIRECTDRAWSURFACE lpDDS_clanMark;
	char *szClanName;
	char *szBoxMsg;
	BOOL  selectedBox;

	y = 8 + (ViewAnx >> 6);


	for(cnt = 0; cnt < ChatMsgSortCnt; cnt++)
	{
		dwColor = RGB(230, 255, 160);

		DispBar = FALSE;
		DispMaster = FALSE;
		selectedBox = FALSE;

		if(lpCharMsgSort[cnt]->PartyFlag)
		{
			dwColor = RGB(220, 255, 160);
			DispBar = TRUE;
		}
		else if(lpCharMsgSort[cnt]->smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			if(lpCharMsgSort[cnt]->smCharInfo.Brood == smCHAR_MONSTER_USER)
			{
				dwColor = RGB(220, 255, 160);

				if(lpCharMsgSort[cnt]->smCharInfo.Next_Exp == lpCurPlayer->dwObjectSerial || lpCharMsgSort[cnt]->smCharInfo.ClassClan)
					DispBar = TRUE;
				else
					DispMaster = TRUE;
			}
			else
				dwColor = RGB(255, 210, 210);
		}
		else if(lpCharMsgSort[cnt]->smCharInfo.State == smCHAR_STATE_NPC)
		{
			dwColor = RGB(180, 180, 255);
		}

		if(lpCharMsgSort[cnt] == lpCharMsTrace)
		{
			if(lpCharMsgSort[cnt]->smCharInfo.State == smCHAR_STATE_ENEMY && lpCharMsgSort[cnt]->smCharInfo.Brood != smCHAR_MONSTER_USER)
				dwColor = RGB(255, 230, 200);
			else
				dwColor = RGB(255, 255, 255);

			selectedBox = TRUE;
		}
		else
		{
			if(lpCharMsgSort[cnt] == lpCharSelPlayer && lpCharMsgSort[cnt]->szChatMessage[0]) selectedBox = TRUE;
		}

		lpDDS_clanMark = 0;
		szClanName = 0;
		DWORD	dwClanMgrBit;

		if(lpCharMsgSort[cnt]->smCharInfo.ClassClan)
		{
			if(lpCharMsgSort[cnt] == lpCurPlayer)
			{
				lpDDS_clanMark = cldata.hClanMark16;
				szClanName = cldata.name;
			}
			else if(lpCharMsgSort[cnt]->ClanInfoNum >= 0)
			{
				lpDDS_clanMark = ClanInfo[lpCharMsgSort[cnt]->ClanInfoNum].hClanMark;
				szClanName = ClanInfo[lpCharMsgSort[cnt]->ClanInfoNum].ClanInfoHeader.ClanName;
			}
		}


		if(((lpCharMsgSort[cnt]->szChatMessage[0] || lpCharMsgSort[cnt]->dwTradeMsgCode) && lpCharMsgSort[cnt]->smCharInfo.State && lpCharMsgSort[cnt]->RendPoint.z < 12 * 64 * fONE) ||
			lpCharMsgSort[cnt] == lpCurPlayer)
		{
			if(szClanName && lpCharMsgSort[cnt] != lpCharMsTrace && lpCharMsgSort[cnt] != lpCharSelPlayer)
			{
				if(!lpCurPlayer->smCharInfo.ClassClan || lpCharMsgSort[cnt]->smCharInfo.ClassClan != lpCurPlayer->smCharInfo.ClassClan)
					szClanName = 0;
			}

			if(lpCharMsgSort[cnt]->szChatMessage[0])
			{
				DrawCharacterMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
					lpCharMsgSort[cnt]->szChatMessage, 30, lpDDS_clanMark, szClanName, dwColor, selectedBox);
			}
			else
			{
				if(lpCharMsgSort[cnt]->szTradeMessage[0])
				{
					DrawCharacterShopByeMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
						lpCharMsgSort[cnt]->szTradeMessage, 30, lpDDS_clanMark, dwColor, selectedBox);
				}
			}
		}
		else
		{
			if(DispMaster && !lpCharMsgSort[cnt]->smCharInfo.ClassClan)
			{

				wsprintf(strBuff, "(%s)", lpCharMsgSort[cnt]->smCharInfo.szModelName2 + 1);
				DrawTwoLineMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
					lpCharMsgSort[cnt]->smCharInfo.szName, strBuff, dwColor, RGB(255, 255, 200), 0, selectedBox);

			}
			else
			{
				if(HoMsgBoxMode)
					dwClanMgrBit = lpCharMsgSort[cnt]->dwClanManageBit;
				else
					dwClanMgrBit = 0;

				if(szClanName)
				{
					if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_CONTROL])
						wsprintf(strBuff, "%d/%d", lpCharMsgSort[cnt]->smCharInfo.ClassClan, lpCharMsgSort[cnt]->ClanInfoNum);
					else
						wsprintf(strBuff, "[Clan: %s]", szClanName);

					DrawTwoLineMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y,
						strBuff, lpCharMsgSort[cnt]->smCharInfo.szName, RGB(150, 255, 200), dwColor, lpDDS_clanMark, selectedBox, dwClanMgrBit);
				}
				else
				{
					szBoxMsg = lpCharMsgSort[cnt]->smCharInfo.szName;
					DrawCharacterMessage(lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top + y, szBoxMsg, 30, lpDDS_clanMark, szClanName, dwColor, selectedBox, dwClanMgrBit);
				}
			}
		}

		if(DispBar)
		{
			renderDevice.EndScene();
			lpCharMsgSort[cnt]->DrawStateBar2(lpCharMsgSort[cnt]->RendPoint.x - 30, lpCharMsgSort[cnt]->RendRect2D.top + y - 14);
			renderDevice.BeginScene();
		}
	}


	if(lpCurPlayer->AttackSkil)
	{
		switch(lpCurPlayer->AttackSkil & 0xFF)
		{
		case SKILL_PLAY_CHARGING_STRIKE:
			cnt = lpCurPlayer->frame - lpCurPlayer->MotionInfo->StartFrame * 160;
			if(lpCurPlayer->MotionInfo->EventFrame[0]<(DWORD)cnt && lpCurPlayer->MotionInfo->EventFrame[1]>(DWORD)cnt)
			{
				cnt -= (int)lpCurPlayer->MotionInfo->EventFrame[0];
				cnt2 = (int)(lpCurPlayer->MotionInfo->EventFrame[1] - lpCurPlayer->MotionInfo->EventFrame[0]);

				renderDevice.EndScene();
				lpCurPlayer->DrawChargingBar(lpCurPlayer->RendPoint.x - 30, lpCurPlayer->RendRect2D.bottom, cnt, cnt2);
				renderDevice.BeginScene();
			}
			break;
		case SKILL_PLAY_PHOENIX_SHOT:

			cnt = lpCurPlayer->frame - lpCurPlayer->MotionInfo->StartFrame * 160;
			if(lpCurPlayer->MotionInfo->EventFrame[0]<(DWORD)cnt && lpCurPlayer->MotionInfo->EventFrame[1]>(DWORD)cnt)
			{
				cnt -= (int)lpCurPlayer->MotionInfo->EventFrame[0];
				cnt2 = (int)(lpCurPlayer->MotionInfo->EventFrame[1] - lpCurPlayer->MotionInfo->EventFrame[0]);

				renderDevice.EndScene();
				lpCurPlayer->DrawChargingBar(lpCurPlayer->RendPoint.x - 30, lpCurPlayer->RendRect2D.bottom, cnt, cnt2);
				renderDevice.BeginScene();
			}
			break;
		}
	}

	if(DispInterface)
	{
		if(DispEachMode)
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

		if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{
			extern int Debug_TalkZoomMode;
			if(Debug_TalkZoomMode && lpCurPlayer->TalkPattern)
			{
				extern void DrawTalkZoom(smCHAR *lpChar, smPAT3D *lpPattern, float fx, float fy);
				DrawTalkZoom(lpCurPlayer, lpCurPlayer->TalkPattern, 0.2f, 0.32f);
			}
		}
	}


#ifdef	_NEW_PARTRADE
	if(EachTradeButton && chrEachMaster)
	{

		DisplayPartyTradeButton();
	}
#endif



	DisplaySodScore();

#ifdef _SINBARAM

	RestoreInterfaceTexture();

	dsDrawOffset_X = WinSizeX - 800;
	dsDrawOffset_Y = WinSizeY - 600;

	if(DispInterface)
	{
		sinDraw();
	}

	dsDrawOffset_X = 0;
	dsDrawOffset_Y = 0;
#endif

	if(BellatraEffectInitFlag)
		DrawBellatraFontEffect();

	//renderDevice.lpDDSBack->GetDC(&hdc);

	SelectObject(hdc, hFont);

#ifdef	_IME_ACTIVE

	char *ImeStr;

	int ImeY;

	if(DisplayIME)
	{

		SetBkColor(hdc, RGB(255, 255, 200));
		SetTextColor(hdc, RGB(0, 0, 0));

		if(sinChatDisplayMode == 1)
			ImeY = 442;
		else
			ImeY = 340;




		IMETest.GetImeInfo();
		ImeStr = IMETest.m_szTitle.GetBuffer(IMETest.m_szTitle.GetLength());
		if(ImeStr[0])

			dsTextLineOut(hdc, 8, ImeY - 12, ImeStr, lstrlen(ImeStr));







		SetBkColor(hdc, RGB(255, 255, 255));

}

#endif

	SetBkMode(hdc, TRANSPARENT);

#ifdef _WINMODE_DEBUG

	int	rcv1, rcv2, snd1, snd2, arcv1, brcv1, arcv2, brcv2;
	int LineY;

	if(DisplayDebug)
	{
		rcv1 = 0;
		rcv2 = 0;
		snd1 = 0;
		snd2 = 0;
		arcv1 = 0;
		brcv1 = 0;
		arcv2 = 0;
		brcv2 = 0;

		if(smWsockServer)
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

		if(smWsockUserServer)
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

		SetTextColor(hdc, RGB(0, 0, 0));
		dsTextLineOut(hdc, 11, 11, strBuff, lstrlen(strBuff));
		SetTextColor(hdc, RGB(255, 255, 255));
		dsTextLineOut(hdc, 10, 10, strBuff, lstrlen(strBuff));

		wsprintf(strBuff, "Stage : %s , %s", szGameStageName[0], szGameStageName[1]);
		SetTextColor(hdc, RGB(0, 0, 0));
		dsTextLineOut(hdc, 11, 31, strBuff, lstrlen(strBuff));
		SetTextColor(hdc, RGB(255, 255, 255));
		dsTextLineOut(hdc, 10, 30, strBuff, lstrlen(strBuff));

		wsprintf(strBuff, "World Time (%d:%d)", dwGameHour, dwGameMin);
		SetTextColor(hdc, RGB(0, 0, 0));
		dsTextLineOut(hdc, (WinSizeX >> 1) + 1, 31, strBuff, lstrlen(strBuff));
		SetTextColor(hdc, RGB(255, 255, 255));
		dsTextLineOut(hdc, (WinSizeX >> 1), 30, strBuff, lstrlen(strBuff));


		int cursorX = 0;
		int cursorY = 0;

		if(g_iFzmCursorPosX < 67)
		{
			cursorX = 100;
		}

		if(g_iFzmCursorPosY < 10)
		{
			cursorY = 10;
		}



		wsprintf(strBuff, "[%d:%d]", g_iFzmCursorPosX, g_iFzmCursorPosY);
		dsTextLineOut(hdc, (g_iFzmCursorPosX - 65) + cursorX, (g_iFzmCursorPosY - 10) + cursorY, strBuff, lstrlen(strBuff));

		if(lpCurPlayer->PatLoading == FALSE)
		{
			if(AdminCharMode)
				wsprintf(strBuff, "%s", lpCurPlayer->smCharInfo.szName);
			else
				wsprintf(strBuff, "%s", lpCurPlayer->lpDinaPattern->szPatName);

			SetTextColor(hdc, RGB(0, 0, 0));
			dsTextLineOut(hdc, (WinSizeX >> 1) + 1 + 120, 31, strBuff, lstrlen(strBuff));
			SetTextColor(hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, (WinSizeX >> 1) + 120, 30, strBuff, lstrlen(strBuff));

			wsprintf(strBuff, "Damage : %d", LastAttackDamage);
			SetTextColor(hdc, RGB(0, 0, 0));
			dsTextLineOut(hdc, 9, 48, strBuff, lstrlen(strBuff));
			SetTextColor(hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, 8, 47, strBuff, lstrlen(strBuff));

			wsprintf(strBuff, "RcvDamage:(%d) [%d] %d %d", Record_TotalRecvDamageCount, Record_RecvDamageCount, Record_DefenceCount, Record_BlockCount);
			SetTextColor(hdc, RGB(0, 0, 0));
			dsTextLineOut(hdc, 9, 62, strBuff, lstrlen(strBuff));
			SetTextColor(hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, 8, 61, strBuff, lstrlen(strBuff));

			if(AreaServerMode)
			{
				if(lpWSockServer_Area[0])
				{
					wsprintf(strBuff, "Area Server[0]: (%s)", lpWSockServer_Area[0]->szIPAddr);
					SetTextColor(hdc, RGB(0, 0, 0));
					dsTextLineOut(hdc, 9, 82, strBuff, lstrlen(strBuff));
					SetTextColor(hdc, RGB(255, 255, 255));
					dsTextLineOut(hdc, 8, 81, strBuff, lstrlen(strBuff));
				}
				if(lpWSockServer_Area[1])
				{
					wsprintf(strBuff, "Area Server[1]: (%s)", lpWSockServer_Area[1]->szIPAddr);
					SetTextColor(hdc, RGB(0, 0, 0));
					dsTextLineOut(hdc, 9, 96, strBuff, lstrlen(strBuff));
					SetTextColor(hdc, RGB(255, 255, 255));
					dsTextLineOut(hdc, 8, 95, strBuff, lstrlen(strBuff));
				}

				if(lpWSockServer_DispArea[0])
				{
					wsprintf(strBuff, "Area Server[0]: (%s)", lpWSockServer_DispArea[0]->szIPAddr);
					SetTextColor(hdc, RGB(0, 0, 0));
					dsTextLineOut(hdc, 209, 82, strBuff, lstrlen(strBuff));
					SetTextColor(hdc, RGB(255, 255, 255));
					dsTextLineOut(hdc, 208, 81, strBuff, lstrlen(strBuff));
				}

				if(lpWSockServer_DispArea[1])
				{
					wsprintf(strBuff, "Area Server[1]: (%s)", lpWSockServer_DispArea[1]->szIPAddr);
					SetTextColor(hdc, RGB(0, 0, 0));
					dsTextLineOut(hdc, 209, 96, strBuff, lstrlen(strBuff));
					SetTextColor(hdc, RGB(255, 255, 255));
					dsTextLineOut(hdc, 208, 95, strBuff, lstrlen(strBuff));
				}

				wsprintf(strBuff, "AreaCount(%d) AreaConn(%d) AreaIP( [%d] %d %d ) Step(%d)",
					dwDebugAreaCount, dwDebugAreaConnCount,
					dwDebugAreaIP[0], dwDebugAreaIP[1], dwDebugAreaIP[2], dwDebugAreaStep);

				SetTextColor(hdc, RGB(0, 0, 0));
				dsTextLineOut(hdc, 9, 108, strBuff, lstrlen(strBuff));
				SetTextColor(hdc, RGB(255, 255, 255));
				dsTextLineOut(hdc, 8, 108, strBuff, lstrlen(strBuff));
			}
		}

		SetTextColor(hdc, RGB(255, 255, 255));

		LineY = 48;
		for(i = 0; i < OTHER_PLAYER_MAX; i++)
		{
			if(chrOtherPlayer[i].Flag && chrOtherPlayer[i].Pattern && chrOtherPlayer[i].smCharInfo.State == smCHAR_STATE_USER)
			{
				wsprintf(strBuff, "%s", chrOtherPlayer[i].smCharInfo.szName);
				SetTextColor(hdc, RGB(0, 0, 0));
				dsTextLineOut(hdc, WinSizeX - 220, LineY + 1, strBuff, lstrlen(strBuff));
				SetTextColor(hdc, RGB(255, 255, 255));
				dsTextLineOut(hdc, WinSizeX - 221, LineY, strBuff, lstrlen(strBuff));
				LineY += 16;
				if(LineY > 460)
					break;
			}
		}

		int	MonCharBuff[OTHER_PLAYER_MAX];
		int MonCharCnt = 0;
		int	MonCnt;

		for(i = 0; i < OTHER_PLAYER_MAX; i++)
		{
			if(chrOtherPlayer[i].Flag && chrOtherPlayer[i].Pattern && chrOtherPlayer[i].smCharInfo.State != smCHAR_STATE_USER)
				MonCharBuff[MonCharCnt++] = i;
		}

		LineY = 48;
		for(i = 0; i < MonCharCnt; i++)
		{
			if(MonCharBuff[i] >= 0)
			{
				MonCnt = 1;
				for(cnt = i + 1; cnt < MonCharCnt; cnt++)
				{
					if(MonCharBuff[cnt] >= 0 && lstrcmp(chrOtherPlayer[MonCharBuff[cnt]].smCharInfo.szName,
						chrOtherPlayer[MonCharBuff[i]].smCharInfo.szName) == 0)
					{
						MonCharBuff[cnt] = -1;
						MonCnt++;
					}
				}

				wsprintf(strBuff, "%s x %d", chrOtherPlayer[MonCharBuff[i]].smCharInfo.szName, MonCnt);
				SetTextColor(hdc, RGB(0, 0, 0));
				dsTextLineOut(hdc, WinSizeX - 380, LineY + 1, strBuff, lstrlen(strBuff));

				if(chrOtherPlayer[MonCharBuff[i]].smCharInfo.State == smCHAR_STATE_NPC)
					SetTextColor(hdc, RGB(192, 192, 255));
				else
					SetTextColor(hdc, RGB(255, 192, 192));
				dsTextLineOut(hdc, WinSizeX - 381, LineY, strBuff, lstrlen(strBuff));
				LineY += 16;
				if(LineY > 460) break;
			}
		}
	}
#endif

	//renderDevice.lpDDSBack->ReleaseDC(hdc);

	if(DisconnectFlag)
	{

		if(DisconnectServerCode == 0)
			DrawMessage(MidX - 64, MidY, mgDiconnect, 36, BOX_ONE);

		if(DisconnectServerCode == 1)
			DrawMessage(MidX - 64, MidY, mgDiconnect1, 36, BOX_ONE);

		if(DisconnectServerCode == 2)
			DrawMessage(MidX - 64, MidY, mgDiconnect2, 36, BOX_ONE);

		if(DisconnectServerCode == 3)
			DrawMessage(MidX - 64, MidY, mgDiconnect3, 36, BOX_ONE);

		if(DisconnectServerCode == 4)
			DrawMessage(MidX - 64, MidY, mgDiconnect4, 36, BOX_ONE);


#ifdef	_WINMODE_DEBUG
		if(smConfig.getSecurity() < AccountTypes::SEC_MODERATOR && !quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime)
			quit = TRUE;
#else
		if(!quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime)
			quit = TRUE;
#endif
	}
	else
	{
		if(quit)
			DrawMessage(MidX - 40, MidY, mgCloseGame, 36, BOX_ONE);
		else
		{
			if(dwCloseBoxTime && dwCloseBoxTime > dwPlayTime)
			{
				DrawMessage(MidX - 100, MidY, mgCloseWindow, 36, BOX_ONE);
			}
			else
			{
				if(dwBattleQuitTime)
				{
					if((dwBattleQuitTime + 5000) > dwPlayTime)
						DrawMessage(MidX - 40, MidY, mgCloseBattle, 36, BOX_ONE);
					else
						dwBattleQuitTime = 0;
				}
			}
		}
	}

	DarkLevel = BackDarkLevel;

	if(renderDevice.Flip() == FALSE)
	{
		DisconnectFlag = dwPlayTime;
		quit = 1;
	}

	return TRUE;
	}

void smPlayD3D(int x, int y, int z, int ax, int ay, int az)
{
	eCAMERA_TRACE	eTrace;
	int	ap;

	DispPolyCnt = 0;

	if(renderDevice.lpDDSBack->IsLost() == DDERR_SURFACELOST || renderDevice.lpDDSPrimary->IsLost() == DDERR_SURFACELOST)
	{

		DisconnectFlag = dwPlayTime;
		quit = TRUE;

		renderDevice.lpDDSPrimary->Restore();
		renderDevice.lpDDSBack->Restore();
		RestoreFlag = TRUE;
		return;
	}
	else
	{
		if(RestoreFlag)
		{
			RestoreAll();
			RestoreFlag = FALSE;
		}
	}

	SetRendSight();

	if(g_IsDxProjectZoomIn <= 0)
		DrawGameState();
	else
		VirtualDrawGameState();

	if(smConfig.getSecurity() != AccountTypes::SEC_PLAYER && !smConfig.isSecurityAuth())
	{
		SendAdminMode(smConfig.getSecurity());
	}

	int Mapfl;
	int cy;
	int mapY;

	Mapfl = 0;
	cy = y + 16 * fONE;

	if(!DebugPlayer)
	{
		if(smGameStage[0])
		{
			mapY = (smGameStage[0]->GetHeight(x, z));
			if(y < mapY)
			{
				y = mapY;
				y += 8 << FLOATNS;
			}
			if(mapY > CLIP_OUT) Mapfl++;
		}
		if(smGameStage[1])
		{
			mapY = (smGameStage[1]->GetHeight(x, z));
			if(y < mapY)
			{
				y = mapY;
				y += 8 << FLOATNS;
			}
			if(mapY > CLIP_OUT)
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


	if(dwM_BlurTime && IsCreateNewRenderTarget())
	{
		if(dwM_BlurTime < dwPlayTime)
		{
			dwM_BlurTime = 0;
			SetFilterEffect(FILTER_EFFECT_SET_BRIGHT_CONTRAST, 160);
			SetFilterEffect(FILTER_EFFECT_DEL_MOTION_BLUR, 0);
		}
	}

	if(GetFilterEffect())
	{
		renderDevice.ClearViewport(D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET);
		ChangeRenderTarget(NEW_TARGET_BACK);
	}

	renderDevice.ClearViewport(D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET);

	y += (32 << FLOATNS);

	// Camera Desbugada ( pode aproximar )
	//if(anx <= 40 && dist <= 40)
	//{
	//	y -= ((110 - dist) << FLOATNS);
	//}

	TraceTargetPosi.x = x;
	TraceTargetPosi.y = y;
	TraceTargetPosi.z = z;

	if(AutoCameraFlag)
	{

		TraceCameraMain();

		x = TraceCameraPosi.x;
		y = TraceCameraPosi.y;
		z = TraceCameraPosi.z;
	}


	int ey = lpCurPlayer->pY + (32 * fONE);

	// Camera Desbugada ( pode aproximar )
	//if(anx <= 40 && dist <= 40)
	//{
	//	ey += ((100 - dist) * fONE);
	//}

	ActionGameMode = FALSE;


	if(lpCurPlayer && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ACTION)
	{

		x = lpCurPlayer->pX;
		y = StageField[lpCurPlayer->OnStageField]->ActionCamera.FixPos.y + 80 * fONE;
		z = StageField[lpCurPlayer->OnStageField]->ActionCamera.FixPos.z*fONE;

		if(x < StageField[lpCurPlayer->OnStageField]->ActionCamera.LeftX*fONE) x = StageField[lpCurPlayer->OnStageField]->ActionCamera.LeftX*fONE;
		else if(x > StageField[lpCurPlayer->OnStageField]->ActionCamera.RightX*fONE) x = StageField[lpCurPlayer->OnStageField]->ActionCamera.RightX*fONE;

		MakeTraceMatrix(&eTrace, x, y, z, x, lpCurPlayer->pY, 326711 * fONE);

		ax = eTrace.AngX;
		ay = eTrace.AngY;
		smRender.OpenCameraPosi(x, y, z, &eTrace.eRotMatrix);

		ActionGameMode = TRUE;
	}
	else if(!DebugPlayer)
	{
		MakeTraceMatrix(&eTrace, x, y, z, lpCurPlayer->pX, ey, lpCurPlayer->pZ);

		ax = eTrace.AngX;
		ay = eTrace.AngY;
		smRender.OpenCameraPosi(x, y, z, &eTrace.eRotMatrix);
	}

	smRender.ClearLight();

	if(DarkLevel > 0)
	{
		ap = DarkLevel + (DarkLevel >> 2);

		if(StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_DUNGEON)
		{
			DarkLightRange = 400 * fONE;
			ap = DarkLevel;
		}
		else
			DarkLightRange = 260 * fONE;


		if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
		{


		}
		else
			smRender.AddDynamicLight(lpCurPlayer->pX, lpCurPlayer->pY + 32 * fONE, lpCurPlayer->pZ, ap, ap, ap, 0, DarkLightRange);
	}

	DynLightApply();

	DrawSky(x, y, z, ax, ay, az);

	smRender.DeviceRendMode = FALSE;

	renderDevice.BeginScene();
	if(smRender.m_FogIsRend && smRender.m_FogMode)
		renderDevice.SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);

	smRender.bApplyRendObjLight = TRUE;
	DrawPat3D(x, y, z, ax, ay, az);

	smRender.bApplyRendObjLight = FALSE;
	NumPoly = DisplayStage(x, y, z, ax, ay, az);

	smRender.bApplyRendObjLight = TRUE;
	DrawPat3D_Alpha();

	smRender.ClearObjLight();

	if(smRender.m_FogIsRend && smRender.m_FogMode)
		renderDevice.SetRenderState(D3DRENDERSTATE_FOGENABLE, FALSE);

	smRender.ClearLight();
	smRender.Color_A = 0;
	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;


	DrawPatShadow(x, y, z, ax, ay, az);

	renderDevice.EndScene();

	smRender.DeviceRendMode = TRUE;


	RestoreInterfaceTexture();

	DrawEffect(x, y, z, ax, ay, az);
	cSin3D.Draw(x, y, z, ax, ay, az);
	DrawPat2D(x, y, z, ax, ay, az);


	if(GetFilterEffect() && GetRenderTarget() == NEW_TARGET_BACK)
	{
		SetNewTargetTextureState();

		renderDevice.BeginScene();
		RenderFilterEffect();
		renderDevice.EndScene();

		DefaultsNewTargetTextureState();
	}


	if(g_IsDxProjectZoomIn)
	{
		DrawFullZoomMap();
	}
	else
	{
		if(cInterFace.sInterFlags.MapOnFlag)
		{

			if(DispInterface)
			{
				DrawFieldMap();
			}
		}
	}

	if((!MsTraceMode && MouseButton[0] == 0) || lpCurPlayer->smCharInfo.Stamina[0] > (lpCurPlayer->smCharInfo.Stamina[1] >> 2))
	{

		lpCurPlayer->MoveMode = cInterFace.sInterFlags.RunFlag;

		if(ActionGameMode)
			lpCurPlayer->MoveMode = ActionDashMode;
	}
	else
	{
		if(lpCurPlayer->smCharInfo.Stamina[0] == 0)
			lpCurPlayer->MoveMode = FALSE;
	}

	smRender.CloseCameraPosi();

	Disp_tx = MsSelPos.x - 32;
	Disp_ty = MsSelPos.y;


	IncTextureFrame();
}

char *CompCmdStr(char *strCmdLine, char *strword)
{
	int len, len2;
	int cnt, cnt2;

	len = lstrlen(strCmdLine);
	len2 = lstrlen(strword);

	for(cnt = 0; cnt < len - len2; cnt++)
	{
		for(cnt2 = 0; cnt2 < len2; cnt2++)
		{
			if(strword[cnt2] != strCmdLine[cnt + cnt2]) break;
		}
		if(cnt2 == len2)
			return &strCmdLine[cnt + cnt2];
	}

	return NULL;
};



char *RegPath_3DMax = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\3D Studio MAX R3.1L";
char *RegPath_3DMax2 = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\3D Studio MAX R3.1";
char *RegPath_Photoshop = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Adobe Photoshop 6.0";
char *RegPath_ACDSee = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\ACDSee";





int SetCreateFont()
{

#ifdef _LANGUAGE_BRAZIL	
	hFont = CreateFont(16,
		0,
		0,
		0,
		FW_THIN,
		FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET | FS_LATIN1,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FIXED_PITCH | FF_MODERN,
		"Noto Sans");
#endif					

	return TRUE;

}


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

	switch(messg)
	{


	case WM_KEYDOWN:

		if(GameMode == 2)
		{

			if(wParam == VK_RETURN && VRKeyBuff[wParam] == 0 && !sinMessageBoxShowFlag &&
				!VRKeyBuff[VK_CONTROL])
			{

				SetChatingLine("");
			}

			if(wParam == VK_BACK && VRKeyBuff[wParam] == 0)
			{
				if(HoMsgBoxMode)
					HoMsgBoxMode = 0;
				else
					HoMsgBoxMode = 1;

				SetMessageFrameSelect(HoMsgBoxMode);
			}

			if(wParam == 'M' && VRKeyBuff[wParam] == 0)
			{

				sinCheck_ShowHelpMap();
			}

			if(dwYahooTime > dwPlayTime && dwYahooTime < (dwPlayTime + 60 * 1000))
			{
				if(wParam == VK_SPACE && VRKeyBuff[wParam] == 0)
				{
					if(lpCurPlayer && lpCurPlayer->MotionInfo)
					{
						stm = sinGetStamina();
						cnt = (lpCurPlayer->smCharInfo.Stamina[1] * 3) / 100;
						if(lpCurPlayer->MotionInfo->State<0x100 && stm>cnt)
						{
							if(lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_YAHOO))
							{

								if(cnt > 0) sinSetStamina(stm - cnt);
							}
						}
					}
					VRKeyBuff[wParam] = 1;
					return FALSE;
				}
			}



			if(smRender.m_GameFieldView && !VRKeyBuff[wParam])
			{
				if(wParam == VK_ADD)
				{
					if(smRender.m_GameFieldViewStep < 22)
					{
						smRender.m_GameFieldViewStep++;

						RendSightSub(1);
					}
				}
				else if(wParam == VK_SUBTRACT)
				{
					if(smRender.m_GameFieldViewStep > 1)
					{
						smRender.m_GameFieldViewStep--;

						RendSightSub(1);
					}
				}
			}




#ifdef _WINMODE_DEBUG

			if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
			{

				if(wParam == VK_F9 && VRKeyBuff[VK_F9] == 0)
				{
					if(DisplayDebug) DisplayDebug = FALSE;
					else DisplayDebug = TRUE;
				}

				if(VRKeyBuff[VK_CONTROL] && wParam == 'E' && VRKeyBuff['E'] == 0)
				{




					strcpy_s(szSOD_String, "Score up 5000 pts");
					bSOD_StringColor[0] = 128;
					bSOD_StringColor[1] = 255;
					bSOD_StringColor[2] = 128;
					SOD_StringCount = 256;
				}









				if(VRKeyBuff[VK_SHIFT] && !VRKeyBuff[VK_CONTROL])
				{

					if(wParam == VK_F5 && VRKeyBuff[VK_F5] == 0)
					{
						SkipNextField = 1;
					}
					if(wParam == VK_F6 && VRKeyBuff[VK_F6] == 0)
					{
						SkipNextField = 2;
					}


					if(wParam == VK_F7 && VRKeyBuff[VK_F7] == 0)
					{
						if(smRender.dwMatDispMask)
							smRender.dwMatDispMask = 0;
						else
							smRender.dwMatDispMask = sMATS_SCRIPT_NOTVIEW;
					}


					if(wParam == VK_F8 && VRKeyBuff[wParam] == 0)
					{

						if(ktj_imsiDRAWinfo) ktj_imsiDRAWinfo = 0;
						else ktj_imsiDRAWinfo = 1;
					}
				}

				if(VRKeyBuff[VK_CONTROL] && wParam == VK_F11 && VRKeyBuff[wParam] == 0)
				{
					DispInterface = !DispInterface;
				}



				if(AdminCharMode)
				{
					if(wParam == VK_INSERT && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
					{

						SendAdd_Npc(lpCurPlayer, 0);
					}
					if(wParam == VK_DELETE && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
					{

						if(lpCharSelPlayer)
						{

							SendDelete_Npc(lpCharSelPlayer);
						}
					}
				}
				else
				{
					if(wParam == VK_INSERT && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
					{

						SendAddStartPoint(lpCurPlayer->pX, lpCurPlayer->pZ);
					}

					if(wParam == VK_DELETE && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
					{

						if(lpSelItem)
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


	if(InterfaceParty.PartyPosState == PARTY_NONE)
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
	if(vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
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
	if(vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
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
