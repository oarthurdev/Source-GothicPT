#ifndef _HO_OPENING_H_
#define _HO_OPENING_H_

#define FADE_IN		0
#define FADE_OUT	1

#define ERROR_NONE				     0	   
#define ERROR_CONNECT			     1	   
#define ERROR_NO_ACCOUNT		     2     
#define ERROR_NO_PASSWORD		     3     
#define ERROR_NO_BETA_TESTER	     4     
#define ERROR_NO_ACCOUNT_IN		     5     
#define ERROR_NO_FILTER_PASSWORD     6     
#define ERROR_NO_VERSION		     7     
#define ERROR_NO_LIMIT			     8     
#define ERROR_NO_SERVER_CONNECT      9     

#define ERROR_NO_USE_DATE_OVER	    10     
#define ERROR_NO_USE_TIME_OVER	    11     
#define ERROR_DELETE_ACCOUNT_NOTIFY 12     

#define ERROR_SERVER_TRAFFIC_BUSY	13     
#define ERROR_SERVER_WAIT_MOMNENT	14     
#define ERROR_THIRD_CONNECT         15     
#define ERROR_HAN_PASSWORD          16     
#define ERROR_12YEARS		        17     
#define ERROR_HOMEAGREE		        18     

#define ERROR_UNTIL_LOGINDENIED		23
#define ERROR_LOGIN_DENIED			24

enum
{
	STATE_START, STATE_OPENING, STATE_LOGIN_INPUT, STATE_SERVER_SELECT, STATE_END
};

enum
{
	STATE_FADE_NONE, STATE_FADE_IN, STATE_FADE_OUT
};

class HoOpening
{


public:

	smPAT3D     *PatCamera;
	POINT3D     PatCameraWorldPos;
	smOBJ3D     *ObjCamera;
	int			CameraFrame;

	smSTAGE3D	*Stage;

	POINT3D	CaAngle;
	int		TarDist;


	int			GameLogo[6];
	int			TriGlowLogo;


	int			ButtonLoginImage[2];
	int			ButtonQuitImage[2];
	int			ButtonNewJoinImage[2];
	int			PristonLogoImage;

	BOOL		CinemaFadeOutFlag;

	int			CinemaFadeState;

	int			CinemaBlendValue;
	void		InitCinemaFadeEffect();
	void		MainCinemaFadeEffect();
	void		DrawCinemaFadeEffect();


	int			LoginInputState;
	BOOL		StartQuitFlag;


	int			WorkState;

	int			CurrentWorkState;
	int			NextWorkState;


	BOOL		StartConnectServerFlag;
	BOOL		ConnectServerSucessFlag;
	int			ServerWaitTimeCount;


	int			ConnectError;
	int			ConnectErrorCount;
	HoMessage	Message;
	BOOL		FocusWndFlag;

	BOOL		MouseDownFlag;

private:



	int			BlackBoxImage;
	int			WhiteBoxImage;

	BOOL		FadeCurrentState;
	BOOL		FadeNextState;

	int			ScreenBlendValue;
	int			LogoBlendValue;
	int			LoginBlendValue;
	int			ServerSelectBlendValue;

	int			MouseDownServerIndex;
	int			OpeningBgmVolume;

	int			MainFadeIn();
	int			MainFadeOut();
	int			MainFade();
	int			DrawFade();
	int			FastFade();

	HoMessageBox	MessageBox;

	int		startLogoX;
	int		startLogoY;
	int		startLogoAddX;
	int		startAccountAddX;
	int		startAccountAddY;
	int		m_AddWidth;
	int		m_AddHeight;



	smMATRIX	m_CameraRotInvert;
	int			m_IsDrawOpening;
	int			m_AutoCameraFrameTime;
	int			m_ParticleSpawnTimeCount;


public:

	int			LoginDataServer();
	int			LoginGameServer(int serverIndex);

	int		Init();
	int		Load();
	void	Close();

	int		Main();
	int		Draw();

	void resize();



	void	SetFade();
	int		KeyFilter(char *message);
	void    SetConnectError(int errorCode)
	{
		ConnectError = errorCode;
	}
	HoOpening();
	~HoOpening();




	int  DebugModeLoadFieldInfo(void);
	void SetCameraCharPos(void);
	void SetParticleEffectSpawn(void);

};

extern HWND hTextWnd;
#endif