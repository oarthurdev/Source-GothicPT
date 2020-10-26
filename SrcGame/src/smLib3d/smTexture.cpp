
#include "smd3d.h"
#include <io.h>




int		g_IsReadTextures = 1;

BYTE	g_DibImageDateBuff[(1024 * 768) * 4];
int		g_DibLastReadWidth;
int		g_DibLastReadHeight;
int		g_TgaLastBitCnt;
int		g_TgaLastSwapHeight;

int		new_smCreateTexture(smTEXTUREHANDLE *lpTexHandle, int MipMap = 0);

#define ERROR_LIST_MAX		32
#define ERROR_LIST_MASK		(ERROR_LIST_MAX-1)

char szErrorList[ERROR_LIST_MAX][64];
int ErrorListCnt = 0;


int AddErrorList(char *szErrMsg)
{
	return ErrorListCnt;
}




DWORD	VramTotal = 0;




#define	MAX_MAP_BLINK_COLOR_TIME				8

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

static int  MipMapCount = 0;
static char MipMapFileBuff[MIPMAP_FILELIST][126] = { 0, };
static int  MipMapCountA = 0;
static char MipMapFileABuff[MIPMAP_FILELIST][126] = { 0, };
static char FileTypeBuff[16] = { 0, };



int		   MaterialFrame;


int SetTextureSwapMode(int mode)
{
	int OldValue;

	OldValue = TextureSwapMode;

	TextureSwapMode = mode;

	return OldValue;
}


int smSetTextureLevel(int Level)
{
	switch (Level) {
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
	TextureCnt = 0;

	
	InitializeCriticalSection(&cTextureSection);

}

int smTEXTURE::Remove()
{
	int cnt;

	
	EnterCriticalSection(&cTextureSection);


	for (cnt = 0; cnt < MAX_TEXTURE; cnt++) {
		if (Texture[cnt].UseCounter > 0) {
			
			if (Texture[cnt].lpD3DTexture) Texture[cnt].lpD3DTexture->Release();
			Texture[cnt].UseCounter = 0;
		}
	}
	
	LeaveCriticalSection(&cTextureSection);

	
	DeleteCriticalSection(&cTextureSection);

	return TRUE;
}





int smTEXTURE::Find(DWORD dwCode, char *Name)
{
	int cnt;
	for (cnt = 0; cnt < MAX_TEXTURE; cnt++)
	{
		if (TexSpeedSum[cnt] == dwCode)
		{
			if (Texture[cnt].UseCounter && _stricmp(Texture[cnt].Name, Name) == 0)
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

	if (TexNum >= 0)
	{
		LastTextureCnt = TexNum;
		Texture[TexNum].UseCounter++;
		return &Texture[TexNum];
	}

	for (cnt = 0; cnt < MAX_TEXTURE; cnt++)
	{
		if (Texture[cnt].UseCounter == 0)
			break;
	}

	if (cnt == MAX_TEXTURE)
		return NULL;

	TextureCnt = cnt;

	lpLastTexture = &Texture[TextureCnt].lpD3DTexture;

	Texture[TextureCnt].lpD3DTexture = NULL;

	if (strlen(name) > sizeof(Texture[TextureCnt].Name))
	{
		Log::getInstance()->output(LOG_ERROR, "[smTEXTURE::Add] - [Buffer Overflow][Capacity: %d] - [required: %d] Buffer: (%s)", sizeof(Texture[TextureCnt].Name), strlen(name), name);
		return NULL;
	}


	strcpy_s(Texture[TextureCnt].Name, sizeof(Texture[TextureCnt].Name), name);

	if (nameA)
	{
		strcpy_s(Texture[TextureCnt].NameA, sizeof(Texture[TextureCnt].NameA), nameA);
	}
	else
	{
		Texture[TextureCnt].NameA[0] = 0;
	}

	Texture[TextureCnt].TexSwapMode = TextureSwapMode;
	Texture[TextureCnt].UseCounter++;


	TexSpeedSum[TextureCnt] = dwCode;


	return &Texture[TextureCnt];
}


int smTEXTURE::Delete(smTEXTUREHANDLE *lpTex)
{
	int cnt;

	if (lpTex->UseCounter <= 0) return FALSE;

	lpTex->UseCounter--;

	if (lpTex->UseCounter <= 0) {
		
		if (lpTex->lpD3DTexture)
			lpTex->lpD3DTexture->Release();

		lpTex->lpD3DTexture = 0;

		VramTotal -= lpTex->Width * lpTex->Height * 2;

	}

	return lpTex->UseCounter;
}

int smTEXTURE::ReadTexture()
{
	
	
	if (g_IsReadTextures == 0)
		return 0;
	

	int cnt;
	int	Result;
	int ReadCount = 0;

	for (cnt = 0; cnt < MAX_TEXTURE; cnt++) 
	{

		if (Texture[cnt].UseCounter && !Texture[cnt].lpD3DTexture)
		{

			EnterCriticalSection(&cTextureSection);			

			Result = new_smCreateTexture(&Texture[cnt]);
			
			ReadCount++;

			LeaveCriticalSection(&cTextureSection);		

			if ((ReadCount & 0x7) == 0)	smPlayWindowMessage();	
		}
	}

	return TRUE;
}










smTEXTURE smTexture;




smMATERIAL_GROUP::smMATERIAL_GROUP()
{

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

	MaterialCount = 0;
	MaxMaterial = MaterialMax;
	ReformTexture = 0;

	smMaterial = new smMATERIAL[MaterialMax];
	ZeroMemory(smMaterial, sizeof(smMATERIAL)*MaterialMax);

}


int smMATERIAL_GROUP::Close()
{
	DWORD cnt, tcnt;

	for (cnt = 0; cnt < MaterialCount; cnt++) 
	{
			if (smMaterial[cnt].InUse) 
			{

				for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
					if (smMaterial[cnt].smTexture[tcnt])
						smTexture.Delete(smMaterial[cnt].smTexture[tcnt]);

				for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
					if (smMaterial[cnt].smAnimTexture[tcnt])
						smTexture.Delete(smMaterial[cnt].smAnimTexture[tcnt]);

			}
	}

	delete smMaterial;

	return TRUE;
}

#define TEXFILENAME_SIZE	64


int smMATERIAL_GROUP::GetSaveSize()
{
	int size;
	DWORD cnt, tcnt;
	int	len, alen;

	size = sizeof(smMATERIAL_GROUP);

	for (cnt = 0; cnt < MaterialCount; cnt++) {
		size += sizeof(smMATERIAL);
		if (smMaterial[cnt].InUse) {
			size += sizeof(int);					
			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++) {
				len = lstrlen(smMaterial[cnt].smTexture[tcnt]->Name) + 1;
				alen = lstrlen(smMaterial[cnt].smTexture[tcnt]->NameA) + 1;
				size += len;
				size += alen;
			}

			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++) {
				len = lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->Name) + 1;
				alen = lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->NameA) + 1;
				size += len;
				size += alen;
			}

		}
	}
	return size;
}


int smMATERIAL_GROUP::SaveFile(HANDLE hFile)
{
	DWORD	dwAcess;
	DWORD cnt, tcnt;
	int	len;
	int size;

	size = WriteFile(hFile, &Head, sizeof(smMATERIAL_GROUP), &dwAcess, NULL);

	for (cnt = 0; cnt < MaterialCount; cnt++) {
		
		size += WriteFile(hFile, &smMaterial[cnt], sizeof(smMATERIAL), &dwAcess, NULL);

		if (smMaterial[cnt].InUse) {

			
			len = 0;
			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++) {
				len += lstrlen(smMaterial[cnt].smTexture[tcnt]->Name) + 1;
				len += lstrlen(smMaterial[cnt].smTexture[tcnt]->NameA) + 1;
			}
			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++) {
				len += lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->Name) + 1;
				len += lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->NameA) + 1;
			}
			
			size += WriteFile(hFile, &len, sizeof(int), &dwAcess, NULL);

			
			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++) {
				len = lstrlen(smMaterial[cnt].smTexture[tcnt]->Name) + 1;
				size += WriteFile(hFile, smMaterial[cnt].smTexture[tcnt]->Name, len, &dwAcess, NULL);
				len = lstrlen(smMaterial[cnt].smTexture[tcnt]->NameA) + 1;
				size += WriteFile(hFile, smMaterial[cnt].smTexture[tcnt]->NameA, len, &dwAcess, NULL);
			}

			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++) {
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
	DWORD	dwAcess;
	DWORD	cnt, tcnt;
	int		StrLen;
	int		size;
	char	szNameBuff[4096];
	char	*lpNameBuff;
	char	*szName, *szNameA;

	
	size = ReadFile(hFile, &Head, sizeof(smMATERIAL_GROUP), &dwAcess, NULL);

	
	smMaterial = new smMATERIAL[MaterialCount];

	for (cnt = 0; cnt < MaterialCount; cnt++) {
		
		size += ReadFile(hFile, &smMaterial[cnt], sizeof(smMATERIAL), &dwAcess, NULL);

		if (smMaterial[cnt].InUse) {
			
			size += ReadFile(hFile, &StrLen, sizeof(int), &dwAcess, NULL);
			
			size += ReadFile(hFile, szNameBuff, StrLen, &dwAcess, NULL);

			lpNameBuff = szNameBuff;

			
			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++) {
				szName = lpNameBuff;
				lpNameBuff += lstrlen(szName) + 1;
				szNameA = lpNameBuff;
				lpNameBuff += lstrlen(szNameA) + 1;

				if (szNameA[0])
					smMaterial[cnt].smTexture[tcnt] = smTexture.Add(szName, szNameA);
				else
					smMaterial[cnt].smTexture[tcnt] = smTexture.Add(szName);
			}

			
			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++) {
				szName = lpNameBuff;
				lpNameBuff += lstrlen(szName) + 1;
				szNameA = lpNameBuff;
				lpNameBuff += lstrlen(szNameA) + 1;

				if (szNameA[0])
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
	DWORD cnt, dcnt, tcnt;

	dcnt = 0;
	for (cnt = 0; cnt < MaterialCount; cnt++) {
		if (smMaterial[cnt].InUse == TRUE) {
			
			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
				smTexture.Delete(smMaterial[cnt].smTexture[tcnt]);

			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
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
	int	AnimCount, FrameSpeed;
	int MatNum;
	char	*lpAnimFileList[16];
	char	*szDirectory;
	char	*lpScript;
	char	szTemp[64];

	MatNum = MaterialCount;
	MaterialCount++;

	smMaterial[MatNum].InUse = TRUE;
	smMaterial[MatNum].Shade = TRUE;
	smMaterial[MatNum].BlendType = SMMAT_BLEND_ALPHA;
	smMaterial[MatNum].TwoSide = aseMaterial->TwoSide;
	smMaterial[MatNum].ReformTexture = 0;

	
	if (!aseMaterial->MAP_OPACITY[0]) {
		for (cnt = 0; cnt < aseMaterial->TextureCounter; cnt++) {
			smMaterial[MatNum].smTexture[cnt] = smTexture.Add(aseMaterial->BITMAP[cnt]);
			smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
			smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
			smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
		}
		smMaterial[MatNum].MapOpacity = FALSE;
	}
	else {
		
		
		if (aseMaterial->TextureCounter > 1)
		{
			for (cnt = 0; cnt < aseMaterial->TextureCounter - 1; cnt++)
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
			for (cnt = 0; cnt < aseMaterial->TextureCounter; cnt++)
			{
				smMaterial[MatNum].smTexture[cnt] = smTexture.Add(aseMaterial->BITMAP[cnt], aseMaterial->MAP_OPACITY);
				smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
				smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
				smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
			}
		}

		smMaterial[MatNum].MapOpacity = TRUE;
		
	}

	
	if (smMaterial[MatNum].ReformTexture)	ReformTexture++;

	smMaterial[MatNum].TextureCounter = aseMaterial->TextureCounter;	
	smMaterial[MatNum].Transparency = aseMaterial->Transparency;		
	smMaterial[MatNum].SelfIllum = aseMaterial->SelfIllum;		
	smMaterial[MatNum].Diffuse = aseMaterial->Diffuse;			

	smMaterial[MatNum].UseState = aseMaterial->ScriptState;
	smMaterial[MatNum].TextureType = SMTEX_TYPE_MULTIMIX;

	if (aseMaterial->BlendType)
		smMaterial[MatNum].BlendType = aseMaterial->BlendType;

	
	if (smMaterial[MatNum].Transparency == 0)
		smMaterial[MatNum].MeshState = SMMAT_STAT_CHECK_FACE;

	
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WIND)) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ1;
		smMaterial[MatNum].MeshState = 0;
	}
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WINDX1)) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDX1;
		smMaterial[MatNum].MeshState = 0;
	}
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WINDX2)) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDX2;
		smMaterial[MatNum].MeshState = 0;
	}
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ1)) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ1;
		smMaterial[MatNum].MeshState = 0;
	}
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ2)) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ2;
		smMaterial[MatNum].MeshState = 0;
	}

	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ2)) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ2;
		smMaterial[MatNum].MeshState = 0;
	}

	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WATER)) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WATER;
		smMaterial[MatNum].MeshState = 0;
	}

	
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_NOTPASS)) {
		smMaterial[MatNum].MeshState = SMMAT_STAT_CHECK_FACE;	
	}
	else {
		if ((aseMaterial->ScriptState&sMATS_SCRIPT_PASS)) {
			smMaterial[MatNum].MeshState = 0;					
		}
	}
	
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_RENDLATTER)) {
		smMaterial[MatNum].MeshState |= sMATS_SCRIPT_RENDLATTER;
	}

	
	
	if ((aseMaterial->ScriptState & sMATS_SCRIPT_CHECK_ICE))
		smMaterial[MatNum].MeshState |= sMATS_SCRIPT_CHECK_ICE;
	

	
	
	if ((aseMaterial->ScriptState & sMATS_SCRIPT_ORG_WATER))
		smMaterial[MatNum].MeshState = sMATS_SCRIPT_ORG_WATER;
	

	
	AnimCount = 0;
	if (szScript) {
		if (aseMaterial->ScriptState&sMATS_SCRIPT_ANIM2) AnimCount = 2;
		if (aseMaterial->ScriptState&sMATS_SCRIPT_ANIM4) AnimCount = 4;
		if (aseMaterial->ScriptState&sMATS_SCRIPT_ANIM8) AnimCount = 8;
		if (aseMaterial->ScriptState&sMATS_SCRIPT_ANIM16) AnimCount = 16;
	}

	if (AnimCount) {
		len = lstrlen(szScript);

		for (cnt = 0; cnt < len; cnt++) {
			if (szScript[cnt] == 'a' && szScript[cnt + 1] == 'n' &&
				szScript[cnt + 2] == 'i' && szScript[cnt + 3] == 'm') {
				for (cnt = cnt; cnt < len; cnt++) {
					if (szScript[cnt] == ':') break;
				}
				break;
			}
		}

		if (cnt < len) {
			cnt++;
			lpScript = &szScript[cnt];
			FrameSpeed = 0;

			for (cnt = cnt; cnt < len; cnt++) {
				if (szScript[cnt] == ':') {
					FrameSpeed = atoi(&szScript[cnt + 1]);
					szScript[cnt] = 0;
					break;
				}
			}

			szDirectory = SetDirectoryFromFile(aseMaterial->BITMAP[0]);

			if (szDirectory) {
				for (cnt = 0; cnt < AnimCount; cnt++) {
					lpAnimFileList[cnt] = new char[64];
					lstrcpy(szTemp, szDirectory);
					lstrcat(szTemp, lpScript);
					wsprintf(lpAnimFileList[cnt], szTemp, cnt);
				}

				ChangeMaterialToAnimation(&smMaterial[MatNum], lpAnimFileList, AnimCount, smMaterial[MatNum].BlendType, TRUE);
				if (FrameSpeed) smMaterial[MatNum].Shift_FrameSpeed = FrameSpeed;			

				smMaterial[MatNum].Transparency = aseMaterial->Transparency;		

				for (cnt = AnimCount - 1; cnt >= 0; cnt--) delete lpAnimFileList[cnt];
			}
		}
	}

	
	
	if ((aseMaterial->ScriptState & sMATS_SCRIPT_BLINK_COLOR) && smMaterial[MatNum].WindMeshBottom == 0)
	{
		for (cnt = 0; cnt < MAX_MAP_BLINK_COLOR_TIME; cnt++)
		{
			if (strstr(szScript, szBlinkTimeScript[cnt]) != 0)
				break;
		}

		if (cnt >= MAX_MAP_BLINK_COLOR_TIME)
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
	int MatNum;


	MatNum = MaterialCount;
	MaterialCount++;

	smMaterial[MatNum].InUse = TRUE;
	smMaterial[MatNum].Shade = Shade;
	smMaterial[MatNum].TwoSide = TwoSide;

	if (szOpacity)
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


int	smMATERIAL_GROUP::AddTexture(int MatNum, char *szBitmap, char *szOpacity)
{
	int cnt;

	cnt = smMaterial[MatNum].TextureCounter;			

	if (szOpacity)
		smMaterial[MatNum].smTexture[cnt] = smTexture.Add(szBitmap, szOpacity);
	else
		smMaterial[MatNum].smTexture[cnt] = smTexture.Add(szBitmap);

	if (smMaterial[MatNum].smTexture[cnt])
		smMaterial[MatNum].TextureCounter++;

	return TRUE;
}


smMATERIAL *smMATERIAL_GROUP::FindNextMaterialFromTextureName()
{
	DWORD cnt, cnt2;

	char *szName;

	szName = szLastSearchName;


	
	for (cnt = LastSearchMaterial; cnt < MaterialCount; cnt++) {
		if (smMaterial[cnt].InUse) {

			for (cnt2 = 0; cnt2 < smMaterial[cnt].TextureCounter; cnt2++) {
				if (lstrcmpi(smMaterial[cnt].smTexture[cnt2]->Name, szName) == 0) {
					return	&smMaterial[cnt];
				}
			}

			for (cnt2 = 0; cnt2 < smMaterial[cnt].AnimTexCounter; cnt2++) {
				if (lstrcmpi(smMaterial[cnt].smAnimTexture[cnt2]->Name, szName) == 0) {
					return	&smMaterial[cnt];
				}
			}

		}
	}

	return NULL;
}


smMATERIAL *smMATERIAL_GROUP::FindMaterialFromTextureName(char *szName)
{
	LastSearchMaterial = 0;

	lstrcpy(szLastSearchName, szName);

	return FindNextMaterialFromTextureName();
}


int smMATERIAL_GROUP::SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame)
{
	int OldFrame;

	OldFrame = lpMaterial->AnimationFrame;
	lpMaterial->AnimationFrame = frame;

	return OldFrame;
}




int smMATERIAL_GROUP::ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode)
{
	int cnt;

	for (cnt = 0; cnt < NumTex; cnt++) {
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

	
	if (AutoAnimMode)
		lpMaterial->AnimationFrame = SMTEX_AUTOANIMATION;
	else
		lpMaterial->AnimationFrame = 0;

	lpMaterial->InUse++;

	return TRUE;
}



int smMATERIAL_GROUP::CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode)
{
	int cnt;

	smMATERIAL *lpMaterial;

	cnt = MaterialCount;
	MaterialCount++;

	lpMaterial = &smMaterial[cnt];

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

	
	for (cnt = 0; cnt < MaterialCount; cnt++)
		if (smMaterial[cnt].InUse) 
		{
			if (smMaterial[cnt].TextureType == SMTEX_TYPE_MULTIMIX) 
			{
				for (cnt2 = 0; cnt2 < smMaterial[cnt].TextureCounter; cnt2++) 
				{
					if (smMaterial[cnt].smTexture[cnt2]) 
					{
						smMaterial[cnt].TextureSwap = TRUE;
						break;
					}
				}
			}

			if (smMaterial[cnt].TextureType == SMTEX_TYPE_ANIMATION)
			{
				for (cnt2 = 0; cnt2 < smMaterial[cnt].AnimTexCounter; cnt2++) 
				{
					if (smMaterial[cnt].smAnimTexture[cnt2])
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

	if (lpMaterial->TextureSwap) 
	{
		result = 0;

		if (result) 
		{
			lpMaterial->TextureClip = TRUE;
			return TRUE;
		}
	}

	return FALSE;
}




int smMATERIAL_GROUP::ReadTextures(int MipMap)

{
	
	
	if (g_IsReadTextures == 0)
		return 0;
	

	DWORD cnt;
	DWORD tcnt;
	int	Result;
	int	ReadCount;
	smTEXTUREHANDLE	*lpTexture;

	
	smEnterTextureCriticalSection();

	ReadCount = 0;

	for (cnt = 0; cnt < MaterialCount; cnt++) {
		if (smMaterial[cnt].InUse) {
			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++) {
				if (smMaterial[cnt].smTexture[tcnt]) {
					lpTexture = smMaterial[cnt].smTexture[tcnt];

					if (lpTexture->UseCounter && !lpTexture->lpD3DTexture)
					{
						
						
						
						Result = new_smCreateTexture(lpTexture, MipMap);
						

						ReadCount++;
					}
				}
			}

			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++) {
				if (smMaterial[cnt].smAnimTexture[tcnt]) {
					lpTexture = smMaterial[cnt].smAnimTexture[tcnt];
					if (lpTexture->UseCounter && !lpTexture->lpD3DTexture)
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



































smMATERIAL *smMaterial;

smMATERIAL_GROUP	*smMaterialGroup;


int InitMaterial()
{
	
	smMaterialGroup = new smMATERIAL_GROUP(MATRIAL_MAX);
	smMaterial = smMaterialGroup->smMaterial;

	MaterialFrame = 0;

	return TRUE;
}


int CloseMaterial()
{
	
	delete smMaterialGroup;
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


int CreateTextureMaterial(char *szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD TexSwap, DWORD BlendType)
{
	return smMaterialGroup->CreateTextureMaterial(szBitmap, szOpacity, TwoSide, Shade, TexSwap, BlendType);
}


int	AddTexture(int MatNum, char *szBitmap, char *szOpacity)
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
	return MaterialFrame++;
}


int CheckMatreialTextureSwap()
{
	return smMaterialGroup->CheckMatreialTextureSwap();
}



int ReSwapMaterial(smMATERIAL *lpMaterial)
{
	return smMaterialGroup->ReSwapMaterial(lpMaterial);
}



int InitTexture()
{
	smTexture.Init();

	return TRUE;
}

int CloseTexture()
{
	smTexture.Remove();

	return TRUE;
}

int ReadTextures()
{
	
	
	if (g_IsReadTextures == 0)
		return 0;
	

	int val;

	val = smTexture.ReadTexture();
	CheckMatreialTextureSwap();

	return val;
}



void smEnterTextureCriticalSection()
{
	EnterCriticalSection(&smTexture.cTextureSection);
}


void smLeaveTextureCriticalSection()
{
	LeaveCriticalSection(&smTexture.cTextureSection);
}


#define smTEXFILETYPE_BMP		0
#define smTEXFILETYPE_JPG		1
#define smTEXFILETYPE_TGA		2
#define smTEXFILETYPE_PNG		3

int GetTextureFileType(char *Filename)
{
	int len;
	int cnt;
	char *szFileExt = 0;
	len = lstrlen(Filename);
	for (cnt = len - 1; cnt >= 0; cnt--)
	{
		if (Filename[cnt] == '.')
		{
			szFileExt = Filename + cnt + 1;
			break;
		}
	}
	if (!szFileExt)
		return -1;
	if ((szFileExt[0] == 'j' || szFileExt[0] == 'J') &&
		(szFileExt[1] == 'p' || szFileExt[1] == 'P') &&
		(szFileExt[2] == 'g' || szFileExt[2] == 'G'))
		return smTEXFILETYPE_JPG;
	if ((szFileExt[0] == 'b' || szFileExt[0] == 'B') &&
		(szFileExt[1] == 'm' || szFileExt[1] == 'M') &&
		(szFileExt[2] == 'p' || szFileExt[2] == 'P'))
		return smTEXFILETYPE_BMP;
	if ((szFileExt[0] == 't' || szFileExt[0] == 'T') &&
		(szFileExt[1] == 'g' || szFileExt[1] == 'G') &&
		(szFileExt[2] == 'a' || szFileExt[2] == 'A'))
		return smTEXFILETYPE_TGA;
	if ((szFileExt[0] == 'p' || szFileExt[0] == 'P') &&
		(szFileExt[1] == 'n' || szFileExt[1] == 'N') &&
		(szFileExt[2] == 'g' || szFileExt[2] == 'G'))
		return smTEXFILETYPE_TGA;
	if ((szFileExt[0] == 's' || szFileExt[0] == 'S') &&
		(szFileExt[1] == 't' || szFileExt[1] == 'T') &&
		(szFileExt[2] == 'g' || szFileExt[2] == 'G'))
		return smTEXFILETYPE_JPG;
	if ((szFileExt[0] == 's' || szFileExt[0] == 'S') &&
		(szFileExt[1] == 't' || szFileExt[1] == 'T') &&
		(szFileExt[2] == 'a' || szFileExt[2] == 'A'))
		return smTEXFILETYPE_TGA;
	return -1;
}

BOOL DecryptBMP(char * pBuffer, unsigned int uBufferSize)
{
	if (uBufferSize < 14)
		return FALSE;

	if ((pBuffer[0] != 'B') || (pBuffer[1] != 'M'))
	{
		pBuffer[0] = 'B';
		pBuffer[1] = 'M';

		for (unsigned char c = 2; c < 14; c++)
			pBuffer[c] -= (c * c);
	}

	pBuffer[2] = 0;
	pBuffer[3] = 0;
	pBuffer[4] = 0;
	pBuffer[5] = 0;

	return TRUE;
}

BOOL DecryptTGA(char * pBuffer, unsigned int uBufferSize)
{
	if (uBufferSize < 18)
		return FALSE;

	if ((pBuffer[0] == 'G') && (pBuffer[1] == '8'))
	{
		pBuffer[0] = 0;
		pBuffer[1] = 0;

		for (unsigned char c = 2; c < 18; c++)
			pBuffer[c] -= (c * c);
	}

	return TRUE;
}

LPDIRECT3DTEXTURE9 LoadDibSurfaceOffscreen(char *Filename)
{

	if (PathFileExists(Filename))

	{
		FILE * pFile = NULL;
		char * pBuffer = NULL;
		LPDIRECT3DTEXTURE9 Image = NULL;
		fopen_s(&pFile, Filename, "rb");
		if (pFile)

		{
			fseek(pFile, 0, SEEK_END);
			int iSize = ftell(pFile);
			fseek(pFile, 0, SEEK_SET);
			if (iSize <= 0)

			{
				fclose(pFile);
				delete[] pBuffer;
				return NULL;
			}

			pBuffer = new char[iSize];
			fread(pBuffer, iSize, 1, pFile);
			fclose(pFile);
			if (DecryptBMP(pBuffer, iSize) == false)

			{
				delete[] pBuffer;
				return NULL;
			}
			D3DXIMAGE_INFO ImageInfo;
			D3DXGetImageInfoFromFileInMemory(pBuffer, iSize, &ImageInfo);
			if (FAILED(D3DXCreateTextureFromFileInMemoryEx(d3ddev, pBuffer, iSize, ImageInfo.Width, ImageInfo.Height, D3DX_FROM_FILE, 0, D3DFMT_FROM_FILE, D3DPOOL_MANAGED, D3DX_FILTER_POINT, D3DX_DEFAULT, 0xFF000000, &ImageInfo, NULL, &Image)))
			{
				delete[] pBuffer;
				return NULL;
			}
		}

		delete[] pBuffer;

		return Image;
	}
	else return NULL;
}


int new_smCreateTexture(smTEXTUREHANDLE *lpTexHandle, int MipMap)
{
	if (PathFileExists(lpTexHandle->Name))
	{
		FILE * pFile = NULL;
		char * pBuffer = NULL;
		fopen_s(&pFile, lpTexHandle->Name, "rb");
		if (pFile)
		{
			fseek(pFile, 0, SEEK_END);
			int iSize = ftell(pFile);
			fseek(pFile, 0, SEEK_SET);
			if (iSize <= 0)
			{
				fclose(pFile);
				delete[] pBuffer;
			}

			pBuffer = new char[iSize];
			fread(pBuffer, iSize, 1, pFile);
			fclose(pFile);
			UINT uMipLevels = 0;

			if (MipMap == true)

			{
				char szFilePath[MAX_PATH] =
				{
					0 }
				;
				lstrcpy(szFilePath, lpTexHandle->Name);
				const char * iDot = strrchr(szFilePath, '.');
				if (iDot != NULL)

				{
					char szBaseFile[MAX_PATH], szFileExtension[MAX_PATH];
					int iLenToDot = iDot - szFilePath;

					lstrcpy(szBaseFile, szFilePath);
					szBaseFile[iLenToDot] = 0;

					lstrcpy(szFileExtension, szBaseFile + iLenToDot + 1);

					for (int i = 1; i <= 4; i++)

					{
						char szBuffer[MAX_PATH];
						wsprintf(szBuffer, "%s_mm%d.%s", szBaseFile, i, szFileExtension);
						uMipLevels += PathFileExistsA(szBuffer) ? 1 : 0;
					}
				}
			}
			if (GetTextureFileType(lpTexHandle->Name) == smTEXFILETYPE_TGA)

			{
				if (DecryptTGA(pBuffer, iSize) == false)

				{
					delete[] pBuffer;

				}
				lpTexHandle->MapOpacity = TRUE;
			}
			if (GetTextureFileType(lpTexHandle->Name) == smTEXFILETYPE_BMP)

			{
				if (DecryptBMP(pBuffer, iSize) == false)

				{
					delete[] pBuffer;

				}
				lpTexHandle->MapOpacity = FALSE;
			}
			if (GetTextureFileType(lpTexHandle->Name) == smTEXFILETYPE_JPG)

			{
				lpTexHandle->MapOpacity = FALSE;
			}
			if (GetTextureFileType(lpTexHandle->Name) == smTEXFILETYPE_PNG)

			{
				lpTexHandle->MapOpacity = TRUE;
			}
			D3DXIMAGE_INFO ImageInfo;
			D3DXGetImageInfoFromFileInMemory(pBuffer, iSize, &ImageInfo);
			lpTexHandle->Width = ImageInfo.Width;
			lpTexHandle->Height = ImageInfo.Height;

			if (FAILED(D3DXCreateTextureFromFileInMemoryEx(d3ddev, pBuffer, iSize, ImageInfo.Width, ImageInfo.Height, D3DX_FROM_FILE, 0, D3DFMT_FROM_FILE, D3DPOOL_MANAGED, D3DX_FILTER_POINT, D3DX_DEFAULT, 0xFFF0FFFF, &ImageInfo, NULL, &lpTexHandle->lpD3DTexture)))

			{
				lpTexHandle->lpD3DTexture = NULL;
			}

			delete[] pBuffer;
		}
	}

	return TRUE;
}

