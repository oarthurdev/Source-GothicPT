#include "smd3d.h"
#include <io.h>



int g_IsReadTextures = 1;

BYTE g_DibImageDateBuff[(1024 * 768) * 4];
int g_DibLastReadWidth;
int g_DibLastReadHeight;
int g_TgaLastBitCnt;
int g_TgaLastSwapHeight;

int new_smCreateTexture(smTEXTUREHANDLE *lpTexHandle, int MipMap = 0);

int new_LoadDib(char *Filename);
int new_LoadTga(char *Filename);
int New_DrawSurfaceFromTga(LPDIRECTDRAWSURFACE4 lpDDSurface);

LPDIRECTDRAWSURFACE4 new_LoadBmpCreateTexSurface(char *Filename, int MipMap, int &rTexHalf);
LPDIRECTDRAWSURFACE4 new_LoadTgaCreateTexSurface(char *Filename, int MipMap, int &rTexHalf);
LPDIRECTDRAWSURFACE4 new_LoadBmpSurfaceOffscreen(char *Filename);




DDPIXELFORMAT ddTextureFormat;

DDPIXELFORMAT ddDefaultTextureFormat;

int GetPixelFormatAlphaTexture();

#define ERROR_LIST_MAX 32
#define ERROR_LIST_MASK (ERROR_LIST_MAX - 1)

char szErrorList[ERROR_LIST_MAX][200];
int ErrorListCnt = 0;


int AddErrorList(char *szErrMsg)
{
	int cnt = ErrorListCnt & ERROR_LIST_MASK;

	strncpy(szErrorList[cnt], szErrMsg, sizeof(szErrorList[cnt]));

	ErrorListCnt++;

	return ErrorListCnt;
}

int DisplayError(HDC hdc, int x, int y)
{
	int dy = y;

	for(int cnt = ErrorListCnt - ERROR_LIST_MASK; cnt < ErrorListCnt; cnt++)
	{
		if(cnt >= 0)
		{
			int mcnt = cnt & ERROR_LIST_MASK;
			int len = lstrlen(szErrorList[mcnt]);

			dy += 14;
		}
	}

	return TRUE;
}





DWORD VramTotal = 0;




#define MAX_MAP_BLINK_COLOR_TIME 8

const char *szBlinkTimeScript[MAX_MAP_BLINK_COLOR_TIME] =
{
	"BLINK_TIME1:",
	"BLINK_TIME2:",
	"BLINK_TIME3:",
	"BLINK_TIME4:",
	"BLINK_TIME5:",
	"BLINK_TIME6:",
	"BLINK_TIME7:",
	"BLINK_TIME8:",
};

const DWORD dwBlinkTimeCode[MAX_MAP_BLINK_COLOR_TIME] =
{
	9, 10, 11, 12, 13, 14, 15, 16,
};





int MipMapModeCreate;
int TextureSwapMode = TRUE;
static int TexturHalfSize = FALSE;




static char MipMapFileListBuff[MIPMAP_FILELIST][16] = { "", "_mm1", "_mm2", "_mm3", "_mm4", };

static int MipMapCount = 0;
static char MipMapFileBuff[MIPMAP_FILELIST][126] = { 0, };
static int MipMapCountA = 0;
static char MipMapFileABuff[MIPMAP_FILELIST][126] = { 0, };
static char FileTypeBuff[16] = { 0, };



int MaterialFrame = 0;


int SetTextureSwapMode(int mode)
{
	int OldValue = TextureSwapMode;

	TextureSwapMode = mode;

	return OldValue;
}


int smSetTextureLevel(int Level)
{
	switch(Level)
	{
	case 0:

		TextureSwapMode = FALSE;
		TexturHalfSize = 0;
		break;

	case 1:

		TextureSwapMode = TRUE;
		TexturHalfSize = 0;
		break;

	case 2:

		TextureSwapMode = TRUE;
		TexturHalfSize = 1;
		break;

	case 3:

		TextureSwapMode = TRUE;
		TexturHalfSize = 2;
		break;
	}

	return TRUE;
}



smTEXTURE::smTEXTURE()
{
	Init();
}

smTEXTURE::~smTEXTURE()
{

}

void smTEXTURE::Init()
{


	ZeroMemory(TexSpeedSum, sizeof(TexSpeedSum));


	ZeroMemory(Texture, sizeof(smTEXTUREHANDLE) * MAX_TEXTURE);
	ZeroMemory(SwapTexture, sizeof(smSWAPTEXTURE) * SWAPTEXTURE_MAX);
	TextureCnt = 0;
	SwapCount = 0;


	InitializeCriticalSection(&cTextureSection);

}

int smTEXTURE::Remove()
{

	EnterCriticalSection(&cTextureSection);

	for(int cnt = 0; cnt < SWAPTEXTURE_MAX; cnt++)
	{
		if(SwapTexture[cnt].SwapState == TRUE)
		{
			DeleteSwapTexture(cnt);
		}
	}

	for(int cnt = 0; cnt < MAX_TEXTURE; cnt++)
	{
		if(Texture[cnt].UseCounter > 0)
		{

			if(Texture[cnt].lpD3DTexture)
				Texture[cnt].lpD3DTexture->Release();

			if(Texture[cnt].lpDDSurface)
				Texture[cnt].lpDDSurface->Release();

			if(Texture[cnt].lpDDSSysMemory)
				Texture[cnt].lpDDSSysMemory->Release();

			Texture[cnt].UseCounter = 0;
		}
	}

	LeaveCriticalSection(&cTextureSection);


	DeleteCriticalSection(&cTextureSection);

	return TRUE;
}





int smTEXTURE::Find(DWORD dwCode, char *Name)
{
	for(int cnt = 0; cnt < MAX_TEXTURE; cnt++)
	{
		if(TexSpeedSum[cnt] == dwCode)
		{
			if(Texture[cnt].UseCounter && _stricmp(Texture[cnt].Name, Name) == 0)
				return cnt;
		}
	}

	return -1;
}



smTEXTUREHANDLE *smTEXTURE::Add(char *name, char *nameA)
{
	int cnt = 0;

	extern DWORD GetSpeedSum(const char *szName);

	DWORD dwCode = GetSpeedSum(name);
	int TexNum = Find(dwCode, name);

	if(TexNum >= 0)
	{
		LastTextureCnt = TexNum;
		Texture[TexNum].UseCounter++;
		return &Texture[TexNum];
	}

	for(cnt = 0; cnt < MAX_TEXTURE; cnt++)
	{
		if(Texture[cnt].UseCounter == 0)
			break;
	}

	if(cnt == MAX_TEXTURE)
		return NULL;

	TextureCnt = cnt;

	lpLastTextureSurface = &Texture[TextureCnt].lpDDSurface;
	lpLastTexture = &Texture[TextureCnt].lpD3DTexture;


	Texture[TextureCnt].lpDDSurface = NULL;
	Texture[TextureCnt].lpD3DTexture = NULL;

	if(strlen(name) > sizeof(Texture[TextureCnt].Name))
	{
		//LOG(LOG_ERROR, "[smTEXTURE::Add] - [Buffer Overflow][Capacity: %d] - [required: %d] Buffer: (%s)", sizeof(Texture[TextureCnt].Name), strlen(name), name);
	}


	strcpy_s(Texture[TextureCnt].Name, name);

	if(nameA)
	{
		strcpy_s(Texture[TextureCnt].NameA, nameA);
	}
	else
	{
		Texture[TextureCnt].NameA[0] = 0;
	}

	Texture[TextureCnt].TexSwapMode = TextureSwapMode;
	Texture[TextureCnt].UseCounter++;
	Texture[TextureCnt].lpD3DTextureLarge = NULL;



	TexSpeedSum[TextureCnt] = dwCode;


	return &Texture[TextureCnt];
}


int smTEXTURE::Delete(smTEXTUREHANDLE *lpTex)
{
	if(lpTex->UseCounter <= 0)
		return FALSE;

	lpTex->UseCounter--;

	if(lpTex->UseCounter <= 0)
	{

		if(lpTex->lpD3DTextureLarge)
		{
			for(int cnt = 0; cnt < SWAPTEXTURE_MAX; cnt++)
			{
				if(SwapTexture[cnt].SwapState && SwapTexture[cnt].smTextureMaster == lpTex)
				{
					DeleteSwapTexture(cnt);
					break;
				}
			}
		}

		if(lpTex->lpDDSurface)
			lpTex->lpDDSurface->Release();

		if(lpTex->lpD3DTexture)
			lpTex->lpD3DTexture->Release();

		if(lpTex->lpDDSSysMemory)
			lpTex->lpDDSSysMemory->Release();

		lpTex->lpD3DTexture = 0;
		lpTex->lpDDSurface = 0;
		lpTex->lpDDSSysMemory = 0;

		VramTotal -= lpTex->Width * lpTex->Height * 2;

	}

	return lpTex->UseCounter;
}





int smTEXTURE::DeleteSwapTexture(int TexNum)
{

	EnterCriticalSection(&cTextureSection);

	if(SwapTexture[TexNum].lpDDSurface)
	{
		SwapTexture[TexNum].lpDDSurface->Release();
		SwapTexture[TexNum].lpDDSurface = 0;
	}

	if(SwapTexture[TexNum].lpD3DTexture)
	{
		SwapTexture[TexNum].lpD3DTexture->Release();
		SwapTexture[TexNum].lpD3DTexture = 0;
	}

	SwapTexture[TexNum].smTextureMaster->lpD3DTextureLarge = NULL;
	SwapTexture[TexNum].SwapState = FALSE;


	VramTotal -= SwapTexture[TexNum].smTextureMaster->Width *
		SwapTexture[TexNum].smTextureMaster->Height * 2;


	LeaveCriticalSection(&cTextureSection);

	return TRUE;
}


int smTEXTURE::SetLargeTexture(smTEXTUREHANDLE *TexHandle)
{
	int cnt = 0;
	int OldTex = 0;
	int OldTexNum = 0;


	if(TexHandle->lpDDSSysMemory == NULL)
		return FALSE;


	for(cnt = 0; cnt < SWAPTEXTURE_MAX; cnt++)
	{
		if(SwapTexture[cnt].SwapState == TRUE && SwapTexture[cnt].smTextureMaster == TexHandle)
		{
			SwapTexture[cnt].UsedTime = SwapCount;
			return TRUE;
		}
	}


	for(cnt = 0; cnt < SWAPTEXTURE_MAX; cnt++)
	{
		if(SwapTexture[cnt].SwapState == NULL)
			break;
	}

	if(cnt == SWAPTEXTURE_MAX)
	{


		OldTex = SwapTexture[cnt].UsedTime;

		for(cnt = 0; cnt < SWAPTEXTURE_MAX; cnt++)
		{
			if(SwapTexture[cnt].UsedTime < OldTex)
			{
				OldTex = SwapTexture[cnt].UsedTime;
				OldTexNum = cnt;
			}
		}


		if(OldTex == SwapCount)
			return FALSE;


		DeleteSwapTexture(OldTexNum);
		cnt = OldTexNum;
	}


	EnterCriticalSection(&cTextureSection);


	LPDIRECT3DTEXTURE2 lpD3DTexture;
	LPDIRECTDRAWSURFACE4 lpDDSurface;
	DDSURFACEDESC2 ddsd;
	RECT ddRect;
	int hresult;


	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwWidth = TexHandle->Width;
	ddsd.dwHeight = TexHandle->Height;
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;


	if(TexHandle->NameA[0])
	{
		memcpy(&ddsd.ddpfPixelFormat, &ddTextureFormat, sizeof(DDPIXELFORMAT));
	}
	else
	{
		memcpy(&ddsd.ddpfPixelFormat, &ddDefaultTextureFormat, sizeof(DDPIXELFORMAT));
	}


	if(renderDevice.GetDeviceDesc_IsHardware())
	{

		ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
		ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
	else
		ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;

	renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);

	if(lpDDSurface)
	{
		hresult = lpDDSurface->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&lpD3DTexture);
		if(hresult != D3D_OK)
		{
			lpDDSurface->Release();

			LeaveCriticalSection(&cTextureSection);
			return FALSE;
		}
	}
	else
	{
		LeaveCriticalSection(&cTextureSection);
		return FALSE;
	}

	ddRect.left = 0;
	ddRect.right = TexHandle->Width;
	ddRect.top = 0;
	ddRect.bottom = TexHandle->Height;

	renderDevice.BltFast(lpDDSurface, 0, 0, TexHandle->lpDDSSysMemory, &ddRect, DDBLTFAST_WAIT);
	lpDDSurface->BltFast(0, 0, TexHandle->lpDDSSysMemory, &ddRect, DDBLTFAST_WAIT);


	TexHandle->lpD3DTextureLarge = lpD3DTexture;
	SwapTexture[cnt].lpD3DTexture = lpD3DTexture;
	SwapTexture[cnt].lpDDSurface = lpDDSurface;
	SwapTexture[cnt].smTextureMaster = TexHandle;
	SwapTexture[cnt].UsedTime = SwapCount;
	SwapTexture[cnt].SwapState = TRUE;


	VramTotal += TexHandle->Width * TexHandle->Height * 2;


	LeaveCriticalSection(&cTextureSection);


	return TRUE;
}


int smTEXTURE::ReadTexture()
{


	if(g_IsReadTextures == 0)
	{
		return 0;
	}


	char szErrMsg[128];
	int ReadCount = 0;

	for(int cnt = 0; cnt < MAX_TEXTURE; cnt++)
	{
		if(Texture[cnt].UseCounter && !Texture[cnt].lpD3DTexture)
		{

			EnterCriticalSection(&cTextureSection);

			int Result = new_smCreateTexture(&Texture[cnt]);


			if(Result <= 0)
			{
				switch(Result)
				{
				case 0:
					wsprintf(szErrMsg, "TEX_D3D 오류 [%s]", Texture[cnt].Name);
					break;
				case -1:
					wsprintf(szErrMsg, "TEX_FILE 오류 [%s]", Texture[cnt].Name);
					break;
				case -2:
					wsprintf(szErrMsg, "TEX_ALPHA 오류 [%s]", Texture[cnt].Name);
					break;
				}

				AddErrorList(szErrMsg);
			}

			ReadCount++;

			LeaveCriticalSection(&cTextureSection);

			if((ReadCount & 0x7) == 0)
				smPlayWindowMessage();
		}
	}

	return TRUE;
}

int smTEXTURE::Restore()
{
	for(int cnt = 0; cnt < SWAPTEXTURE_MAX; cnt++)
	{
		if(SwapTexture[cnt].SwapState == TRUE)
		{
			DeleteSwapTexture(cnt);
		}
	}


	EnterCriticalSection(&cTextureSection);

	for(int cnt = 0; cnt < MAX_TEXTURE; cnt++)
	{
		if(Texture[cnt].UseCounter && Texture[cnt].lpD3DTexture)
		{




			if(Texture[cnt].lpD3DTexture)
				Texture[cnt].lpD3DTexture->Release();

			if(Texture[cnt].lpDDSurface)
				Texture[cnt].lpDDSurface->Release();

			if(Texture[cnt].lpDDSSysMemory)
				Texture[cnt].lpDDSSysMemory->Release();

			Texture[cnt].lpD3DTexture = 0;
			Texture[cnt].lpDDSurface = 0;
			Texture[cnt].lpDDSSysMemory = 0;

		}
	}
	LeaveCriticalSection(&cTextureSection);

	ReadTexture();

	return TRUE;
}


smTEXTURE smTexture;




smMATERIAL_GROUP::smMATERIAL_GROUP()
{
	smMaterial = nullptr;
	MaterialCount = 0;

	ReformTexture = 0;

	MaxMaterial = 0;

	LastSearchMaterial = 0;
	ZeroMemory(szLastSearchName, sizeof(szLastSearchName));
}

smMATERIAL_GROUP::smMATERIAL_GROUP(int MaterialMax)
{
	Init(MaterialMax);
}

smMATERIAL_GROUP::~smMATERIAL_GROUP()
{
	Close();
}

void smMATERIAL_GROUP::Init(int MaterialMax)
{
	Head = 0;
	MaterialCount = 0;
	MaxMaterial = MaterialMax;
	ReformTexture = 0;

	this->smMaterial = new smMATERIAL[MaterialMax]();
	//ZeroMemory(this->smMaterial, sizeof(smMATERIAL) * MaterialMax);
}

int smMATERIAL_GROUP::Close()
{
	for(DWORD cnt = 0; cnt < MaterialCount; cnt++)
	{
		if(smMaterial[cnt].InUse)
		{
			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				if(smMaterial[cnt].smTexture[tcnt])
					smTexture.Delete(smMaterial[cnt].smTexture[tcnt]);
			}

			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				if(smMaterial[cnt].smAnimTexture[tcnt])
					smTexture.Delete(smMaterial[cnt].smAnimTexture[tcnt]);
			}
		}
	}

	if(smMaterial)
	{
		delete[] smMaterial;
		smMaterial = nullptr;
	}

	return TRUE;
}

#define TEXFILENAME_SIZE 64

int smMATERIAL_GROUP::GetSaveSize()
{

	int size = sizeof(smMATERIAL_GROUP);

	for(DWORD cnt = 0; cnt < MaterialCount; cnt++)
	{
		size += sizeof(smMATERIAL);
		if(smMaterial[cnt].InUse)
		{
			size += sizeof(int);

			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				int len = lstrlen(smMaterial[cnt].smTexture[tcnt]->Name) + 1;
				int alen = lstrlen(smMaterial[cnt].smTexture[tcnt]->NameA) + 1;

				size += len;
				size += alen;
			}

			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				int len = lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->Name) + 1;
				int alen = lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->NameA) + 1;

				size += len;
				size += alen;
			}

		}
	}
	return size;
}

int smMATERIAL_GROUP::SaveFile(HANDLE hFile)
{
	DWORD dwAcess = 0;

	int size = WriteFile(hFile, &Head, sizeof(smMATERIAL_GROUP), &dwAcess, NULL);

	for(DWORD cnt = 0; cnt < MaterialCount; cnt++)
	{
		size += WriteFile(hFile, &smMaterial[cnt], sizeof(smMATERIAL), &dwAcess, NULL);

		if(smMaterial[cnt].InUse)
		{
			int len = 0;

			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				len += lstrlen(smMaterial[cnt].smTexture[tcnt]->Name) + 1;
				len += lstrlen(smMaterial[cnt].smTexture[tcnt]->NameA) + 1;
			}
			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				len += lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->Name) + 1;
				len += lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->NameA) + 1;
			}

			size += WriteFile(hFile, &len, sizeof(int), &dwAcess, NULL);

			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				len = lstrlen(smMaterial[cnt].smTexture[tcnt]->Name) + 1;
				size += WriteFile(hFile, smMaterial[cnt].smTexture[tcnt]->Name, len, &dwAcess, NULL);
				len = lstrlen(smMaterial[cnt].smTexture[tcnt]->NameA) + 1;
				size += WriteFile(hFile, smMaterial[cnt].smTexture[tcnt]->NameA, len, &dwAcess, NULL);
			}

			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				len = lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->Name) + 1;
				size += WriteFile(hFile, smMaterial[cnt].smAnimTexture[tcnt]->Name, len, &dwAcess, NULL);
				len = lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->NameA) + 1;
				size += WriteFile(hFile, smMaterial[cnt].smAnimTexture[tcnt]->NameA, len, &dwAcess, NULL);
			}
		}
	}

	return size;
}

int smMATERIAL_GROUP::LoadFile(HANDLE hFile)
{
	int StrLen = 0;
	char szNameBuff[4096] = { 0 };
	char *szName = nullptr;
	char *szNameA = nullptr;

	DWORD dwAcess = 0;
	INT size = ReadFile(hFile, &Head, sizeof(smMATERIAL_GROUP), &dwAcess, NULL);

	smMaterial = new smMATERIAL[MaterialCount]();

	for(DWORD cnt = 0; cnt < MaterialCount; cnt++)
	{
		size += ReadFile(hFile, &smMaterial[cnt], sizeof(smMATERIAL), &dwAcess, NULL);

		if(smMaterial[cnt].InUse)
		{
			size += ReadFile(hFile, &StrLen, sizeof(int), &dwAcess, NULL);

			size += ReadFile(hFile, szNameBuff, StrLen, &dwAcess, NULL);

			char* lpNameBuff = szNameBuff;

			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				szName = lpNameBuff;
				lpNameBuff += lstrlen(szName) + 1;
				szNameA = lpNameBuff;
				lpNameBuff += lstrlen(szNameA) + 1;

				if(szNameA[0])
					smMaterial[cnt].smTexture[tcnt] = smTexture.Add(szName, szNameA);
				else
					smMaterial[cnt].smTexture[tcnt] = smTexture.Add(szName);
			}

			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				szName = lpNameBuff;
				lpNameBuff += lstrlen(szName) + 1;
				szNameA = lpNameBuff;
				lpNameBuff += lstrlen(szNameA) + 1;

				if(szNameA[0])
					smMaterial[cnt].smAnimTexture[tcnt] = smTexture.Add(szName, szNameA);
				else
					smMaterial[cnt].smAnimTexture[tcnt] = smTexture.Add(szName);
			}
		}

	}

	return size;
}

int smMATERIAL_GROUP::DeleteUnuseMaterial()
{
	int dcnt = 0;

	for(DWORD cnt = 0; cnt < MaterialCount; cnt++)
	{
		if(smMaterial[cnt].InUse == TRUE)
		{
			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
				smTexture.Delete(smMaterial[cnt].smTexture[tcnt]);

			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
				smTexture.Delete(smMaterial[cnt].smAnimTexture[tcnt]);

			ZeroMemory(&smMaterial[cnt], sizeof(smMATERIAL));

			dcnt++;
		}
	}

	return dcnt;
}

int smMATERIAL_GROUP::AddMaterial(ASE_MATERIAL *aseMaterial, char *szScript)
{
	int cnt, len;
	int AnimCount, FrameSpeed;
	int MatNum;
	char *lpAnimFileList[16];
	char *szDirectory;
	char *lpScript;
	char szTemp[64];

	MatNum = MaterialCount;
	MaterialCount++;

	smMaterial[MatNum].InUse = TRUE;
	smMaterial[MatNum].Shade = TRUE;
	smMaterial[MatNum].BlendType = SMMAT_BLEND_ALPHA;
	smMaterial[MatNum].TwoSide = aseMaterial->TwoSide;
	smMaterial[MatNum].ReformTexture = 0;


	if(!aseMaterial->MAP_OPACITY[0])
	{
		for(cnt = 0; cnt < aseMaterial->TextureCounter; cnt++)
		{
			smMaterial[MatNum].smTexture[cnt] = smTexture.Add(aseMaterial->BITMAP[cnt]);
			smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
			smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
			smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
		}
		smMaterial[MatNum].MapOpacity = FALSE;
	}
	else
	{


		if(aseMaterial->TextureCounter > 1)
		{
			for(cnt = 0; cnt < aseMaterial->TextureCounter - 1; cnt++)
			{
				smMaterial[MatNum].smTexture[cnt] = smTexture.Add(aseMaterial->BITMAP[cnt], aseMaterial->MAP_OPACITY);
				smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
				smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
				smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
			}

			smMaterial[MatNum].smTexture[cnt] = smTexture.Add(aseMaterial->BITMAP[cnt]);
			smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
			smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
			smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
		}
		else
		{
			for(cnt = 0; cnt < aseMaterial->TextureCounter; cnt++)
			{
				smMaterial[MatNum].smTexture[cnt] = smTexture.Add(aseMaterial->BITMAP[cnt], aseMaterial->MAP_OPACITY);
				smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
				smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
				smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
			}
		}

		smMaterial[MatNum].MapOpacity = TRUE;

	}


	if(smMaterial[MatNum].ReformTexture) ReformTexture++;

	smMaterial[MatNum].TextureCounter = aseMaterial->TextureCounter;
	smMaterial[MatNum].Transparency = aseMaterial->Transparency;
	smMaterial[MatNum].SelfIllum = aseMaterial->SelfIllum;
	smMaterial[MatNum].Diffuse = aseMaterial->Diffuse;

	smMaterial[MatNum].UseState = aseMaterial->ScriptState;
	smMaterial[MatNum].TextureType = SMTEX_TYPE_MULTIMIX;

	if(aseMaterial->BlendType)
		smMaterial[MatNum].BlendType = aseMaterial->BlendType;


	if(smMaterial[MatNum].Transparency == 0)
		smMaterial[MatNum].MeshState = SMMAT_STAT_CHECK_FACE;


	if((aseMaterial->ScriptState&sMATS_SCRIPT_WIND))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ1;
		smMaterial[MatNum].MeshState = 0;
	}
	if((aseMaterial->ScriptState&sMATS_SCRIPT_WINDX1))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDX1;
		smMaterial[MatNum].MeshState = 0;
	}
	if((aseMaterial->ScriptState&sMATS_SCRIPT_WINDX2))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDX2;
		smMaterial[MatNum].MeshState = 0;
	}
	if((aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ1))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ1;
		smMaterial[MatNum].MeshState = 0;
	}
	if((aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ2))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ2;
		smMaterial[MatNum].MeshState = 0;
	}

	if((aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ2))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ2;
		smMaterial[MatNum].MeshState = 0;
	}

	if((aseMaterial->ScriptState&sMATS_SCRIPT_WATER))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WATER;
		smMaterial[MatNum].MeshState = 0;
	}


	if((aseMaterial->ScriptState&sMATS_SCRIPT_NOTPASS))
	{
		smMaterial[MatNum].MeshState = SMMAT_STAT_CHECK_FACE;
	}
	else
	{
		if((aseMaterial->ScriptState&sMATS_SCRIPT_PASS))
		{
			smMaterial[MatNum].MeshState = 0;
		}
	}

	if((aseMaterial->ScriptState&sMATS_SCRIPT_RENDLATTER))
	{
		smMaterial[MatNum].MeshState |= sMATS_SCRIPT_RENDLATTER;
	}



	if((aseMaterial->ScriptState & sMATS_SCRIPT_CHECK_ICE))
		smMaterial[MatNum].MeshState |= sMATS_SCRIPT_CHECK_ICE;




	if((aseMaterial->ScriptState & sMATS_SCRIPT_ORG_WATER))
		smMaterial[MatNum].MeshState = sMATS_SCRIPT_ORG_WATER;



	AnimCount = 0;
	if(szScript)
	{
		if(aseMaterial->ScriptState&sMATS_SCRIPT_ANIM2) AnimCount = 2;
		if(aseMaterial->ScriptState&sMATS_SCRIPT_ANIM4) AnimCount = 4;
		if(aseMaterial->ScriptState&sMATS_SCRIPT_ANIM8) AnimCount = 8;
		if(aseMaterial->ScriptState&sMATS_SCRIPT_ANIM16) AnimCount = 16;
	}

	if(AnimCount)
	{
		len = lstrlen(szScript);

		for(cnt = 0; cnt < len; cnt++)
		{
			if(szScript[cnt] == 'a' && szScript[cnt + 1] == 'n' &&
				szScript[cnt + 2] == 'i' && szScript[cnt + 3] == 'm')
			{
				for(cnt = cnt; cnt < len; cnt++)
				{
					if(szScript[cnt] == ':') break;
				}
				break;
			}
		}

		if(cnt < len)
		{
			cnt++;
			lpScript = &szScript[cnt];
			FrameSpeed = 0;

			for(cnt = cnt; cnt < len; cnt++)
			{
				if(szScript[cnt] == ':')
				{
					FrameSpeed = atoi(&szScript[cnt + 1]);
					szScript[cnt] = 0;
					break;
				}
			}

			szDirectory = SetDirectoryFromFile(aseMaterial->BITMAP[0]);

			if(szDirectory)
			{
				for(cnt = 0; cnt < AnimCount; cnt++)
				{
					lpAnimFileList[cnt] = new char[64];

					strcpy_s(szTemp, sizeof(szTemp), szDirectory);
					lstrcat(szTemp, lpScript);
					wsprintf(lpAnimFileList[cnt], szTemp, cnt);
				}

				ChangeMaterialToAnimation(&smMaterial[MatNum], lpAnimFileList, AnimCount, smMaterial[MatNum].BlendType, TRUE);
				if(FrameSpeed) smMaterial[MatNum].Shift_FrameSpeed = FrameSpeed;

				smMaterial[MatNum].Transparency = aseMaterial->Transparency;

				for(cnt = AnimCount - 1; cnt >= 0; cnt--)
				{
					if(lpAnimFileList[cnt])
					{
						delete[] lpAnimFileList[cnt];
						lpAnimFileList[cnt] = nullptr;
					}

				}
			}
		}
	}



	if((aseMaterial->ScriptState & sMATS_SCRIPT_BLINK_COLOR) && smMaterial[MatNum].WindMeshBottom == 0)
	{
		for(cnt = 0; cnt < MAX_MAP_BLINK_COLOR_TIME; cnt++)
		{
			if(strstr(szScript, szBlinkTimeScript[cnt]) != 0)
				break;
		}

		if(cnt >= MAX_MAP_BLINK_COLOR_TIME)
			smMaterial[MatNum].WindMeshBottom = dwBlinkTimeCode[0];
		else
			smMaterial[MatNum].WindMeshBottom = dwBlinkTimeCode[cnt];
	}


	aseMaterial->Regist++;
	aseMaterial->RegistNum = MatNum;

	return MatNum;
}


int smMATERIAL_GROUP::CreateTextureMaterial(char *szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD TexSwap, DWORD BlendType)
{
	int MatNum = MaterialCount;
	MaterialCount++;

	smMaterial[MatNum].InUse = TRUE;
	smMaterial[MatNum].Shade = Shade;
	smMaterial[MatNum].TwoSide = TwoSide;

	if(szOpacity)
		smMaterial[MatNum].smTexture[0] = smTexture.Add(szBitmap, szOpacity);
	else
		smMaterial[MatNum].smTexture[0] = smTexture.Add(szBitmap);


	smMaterial[MatNum].ReformTexture = 0;

	smMaterial[MatNum].TextureStageState[0] = 0;
	smMaterial[MatNum].TextureFormState[0] = 0;

	smMaterial[MatNum].smTexture[0]->TexSwapMode = TexSwap;
	smMaterial[MatNum].MapOpacity = FALSE;

	smMaterial[MatNum].TextureCounter = 1;
	smMaterial[MatNum].Transparency = 0;


	smMaterial[MatNum].UseState = 0;
	smMaterial[MatNum].TextureType = SMTEX_TYPE_MULTIMIX;
	smMaterial[MatNum].BlendType = BlendType;


	smMaterial[MatNum].InUse++;

	return MatNum;
}


int smMATERIAL_GROUP::AddTexture(int MatNum, char *szBitmap, char *szOpacity)
{
	int cnt = smMaterial[MatNum].TextureCounter;

	if(szOpacity)
		smMaterial[MatNum].smTexture[cnt] = smTexture.Add(szBitmap, szOpacity);
	else
		smMaterial[MatNum].smTexture[cnt] = smTexture.Add(szBitmap);

	if(smMaterial[MatNum].smTexture[cnt])
		smMaterial[MatNum].TextureCounter++;

	return TRUE;
}


smMATERIAL *smMATERIAL_GROUP::FindNextMaterialFromTextureName()
{
	char *szName = szLastSearchName;


	for(DWORD cnt = LastSearchMaterial; cnt < MaterialCount; cnt++)
	{
		if(smMaterial[cnt].InUse)
		{

			for(DWORD cnt2 = 0; cnt2 < smMaterial[cnt].TextureCounter; cnt2++)
			{
				if(lstrcmpi(smMaterial[cnt].smTexture[cnt2]->Name, szName) == 0)
				{
					return &smMaterial[cnt];
				}
			}

			for(DWORD cnt2 = 0; cnt2 < smMaterial[cnt].AnimTexCounter; cnt2++)
			{
				if(lstrcmpi(smMaterial[cnt].smAnimTexture[cnt2]->Name, szName) == 0)
				{
					return &smMaterial[cnt];
				}
			}

		}
	}

	return NULL;
}


smMATERIAL *smMATERIAL_GROUP::FindMaterialFromTextureName(char *szName)
{
	LastSearchMaterial = 0;

	int size = strlen(szName);

	if(size > sizeof(szLastSearchName))
	{
		MessageBox(NULL, "smMATERIAL_GROUP::FindMaterialFromTextureName", szName, 0x30);
	}

	strcpy_s(szLastSearchName, szName);

	return FindNextMaterialFromTextureName();
}


int smMATERIAL_GROUP::SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame)
{
	int OldFrame = lpMaterial->AnimationFrame;
	lpMaterial->AnimationFrame = frame;

	return OldFrame;
}




int smMATERIAL_GROUP::ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode)
{
	for(int cnt = 0; cnt < NumTex; cnt++)
	{
		lpMaterial->smAnimTexture[cnt] = smTexture.Add(szBitmap[cnt]);
		lpMaterial->smAnimTexture[cnt]->TexSwapMode = FALSE;
	}


	lpMaterial->MapOpacity = FALSE;
	lpMaterial->TextureCounter = 1;
	lpMaterial->Transparency = 0;

	lpMaterial->AnimTexCounter = NumTex;
	lpMaterial->FrameMask = NumTex - 1;
	lpMaterial->Shift_FrameSpeed = 6;

	lpMaterial->UseState = 0;
	lpMaterial->TextureType = SMTEX_TYPE_ANIMATION;
	lpMaterial->BlendType = BlendType;


	if(AutoAnimMode)
		lpMaterial->AnimationFrame = SMTEX_AUTOANIMATION;
	else
		lpMaterial->AnimationFrame = 0;

	lpMaterial->InUse++;

	return TRUE;
}



int smMATERIAL_GROUP::CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode)
{
	int cnt = MaterialCount;

	MaterialCount++;

	smMATERIAL* lpMaterial = &smMaterial[cnt];

	lpMaterial->InUse = TRUE;
	lpMaterial->Shade = FALSE;
	lpMaterial->TwoSide = TRUE;

	ChangeMaterialToAnimation(lpMaterial, szBitmap, NumTex, BlendType, AutoAnimMode);

	return cnt;
}




int smMATERIAL_GROUP::IncTextureFrame()
{
	return TRUE;
}




int smMATERIAL_GROUP::CheckMatreialTextureSwap()
{


	return TRUE;


	DWORD cnt, cnt2;


	for(cnt = 0; cnt < MaterialCount; cnt++)
		if(smMaterial[cnt].InUse)
		{
			if(smMaterial[cnt].TextureType == SMTEX_TYPE_MULTIMIX)
			{
				for(cnt2 = 0; cnt2 < smMaterial[cnt].TextureCounter; cnt2++)
				{
					if(smMaterial[cnt].smTexture[cnt2] && smMaterial[cnt].smTexture[cnt2]->lpDDSSysMemory)
					{
						smMaterial[cnt].TextureSwap = TRUE;
						break;
					}
				}
			}

			if(smMaterial[cnt].TextureType == SMTEX_TYPE_ANIMATION)
			{
				for(cnt2 = 0; cnt2 < smMaterial[cnt].AnimTexCounter; cnt2++)
				{
					if(smMaterial[cnt].smAnimTexture[cnt2] && smMaterial[cnt].smAnimTexture[cnt2]->lpDDSSysMemory)
					{
						smMaterial[cnt].TextureSwap = TRUE;
						break;
					}
				}
			}

		}

	return TRUE;
}



int smMATERIAL_GROUP::ReSwapMaterial(smMATERIAL *lpMaterial)
{


	return TRUE;


	DWORD cnt;
	int result;

	lpMaterial->MatFrame = MaterialFrame;

	lpMaterial->TextureClip = FALSE;

	if(lpMaterial->TextureSwap)
	{
		result = 0;
		for(cnt = 0; cnt < lpMaterial->TextureCounter; cnt++)
		{
			result |= smTexture.SetLargeTexture(lpMaterial->smTexture[cnt]);
		}

		if(result)
		{
			lpMaterial->TextureClip = TRUE;
			return TRUE;
		}
	}

	return FALSE;
}




int smMATERIAL_GROUP::ReadTextures(int MipMap)

{


	if(g_IsReadTextures == 0)
		return 0;


	int Result = 0;
	int ReadCount = 0;
	smTEXTUREHANDLE *lpTexture = nullptr;


	smEnterTextureCriticalSection();


	for(DWORD cnt = 0; cnt < MaterialCount; cnt++)
	{
		if(smMaterial && smMaterial[cnt].InUse)
		{
			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				if(smMaterial[cnt].smTexture[tcnt])
				{
					lpTexture = smMaterial[cnt].smTexture[tcnt];

					if(lpTexture->UseCounter && !lpTexture->lpD3DTexture)
					{



						Result = new_smCreateTexture(lpTexture, MipMap);


						ReadCount++;
					}
				}
			}

			for(DWORD tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				if(smMaterial[cnt].smAnimTexture[tcnt])
				{
					lpTexture = smMaterial[cnt].smAnimTexture[tcnt];
					if(lpTexture->UseCounter && !lpTexture->lpD3DTexture)
					{



						Result = new_smCreateTexture(lpTexture, MipMap);


						ReadCount++;
					}
				}
			}
		}
	}

	smLeaveTextureCriticalSection();

	return ReadCount;
}

smMATERIAL *smMaterial = nullptr;
smMATERIAL_GROUP *smMaterialGroup = nullptr;

int InitMaterial()
{
	smMaterialGroup = new smMATERIAL_GROUP(MATRIAL_MAX);
	smMaterial = smMaterialGroup->smMaterial;

	MaterialFrame = 0;

	return TRUE;
}

int CloseMaterial()
{
	if(smMaterialGroup)
	{
		delete smMaterialGroup;
		smMaterialGroup = nullptr;
	}

	return TRUE;
}

int DeleteUnuseMaterial()
{
	return smMaterialGroup->DeleteUnuseMaterial();
}

int AddMaterial(ASE_MATERIAL *aseMaterial)
{
	return smMaterialGroup->AddMaterial(aseMaterial);
}

int CreateTextureMaterial(char* szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD TexSwap, DWORD BlendType)
{
	return smMaterialGroup->CreateTextureMaterial(szBitmap, szOpacity, TwoSide, Shade, TexSwap, BlendType);
}

int AddTexture(int MatNum, char *szBitmap, char *szOpacity)
{
	return smMaterialGroup->AddTexture(MatNum, szBitmap, szOpacity);
}

smMATERIAL *FindNextMaterialFromTextureName()
{
	return smMaterialGroup->FindNextMaterialFromTextureName();
}

smMATERIAL *FindMaterialFromTextureName(char *szName)
{
	return smMaterialGroup->FindMaterialFromTextureName(szName);
}

int SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame)
{
	return smMaterialGroup->SetMaterialAnimFrame(lpMaterial, frame);
}

int ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode)
{
	return smMaterialGroup->ChangeMaterialToAnimation(lpMaterial, szBitmap, NumTex, BlendType, AutoAnimMode);
}

int CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode)
{
	return smMaterialGroup->CreateAnimationMaterial(szBitmap, NumTex, BlendType, AutoAnimMode);
}

int IncTextureFrame()
{
	MaterialFrame++;
	return smTexture.SwapCount++;
}

int CheckMatreialTextureSwap()
{
	return smMaterialGroup->CheckMatreialTextureSwap();
}


int ReSwapMaterial(smMATERIAL *lpMaterial)
{
	return smMaterialGroup->ReSwapMaterial(lpMaterial);
}


struct smTEXTUREFORMAT
{
	DWORD BPP_DW;
	DWORD MinAlpha;
	BOOL bUsePalette;
	BOOL bUseFourCC;
	BOOL bFoundGoodFormat;
	DDPIXELFORMAT *pddpf;
};




static HRESULT CALLBACK TextureSearchCallback(DDPIXELFORMAT* pddpf,
	VOID* param)
{
	if(NULL == pddpf || NULL == param)
		return DDENUMRET_OK;

	smTEXTUREFORMAT* ptsi = (smTEXTUREFORMAT*)param;


	if(pddpf->dwFlags & (DDPF_LUMINANCE | DDPF_BUMPLUMINANCE | DDPF_BUMPDUDV))
		return DDENUMRET_OK;


	if(ptsi->bUsePalette)
	{
		if(!(pddpf->dwFlags & DDPF_PALETTEINDEXED8))
			return DDENUMRET_OK;


		memcpy(ptsi->pddpf, pddpf, sizeof(DDPIXELFORMAT));
		ptsi->bFoundGoodFormat = TRUE;
		return DDENUMRET_CANCEL;
	}


	if(pddpf->dwRGBBitCount < 16)
		return DDENUMRET_OK;


	if(ptsi->bUseFourCC)
	{
		if(pddpf->dwFourCC == 0)
			return DDENUMRET_OK;

		return DDENUMRET_CANCEL;
	}


	if(pddpf->dwFourCC != 0)
		return DDENUMRET_OK;


	if((ptsi->MinAlpha > 0) && !(pddpf->dwFlags&DDPF_ALPHAPIXELS))
		return DDENUMRET_OK;
	if((ptsi->MinAlpha == 0) && (pddpf->dwFlags&DDPF_ALPHAPIXELS))
		return DDENUMRET_OK;

	DWORD AlphaBitTest;
	int cnt;

	if(ptsi->MinAlpha > 0)
	{
		AlphaBitTest = pddpf->dwRGBAlphaBitMask;
		for(cnt = 0; cnt < 32; cnt++)
		{
			if((AlphaBitTest & 1)) break;
			AlphaBitTest >>= 1;
		}
		if(ptsi->MinAlpha > AlphaBitTest)
			return DDENUMRET_OK;
	}


	if(pddpf->dwRGBBitCount == ptsi->BPP_DW)
	{
		memcpy(ptsi->pddpf, pddpf, sizeof(DDPIXELFORMAT));
		ptsi->bFoundGoodFormat = TRUE;
		return DDENUMRET_CANCEL;
	}

	return DDENUMRET_OK;
}

int GetPixelFormatAlphaTexture()
{
	smTEXTUREFORMAT TextureFormat;


	TextureFormat.BPP_DW = 32;

	TextureFormat.MinAlpha = 8;
	TextureFormat.bUseFourCC = FALSE;
	TextureFormat.bUsePalette = FALSE;
	TextureFormat.bFoundGoodFormat = FALSE;
	TextureFormat.pddpf = &ddTextureFormat;

	renderDevice.EnumTextureFormats(TextureSearchCallback, &TextureFormat);

	TextureFormat.BPP_DW = 32;

	TextureFormat.MinAlpha = 0;
	TextureFormat.bUseFourCC = FALSE;
	TextureFormat.bUsePalette = FALSE;
	TextureFormat.bFoundGoodFormat = FALSE;
	TextureFormat.pddpf = &ddDefaultTextureFormat;

	renderDevice.EnumTextureFormats(TextureSearchCallback, &TextureFormat);

	return TRUE;

}



int InitTexture()
{
	smTexture.Init();

	GetPixelFormatAlphaTexture();

	return TRUE;
}

int CloseTexture()
{
	smTexture.Remove();

	return TRUE;
}

int ReadTextures()
{
	if(g_IsReadTextures == 0)
	{
		return 0;
	}


	int val = smTexture.ReadTexture();

	CheckMatreialTextureSwap();

	return val;
}


int RestoreTextures()
{
	return smTexture.Restore();
}




LPDIRECT3DTEXTURE2 GetTextureHandle(int num)
{
	return smTexture.Texture[num].lpD3DTexture;
}

LPDIRECT3DTEXTURE2 GetTextureChildHandle(int num)
{
	if(smTexture.Texture[num].TexChild)
		return smTexture.Texture[num].TexChild->lpD3DTexture;
	else
		return NULL;
}



LPDIRECTDRAWSURFACE4 *GetLastTextureSurface()
{
	return smTexture.lpLastTextureSurface;
}

LPDIRECT3DTEXTURE2 *GetLastTexture()
{
	return smTexture.lpLastTexture;
}


void smEnterTextureCriticalSection()
{
	EnterCriticalSection(&smTexture.cTextureSection);
}


void smLeaveTextureCriticalSection()
{
	LeaveCriticalSection(&smTexture.cTextureSection);
}

int hresult;



DWORD GetDibInfoHeaderSize(BYTE *lpDib)
{
	return ((BITMAPINFOHEADER *)lpDib)->biSize;
}
WORD GetDibWidth(BYTE *lpDib)
{
	if(GetDibInfoHeaderSize(lpDib) + sizeof(BITMAPCOREHEADER))
		return (WORD)(((BITMAPCOREHEADER *)lpDib)->bcWidth);
	else
		return (WORD)(((BITMAPINFOHEADER *)lpDib)->biWidth);
}
WORD GetDibHeight(BYTE *lpDib)
{
	if(GetDibInfoHeaderSize(lpDib) == sizeof(BITMAPCOREHEADER))
		return (WORD)(((BITMAPCOREHEADER *)lpDib)->bcHeight);
	else
		return (WORD)(((BITMAPINFOHEADER *)lpDib)->biHeight);
}

WORD GetDibBitCount(BYTE *lpDib)
{
	return ((BITMAPINFOHEADER *)lpDib)->biBitCount;
}

BYTE *GetDibBitsAddr(BYTE *lpDib)
{
	DWORD dwNumColors, dwColorTableSize;
	WORD wBitCount;

	if(GetDibInfoHeaderSize(lpDib) == sizeof(BITMAPCOREHEADER))
	{
		wBitCount = ((BITMAPCOREHEADER *)lpDib)->bcBitCount;
		if(wBitCount != 24)
			dwNumColors = 1L << wBitCount;
		else dwNumColors = 0;
		dwColorTableSize = dwNumColors * sizeof(RGBTRIPLE);
	}
	else
	{
		wBitCount = ((BITMAPINFOHEADER *)lpDib)->biBitCount;
		if(GetDibInfoHeaderSize(lpDib) >= 36)
			dwNumColors = ((BITMAPINFOHEADER *)lpDib)->biClrUsed;
		else
			dwNumColors = 0;
		if(dwNumColors == 0)
		{
			if(wBitCount != 24)
				dwNumColors = 1L << wBitCount;
			else
				dwNumColors = 0;
		}
		dwColorTableSize = dwNumColors * sizeof(RGBQUAD);
	}
	return lpDib + GetDibInfoHeaderSize(lpDib) + dwColorTableSize;
}

BYTE *LoadDib(char *Filename)
{
	BITMAPFILEHEADER bmfh;
	DWORD dwDibSize, dwHeaderSize;
	DWORD dwAcess;

	HANDLE hFile = CreateFile(Filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	ReadFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwAcess, NULL);

	if(bmfh.bfType != *(WORD *)"BM" && bmfh.bfType != *(WORD *)"C8" && bmfh.bfType != *(WORD *)"A8")
	{
		CloseHandle(hFile);
		return NULL;
	}

	if(bmfh.bfType == *(WORD *)"A8")
	{
		BYTE* lpHeader = (BYTE *)&bmfh;

		for(int cnt = 0; cnt < sizeof(bmfh); cnt++)
		{
			BYTE ch = (BYTE)(lpHeader[cnt] - (cnt * cnt));
			lpHeader[cnt] = ch;
		}
	}

	dwDibSize = bmfh.bfSize - sizeof(BITMAPFILEHEADER);

	BYTE* lpDib = new BYTE[dwDibSize];

	if(!lpDib)
	{
		CloseHandle(hFile);
		return nullptr;
	}

	ReadFile(hFile, lpDib, dwDibSize, &dwAcess, NULL);
	CloseHandle(hFile);
	dwHeaderSize = GetDibInfoHeaderSize(lpDib);

	if(dwHeaderSize < 12 || (dwHeaderSize > 12 && dwHeaderSize < 16))
	{
		if(lpDib)
		{
			delete[] lpDib;
			return nullptr;
		}
	}

	return lpDib;
}


class cTGA
{
public:
	BYTE *m_pBuff;
	BYTE *m_pData;
	int Width, Height;
	int SwapHeight;
	int BitCount;

	cTGA();
	~cTGA();

	int LoadTga(char *Filename);
	int GetWidth();
	int GetHeight();
	int GetBitCount();

};

cTGA::cTGA()
{
	m_pBuff = 0;
	m_pData = 0;
	Width = 0;
	Height = 0;
	BitCount = 0;
}

cTGA::~cTGA()
{
	if(m_pBuff)
	{
		delete[] m_pData;
		m_pData = nullptr;
	}


}


int cTGA::LoadTga(char *Filename)
{
	WORD *Bit16Buff;
	WORD r, g, b;

	int DestCnt;
	int SrcCnt;

	DWORD dwAcess;

	HANDLE hFile = CreateFile(Filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	BYTE TGAHeader[0x12];

	ReadFile(hFile, TGAHeader, 0x12, &dwAcess, NULL);

	if(TGAHeader[0] == 'G' && TGAHeader[1] == '8')
	{
		BYTE ch = 0;
		BYTE *lpHeader = (BYTE *)&TGAHeader;

		for(int cnt = 0; cnt < sizeof(TGAHeader); cnt++)
		{
			ch = (BYTE)(lpHeader[cnt] - (cnt*cnt));
			lpHeader[cnt] = ch;
		}
	}

	Width = *((WORD *)(&TGAHeader[0xC]));
	Height = *((WORD *)(&TGAHeader[0xE]));

	if((TGAHeader[0x11] & 0x20))
	{
		SwapHeight = FALSE;
	}
	else
		SwapHeight = TRUE;

	switch(TGAHeader[0x10])
	{
	case 16:
	{
		m_pBuff = new BYTE[Width * Height * 3];
		int len = Width * Height;
		Bit16Buff = new WORD[len];
		ReadFile(hFile, Bit16Buff, len * 2, &dwAcess, NULL);

		DestCnt = 0;
		for(SrcCnt = 0; SrcCnt < len; SrcCnt++)
		{
			r = (Bit16Buff[SrcCnt] >> 10) & 0x1F;
			g = (Bit16Buff[SrcCnt] >> 5) & 0x1F;
			b = (Bit16Buff[SrcCnt]) & 0x1F;

			m_pBuff[DestCnt] = (r << 3) | (r >> 2);
			m_pBuff[DestCnt + 1] = (g << 3) | (g >> 2);
			m_pBuff[DestCnt + 2] = (b << 3) | (b >> 2);
			DestCnt += 3;
		}

		if(Bit16Buff)
		{
			delete[] Bit16Buff;
			Bit16Buff = nullptr;
		}

		BitCount = 24;
	}
	break;

	case 24:
		m_pBuff = new BYTE[Width*Height * 3];
		ReadFile(hFile, m_pBuff, Width*Height * 3, &dwAcess, NULL);

		BitCount = 24;
		break;
	case 32:
		m_pBuff = new BYTE[Width*Height * 4];
		ReadFile(hFile, m_pBuff, Width*Height * 4, &dwAcess, NULL);

		BitCount = 32;
		break;
	}
	CloseHandle(hFile);

	m_pData = m_pBuff;

	return TRUE;
}

int cTGA::GetWidth()
{
	return Width;
}

int cTGA::GetHeight()
{
	return Height;
}

int cTGA::GetBitCount()
{
	return BitCount;
}

#define smTEXFILETYPE_BMP 0
#define smTEXFILETYPE_JPG 1
#define smTEXFILETYPE_TGA 2


int GetTextureFileType(char *Filename)
{
	char *szFileExt = nullptr;

	int len = lstrlen(Filename);

	for(int cnt = len - 1; cnt >= 0; cnt--)
	{
		if(Filename[cnt] == '.')
		{
			szFileExt = Filename + cnt + 1;
			break;
		}
	}

	if(!szFileExt)
		return -1;

	if((szFileExt[0] == 'j' || szFileExt[0] == 'J') &&
		(szFileExt[1] == 'p' || szFileExt[1] == 'P') &&
		(szFileExt[2] == 'g' || szFileExt[2] == 'G'))
		return smTEXFILETYPE_JPG;

	if((szFileExt[0] == 'b' || szFileExt[0] == 'B') &&
		(szFileExt[1] == 'm' || szFileExt[1] == 'M') &&
		(szFileExt[2] == 'p' || szFileExt[2] == 'P'))
		return smTEXFILETYPE_BMP;

	if((szFileExt[0] == 't' || szFileExt[0] == 'T') &&
		(szFileExt[1] == 'g' || szFileExt[1] == 'G') &&
		(szFileExt[2] == 'a' || szFileExt[2] == 'A'))
		return smTEXFILETYPE_TGA;


	if((szFileExt[0] == 's' || szFileExt[0] == 'S') &&
		(szFileExt[1] == 't' || szFileExt[1] == 'T') &&
		(szFileExt[2] == 'g' || szFileExt[2] == 'G'))
		return smTEXFILETYPE_JPG;

	if((szFileExt[0] == 's' || szFileExt[0] == 'S') &&
		(szFileExt[1] == 't' || szFileExt[1] == 'T') &&
		(szFileExt[2] == 'a' || szFileExt[2] == 'A'))
		return smTEXFILETYPE_TGA;

	return -1;
}






int LoadDibSurfaceAlphaMipMap(LPDIRECTDRAWSURFACE4 lpDDSurface, char *Filename, char *FileAlpha, int CheckWidth, int CheckHeight)
{
	BYTE *lpDib = nullptr;
	BYTE *dAddr = nullptr;
	int height = 0, width = 0;

	BYTE *lpDibAlpha = nullptr;
	BYTE *dAddrAlpha = nullptr;
	int BitCnt = 0;
	int AlphaBitCnt = 0;
	int SwapHeight = TRUE;
	int SwapHeightAl = TRUE;

	CJpeg *cJpeg = nullptr;
	CJpeg *cJpegAl = nullptr;
	cTGA *cTga = nullptr;
	cTGA *cTgaAl = nullptr;


	int FileTypeCl = GetTextureFileType(Filename);
	int FileTypeAl = GetTextureFileType(FileAlpha);


	switch(FileTypeCl)
	{
	case smTEXFILETYPE_TGA:
		cTga = new cTGA;
		if(cTga->LoadTga(Filename))
		{
			dAddr = cTga->m_pData;
			width = cTga->GetWidth();
			height = cTga->GetHeight();
			BitCnt = cTga->GetBitCount();
			SwapHeightAl = cTga->SwapHeight;
		}
		else
		{
			if(cTga)
			{
				delete cTga;
				cTga = nullptr;
			}

			BitCnt = 0;
			return -1;
		}
		break;

	case smTEXFILETYPE_BMP:
		lpDib = LoadDib(Filename);

		if(lpDib)
		{
			dAddr = GetDibBitsAddr(lpDib);
			height = GetDibHeight(lpDib);
			width = GetDibWidth(lpDib);
			BitCnt = GetDibBitCount(lpDib);
		}
		else
		{
			if(lpDib)
			{
				delete[] lpDib;
				lpDib = nullptr;
			}

			return -1;

		}
		break;

	case smTEXFILETYPE_JPG:
		cJpeg = new CJpeg;
		cJpeg->LoadJPG(Filename);
		if(cJpeg->m_pData)
		{
			dAddr = cJpeg->m_pData;
			height = cJpeg->GetHeight();
			width = cJpeg->GetWidth();
			BitCnt = 24;
		}
		else
		{


			if(cJpeg)
			{
				delete cJpeg;
				cJpeg = nullptr;
			}

			return -1;

		}
		break;
	}



	if(width != CheckWidth || height != CheckHeight)
	{
		if(lpDib)
		{
			delete[] lpDib;
			lpDib = nullptr;
		}

		if(cTga)
		{
			delete cTga;
			cTga = nullptr;
		}

		if(cJpeg)
		{
			delete cJpeg;
			cJpeg = nullptr;
		}

		return -1;
	}





	int ErrorFileTypeAl = 0;

	switch(FileTypeAl)
	{
	case smTEXFILETYPE_TGA:
		cTgaAl = new cTGA;
		if(cTgaAl->LoadTga(FileAlpha))
		{
			dAddrAlpha = cTgaAl->m_pData;
			AlphaBitCnt = cTgaAl->GetBitCount();
			SwapHeightAl = cTgaAl->SwapHeight;

			if(CheckWidth != cTgaAl->GetWidth() || CheckHeight != cTgaAl->GetHeight())
				ErrorFileTypeAl = 1;
		}
		else
		{
			dAddrAlpha = NULL;
			AlphaBitCnt = 0;
		}
		break;

	case smTEXFILETYPE_BMP:
		lpDibAlpha = LoadDib(FileAlpha);
		if(lpDibAlpha)
		{
			dAddrAlpha = GetDibBitsAddr(lpDibAlpha);
			AlphaBitCnt = GetDibBitCount(lpDibAlpha);

			if(CheckWidth != GetDibWidth(lpDibAlpha) || CheckHeight != GetDibHeight(lpDibAlpha))
				ErrorFileTypeAl = 1;
		}
		else
		{
			dAddrAlpha = NULL;
			AlphaBitCnt = 0;
		}
		break;

	case smTEXFILETYPE_JPG:
		cJpegAl = new CJpeg;
		cJpegAl->LoadJPG(FileAlpha);
		if(cJpegAl->m_pData)
		{
			dAddrAlpha = cJpegAl->m_pData;
			AlphaBitCnt = 24;

			if(CheckWidth != cJpegAl->GetWidth() || CheckHeight != cJpegAl->GetHeight())
				ErrorFileTypeAl = 1;
		}
		else
		{
			dAddrAlpha = NULL;
			AlphaBitCnt = 0;
		}
		break;
	}

	if(ErrorFileTypeAl)
	{
		if(lpDib)
		{
			delete[] lpDib;
			lpDib = nullptr;
		}


		if(cTga)
		{
			delete cTga;
			cTga = nullptr;
		}

		if(cJpeg)
		{
			delete cJpeg;
			cJpeg = nullptr;
		}

		if(lpDibAlpha)
		{
			delete[] lpDibAlpha;
			lpDibAlpha = nullptr;
		}

		if(cJpegAl)
		{
			delete cJpegAl;
			cJpegAl = nullptr;
		}

		if(cTgaAl)
		{
			delete cTgaAl;
			cTgaAl = nullptr;
		}

		return -2;
	}


	int i, j, k;
	int r, g, b, a, tp;
	BYTE *Dest;
	DWORD MaskAll;

	DWORD Mask[4];
	DWORD Shift[4];
	DWORD ShiftPixel[4];
	DWORD ShiftTemp;


	Mask[0] = ddTextureFormat.dwRBitMask;
	Mask[1] = ddTextureFormat.dwGBitMask;
	Mask[2] = ddTextureFormat.dwBBitMask;
	Mask[3] = ddTextureFormat.dwRGBAlphaBitMask;

	MaskAll = Mask[0] | Mask[1] | Mask[2] | Mask[3];

	for(i = 0; i < 4; i++)
	{
		if(Mask[i])
		{
			ShiftTemp = Mask[i];
			for(j = 0; j < 32; j++)
			{
				if(ShiftTemp & 1) break;
				ShiftTemp >>= 1;
			}
			Shift[i] = j;
			for(j = 0; j < 32; j++)
			{
				if((ShiftTemp & 1) == 0) break;
				ShiftTemp >>= 1;
			}
			ShiftPixel[i] = j;
		}
		else
		{
			Shift[i] = 32;
			ShiftPixel[i] = 32;
		}
	}

	int pBuff, pBuffAl;
	int incByte = 3;
	int incByteAl = 3;
	int pBuff_k;

	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	lpDDSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	Dest = (BYTE *)ddsd.lpSurface;

	if(!Dest) goto Lop_Quit;


	pBuff_k = 0;
	k = 0;
	for(i = 0; i < height; i++)
	{
		switch(BitCnt)
		{
		case 24:
			if(SwapHeight) pBuff = (height - i - 1)*width * 3;
			else pBuff = i*width * 3;
			incByte = 3;
			break;
		case 32:
			if(SwapHeight) pBuff = ((height - i - 1)*width) << 2;
			else pBuff = (i*width) << 2;
			incByte = 4;
			break;
		}

		switch(AlphaBitCnt)
		{
		case 8:
			if(SwapHeightAl) pBuffAl = (height - i - 1)*width;
			else pBuffAl = i*width;
			incByteAl = 1;
			break;

		case 24:
			if(SwapHeightAl) pBuffAl = (height - i - 1)*width * 3;
			else pBuffAl = i*width * 3;
			incByteAl = 3;
			break;

		case 32:
			if(SwapHeightAl) pBuffAl = ((height - i - 1)*width) << 2;
			else pBuffAl = (i*width) << 2;
			incByteAl = 4;
			break;
		}



		k = pBuff_k;

		if(dAddrAlpha)
		{
			for(j = 0; j < width; j++)
			{

				b = dAddr[pBuff];
				g = dAddr[pBuff + 1];
				r = dAddr[pBuff + 2];

				if(BitCnt == 32)
				{
					a = dAddr[pBuff + 3];
				}
				else
				{
					a = 255;

					switch(AlphaBitCnt)
					{
					case 8:
						a = dAddrAlpha[pBuffAl];
						break;
					case 24:
					case 32:
						a = dAddrAlpha[pBuffAl] + dAddrAlpha[pBuffAl + 1] + dAddrAlpha[pBuffAl + 2];
						a /= 3;
						break;
					}
					pBuffAl += incByteAl;
				}
				pBuff += incByte;

				r = ((r >> (8 - ShiftPixel[0])) << Shift[0]) & Mask[0];
				g = ((g >> (8 - ShiftPixel[1])) << Shift[1]) & Mask[1];
				b = ((b >> (8 - ShiftPixel[2])) << Shift[2]) & Mask[2];
				a = ((a >> (8 - ShiftPixel[3])) << Shift[3]) & Mask[3];

				tp = r | g | b | a;




				if(MaskAll <= 0xFFFF)
				{
					*((WORD *)&Dest[k]) = (WORD)tp;
					k += 2;
				}
				else
				{
					*((DWORD *)&Dest[k]) = tp;
					k += 4;
				}
			}
		}
		pBuff_k += (int)ddsd.lPitch;

	}
	lpDDSurface->Unlock(NULL);


Lop_Quit:

	if(cJpeg)
	{
		delete cJpeg;
		cJpeg = nullptr;
	}

	if(lpDib)
	{
		delete[] lpDib;
		lpDib = nullptr;
	}

	if(cTga)
	{
		delete cTga;
		cTga = nullptr;
	}

	if(cJpegAl)
	{
		delete cJpegAl;
		cJpegAl = nullptr;
	}

	if(lpDibAlpha)
	{
		delete[] lpDibAlpha;
		lpDibAlpha = nullptr;
	}

	if(cTgaAl)
	{
		delete cTgaAl;
		cTgaAl = nullptr;
	}

	return TRUE;
}


LPDIRECTDRAWSURFACE4 LoadDibSurfaceAlpha(char *Filename, char *FileAlpha, int SysMem)
{
	BYTE *lpDib = nullptr;
	BYTE *dAddr = nullptr;
	int height = 0, width = 0;

	BYTE *lpDibAlpha = nullptr;
	BYTE *dAddrAlpha = nullptr;
	int BitCnt = 0;
	int AlphaBitCnt = 0;


	CJpeg *cJpeg = nullptr;
	CJpeg *cJpegAl = nullptr;
	cTGA *cTga = nullptr;
	cTGA *cTgaAl = nullptr;

	int SwapHeight = TRUE;
	int SwapHeightAl = TRUE;

	int FileTypeCl = GetTextureFileType(Filename);
	int FileTypeAl = GetTextureFileType(FileAlpha);


	switch(FileTypeCl)
	{
	case smTEXFILETYPE_TGA:
		cTga = new cTGA;
		if(cTga->LoadTga(Filename))
		{
			dAddr = cTga->m_pData;
			width = cTga->GetWidth();
			height = cTga->GetHeight();
			BitCnt = cTga->GetBitCount();
			SwapHeightAl = cTga->SwapHeight;

		}
		else
		{


			if(cTga)
			{
				delete cTga;
				cTga = nullptr;
			}

			BitCnt = 0;
			return NULL;
		}

		break;

	case smTEXFILETYPE_BMP:
		lpDib = LoadDib(Filename);
		if(lpDib)
		{
			dAddr = GetDibBitsAddr(lpDib);
			height = GetDibHeight(lpDib);
			width = GetDibWidth(lpDib);
			BitCnt = GetDibBitCount(lpDib);
		}
		else
		{


			if(lpDib)
			{
				delete[] lpDib;
				lpDib = nullptr;
			}

			return NULL;
		}
		break;

	case smTEXFILETYPE_JPG:
		cJpeg = new CJpeg;
		cJpeg->LoadJPG(Filename);
		if(cJpeg->m_pData)
		{
			dAddr = cJpeg->m_pData;
			height = cJpeg->GetHeight();
			width = cJpeg->GetWidth();
			BitCnt = 24;
		}
		else
		{


			if(cJpeg)
			{
				delete cJpeg;
				cJpeg = nullptr;
			}

			return NULL;
		}
		break;
	}

	switch(FileTypeAl)
	{
	case smTEXFILETYPE_TGA:
		cTgaAl = new cTGA;
		if(cTgaAl->LoadTga(FileAlpha))
		{
			dAddrAlpha = cTgaAl->m_pData;
			AlphaBitCnt = cTgaAl->GetBitCount();
			SwapHeightAl = cTgaAl->SwapHeight;
		}
		else
		{
			dAddrAlpha = NULL;
			AlphaBitCnt = 0;
		}

		break;

	case smTEXFILETYPE_BMP:

		lpDibAlpha = LoadDib(FileAlpha);

		if(lpDibAlpha)
		{
			dAddrAlpha = GetDibBitsAddr(lpDibAlpha);
			AlphaBitCnt = GetDibBitCount(lpDibAlpha);
		}
		else
		{
			dAddrAlpha = NULL;
			AlphaBitCnt = 0;
		}

		break;

	case smTEXFILETYPE_JPG:
		cJpegAl = new CJpeg;
		cJpegAl->LoadJPG(FileAlpha);
		if(cJpegAl->m_pData)
		{
			dAddrAlpha = cJpegAl->m_pData;
			AlphaBitCnt = 24;
		}
		else
		{
			dAddrAlpha = NULL;
			AlphaBitCnt = 0;
		}
		break;
	}


	LPDIRECTDRAWSURFACE4 lpDDSurface;
	DDSURFACEDESC2 ddsd;

	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS |
		DDSD_HEIGHT |
		DDSD_WIDTH |
		DDSD_PIXELFORMAT;
	ddsd.dwWidth = width;
	ddsd.dwHeight = height;

	memcpy(&ddsd.ddpfPixelFormat, &ddTextureFormat, sizeof(DDPIXELFORMAT));



	if(renderDevice.GetDeviceDesc_IsHardware() && SysMem == FALSE)
	{

		ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
		ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
	else
		ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;


	hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);


	if(hresult != DD_OK)
	{
		if(cJpeg)
		{
			delete cJpeg;
			cJpeg = nullptr;
		}

		if(lpDib)
		{
			delete[] lpDib;
			lpDib = nullptr;
		}

		if(cTga)
		{
			delete cTga;
			cTga = nullptr;
		}

		if(cJpegAl)
		{
			delete cJpegAl;
			cJpegAl = nullptr;
		}

		if(lpDibAlpha)
		{
			delete[] lpDibAlpha;
			lpDibAlpha = nullptr;
		}

		if(cTgaAl)
		{
			delete cTgaAl;
			cTgaAl = nullptr;
		}

		return NULL;
	}


	int i, j, k;
	int r, g, b, a, tp;
	BYTE *Dest;
	DWORD MaskAll;

	DWORD Mask[4];
	DWORD Shift[4];
	DWORD ShiftPixel[4];
	DWORD ShiftTemp;


	Mask[0] = ddTextureFormat.dwRBitMask;
	Mask[1] = ddTextureFormat.dwGBitMask;
	Mask[2] = ddTextureFormat.dwBBitMask;
	Mask[3] = ddTextureFormat.dwRGBAlphaBitMask;

	MaskAll = Mask[0] | Mask[1] | Mask[2] | Mask[3];

	for(i = 0; i < 4; i++)
	{
		if(Mask[i])
		{
			ShiftTemp = Mask[i];
			for(j = 0; j < 32; j++)
			{
				if(ShiftTemp & 1) break;
				ShiftTemp >>= 1;
			}
			Shift[i] = j;
			for(j = 0; j < 32; j++)
			{
				if((ShiftTemp & 1) == 0) break;
				ShiftTemp >>= 1;
			}
			ShiftPixel[i] = j;
		}
		else
		{
			Shift[i] = 32;
			ShiftPixel[i] = 32;
		}
	}



	int pBuff, pBuffAl;
	int incByte = 3;
	int incByteAl = 3;
	int pBuff_k;


	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	lpDDSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	Dest = (BYTE *)ddsd.lpSurface;

	if(!Dest) goto Lop_Quit;


	pBuff_k = 0;
	k = 0;
	for(i = 0; i < height; i++)
	{
		switch(BitCnt)
		{
		case 24:
			if(SwapHeight) pBuff = (height - i - 1)*width * 3;
			else pBuff = i*width * 3;
			incByte = 3;
			break;
		case 32:
			if(SwapHeight) pBuff = ((height - i - 1)*width) << 2;
			else pBuff = (i*width) << 2;
			incByte = 4;
			break;
		}

		switch(AlphaBitCnt)
		{
		case 8:
			if(SwapHeightAl) pBuffAl = (height - i - 1)*width;
			else pBuffAl = i*width;
			incByteAl = 1;
			break;

		case 24:
			if(SwapHeightAl) pBuffAl = (height - i - 1)*width * 3;
			else pBuffAl = i*width * 3;
			incByteAl = 3;
			break;

		case 32:
			if(SwapHeightAl) pBuffAl = ((height - i - 1)*width) << 2;
			else pBuffAl = (i*width) << 2;
			incByteAl = 4;
			break;
		}



		k = pBuff_k;

		if(dAddr)
		{
			for(j = 0; j < width; j++)
			{

				b = dAddr[pBuff];
				g = dAddr[pBuff + 1];
				r = dAddr[pBuff + 2];

				if(BitCnt == 32)
					a = dAddr[pBuff + 3];
				else
				{
					a = 255;

					if(dAddrAlpha)
					{
						switch(AlphaBitCnt)
						{
						case 8:
							a = dAddrAlpha[pBuffAl];
							break;
						case 24:
						case 32:
							a = dAddrAlpha[pBuffAl] + dAddrAlpha[pBuffAl + 1] + dAddrAlpha[pBuffAl + 2];
							a /= 3;
							break;
						}
					}
					pBuffAl += incByteAl;
				}

				pBuff += incByte;

				r = ((r >> (8 - ShiftPixel[0])) << Shift[0]) & Mask[0];
				g = ((g >> (8 - ShiftPixel[1])) << Shift[1]) & Mask[1];
				b = ((b >> (8 - ShiftPixel[2])) << Shift[2]) & Mask[2];
				a = ((a >> (8 - ShiftPixel[3])) << Shift[3]) & Mask[3];

				tp = r | g | b | a;




				if(MaskAll <= 0xFFFF)
				{
					*((WORD *)&Dest[k]) = (WORD)tp;
					k += 2;
				}
				else
				{
					*((DWORD *)&Dest[k]) = tp;
					k += 4;
				}
			}
		}
		pBuff_k += (int)ddsd.lPitch;

	}
	lpDDSurface->Unlock(NULL);

Lop_Quit:

	if(cJpeg)
	{
		delete cJpeg;
		cJpeg = nullptr;
	}

	if(lpDib)
	{
		delete[] lpDib;
		lpDib = nullptr;
	}

	if(cTga)
	{
		delete cTga;
		cTga = nullptr;
	}

	if(cJpegAl)
	{
		delete cJpegAl;
		cJpegAl = nullptr;
	}

	if(lpDibAlpha)
	{
		delete[] lpDibAlpha;
		lpDibAlpha = nullptr;
	}

	if(cTgaAl)
	{
		delete cTgaAl;
		cTgaAl = nullptr;
	}

	return lpDDSurface;
}



LPDIRECTDRAWSURFACE4 LoadDibSurface(char *Filename, int SysMem)
{
	BYTE* lpDib = LoadDib(Filename);

	if(!lpDib)
		return NULL;

	BYTE* dAddr = GetDibBitsAddr(lpDib);
	INT height = GetDibHeight(lpDib);
	INT width = GetDibWidth(lpDib);


	LPDIRECTDRAWSURFACE4 lpDDSurface;
	DDSURFACEDESC2 ddsd;

	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.dwWidth = width;
	ddsd.dwHeight = height;



	if(renderDevice.GetDeviceDesc_IsHardware() && SysMem == FALSE)
	{

		ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
		ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
	else
		ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;


	hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);

	if(hresult != DD_OK)
	{
		if(lpDib)
		{
			delete[] lpDib;
			lpDib = nullptr;
		}

		return NULL;
	}


	DrawSurfaceFromDib(lpDDSurface, lpDib);

	if(lpDib)
	{
		delete[] lpDib;
		lpDib = nullptr;
	}


	DDCOLORKEY ColKey;
	ColKey.dwColorSpaceLowValue = RGB(0, 0, 0);
	ColKey.dwColorSpaceHighValue = RGB(255, 255, 255);
	lpDDSurface->SetColorKey(DDCKEY_SRCBLT, &ColKey);

	return lpDDSurface;
}


int DrawSurfaceFromDib(LPDIRECTDRAWSURFACE4 lpDDSurface, BYTE *lpDib)
{
	int i, j, k;
	DWORD r, g, b, a, tp;
	BYTE *Dest;

	DWORD MaskAll;

	DWORD Mask[4];
	DWORD Shift[4];
	DWORD ShiftPixel[4];
	DWORD ShiftTemp;

	DDSURFACEDESC2 ddsd;
	DDPIXELFORMAT ddPixelFormat;

	BYTE *dAddr;
	int height, width;


	dAddr = GetDibBitsAddr(lpDib);
	height = GetDibHeight(lpDib);
	width = GetDibWidth(lpDib);


	ddPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	lpDDSurface->GetPixelFormat(&ddPixelFormat);

	Mask[0] = ddPixelFormat.dwRBitMask;
	Mask[1] = ddPixelFormat.dwGBitMask;
	Mask[2] = ddPixelFormat.dwBBitMask;
	Mask[3] = ddPixelFormat.dwRGBAlphaBitMask;

	MaskAll = Mask[0] | Mask[1] | Mask[2] | Mask[3];

	for(i = 0; i < 4; i++)
	{
		if(Mask[i])
		{
			ShiftTemp = Mask[i];
			for(j = 0; j < 32; j++)
			{
				if(ShiftTemp & 1) break;
				ShiftTemp >>= 1;
			}
			Shift[i] = j;
			for(j = 0; j < 32; j++)
			{
				if((ShiftTemp & 1) == 0) break;
				ShiftTemp >>= 1;
			}
			ShiftPixel[i] = j;
		}
		else
		{
			Shift[i] = 32;
			ShiftPixel[i] = 32;
		}
	}

	int pBuff;
	int pBuff_w;
	int pBuff_k;

	if(GetDibBitCount(lpDib) == 24)
	{
		ddsd.dwSize = sizeof(DDSURFACEDESC2);
		lpDDSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
		Dest = (BYTE *)ddsd.lpSurface;
		if(!Dest)
		{
			lpDDSurface->Unlock(NULL);
			return FALSE;
		}

		pBuff_w = 0;
		if((int)ddsd.lPitch != 0)
			pBuff_k = (int)ddsd.lPitch*(height - 1);
		else
		{
			if(MaskAll <= 0xFFFF)
				pBuff_k = width * (height - 1) * 2;
			else
				pBuff_k = width * (height - 1) * 4;
		}

		for(i = 0; i < height; i++)
		{

			k = pBuff_k;
			for(j = 0; j < width; j++)
			{


				pBuff = pBuff_w + (j * 3);
				b = dAddr[pBuff];
				g = dAddr[pBuff + 1];
				r = dAddr[pBuff + 2];
				a = 255;

				if((r + g + b) > 0 && r < 9 && g < 9 && b < 9)
				{
					r = g = b = 9;
				}

				r = ((r >> (8 - ShiftPixel[0])) << Shift[0]) & Mask[0];
				g = ((g >> (8 - ShiftPixel[1])) << Shift[1]) & Mask[1];
				b = ((b >> (8 - ShiftPixel[2])) << Shift[2]) & Mask[2];
				a = ((a >> (8 - ShiftPixel[3])) << Shift[3]) & Mask[3];

				tp = r | g | b | a;

				if(MaskAll <= 0xFFFF)
				{
					*((WORD *)&Dest[k]) = (WORD)tp;
					k += 2;
				}
				else
				{
					*((DWORD *)&Dest[k]) = tp;
					k += 4;
				}

			}
			pBuff_w = ((pBuff_w + width * 3) + 3) & 0xFFFFFFFC;
			pBuff_k -= (int)ddsd.lPitch;
		}
		lpDDSurface->Unlock(NULL);
	}




	return TRUE;
}




int DrawSurfaceFromJpeg(LPDIRECTDRAWSURFACE4 lpDDSurface, CJpeg *cJpeg)
{


	int i, j, k;
	DWORD r, g, b, a, tp;
	BYTE *Dest;

	DWORD MaskAll;


	DWORD Mask[4];
	DWORD Shift[4];
	DWORD ShiftPixel[4];
	DWORD ShiftTemp;

	DDSURFACEDESC2 ddsd;
	DDPIXELFORMAT ddPixelFormat;

	BYTE *dAddr;
	int height, width;


	ddPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	lpDDSurface->GetPixelFormat(&ddPixelFormat);

	dAddr = cJpeg->m_pData;
	height = cJpeg->GetHeight();
	width = cJpeg->GetWidth();

	Mask[0] = ddPixelFormat.dwRBitMask;
	Mask[1] = ddPixelFormat.dwGBitMask;
	Mask[2] = ddPixelFormat.dwBBitMask;
	Mask[3] = ddPixelFormat.dwRGBAlphaBitMask;



	MaskAll = Mask[0] | Mask[1] | Mask[2] | Mask[3];


	for(i = 0; i < 4; i++)
	{
		if(Mask[i])
		{
			ShiftTemp = Mask[i];
			for(j = 0; j < 16; j++)
			{
				if(ShiftTemp & 1) break;
				ShiftTemp >>= 1;
			}
			Shift[i] = j;
			for(j = 0; j < 16; j++)
			{
				if((ShiftTemp & 1) == 0) break;
				ShiftTemp >>= 1;
			}
			ShiftPixel[i] = j;
		}
		else
		{
			Shift[i] = 16;
			ShiftPixel[i] = 16;
		}
	}

	int pBuff;

	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	lpDDSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	Dest = (BYTE *)ddsd.lpSurface;

	k = 0;
	for(i = 0; i < height; i++)
	{
		if((int)ddsd.lPitch != 0) k = ((int)ddsd.lPitch*i);
		for(j = 0; j < width; j++)
		{

			pBuff = (height - i - 1)*width * 3 + (j * 3);
			b = dAddr[pBuff];
			g = dAddr[pBuff + 1];
			r = dAddr[pBuff + 2];
			a = 255;

			r = ((r >> (8 - ShiftPixel[0])) << Shift[0]) & Mask[0];
			g = ((g >> (8 - ShiftPixel[1])) << Shift[1]) & Mask[1];
			b = ((b >> (8 - ShiftPixel[2])) << Shift[2]) & Mask[2];
			a = ((a >> (8 - ShiftPixel[3])) << Shift[3]) & Mask[3];

			tp = r | g | b | a;



			if(MaskAll <= 0xFFFF)
			{
				*((WORD *)&Dest[k]) = (WORD)tp;
				k += 2;
			}
			else
			{
				*((DWORD *)&Dest[k]) = tp;
				k += 4;
			}

		}
	}
	lpDDSurface->Unlock(NULL);


	return TRUE;
}



int DrawSurfaceFromTga(LPDIRECTDRAWSURFACE4 lpDDSurface, cTGA *cTga)
{


	int i, j, k;
	int r, g, b, a, tp;
	BYTE *Dest;
	int SwapHeight;

	DWORD MaskAll;


	DWORD Mask[4];
	DWORD Shift[4];
	DWORD ShiftPixel[4];
	DWORD ShiftTemp;

	DDSURFACEDESC2 ddsd;
	DDPIXELFORMAT ddPixelFormat;

	BYTE *dAddr;
	int height, width;

	dAddr = cTga->m_pData;
	height = cTga->GetHeight();
	width = cTga->GetWidth();
	SwapHeight = cTga->SwapHeight;


	ddPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	lpDDSurface->GetPixelFormat(&ddPixelFormat);


	Mask[0] = ddPixelFormat.dwRBitMask;
	Mask[1] = ddPixelFormat.dwGBitMask;
	Mask[2] = ddPixelFormat.dwBBitMask;
	Mask[3] = ddPixelFormat.dwRGBAlphaBitMask;



	MaskAll = Mask[0] | Mask[1] | Mask[2] | Mask[3];


	for(i = 0; i < 4; i++)
	{
		if(Mask[i])
		{
			ShiftTemp = Mask[i];
			for(j = 0; j < 16; j++)
			{
				if(ShiftTemp & 1) break;
				ShiftTemp >>= 1;
			}
			Shift[i] = j;
			for(j = 0; j < 16; j++)
			{
				if((ShiftTemp & 1) == 0) break;
				ShiftTemp >>= 1;
			}
			ShiftPixel[i] = j;
		}
		else
		{
			Shift[i] = 16;
			ShiftPixel[i] = 16;
		}
	}

	int pBuff;

	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	lpDDSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	Dest = (BYTE *)ddsd.lpSurface;

	k = 0;
	for(i = 0; i < height; i++)
	{
		if((int)ddsd.lPitch != 0) k = ((int)ddsd.lPitch*i);
		for(j = 0; j < width; j++)
		{

			if(SwapHeight) pBuff = (height - i - 1)*width + j;
			else pBuff = i*width + j;

			pBuff *= 3;

			b = dAddr[pBuff];
			g = dAddr[pBuff + 1];
			r = dAddr[pBuff + 2];
			a = 255;

			r = ((r >> (8 - ShiftPixel[0])) << Shift[0]) & Mask[0];
			g = ((g >> (8 - ShiftPixel[1])) << Shift[1]) & Mask[1];
			b = ((b >> (8 - ShiftPixel[2])) << Shift[2]) & Mask[2];
			a = ((a >> (8 - ShiftPixel[3])) << Shift[3]) & Mask[3];

			tp = r | g | b | a;



			if(MaskAll <= 0xFFFF)
			{
				*((WORD *)&Dest[k]) = (WORD)tp;
				k += 2;
			}
			else
			{
				*((DWORD *)&Dest[k]) = tp;
				k += 4;
			}

		}
	}
	lpDDSurface->Unlock(NULL);


	return TRUE;
}





int MipMapCreateTextureCheck(int width, int height, int MipMapCount)
{
	if(width > 256 || height > 256)
		return 0;

	switch(MipMapCount)
	{
	case 5:
		if(width == 256 && height == 256)
			return 1;
		break;

	case 4:
		if(width >= 128 && height >= 128)
			return 1;
		break;

	case 3:
		if(width >= 64 && height >= 64)
			return 1;
		break;

	case 2:
		if(width >= 32 && height >= 32)
			return 1;
		break;

	case 1:
		return 0;

	default:
		return 0;
	}

	return 0;
}









int smCreateTexture(smTEXTUREHANDLE *lpTexHandle, int MipMap)
{
	MipMapCount = 0;
	::ZeroMemory(MipMapFileBuff, sizeof(MipMapFileBuff));
	MipMapCountA = 0;
	::ZeroMemory(MipMapFileABuff, sizeof(MipMapFileABuff));
	::ZeroMemory(FileTypeBuff, sizeof(FileTypeBuff));

	char szMipMapFileError[256] = { "MipMap File Error : " };


	BYTE *dAddr;
	int height, width;
	int height2, width2;
	int TexSwap;


	LPDIRECT3DTEXTURE2 lpD3DTexture;
	LPDIRECTDRAWSURFACE4 lpDDSurface;
	LPDIRECTDRAWSURFACE4 lpDDSurface2;
	DDSURFACEDESC2 ddsd;


	CJpeg *cJpeg = nullptr;
	cTGA *cTga = nullptr;
	int TgaBitCount = 0;

	BYTE *lpDib = 0;
	int TexHalf = 0;

	char *Filename = lpTexHandle->Name;
	int FileType = GetTextureFileType(Filename);

	if(FileType < 0)
		return -1;

	switch(FileType)
	{
	case smTEXFILETYPE_TGA:
		cTga = new cTGA;

		if(cTga->LoadTga(Filename))
		{
			dAddr = cTga->m_pData;
			width = cTga->GetWidth();
			height = cTga->GetHeight();
			TgaBitCount = cTga->GetBitCount();
		}
		else
		{
			if(cTga)
			{
				delete cTga;
				cTga = nullptr;
			}

			return -1;
		}



		strcpy_s(FileTypeBuff, sizeof(FileTypeBuff), ".tga");

		break;

	case smTEXFILETYPE_JPG:
		cJpeg = new CJpeg;
		cJpeg->LoadJPG(Filename);


		if(!cJpeg->m_pData)
		{
			if(cJpeg)
			{
				delete cJpeg;
				cJpeg = nullptr;
			}

			return -1;
		}


		dAddr = cJpeg->m_pData;
		width = cJpeg->GetWidth();
		height = cJpeg->GetHeight();



		strcpy_s(FileTypeBuff, sizeof(FileTypeBuff), ".jpg");

		break;

	case smTEXFILETYPE_BMP:
		lpDib = LoadDib(Filename);

		if(lpDib == NULL)
			return -1;

		dAddr = GetDibBitsAddr(lpDib);
		height = GetDibHeight(lpDib);
		width = GetDibWidth(lpDib);



		strcpy_s(FileTypeBuff, sizeof(FileTypeBuff), ".bmp");

		break;

	}

	TexSwap = FALSE;

	lpTexHandle->Width = width;
	lpTexHandle->Height = height;

	if(MipMap && MipMapModeCreate && width < 512 && height < 512)
	{
		if(MipMapModeCreate == NOSQUARE_MODE || width == height)
		{
			int len = ::lstrlen(Filename);
			for(int i = len - 1; i >= 0; i--)
			{
				if(Filename[i] == '.')
				{
					CopyMemory(MipMapFileBuff[0], Filename, i);
					break;
				}
			}

			for(int i = 1; i < MIPMAP_FILELIST; i++)
			{
				strcpy_s(MipMapFileBuff[i], sizeof(MipMapFileBuff[i]), MipMapFileBuff[0]);
				strcat_s(MipMapFileBuff[i], sizeof(MipMapFileBuff[i]), MipMapFileListBuff[i]);
				strcat_s(MipMapFileBuff[i], sizeof(MipMapFileBuff[i]), FileTypeBuff);

				if(PathFileExists(MipMapFileBuff[i]))
					MipMapCount++;
				else
					break;
			}

			strcat_s(MipMapFileBuff[0], sizeof(MipMapFileBuff[0]), FileTypeBuff);
		}
	}


	if(!lpTexHandle->NameA[0] && TgaBitCount < 32)
	{

		ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));



		if(MipMapCount)
		{
			MipMapCount++;

			if(MipMapCreateTextureCheck(width, height, MipMapCount) <= 0)
			{
				if(cJpeg)
				{
					delete cJpeg;
					cJpeg = nullptr;
				}

				if(cTga)
				{
					delete cTga;
					cTga = nullptr;
				}

				if(lpDib)
				{
					delete[] lpDib;
					lpDib = nullptr;
				}

				strcat_s(szMipMapFileError, sizeof(szMipMapFileError), Filename);
				//(szMipMapFileError);
				return NULL;
			}

			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT;
			ddsd.dwWidth = width;
			ddsd.dwHeight = height;
			ddsd.dwMipMapCount = MipMapCount;
			ddsd.ddsCaps.dwCaps = DDSCAPS_MIPMAP | DDSCAPS_COMPLEX | DDSCAPS_TEXTURE;
			ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
		}
		else
		{
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
			ddsd.dwWidth = width;
			ddsd.dwHeight = height;

			if(renderDevice.GetDeviceDesc_IsHardware() && TexSwap == FALSE)
			{

				ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
				ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
			}
			else
				ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;
		}


		memcpy(&ddsd.ddpfPixelFormat, &ddDefaultTextureFormat, sizeof(DDPIXELFORMAT));

		hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);
		width2 = width;
		height2 = height;



		if(hresult != DD_OK)
		{
			if(TexSwap == FALSE && (width > 256 || height > 256))
			{


				if(renderDevice.GetDeviceDesc_IsHardware())
				{
					ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;

					hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);
					if(hresult == DD_OK) TexHalf = TRUE;
				}

			}

			if(hresult != DD_OK)
			{
				if(cJpeg)
				{
					delete cJpeg;
					cJpeg = nullptr;
				}

				if(cTga)
				{
					delete cTga;
					cTga = nullptr;
				}

				if(lpDib)
				{
					delete[] lpDib;
					lpDib = nullptr;
				}
				return NULL;
			}
		}



		if(lpDib)
		{
			DrawSurfaceFromDib(lpDDSurface, lpDib);
			delete[] lpDib;
			lpDib = nullptr;

		}

		if(cJpeg)
		{
			DrawSurfaceFromJpeg(lpDDSurface, cJpeg);
			delete cJpeg;
			cJpeg = nullptr;
		}

		if(cTga)
		{
			DrawSurfaceFromTga(lpDDSurface, cTga);
			delete cTga;
			cTga = nullptr;

		}

		DDSCAPS2 ddsCaps = { 0, };
		ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;

		lpDDSurface2 = lpDDSurface;
		for(int i = 1; i < MipMapCount; i++)
		{
			LPDIRECTDRAWSURFACE4 lpDDNextLevel = NULL;
			if(FAILED(lpDDSurface2->GetAttachedSurface(&ddsCaps, &lpDDNextLevel)))
			{
				lpDDSurface->Release();
				return NULL;
			}

			width2 >>= 1;
			height2 >>= 1;

			switch(FileType)
			{
			case smTEXFILETYPE_BMP:
				lpDib = LoadDib(MipMapFileBuff[i]);
				if(lpDib == NULL)
				{
					lpDDNextLevel->Release();
					lpDDSurface->Release();
					return NULL;
				}

				if(width2 != GetDibWidth(lpDib) || height2 != GetDibHeight(lpDib))
				{
					lpDDNextLevel->Release();
					lpDDSurface->Release();

					strcat_s(szMipMapFileError, sizeof(szMipMapFileError), MipMapFileBuff[i]);
					//MESSAGE(szMipMapFileError);
					return NULL;
				}

				DrawSurfaceFromDib(lpDDNextLevel, lpDib);

				if(lpDib)
				{
					delete[] lpDib;
					lpDib = nullptr;
				}

				break;

			case smTEXFILETYPE_JPG:
				cJpeg = new CJpeg;
				cJpeg->LoadJPG(MipMapFileBuff[i]);

				if(!cJpeg->m_pData)
				{
					if(cJpeg)
					{
						delete cJpeg;
						cJpeg = nullptr;
					}

					lpDDNextLevel->Release();
					lpDDSurface->Release();
					return NULL;
				}

				if(width2 != cJpeg->GetWidth() || height2 != cJpeg->GetHeight())
				{
					if(cJpeg)
					{
						delete cJpeg;
						cJpeg = nullptr;
					}

					lpDDNextLevel->Release();
					lpDDSurface->Release();

					strcat_s(szMipMapFileError, sizeof(szMipMapFileError), MipMapFileBuff[i]);
					//MESSAGE(szMipMapFileError);
					return NULL;
				}

				DrawSurfaceFromJpeg(lpDDNextLevel, cJpeg);
				if(cJpeg)
				{
					delete cJpeg;
					cJpeg = nullptr;
				}
				break;

			case smTEXFILETYPE_TGA:
				cTga = new cTGA;
				cTga->LoadTga(MipMapFileBuff[i]);

				if(cTga->m_pBuff == NULL)
				{
					if(cTga)
					{
						delete cTga;
						cTga = nullptr;
					}

					lpDDNextLevel->Release();
					lpDDSurface->Release();
					return NULL;
				}

				if(width2 != cTga->GetWidth() || height2 != cTga->GetHeight())
				{
					if(cTga)
					{
						delete cTga;
						cTga = nullptr;
					}

					lpDDNextLevel->Release();
					lpDDSurface->Release();

					strcat_s(szMipMapFileError, sizeof(szMipMapFileError), MipMapFileBuff[i]);
					//MESSAGE(szMipMapFileError);
					return NULL;
				}

				DrawSurfaceFromTga(lpDDNextLevel, cTga);

				if(cTga)
				{
					delete cTga;
					cTga = nullptr;
				}

				break;
			}

			lpDDSurface2 = lpDDNextLevel;
			lpDDNextLevel->Release();
		}

		lpDDSurface2 = NULL;


		lpTexHandle->MapOpacity = FALSE;
	}
	else
	{

		if(cJpeg)
		{
			delete cJpeg;
			cJpeg = nullptr;
		}

		if(lpDib)
		{
			delete[] lpDib;
			lpDib = nullptr;
		}

		if(cTga)
		{
			delete cTga;
			cTga = nullptr;
		}


		if(MipMapCount)
		{
			if(lpTexHandle->NameA[0])
			{
				ZeroMemory(FileTypeBuff, sizeof(FileTypeBuff));

				int len = lstrlen(lpTexHandle->NameA);

				for(int i = len - 1; i >= 0; i--)
				{
					if(lpTexHandle->NameA[i] == '.')
					{
						CopyMemory(MipMapFileABuff[0], lpTexHandle->NameA, i);

						if(_stricmp(&lpTexHandle->NameA[i], ".bmp") == 0)
							strcpy_s(FileTypeBuff, sizeof(FileTypeBuff), ".bmp");
						else if(_stricmp(&lpTexHandle->NameA[i], ".jpg") == 0)
							strcpy_s(FileTypeBuff, sizeof(FileTypeBuff), ".jpg");
						else if(_stricmp(&lpTexHandle->NameA[i], ".tga") == 0)
							strcpy_s(FileTypeBuff, sizeof(FileTypeBuff), ".tga");
						else
							return -1;
						break;
					}
				}

				for(int i = 1; i < MIPMAP_FILELIST; i++)
				{
					strcpy_s(MipMapFileABuff[i], sizeof(MipMapFileABuff[i]), MipMapFileABuff[0]);
					strcat_s(MipMapFileABuff[i], sizeof(MipMapFileABuff[i]), MipMapFileListBuff[i]);
					strcat_s(MipMapFileABuff[i], sizeof(MipMapFileABuff[i]), FileTypeBuff);

					if(PathFileExists(MipMapFileABuff[i]))
						MipMapCountA++;
					else
						break;
				}

				strcat_s(MipMapFileABuff[0], sizeof(MipMapFileABuff[0]), FileTypeBuff);


				if(MipMapCount != MipMapCountA)
					return -1;

				MipMapCountA++;
			}

			MipMapCount++;









			if(MipMapCreateTextureCheck(width, height, MipMapCount) <= 0)
			{
				strcat_s(szMipMapFileError, sizeof(szMipMapFileError), Filename);
				//MESSAGE(szMipMapFileError);
				return -2;
			}


			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT;
			ddsd.dwWidth = width;
			ddsd.dwHeight = height;
			ddsd.dwMipMapCount = MipMapCount;
			ddsd.ddsCaps.dwCaps = DDSCAPS_MIPMAP | DDSCAPS_COMPLEX | DDSCAPS_TEXTURE;
			ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
			memcpy(&ddsd.ddpfPixelFormat, &ddTextureFormat, sizeof(DDPIXELFORMAT));

			hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);
			if(hresult != DD_OK)
				return -2;

			width2 = width;
			height2 = height;
			if(LoadDibSurfaceAlphaMipMap(lpDDSurface, MipMapFileBuff[0], MipMapFileABuff[0], width2, height2) == FALSE)
			{
				lpDDSurface->Release();
				return -2;
			}

			DDSCAPS2 ddsCaps = { 0, };
			ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;

			lpDDSurface2 = lpDDSurface;
			for(int i = 1; i < MipMapCount; i++)
			{
				LPDIRECTDRAWSURFACE4 lpDDNextLevel = NULL;
				if(FAILED(lpDDSurface2->GetAttachedSurface(&ddsCaps, &lpDDNextLevel)))
				{
					lpDDSurface->Release();
					return -2;
				}

				width2 >>= 1;
				height2 >>= 1;

				int ErrorAlphaMipMap = LoadDibSurfaceAlphaMipMap(lpDDNextLevel, MipMapFileBuff[i], MipMapFileABuff[i], width2, height2);
				if(ErrorAlphaMipMap == -1)
				{
					lpDDNextLevel->Release();
					lpDDSurface->Release();

					strcat_s(szMipMapFileError, sizeof(szMipMapFileError), MipMapFileBuff[i]);
					//MESSAGE(szMipMapFileError);
					return -2;
				}
				else if(ErrorAlphaMipMap == -2)
				{
					lpDDNextLevel->Release();
					lpDDSurface->Release();

					strcat_s(szMipMapFileError, sizeof(szMipMapFileError), MipMapFileABuff[i]);
					//MESSAGE(szMipMapFileError);
					return -2;
				}

				lpDDSurface2 = lpDDNextLevel;
				lpDDNextLevel->Release();
			}

			if(!lpTexHandle->NameA[0])
				lpTexHandle->NameA[0] = TRUE;

			lpDDSurface2 = NULL;
		}
		else
		{
			lpDDSurface = LoadDibSurfaceAlpha(Filename, lpTexHandle->NameA, TexSwap);
			if(!lpTexHandle->NameA[0]) lpTexHandle->NameA[0] = TRUE;
			if(lpDDSurface == NULL)
				return -2;
		}


		lpTexHandle->MapOpacity = TRUE;
	}


	if(TexSwap == TRUE || TexHalf || (TexturHalfSize && width > 32 && height > 32 && lpTexHandle->TexSwapMode))
	{
		if(TexturHalfSize == 2)
		{
			width2 = width / 4;
			height2 = height / 4;
		}
		else
		{
			width2 = width / 2;
			height2 = height / 2;
		}

		ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
		ddsd.dwSize = sizeof(DDSURFACEDESC2);
		ddsd.dwWidth = width2;
		ddsd.dwHeight = height2;
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;


		if(lpTexHandle->MapOpacity)
		{
			memcpy(&ddsd.ddpfPixelFormat, &ddTextureFormat, sizeof(DDPIXELFORMAT));
		}
		else
		{
			memcpy(&ddsd.ddpfPixelFormat, &ddDefaultTextureFormat, sizeof(DDPIXELFORMAT));
		}



		if(renderDevice.GetDeviceDesc_IsHardware())
		{

			ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
			ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
		}
		else
			ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;


		hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface2, NULL);
		if(hresult != DD_OK)
		{
			lpDDSurface->Release();
			return NULL;
		}





		RECT srcRect, destRect;

		srcRect.top = 0;
		srcRect.left = 0;
		srcRect.right = width;
		srcRect.bottom = height;

		destRect.top = 0;
		destRect.left = 0;
		destRect.right = width2;
		destRect.bottom = height2;

		lpDDSurface2->Blt(&destRect, lpDDSurface, &srcRect, DDBLT_WAIT, NULL);

















		lpTexHandle->lpDDSurface = lpDDSurface2;
		lpTexHandle->lpDDSSysMemory = NULL;

		if(lpDDSurface2 != NULL)
		{
			hresult = lpDDSurface2->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&lpD3DTexture);
			if(hresult == D3D_OK)
				lpTexHandle->lpD3DTexture = lpD3DTexture;
			else
			{
				lpDDSurface2->Release();
				lpTexHandle->lpDDSurface = NULL;
				return 0;
			}
		}



		VramTotal += width2 * height2 * 2;

		return TRUE;
	}

	lpTexHandle->lpDDSurface = lpDDSurface;
	lpTexHandle->lpDDSSysMemory = NULL;
	if(lpDDSurface != NULL)
	{
		hresult = lpDDSurface->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&lpD3DTexture);
		if(hresult == D3D_OK)
			lpTexHandle->lpD3DTexture = lpD3DTexture;
		else
		{
			lpDDSurface->Release();
			lpTexHandle->lpDDSurface = NULL;
			return 0;
		}
	}


	VramTotal += width * height * 2;

	return TRUE;
}


extern HWND hwnd;


LPDIRECTDRAWSURFACE4 LoadDibSurfaceOffscreen(char *Filename)
{
	return new_LoadBmpSurfaceOffscreen(Filename);


	BYTE* lpDib = LoadDib(Filename);

	if(!lpDib)
		return NULL;

	BYTE* dAddr = GetDibBitsAddr(lpDib);
	int width = GetDibWidth(lpDib);
	int height = GetDibHeight(lpDib);



	LPDIRECTDRAWSURFACE4 lpDDSurface;
	DDSURFACEDESC2 ddsd;

	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.dwWidth = width;
	ddsd.dwHeight = height;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

	hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);

	if(hresult != DD_OK)
	{
		if(lpDib)
		{
			delete[] lpDib;
			lpDib = nullptr;
		}

		return NULL;
	}

	DrawSurfaceFromDib(lpDDSurface, lpDib);

	if(lpDib)
	{
		delete[] lpDib;
		lpDib = nullptr;
	}


	DDCOLORKEY ColKey;
	ColKey.dwColorSpaceLowValue = RGB(0, 0, 0);
	ColKey.dwColorSpaceHighValue = RGB(255, 255, 255);
	lpDDSurface->SetColorKey(DDCKEY_SRCBLT, &ColKey);

	return lpDDSurface;
}


LPDIRECTDRAWSURFACE4 lpDDSMapTexture[256];
LPDIRECTDRAWSURFACE4 lpDDSMapTextureVideo[8 * 8];
LPDIRECT3DTEXTURE2 lpD3DMapTexture[8 * 8];

int MapTexCode[8][8];

int MapTextureSize;

int LoadDibMapTexture(char *Filename, int tSize)
{

	BYTE *lpDib;
	BYTE *dAddr;
	int height, width;


	lpDib = LoadDib(Filename);
	if(lpDib == NULL) return NULL;

	dAddr = GetDibBitsAddr(lpDib);
	height = GetDibHeight(lpDib);
	width = GetDibWidth(lpDib);

	MapTextureSize = tSize;

	int cnt;


	DDSURFACEDESC2 ddsd;

	for(cnt = 0; cnt < 64; cnt++)
	{
		ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

		ddsd.dwSize = sizeof(DDSURFACEDESC2);
		ddsd.dwFlags = DDSD_CAPS |
			DDSD_HEIGHT |
			DDSD_WIDTH;
		ddsd.dwWidth = tSize;
		ddsd.dwHeight = tSize;



		if(renderDevice.GetDeviceDesc_IsHardware())
		{

			ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
			ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
		}
		else
			ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;


		hresult = renderDevice.CreateSurface(&ddsd, &lpDDSMapTextureVideo[cnt], NULL);
		if(hresult != DD_OK)
		{
			if(lpDib)
			{
				delete[] lpDib;
				lpDib = nullptr;
			}

			return NULL;
		}
	}

	for(cnt = 0; cnt < 256; cnt++)
	{
		ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

		ddsd.dwSize = sizeof(DDSURFACEDESC2);
		ddsd.dwFlags = DDSD_CAPS |
			DDSD_HEIGHT |
			DDSD_WIDTH;
		ddsd.dwWidth = tSize;
		ddsd.dwHeight = tSize;

		ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;

		hresult = renderDevice.CreateSurface(&ddsd, &lpDDSMapTexture[cnt], NULL);
		if(hresult != DD_OK)
		{
			if(lpDib)
			{
				delete[] lpDib;
				lpDib = nullptr;
			}

			return NULL;
		}
	}


	HBITMAP TempBitmap;
	HDC TempDC;
	HDC BitmapDC;
	HDC hdc = NULL;
	int cntX, cntY, cntH;
	RECT ddRect;


	TempDC = GetDC(hwnd);
	TempBitmap = CreateCompatibleBitmap(TempDC, width, height);
	BitmapDC = CreateCompatibleDC(TempDC);
	SelectObject(BitmapDC, TempBitmap);
	SetDIBitsToDevice(BitmapDC, 0, 0, width, height, 0, 0, 0, height, (LPSTR)dAddr, (LPBITMAPINFO)lpDib, DIB_RGB_COLORS);

	cnt = 0;
	for(cntY = 0; cntY < 16; cntY++)
	{
		cntH = 15 - cntY;
		for(cntX = 0; cntX < 16; cntX++)
		{

			//lpDDSMapTexture[cnt]->GetDC(&hdc);

			BitBlt(hdc, 1, 1, tSize - 2, tSize - 2, BitmapDC, cntX*(tSize - 2), cntH*(tSize - 2), SRCCOPY);

			BitBlt(hdc, 0, 0, tSize, 1, BitmapDC, cntX*(tSize - 2), cntH*(tSize - 2), SRCCOPY);
			BitBlt(hdc, 0, tSize - 1, tSize, 1, BitmapDC, cntX*(tSize - 2), cntH*(tSize - 2) + (tSize - 1), SRCCOPY);

			BitBlt(hdc, 0, 0, 1, tSize, BitmapDC, cntX*(tSize - 2), cntH*(tSize - 2), SRCCOPY);
			BitBlt(hdc, tSize - 1, 0, 1, tSize, BitmapDC, cntX*(tSize - 2) + (tSize - 1), cntH*(tSize - 2), SRCCOPY);

			//lpDDSMapTexture[cnt]->ReleaseDC(hdc);
			cnt++;
		}
	}

	DeleteDC(BitmapDC);
	DeleteObject(TempBitmap);
	ReleaseDC(hwnd, TempDC);

	if(lpDib)
	{
		delete[] lpDib;
		lpDib = nullptr;
	}


	for(cnt = 0; cnt < 64; cnt++)
	{
		hresult = lpDDSMapTextureVideo[cnt]->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&lpD3DMapTexture[cnt]);
		if(hresult != D3D_OK)
		{
			lpDDSMapTextureVideo[cnt]->Release();
			lpDDSMapTextureVideo[cnt] = 0;
			lpD3DMapTexture[cnt] = 0;
			return NULL;
		}
	}



	for(cntY = 0; cntY < 8; cntY++)
	{
		for(cntX = 0; cntX < 8; cntX++)
		{


			ddRect.left = 0;
			ddRect.right = tSize;
			ddRect.top = 0;
			ddRect.bottom = tSize;


			lpDDSMapTextureVideo[cntX + (cntY * 8)]->BltFast(0, 0, lpDDSMapTexture[cntX + (cntY * 16)], &ddRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

			MapTexCode[cntX][cntY] = cntX + (cntY * 16);

		}
	}


	return TRUE;

}

int RemoveMapTexture()
{
	int cnt;

	for(cnt = 63; cnt >= 0; cnt--)
	{
		lpD3DMapTexture[cnt]->Release();
		lpDDSMapTextureVideo[cnt]->Release();
	}

	for(cnt = 255; cnt >= 0; cnt--)
	{
		lpDDSMapTexture[cnt]->Release();
	}

	return TRUE;
}



int SetMapTextureMem(int x, int y)
{

	RECT ddRect;
	int mx, my;
	int vx, vy;
	int ddval;
	int sc, dc;

	ddRect.left = 0;
	ddRect.right = MapTextureSize;
	ddRect.top = 0;
	ddRect.bottom = MapTextureSize;

	mx = x & 15;
	my = y & 15;

	vx = x & 7;
	vy = y & 7;

	dc = vx + (vy << 3);
	sc = mx + (my << 4);

	if(MapTexCode[vx][vy] != sc)
	{
		ddval = lpDDSMapTextureVideo[dc]->BltFast(0, 0, lpDDSMapTexture[sc], &ddRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		MapTexCode[vx][vy] = sc;
	}

	return ddval;
}

int SetMapTextureWidth(int x, int y)
{
	int cnt;

	for(cnt = 0; cnt < 8; cnt++)
	{
		SetMapTextureMem(x + cnt, y);
	}

	return TRUE;
}

int SetMapTextureHeight(int x, int y)
{
	int cnt;

	for(cnt = 0; cnt < 8; cnt++)
	{
		SetMapTextureMem(x, y + cnt);
	}


	return TRUE;
}

int SetMapImage(int x, int y)
{
	int sx, sy;
	int cntX, cntY;

	sx = x >> (ShiftMAPCELL_DIV + 3);
	sy = y >> (ShiftMAPCELL_DIV + 3);


	for(cntX = sx - 3; cntX < sx + 4; cntX++)
	{
		for(cntY = sy - 3; cntY < sy + 4; cntY++)
		{
			SetMapTextureMem(cntX, cntY);
		}
	}



	return TRUE;

}








LPDIRECTDRAWSURFACE4 LoadDibBGTexture(char *Filename)
{

	BYTE *lpDib;
	BYTE *dAddr;
	int height, width;
	LPDIRECTDRAWSURFACE4 lpDDSurface;


	lpDib = LoadDib(Filename);
	if(lpDib == NULL) return NULL;

	dAddr = GetDibBitsAddr(lpDib);
	height = GetDibHeight(lpDib);
	width = GetDibWidth(lpDib);



	DDSURFACEDESC2 ddsd;

	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	ddsd.dwWidth = width + 2;
	ddsd.dwHeight = height;

	memcpy(&ddsd.ddpfPixelFormat, &ddDefaultTextureFormat, sizeof(DDPIXELFORMAT));

	ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;

	hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);
	if(hresult != DD_OK)
	{
		if(lpDib)
		{
			delete[] lpDib;
			lpDib = nullptr;
		}

		return NULL;
	}


	HBITMAP TempBitmap = NULL;
	HDC TempDC = NULL;
	HDC BitmapDC = NULL;
	HDC hdc = NULL;


	TempDC = GetDC(hwnd);
	TempBitmap = CreateCompatibleBitmap(TempDC, width, height);
	BitmapDC = CreateCompatibleDC(TempDC);
	SelectObject(BitmapDC, TempBitmap);
	SetDIBitsToDevice(BitmapDC, 0, 0, width, height, 0, 0, 0, height, (LPSTR)dAddr, (LPBITMAPINFO)lpDib, DIB_RGB_COLORS);

	lpDDSurface->GetDC(&hdc);

	BitBlt(hdc, 1, 0, width, height, BitmapDC, 0, 0, SRCCOPY);

	BitBlt(hdc, 0, 0, 1, height, BitmapDC, 0, 0, SRCCOPY);
	BitBlt(hdc, width + 1, 0, 1, height, BitmapDC, width - 1, 0, SRCCOPY);

	lpDDSurface->ReleaseDC(hdc);

	DeleteDC(BitmapDC);
	DeleteObject(TempBitmap);
	ReleaseDC(hwnd, TempDC);

	if(lpDib)
	{
		delete[] lpDib;
		lpDib = nullptr;
	}

	return lpDDSurface;

}


char *BGTextureName[32] = {
	"clo00.bmp",
	"clo01.bmp",
	"clo02.bmp",
	"clo03.bmp",
	"clo04.bmp",
	"clo05.bmp",
	"clo06.bmp",
	"clo07.bmp",
	"clo08.bmp",
	"clo09.bmp",
	"clo10.bmp",
	"clo11.bmp",
	"clo12.bmp",
	"clo13.bmp",
	"clo14.bmp",
	"clo15.bmp",
	"clo16.bmp",
	"clo17.bmp",
	"clo18.bmp",
	"clo19.bmp",
	"clo20.bmp",
	"clo21.bmp",
	"clo22.bmp",
	"clo23.bmp",
	"clo24.bmp",
	"clo25.bmp",
	"clo26.bmp",
	"clo27.bmp",
	"clo28.bmp",
	"clo29.bmp",
	"clo30.bmp",
	"clo31.bmp"
};


LPDIRECTDRAWSURFACE4 lpDDSAnimBG[32];

int DrawAnimBG(LPDIRECTDRAWSURFACE4 lpDDSSrc, int frame)
{

	RECT ddRect;
	int ddval;

	ddRect.left = 0;
	ddRect.right = 256;
	ddRect.top = 0;
	ddRect.bottom = 128;

	//ddval = lpDDSSrc->BltFast(0, 90, lpDDSAnimBG[frame & 0x1F], &ddRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	ddval = renderDevice.BltFast(lpDDSSrc, 0, 90, lpDDSAnimBG[frame & 0x1F], &ddRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

	return ddval;
}

int LoadAnimBG()
{
	int cnt;
	char strName[64];

	for(cnt = 0; cnt < 32; cnt++)
	{
		strcpy_s(strName, "cloud\\");
		lstrcat(strName, BGTextureName[cnt]);
		lpDDSAnimBG[cnt] = LoadDibBGTexture(strName);
	}

	return TRUE;
}

int ClearBG(LPDIRECTDRAWSURFACE4 lpDDSSrc, DWORD color)
{



	DDBLTFX bltFx;
	ZeroMemory(&bltFx, sizeof(DDBLTFX));
	bltFx.dwSize = sizeof(DDBLTFX);
	bltFx.dwFillColor = color;
	//lpDDSSrc->Blt(NULL, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &bltFx);
	renderDevice.Blt(lpDDSSrc, NULL, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &bltFx);

	return TRUE;

}

int CloseAnimBG()
{
	for(int cnt = 31; cnt >= 0; cnt--)
	{
		if(lpDDSAnimBG[cnt])
			lpDDSAnimBG[cnt]->Release();
	}

	return TRUE;
}



int new_smCreateTexture(smTEXTUREHANDLE *lpTexHandle, int MipMap)
{
	MipMapCount = 0;
	::ZeroMemory(MipMapFileBuff, sizeof(MipMapFileBuff));
	MipMapCountA = 0;
	::ZeroMemory(MipMapFileABuff, sizeof(MipMapFileABuff));
	::ZeroMemory(FileTypeBuff, sizeof(FileTypeBuff));

	char *Filename = lpTexHandle->Name;
	int FileType = GetTextureFileType(Filename);

	if(FileType < 0)
		return -1;

	int TexHalf = 0;
	LPDIRECTDRAWSURFACE4 lpDDSurface = NULL;

	if(FileType == smTEXFILETYPE_BMP)
	{
		lpDDSurface = new_LoadBmpCreateTexSurface(Filename, MipMap, TexHalf);

		if(lpDDSurface)
			lpTexHandle->MapOpacity = FALSE;
		else
			return -1;
	}
	else if(FileType == smTEXFILETYPE_TGA)
	{
		lpDDSurface = new_LoadTgaCreateTexSurface(Filename, MipMap, TexHalf);

		if(lpDDSurface)
		{
			lpTexHandle->MapOpacity = TRUE;

			if(!lpTexHandle->NameA[0])
				lpTexHandle->NameA[0] = TRUE;
		}
		else
			return -1;
	}
	else
		return -1;

	LPDIRECT3DTEXTURE2 lpD3DTexture;

	if(TexHalf || (TexturHalfSize && g_DibLastReadWidth > 32 && g_DibLastReadHeight > 32 && lpTexHandle->TexSwapMode))
	{
		int width2, height2;

		if(TexturHalfSize == 2)
		{
			width2 = g_DibLastReadWidth >> 2;
			height2 = g_DibLastReadHeight >> 2;
		}
		else
		{
			width2 = g_DibLastReadWidth >> 1;
			height2 = g_DibLastReadHeight >> 1;
		}

		DDSURFACEDESC2 ddsd;
		ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

		ddsd.dwSize = sizeof(DDSURFACEDESC2);
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		ddsd.dwWidth = width2;
		ddsd.dwHeight = height2;

		if(FileType == smTEXFILETYPE_BMP)
			memcpy(&ddsd.ddpfPixelFormat, &ddDefaultTextureFormat, sizeof(DDPIXELFORMAT));
		else
			memcpy(&ddsd.ddpfPixelFormat, &ddTextureFormat, sizeof(DDPIXELFORMAT));

		if(renderDevice.GetDeviceDesc_IsHardware())
		{
			ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
			ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
		}
		else
			ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;

		LPDIRECTDRAWSURFACE4 lpDDSurface2;
		hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface2, NULL);
		if(hresult != DD_OK)
		{
			lpDDSurface->Release();
			lpTexHandle->lpDDSurface = NULL;
			return 0;
		}


		RECT srcRect, destRect;

		srcRect.top = 0;
		srcRect.left = 0;
		srcRect.right = g_DibLastReadWidth;
		srcRect.bottom = g_DibLastReadHeight;

		destRect.top = 0;
		destRect.left = 0;
		destRect.right = width2;
		destRect.bottom = height2;

		lpDDSurface2->Blt(&destRect, lpDDSurface, &srcRect, DDBLT_WAIT, NULL);
		lpDDSurface->Release();

		g_DibLastReadWidth = width2;
		g_DibLastReadHeight = height2;

		lpTexHandle->Width = width2;
		lpTexHandle->Height = height2;
		lpTexHandle->lpDDSurface = lpDDSurface2;
		lpTexHandle->lpDDSSysMemory = NULL;

		hresult = lpDDSurface2->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&lpD3DTexture);
		if(hresult == D3D_OK)
			lpTexHandle->lpD3DTexture = lpD3DTexture;
		else
		{
			lpDDSurface2->Release();
			lpTexHandle->lpDDSurface = NULL;
			return 0;
		}


		VramTotal += width2 * height2 * 2;
	}
	else
	{

		lpTexHandle->Width = g_DibLastReadWidth;
		lpTexHandle->Height = g_DibLastReadHeight;
		lpTexHandle->lpDDSurface = lpDDSurface;
		lpTexHandle->lpDDSSysMemory = NULL;

		hresult = lpDDSurface->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&lpD3DTexture);
		if(hresult == D3D_OK)
			lpTexHandle->lpD3DTexture = lpD3DTexture;
		else
		{
			lpDDSurface->Release();
			lpTexHandle->lpDDSurface = NULL;
			return 0;
		}


		VramTotal += g_DibLastReadWidth * g_DibLastReadHeight * 2;
	}

	return TRUE;
}


int new_LoadDib(char *Filename)
{
	HANDLE hFile = CreateFile(Filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	DWORD dwAcess = 0;
	BITMAPFILEHEADER bmfh;

	ReadFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwAcess, NULL);

	if(bmfh.bfType != *(WORD *)"BM" && bmfh.bfType != *(WORD *)"C8" && bmfh.bfType != *(WORD *)"A8")
	{
		CloseHandle(hFile);
		return FALSE;
	}

	if(bmfh.bfType == *(WORD *)"A8")
	{
		BYTE ch = 0;
		BYTE *lpHeader = (BYTE *)&bmfh;

		for(int cnt = 0; cnt < sizeof(bmfh); cnt++)
		{
			ch = (BYTE)(lpHeader[cnt] - (cnt * cnt));
			lpHeader[cnt] = ch;
		}
	}

	size_t size = sizeof(BITMAPFILEHEADER);

	DWORD dwDibSize = bmfh.bfSize - size;
	BYTE *lpDib = g_DibImageDateBuff;


	ReadFile(hFile, lpDib, dwDibSize, &dwAcess, NULL);
	CloseHandle(hFile);

	DWORD dwHeaderSize = GetDibInfoHeaderSize(lpDib);

	if(dwHeaderSize < 12 || (dwHeaderSize > 12 && dwHeaderSize < 16))
	{
		return FALSE;
	}

	return TRUE;
}


int new_LoadTga(char *Filename)
{
	BYTE TGAHeader[0x12];
	HANDLE hFile;
	DWORD dwAcess;


	hFile = CreateFile(Filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return NULL;


	ReadFile(hFile, TGAHeader, 0x12, &dwAcess, NULL);


	if(TGAHeader[0] == 'G' && TGAHeader[1] == '8')
	{
		BYTE *lpHeader = (BYTE *)&TGAHeader;

		BYTE ch = 0;
		for(int cnt = 0; cnt < sizeof(TGAHeader); cnt++)
		{
			ch = (BYTE)(lpHeader[cnt] - (cnt * cnt));
			lpHeader[cnt] = ch;
		}
	}



	g_DibLastReadWidth = *((WORD *)(&TGAHeader[0xC]));
	g_DibLastReadHeight = *((WORD *)(&TGAHeader[0xE]));

	if((TGAHeader[0x11] & 0x20))
		g_TgaLastSwapHeight = FALSE;
	else
		g_TgaLastSwapHeight = TRUE;

	switch(TGAHeader[0x10])
	{

	case 24:
		g_TgaLastBitCnt = 24;
		ReadFile(hFile, g_DibImageDateBuff, g_DibLastReadWidth*g_DibLastReadHeight * 3, &dwAcess, NULL);
		break;

	case 32:
		g_TgaLastBitCnt = 32;
		ReadFile(hFile, g_DibImageDateBuff, g_DibLastReadWidth*g_DibLastReadHeight * 4, &dwAcess, NULL);
		break;

	default:
		CloseHandle(hFile);
		return NULL;
	}

	CloseHandle(hFile);
	return TRUE;
}




int New_DrawSurfaceFromTga(LPDIRECTDRAWSURFACE4 lpDDSurface)
{
	BYTE *dAddr = g_DibImageDateBuff;
	int width = g_DibLastReadWidth;
	int height = g_DibLastReadHeight;


	int i, j, k;
	int r, g, b, a, tp;
	DWORD MaskAll;

	DWORD Mask[4];
	DWORD Shift[4];
	DWORD ShiftPixel[4];
	DWORD ShiftTemp;

	Mask[0] = ddTextureFormat.dwRBitMask;
	Mask[1] = ddTextureFormat.dwGBitMask;
	Mask[2] = ddTextureFormat.dwBBitMask;
	Mask[3] = ddTextureFormat.dwRGBAlphaBitMask;

	MaskAll = Mask[0] | Mask[1] | Mask[2] | Mask[3];

	for(i = 0; i < 4; i++)
	{
		if(Mask[i])
		{
			ShiftTemp = Mask[i];
			for(j = 0; j < 32; j++)
			{
				if(ShiftTemp & 1)
					break;

				ShiftTemp >>= 1;
			}
			Shift[i] = j;
			for(j = 0; j < 32; j++)
			{
				if((ShiftTemp & 1) == 0)
					break;

				ShiftTemp >>= 1;
			}
			ShiftPixel[i] = j;
		}
		else
		{
			Shift[i] = 32;
			ShiftPixel[i] = 32;
		}
	}


	BYTE *Dest;
	int pBuff;
	int incByte;
	int pBuff_k;

	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize = sizeof(DDSURFACEDESC2);


	lpDDSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);

	Dest = (BYTE *)ddsd.lpSurface;

	if(Dest == NULL)
	{
		lpDDSurface->Release();
		return NULL;
	}

	pBuff_k = 0;
	k = 0;

	for(i = 0; i < height; i++)
	{
		switch(g_TgaLastBitCnt)
		{
		case 24:
			incByte = 3;

			if(g_TgaLastSwapHeight)
				pBuff = ((height - i - 1)*width) * 3;
			else
				pBuff = (i * width) * 3;

			break;

		case 32:
			incByte = 4;

			if(g_TgaLastSwapHeight)
				pBuff = ((height - i - 1)*width) << 2;
			else
				pBuff = (i * width) << 2;

			break;
		}

		k = pBuff_k;
		for(j = 0; j < width; j++)
		{
			b = dAddr[pBuff];
			g = dAddr[pBuff + 1];
			r = dAddr[pBuff + 2];

			if(g_TgaLastBitCnt == 32)
				a = dAddr[pBuff + 3];
			else
				a = 255;

			pBuff += incByte;

			r = ((r >> (8 - ShiftPixel[0])) << Shift[0]) & Mask[0];
			g = ((g >> (8 - ShiftPixel[1])) << Shift[1]) & Mask[1];
			b = ((b >> (8 - ShiftPixel[2])) << Shift[2]) & Mask[2];
			a = ((a >> (8 - ShiftPixel[3])) << Shift[3]) & Mask[3];

			tp = r | g | b | a;

			if(MaskAll <= 0xFFFF)
			{
				*((WORD *)&Dest[k]) = (WORD)tp;
				k += 2;
			}
			else
			{
				*((DWORD *)&Dest[k]) = tp;
				k += 4;
			}
		}

		pBuff_k += (int)ddsd.lPitch;

	}

	lpDDSurface->Unlock(NULL);
	return TRUE;
}




LPDIRECTDRAWSURFACE4 new_LoadBmpCreateTexSurface(char *Filename, int MipMap, int &rTexHalf)
{

	if(new_LoadDib(Filename) == NULL)
		return NULL;


	BYTE *lpDib = g_DibImageDateBuff;
	g_DibLastReadWidth = GetDibWidth(lpDib);
	g_DibLastReadHeight = GetDibHeight(lpDib);

	if(MipMap && MipMapModeCreate && g_DibLastReadWidth < 512 && g_DibLastReadHeight < 512)
	{
		if(MipMapModeCreate == NOSQUARE_MODE || g_DibLastReadWidth == g_DibLastReadHeight)
		{
			int len = ::lstrlen(Filename);

			for(int i = len - 1; i >= 0; i--)
			{
				if(Filename[i] == '.')
				{
					CopyMemory(MipMapFileBuff[0], Filename, i);
					break;
				}
			}


			for(int i = 1; i < MIPMAP_FILELIST; i++)
			{
				strcpy_s(MipMapFileBuff[i], sizeof(MipMapFileBuff[i]), MipMapFileBuff[0]);
				strcat_s(MipMapFileBuff[i], sizeof(MipMapFileBuff[i]), MipMapFileListBuff[i]);
				strcat_s(MipMapFileBuff[i], sizeof(MipMapFileBuff[i]), ".bmp");

				if(PathFileExists(MipMapFileBuff[i]))
					MipMapCount++;
				else
					break;
			}

			strcat_s(MipMapFileBuff[0], sizeof(MipMapFileBuff[0]), ".bmp");
		}
	}


	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	memcpy(&ddsd.ddpfPixelFormat, &ddDefaultTextureFormat, sizeof(DDPIXELFORMAT));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwWidth = g_DibLastReadWidth;
	ddsd.dwHeight = g_DibLastReadHeight;

	if(MipMapCount)
	{
		MipMapCount++;
		if(MipMapCreateTextureCheck(g_DibLastReadWidth, g_DibLastReadHeight, MipMapCount) <= 0)
			return NULL;

		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT;
		ddsd.dwMipMapCount = MipMapCount;
		ddsd.ddsCaps.dwCaps = DDSCAPS_MIPMAP | DDSCAPS_COMPLEX | DDSCAPS_TEXTURE;
		ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
	else
	{
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		if(renderDevice.GetDeviceDesc_IsHardware())
		{
			ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
			ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
		}
		else
			ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;
	}


	LPDIRECTDRAWSURFACE4 lpDDSurface;
	hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);
	if(hresult != DD_OK)
	{

		if(g_DibLastReadWidth > 256 || g_DibLastReadHeight > 256)
		{
			if(renderDevice.GetDeviceDesc_IsHardware())
			{
				ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;
				ddsd.ddsCaps.dwCaps2 = 0;

				hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);
				if(hresult == DD_OK)
					rTexHalf = TRUE;
			}
		}

		if(hresult != DD_OK)
			return NULL;
	}

	if(DrawSurfaceFromDib(lpDDSurface, lpDib) == FALSE)
	{
		lpDDSurface->Release();
		return NULL;
	}


	if(MipMapCount && rTexHalf == FALSE)
	{
		DDSCAPS2 ddsCaps;
		ZeroMemory(&ddsCaps, sizeof(DDSCAPS2));
		ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;

		LPDIRECTDRAWSURFACE4 lpDDSurface2 = lpDDSurface;
		int width2 = g_DibLastReadWidth;
		int height2 = g_DibLastReadHeight;

		for(int i = 1; i < MipMapCount; i++)
		{
			LPDIRECTDRAWSURFACE4 lpDDNextLevel = NULL;
			if(FAILED(lpDDSurface2->GetAttachedSurface(&ddsCaps, &lpDDNextLevel)))
			{
				lpDDSurface->Release();
				return NULL;
			}

			width2 >>= 1;
			height2 >>= 1;

			if(new_LoadDib(MipMapFileBuff[i]) == NULL)
			{
				lpDDNextLevel->Release();
				lpDDSurface->Release();
				return NULL;
			}

			if(width2 != GetDibWidth(lpDib) || height2 != GetDibHeight(lpDib))
			{
				lpDDNextLevel->Release();
				lpDDSurface->Release();
				return NULL;
			}

			if(DrawSurfaceFromDib(lpDDNextLevel, lpDib) == FALSE)
			{
				lpDDNextLevel->Release();
				lpDDSurface->Release();
				return NULL;
			}

			lpDDSurface2 = lpDDNextLevel;
			lpDDNextLevel->Release();
		}
	}


	return lpDDSurface;
}




LPDIRECTDRAWSURFACE4 new_LoadTgaCreateTexSurface(char *Filename, int MipMap, int &rTexHalf)
{

	if(new_LoadTga(Filename) == NULL)
		return NULL;


	if(MipMap && MipMapModeCreate && g_DibLastReadWidth < 512 && g_DibLastReadHeight < 512)
	{
		if(MipMapModeCreate == NOSQUARE_MODE || g_DibLastReadWidth == g_DibLastReadHeight)
		{
			int len = lstrlen(Filename);

			for(int i = len - 1; i >= 0; i--)
			{
				if(Filename[i] == '.')
				{
					CopyMemory(MipMapFileBuff[0], Filename, i);
					break;
				}
			}


			for(int i = 1; i < MIPMAP_FILELIST; i++)
			{
				strcpy_s(MipMapFileBuff[i], sizeof(MipMapFileBuff[i]), MipMapFileBuff[0]);
				strcat_s(MipMapFileBuff[i], sizeof(MipMapFileBuff[i]), MipMapFileListBuff[i]);
				strcat_s(MipMapFileBuff[i], sizeof(MipMapFileBuff[i]), ".tga");

				if(PathFileExists(MipMapFileBuff[i]))
					MipMapCount++;
				else
					break;
			}

			strcat_s(MipMapFileBuff[0], sizeof(MipMapFileBuff[0]), ".tga");
		}
	}


	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	memcpy(&ddsd.ddpfPixelFormat, &ddTextureFormat, sizeof(DDPIXELFORMAT));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwWidth = g_DibLastReadWidth;
	ddsd.dwHeight = g_DibLastReadHeight;

	if(MipMapCount)
	{
		MipMapCount++;
		if(MipMapCreateTextureCheck(g_DibLastReadWidth, g_DibLastReadHeight, MipMapCount) <= 0)
			return NULL;

		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT;
		ddsd.dwMipMapCount = MipMapCount;
		ddsd.ddsCaps.dwCaps = DDSCAPS_MIPMAP | DDSCAPS_COMPLEX | DDSCAPS_TEXTURE;
		ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
	else
	{
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		if(renderDevice.GetDeviceDesc_IsHardware())
		{
			ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
			ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
		}
		else
			ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;
	}


	LPDIRECTDRAWSURFACE4 lpDDSurface;
	hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);
	if(hresult != DD_OK)
	{

		if(g_DibLastReadWidth > 256 || g_DibLastReadHeight > 256)
		{
			if(renderDevice.GetDeviceDesc_IsHardware())
			{
				ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;
				ddsd.ddsCaps.dwCaps2 = 0;

				hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);
				if(hresult == DD_OK)
					rTexHalf = TRUE;
			}
		}

		if(hresult != DD_OK)
			return NULL;
	}


	if(New_DrawSurfaceFromTga(lpDDSurface) == FALSE)
	{
		lpDDSurface->Release();
		return NULL;
	}


	if(MipMapCount && rTexHalf == FALSE)
	{
		DDSCAPS2 ddsCaps;
		ZeroMemory(&ddsCaps, sizeof(DDSCAPS2));
		ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;

		LPDIRECTDRAWSURFACE4 lpDDSurface2 = lpDDSurface;

		int width2, height2, OrgWidth, OrgHeight;
		width2 = OrgWidth = g_DibLastReadWidth;
		height2 = OrgHeight = g_DibLastReadHeight;

		for(int i = 1; i < MipMapCount; i++)
		{
			LPDIRECTDRAWSURFACE4 lpDDNextLevel = NULL;
			if(FAILED(lpDDSurface2->GetAttachedSurface(&ddsCaps, &lpDDNextLevel)))
			{
				lpDDSurface->Release();
				return NULL;
			}

			width2 >>= 1;
			height2 >>= 1;

			if(new_LoadTga(MipMapFileBuff[i]) == NULL)
			{
				lpDDNextLevel->Release();
				lpDDSurface->Release();
				return NULL;
			}

			if(width2 != g_DibLastReadWidth || height2 != g_DibLastReadHeight)
			{
				lpDDNextLevel->Release();
				lpDDSurface->Release();
				return NULL;
			}

			if(New_DrawSurfaceFromTga(lpDDNextLevel) == FALSE)
			{
				lpDDNextLevel->Release();
				lpDDSurface->Release();
				return NULL;
			}

			lpDDSurface2 = lpDDNextLevel;
			lpDDNextLevel->Release();
		}

		g_DibLastReadWidth = OrgWidth;
		g_DibLastReadHeight = OrgHeight;
	}


	return lpDDSurface;
}




LPDIRECTDRAWSURFACE4 new_LoadBmpSurfaceOffscreen(char *Filename)
{

	if(new_LoadDib(Filename) == NULL)
		return NULL;


	BYTE *lpDib = g_DibImageDateBuff;
	g_DibLastReadWidth = GetDibWidth(lpDib);
	g_DibLastReadHeight = GetDibHeight(lpDib);

	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.dwWidth = g_DibLastReadWidth;
	ddsd.dwHeight = g_DibLastReadHeight;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

	LPDIRECTDRAWSURFACE4 lpDDSurface;
	hresult = renderDevice.CreateSurface(&ddsd, &lpDDSurface, NULL);
	if(hresult != DD_OK)
		return NULL;

	if(DrawSurfaceFromDib(lpDDSurface, lpDib) == FALSE)
	{
		lpDDSurface->Release();
		return NULL;
	}

	DDCOLORKEY ColKey;
	ColKey.dwColorSpaceLowValue = RGB(0, 0, 0);
	ColKey.dwColorSpaceHighValue = RGB(255, 255, 255);
	lpDDSurface->SetColorKey(DDCKEY_SRCBLT, &ColKey);

	return lpDDSurface;
}

