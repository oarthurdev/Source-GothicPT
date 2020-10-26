#pragma once

#include "smType.h"

#define SWAPTEXTURE_MAX		64




extern int		g_IsReadTextures;

extern int		g_DibLastReadWidth;
extern int		g_DibLastReadHeight;




#define		MIPMAP_FILELIST				5
#define		SQUARE_MODE					1
#define		NOSQUARE_MODE				2

extern int MipMapModeCreate;
extern int TextureSwapMode;




struct smSWAPTEXTURE
{

	int		UsedTime;
	int		SwapState;

	DRZTEXTURE2 lpD3DTexture;
	DIRECTDRAWSURFACE lpDDSurface;

	smTEXTUREHANDLE *smTextureMaster;
};


class smTEXTURE
{
public:



	DWORD			TexSpeedSum[MAX_TEXTURE];


	smTEXTUREHANDLE Texture[MAX_TEXTURE];
	DIRECTDRAWSURFACE *lpLastTextureSurface;
	DRZTEXTURE2 *lpLastTexture;

	CRITICAL_SECTION	cTextureSection;


	smSWAPTEXTURE		SwapTexture[SWAPTEXTURE_MAX];
	int					SwapCount;

	int LastTextureCnt;
	int TextureCnt;


	smTEXTURE();
	~smTEXTURE();

	void Init();
	int	 Remove();




	int Find(DWORD dwCode, char *Name);


	smTEXTUREHANDLE *Add(char *name, char *nameA = 0);





	int Delete(smTEXTUREHANDLE *lpTex);

	int DeleteSwapTexture(int TexNum);

	int SetLargeTexture(smTEXTUREHANDLE *TexHandle);


	int ReadTexture();


	int Restore();

};

class smMATERIAL_GROUP
{
	DWORD	Head;
public:
	smMATERIAL *smMaterial;
	DWORD MaterialCount;

	int ReformTexture;

	int MaxMaterial;

	int LastSearchMaterial;
	char szLastSearchName[64];

	smMATERIAL_GROUP();
	smMATERIAL_GROUP(int MaterialMax);
	~smMATERIAL_GROUP();


	void Init(int MaterialMax);

	int Close();


	int GetSaveSize();

	int SaveFile(HANDLE hFile);

	int LoadFile(HANDLE hFile);


	int DeleteUnuseMaterial();

	int AddMaterial(ASE_MATERIAL *aseMaterial, char *szScript = 0);

	int CreateTextureMaterial(char *szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD TexSwap, DWORD BlendType);

	int	AddTexture(int MatNum, char *szBitmap, char *szOpacity = 0);


	int ReSwapMaterial(smMATERIAL *lpMaterial);

	int CheckMatreialTextureSwap();

	int IncTextureFrame();

	int CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode);

	int ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode);

	int SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame);

	smMATERIAL *FindMaterialFromTextureName(char *szName);

	smMATERIAL *FindNextMaterialFromTextureName();




	int ReadTextures(int MipMap = 0);


};



#define MATRIAL_MAX			5000


extern smMATERIAL *smMaterial;
extern smMATERIAL_GROUP	*smMaterialGroup;

extern smTEXTURE smTexture;



extern DWORD	VramTotal;



int InitMaterial();

int CloseMaterial();


int AddMaterial(ASE_MATERIAL *aseMaterial);

int DeleteUnuseMaterial();

int CreateTextureMaterial(char* szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD TexSwap, DWORD BlendType);

int	AddTexture(int MatNum, char *szBitmap, char *szOpacity = 0);

int CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode = TRUE);

int ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode = TRUE);

int SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame);


int CheckMatreialTextureSwap();

int ReSwapMaterial(smMATERIAL *lpMaterial);

extern int MaterialFrame;

int IncTextureFrame();


int SetTextureSwapMode(int mode);


int smSetTextureLevel(int Level);



smMATERIAL *FindMaterialFromTextureName(char *szName);

smMATERIAL *FindNextMaterialFromTextureName();







int InitTexture();

int CloseTexture();


int ReadTextures();

int RestoreTextures();

void ReleaseTextureAll();
int PopReleaseTexture();


void smLeaveTextureCriticalSection();

void smEnterTextureCriticalSection();


DIRECTDRAWSURFACE *GetLastTextureSurface();
DRZTEXTURE2 *GetLastTexture();


BYTE *LoadDib(char *Filename);

int DrawSurfaceFromDib(DIRECTDRAWSURFACE lpDDSurface, BYTE *lpDib);


DIRECTDRAWSURFACE LoadDibSurface(char *Filename, int SysMem = FALSE);

DIRECTDRAWSURFACE LoadDibSurfaceAlpha(char *Filename, char *FileAlpha, int SysMem = FALSE);




int smCreateTexture(smTEXTUREHANDLE *lpTexHandle, int MipMap = 0);


DIRECTDRAWSURFACE LoadDibSurfaceOffscreen(char *Filename);



int LoadDibTextureNum(char *Filename);


DRZTEXTURE2 GetTextureHandle(int num);
DRZTEXTURE2 GetTextureChildHandle(int num);





int LoadDibMapTexture(char *Filename, int tSize);
int RemoveMapTexture();
int SetMapImage(int x, int y);

int DrawAnimBG(DIRECTDRAWSURFACE lpDDSSrc, int frame);
int LoadAnimBG();
int CloseAnimBG();
int ClearBG(DIRECTDRAWSURFACE lpDDSSrc, DWORD color);




int DisplayError(HDC hdc, int x, int y);
int AddErrorList(char *szErrMsg);


