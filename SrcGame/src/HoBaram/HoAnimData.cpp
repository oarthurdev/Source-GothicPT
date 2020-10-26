

#include "..\\HoBaram\\HoLinkHeader.h"
HoAnimDataMgr	AnimDataMgr;




BOOL GetDirectoryToFileName(char *directoryName, char *getFileName)
{
	int  count = 0;
	for(int index = strlen(directoryName); index > 0; index--)
	{
		if(directoryName[index] == '\\')
		{
			memcpy(getFileName, &directoryName[index + 1], count - 1);
			return TRUE;;
		}
		count++;
	}
	return FALSE;
}

HoAnimSequenceData::HoAnimSequenceData()
{
	AnimFrameCount = 0;
	AnimFrame = NULL;
	DataFileIndex = -1;
	BlendType = 0;
	InfoFlag = 0;

}
HoAnimSequenceData::~HoAnimSequenceData()
{
	Init();
}



int HoAnimSequenceData::Load(char *iniName, HoAnimDataMgr *animationData)
{

	if(iniName == NULL || animationData == NULL)
		return FALSE;

	memset(IniName, 0, sizeof(IniName));

	if(!GetDirectoryToFileName(iniName, IniName))
		return FALSE;


	char buffer[512];

	GetPrivateProfileString("ANIMATION", "DataFile", NULL, buffer, sizeof(buffer), iniName);
	DataFileIndex = animationData->GetSearchAnimImageData(buffer);


	StartBlendValue = GetPrivateProfileInt("ANIMATION", "StartBlendValue", 0, iniName);
	BlendType = GetPrivateProfileInt("ANIMATION", "BlendType", 0, iniName);



	memset(buffer, 0, sizeof(buffer));
	GetPrivateProfileString("ANIMATION", "ImageNum", NULL, buffer, sizeof(buffer), iniName);
	if(strlen(buffer) == 0)
		return FALSE;
	int count = 0;
	for(int index = 0; index < (int)strlen(buffer); index++)
	{
		if(buffer[index] == ',')
			count++;
	}
	AnimFrameCount = count + 1;
	AnimFrame = new hoAnimFrame[AnimFrameCount];
	memset(AnimFrame, 1, sizeof(hoAnimFrame)*AnimFrameCount);




	count = 0;
	int start = 0;
	int end = 0;
	char num[64];
	for(int index = 0; index < (int)strlen(buffer); index++)
	{
		if(buffer[index] == ',')
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);

			AnimFrame[count].ImageNum = (unsigned short)atoi(num);
			count++;
			start = index + 1;
			end = index + 1;
		}
		else if(index == (int)(strlen(buffer) - 1))
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);
			AnimFrame[count].ImageNum = (unsigned short)atoi(num);
		}
		end++;
	}
	InfoFlag |= INFO_IMAGE;



	GetPrivateProfileString("ANIMATION", "Delay", NULL, buffer, sizeof(buffer), iniName);
	if(strlen(buffer) == 0)
		return FALSE;


	count = 0;
	start = 0;
	end = 0;
	for(int index = 0; index < (int)strlen(buffer); index++)
	{
		if(buffer[index] == ',')
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);

			AnimFrame[count].Delay = (unsigned short)atoi(num);
			count++;
			start = index + 1;
			end = index + 1;
		}
		else if(index == (int)(strlen(buffer) - 1))
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);
			AnimFrame[count].Delay = (unsigned short)atoi(num);
		}
		end++;
	}
	InfoFlag |= INFO_DELAY;


	GetPrivateProfileString("ANIMATION", "BlendValue", NULL, buffer, sizeof(buffer), iniName);
	if(strlen(buffer) == 0)
		return FALSE;


	count = 0;
	start = 0;
	end = 0;
	for(int index = 0; index < (int)strlen(buffer); index++)
	{
		if(buffer[index] == ',')
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);

			AnimFrame[count].AlphaValue = (BYTE)atoi(num);
			count++;
			start = index + 1;
			end = index + 1;
		}
		else if(index == (int)(strlen(buffer) - 1))
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);
			AnimFrame[count].AlphaValue = (BYTE)atoi(num);
		}
		end++;
	}
	InfoFlag |= INFO_ALPHA;


	memset(buffer, 0, sizeof(buffer));
	GetPrivateProfileString("ANIMATION", "Size", NULL, buffer, sizeof(buffer), iniName);
	if(strlen(buffer) == 0)
		return TRUE;


	count = 0;
	start = 0;
	end = 0;
	for(int index = 0; index < (int)strlen(buffer); index++)
	{
		if(buffer[index] == ',')
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);

			AnimFrame[count].SizeWidth = (unsigned short)atoi(num);
			count++;
			start = index + 1;
			end = index + 1;
		}
		else if(index == (int)(strlen(buffer) - 1))
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);
			AnimFrame[count].SizeWidth = (unsigned short)atoi(num);
		}
		end++;
	}
	InfoFlag |= INFO_SIZEWIDTH;


	memset(buffer, 0, sizeof(buffer));
	GetPrivateProfileString("ANIMATION", "Angle", NULL, buffer, sizeof(buffer), iniName);
	if(strlen(buffer) == 0)
		return TRUE;



	count = 0;
	start = 0;
	end = 0;
	for(int index = 0; index < (int)strlen(buffer); index++)
	{
		if(buffer[index] == ',')
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);

			int t = atoi(num);
			AnimFrame[count].Angle = float(ANGLE_360*(float(atoi(num)) / 360.f));
			count++;
			start = index + 1;
			end = index + 1;
		}
		else if(index == (int)(strlen(buffer) - 1))
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);
			AnimFrame[count].Angle = float(ANGLE_360*(float(atoi(num)) / 360.f));
		}
		end++;
	}
	InfoFlag |= INFO_ANGLE;

	return TRUE;
}

int HoAnimSequenceData::Init()
{
	InfoFlag = 0;
	if(AnimFrame != NULL)
	{
		delete[] AnimFrame;
		AnimFrame = NULL;
	}
	memset(IniName, 0, sizeof(IniName));

	return TRUE;
}

HoAnimImageData::HoAnimImageData()
{
	AnimationCount = 0;
	MaterialNum = -1;
}

HoAnimImageData::~HoAnimImageData()
{

}

int HoAnimImageData::Load(char *iniName)
{
	int  count = 0;
	for(int index = strlen(iniName); index > 0; index--)
	{
		if(iniName[index] == '\\')
		{
			memcpy(IniName, &iniName[index + 1], count - 1);
			break;
		}
		count++;
	}
	char dataName[512];
	int  dataCount = 0;

	GetPrivateProfileString("IMAGE", "Name", NULL, dataName, sizeof(dataName), iniName);
	dataCount = GetPrivateProfileInt("IMAGE", "Count", 0, iniName);
	Load(dataName, dataCount);

	return TRUE;
}

int HoAnimImageData::Load(char *textureName, int count)
{
	AnimationCount = count;

	char fileName[256];
	char fileExt[64];
	memset(fileName, 0, sizeof(fileName));
	memset(fileExt, 0, sizeof(fileExt));

	for(int cnt = 0; cnt < lstrlen(textureName); cnt++)
	{
		if(textureName[cnt] == '.')
		{
			memset(fileName, 0, sizeof(fileName));
			memcpy(fileName, textureName, cnt);
			memcpy(fileExt, &textureName[cnt + 1], 3);
			break;
		}
	}

	char *szEffect[30];
	memset(szEffect, 0, sizeof(szEffect));

	for(int cnt = 0; cnt < AnimationCount; cnt++)
	{
		szEffect[cnt] = new char[256];

		if(stricmp(fileExt, "bmp") == 0)
			wsprintf(szEffect[cnt], "%s%d%s", fileName, cnt + 1, ".bmp");
		else if(stricmp(fileExt, "tga") == 0)
			wsprintf(szEffect[cnt], "%s%d%s", fileName, cnt + 1, ".tga");
	}

	if(stricmp(fileExt, "bmp") == 0)
	{
		MaterialNum = CreateTextureMaterial(szEffect[0], 0, 0, 0, 0, SMMAT_BLEND_COLOR);
		if(smMaterial[MaterialNum].smTexture == NULL)
		{
			for(int index = 0; index < AnimationCount; index++)
			{
				if(szEffect[index] != NULL)
				{
					delete szEffect[index];
					szEffect[index] = NULL;
				}
			}
			return FALSE;
		}
		smMaterialGroup->ChangeMaterialToAnimation(&smMaterial[MaterialNum], szEffect, AnimationCount, SMMAT_BLEND_COLOR
												   , FALSE);
	}
	else if(stricmp(fileExt, "tga") == 0)
	{
		MaterialNum = CreateTextureMaterial(szEffect[0], 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		if(smMaterial[MaterialNum].smTexture == NULL)
		{
			for(int index = 0; index < AnimationCount; index++)
			{
				if(szEffect[index] != NULL)
				{
					delete szEffect[index];
					szEffect[index] = NULL;
				}
			}
			return FALSE;
		}
		smMaterialGroup->ChangeMaterialToAnimation(&smMaterial[MaterialNum], szEffect, AnimationCount, SMMAT_BLEND_ALPHA, FALSE);
	}

	for(int index = 0; index < AnimationCount; index++)
	{
		if(szEffect[index] != NULL)
		{
			delete szEffect[index];
			szEffect[index] = NULL;
		}
	}
	smMaterial[MaterialNum].TwoSide = TRUE;

	return TRUE;
}

int	HoAnimImageData::Init()
{
	memset(IniName, 0, sizeof(IniName));
	MaterialNum = 0;
	AnimationCount = 0;
	return TRUE;
}

HoAnimDataMgr::HoAnimDataMgr()
{
	Init();

}

HoAnimDataMgr::~HoAnimDataMgr()
{
	Init();
}

int HoAnimDataMgr::SequenceLoad(char *iniName)
{
	if(SequenceDataBufferCount < MAX_SEQUENCEDATA_BUFFER)
	{
		if(!SequenceDataBuffer[SequenceDataBufferCount].Load(iniName, this))
			return FALSE;

		SequenceDataBufferCount++;
		return TRUE;
	}
	return FALSE;
}

int HoAnimDataMgr::ImageLoad(char *iniName)
{

	if(ImageDataBufferCount < MAX_IMAGEDATA_BUFFER)
	{
		if(!ImageDataBuffer[ImageDataBufferCount].Load(iniName))
			return FALSE;
		ImageDataBufferCount++;
		return TRUE;
	}

	return FALSE;
}

int HoAnimDataMgr::Init()
{

	for(int index = 0; index < MAX_IMAGEDATA_BUFFER; index++)
	{
		ImageDataBuffer[index].Init();
	}

	for(int index = 0; index < MAX_SEQUENCEDATA_BUFFER; index++)
	{
		SequenceDataBuffer[index].Init();
	}

	ImageDataBufferCount = 0;
	SequenceDataBufferCount = 0;

	return TRUE;
}


int HoAnimDataMgr::GetSearchSequenceData(char *iniName)
{
	for(int index = 0; index < SequenceDataBufferCount; index++)
	{
		if(stricmp(SequenceDataBuffer[index].IniName, iniName) == 0)
			return index;
	}

	return -1;
}

int HoAnimDataMgr::GetSearchAnimImageData(char *iniName)
{
	for(int index = 0; index < ImageDataBufferCount; index++)
	{
		if(stricmp(ImageDataBuffer[index].IniName, iniName) == 0)
			return index;
	}

	return -1;
}
