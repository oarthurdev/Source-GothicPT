
#include "smd3d.h"

char DataDirectory[128];


static int smMeshReload = TRUE;
static int smMeshSave = 0;

struct smTFACE
{
	DWORD	t[3];
};

struct smFCPOINT
{
	float r, g, b;
};










static char decode[256];
static char line[256];

char *GetWord(char *q, char *p)
{


	while((*p == 32) || (*p == 9) || (*p == 58))
	{
		p++;
	}

	while((*p != 32) && (*p != 9) && (*p != 58))
	{
		if(*p == '\n' || *p == '\r') break;
		*q++ = *p++;
	}
	*q++ = 0;



	return p;
}

char *GetString(char *q, char *p)
{

	while(*p != 34) p++;

	p++;

	while((*p != 34))
	{
		if(*p == 0 || *p == 0x0D || *p == 0x0A) break;
		*q++ = *p++;
	}

	p++;

	*q++ = 0;

	return p;
}


char *SetDirectoryFromFile(char *filename)
{
	int len;
	int cnt;

	strcpy_s(DataDirectory, filename);

	len = lstrlen(DataDirectory);

	for(cnt = len; cnt >= 0; cnt--)
		if(DataDirectory[cnt] == '\\') break;

	DataDirectory[cnt + 1] = NULL;

	return DataDirectory;
}


char szChangeFileExt[64];


char *ChangeFileExt(char *filename, char *FileExt)
{
	int cnt, len;

	strcpy_s(szChangeFileExt, sizeof(szChangeFileExt), filename);
	len = lstrlen(szChangeFileExt);

	for(cnt = len - 1; cnt >= 0; cnt--)
	{
		if(szChangeFileExt[cnt] == '.')
		{
			strcpy_s(&szChangeFileExt[cnt + 1], sizeof(szChangeFileExt) - cnt + 1, FileExt);
			return szChangeFileExt;
		}
	}

	szChangeFileExt[len] = '.';

	strcpy_s(szChangeFileExt + len + 1, sizeof(szChangeFileExt) - len - 1, FileExt);

	return szChangeFileExt;
}







ASE_MATERIAL	aseMaterial[MATRIAL_MAX * 2];

int	aseMaterialCnt;


#define BS_SCRIPT_MAX		7

char *szMapStageScript[BS_SCRIPT_MAX] = {
	"BS_MODULATE:",
	"BS_MODULATE2X:",
	"BS_MODULATE4X:",
	"BS_ADD:",
	"BS_ADDSIGNED:",
	"BS_ADDSIGNED2X:",
	"BS_SUBTRACT:"
};




DWORD BsStageScript[BS_SCRIPT_MAX] = {
	D3DTOP_MODULATE,
	D3DTOP_MODULATE2X,
	D3DTOP_MODULATE4X,
	D3DTOP_ADD,
	D3DTOP_ADDSIGNED,
	D3DTOP_ADDSIGNED2X,
	D3DTOP_SUBTRACT
};






#define FS_SCRIPT_MAX		19


char *szMapFormScript[FS_SCRIPT_MAX] = {
	"FS_NONE:",
	"FS_FORMX:",
	"FS_FORMY:",
	"FS_FORMZ:",
	"FS_SCROLL:",
	"FS_REFLEX:",

	"FS_SCROLL2:",
	"FS_SCROLL3:",
	"FS_SCROLL4:",
	"FS_SCROLL5:",
	"FS_SCROLL6:",
	"FS_SCROLL7:",
	"FS_SCROLL8:",
	"FS_SCROLL9:",
	"FS_SCROLL10:",



	"FS_SCROLLSLOW1:",
	"FS_SCROLLSLOW2:",
	"FS_SCROLLSLOW3:",
	"FS_SCROLLSLOW4:"

};




#define MATS_SCRIPT_MAX		17


struct MATS_SCRIPT_CODE
{
	char *szScript;
	DWORD dwScriptCode;
};

MATS_SCRIPT_CODE MaterialFormScript[MATS_SCRIPT_MAX] = {
	{ "wind:" , sMATS_SCRIPT_WIND },
	{ "anim2:" , sMATS_SCRIPT_ANIM2 },
	{ "anim4:" , sMATS_SCRIPT_ANIM4 },
	{ "anim8:" , sMATS_SCRIPT_ANIM8 },
	{ "anim16:" , sMATS_SCRIPT_ANIM16 },

	{ "wind_z1:" , sMATS_SCRIPT_WINDZ1 },
	{ "wind_z2:" , sMATS_SCRIPT_WINDZ2 },
	{ "wind_x1:" , sMATS_SCRIPT_WINDX1 },
	{ "wind_x2:" , sMATS_SCRIPT_WINDX2 },

	{ "water:" , sMATS_SCRIPT_WATER },
	{ "wall:" , sMATS_SCRIPT_NOTVIEW },

	{ "pass:" , sMATS_SCRIPT_PASS },
	{ "notpass:" , sMATS_SCRIPT_NOTPASS },

	{ "render_latter:" , sMATS_SCRIPT_RENDLATTER },



	{ "BLINK_COLOR:", sMATS_SCRIPT_BLINK_COLOR },




	{ "ice:", sMATS_SCRIPT_CHECK_ICE },




	{ "orgwater:", sMATS_SCRIPT_ORG_WATER },

};


#define		MATS_BLEND_MAX		5

MATS_SCRIPT_CODE MaterialFormBlend[MATS_BLEND_MAX] = {
	{	"BLEND_ALPHA:"		,	SMMAT_BLEND_ALPHA		},
	{	"BLEND_COLOR:"		,	SMMAT_BLEND_COLOR		},
	{	"BLEND_ADDCOLOR:"	,	SMMAT_BLEND_ADDCOLOR	},
	{	"BLEND_SHADOW:"		,	SMMAT_BLEND_SHADOW		},
	{	"BLEND_LAMP:"		,	SMMAT_BLEND_LAMP		}
};



#define	ase_SCRIPT_MAX		256
struct ase_SCRIPT
{
	int		MatNum;
	char	szScript[64];
};



FILE *ReadASE_MATERIAL(FILE *fp, smMATERIAL_GROUP **MatGroup = 0)
{
	char strBuff[256];
	char strFile[256];
	char *p;
	int strLevel;
	int mCount;
	int smCount;
	int MatrialNum;
	int SubMatrialNum;
	int NewMatrial;

	int curMatrialNum;
	int BitMapNum;
	int BitmapDiffuse;
	int BitmapCnt;
	int slen;
	int cnt;

	int BitmapFormState;
	int BitmapStageState;

	ase_SCRIPT	aseScript[ase_SCRIPT_MAX];
	int	aseScriptCnt = 0;
	int	sCnt;
	char	*lpScript;

	BitMapNum = 0;

	strLevel = 0;

	curMatrialNum = 0;

	ZeroMemory(aseMaterial, sizeof(ASE_MATERIAL)*MATRIAL_MAX * 2);


	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)
		{
			fclose(fp);
			return FALSE;
		}

		p = GetWord(decode, line);

		if(lstrcmp(decode, "*MATERIAL_COUNT") == 0)
		{
			p = GetWord(strBuff, p);
			mCount = atoi(strBuff);
			NewMatrial = mCount;
		}
		if(lstrcmp(decode, "*MATERIAL") == 0)
		{
			p = GetWord(strBuff, p);
			MatrialNum = atoi(strBuff);
			curMatrialNum = MatrialNum;
			BitmapCnt = -1;
		}


		if(strLevel == 1)
		{
			if(lstrcmp(decode, "*NUMSUBMTLS") == 0)
			{
				p = GetWord(strBuff, p);
				smCount = atoi(strBuff);
				aseMaterial[MatrialNum].SubPoint = NewMatrial;
				NewMatrial += smCount;
			}

			if(lstrcmp(decode, "*SUBMATERIAL") == 0)
			{
				p = GetWord(strBuff, p);
				SubMatrialNum = atoi(strBuff);
				curMatrialNum = aseMaterial[MatrialNum].SubPoint + SubMatrialNum;
				BitmapCnt = -1;
			}
		}


		if(lstrcmp(decode, "*MATERIAL_NAME") == 0)
		{
			p = GetString(strBuff, p);
			for(cnt = 0; cnt < MATS_SCRIPT_MAX; cnt++)
			{
				if(strstr(strBuff, MaterialFormScript[cnt].szScript) != 0)
				{
					aseMaterial[curMatrialNum].ScriptState |= MaterialFormScript[cnt].dwScriptCode;
				}
			}

			if(aseMaterial[curMatrialNum].ScriptState && aseScriptCnt < ase_SCRIPT_MAX)
			{
				aseScript[aseScriptCnt].MatNum = curMatrialNum;
				strcpy_s(aseScript[aseScriptCnt].szScript, strBuff);
				aseScriptCnt++;
			}


			for(cnt = 0; cnt < MATS_BLEND_MAX; cnt++)
			{
				if(strstr(strBuff, MaterialFormBlend[cnt].szScript) != 0)
				{
					aseMaterial[curMatrialNum].BlendType = MaterialFormBlend[cnt].dwScriptCode;
					break;
				}
			}
		}


		if(lstrcmp(decode, "*MAP_DIFFUSE") == 0)
			BitmapDiffuse = 1;
		if(lstrcmp(decode, "*MAP_OPACITY") == 0)
			BitmapDiffuse = 0;
		if(lstrcmp(decode, "*MAP_AMBIENT") == 0)
			BitmapDiffuse = -1;

		if(lstrcmp(decode, "*MAP_NAME") == 0)
		{

			p = GetString(strBuff, p);
			BitmapStageState = 0;
			BitmapFormState = 0;

			for(cnt = 0; cnt < BS_SCRIPT_MAX; cnt++)
			{
				if(strstr(strBuff, szMapStageScript[cnt]) != 0)
				{
					BitmapStageState = BsStageScript[cnt];
					break;
				}
			}
			for(cnt = 0; cnt < FS_SCRIPT_MAX; cnt++)
			{
				if(strstr(strBuff, szMapFormScript[cnt]) != 0)
				{
					BitmapFormState = cnt;
					break;
				}
			}
		}


		if(lstrcmp(decode, "*BITMAP") == 0)
		{

			p = GetString(strBuff, p);
			slen = lstrlen(strBuff);
			for(cnt = slen - 1; cnt > 0; cnt--)
			{
				if(strBuff[cnt] == '\\' || strBuff[cnt] == ':')
				{
					cnt++; break;
				}
			}

			strcpy_s(strFile, DataDirectory);
			lstrcat(strFile, strBuff + cnt);

			switch(BitmapDiffuse)
			{
				case 1:
				BitmapCnt++;
				strcpy_s(aseMaterial[curMatrialNum].BITMAP[BitmapCnt], strFile);
				aseMaterial[curMatrialNum].TextureCounter++;
				aseMaterial[curMatrialNum].BitmapStateState[BitmapCnt] = BitmapStageState;
				aseMaterial[curMatrialNum].BitmapFormState[BitmapCnt] = BitmapFormState;

				break;
				case 0:
				strcpy_s(aseMaterial[curMatrialNum].MAP_OPACITY, strFile);
				break;
			}
		}


		if(lstrcmp(decode, "*UVW_U_OFFSET") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].UVW_U_OFFSET[BitmapCnt] = (float)atof(strBuff);
		}
		if(lstrcmp(decode, "*UVW_V_OFFSET") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].UVW_V_OFFSET[BitmapCnt] = (float)atof(strBuff);
		}
		if(lstrcmp(decode, "*UVW_U_TILING") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].UVW_U_TILING[BitmapCnt] = (float)atof(strBuff);
		}
		if(lstrcmp(decode, "*UVW_V_TILING") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].UVW_V_TILING[BitmapCnt] = (float)atof(strBuff);
		}
		if(lstrcmp(decode, "*UVW_ANGLE") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].UVW_ANGLE[BitmapCnt] = (float)atof(strBuff);
		}


		if(lstrcmp(decode, "*MATERIAL_TWOSIDED") == 0)
		{
			aseMaterial[curMatrialNum].TwoSide = TRUE;
		}


		if(lstrcmp(decode, "*MATERIAL_DIFFUSE") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].Diffuse.r = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].Diffuse.g = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].Diffuse.b = (float)atof(strBuff);
		}


		if(lstrcmp(decode, "*MATERIAL_TRANSPARENCY") == 0)
		{
			p = GetWord(strBuff, p);

			if(aseMaterial[curMatrialNum].Transparency == 0)
			{
				aseMaterial[curMatrialNum].Transparency = (float)atof(strBuff);
			}
		}

		if(lstrcmp(decode, "*MATERIAL_SELFILLUM") == 0)
		{
			p = GetWord(strBuff, p);

			if(aseMaterial[curMatrialNum].SelfIllum == 0)
			{
				aseMaterial[curMatrialNum].SelfIllum = (float)atof(strBuff);
			}
		}


		if(strstr(line, "{"))
			strLevel++;

		if(strstr(line, "}"))
		{
			strLevel--;
			if(strLevel < 0) break;
		}
	}

	aseMaterialCnt = curMatrialNum + 1;


	DWORD	dwMaterialSum[MATRIAL_MAX * 2];
	int		aseMaterialLink[MATRIAL_MAX * 2];
	DWORD	dwSum;
	BYTE	*lpAseMat;
	int		nCnt, rCnt, lCnt;


	for(cnt = 0; cnt < aseMaterialCnt; cnt++)
	{
		lpAseMat = (BYTE *)&aseMaterial[cnt];
		dwSum = 0;
		for(nCnt = 0; nCnt < sizeof(ASE_MATERIAL); nCnt++)
		{
			dwSum += ((DWORD)lpAseMat[nCnt])*(nCnt + 5) * 10;
		}
		dwMaterialSum[cnt] = dwSum;
	}


	rCnt = 0; lCnt = 0;

	for(cnt = 0; cnt < aseMaterialCnt; cnt++)
	{
		for(nCnt = 0; nCnt < cnt; nCnt++)
		{
			if(dwMaterialSum[nCnt] == dwMaterialSum[cnt])
				break;
		}



		if(nCnt > 0 && nCnt < cnt &&
		   stricmp(aseMaterial[cnt].BITMAP[0], aseMaterial[nCnt].BITMAP[0]) == 0)
		{
			aseMaterialLink[cnt] = nCnt;
			lCnt++;
		}
		else
		{
			aseMaterialLink[cnt] = -1;
			rCnt++;
		}

	}


	smMATERIAL_GROUP *MGroup;

	if(MatGroup)
	{
		MGroup = new smMATERIAL_GROUP(rCnt);
		*MatGroup = MGroup;
	}
	else
		MGroup = smMaterialGroup;

	sCnt = 0;

	for(cnt = 0; cnt < aseMaterialCnt; cnt++)
	{
		lpScript = 0;




		for(nCnt = 0; nCnt < aseScriptCnt; nCnt++)
		{
			if(aseScript[nCnt].MatNum == cnt)
			{
				lpScript = aseScript[nCnt].szScript;
				break;
			}
		}


		if(aseMaterialLink[cnt] < 0)
			aseMaterial[cnt].RegistNum = MGroup->AddMaterial(&aseMaterial[cnt], lpScript);
		else
			aseMaterial[cnt].RegistNum = aseMaterial[aseMaterialLink[cnt]].RegistNum;

		aseMaterial[cnt].Regist = TRUE;

	}

	return fp;
}




struct SLightMapRefInfo
{
	int bLightMap;
	int SubPoint;
	int MaxSubMtl;
};

#define					dMAX_LIGHT_MAP_REF					4000
static int				s_bLightMapStage;
static int				s_LightMapRefMax;
static SLightMapRefInfo	s_LightMapRefBuff[dMAX_LIGHT_MAP_REF];


FILE* ReadASE_LIGHTMAP_MATERIAL(FILE *fp, smMATERIAL_GROUP **MatGroup = 0)
{
	char strBuff[256];
	char strFile[256];
	char *p;
	int strLevel;
	int OldStrLevel;
	int mCount;
	int smCount;
	int MatrialNum;
	int OldMatrialNum;
	int SubMatrialNum;
	int NewMatrial;

	int curMatrialNum;
	int BitMapNum;
	int BitmapDiffuse;
	int BitmapCnt;
	int slen;
	int cnt;

	int BitmapFormState;
	int BitmapStageState;

	ase_SCRIPT	aseScript[ase_SCRIPT_MAX];
	int aseScriptCnt = 0;
	int sCnt = 0;
	char *lpScript;

	BitMapNum = 0;

	OldStrLevel = strLevel = 0;

	curMatrialNum = 0;

	ZeroMemory(aseMaterial, sizeof(ASE_MATERIAL)*MATRIAL_MAX * 2);


	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)
		{
			fclose(fp);
			return FALSE;
		}

		p = GetWord(decode, line);

		if(lstrcmp(decode, "*MATERIAL_COUNT") == 0)
		{
			p = GetWord(strBuff, p);
			mCount = atoi(strBuff);
			NewMatrial = mCount;
		}
		if(lstrcmp(decode, "*MATERIAL") == 0)
		{
			p = GetWord(strBuff, p);
			MatrialNum = atoi(strBuff);
			curMatrialNum = MatrialNum;
			BitmapCnt = -1;
		}


		if(lstrcmp(decode, "*MATERIAL_NAME") == 0)
		{
			p = GetString(strBuff, p);


			if(strLevel == 1)
			{
				if(s_LightMapRefMax >= dMAX_LIGHT_MAP_REF)
				{

					////Utils_//LOG(LOG_ERROR, "MATERIAL Counter Error (ReadAse)");

					s_LightMapRefMax--;
				}

				if(strstr(strBuff, "*LM_") != 0)
				{
					s_LightMapRefBuff[s_LightMapRefMax].bLightMap = TRUE;
					s_bLightMapStage = TRUE;
				}
				else
					s_LightMapRefBuff[s_LightMapRefMax].bLightMap = FALSE;

				s_LightMapRefBuff[s_LightMapRefMax].SubPoint = 0;
				s_LightMapRefBuff[s_LightMapRefMax].MaxSubMtl = 0;
				s_LightMapRefMax++;
			}


			for(cnt = 0; cnt < MATS_SCRIPT_MAX; cnt++)
			{
				if(strstr(strBuff, MaterialFormScript[cnt].szScript) != 0)
				{
					aseMaterial[curMatrialNum].ScriptState |= MaterialFormScript[cnt].dwScriptCode;
				}
			}


			if(aseMaterial[curMatrialNum].ScriptState && aseScriptCnt < ase_SCRIPT_MAX)
			{
				aseScript[aseScriptCnt].MatNum = curMatrialNum;
				strcpy_s(aseScript[aseScriptCnt].szScript, strBuff);
				aseScriptCnt++;
			}


			for(cnt = 0; cnt < MATS_BLEND_MAX; cnt++)
			{
				if(strstr(strBuff, MaterialFormBlend[cnt].szScript) != 0)
				{
					aseMaterial[curMatrialNum].BlendType = MaterialFormBlend[cnt].dwScriptCode;
					break;
				}
			}
		}

		if(lstrcmp(decode, "*NUMSUBMTLS") == 0)
		{
			if((strLevel % 2) == 0 && (smCount - (SubMatrialNum + 1)) > 0)
			{
				OldStrLevel = strLevel - 1;
				OldMatrialNum = MatrialNum;
			}
			else
				OldMatrialNum = 0;

			p = GetWord(strBuff, p);
			smCount = atoi(strBuff);
			aseMaterial[curMatrialNum].SubPoint = NewMatrial;

			int LMRefMax = s_LightMapRefMax - 1;
			if(s_LightMapRefBuff[LMRefMax].bLightMap == TRUE)
			{
				if(LMRefMax == curMatrialNum)
					s_LightMapRefBuff[LMRefMax].SubPoint = NewMatrial;
				else
					s_LightMapRefBuff[LMRefMax].MaxSubMtl = smCount;
			}
			else
			{
				s_LightMapRefBuff[LMRefMax].SubPoint = NewMatrial;
				s_LightMapRefBuff[LMRefMax].MaxSubMtl = smCount;
			}

			MatrialNum = NewMatrial;
			NewMatrial += smCount;
		}
		if(lstrcmp(decode, "*SUBMATERIAL") == 0)
		{
			if(strLevel == OldStrLevel && OldMatrialNum)
			{
				MatrialNum = OldMatrialNum;
				OldStrLevel = OldMatrialNum = 0;
			}

			p = GetWord(strBuff, p);
			SubMatrialNum = atoi(strBuff);
			curMatrialNum = MatrialNum + SubMatrialNum;
			BitmapCnt = -1;
		}


		if(lstrcmp(decode, "*MAP_DIFFUSE") == 0)
			BitmapDiffuse = 1;
		if(lstrcmp(decode, "*MAP_OPACITY") == 0)
			BitmapDiffuse = 0;
		if(lstrcmp(decode, "*MAP_AMBIENT") == 0)
			BitmapDiffuse = -1;

		if(lstrcmp(decode, "*MAP_NAME") == 0)
		{

			p = GetString(strBuff, p);
			BitmapStageState = 0;
			BitmapFormState = 0;

			for(cnt = 0; cnt < BS_SCRIPT_MAX; cnt++)
			{
				if(strstr(strBuff, szMapStageScript[cnt]) != 0)
				{
					BitmapStageState = BsStageScript[cnt];
					break;
				}
			}
			for(cnt = 0; cnt < FS_SCRIPT_MAX; cnt++)
			{
				if(strstr(strBuff, szMapFormScript[cnt]) != 0)
				{
					BitmapFormState = cnt;
					break;
				}
			}
		}


		if(lstrcmp(decode, "*BITMAP") == 0)
		{

			p = GetString(strBuff, p);
			slen = lstrlen(strBuff);
			for(cnt = slen - 1; cnt > 0; cnt--)
			{
				if(strBuff[cnt] == '\\' || strBuff[cnt] == ':')
				{
					cnt++; break;
				}
			}

			strcpy_s(strFile, DataDirectory);
			lstrcat(strFile, strBuff + cnt);

			switch(BitmapDiffuse)
			{
				case 1:
				BitmapCnt++;
				strcpy_s(aseMaterial[curMatrialNum].BITMAP[BitmapCnt], strFile);
				aseMaterial[curMatrialNum].TextureCounter++;
				aseMaterial[curMatrialNum].BitmapStateState[BitmapCnt] = BitmapStageState;
				aseMaterial[curMatrialNum].BitmapFormState[BitmapCnt] = BitmapFormState;

				break;
				case 0:
				strcpy_s(aseMaterial[curMatrialNum].MAP_OPACITY, strFile);
				break;
			}

		}


		if(lstrcmp(decode, "*UVW_U_OFFSET") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].UVW_U_OFFSET[BitmapCnt] = (float)atof(strBuff);
		}
		if(lstrcmp(decode, "*UVW_V_OFFSET") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].UVW_V_OFFSET[BitmapCnt] = (float)atof(strBuff);
		}
		if(lstrcmp(decode, "*UVW_U_TILING") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].UVW_U_TILING[BitmapCnt] = (float)atof(strBuff);
		}
		if(lstrcmp(decode, "*UVW_V_TILING") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].UVW_V_TILING[BitmapCnt] = (float)atof(strBuff);
		}
		if(lstrcmp(decode, "*UVW_ANGLE") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].UVW_ANGLE[BitmapCnt] = (float)atof(strBuff);
		}


		if(lstrcmp(decode, "*MATERIAL_TWOSIDED") == 0)
		{
			aseMaterial[curMatrialNum].TwoSide = TRUE;
		}


		if(lstrcmp(decode, "*MATERIAL_DIFFUSE") == 0)
		{
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].Diffuse.r = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].Diffuse.g = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			aseMaterial[curMatrialNum].Diffuse.b = (float)atof(strBuff);
		}


		if(lstrcmp(decode, "*MATERIAL_TRANSPARENCY") == 0)
		{
			p = GetWord(strBuff, p);

			if(aseMaterial[curMatrialNum].Transparency == 0)
			{
				aseMaterial[curMatrialNum].Transparency = (float)atof(strBuff);
			}
		}


		if(lstrcmp(decode, "*MATERIAL_SELFILLUM") == 0)
		{
			p = GetWord(strBuff, p);

			if(aseMaterial[curMatrialNum].SelfIllum == 0)
			{
				aseMaterial[curMatrialNum].SelfIllum = (float)atof(strBuff);
			}
		}


		if(strstr(line, "{"))
			strLevel++;

		if(strstr(line, "}"))
		{
			strLevel--;
			if(strLevel < 0) break;
		}
	}

	aseMaterialCnt = NewMatrial;


	if(s_bLightMapStage)
	{

		ASE_MATERIAL LightMap_MATERIAL;
		int			 EndSubPoint = s_LightMapRefMax;

		for(cnt = 0; cnt < s_LightMapRefMax; cnt++)
		{
			int SubPoint = s_LightMapRefBuff[cnt].SubPoint;
			if(SubPoint)
			{
				if(s_LightMapRefBuff[cnt].bLightMap)
				{
					LightMap_MATERIAL = aseMaterial[SubPoint + 1];
					::CopyMemory(&aseMaterial[EndSubPoint], &aseMaterial[SubPoint + 2],
								 sizeof(ASE_MATERIAL) * s_LightMapRefBuff[cnt].MaxSubMtl);

					int i = EndSubPoint;
					int iMax = i + s_LightMapRefBuff[cnt].MaxSubMtl;
					for(; i < iMax; i++)
					{
						int BitmapCnt = aseMaterial[i].TextureCounter;
						aseMaterial[i].TextureCounter++;

						strcpy_s(aseMaterial[i].BITMAP[BitmapCnt], LightMap_MATERIAL.BITMAP[0]);
						aseMaterial[i].BitmapStateState[BitmapCnt] = LightMap_MATERIAL.BitmapStateState[0];
						aseMaterial[i].BitmapFormState[BitmapCnt] = LightMap_MATERIAL.BitmapFormState[0];

						aseMaterial[i].UVW_U_OFFSET[BitmapCnt] = LightMap_MATERIAL.UVW_U_OFFSET[0];
						aseMaterial[i].UVW_V_OFFSET[BitmapCnt] = LightMap_MATERIAL.UVW_V_OFFSET[0];
						aseMaterial[i].UVW_U_TILING[BitmapCnt] = LightMap_MATERIAL.UVW_U_TILING[0];
						aseMaterial[i].UVW_V_TILING[BitmapCnt] = LightMap_MATERIAL.UVW_V_TILING[0];
						aseMaterial[i].UVW_ANGLE[BitmapCnt] = LightMap_MATERIAL.UVW_ANGLE[0];
					}

					aseMaterialCnt -= 2;


					for(int scrNum = 0; scrNum < aseScriptCnt; scrNum++)
					{
						if(aseScript[scrNum].MatNum == SubPoint || aseScript[scrNum].MatNum == SubPoint + 1)
						{

							////Utils_//LOG(LOG_ERROR, "ASESCRIPT MATNUM Error (ReadAse)");
							aseScript[scrNum].MatNum = 0;
						}
						else if(aseScript[scrNum].MatNum >= SubPoint + 2 &&
								aseScript[scrNum].MatNum <= SubPoint + 2 + s_LightMapRefBuff[cnt].MaxSubMtl - 1)
						{
							aseScript[scrNum].MatNum -= 2;
						}
					}
				}
				else
				{
					::CopyMemory(&aseMaterial[EndSubPoint], &aseMaterial[SubPoint], s_LightMapRefBuff[cnt].MaxSubMtl);


					int num = SubPoint - EndSubPoint;
					for(int scrNum = 0; scrNum < aseScriptCnt; scrNum++)
					{
						if(aseScript[scrNum].MatNum >= SubPoint &&
						   aseScript[scrNum].MatNum <= SubPoint + s_LightMapRefBuff[cnt].MaxSubMtl - 1)
						{
							aseScript[scrNum].MatNum -= num;
						}
					}
				}

				aseMaterial[cnt].SubPoint = EndSubPoint;
				EndSubPoint += s_LightMapRefBuff[cnt].MaxSubMtl;
			}
			else if(s_LightMapRefBuff[cnt].bLightMap)
				return FALSE;
		}
	}


	DWORD	dwMaterialSum[MATRIAL_MAX * 2];
	int		aseMaterialLink[MATRIAL_MAX * 2];
	DWORD	dwSum;
	BYTE	*lpAseMat;
	int		nCnt, rCnt, lCnt;

	for(cnt = 0; cnt < aseMaterialCnt; cnt++)
	{
		lpAseMat = (BYTE *)&aseMaterial[cnt];
		dwSum = 0;

		for(nCnt = 0; nCnt < sizeof(ASE_MATERIAL); nCnt++)
		{
			dwSum += ((DWORD)lpAseMat[nCnt]) * (nCnt + 5) * 10;
		}

		dwMaterialSum[cnt] = dwSum;
	}

	rCnt = 0; lCnt = 0;
	for(cnt = 0; cnt < aseMaterialCnt; cnt++)
	{
		for(nCnt = 0; nCnt < cnt; nCnt++)
		{
			if(dwMaterialSum[nCnt] == dwMaterialSum[cnt])
				break;
		}



		if(nCnt > 0 && nCnt < cnt &&
		   stricmp(aseMaterial[cnt].BITMAP[0], aseMaterial[nCnt].BITMAP[0]) == 0)
		{
			aseMaterialLink[cnt] = nCnt;
			lCnt++;
		}
		else
		{
			aseMaterialLink[cnt] = -1;
			rCnt++;
		}

	}

	smMATERIAL_GROUP *MGroup;
	if(MatGroup)
	{
		MGroup = new smMATERIAL_GROUP(rCnt);
		*MatGroup = MGroup;
	}
	else
		MGroup = smMaterialGroup;

	sCnt = 0;
	for(cnt = 0; cnt < aseMaterialCnt; cnt++)
	{
		lpScript = 0;




		for(nCnt = 0; nCnt < aseScriptCnt; nCnt++)
		{
			if(aseScript[nCnt].MatNum == cnt)
			{
				lpScript = aseScript[nCnt].szScript;
				break;
			}
		}


		if(aseMaterialLink[cnt] < 0)
			aseMaterial[cnt].RegistNum = MGroup->AddMaterial(&aseMaterial[cnt], lpScript);
		else
			aseMaterial[cnt].RegistNum = aseMaterial[aseMaterialLink[cnt]].RegistNum;

		aseMaterial[cnt].Regist = TRUE;
	}

	return fp;
}




smPAT3D *smPhysique = 0;

static smMATERIAL	*smMatPattern;

#define SCENE_TICKSPERFRAME		160
int AseSceneLastFrame;

FILE *ReadASE_GEOMOBJECT(FILE *fp, smOBJ3D *obj, char *szNodeName = 0)
{


	int nPhysique = 0;
	int pNum = 0;


	char strBuff[256];
	char *p;
	int strLevel;
	int nVertex;
	int nFace;
	int nTVertex;
	int nTFace;
	int InitFlag;
	int InitTFlag;

	int VertexCnt;
	int FaceCnt;
	int TVertexCnt;
	int TFaceCnt;

	int x, y, z;
	int a, b, c;

	float qx, qy, qz, qw;

	smFTPOINT	*tPoint;
	smTFACE		*tFace;

	int *FaceMatrial = 0;
	int mCount = 0;
	int MatrialRef = 0;
	int cnt, cnt2;

	smTM_ROT	TmRot[4096];
	smDTM_ROT	TmDRot[4096];
	smTM_POS	TmPos[4096];
	smTM_SCALE	TmScale[4096];

	int TmRotCnt;
	int TmPosCnt;
	int TmScaleCnt;
	int LastFrame;

	LastFrame = AseSceneLastFrame;

	TmRotCnt = 0;
	TmPosCnt = 0;
	TmScaleCnt = 0;

	tPoint = 0;
	tFace = 0;

	nVertex = -1;
	nFace = -1;
	InitFlag = 0;

	nTVertex = -1;
	nTFace = -1;
	InitTFlag = 0;

	TVertexCnt = 0;
	TFaceCnt = 0;
	VertexCnt = 0;
	FaceCnt = 0;

	strLevel = 0;



	int			 bLightMap = 0;

	smFTPOINT	*tLightMapPoint = NULL;
	smTFACE		*tLightMapFace = NULL;
	smFTPOINT	*lpTexVertex = NULL;
	smTFACE		*lpTexFace = NULL;


	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)
		{
			fclose(fp);
			return FALSE;
		}

		p = GetWord(decode, line);

		if(lstrcmp(decode, "*NODE_NAME") == 0)
		{
			p = GetString(strBuff, p);
			strBuff[31] = 0;
			strcpy_s(obj->NodeName, strBuff);
			if(szNodeName && lstrcmpi(strBuff, szNodeName) != 0)
			{
				obj->nFace = 0; obj->nVertex = 0;

				return fp;
			}
		}

		if(lstrcmp(decode, "*NODE_PARENT") == 0)
		{
			p = GetString(strBuff, p);
			strBuff[31] = 0;
			strcpy_s(obj->NodeParent, strBuff);
		}

		if(lstrcmp(decode, "*MESH_NUMVERTEX") == 0)
		{
			p = GetWord(strBuff, p);
			nVertex = atoi(strBuff);
		}
		if(lstrcmp(decode, "*MESH_NUMFACES") == 0)
		{
			p = GetWord(strBuff, p);
			nFace = atoi(strBuff);
		}



		if(lstrcmp(decode, "*MESH_NUMTVERTEX") == 0)
		{
			p = GetWord(strBuff, p);
			nTVertex = atoi(strBuff);

			if(bLightMap)
			{
				tLightMapPoint = new smFTPOINT[nTVertex];
				tLightMapFace = new smTFACE[nFace];

				lpTexVertex = tLightMapPoint;
				lpTexFace = tLightMapFace;
			}
			else
			{
				tPoint = new smFTPOINT[nTVertex];
				tFace = new smTFACE[nFace];

				lpTexVertex = tPoint;
				lpTexFace = tFace;
			}

			TVertexCnt = TFaceCnt = 0;

			ZeroMemory(lpTexVertex, sizeof(smFTPOINT) * nTVertex);
			ZeroMemory(lpTexFace, sizeof(smTFACE) * nFace);
		}

		if(lstrcmp(decode, "*MESH_MAPPINGCHANNEL") == 0)
		{
			p = GetWord(strBuff, p);
			bLightMap = 1;
		}



		if(InitFlag == 0 && nVertex >= 0 && nFace >= 0)
		{

			if(smPhysique) obj->Init(nVertex, nFace, 1);
			else obj->Init(nVertex, nFace, 0);

			FaceMatrial = new int[nFace];
			InitFlag++;
		}


		if(lstrcmp(decode, "*TM_ROW0") == 0)
		{
			p = GetWord(strBuff, p);
			x = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			y = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			z = (int)(atof(strBuff)*fONE);
			obj->Tm._11 = x;
			obj->Tm._12 = y;
			obj->Tm._13 = z;
		}
		if(lstrcmp(decode, "*TM_ROW1") == 0)
		{
			p = GetWord(strBuff, p);
			x = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			y = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			z = (int)(atof(strBuff)*fONE);
			obj->Tm._21 = x;
			obj->Tm._22 = y;
			obj->Tm._23 = z;
		}
		if(lstrcmp(decode, "*TM_ROW2") == 0)
		{
			p = GetWord(strBuff, p);
			x = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			y = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			z = (int)(atof(strBuff)*fONE);
			obj->Tm._31 = x;
			obj->Tm._32 = y;
			obj->Tm._33 = z;
		}
		if(lstrcmp(decode, "*TM_ROW3") == 0)
		{
			p = GetWord(strBuff, p);
			x = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			y = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			z = (int)(atof(strBuff)*fONE);
			obj->Tm._41 = x;
			obj->Tm._42 = y;
			obj->Tm._43 = z;
		}


		if(lstrcmp(decode, "*TM_POS") == 0)
		{
			p = GetWord(strBuff, p);
			x = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			y = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			z = (int)(atof(strBuff)*fONE);
			obj->px = x;
			obj->py = y;
			obj->pz = z;
		}

		if(lstrcmp(decode, "*TM_ROTAXIS") == 0)
		{
			p = GetWord(strBuff, p);
			qx = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			qy = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			qz = (float)atof(strBuff);
			obj->qx = qx;
			obj->qy = qy;
			obj->qz = qz;
		}
		if(lstrcmp(decode, "*TM_ROTANGLE") == 0)
		{
			p = GetWord(strBuff, p);
			qw = (float)atof(strBuff);
			obj->qw = qw;
			smQuaternionFromAxis(obj->qx, obj->qy, obj->qz, obj->qw);
			smMatrixFromQuaternion(obj->TmRotate, obj->qx, obj->qy, obj->qz, obj->qw);
		}


		if(lstrcmp(decode, "*TM_SCALE") == 0)
		{
			p = GetWord(strBuff, p);
			x = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			y = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			z = (int)(atof(strBuff)*fONE);
			obj->sx = x;
			obj->sy = y;
			obj->sz = z;
		}


		if(lstrcmp(decode, "*CONTROL_ROT_SAMPLE") == 0 ||
		   lstrcmp(decode, "*CONTROL_TCB_ROT_KEY") == 0)
		{
			p = GetWord(strBuff, p);
			TmDRot[TmRotCnt].frame = (int)atoi(strBuff);
			p = GetWord(strBuff, p);
			TmDRot[TmRotCnt].x = atof(strBuff);
			p = GetWord(strBuff, p);
			TmDRot[TmRotCnt].y = atof(strBuff);
			p = GetWord(strBuff, p);
			TmDRot[TmRotCnt].z = atof(strBuff);
			p = GetWord(strBuff, p);
			TmDRot[TmRotCnt].w = atof(strBuff);

			TmRot[TmRotCnt].frame = TmDRot[TmRotCnt].frame;
			TmRot[TmRotCnt].x = (float)TmDRot[TmRotCnt].x;
			TmRot[TmRotCnt].y = (float)TmDRot[TmRotCnt].y;
			TmRot[TmRotCnt].z = (float)TmDRot[TmRotCnt].z;
			TmRot[TmRotCnt].w = (float)TmDRot[TmRotCnt].w;

			TmRotCnt++;
		}




		if(lstrcmp(decode, "*CONTROL_POS_SAMPLE") == 0 ||
		   lstrcmp(decode, "*CONTROL_TCB_POS_KEY") == 0 ||
		   lstrcmp(decode, "*CONTROL_BEZIER_POS_KEY") == 0)
		{
			p = GetWord(strBuff, p);
			TmPos[TmPosCnt].frame = atoi(strBuff);
			p = GetWord(strBuff, p);
			TmPos[TmPosCnt].x = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			TmPos[TmPosCnt].y = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			TmPos[TmPosCnt].z = (float)atof(strBuff);

			TmPosCnt++;
		}



		if(lstrcmp(decode, "*CONTROL_SCALE_SAMPLE") == 0 ||
		   lstrcmp(decode, "*CONTROL_TCB_SCALE_KEY") == 0 ||
		   lstrcmp(decode, "*CONTROL_BEZIER_SCALE_KEY") == 0)
		{
			p = GetWord(strBuff, p);
			TmScale[TmScaleCnt].frame = atoi(strBuff);
			p = GetWord(strBuff, p);
			TmScale[TmScaleCnt].x = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			TmScale[TmScaleCnt].y = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			TmScale[TmScaleCnt].z = (int)(atof(strBuff)*fONE);

			TmScaleCnt++;
		}




		if(lstrcmp(decode, "*MESH_VERTEX") == 0)
		{
			p = GetWord(strBuff, p);

			if(atoi(strBuff) != VertexCnt)
			{
				////Utils_//LOG(LOG_ERROR, "Vetex Counter Error (ReadAse)");
			}

			p = GetWord(strBuff, p);
			x = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			y = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			z = (int)(atof(strBuff)*fONE);

			obj->AddVertex(x, y, z);



			VertexCnt++;

		}


		if(lstrcmp(decode, "*MESH_FACE") == 0)
		{
			p = GetWord(strBuff, p);

			p = GetWord(strBuff, p);
			p = GetWord(strBuff, p);
			a = (int)atoi(strBuff);

			p = GetWord(strBuff, p);
			p = GetWord(strBuff, p);
			b = (int)atoi(strBuff);

			p = GetWord(strBuff, p);
			p = GetWord(strBuff, p);
			c = (int)atoi(strBuff);

			obj->AddFace(a, b, c);


			for(cnt = 0; cnt < 16; cnt++)
			{
				p = GetWord(strBuff, p);
				if(lstrcmp(strBuff, "*MESH_MTLID") == 0)
				{
					p = GetWord(strBuff, p);
					FaceMatrial[mCount++] = atoi(strBuff);
					break;
				}
			}
		}




		if(lstrcmp(decode, "*MESH_TVERT") == 0)
		{
			p = GetWord(strBuff, p);

			if(atoi(strBuff) != TVertexCnt)
			{
				////Utils_//LOG(LOG_ERROR, "TVetex Counter Error (ReadAse)");
			}

			p = GetWord(strBuff, p);
			lpTexVertex[TVertexCnt].u = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpTexVertex[TVertexCnt].v = (float)atof(strBuff);
			p = GetWord(strBuff, p);

			TVertexCnt++;
		}


		if(lstrcmp(decode, "*MESH_TFACE") == 0)
		{
			p = GetWord(strBuff, p);

			if(atoi(strBuff) != TFaceCnt)
			{
				////Utils_//LOG(LOG_ERROR, "TFace Counter Error (ReadAse)");
			}

			p = GetWord(strBuff, p);
			lpTexFace[TFaceCnt].t[0] = (int)atoi(strBuff);
			p = GetWord(strBuff, p);
			lpTexFace[TFaceCnt].t[1] = (int)atoi(strBuff);
			p = GetWord(strBuff, p);
			lpTexFace[TFaceCnt].t[2] = (int)atoi(strBuff);

			TFaceCnt++;
		}




		if(lstrcmp(decode, "*MATERIAL_REF") == 0)
		{
			p = GetWord(strBuff, p);
			MatrialRef = atoi(strBuff);
		}



		if(smPhysique)
		{
			if(lstrcmp(decode, "*PHYSIQUE_NUMVERTEXASSIGNMENT") == 0)
			{
				p = GetWord(strBuff, p);
				nPhysique = atoi(strBuff);
			}

			if(lstrcmp(decode, "*PHYSIQUE_VERTEXASSIGNMENT_NONBLENDED_RIGIDTYPE") == 0)
			{
				p = GetWord(strBuff, p);
				pNum = atoi(strBuff);
				p = GetString(strBuff, p);
				obj->Physique[pNum] = smPhysique->GetObjectFromName(strBuff);

				if(!obj->Physique[pNum])
					x = 0;

			}

			if(lstrcmp(decode, "*PHYSIQUE_VERTEXASSIGNMENT_BLENDED_RIGIDTYPE") == 0)
			{
				p = GetWord(strBuff, p);
				pNum = atoi(strBuff);
			}

			if(lstrcmp(decode, "*PHYSIQUE_VERTEXASSIGNMENT_NODE") == 0)
			{
				p = GetWord(strBuff, p);
				x = atoi(strBuff);
				p = GetWord(strBuff, p);
				y = atoi(strBuff);
				p = GetString(strBuff, p);
				if(x == 0)
				{
					obj->Physique[pNum] = smPhysique->GetObjectFromName(strBuff);
				}
			}

		}


		p = GetWord(strBuff, p);
		if(lstrcmp(decode, "{") == 0 ||
		   lstrcmp(strBuff, "{") == 0)
			strLevel++;

		if(lstrcmp(decode, "}") == 0 ||
		   lstrcmp(strBuff, "}") == 0)
		{
			strLevel--;
			if(strLevel < 0) break;
		}
	}


	int fmat;
	float fu, fv, fU, fV;
	float fOffset_u, fOffset_v;
	float fTiling_u, fTiling_v;
	float fAngle, fSin, fCos;
	int TexCnt, tcnt;
	int mNum;
	smFTPOINT	ftpoint[3];


	for(cnt = 0; cnt < nFace; cnt++)
	{
		if(aseMaterial[MatrialRef].SubPoint)
			fmat = aseMaterial[MatrialRef].SubPoint + FaceMatrial[cnt];
		else
			fmat = MatrialRef;



		mNum = aseMaterial[fmat].RegistNum;


		smMatPattern[mNum].InUse++;


		TexCnt = smMatPattern[mNum].TextureCounter;



		if(bLightMap)
			TexCnt--;


		for(tcnt = 0; tcnt < TexCnt; tcnt++)
		{

			fOffset_u = aseMaterial[fmat].UVW_U_OFFSET[tcnt];
			fOffset_v = aseMaterial[fmat].UVW_V_OFFSET[tcnt];
			fTiling_u = aseMaterial[fmat].UVW_U_TILING[tcnt];
			fTiling_v = aseMaterial[fmat].UVW_V_TILING[tcnt];
			fAngle = (float)(aseMaterial[fmat].UVW_ANGLE[tcnt] * smMULT_PIE);
			fSin = ((float)GetSin[((int)fAngle) & ANGLE_MASK]) / 65536;
			fCos = ((float)GetCos[((int)fAngle) & ANGLE_MASK]) / 65536;

			for(cnt2 = 0; cnt2 < 3; cnt2++)
			{

				fU = (float)(tPoint[tFace[cnt].t[cnt2]].u - 0.5);
				fV = (float)(tPoint[tFace[cnt].t[cnt2]].v - 0.5);

				fu = (fU * fCos) + (fV * fSin);
				fv = (fV * fCos) - (fU * fSin);

				fu -= fOffset_u;
				fv -= fOffset_v;

				fu *= fTiling_u;
				fv *= fTiling_v;

				fu += 0.5;
				fv += 0.5;

				ftpoint[cnt2].u = fu;
				ftpoint[cnt2].v = 1 - fv;
			}

			obj->AddTexLink(cnt, (DWORD*)&smMatPattern[mNum].smTexture[tcnt], &ftpoint[0], &ftpoint[1], &ftpoint[2]);
		}



		if(bLightMap)
		{

			fOffset_u = aseMaterial[fmat].UVW_U_OFFSET[tcnt];
			fOffset_v = aseMaterial[fmat].UVW_V_OFFSET[tcnt];
			fTiling_u = aseMaterial[fmat].UVW_U_TILING[tcnt];
			fTiling_v = aseMaterial[fmat].UVW_V_TILING[tcnt];
			fAngle = (float)(aseMaterial[fmat].UVW_ANGLE[tcnt] * smMULT_PIE);
			fSin = ((float)GetSin[((int)fAngle) & ANGLE_MASK]) / 65536;
			fCos = ((float)GetCos[((int)fAngle) & ANGLE_MASK]) / 65536;

			for(cnt2 = 0; cnt2 < 3; cnt2++)
			{
				fU = (float)(tLightMapPoint[tLightMapFace[cnt].t[cnt2]].u - 0.5);
				fV = (float)(tLightMapPoint[tLightMapFace[cnt].t[cnt2]].v - 0.5);

				fu = (fU * fCos) + (fV * fSin);
				fv = (fV * fCos) - (fU * fSin);

				fu -= fOffset_u;
				fv -= fOffset_v;

				fu *= fTiling_u;
				fv *= fTiling_v;

				fu += 0.5;
				fv += 0.5;

				ftpoint[cnt2].u = fu;
				ftpoint[cnt2].v = 1 - fv;
			}

			obj->AddTexLink(cnt, (DWORD*)&smMatPattern[mNum].smTexture[tcnt], &ftpoint[0], &ftpoint[1], &ftpoint[2]);
		}



		obj->SetFaceMaterial(cnt, mNum);

	}

	if(FaceMatrial) delete FaceMatrial;
	if(tPoint) delete tPoint;
	if(tFace) delete tFace;



	if(tLightMapPoint)	 delete tLightMapPoint;
	if(tLightMapFace)	 delete tLightMapFace;




	smDTM_ROT tRot;


	smDMATRIX dtmat;
	smDMATRIX dPrevMat;



	if(TmRotCnt > 0 && TmRot[TmRotCnt - 1].frame < LastFrame)
	{
		memcpy(&TmRot[TmRotCnt], &TmRot[TmRotCnt - 1], sizeof(smTM_ROT));
		TmRot[TmRotCnt].frame = LastFrame;
		memcpy(&TmDRot[TmRotCnt], &TmDRot[TmRotCnt - 1], sizeof(smDTM_ROT));
		TmDRot[TmRotCnt].frame = LastFrame;
		TmRotCnt++;
	}

	if(TmPosCnt > 0 && TmPos[TmPosCnt - 1].frame < LastFrame)
	{
		memcpy(&TmPos[TmPosCnt], &TmPos[TmPosCnt - 1], sizeof(smTM_POS));
		TmPos[TmPosCnt].frame = LastFrame;
		TmPosCnt++;
	}

	if(TmScaleCnt > 0 && TmScale[TmScaleCnt - 1].frame < LastFrame)
	{
		memcpy(&TmScale[TmScaleCnt], &TmScale[TmScaleCnt - 1], sizeof(smTM_SCALE));
		TmScale[TmScaleCnt].frame = LastFrame;
		TmScaleCnt++;
	}


	if(TmRotCnt > 0)
	{


		obj->TmPrevRot = new smFMATRIX[TmRotCnt];


		obj->TmRot = new smTM_ROT[TmRotCnt];

		obj->TmRotCnt = TmRotCnt;

		smDIdentityMatrix(dPrevMat);


		for(cnt = 0; cnt < TmRotCnt; cnt++)
		{
			memcpy(&tRot, &TmDRot[cnt], sizeof(smDTM_ROT));


			smDQuaternionFromAxis(tRot.x, tRot.y, tRot.z, tRot.w);

			smDMatrixFromQuaternion(dtmat, tRot.x, tRot.y, tRot.z, tRot.w);
			smDMatrixMult(dPrevMat, dPrevMat, dtmat);



			smFMatrixFromDMatrix(obj->TmPrevRot[cnt], dPrevMat);

		}

		for(cnt = 0; cnt < TmRotCnt; cnt++)
		{
			smQuaternionFromAxis(TmRot[cnt].x, TmRot[cnt].y, TmRot[cnt].z, TmRot[cnt].w);
		}

		memcpy(obj->TmRot, TmRot, sizeof(smTM_ROT) * TmRotCnt);

	}

	if(TmPosCnt > 0)
	{
		obj->TmPos = new smTM_POS[TmPosCnt];
		obj->TmPosCnt = TmPosCnt;
		memcpy(obj->TmPos, TmPos, sizeof(smTM_POS) * TmPosCnt);
	}

	if(TmScaleCnt > 0)
	{
		obj->TmScale = new smTM_SCALE[TmScaleCnt];
		obj->TmScaleCnt = TmScaleCnt;
		memcpy(obj->TmScale, TmScale, sizeof(smTM_SCALE) * TmScaleCnt);
	}

	return fp;
}



void  smASE_SetPhysique(smPAT3D *p)
{
	smPhysique = p;
}


smPAT3D *smASE_GetPhysique()
{
	return smPhysique;
}

char *szFileModelBip = "smb";
char *szFileModel = "smd";


char *smFindFile(char *szfile, char *FileExt, DWORD *lpFileLen)
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	WIN32_FIND_DATA	fd2;

	char *szFileName;


	if(FileExt)
	{
		szFileName = ChangeFileExt(szfile, FileExt);
	}
	else
	{
		szFileName = szfile;
	}

	hFindHandle = FindFirstFile(szFileName, &fd);


	if(hFindHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);
		return FALSE;
	}

	FindClose(hFindHandle);

	if(lpFileLen)
	{
		*lpFileLen = fd.nFileSizeLow;
	}


	if(!FileExt)
	{
		return szFileName;
	}


	hFindHandle = FindFirstFile(szfile, &fd2);

	if(hFindHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);
		return	szFileName;
	}


	if(CompareFileTime(&fd.ftLastWriteTime, &fd2.ftLastWriteTime) < 0)
	{
		return FALSE;
	}

	return szFileName;
}







smPAT3D *smReadModel(char *file, char *szModelName)
{
	smPAT3D *pat;
	int result;

	pat = new smPAT3D;

	result = pat->LoadFile(file, szModelName);

	if(result == FALSE)
	{
		delete pat;
		return NULL;
	}

	return pat;
}

smPAT3D *smReadModel_Bip(char *file)
{
	smPAT3D *pat;
	int result;

	pat = new smPAT3D;

	result = pat->LoadFile(file);

	if(result == FALSE)
	{
		delete pat;
		return NULL;
	}

	return pat;
}





smPAT3D *smASE_Read(char *file, char *szModelName)
{
	FILE *fp;
	smOBJ3D *obj;
	smPAT3D *pat;
	char *szName;
	char *szFile;
	char strBuff[256];
	char *p;

	szName = szModelName;
	if(szName && szName[0] == 0) szName = 0;

	SetDirectoryFromFile(file);

	if(smMeshReload && (szFile = smFindFile(file, szFileModel)))
	{
		pat = smReadModel(szFile, szName);
		if(pat) return pat;
	}

	fp = fopen(file, "rt");

	if(fp == NULL) return FALSE;

	pat = new smPAT3D;



	s_bLightMapStage = FALSE;
	s_LightMapRefMax = 0;
	::ZeroMemory(s_LightMapRefBuff, sizeof(s_LightMapRefBuff));

	smMATERIAL_GROUP *lpMaterialGroup = NULL;


	while(!feof(fp))
	{

		if(fgets(line, 255, fp) == NULL)
		{
			break;
		}

		p = GetWord(decode, line);



		if(lstrcmp(decode, "*MATERIAL_LIST") == 0)
		{
			if((fp = ReadASE_LIGHTMAP_MATERIAL(fp, &lpMaterialGroup)) == FALSE)
				return FALSE;

			pat->smMaterialGroup = lpMaterialGroup;
			smMatPattern = pat->smMaterialGroup->smMaterial;
		}





		if(lstrcmp(decode, "*SCENE_LASTFRAME") == 0)
		{
			p = GetWord(strBuff, p);
			AseSceneLastFrame = atoi(strBuff)*SCENE_TICKSPERFRAME;
		}

		if(lstrcmp(decode, "*GEOMOBJECT") == 0)
		{
			obj = new smOBJ3D;


			fp = ReadASE_GEOMOBJECT(fp, obj);



			if((obj->NodeName[0] == 'B' && obj->NodeName[1] == 'i' && obj->NodeName[2] == 'p'))
			{
				delete obj;
			}
			else
			{
				obj->SortVertex();
				pat->AddObject(obj);
			}

		}

	}

	fclose(fp);

	pat->TmParent = smPhysique;

	if(smPhysique) pat->ReformPhysique();
	else
	{
		pat->LinkObject();
		pat->ReformTM();
	}

	szFile = ChangeFileExt(file, szFileModel);
	pat->SaveFile(szFile);




	delete pat;

	pat = smReadModel(szFile, szName);

	return pat;

}



smPAT3D *smASE_ReadBone(char *file)
{
	FILE *fp;
	smOBJ3D *obj;
	smPAT3D *pat;
	char *szFile;
	char strBuff[256];
	char *p;

	smMatPattern = smMaterial;

	if(smMeshReload && (szFile = smFindFile(file, szFileModelBip)))
	{
		pat = smReadModel_Bip(szFile);
		if(pat) return pat;
	}

	fp = fopen(file, "rt");
	if(fp == NULL)
	{
		if(szFile = smFindFile(file, szFileModelBip))
		{
			return smReadModel_Bip(szFile);
		}
		return FALSE;
	}

	pat = new smPAT3D;

	while(!feof(fp))
	{

		if(fgets(line, 255, fp) == NULL)
		{
			break;


		}


		p = GetWord(decode, line);










		if(lstrcmp(decode, "*SCENE_LASTFRAME") == 0)
		{
			p = GetWord(strBuff, p);
			AseSceneLastFrame = atoi(strBuff)*SCENE_TICKSPERFRAME;
		}

		if(lstrcmp(decode, "*GEOMOBJECT") == 0)
		{
			obj = new smOBJ3D;
			fp = ReadASE_GEOMOBJECT(fp, obj);

			if(obj->NodeName[0] == 'B' && obj->NodeName[1] == 'i' && obj->NodeName[2] == 'p')
				pat->AddObject(obj);
			else
				delete obj;

		}
	}

	fclose(fp);

	pat->LinkObject();
	pat->ReformTM();
	smPhysique = pat;

	szFile = ChangeFileExt(file, szFileModelBip);
	pat->SaveFile(szFile);

	return pat;
}




smPAT3D* smASE_TalkReadBone(char *file)
{
	FILE *fp;
	smOBJ3D *HeadObj = NULL;
	smOBJ3D *obj;
	smPAT3D *pat;
	char *szFile;
	char strBuff[256];
	char *p;

	smMatPattern = smMaterial;

	if(smMeshReload && (szFile = smFindFile(file, szFileModelBip)))
	{
		pat = smReadModel_Bip(szFile);
		if(pat)
			return pat;
	}

	fp = fopen(file, "rt");
	if(fp == NULL)
	{
		if(szFile = smFindFile(file, szFileModelBip))
		{
			return smReadModel_Bip(szFile);
		}
		return FALSE;
	}

	pat = new smPAT3D;

	while(!feof(fp))
	{

		if(fgets(line, 255, fp) == NULL)
			break;

		p = GetWord(decode, line);


		if(lstrcmp(decode, "*SCENE_LASTFRAME") == 0)
		{
			p = GetWord(strBuff, p);
			AseSceneLastFrame = atoi(strBuff) * SCENE_TICKSPERFRAME;
		}

		if(lstrcmp(decode, "*GEOMOBJECT") == 0)
		{
			obj = new smOBJ3D;
			fp = ReadASE_GEOMOBJECT(fp, obj);

			if(obj->NodeName[0] == 'B' && obj->NodeName[1] == 'i' && obj->NodeName[2] == 'p')
			{
				if(obj->TmRotCnt || obj->TmPosCnt)
					pat->AddObject(obj);
				else
				{
					char *lpBuff = strstr(obj->NodeName, "Head");
					if(lpBuff && *(lpBuff - 1) == 32 && (lpBuff[4] == 32 || lpBuff[4] == 0))
					{
						HeadObj = obj;
						obj->NodeParent[0] = 0;
						pat->AddObject(obj);
					}
				}
			}
			else
				delete obj;
		}
	}

	fclose(fp);

	pat->LinkObject();
	pat->ReformTM();
	smPhysique = pat;

	if(HeadObj)
		strcpy(HeadObj->NodeName, "Head");

	szFile = ChangeFileExt(file, szFileModelBip);
	pat->SaveFile(szFile);

	return pat;
}







smPAT3D* smASE_MergeBone(char *szMeshFile, char **FileList, int FileCnt, int ReadType)

{
	smPAT3D *PatList[256];
	smPAT3D *Pat3d;
	smOBJ3D *Obj3d;
	smOBJ3D *Obj3d2;
	int cnt, cnt2, cnt3;
	int TmCnt;
	int NextFrame;
	int TmRotCnt;
	int TmPosCnt;
	int TmScaleCnt;
	char *szFile;

	int TmFrameCnt;
	smFRAME_POS TmFrame[OBJ_FRAME_SEARCH_MAX];







	if(ReadType)
	{
		for(cnt = 0; cnt < FileCnt; cnt++)
		{
			smPhysique = 0;
			PatList[cnt] = smASE_ReadBone(FileList[cnt]);
		}
	}
	else
	{
		for(cnt = 0; cnt < FileCnt; cnt++)
		{
			smPhysique = 0;
			PatList[cnt] = smASE_TalkReadBone(FileList[cnt]);
		}
	}


	Pat3d = new smPAT3D;

	NextFrame = 0;
	TmRotCnt = 0;
	TmPosCnt = 0;
	TmScaleCnt = 0;
	TmFrameCnt = 0;


	for(cnt = 0; cnt < FileCnt; cnt++)
	{
		for(cnt2 = 0; cnt2 < PatList[cnt]->nObj3d; cnt2++)
		{
			Obj3d2 = PatList[cnt]->obj3d[cnt2];
			Obj3d = Pat3d->GetObjectFromName(Obj3d2->NodeName);
			if(Obj3d == NULL)
			{
				Obj3d = new smOBJ3D(0, 0);

				strcpy_s(Obj3d->NodeName, Obj3d2->NodeName);
				strcpy_s(Obj3d->NodeParent, Obj3d2->NodeParent);

				Obj3d->qx = Obj3d2->qx;
				Obj3d->qy = Obj3d2->qy;
				Obj3d->qz = Obj3d2->qz;
				Obj3d->qw = Obj3d2->qw;

				Obj3d->sx = Obj3d2->sx;
				Obj3d->sy = Obj3d2->sy;
				Obj3d->sz = Obj3d2->sz;

				Obj3d->px = Obj3d2->px;
				Obj3d->py = Obj3d2->py;
				Obj3d->pz = Obj3d2->pz;

				memcpy(&Obj3d->Tm, &Obj3d2->Tm, sizeof(smMATRIX));
				memcpy(&Obj3d->TmInvert, &Obj3d2->TmInvert, sizeof(smMATRIX));
				memcpy(&Obj3d->TmRotate, &Obj3d2->TmRotate, sizeof(smMATRIX));

				for(cnt3 = 0; cnt3 < OBJ_FRAME_SEARCH_MAX; cnt3++)
				{
					Obj3d->TmRotFrame[cnt3].StartFrame = -1;
					Obj3d->TmRotFrame[cnt3].EndFrame = -1;
					Obj3d->TmRotFrame[cnt3].PosNum = -1;
					Obj3d->TmRotFrame[cnt3].PosCnt = 0;

					Obj3d->TmPosFrame[cnt3].StartFrame = -1;
					Obj3d->TmPosFrame[cnt3].EndFrame = -1;
					Obj3d->TmPosFrame[cnt3].PosNum = -1;
					Obj3d->TmPosFrame[cnt3].PosCnt = 0;

					Obj3d->TmScaleFrame[cnt3].StartFrame = -1;
					Obj3d->TmScaleFrame[cnt3].EndFrame = -1;
					Obj3d->TmScaleFrame[cnt3].PosNum = -1;
					Obj3d->TmScaleFrame[cnt3].PosCnt = 0;
				}

				Obj3d->TmRotCnt = 0;
				Obj3d->TmPosCnt = 0;
				Obj3d->TmScaleCnt = 0;

				Pat3d->AddObject(Obj3d);
			}

			Obj3d->TmRotFrame[cnt].PosNum = Obj3d->TmRotCnt;
			Obj3d->TmPosFrame[cnt].PosNum = Obj3d->TmPosCnt;
			Obj3d->TmScaleFrame[cnt].PosNum = Obj3d->TmScaleCnt;

			Obj3d->TmRotFrame[cnt].PosCnt = Obj3d2->TmRotCnt;
			Obj3d->TmPosFrame[cnt].PosCnt = Obj3d2->TmPosCnt;
			Obj3d->TmScaleFrame[cnt].PosCnt = Obj3d2->TmScaleCnt;

			Obj3d->TmRotCnt += Obj3d2->TmRotCnt;
			Obj3d->TmPosCnt += Obj3d2->TmPosCnt;
			Obj3d->TmScaleCnt += Obj3d2->TmScaleCnt;

		}

		TmFrame[cnt].StartFrame = NextFrame;
		NextFrame += PatList[cnt]->MaxFrame;
		TmFrame[cnt].EndFrame = NextFrame;
	}

	memcpy(Pat3d->TmFrame, TmFrame, sizeof(smFRAME_POS) * OBJ_FRAME_SEARCH_MAX);
	Pat3d->TmFrameCnt = FileCnt;

	Pat3d->MaxFrame = NextFrame;


	for(cnt = 0; cnt < Pat3d->nObj3d; cnt++)
	{
		Obj3d = Pat3d->obj3d[cnt];
		if(Obj3d)
		{

			Obj3d->TmRot = new smTM_ROT[Obj3d->TmRotCnt];
			Obj3d->TmPos = new smTM_POS[Obj3d->TmPosCnt];
			Obj3d->TmScale = new smTM_SCALE[Obj3d->TmScaleCnt];



			Obj3d->TmPrevRot = new smFMATRIX[Obj3d->TmRotCnt];


			Obj3d->TmFrameCnt = FileCnt;

			for(cnt2 = 0; cnt2 < FileCnt; cnt2++)
			{
				Obj3d->TmRotFrame[cnt2].StartFrame = TmFrame[cnt2].StartFrame;
				Obj3d->TmRotFrame[cnt2].EndFrame = TmFrame[cnt2].EndFrame;
				Obj3d->TmPosFrame[cnt2].StartFrame = TmFrame[cnt2].StartFrame;
				Obj3d->TmPosFrame[cnt2].EndFrame = TmFrame[cnt2].EndFrame;
				Obj3d->TmScaleFrame[cnt2].StartFrame = TmFrame[cnt2].StartFrame;
				Obj3d->TmScaleFrame[cnt2].EndFrame = TmFrame[cnt2].EndFrame;
			}

		}
	}


	for(cnt = 0; cnt < FileCnt; cnt++)
	{
		for(cnt2 = 0; cnt2 < PatList[cnt]->nObj3d; cnt2++)
		{
			Obj3d2 = PatList[cnt]->obj3d[cnt2];
			Obj3d = Pat3d->GetObjectFromName(Obj3d2->NodeName);

			if(Obj3d)
			{


				TmCnt = Obj3d->TmRotFrame[cnt].PosNum;
				if(TmCnt >= 0)
				{
					for(cnt3 = 0; cnt3 < Obj3d2->TmRotCnt; cnt3++)
					{
						memcpy(&Obj3d->TmRot[TmCnt], &Obj3d2->TmRot[cnt3], sizeof(smTM_ROT));
						memcpy(&Obj3d->TmPrevRot[TmCnt], &Obj3d2->TmPrevRot[cnt3], sizeof(smMATRIX));


						Obj3d->TmRot[TmCnt].frame += TmFrame[cnt].StartFrame;
						TmCnt++;
					}
				}


				TmCnt = Obj3d->TmPosFrame[cnt].PosNum;
				if(TmCnt >= 0)
				{
					for(cnt3 = 0; cnt3 < Obj3d2->TmPosCnt; cnt3++)
					{
						memcpy(&Obj3d->TmPos[TmCnt], &Obj3d2->TmPos[cnt3], sizeof(smTM_POS));

						Obj3d->TmPos[TmCnt].frame += TmFrame[cnt].StartFrame;
						TmCnt++;
					}
				}


				TmCnt = Obj3d->TmScaleFrame[cnt].PosNum;
				if(TmCnt >= 0)
				{
					for(cnt3 = 0; cnt3 < Obj3d2->TmScaleCnt; cnt3++)
					{
						memcpy(&Obj3d->TmScale[TmCnt], &Obj3d2->TmScale[cnt3], sizeof(smTM_SCALE));
						Obj3d->TmScale[TmCnt].frame += TmFrame[cnt].StartFrame;
						TmCnt++;
					}
				}

			}
		}
	}



	Pat3d->LinkObject();


	szFile = ChangeFileExt(szMeshFile, szFileModelBip);

	Pat3d->SaveFile(szFile);

	for(cnt = FileCnt - 1; cnt >= 0; cnt--)
	{
		if(PatList[cnt]) delete PatList[cnt];
	}

	return Pat3d;
}







FILE *smSTAGE3D_ReadASE_GEOMOBJECT(FILE *fp, smSTAGE3D *smStage)
{
	char strBuff[256];
	char *p;
	int strLevel;
	int nVertex;
	int nFace;
	int nTVertex;
	int nTFace;
	int InitTFlag;

	int VertexCnt;
	int FaceCnt;
	int TVertexCnt;
	int TFaceCnt;

	int ObjVertex;
	int ObjFace;

	int x, y, z;
	int a, b, c;
	smFTPOINT	*tPoint;
	smTFACE		*tFace;

	smFCPOINT	*cPoint = 0;
	smTFACE		*cFace = 0;
	int			ncVert;
	int			ncFace;
	int			cvertCnt = 0;
	int			cfaceCnt = 0;

	int *FaceMatrial = 0;
	int mCount = 0;
	int MatrialRef = 0;
	int cnt, cnt2;




	int			 bLightMap = 0;

	smFTPOINT	*tLightMapPoint = NULL;
	smTFACE		*tLightMapFace = NULL;
	smFTPOINT	*lpTexVertex = NULL;
	smTFACE		*lpTexFace = NULL;



	ObjFace = smStage->nFace;
	ObjVertex = smStage->nVertex;

	tPoint = 0;
	tFace = 0;

	nVertex = -1;
	nFace = -1;

	nTVertex = -1;
	nTFace = -1;
	InitTFlag = 0;

	TVertexCnt = 0;
	TFaceCnt = 0;
	VertexCnt = 0;
	FaceCnt = 0;


	strLevel = 0;

	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)
		{
			fclose(fp);
			return FALSE;
		}

		p = GetWord(decode, line);

		if(lstrcmp(decode, "*NODE_NAME") == 0)
		{
			p = GetWord(strBuff, p);

		}


		if(lstrcmp(decode, "*MESH_NUMVERTEX") == 0)
		{
			p = GetWord(strBuff, p);
			nVertex = atoi(strBuff);
		}

		if(lstrcmp(decode, "*MESH_NUMFACES") == 0)
		{
			p = GetWord(strBuff, p);
			nFace = atoi(strBuff);

			FaceMatrial = new int[nFace];
		}




		if(lstrcmp(decode, "*MESH_NUMTVERTEX") == 0)
		{
			p = GetWord(strBuff, p);
			nTVertex = atoi(strBuff);

			if(bLightMap)
			{
				tLightMapPoint = new smFTPOINT[nTVertex];
				tLightMapFace = new smTFACE[nFace];

				lpTexVertex = tLightMapPoint;
				lpTexFace = tLightMapFace;
			}
			else
			{
				tPoint = new smFTPOINT[nTVertex];
				tFace = new smTFACE[nFace];

				lpTexVertex = tPoint;
				lpTexFace = tFace;
			}

			TVertexCnt = TFaceCnt = 0;
		}

		if(lstrcmp(decode, "*MESH_MAPPINGCHANNEL") == 0)
		{
			p = GetWord(strBuff, p);
			bLightMap = 1;
		}


		if(lstrcmp(decode, "*MESH_VERTEX") == 0)
		{
			p = GetWord(strBuff, p);

			if(atoi(strBuff) != VertexCnt)
			{
				////Utils_//LOG(LOG_ERROR, "Vetex Counter Error (ReadAse)");
			}

			p = GetWord(strBuff, p);
			x = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			z = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			y = (int)(atof(strBuff)*fONE);

			smStage->AddVertex(x, y, z);

			VertexCnt++;
		}


		if(lstrcmp(decode, "*MESH_FACE") == 0)
		{
			p = GetWord(strBuff, p);

			if(atoi(strBuff) != FaceCnt)
			{
			//	//Utils_//LOG(LOG_ERROR, "Face Counter Error (ReadAse)");
			}

			p = GetWord(strBuff, p);
			p = GetWord(strBuff, p);
			a = (int)atoi(strBuff);

			p = GetWord(strBuff, p);
			p = GetWord(strBuff, p);
			b = (int)atoi(strBuff);

			p = GetWord(strBuff, p);
			p = GetWord(strBuff, p);
			c = (int)atoi(strBuff);

			for(cnt = 0; cnt < 16; cnt++)
			{
				p = GetWord(strBuff, p);
				if(lstrcmp(strBuff, "*MESH_MTLID") == 0)
				{

					p = GetWord(strBuff, p);
					FaceMatrial[mCount++] = atoi(strBuff);
					break;
				}
			}

			smStage->AddFace(a + ObjVertex, b + ObjVertex, c + ObjVertex);

			FaceCnt++;
		}




		if(lstrcmp(decode, "*MESH_TVERT") == 0)
		{
			p = GetWord(strBuff, p);

			if(atoi(strBuff) != TVertexCnt)
			{
				////Utils_//LOG(LOG_ERROR, "TVetex Counter Error (ReadAse)");
			}

			p = GetWord(strBuff, p);
			lpTexVertex[TVertexCnt].u = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			lpTexVertex[TVertexCnt].v = -(float)atof(strBuff);
			p = GetWord(strBuff, p);

			TVertexCnt++;
		}


		if(lstrcmp(decode, "*MESH_TFACE") == 0)
		{
			p = GetWord(strBuff, p);

			if(atoi(strBuff) != TFaceCnt)
			{
				////Utils_//LOG(LOG_ERROR, "TFace Counter Error (ReadAse)");
			}

			p = GetWord(strBuff, p);
			lpTexFace[TFaceCnt].t[0] = (int)atoi(strBuff);
			p = GetWord(strBuff, p);
			lpTexFace[TFaceCnt].t[1] = (int)atoi(strBuff);
			p = GetWord(strBuff, p);
			lpTexFace[TFaceCnt].t[2] = (int)atoi(strBuff);

			TFaceCnt++;
		}





		if(lstrcmp(decode, "*MESH_NUMCVERTEX") == 0)
		{
			p = GetWord(strBuff, p);
			ncVert = atoi(strBuff);
			cPoint = new smFCPOINT[ncVert];
		}

		if(lstrcmp(decode, "*MESH_NUMCVFACES") == 0)
		{
			p = GetWord(strBuff, p);
			ncFace = atoi(strBuff);
			cFace = new smTFACE[ncFace];
		}


		if(lstrcmp(decode, "*MESH_VERTCOL") == 0)
		{
			p = GetWord(strBuff, p);

			p = GetWord(strBuff, p);
			cPoint[cvertCnt].r = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			cPoint[cvertCnt].g = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			cPoint[cvertCnt].b = (float)atof(strBuff);

			cvertCnt++;
		}


		if(lstrcmp(decode, "*MESH_CFACE") == 0)
		{
			p = GetWord(strBuff, p);

			p = GetWord(strBuff, p);
			cFace[cfaceCnt].t[0] = (int)atoi(strBuff);
			p = GetWord(strBuff, p);
			cFace[cfaceCnt].t[1] = (int)atoi(strBuff);
			p = GetWord(strBuff, p);
			cFace[cfaceCnt].t[2] = (int)atoi(strBuff);

			cfaceCnt++;
		}





		if(lstrcmp(decode, "*MATERIAL_REF") == 0)
		{
			p = GetWord(strBuff, p);
			MatrialRef = atoi(strBuff);
		}


		p = GetWord(strBuff, p);
		if(lstrcmp(decode, "{") == 0 ||
		   lstrcmp(strBuff, "{") == 0)
			strLevel++;

		if(lstrcmp(decode, "}") == 0 ||
		   lstrcmp(strBuff, "}") == 0)
		{
			strLevel--;
			if(strLevel < 0) break;
		}
	}




	int fmat;
	float fu, fv, fU, fV;
	float fOffset_u, fOffset_v;
	float fTiling_u, fTiling_v;
	float fAngle, fSin, fCos;
	int TexCnt, tcnt;
	int mNum;
	smFTPOINT	ftpoint[3];


	if(nTVertex > 0)
	{
		for(cnt = 0; cnt < nFace; cnt++)
		{
			if(aseMaterial[MatrialRef].SubPoint)
				fmat = aseMaterial[MatrialRef].SubPoint + FaceMatrial[cnt];
			else
				fmat = MatrialRef;



			mNum = aseMaterial[fmat].RegistNum;


			smStage->smMaterial[mNum].InUse++;


			TexCnt = smStage->smMaterial[mNum].TextureCounter;



			if(bLightMap)
				TexCnt--;


			for(tcnt = 0; tcnt < TexCnt; tcnt++)
			{


				fOffset_u = aseMaterial[fmat].UVW_U_OFFSET[tcnt];
				fOffset_v = aseMaterial[fmat].UVW_V_OFFSET[tcnt];
				fTiling_u = aseMaterial[fmat].UVW_U_TILING[tcnt];
				fTiling_v = aseMaterial[fmat].UVW_V_TILING[tcnt];
				fAngle = (float)(aseMaterial[fmat].UVW_ANGLE[tcnt] * smMULT_PIE);
				fSin = ((float)GetSin[((int)fAngle) & ANGLE_MASK]) / 65536;
				fCos = ((float)GetCos[((int)fAngle) & ANGLE_MASK]) / 65536;

				for(cnt2 = 0; cnt2 < 3; cnt2++)
				{

					fU = (float)(tPoint[tFace[cnt].t[cnt2]].u - 0.5);
					fV = (float)(tPoint[tFace[cnt].t[cnt2]].v - 0.5);

					fu = (fU * fCos) + (fV * fSin);
					fv = (fV * fCos) - (fU * fSin);

					fu -= fOffset_u;
					fv -= fOffset_v;

					fu *= fTiling_u;
					fv *= fTiling_v;

					fu += 0.5;
					fv += 0.5;

					ftpoint[cnt2].u = fu;
					ftpoint[cnt2].v = fv;
				}

				smStage->AddTexLink(cnt + ObjFace, (DWORD*)&smStage->smMaterial[mNum].smTexture[tcnt], &ftpoint[0], &ftpoint[1], &ftpoint[2]);
			}



			if(bLightMap)
			{

				fOffset_u = aseMaterial[fmat].UVW_U_OFFSET[tcnt];
				fOffset_v = aseMaterial[fmat].UVW_V_OFFSET[tcnt];
				fTiling_u = aseMaterial[fmat].UVW_U_TILING[tcnt];
				fTiling_v = aseMaterial[fmat].UVW_V_TILING[tcnt];
				fAngle = (float)(aseMaterial[fmat].UVW_ANGLE[tcnt] * smMULT_PIE);
				fSin = ((float)GetSin[((int)fAngle) & ANGLE_MASK]) / 65536;
				fCos = ((float)GetCos[((int)fAngle) & ANGLE_MASK]) / 65536;

				for(cnt2 = 0; cnt2 < 3; cnt2++)
				{
					fU = (float)(tLightMapPoint[tLightMapFace[cnt].t[cnt2]].u - 0.5);
					fV = (float)(tLightMapPoint[tLightMapFace[cnt].t[cnt2]].v - 0.5);

					fu = (fU * fCos) + (fV * fSin);
					fv = (fV * fCos) - (fU * fSin);

					fu -= fOffset_u;
					fv -= fOffset_v;

					fu *= fTiling_u;
					fv *= fTiling_v;

					fu += 0.5;
					fv += 0.5;

					ftpoint[cnt2].u = fu;
					ftpoint[cnt2].v = fv;
				}

				smStage->AddTexLink(cnt + ObjFace, (DWORD*)&smStage->smMaterial[mNum].smTexture[tcnt], &ftpoint[0], &ftpoint[1], &ftpoint[2]);
			}



			smStage->SetFaceMaterial(cnt + ObjFace, mNum);
		}
	}
	else
	{

		smFTPOINT ftp;
		ftp.u = 0;
		ftp.v = 0;

		for(cnt = 0; cnt < nFace; cnt++)
		{
			smStage->SetFaceMaterial(cnt + ObjFace, 0);
			smStage->AddTexLink(cnt + ObjFace, 0, &ftp, &ftp, &ftp);
		}
	}




	smFCPOINT  *cVertex;
	int	       *cNumVertex;
	int			vnum;
	int			vcnt;

	int		bR, bG, bB;

	if(cfaceCnt)
	{
		cVertex = new smFCPOINT[nVertex];
		cNumVertex = new int[nVertex];

		for(cnt = 0; cnt < nVertex; cnt++)
		{
			cVertex[cnt].r = 1;
			cVertex[cnt].g = 1;
			cVertex[cnt].b = 1;
			cNumVertex[cnt] = 1;
		}

		for(cnt = 0; cnt < nFace; cnt++)
		{
			for(vcnt = 0; vcnt < 3; vcnt++)
			{
				vnum = smStage->Face[cnt + ObjFace].Vertex[vcnt] - ObjVertex;
				cVertex[vnum].r += cPoint[cFace[cnt].t[vcnt]].r;
				cVertex[vnum].g += cPoint[cFace[cnt].t[vcnt]].g;
				cVertex[vnum].b += cPoint[cFace[cnt].t[vcnt]].b;
				cNumVertex[vnum] ++;
			}
		}

		for(cnt = 0; cnt < nVertex; cnt++)
		{
			vcnt = cNumVertex[cnt];
			if(vcnt)
			{
				cVertex[cnt].r /= vcnt;
				cVertex[cnt].g /= vcnt;
				cVertex[cnt].b /= vcnt;

				bR = (BYTE)(cVertex[cnt].r * 255);
				bG = (BYTE)(cVertex[cnt].g * 255);
				bB = (BYTE)(cVertex[cnt].b * 255);

				smStage->SetVertexColor(ObjVertex + cnt, bR, bG, bB);
			}
		}


		delete cNumVertex;
		delete cVertex;


	}




	if(cFace) delete cFace;
	if(cPoint) delete cPoint;
	if(FaceMatrial) delete FaceMatrial;
	if(tPoint) delete tPoint;
	if(tFace) delete tFace;
	if(tLightMapPoint)	 delete tLightMapPoint;
	if(tLightMapFace)	 delete tLightMapFace;

	return fp;
}



FILE *smReadASE_LIGHTOBJECT(FILE *fp, smASE_LIGHT *smLight)
{

	char strBuff[256];
	char *p;
	int strLevel;
	int Intens;
	int col;

	strLevel = 0;

	smLight->Type = 0;

	Intens = 0;


	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)
		{
			fclose(fp);
			return FALSE;
		}

		p = GetWord(decode, line);


		if(lstrcmp(decode, "*NODE_NAME") == 0)
		{
			p = GetString(strBuff, p);
			strBuff[31] = 0;
			if(strstr(strBuff, "dynamic:") != 0)
			{
				smLight->Type |= smLIGHT_TYPE_DYNAMIC;
			}
			if(strstr(strBuff, "night:") != 0)
			{
				smLight->Type |= smLIGHT_TYPE_DYNAMIC;
				smLight->Type |= smLIGHT_TYPE_NIGHT;
			}
			if(strstr(strBuff, "lens:") != 0)
			{
				smLight->Type |= smLIGHT_TYPE_DYNAMIC;
				smLight->Type |= smLIGHT_TYPE_LENS;
			}



			if(strstr(strBuff, "obj:") != 0)
			{
				smLight->Type |= smLIGHT_TYPE_DYNAMIC;
				smLight->Type |= SMLIGHT_TYPE_OBJ;
			}

		}


		if(lstrcmp(decode, "*LIGHT_COLOR") == 0)
		{
			p = GetWord(strBuff, p);
			smLight->r = (int)(atof(strBuff) * 255);
			p = GetWord(strBuff, p);
			smLight->g = (int)(atof(strBuff) * 255);
			p = GetWord(strBuff, p);
			smLight->b = (int)(atof(strBuff) * 255);

		}


		if(lstrcmp(decode, "*LIGHT_INTENS") == 0)
		{
			p = GetWord(strBuff, p);
			Intens = (int)(atof(strBuff)*fONE);
		}


		if(lstrcmp(decode, "*TM_POS") == 0)
		{
			p = GetWord(strBuff, p);
			smLight->x = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			smLight->z = (int)(atof(strBuff)*fONE);
			p = GetWord(strBuff, p);
			smLight->y = (int)(atof(strBuff)*fONE);
		}


		if(lstrcmp(decode, "*LIGHT_MAPRANGE") == 0)
		{
			p = GetWord(strBuff, p);
			smLight->Range = (int)((atof(strBuff)*fONE) / 4 * fONE);



		}

		p = GetWord(strBuff, p);
		if(lstrcmp(decode, "{") == 0 ||
		   lstrcmp(strBuff, "{") == 0)
			strLevel++;

		if(lstrcmp(decode, "}") == 0 ||
		   lstrcmp(strBuff, "}") == 0)
		{
			strLevel--;
			if(strLevel < 0) break;
		}
	}

	if(Intens)
	{

		if(Intens >= 0 && Intens < 64) Intens = 64;
		if(Intens<0 && Intens>-64) Intens = -64;

		col = (smLight->r*Intens) >> FLOATNS;
		smLight->r = col;

		col = (smLight->g*Intens) >> FLOATNS;
		smLight->g = col;

		col = (smLight->b*Intens) >> FLOATNS;
		smLight->b = col;
	}
	return fp;
}

FILE *smSTAGE3D_GetASE_Info(FILE *fp, int *pVertex, int *pFace)
{
	char strBuff[256];
	char *p;
	int strLevel;
	int nVertex;
	int nFace;
	int nTVertex;
	int nTFace;
	int InitFlag;
	int InitTFlag;

	int VertexCnt;
	int FaceCnt;
	int TVertexCnt;
	int TFaceCnt;

	smTPOINT *tPoint;
	tPoint = 0;

	nVertex = -1;
	nFace = -1;
	InitFlag = 0;

	nTVertex = -1;
	nTFace = -1;
	InitTFlag = 0;

	TVertexCnt = 0;
	TFaceCnt = 0;
	VertexCnt = 0;
	FaceCnt = 0;


	strLevel = 0;

	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)
		{
			fclose(fp);
			return FALSE;
		}

		p = GetWord(decode, line);

		if(lstrcmp(decode, "*MESH_NUMVERTEX") == 0)
		{
			p = GetWord(strBuff, p);
			nVertex = atoi(strBuff);
		}
		if(lstrcmp(decode, "*MESH_NUMFACES") == 0)
		{
			p = GetWord(strBuff, p);
			nFace = atoi(strBuff);
		}
		if(lstrcmp(decode, "*MESH_NUMTVERTEX") == 0)
		{
			p = GetWord(strBuff, p);
			nTVertex = atoi(strBuff);





		}

		p = GetWord(strBuff, p);
		if(lstrcmp(decode, "{") == 0 ||
		   lstrcmp(strBuff, "{") == 0)
			strLevel++;

		if(lstrcmp(decode, "}") == 0 ||
		   lstrcmp(strBuff, "}") == 0)
		{
			strLevel--;
			if(strLevel < 0) break;
		}
	}

	*pVertex = nVertex;
	*pFace = nFace;


	return fp;
}


smSTAGE3D *smReadStage(char *file, smSTAGE3D *smStagep)
{
	smSTAGE3D *smStage;
	int result;

	if(smStagep)
		smStage = smStagep;
	else
		smStage = new smSTAGE3D;

	result = smStage->LoadFile(file);

	if(result == FALSE)
	{
		if(!smStagep)
		{
			smStage->Init(0, 0);
			delete smStage;
		}
		return NULL;
	}

	return smStage;
}









smSTAGE3D *smSTAGE3D_ReadASE(char *file, smSTAGE3D *smStagep)
{
	FILE *fp;
	int nVertex, nFace;
	int pVertex, pFace;
	smSTAGE3D *smStage;
	char	*szFile;
	char	szObjFlag[2048];
	int		ObjCnt;
	int		cnt;
	int		dLightCnt;


	smASE_LIGHT	smAseLight[256];
	int	AseLightCnt = 0;
	POINT3D	plight;

	nVertex = 0;
	nFace = 0;

	SetDirectoryFromFile(file);

	if(smMeshReload && (szFile = smFindFile(file, szFileModel)))
	{
		smStage = smReadStage(szFile, smStagep);

		if(smStage)
		{
			return smStage;
		}
	}

	fp = fopen(file, "rt");

	if(fp == NULL)
	{
		return FALSE;
	}

	s_bLightMapStage = FALSE;
	s_LightMapRefMax = 0;
	::ZeroMemory(s_LightMapRefBuff, sizeof(s_LightMapRefBuff));

	smMATERIAL_GROUP *lpMaterialGroup = NULL;

	ObjCnt = 0;

	while(!feof(fp))
	{

		if(fgets(line, 255, fp) == NULL)
		{
			break;
		}

		GetWord(decode, line);

		if(lstrcmp(decode, "*MATERIAL_LIST") == 0)
		{
			if((fp = ReadASE_LIGHTMAP_MATERIAL(fp, &lpMaterialGroup)) == FALSE)
			{
				return FALSE;
			}
		}

		if(lstrcmp(decode, "*GEOMOBJECT") == 0)
		{
			fp = smSTAGE3D_GetASE_Info(fp, &pVertex, &pFace);

			nVertex += pVertex;
			nFace += pFace;

			if(pVertex == 0 || pFace == 0)
			{
				szObjFlag[ObjCnt] = 0;
			}
			else
			{
				szObjFlag[ObjCnt] = 1;
			}

			ObjCnt++;
		}
	}

	fclose(fp);

	if(smStagep)
	{
		smStage = smStagep;
		smStage->Init(nVertex, nFace);
	}
	else
	{
		smStage = new smSTAGE3D(nVertex, nFace);
	}

	smStage->smMaterialGroup = lpMaterialGroup;
	smStage->smMaterial = smStage->smMaterialGroup->smMaterial;


	fp = fopen(file, "rt");

	if(fp == NULL)
	{
		return FALSE;
	}

	ObjCnt = 0;

	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)
		{
			break;
		}

		GetWord(decode, line);

		if(lstrcmp(decode, "*LIGHTOBJECT") == 0)
		{
			fp = smReadASE_LIGHTOBJECT(fp, &smAseLight[AseLightCnt++]);
		}

		if(lstrcmp(decode, "*GEOMOBJECT") == 0)
		{
			if(szObjFlag[ObjCnt])
			{
				fp = smSTAGE3D_ReadASE_GEOMOBJECT(fp, smStage);
			}

			ObjCnt++;
		}
	}

	fclose(fp);

	smStage->SetupPolyAreas();

	smStage->SetVertexShade(!s_bLightMapStage);

	dLightCnt = 0;

	for(cnt = 0; cnt < AseLightCnt; cnt++)
	{
		if((smAseLight[cnt].Type&smLIGHT_TYPE_DYNAMIC) == 0)
		{
			plight.x = smAseLight[cnt].x;
			plight.y = smAseLight[cnt].y;
			plight.z = smAseLight[cnt].z;
			smStage->AddVertexLightRound(&plight,
										 smAseLight[cnt].r,
										 smAseLight[cnt].g,
										 smAseLight[cnt].b,
										 smAseLight[cnt].Range);
		}
		else
			dLightCnt++;
	}


	if(dLightCnt > 0)
	{
		smStage->InitDynLight(dLightCnt);
		for(cnt = 0; cnt < AseLightCnt; cnt++)
		{
			if((smAseLight[cnt].Type&smLIGHT_TYPE_DYNAMIC) != 0)
			{
				plight.x = smAseLight[cnt].x;
				plight.y = smAseLight[cnt].y;
				plight.z = smAseLight[cnt].z;

				smStage->AddDynLight(smAseLight[cnt].Type, &plight,
									 smAseLight[cnt].r,
									 smAseLight[cnt].g,
									 smAseLight[cnt].b,
									 smAseLight[cnt].Range);
			}
		}
	}

	if(smMeshReload || smMeshSave)
	{
		szFile = ChangeFileExt(file, szFileModel);
		smStage->SaveFile(szFile);
	}

	return smStage;
}



void smSetMeshReload(int flag, int MeshSave)
{
	smMeshReload = flag;
	smMeshSave = MeshSave;
}
