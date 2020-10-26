
#define CHARACTER_USER_MAX			5
#define CHARACTER_JOB_MAX			4


#define CHARACTER_SELECT_STATE		0
#define RACE_SELECT_STATE			1
#define JOB_SELECT_STATE			2
#define FACE_SELECT_STATE			3
#define NAME_SELECT_STATE			4
#define COMPLETE_SELECT_STATE		5
#define START_GAME_STATE			6
#define RETURN_OPENING_STATE        7


#define TEMPSCRON					0





#define TRIBE_Tempscron 0		
#define TRIBE_Moryon	1		

struct HoNewCharInfo
{
	int	  JobCode;
	int   Strength;
	int   Spirit;
	int   Talent;
	int   Dexterity;
	int   Health;


};



#define		ERROR_NONAME_NEWPLAYER		10	
#define		ERROR_MAX_NEWPLAYER			20	
#define		ERROR_EXHIST_NEWPLAYER		30  
#define		ERROR_SELECT_CHAR			40	
#define		ERROR_SELECT_RACE			50  
#define		ERROR_SELECT_JOB			60  
#define		ERROR_SELECT_FACE			80  
#define     ERROR_DELETE_CLAN_MEMBER    90  
#define     ERROR_CLAN_SERVER_NONE     100  

#define     SUB_SELECT_NONE					0
#define		SUB_SELECT_CHARACTER_MANAGE		1 
#define		SUB_SELECT_CHARACTER_USER		2 
#define		SUB_SELECT_CHARACTER_NEW		3 
#define		SUB_SELECT_CHARACTER_NEW_SERVER	4 
#define		SUB_SELECT_BACK					5 

class HoLogin
{
public:




	int tribeNum;
	RECT menuPos[2];



	int						MorFaceImage[CHARACTER_JOB_MAX][4][2];

	void Init_UseMor();



	BOOL					ClanMarkUpdateSuccessFlag;




	int			MainBoxFrameImage1[4];
	int			MainBoxFrameImage2[4];
	int			TitleBoxFrameImage;
	int			TitleNameImage;


	int						TempscronMarkImage;
	int						TempscronLogoImage;

	int						MoryonMarkImage;
	int						MoryonLogoImage;

	int						TempscronTextImage;
	int						MoryonTextImage;

	int						RaceTextBoxImage[2];
	int						JobTextBoxImage[2];

	int						TempscronJobImage[CHARACTER_JOB_MAX][2];
	int						MoryonJobImage[CHARACTER_JOB_MAX][2];
	int						TempscronJobTextImage[CHARACTER_JOB_MAX];
	int						MoryonJobTextImage[CHARACTER_JOB_MAX];


	int						FaceBoxBigImage[2];
	int						FaceBoxSmallImage[3];

	BOOL					FaceSelectFirstFlag;
	int						DrawTitle(int state);

	int						ErrorDelayCount;
	BOOL					StartErrorDelayFlag;

	int						m_ScreenHalf;
private:

	smSTAGE3D	*Stage;
	POINT3D		CaAngle;
	POINT3D		TarPosi;
	int			TarDist;

	BOOL		CharacterStopFlag;
	BOOL		CharacterReturnFlag;


	int SelectCurrentState;
	int SelectNextState;

	int  SelectSubState;

	BOOL FocusWndFlag;


	int		ErrorSelect;


	HoButton				OkButton;
	HoButton				BackButton;
	HoButton				QuitButton;
	HoButton				DeleteButton;
	HoButton				NewCharButton;



	smCHAR					UserCharacter[CHARACTER_USER_MAX];
	int						UserCharacterCount;

	smCHAR					JobCharacter[CHARACTER_JOB_MAX];
	int						JobCharacterCount;



	int						NewCharacterImage;
	float					NewCharacterImageBlendCount;
	bool					NewCharacterImageBlendFlag;

	int						UserCharacterInfoImage;
	int						UserCharacterInfoBackImage;













	DIRECTDRAWSURFACE	FaceSelectImage;
	int						TempFaceImage[CHARACTER_JOB_MAX][4][2];






	int						MouseDownCharacterNum;
	int						MouseMoveCharacterNum;

	int						JobBodySelectNum;
	int						JobFaceSelectNum;
	char					UserCharacterNewName[256];


	DIRECTDRAWSURFACE	GameMapImage;
	int						MapBlendCount;
	BOOL					MapBlendFlag;


	HoMessage				Message;
	HoMessageBox			MessageBox;





	int						BlackBoxImage;


	HFONT					Font;


	int						RaceMarkBlendCount;

	int						RaceMarkScaleSize;

	int						LoginVolume;
public:
	int		Load();
	int		Init();
	int		Close();
	int		Main();
	int		Draw();


	int		SetChangeJobFace(char *charFile1, char *chrFile2, int jobIndex);

	int		InitUserCharacter();
	int		DrawUserCharacter(int x, int y, int z, int ax, int ay, int az);
	int		DrawJobCharacter(int x, int y, int z, int ax, int ay, int az);
	int		DrawGameFrame();
	int		DrawLight();

	int		DrawMap(int alpha);
	int		DrawCharacterInfo();
	int		MainDefaultButton();

	int		KeyFilter();



	BOOL		FadeCurrentState;
	BOOL		FadeNextState;

	int		BlendValue;
	int		DrawFade();
	int		MainFade();
	int		MainFadeIn();
	int		MainFadeOut();
	void	SetFade();
	int		ReLoad();
	void resize();

	HoLogin();
	~HoLogin();
private:
	int		DrawSelectSubState();
	int		CameraUpDown();
	int		AddUserCharacter(char *chrFile1, char *chrFile2, int jobCode = 0);
	int		AddJobCharacter(char *chrFile1, char *chrFile2, int index = -1);
	int		GetSelectCharacter(smCHAR *lpChar);
	void	LoadLoadingImage(int level);

};



extern char *szTempPikeFaceName[2][3];
extern char *szTempArcherFaceName[2][3];
extern char *szTempMechFaceName[2][3];
extern char *szTempFighterFaceName[2][3];