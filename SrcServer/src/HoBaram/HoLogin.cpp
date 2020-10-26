
#include "sinbaram\\SinLinkHeader.h"
#include "..\\HoBaram\\HoLinkHeader.h"
#include "..\\HoBaram\\HoTextFile.h"
#include "..\\HoBaram\\HoMinMax.h"
#include "..\\HoBaram\\HoNewParticle.h"
#include "..\\HoBaram\\HoNewParticleMgr.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "..\\CurseFilter.h"		

#include "Language\\language.h"
#include "Language\\jts.h"



int  CharacterPosX = 0;
int  CharacterPosZ = 0;

int  MouseDblClick;

char SelectCharacterName1[3][500];
char SelectCharacterName2[3][500];

char JobSelectCharacterName1[4][500];
char JobSelectCharacterName2[4][500];


static int UserCharacterPos[5][2] =
{
	{ 0 ,-110 },
	{ -35 ,-90 },
	{ 35 ,-90 },
	{ -70 ,-60 },
	{ 70 ,-60 }
};

static int JobCharacterPos[5][2] = {
	{ -75, -320 },
	{ -25, -330 },
	{ 25, -330 },
	{ 75, -320 }
};

static int CharacterInfoPosi[5] = { 362, 243, 488, 154, 588 };


static char *szTempFighterBodyName[] = {
	"char\\tmABCD\\b001.ini",
	"char\\tmABCD\\b002.ini",
	"char\\tmABCD\\b003.ini",
	"char\\tmABCD\\b004.ini",
	"char\\tmABCD\\b005.ini",
	"char\\tmABCD\\b006.ini",
	"char\\tmABCD\\b007.ini"
};
static char *szTempMechBodyName[] = {
	"char\\tmABCD\\a001.ini",
	"char\\tmABCD\\a002.ini",
	"char\\tmABCD\\a003.ini",
	"char\\tmABCD\\a004.ini",
	"char\\tmABCD\\a005.ini",
	"char\\tmABCD\\a006.ini",
	"char\\tmABCD\\a007.ini"
};
static char *szTempArcherBodyName[] = {
	"char\\tmABCD\\d001.ini",
	"char\\tmABCD\\d002.ini",
	"char\\tmABCD\\d003.ini",
	"char\\tmABCD\\d004.ini",
	"char\\tmABCD\\d005.ini",
	"char\\tmABCD\\d006.ini",
	"char\\tmABCD\\d007.ini"
};
static char *szTempPikeBodyName[] = {
	"char\\tmABCD\\c001.ini",
	"char\\tmABCD\\c002.ini",
	"char\\tmABCD\\c003.ini",
	"char\\tmABCD\\c004.ini",
	"char\\tmABCD\\c005.ini",
	"char\\tmABCD\\c006.ini",
	"char\\tmABCD\\c007.ini"
};

//static char *szTempAssassineBodyName[] = {
//	"char\\tmABCD\\e001.ini",
//	"char\\tmABCD\\e002.ini",
//	"char\\tmABCD\\e003.ini",
//	"char\\tmABCD\\e004.ini",
//	"char\\tmABCD\\e005.ini",
//	"char\\tmABCD\\e006.ini",
//	"char\\tmABCD\\e007.ini"
//};


char *szTempFighterFaceName[2][3] = {
	{
		"char\\tmABCD\\tmh-b01.inf",
		"char\\tmABCD\\tmh-b02.inf",
		"char\\tmABCD\\tmh-b03.inf"
	},
	{
		"char\\tmABCD\\tmh-b01a.inf",
		"char\\tmABCD\\tmh-b02a.inf",
		"char\\tmABCD\\tmh-b03a.inf"
	}
};

char *szTempMechFaceName[2][3] = {
	{
		"char\\tmABCD\\tmh-a01.inf",
		"char\\tmABCD\\tmh-a02.inf",
		"char\\tmABCD\\tmh-a03.inf"
	},
	{
		"char\\tmABCD\\tmh-a01a.inf",
		"char\\tmABCD\\tmh-a02a.inf",
		"char\\tmABCD\\tmh-a03a.inf"
	}
};

char *szTempArcherFaceName[2][3] = {
	{	"char\\tmABCD\\tfh-D01.inf",
		"char\\tmABCD\\tfh-d02.inf",
		"char\\tmABCD\\tfh-d03.inf"
	},
	{
		"char\\tmABCD\\tfh-D01a.inf",
		"char\\tmABCD\\tfh-d02a.inf",
		"char\\tmABCD\\tfh-d03a.inf"
	}
};

char *szTempPikeFaceName[2][3] = {
	{
		"char\\tmABCD\\tmh-c01.inf",
		"char\\tmABCD\\tmh-c02.inf",
		"char\\tmABCD\\tmh-c03.inf"
	},
	{
		"char\\tmABCD\\tmh-c01a.inf",
		"char\\tmABCD\\tmh-c02a.inf",
		"char\\tmABCD\\tmh-c03a.inf"
	}
};

//char *szTempAssassineFaceName[2][3] = {
//	{
//		"char\\tmABCD\\tfh-e01.inf",
//		"char\\tmABCD\\tfh-e02.inf",
//		"char\\tmABCD\\tfh-e03.inf"
//	},
//	{
//		"char\\tmABCD\\tfh-e01a.inf",
//		"char\\tmABCD\\tfh-e02a.inf",
//		"char\\tmABCD\\tfh-e03a.inf"
//	}
//};


static char *szMorKnightBodyName[] = {
	"char\\tmABCD\\ma001.ini",
	"char\\tmABCD\\ma002.ini",
	"char\\tmABCD\\ma003.ini",
	"char\\tmABCD\\ma004.ini",
	"char\\tmABCD\\ma005.ini",
	"char\\tmABCD\\ma006.ini",
	"char\\tmABCD\\ma007.ini"
};

static char *szMorAtalantaBodyName[] = {
	"char\\tmABCD\\mb001.ini",
	"char\\tmABCD\\mb002.ini",
	"char\\tmABCD\\mb003.ini",
	"char\\tmABCD\\mb004.ini",
	"char\\tmABCD\\mb005.ini",
	"char\\tmABCD\\mb006.ini",
	"char\\tmABCD\\mb007.ini"
};

static char *szMorPriestessBodyName[] = {
	"char\\tmABCD\\mc001.ini",
	"char\\tmABCD\\mc002.ini",
	"char\\tmABCD\\mc003.ini",
	"char\\tmABCD\\mc004.ini",
	"char\\tmABCD\\mc005.ini",
	"char\\tmABCD\\mc006.ini",
	"char\\tmABCD\\mc007.ini"
};

static char *szMorMagicianBodyName[] = {
	"char\\tmABCD\\md001.ini",
	"char\\tmABCD\\md002.ini",
	"char\\tmABCD\\md003.ini",
	"char\\tmABCD\\md004.ini",
	"char\\tmABCD\\md005.ini",
	"char\\tmABCD\\md006.ini",
	"char\\tmABCD\\md007.ini"
};


char *szMorKnightFaceName[2][3] = {
	{
		"char\\tmABCD\\Mmh-A01.inf",
		"char\\tmABCD\\Mmh-A02.inf",
		"char\\tmABCD\\Mmh-A03.inf"
	},
	{

		"char\\tmABCD\\Mmh-A01.inf",
		"char\\tmABCD\\Mmh-A02.inf",
		"char\\tmABCD\\Mmh-A03.inf"
	}
};

char *szMorAtalantaFaceName[2][3] = {
	{
		"char\\tmABCD\\Mfh-B01.inf",
		"char\\tmABCD\\Mfh-B02.inf",
		"char\\tmABCD\\Mfh-B03.inf"
	},
	{
		"char\\tmABCD\\Mfh-B01.inf",
		"char\\tmABCD\\Mfh-B02.inf",
		"char\\tmABCD\\Mfh-B03.inf"
	}
};


char *szMorPriestessFaceName[2][3] = {
	{
		"char\\tmABCD\\Mfh-C01.inf",
		"char\\tmABCD\\Mfh-C02.inf",
		"char\\tmABCD\\Mfh-C03.inf"
	},
	{
		"char\\tmABCD\\Mfh-C01.inf",
		"char\\tmABCD\\Mfh-C02.inf",
		"char\\tmABCD\\Mfh-C03.inf"
	}
};

char *szMorMagicianFaceName[2][3] = {
	{
		"char\\tmABCD\\Mmh-D01.inf",
		"char\\tmABCD\\Mmh-D02.inf",
		"char\\tmABCD\\Mmh-D03.inf"
	},
	{
		"char\\tmABCD\\Mmh-D01.inf",
		"char\\tmABCD\\Mmh-D02.inf",
		"char\\tmABCD\\Mmh-D03.inf"
	}
};



int TempNewCharacterInit[4][6] =
{

	{ 2,  24,  8,  25,  18,  24 },
	{ 1,  28,  6,  21,  17,  27 },
	{ 4,  26,  9,  20,  19,  25 },
	{ 3,  17,  11,  21,  27,  23 }
};

int MorNewCharacterInit[4][6] =
{

	{ 6,  26,  13,  17,  19,  24 },
	{ 5,  23,  15,  19,  19,  23 },
	{ 8,  15,  28,  21,  15,  20 },
	{ 7,  16,  29,  19,  14,  21 }
};

static int TempFaceCount[CHARACTER_JOB_MAX] =
{ 3, 3, 3, 3 };

static int TempFacePos[4][4] =
{
	{ 400 - 64 - 128, 400 - 64, 400 - 64 + 128,   -1 },
	{ 400 - 64 - 128, 400 - 64, 400 - 64 + 128,   -1 },
	{ 400 - 64 - 128, 400 - 64, 400 - 64 + 128, -1 },
	{ 400 - 64 - 128, 400 - 64, 400 - 64 + 128, -1 }
};

HoNewCharInfo	NewCharInfo;

extern smCHAR chrPlayer;
extern smCHAR *chrEachMaster;
extern int MatEachBox;

static int GetSelRectChar(smCHAR *lpChar);


static int GetSelRectJobChar(smCHAR *lpChar);
static int CameraZPos[5] = { fONE * 300, fONE * 300 + fONE * 70, fONE * 300 + fONE * 250, fONE * 300 + fONE * 420, fONE * 300 + fONE * 400 };


HoLogin::HoLogin()
{
	ErrorSelect = ERROR_NONE;
	SelectCurrentState = CHARACTER_SELECT_STATE;
	SelectNextState = CHARACTER_SELECT_STATE;


	UserCharacterCount = 0;
	JobCharacterCount = 0;




	FaceSelectImage = NULL;


	TempscronMarkImage = -1;
	TempscronLogoImage = -1;

	GameMapImage = NULL;


	MoryonMarkImage = -1;
	MoryonLogoImage = -1;
	Init_UseMor();



	Load();

}

HoLogin::~HoLogin()
{
	Close();
}

void HoLogin::Init_UseMor()
{
	menuPos[0].left = 270;
	menuPos[0].right = menuPos[0].left + 128,
		menuPos[0].top = 166,
		menuPos[0].bottom = menuPos[0].top + 128;

	menuPos[1].left = 430;
	menuPos[1].right = menuPos[1].left + 128,
		menuPos[1].top = 166,
		menuPos[1].bottom = menuPos[1].top + 128;
}

int HoLogin::Init()
{
	return TRUE;
}


int HoLogin::Load()
{

#ifdef _LANGUAGE_BRAZIL
	Font = CreateFont(16,
					  0,
					  0,
					  0,
					  FW_NORMAL,
					  FALSE,
					  FALSE,
					  FALSE,
					  ANSI_CHARSET | FS_LATIN1,
					  OUT_DEFAULT_PRECIS,
					  CLIP_DEFAULT_PRECIS,
					  DEFAULT_QUALITY,
					  VARIABLE_PITCH,
					  "Noto Sans");
#endif



	Stage = new smSTAGE3D();


	Stage->VectLight.x = smConfig.MapLightVector.x;
	Stage->VectLight.y = smConfig.MapLightVector.y;
	Stage->VectLight.z = smConfig.MapLightVector.z;

	Stage->Bright = smConfig.MapBright;
	Stage->Contrast = smConfig.MapContrast;

	//Stage = smSTAGE3D_ReadASE("Assets\\GUI\\Opening\\Select\\Stage\\Stage.ASE", smStage);

	Stage = smSTAGE3D_ReadASE("cSelect\\Login.ASE", smStage);

	if(Stage)
	{
		Stage->Head = TRUE;
	}

	ReadTextures();

	if(Stage)
	{
		Stage->smMaterialGroup->CheckMatreialTextureSwap();
	}

	OkButton.Init("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\Bt_select.tga", 128, 32);
	OkButton.InitCrashRect(10, 0, 110, 32);

	BackButton.Init("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\Bt_back.tga", 128, 32);
	BackButton.InitCrashRect(20, 0, 103, 32);

	NewCharButton.Init("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\bt-NewChar.tga", 128, 32);
	NewCharButton.InitCrashRect(10, 0, 110, 32);

	QuitButton.Init("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\Bt_exit.tga", 128, 32);
	QuitButton.InitCrashRect(15, 0, 108, 32);

	DeleteButton.Init("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\Bt_delet.tga", 128, 32);
	DeleteButton.InitCrashRect(10, 0, 108, 32);


	UserCharacterInfoBackImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\UserCharacterInfo.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UserCharacterInfoImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharacterInfo.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);


	TempscronMarkImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mark_T.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronLogoImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T-tempscron.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MoryonMarkImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mark_M.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonLogoImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T-Morion.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	FaceSelectImage = LoadDibSurfaceOffscreen("Assets\\GUI\\Opening\\Select\\UI\\SelectFace.bmp");

	TempFaceImage[0][0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmA01-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[0][0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmA01-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[0][1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmA02-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[0][1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmA02-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[0][2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmA03-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[0][2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmA03-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	TempFaceImage[1][0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmB01-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[1][0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmB01-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[1][1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmB02-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[1][1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmB02-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[1][2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmB03-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[1][2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmB03-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	
	TempFaceImage[2][0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmC01-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[2][0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmC01-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[2][1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmC02-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[2][1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmC02-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[2][2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmC03-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[2][2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TmC03-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	
	TempFaceImage[3][0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfD01-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[3][0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfD01-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[3][1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfD02-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[3][1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfD02-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[3][2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfD03-01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[3][2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfD03-02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	
	TempFaceImage[4][0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfE01-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[4][0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfE01-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[4][1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfE02-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[4][1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfE02-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[4][2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfE03-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempFaceImage[4][2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\TfE03-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	
	MorFaceImage[0][0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MmA01-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[0][0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MmA01-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[0][1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MmA02-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[0][1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MmA02-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[0][2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MmA03-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[0][2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MmA03-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	
	MorFaceImage[1][0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MfB02-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[1][0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MfB02-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[1][1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MfB01-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[1][1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MfB01-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[1][2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MfB03-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[1][2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\MfB03-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	
	MorFaceImage[2][0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mfc01-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[2][0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mfc01-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[2][1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mfc02-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[2][1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mfc02-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[2][2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mfc03-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[2][2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mfc03-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	
	MorFaceImage[3][0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mmd01-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[3][0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mmd01-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[3][1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mmd02-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[3][1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mmd02-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[3][2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mmd03-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[3][2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mmd03-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	
	MorFaceImage[4][0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mme01-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[4][0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mme01-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[4][1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mme02-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[4][1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mme02-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[4][2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mme03-a.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MorFaceImage[4][2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\Moryon\\Mme03-b.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MatEachBox = -1;

	BlackBoxImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\BlackBox.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

	SYSTEMTIME st;
	GetLocalTime(&st);

	Message.Init();
	MessageBox.Init();
	InitMessageBox();

	MainBoxFrameImage1[0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mainbox_L.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage1[1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mainbox_T.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage1[2] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mainbox_R.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage1[3] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mainbox_D.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

	MainBoxFrameImage2[0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mainbox_CN1.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage2[1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mainbox_CN2.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage2[2] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mainbox_CN3.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MainBoxFrameImage2[3] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mainbox_CN4.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

	TitleBoxFrameImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\title-box.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	TitleNameImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\title-txt30.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

	TempscronTextImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T-ex_tscr.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MoryonTextImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T-ex_mrin.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

	RaceTextBoxImage[0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mark_box1.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RaceTextBoxImage[1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\mark_box2.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	
	JobTextBoxImage[0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-box1.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	JobTextBoxImage[1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-box2.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

	TempscronJobImage[0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-meca_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-ft_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-pkm_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[3][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-ac_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[4][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-assa_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	TempscronJobImage[0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-meca.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-ft.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-pkm.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[3][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-ac.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobImage[4][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-assa.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MoryonJobImage[0][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T-cls-knt_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[1][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-atlt_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[2][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-prts_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[3][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-mgc_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[4][0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-sha_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MoryonJobImage[0][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T-cls-knt.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[1][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-atlt.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[2][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-prts.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[3][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-mgc.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobImage[4][1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_cls-sha.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	TempscronJobTextImage[0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_chr-meca.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobTextImage[1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_chr-ft.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobTextImage[2] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_chr-pkm.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobTextImage[3] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_chr-ac.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	TempscronJobTextImage[4] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_chr-assa.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MoryonJobTextImage[0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_chr-knt.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobTextImage[1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_chr-atlt.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobTextImage[2] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_chr-prts.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobTextImage[3] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_chr-mgc.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MoryonJobTextImage[4] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\T_chr-sha.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	FaceBoxBigImage[0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\face_bigbox1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	FaceBoxBigImage[1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\face_bigbox2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	FaceBoxSmallImage[0] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\face_box_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	FaceBoxSmallImage[1] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\face_box.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	FaceBoxSmallImage[2] = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\face_box2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	NewCharacterImage = CreateTextureMaterial("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\New_char.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	ReadTextures();

	return TRUE;
}


void HoLogin::LoadLoadingImage(int level)
{
	GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\1.bmp");
	GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\2.bmp");
	GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\3.bmp");
	GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\4.bmp");
	GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\5.bmp");
	GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\6.bmp");
	GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\7.bmp");
	GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\8.bmp");
}

int	HoLogin::AddUserCharacter(char *chrFile1, char *chrFile2, int jobCode)
{
	for(int index = 0; index < CHARACTER_USER_MAX; index++)
	{
		if(UserCharacter[index].DisplayFlag == FALSE)
		{
			UserCharacter[index].Init();
			UserCharacter[index].lpStage = Stage;

			SetLoadPattern(&UserCharacter[index], chrFile1, chrFile2, 0, 0);
			UserCharacter[index].SetPosi(UserCharacterPos[index][0] * fONE,
										 Stage->GetHeight(UserCharacterPos[index][0] * fONE, UserCharacterPos[index][1] * fONE)
										 , UserCharacterPos[index][1] * fONE, 0, ANGLE_180, 0);
			UserCharacter[index].ActionPattern = 0;


			UserCharacter[index].ChangeMotion(10);

			UserCharacterCount++;
			ReadTextures();

			UserCharacter[index].lpDinaPattern->Pat->smMaterialGroup->CheckMatreialTextureSwap();
			
			if(UserCharacter[index].lpDinaPattern2)
			{
				UserCharacter[index].lpDinaPattern2->Pat->smMaterialGroup->CheckMatreialTextureSwap();
			}
			
			break;
		}
	}


	return TRUE;
}

int HoLogin::AddJobCharacter(char *chrFile1, char *chrFile2, int index)
{
	if(index == -1)
	{
		JobCharacter[JobCharacterCount].Init();
		JobCharacter[JobCharacterCount].lpStage = Stage;
		JobCharacter[JobCharacterCount].smCharInfo.wPlayerKilling[0] = 0;


		SetLoadPattern(&JobCharacter[JobCharacterCount], chrFile1, chrFile2, 0, 0);

		JobCharacter[JobCharacterCount].SetPosi(JobCharacterPos[JobCharacterCount][0] * fONE,
												Stage->GetHeight(JobCharacterPos[JobCharacterCount][0] * fONE, JobCharacterPos[JobCharacterCount][1] * fONE),
												JobCharacterPos[JobCharacterCount][1] * fONE, 0, ANGLE_180, 0);
		JobCharacter[JobCharacterCount].ActionPattern = 0;
		memset(JobCharacter[JobCharacterCount].szChatMessage, 0, sizeof(JobCharacter[JobCharacterCount].szChatMessage));
		memset(JobCharacter[JobCharacterCount].smCharInfo.szName, 0, sizeof(JobCharacter[JobCharacterCount].smCharInfo.szName));

		JobCharacter[JobCharacterCount].ChangeMotion(10);

		JobCharacterCount++;
		ReadTextures();
		JobCharacter[JobCharacterCount - 1].lpDinaPattern->Pat->smMaterialGroup->CheckMatreialTextureSwap();
		JobCharacter[JobCharacterCount - 1].lpDinaPattern2->Pat->smMaterialGroup->CheckMatreialTextureSwap();

		JobCharacter[JobCharacterCount].smCharInfo.Stamina[0] = 100;
		JobCharacter[JobCharacterCount].smCharInfo.Stamina[1] = 100;

	}
	else
	{
		if(index >= 0 && index < CHARACTER_JOB_MAX)
		{
			JobCharacter[index].Init();
			JobCharacter[index].lpStage = Stage;
			JobCharacter[index].smCharInfo.wPlayerKilling[0] = 0;


			SetLoadPattern(&JobCharacter[index], chrFile1, chrFile2, 0, 0);
			JobCharacter[index].SetPosi(JobCharacterPos[index][0] * fONE,
										Stage->GetHeight(JobCharacterPos[index][0] * fONE, JobCharacterPos[index][1] * fONE)
										, JobCharacterPos[index][1] * fONE, 0, ANGLE_180, 0);
			JobCharacter[index].ActionPattern = 0;
			memset(JobCharacter[index].szChatMessage, 0, sizeof(JobCharacter[JobCharacterCount].szChatMessage));
			memset(JobCharacter[index].smCharInfo.szName, 0, sizeof(JobCharacter[JobCharacterCount].smCharInfo.szName));

			ReadTextures();
			JobCharacter[index].lpDinaPattern->Pat->smMaterialGroup->CheckMatreialTextureSwap();
			JobCharacter[index].lpDinaPattern2->Pat->smMaterialGroup->CheckMatreialTextureSwap();

			JobCharacter[index].smCharInfo.Stamina[0] = 100;
			JobCharacter[index].smCharInfo.Stamina[1] = 100;

		}
		else
			return FALSE;
	}


	return TRUE;
}




int HoLogin::GetSelectCharacter(smCHAR *lpChar)
{
	if(lpChar == NULL)
		return FALSE;
	if(lpChar->DisplayFlag == FALSE)
		return FALSE;

	RECT rect;
	POINT	sPos;
	int sez;
	int SelZ = 65536 * 16384;


	if(lpChar)
	{
		int x, y, z;
		int anx, any;

		anx = CaAngle.x;
		any = CaAngle.y;

		any &= ANGCLIP;
		anx &= ANGCLIP;

		GetMoveLocation(0, 0, -TarDist, anx, any, 0);
		x = TarPosi.x + GeoResult_X;
		y = TarPosi.y + GeoResult_Y;
		z = TarPosi.z + GeoResult_Z;
		smRender.SetCameraPosi(x, y, z, anx, any, 0);

		sez = smRender.GetRect2D(lpChar->pX, lpChar->pY + (32 * fONE), lpChar->pZ,
								 24 * fONE, 32 * fONE, &rect, &sPos);


		if(sez > 0 && sez < SelZ &&
		   rect.left<pCursorPos.x && rect.right>pCursorPos.x &&
		   rect.top<pCursorPos.y && rect.bottom>pCursorPos.y)
		{

			if(MouseButton[0])
				return 2;

			return 1;
		}
	}
	return FALSE;
}

int HoLogin::SetChangeJobFace(char *charFile1, char *chrFile2, int jobIndex)
{
	int PosX, PosZ;
	PosX = JobCharacter[jobIndex].pX;
	PosZ = JobCharacter[jobIndex].pZ;
	AddJobCharacter(charFile1, chrFile2, jobIndex);
	JobCharacter[jobIndex].SetPosi(PosX, 10, PosZ, 0, ANGLE_180, 0);
	ReadTextures();
	JobCharacter[jobIndex].lpDinaPattern2->Pat->smMaterialGroup->CheckMatreialTextureSwap();
	return TRUE;
}

int HoLogin::Close()
{

	if(Font != NULL)
		DeleteObject(Font);

	CloseEachPlayer();

	if(Stage)
	{
		delete Stage;
		Stage = NULL;
	}

	for(int index = 0; index < UserCharacterCount; index++)
		UserCharacter[index].Init();

	for(int index = 0; index < JobCharacterCount; index++)
		JobCharacter[index].Init();


	if(GameMapImage)
	{
		GameMapImage->Release();
		GameMapImage = NULL;
	}

	void ClearSelectCha();
	ClearSelectCha();
	return TRUE;
}

int HoLogin::CameraUpDown()
{

	static int	cameraUpDown = 0;
	if(cameraUpDown < 80)
	{
		TarPosi.y += 4;
	}

	if(cameraUpDown >= 80 && cameraUpDown < 160)
	{
		TarPosi.y -= 4;
	}

	cameraUpDown++;
	if(cameraUpDown >= 160)
		cameraUpDown = 0;

	if(SelectCurrentState == CHARACTER_SELECT_STATE)
	{
		if(NewCharacterImageBlendFlag)
		{
			NewCharacterImageBlendCount -= 1.25f;
		}
		else
		{
			NewCharacterImageBlendCount += 1.25f;
		}

		if(NewCharacterImageBlendCount >= 255.f)
		{
			NewCharacterImageBlendFlag = true;
			NewCharacterImageBlendCount = 255.f;

		}


		if(NewCharacterImageBlendCount < 100.f)
		{
			NewCharacterImageBlendFlag = false;
			NewCharacterImageBlendCount = 100.f;
		}

	}

	return TRUE;
}

int HoLogin::Main()
{
	if(ErrorSelect != ERROR_NONE)
	{
		if(StartErrorDelayFlag == FALSE)
		{
			StartErrorDelayFlag = TRUE;
			ErrorDelayCount = 0;
		}
		else
		{
			ErrorDelayCount++;
		}

		if(ErrorDelayCount > 100)
		{
			if(ErrorSelect == ERROR_NONAME_NEWPLAYER)
			{
				hFocusWnd = hTextWnd;
				FocusWndFlag = TRUE;
			#ifdef	_LANGUAGE_JAPANESE		
				SetIME_Mode(1);
			#endif
			}
			ErrorSelect = ERROR_NONE;
			MouseButton[0] = FALSE;
			MouseDblClick = FALSE;

			StartErrorDelayFlag = FALSE;
		}
	}



	void ktj_imsi_clanMENU_Main();
	ktj_imsi_clanMENU_Main();




	int  main_chaC();

	if(main_chaC() && ClanMarkUpdateSuccessFlag == FALSE)
	{
		for(int m = 0; m < 5; m++)
		{
			if(strlen(chacldata[m].ChaName) >= 1)
			{
				for(int n = 0; n < DownUserCharacterCount; n++)
				{
					if(stricmp(chacldata[m].ChaName, DownUserCharacterInfo[n].Name) == 0 &&
					   DownUserCharacterInfo[n].ClanFlag == FALSE)
					{
						strcpy(DownUserCharacterInfo[n].ClanName, chacldata[m].name);
						DownUserCharacterInfo[n].ClanFlag = TRUE;
						if(chacldata[m].hClanMark16)
							DownUserCharacterInfo[n].ClanMark = chacldata[m].hClanMark16;
					}
				}
			}
		}
		ClanMarkUpdateSuccessFlag = TRUE;
	}

	MainEffect();

	CameraUpDown();

	if(SelectCurrentState == START_GAME_STATE && FadeCurrentState == FADE_IN)
	{
		switch(SelectSubState)
		{
			case SUB_SELECT_CHARACTER_USER:
			{
				if(MouseDownCharacterNum != -1)
				{
					memcpy(CharacterName1, DownUserCharacterInfo[MouseDownCharacterNum].BodyName, sizeof(CharacterName1));
					memcpy(CharacterName2, DownUserCharacterInfo[MouseDownCharacterNum].FaceName, sizeof(CharacterName2));
					memset(PlayerName, 0, sizeof(PlayerName));
					memcpy(PlayerName, DownUserCharacterInfo[MouseDownCharacterNum].Name, sizeof(PlayerName));
					CharacterJob = DownUserCharacterInfo[MouseDownCharacterNum].Job;
					GameStartField = DownUserCharacterInfo[MouseDownCharacterNum].StartField;

					CharacterPosX = DownUserCharacterInfo[MouseDownCharacterNum].PosX;
					CharacterPosZ = DownUserCharacterInfo[MouseDownCharacterNum].PosZ;
				}

				SelectSubState = SUB_SELECT_NONE;
				return 3;
				break;
			}

			case SUB_SELECT_CHARACTER_NEW_SERVER:
			{
				SelectSubState = SUB_SELECT_NONE;
				memset(CharacterName1, 0, sizeof(CharacterName1));
				memset(CharacterName2, 0, sizeof(CharacterName2));


				switch(tribeNum)
				{
					case TRIBE_Tempscron:

					if(JobBodySelectNum == 0)
					{
						memcpy(CharacterName1, szTempMechBodyName[0], sizeof(CharacterName1));
						memcpy(CharacterName2, szTempMechFaceName[0][JobFaceSelectNum], sizeof(CharacterName2));
					}
					else if(JobBodySelectNum == 1)
					{
						memcpy(CharacterName1, szTempFighterBodyName[0], sizeof(CharacterName1));
						memcpy(CharacterName2, szTempFighterFaceName[0][JobFaceSelectNum], sizeof(CharacterName2));
					}
					else if(JobBodySelectNum == 2)
					{
						memcpy(CharacterName1, szTempPikeBodyName[0], sizeof(CharacterName1));
						memcpy(CharacterName2, szTempPikeFaceName[0][JobFaceSelectNum], sizeof(CharacterName2));
					}
					else if(JobBodySelectNum == 3)
					{
						memcpy(CharacterName1, szTempArcherBodyName[0], sizeof(CharacterName1));
						memcpy(CharacterName2, szTempArcherFaceName[0][JobFaceSelectNum], sizeof(CharacterName2));
					}
					/*else if(JobBodySelectNum == 4)
					{
						memcpy(CharacterName1, szTempAssassineBodyName[0], sizeof(CharacterName1));
						memcpy(CharacterName2, szTempAssassineFaceName[0][JobFaceSelectNum], sizeof(CharacterName2));
					}*/
					NewCharInfo.JobCode = TempNewCharacterInit[JobBodySelectNum][0];
					NewCharInfo.Strength = TempNewCharacterInit[JobBodySelectNum][1];
					NewCharInfo.Spirit = TempNewCharacterInit[JobBodySelectNum][2];
					NewCharInfo.Talent = TempNewCharacterInit[JobBodySelectNum][3];
					NewCharInfo.Dexterity = TempNewCharacterInit[JobBodySelectNum][4];
					NewCharInfo.Health = TempNewCharacterInit[JobBodySelectNum][5];

					break;

					case TRIBE_Moryon:


					if(JobBodySelectNum == 0)
					{
						memcpy(CharacterName1, szMorKnightBodyName[0], sizeof(CharacterName1));
						memcpy(CharacterName2, szMorKnightFaceName[0][JobFaceSelectNum], sizeof(CharacterName2));
					}
					else if(JobBodySelectNum == 1)
					{
						memcpy(CharacterName1, szMorAtalantaBodyName[0], sizeof(CharacterName1));
						memcpy(CharacterName2, szMorAtalantaFaceName[0][JobFaceSelectNum], sizeof(CharacterName2));
					}
					else if(JobBodySelectNum == 2)
					{
						memcpy(CharacterName1, szMorPriestessBodyName[0], sizeof(CharacterName1));
						memcpy(CharacterName2, szMorPriestessFaceName[0][JobFaceSelectNum], sizeof(CharacterName2));
					}
					else if(JobBodySelectNum == 3)
					{
						memcpy(CharacterName1, szMorMagicianBodyName[0], sizeof(CharacterName1));
						memcpy(CharacterName2, szMorMagicianFaceName[0][JobFaceSelectNum], sizeof(CharacterName2));
					}

					NewCharInfo.JobCode = MorNewCharacterInit[JobBodySelectNum][0];
					NewCharInfo.Strength = MorNewCharacterInit[JobBodySelectNum][1];
					NewCharInfo.Spirit = MorNewCharacterInit[JobBodySelectNum][2];
					NewCharInfo.Talent = MorNewCharacterInit[JobBodySelectNum][3];
					NewCharInfo.Dexterity = MorNewCharacterInit[JobBodySelectNum][4];
					NewCharInfo.Health = MorNewCharacterInit[JobBodySelectNum][5];

					break;
				}
				return 3;
				break;
			}

		}
	}

	if(SelectCurrentState != COMPLETE_SELECT_STATE && SelectCurrentState != START_GAME_STATE)
	{

		for(int index = 0; index < UserCharacterCount; index++)
		{
			if(UserCharacter[index].DisplayFlag)
				UserCharacter[index].Main();
		}

		for(int index = 0; index < JobCharacterCount; index++)
			JobCharacter[index].Main();
	}


	if(SelectCurrentState == SelectNextState)
	{
		if(SelectCurrentState == RACE_SELECT_STATE)
		{

			if(RaceMarkBlendCount < 200)
				RaceMarkBlendCount += 4;
		}
		else if(SelectCurrentState == JOB_SELECT_STATE)
		{


			if(CharacterReturnFlag)
			{
				CharacterStopFlag = FALSE;
				CharacterReturnFlag = FALSE;
				for(int index = 0; index < JobCharacterCount; index++)
				{
					JobCharacter[index].SetPosi(JobCharacterPos[index][0] * fONE,
												Stage->GetHeight(JobCharacterPos[index][0] * fONE, JobCharacterPos[index][1] * fONE)
												, JobCharacterPos[index][1] * fONE, 0, ANGLE_180, 0);
					JobCharacter[index].ChangeMotion(10);
				}
			}

		}
		else if(SelectCurrentState == FACE_SELECT_STATE)
		{
			if(chrEachMaster != NULL)
				chrEachMaster->Flag = 1;
			EachPlayerMain();
		}
		else if(SelectCurrentState == COMPLETE_SELECT_STATE)
		{
			if(FadeCurrentState == FADE_OUT)
			{
				SelectNextState = START_GAME_STATE;
				SetFade();
			}
			if(MouseButton[0] || MouseDblClick || MapBlendCount >= 255)
				SelectNextState = START_GAME_STATE;
		}
	}


	if(FadeCurrentState == FADE_OUT && FadeNextState == FADE_OUT && SelectNextState == RETURN_OPENING_STATE)
	{
		if(smWsockDataServer != NULL)
		{
			DisconnectServerFull();

		}
		InitUserCharacter();
		return 2;
	}


	if(SelectCurrentState != SelectNextState)
	{
		if(SelectCurrentState != COMPLETE_SELECT_STATE && SelectNextState != COMPLETE_SELECT_STATE &&
		   SelectCurrentState != START_GAME_STATE && SelectNextState != START_GAME_STATE)
		{

			if((SelectCurrentState == RACE_SELECT_STATE) && (SelectNextState == JOB_SELECT_STATE))
				RaceMarkScaleSize--;

			MouseDownCharacterNum = -1;
			MouseMoveCharacterNum = -1;
			RaceMarkBlendCount = 0;


			static int step = 1000;
			if(SelectNextState >= 0 && SelectNextState < COMPLETE_SELECT_STATE &&
			   SelectCurrentState >= 0 && SelectCurrentState < COMPLETE_SELECT_STATE)
			{
				if(SelectNextState > SelectCurrentState)
				{

					TarDist += step;
					if(TarDist > CameraZPos[SelectNextState] + 800)
					{
						TarDist = CameraZPos[SelectNextState];
						SelectCurrentState = SelectNextState;
						step = 1000;
					}

					if((CameraZPos[SelectNextState] - CameraZPos[SelectCurrentState]) / 16 * 15 + CameraZPos[SelectCurrentState] < TarDist)
						step = 100;
				}
				else if(SelectNextState < SelectCurrentState)
				{
					TarDist -= step;
					if(TarDist < CameraZPos[SelectNextState] - 800)
					{
						TarDist = CameraZPos[SelectNextState];
						SelectCurrentState = SelectNextState;
						step = 1000;
					}

					if((CameraZPos[SelectCurrentState] - CameraZPos[SelectNextState]) / 16 + CameraZPos[SelectNextState] > TarDist)
						step = 100;
				}
			}
		}

		if(SelectNextState == COMPLETE_SELECT_STATE)
		{
			if(FadeCurrentState == FadeNextState)
			{
				SelectCurrentState = COMPLETE_SELECT_STATE;
			}
		}

		if(SelectNextState == START_GAME_STATE)
		{
			SelectCurrentState = START_GAME_STATE;
		}

		if(SelectCurrentState == FACE_SELECT_STATE && SelectNextState == JOB_SELECT_STATE)
		{
			JobBodySelectNum = -1;
			JobFaceSelectNum = -1;
			memset(UserCharacterNewName, 0, sizeof(UserCharacterNewName));
			SetWindowText(hTextWnd, 0);
			hFocusWnd = NULL;
		}


		if(SelectCurrentState == JOB_SELECT_STATE && SelectNextState == FACE_SELECT_STATE)
		{
			if(JobFaceSelectNum == -1)
			{
				JobFaceSelectNum = 1;
				hFocusWnd = hTextWnd;
				FocusWndFlag = TRUE;
			#ifdef	_LANGUAGE_JAPANESE		
				SetIME_Mode(1);
			#endif

				FaceSelectFirstFlag = FALSE;
			}
		}
	}


	if(SelectNextState == FACE_SELECT_STATE)
	{

		if(JobCharacter[JobBodySelectNum].pZ < -415 * fONE && CharacterStopFlag == FALSE)
		{
			JobCharacter[JobBodySelectNum].MoveFlag = FALSE;
			JobCharacter[JobBodySelectNum].Angle.x = 0;
			JobCharacter[JobBodySelectNum].Angle.y = ANGLE_180;
			JobCharacter[JobBodySelectNum].Angle.z = 0;
			JobCharacter[JobBodySelectNum].ActionPattern = 0;
			JobCharacter[JobBodySelectNum].pZ = -429 * fONE;

			CharacterStopFlag = TRUE;
		}
	}

	return TRUE;

}

int HoLogin::MainDefaultButton()
{
	if(SelectSubState != SUB_SELECT_NONE || ErrorSelect != ERROR_NONE)
		return FALSE;

	if(SelectCurrentState == SelectNextState && SelectCurrentState == CHARACTER_SELECT_STATE)
	{
		if(MouseDownCharacterNum != -1)
		{

			if(DeleteButton.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]))
			{
				SelectSubState = SUB_SELECT_CHARACTER_MANAGE;
				MessageBox.Flag = TRUE;
				PlayWav2(4 - 1);


			}
		}

		int userCount = 0;
		for(int index = 0; index < DownUserCharacterCount; index++)
		{
			if(UserCharacter[index].DisplayFlag)
				userCount++;
		}

		if(userCount == 0)
		{
			if(NewCharButton.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]))
			{
				if(userCount == 0)
				{
					SelectNextState = RACE_SELECT_STATE;
					PlayWav2(5 - 1);
				}
			}
		}
	}


	if(OkButton.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]))
	{
		PlayWav(4 - 1);

		if(SelectCurrentState == CHARACTER_SELECT_STATE)
		{
			if(MouseDownCharacterNum != -1)
			{
				MessageBox.Flag = TRUE;
				SelectSubState = SUB_SELECT_CHARACTER_USER;
			}

			if(MouseDownCharacterNum == -1)
				ErrorSelect = ERROR_SELECT_CHAR;
		}
		else if(SelectCurrentState == RACE_SELECT_STATE)
		{
			ErrorSelect = ERROR_SELECT_RACE;
		}
		else if(SelectCurrentState == JOB_SELECT_STATE)
		{
			if(MouseDownCharacterNum != -1)
			{
				SelectNextState = FACE_SELECT_STATE;
				JobCharacter[JobBodySelectNum].SetTargetPosi(0, (-420 * fONE) >> FLOATNS);
				JobCharacter[JobBodySelectNum].MoveMode = TRUE;

				JobCharacter[JobBodySelectNum].smCharInfo.Weight[0] = 0;
				JobCharacter[JobBodySelectNum].smCharInfo.Weight[1] = 1000;
				JobCharacter[JobBodySelectNum].smCharInfo.Stamina[0] = 1000;

				JobCharacter[JobBodySelectNum].smCharInfo.ArrowPosi[0] = 0;
				JobCharacter[JobBodySelectNum].smCharInfo.ArrowPosi[1] = 0;

				JobCharacter[JobBodySelectNum].Flag = 1;
				OpenEachPlayer(&JobCharacter[JobBodySelectNum]);
				MouseDownCharacterNum = -1;
				CharacterReturnFlag = TRUE;
			}

			if(JobBodySelectNum == -1)
				ErrorSelect = ERROR_SELECT_JOB;

		}
		else if(SelectCurrentState == FACE_SELECT_STATE)
		{

			if(JobBodySelectNum != -1 && JobFaceSelectNum != -1)
			{
				hFocusWnd = NULL;
				if(strlen(UserCharacterNewName) > 0)
				{
					MessageBox.Flag = TRUE;
					SelectSubState = SUB_SELECT_CHARACTER_NEW;
				}
				else
					ErrorSelect = ERROR_NONAME_NEWPLAYER;
			}

			if(JobFaceSelectNum == -1)
			{
				hFocusWnd = NULL;
				ErrorSelect = ERROR_SELECT_FACE;
			}
		}

	}


	if(QuitButton.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]))
	{
		PlayWav(4 - 1);
		SelectSubState = SUB_SELECT_BACK;
	}

	if(BackButton.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]) && SelectCurrentState != CHARACTER_SELECT_STATE)
	{
		PlayWav(7 - 1);
		SelectNextState = SelectCurrentState - 1;
	}

	return TRUE;
}

int HoLogin::InitUserCharacter()
{
	for(int index = 0; index < CHARACTER_USER_MAX; index++)
	{
		if(UserCharacter[index].DisplayFlag != FALSE)
			UserCharacter[index].Init();
	}
	UserCharacterCount = 0;

	return TRUE;
}

int HoLogin::DrawJobCharacter(int x, int y, int z, int ax, int ay, int az)
{
	return TRUE;
}

int HoLogin::DrawUserCharacter(int x, int y, int z, int ax, int ay, int az){
	return TRUE;
}

int HoLogin::DrawTitle(int state){
	return TRUE;
}

int HoLogin::DrawGameFrame(){
	return TRUE;
}

int HoLogin::DrawLight(){
	return TRUE;
}

int HoLogin::DrawMap(int alpha)
{

	return TRUE;
}

int HoLogin::DrawCharacterInfo()
{
	return TRUE;
}

int HoLogin::DrawSelectSubState()
{
	if(SelectNextState == COMPLETE_SELECT_STATE || SelectNextState == START_GAME_STATE)
		return FALSE;

	int flag = 0;
	switch(SelectSubState)
	{
		case SUB_SELECT_CHARACTER_MANAGE:
		{
			flag = MessageBox.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]);
			if(flag == 1)
			{
				PlayWav2(4 - 1);

				int isDELETE_character(char *charName);
				int chk = isDELETE_character(DownUserCharacterInfo[MouseDownCharacterNum].Name);

				if(chk == 102 || chk == 1)
				{
					PlayWav2(6 - 1);
					UserCharacter[MouseDownCharacterNum].Init();
					UserCharacterCount--;


					if(smWsockDataServer)
					{
						TransUserCommand(OpCode::OPCODE_DELRECORDDATA, UserAccount, DownUserCharacterInfo[MouseDownCharacterNum].Name);
					}
					MouseDownCharacterNum = -1;
					SelectSubState = SUB_SELECT_NONE;
				}
				else if(chk == 101 || chk == 100)
				{
					ErrorSelect = ERROR_DELETE_CLAN_MEMBER;
					SelectSubState = SUB_SELECT_NONE;
				}
				else if(chk == 103)
				{
					ErrorSelect = ERROR_CLAN_SERVER_NONE;
					SelectSubState = SUB_SELECT_NONE;
				}
				else
				{
					ErrorSelect = ERROR_CLAN_SERVER_NONE;
					SelectSubState = SUB_SELECT_NONE;
				}

			}
			else if(flag == 2)
			{
				PlayWav2(4 - 1);
				SelectSubState = SUB_SELECT_NONE;
			}

			break;
		}

		case SUB_SELECT_CHARACTER_USER:
		{
			flag = MessageBox.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]);
			if(flag == 1 || VRKeyBuff[VK_RETURN])
			{
				PlayWav2(12 - 1);
				SelectNextState = COMPLETE_SELECT_STATE;
				MessageBox.Flag = FALSE;

				LoadLoadingImage(DownUserCharacterInfo[MouseDownCharacterNum].Level);
				SetFade();
			}
			else if(flag == 2)
			{
				PlayWav2(4 - 1);
				SelectSubState = SUB_SELECT_NONE;
				MessageBox.Flag = FALSE;
			}
			break;
		}

		case SUB_SELECT_CHARACTER_NEW:
		{
			flag = MessageBox.Main(pCursorPos.x, pCursorPos.y, MouseButton[0]);
			if(flag == 1 || VRKeyBuff[VK_RETURN])
			{
				PlayWav2(12 - 1);
				ServerReturn = NULL;
				TransUserCommand(OpCode::OPCODE_INSRECORDDATA, UserAccount, UserCharacterNewName);
				SelectSubState = SUB_SELECT_CHARACTER_NEW_SERVER;
				LoadLoadingImage(0);
			}
			else if(flag == 2)
			{
				PlayWav2(4 - 1);
				SelectSubState = SUB_SELECT_NONE;
				hFocusWnd = hTextWnd;
				FocusWndFlag = TRUE;
			#ifdef	_LANGUAGE_JAPANESE		
				SetIME_Mode(1);
			#endif
			}
			break;
		}

		case SUB_SELECT_CHARACTER_NEW_SERVER:
		{
			if(ServerReturn != NULL)
			{
				if(ServerReturn->WParam == 1)
				{
					SelectNextState = COMPLETE_SELECT_STATE;
					SetFade();
					memset(PlayerName, 0, sizeof(PlayerName));
					memcpy(PlayerName, UserCharacterNewName, sizeof(PlayerName));
				}
				else
				{
					memset(UserCharacterNewName, 0, sizeof(UserCharacterNewName));
					ErrorSelect = ERROR_EXHIST_NEWPLAYER;
					SelectSubState = SUB_SELECT_NONE;
				}
			}
			break;
		}

		case SUB_SELECT_BACK:
		{

			SetFade();
			SelectSubState = SUB_SELECT_NONE;
			SelectNextState = RETURN_OPENING_STATE;
			break;
		}
	}

	return TRUE;
}

int HoLogin::KeyFilter(){
	return TRUE;
}

int HoLogin::Draw(){
	return TRUE;
}

int HoLogin::DrawFade(){
	return TRUE;
}

int HoLogin::MainFade()
{

	if(FadeCurrentState != FadeNextState)
	{
		if(FadeNextState == FADE_IN)
			MainFadeIn();
		else
			MainFadeOut();
	}

	return TRUE;
}

int HoLogin::MainFadeIn()
{

	if(BlendValue > 0)
	{
		BlendValue -= 6;
		if(SelectCurrentState != COMPLETE_SELECT_STATE &&
		   SelectCurrentState != START_GAME_STATE)
		{
			LoginVolume += 10;
			if(LoginVolume > 350)
				LoginVolume = 350;
		}
	}

	if(BlendValue <= 0)
	{
		BlendValue = 0;
		FadeCurrentState = FADE_IN;
		FadeNextState = FADE_IN;
	}
	return TRUE;
}

int HoLogin::MainFadeOut()
{
	if(BlendValue < 255)
	{
		BlendValue += 8;

		if(SelectCurrentState != COMPLETE_SELECT_STATE &&
		   SelectCurrentState != START_GAME_STATE)
		{
			LoginVolume -= 10;
			if(LoginVolume < 0)
				LoginVolume = 0;
		}
	}

	if(BlendValue >= 255)
	{
		BlendValue = 255;
		LoginVolume = 0;
		FadeCurrentState = FADE_OUT;
		FadeNextState = FADE_OUT;
	}
	return TRUE;
}

void HoLogin::SetFade()
{


	if(FadeCurrentState == FADE_OUT)
	{
		FadeNextState = FADE_IN;
		BlendValue = 255;
		LoginVolume = 0;
	}
	else
	{
		FadeNextState = FADE_OUT;
		BlendValue = 0;
		LoginVolume = 350;
	}
}

int HoLogin::ReLoad()
{
	if(GameMapImage)
	{
		GameMapImage->Release();
		GameMapImage = NULL;
		GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\1.bmp");
		GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\2.bmp");
		GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\3.bmp");
		GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\4.bmp");
		GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\5.bmp");
		GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\6.bmp");
		GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\7.bmp");
		GameMapImage = LoadDibSurfaceOffscreen("game\\GUI\\Opening\\Loading\\8.bmp");
	}

	return TRUE;
}

void HoLogin::resize()
{

}

int GetSelRectChar(smCHAR *lpChar)
{
	RECT rect;
	POINT	sPos;
	int sez;
	int SelZ = 65536 * 16384;

	if(lpChar)
	{



		sez = smRender.GetRect2D(lpChar->pX, lpChar->pY + (32 * fONE), lpChar->pZ,
								 24 * fONE, 32 * fONE, &rect, &sPos);


		if(sez > 0 && sez < SelZ &&
		   rect.left<pCursorPos.x && rect.right>pCursorPos.x &&
		   rect.top<pCursorPos.y && rect.bottom>pCursorPos.y)
		{

			if(MouseButton[0])
				return 2;


			return 1;

		}
	}

	return FALSE;
}

int GetSelRectJobChar(smCHAR *lpChar)
{

	RECT rect;
	POINT	sPos;
	int sez;
	int SelZ = 65536 * 16384;

	if(lpChar)
	{

		sez = smRender.GetRect2D(lpChar->pX, lpChar->pY + (32 * fONE), lpChar->pZ,
								 24 * fONE, 32 * fONE, &rect, &sPos);
		if(sez > 0 && sez < SelZ &&
		   rect.left<pCursorPos.x && rect.right>pCursorPos.x &&
		   rect.top<pCursorPos.y && rect.bottom>pCursorPos.y)
		{

			if(MouseButton[0])
				return 2;

			return 1;

		}
	}

	return FALSE;
}