
#include "sinbaram\\SinLinkHeader.h"
#include "..\\HoBaram\\HoLinkHeader.h"
#include "..\\smreg.h"
#include "..\\HoBaram\\HoTextFile.h"
#include "..\\HoBaram\\HoMinMax.h"
#include "..\\HoBaram\\HoNewParticle.h"
#include "..\\HoBaram\\HoNewParticleMgr.h"
#include "Language\\language.h"
#include "..\\CAutoCamera.h"

#include "File\File.h"
#include "Priston\Login.h"

static CAutoCamera		s_AutoCamera;

#ifdef _LANGUAGE_BRAZIL	
char *szJoinWebUrl = "http://www.pristontale.com";
#endif

extern POINT3D WaveCameraPosi;
extern int	   WaveCameraFactor;
extern int	   WaveCameraTimeCount;
extern int	   WaveCameraDelay;
extern BOOL	   WaveCameraFlag;

char	UserAccount[ACCOUNT_SIZE];
char	UserPassword[PASSWORD_SIZE];

HoOpening::HoOpening()
{


	Stage = NULL;
	PatCamera = NULL;

	LogoBlendValue = 0;
	LoginBlendValue = 0;

	Load();
	StartConnectServerFlag = FALSE;
	WorkState = STATE_OPENING;

	MidY = (600 / 2);
	SetWindowText(hTextWnd, NULL);

	memset(UserAccount, 0, sizeof(UserAccount));
	memset(UserPassword, 0, sizeof(UserPassword));

	TarDist = 1600 * fONE;
	CaAngle.x = 220;
	CaAngle.y = 0;
	CaAngle.z = 0;




	MouseDownServerIndex = -1;
	CameraFrame = 0;
}

HoOpening::~HoOpening()
{
	Close();
}

int HoOpening::Init()
{

	return TRUE;
}




void HoOpening::SetCameraCharPos(void){}





void HoOpening::SetParticleEffectSpawn(void){}






int HoOpening::DebugModeLoadFieldInfo(void){

	return TRUE;
}


int HoOpening::Load(){

	return TRUE;
}



int		CaretCount = 0;
DWORD	End = 0;
extern int Client_Version;

#define	DISP_LOGIN_LEN		15

int HoOpening::Draw(){

	return TRUE;
}

void HoOpening::resize(){}

HANDLE	hHoLoginThread = 0;

DWORD WINAPI HoLoginThreadProc(void *pInfo)
{
	return TRUE;
}

int HoOpening::LoginDataServer()
{
	DWORD dwHoLoginThreadId;

	if(!hHoLoginThread)
	{
		hHoLoginThread = CreateThread(NULL, 0, HoLoginThreadProc, this, 0, &dwHoLoginThreadId);

		PlayWav2(13 - 1);
		StartConnectServerFlag = TRUE;
		return TRUE;
	}
	return FALSE;
}

int HoOpening::LoginGameServer(int serverIndex)
{

	PlayWav2(13 - 1);
	DisconnectServer_GameMain();


	if(ConnectServer_GameMain(UserServerListInfo[serverIndex].szServerIp1,
							  UserServerListInfo[serverIndex].dwServerPort1,
							  UserServerListInfo[serverIndex].szServerIp2,
							  UserServerListInfo[serverIndex].dwServerPort2,
							  UserServerListInfo[serverIndex].szServerIp3,
							  UserServerListInfo[serverIndex].dwServerPort3))
	{
		StartConnectServerFlag = TRUE;
	}
	else
		ConnectError = ERROR_CONNECT;

	return TRUE;
}


int HoOpening::KeyFilter(char *message)
{
	if(message == NULL || hFocusWnd == NULL)
		return FALSE;

	if(lstrlen(message) >= 31 && message[30] != '\t')
	{
		message[30] = 0;
		SetWindowText(hFocusWnd, 0);
		SetWindowText(hFocusWnd, message);
		SendMessage(hFocusWnd, EM_SETSEL, lstrlen(message) + 1, lstrlen(message) + 1);
	}

	for(int index = 0; index < (int)strlen(message); index++)
	{
		if(message[index] == '\t')
		{
			message[index] = 0;
			SetWindowText(hFocusWnd, 0);

			if(LoginInputState == 0)
			{
				SetIME_Mode(0);
				LoginInputState = 1;
				SetWindowText(hFocusWnd, UserPassword);
				SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserPassword) + 1, lstrlen(UserPassword) + 1);
			}
			else if(LoginInputState == 1)
			{
				LoginInputState = 0;
				SetWindowText(hFocusWnd, UserAccount);
				SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserAccount) + 1, lstrlen(UserAccount) + 1);
			}
		}
		else if(message[index] >='a' &&  message[index] <= 'z'
			|| message[index] >= 'A' &&  message[index] <= 'Z'
			|| message[index] >= '0' &&  message[index] <= '9')
		{
			continue;
		}
		else
		{
			message[index] = 0;
			SetWindowText(hFocusWnd, message);
			SendMessage(hTextWnd, EM_SETSEL, lstrlen(message) + 1, lstrlen(message) + 1);
			break;
		}


	}
	return TRUE;
};


int HoOpening::MainFadeIn()
{
	if(FadeNextState == FADE_IN)
	{
		ScreenBlendValue -= 2;
		if(ScreenBlendValue < 0)
			ScreenBlendValue = 0;

		if(ScreenBlendValue <= 0)
		{
			ScreenBlendValue = 0;
			FadeCurrentState = FADE_IN;
			FadeNextState = FADE_IN;
		}
	}
	return TRUE;
}


int HoOpening::MainFadeOut()
{
	if(FadeNextState == FADE_OUT)
	{
		if(ScreenBlendValue < 255)
		{
			OpeningBgmVolume -= 2;
			if(OpeningBgmVolume < 0)
				OpeningBgmVolume = 0;
			ScreenBlendValue += 3;
		}

		if(ScreenBlendValue >= 255)
		{
			ScreenBlendValue = 255;
			LogoBlendValue = 255;
			LoginBlendValue = 255;
			FadeCurrentState = FADE_OUT;
			FadeNextState = FADE_OUT;
		}
	}
	return TRUE;
}


void HoOpening::InitCinemaFadeEffect()
{
	CinemaFadeOutFlag = FALSE;
	CinemaBlendValue = 0;
	CinemaFadeState = STATE_FADE_NONE;
}


void HoOpening::MainCinemaFadeEffect()
{
	if(CinemaFadeState == STATE_FADE_IN)
	{
		CinemaBlendValue += 5;
		if(CinemaBlendValue >= 255)
			CinemaBlendValue = 255;
	}

	if(CinemaFadeState == STATE_FADE_IN && CinemaBlendValue >= 255)
		CinemaFadeState = STATE_FADE_OUT;

	if(CinemaFadeState == STATE_FADE_OUT)
	{
		CinemaBlendValue -= 5;
		if(CinemaBlendValue <= 0)
			CinemaBlendValue = 0;
	}
}



void HoOpening::DrawCinemaFadeEffect(){}


int HoOpening::FastFade(){

	return TRUE;
}

int HoOpening::DrawFade(){

	return TRUE;
}

int HoOpening::MainFade(){

	return TRUE;
}

void HoOpening::SetFade(){}


void HoOpening::Close(){}






int HoOpening::Main(){

	return TRUE;
}


