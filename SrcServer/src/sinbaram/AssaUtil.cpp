

#include "sinLinkHeader.h"


#define MAX_RES_PATH	300
#define MAX_RES_DRIVE   200
#define MAX_FIND_FILE   300
char FindFileName[MAX_FIND_FILE];

char *AssaErrorFile = "AssaErrorFile.txt";
char *AssaLoadingFile = "AssaLoadingFile.txt";

BOOL FindFileRecursive(char *path, char *fileName)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	char drive[MAX_RES_DRIVE];
	char dir[MAX_RES_PATH];
	char newpath[MAX_RES_PATH];

	hSrch = FindFirstFile(path, &wfd);
	while(bResult)
	{
		_splitpath(path, drive, dir, NULL, NULL);
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(wfd.cFileName[0] != '.')
			{
				wsprintf(newpath, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
				if(FindFileRecursive(newpath, fileName))
					return TRUE;
			}
		}
		else
		{
			if(stricmp(wfd.cFileName, fileName) == 0)
			{
				wsprintf(FindFileName, "%s%s%s", drive, dir, wfd.cFileName);
				return TRUE;
			}
		}
		bResult = FindNextFile(hSrch, &wfd);
	}

	FindClose(hSrch);
	return FALSE;
}


char *FindFile(char *fileName)
{
	char Path[MAX_RES_PATH];
	GetCurrentDirectory(MAX_RES_PATH, Path);
	strcat(Path, "\\image\\Sinimage\\TestEffect\\*.*");


	memset(FindFileName, 0, sizeof(FindFileName));
	FindFileRecursive(Path, fileName);
	return FindFileName;
}

#define MAX_RES_NAME	  64
#define MAX_RES_FULL_NAME 512
#define MAX_RES_BUFFER    1000			

#define TYPE_MAT        100
#define TYPE_ASE        200
#define TYPE_BONE       300
#define TYPE_BONE_ANI   400				

struct cASSARES
{
	void *res;
	char resName[MAX_RES_NAME];
	char resFullName[MAX_RES_FULL_NAME];
	int  type;
	BOOL LoadFlag;
};


cASSARES AssaRes[MAX_RES_BUFFER];
int		 AssaResCount;



bool GetLoadedFile(char *searchFileName)
{
	for(int index = 0; index < AssaResCount; index++)
	{
		if(AssaRes[index].type == TYPE_ASE || AssaRes[index].type == TYPE_BONE || AssaRes[index].type == TYPE_BONE_ANI)
		{
			if(stricmp(searchFileName, AssaRes[index].resName) == 0)
				return true;
		}
	}

	return false;
}


bool ExistAseFile(char *directory)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;

	char tempFileName[512];
	char tempExtName[32];

	hSrch = FindFirstFile(directory, &wfd);
	while(bResult)
	{
		strcpy(tempFileName, wfd.cFileName);

		for(int index = strlen(tempFileName) - 1; index > 0; index--)
		{
			if(tempFileName[index] == '.')
			{
				tempFileName[index] = '\0';
				strcpy(tempExtName, &tempFileName[index + 1]);
				break;
			}
		}


		if(stricmp(tempExtName, "ase") == 0 || stricmp(tempExtName, "smd") == 0)
			return true;

		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);

	return false;
}

void LoadResFile(char *path, bool aseExistFlag)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	char drive[MAX_RES_DRIVE];
	char dir[MAX_RES_PATH];
	char newpath[MAX_RES_PATH];
	hSrch = FindFirstFile(path, &wfd);

	while(bResult)
	{
		_splitpath(path, drive, dir, NULL, NULL);
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(wfd.cFileName[0] != '.')
			{
				wsprintf(newpath, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
				LoadResFile(newpath, ExistAseFile(newpath));
			}
		}
		else
		{
			if(strlen(wfd.cFileName) > 4)
			{
				if(AssaResCount >= MAX_RES_BUFFER)
					return;

				char fileDirectoryName[1024];
				memset(fileDirectoryName, 0, sizeof(fileDirectoryName));
				wsprintf(fileDirectoryName, "%s%s%s", drive, dir, wfd.cFileName);

				char tempFileName[256];
				char tempExtName[10];
				strcpy(tempFileName, wfd.cFileName);

				for(int index = strlen(tempFileName) - 1; index > 0; index--)
				{
					if(tempFileName[index] == '.')
					{
						tempFileName[index] = '\0';
						strcpy(tempExtName, &tempFileName[index + 1]);
						break;
					}
				}

				if(aseExistFlag == false)
				{

					if(stricmp(tempExtName, "bmp") == 0 || stricmp(tempExtName, "tga") == 0)
					{
						if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
						{
							FILE *loadFp;
							loadFp = fopen(AssaLoadingFile, "at");
							fprintf(loadFp, "%s\n", fileDirectoryName);
							fclose(loadFp);


							FILE *errorFp;
							errorFp = fopen(AssaErrorFile, "wt");
							fprintf(errorFp, "%s\n", fileDirectoryName);
							fclose(errorFp);
						}
						strcpy(AssaRes[AssaResCount].resName, wfd.cFileName);

						AssaRes[AssaResCount].type = TYPE_MAT;
						strcpy(AssaRes[AssaResCount].resFullName, fileDirectoryName);


					#ifdef _EFFECT_RES_LOADING_
						if(HoEffectResLoadingFlag)
						{
							if(AssaRes[AssaResCount].LoadFlag == FALSE)
							{
								int *matNum = new int;
								(*matNum) = CreateTextureMaterial(AssaRes[AssaResCount].resFullName, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
								AssaRes[AssaResCount].res = matNum;
								AssaRes[AssaResCount].LoadFlag = TRUE;
								smMaterialGroup->ReadTextures();
							}
						}
					#endif
						AssaResCount++;
					}
				}


				if(stricmp(tempExtName, "ase") == 0 || stricmp(tempExtName, "smd") == 0)
				{

					char boneName[8];
					memset(boneName, 0, sizeof(boneName));
					memcpy(boneName, wfd.cFileName, 2);

					char aseName[256];
					memset(aseName, 0, sizeof(aseName));
					strcpy(aseName, wfd.cFileName);

					for(int index = strlen(aseName) - 1; index > 0; index--)
					{
						if(aseName[index] == '.')
						{
							aseName[index] = '\0';
							strcat(aseName, ".ase");
							break;
						}
					}

					memset(fileDirectoryName, 0, sizeof(fileDirectoryName));
					wsprintf(fileDirectoryName, "%s%s%s", drive, dir, aseName);

					if(GetLoadedFile(aseName) == true)
					{
						bResult = FindNextFile(hSrch, &wfd);
						continue;
					}

					if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
					{
						FILE *loadFp;
						loadFp = fopen(AssaLoadingFile, "at");
						fprintf(loadFp, "%s\n", fileDirectoryName);
						fclose(loadFp);


						FILE *errorFp;
						errorFp = fopen(AssaErrorFile, "wt");
						fprintf(errorFp, "%s\n", fileDirectoryName);
						fclose(errorFp);
					}

					if(stricmp(boneName, "b_") == 0)
					{
						strcpy(AssaRes[AssaResCount].resName, aseName);
						strcpy(AssaRes[AssaResCount].resFullName, fileDirectoryName);
						AssaRes[AssaResCount].type = TYPE_BONE_ANI;
						AssaResCount++;


						char tempName[64];
						memset(tempName, 0, sizeof(tempName));
						strcpy(tempName, aseName);
						for(int index = 0; index < (int)strlen(tempName); index++)
						{
							if(tempName[index] == '_')
							{
								strcpy(AssaRes[AssaResCount].resName, &tempName[index + 1]);
								break;
							}
						}
						strcpy(AssaRes[AssaResCount].resFullName, fileDirectoryName);

					#ifdef _EFFECT_RES_LOADING_
						if(HoEffectResLoadingFlag)
						{
							if((AssaResCount - 1) >= 0)
							{

								if(AssaRes[AssaResCount - 1].LoadFlag == FALSE)
								{

									AssaRes[AssaResCount - 1].res = (void *)smASE_ReadBone(AssaRes[AssaResCount - 1].resFullName);
									AssaRes[AssaResCount - 1].LoadFlag = TRUE;
									smASE_SetPhysique(((smPAT3D *)AssaRes[AssaResCount - 1].res));
								}


								AssaRes[AssaResCount].res = (void *)smASE_Read(AssaRes[AssaResCount].resFullName);
								((smPAT3D *)AssaRes[AssaResCount].res)->ZeroNormals();
								smASE_SetPhysique(NULL);

								AssaRes[AssaResCount].LoadFlag = TRUE;
								((smPAT3D *)AssaRes[AssaResCount].res)->smMaterialGroup->ReadTextures();
							}
						}

					#endif
						AssaRes[AssaResCount].type = TYPE_BONE;
						AssaResCount++;
					}
					else
					{
						strcpy(AssaRes[AssaResCount].resName, aseName);
						strcpy(AssaRes[AssaResCount].resFullName, fileDirectoryName);

					#ifdef _EFFECT_RES_LOADING_
						if(HoEffectResLoadingFlag)
						{
							if(AssaRes[AssaResCount].LoadFlag == FALSE)
							{
								smASE_SetPhysique(NULL);
								AssaRes[AssaResCount].res = (void *)smASE_Read(AssaRes[AssaResCount].resFullName);

								((smPAT3D *)AssaRes[AssaResCount].res)->ZeroNormals();
								AssaRes[AssaResCount].LoadFlag = TRUE;
								((smPAT3D *)AssaRes[AssaResCount].res)->smMaterialGroup->ReadTextures();
							}
						}
					#endif
						AssaRes[AssaResCount].type = TYPE_ASE;
						AssaResCount++;
					}
				}
			}
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
}


void InitAssaRes()
{
	AssaResCount = 0;
	memset(AssaRes, 0, sizeof(AssaRes));
}


void CloseAssaRes()
{
	for(int index = 0; index < AssaResCount; index++)
	{
		if(AssaRes[index].res != NULL)
		{
			if(AssaRes[index].type == TYPE_MAT)
			{
				delete ((int *)AssaRes[index].res);
				AssaRes[index].res = NULL;
			}
			if(AssaRes[index].type == TYPE_ASE)
			{
				delete ((smPAT3D *)AssaRes[index].res);
				AssaRes[index].res = NULL;
				memset(AssaRes[index].resName, 0, sizeof(AssaRes[index].resName));
				AssaRes[index].type = 0;
			}
		}
	}
}


void LoadAssaRes()
{
	CloseAssaRes();
	char Path[MAX_RES_PATH];

	if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		DeleteFile(AssaLoadingFile);
	strcpy(Path, "image\\Sinimage\\AssaEffect\\*.*");
	LoadResFile(Path, false);

	strcpy(Path, "Effect\\AssaEffect\\*.*");
	LoadResFile(Path, false);

	if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		DeleteFile(AssaErrorFile);



}




void *AssaSearchRes(char *resName, int blendType)
{
	for(int index = 0; index < AssaResCount; index++)
	{
		if(stricmp(AssaRes[index].resName, resName) == 0)
		{
			if(AssaRes[index].type == TYPE_ASE)
			{
				if(AssaRes[index].LoadFlag == FALSE)
				{
					smASE_SetPhysique(NULL);
					AssaRes[index].res = (void *)smASE_Read(AssaRes[index].resFullName);

					((smPAT3D *)AssaRes[index].res)->ZeroNormals();
					AssaRes[index].LoadFlag = TRUE;
					((smPAT3D *)AssaRes[index].res)->smMaterialGroup->ReadTextures();

				}

				if(((smPAT3D *)AssaRes[index].res)->smMaterialGroup)
				{
					int matCount = ((smPAT3D *)AssaRes[index].res)->smMaterialGroup->MaterialCount;
					for(int i = 0; i < matCount; i++)
						((smPAT3D *)AssaRes[index].res)->smMaterialGroup->smMaterial[i].BlendType = blendType;
				}

				return AssaRes[index].res;
			}
			else if(AssaRes[index].type == TYPE_BONE)
			{
				if(AssaRes[index].LoadFlag == FALSE)
				{
					if((index - 1) >= 0)
					{

						if(AssaRes[index - 1].LoadFlag == FALSE)
						{

							AssaRes[index - 1].res = (void *)smASE_ReadBone(AssaRes[index - 1].resFullName);
							AssaRes[index - 1].LoadFlag = TRUE;
						}

						smASE_SetPhysique(((smPAT3D *)AssaRes[index - 1].res));


						AssaRes[index].res = (void *)smASE_Read(AssaRes[index].resFullName);
						((smPAT3D *)AssaRes[index].res)->ZeroNormals();
						smASE_SetPhysique(NULL);

						AssaRes[index].LoadFlag = TRUE;
						((smPAT3D *)AssaRes[index].res)->smMaterialGroup->ReadTextures();

					}
				}

				if(((smPAT3D *)AssaRes[index].res)->smMaterialGroup)
				{
					int matCount = ((smPAT3D *)AssaRes[index].res)->smMaterialGroup->MaterialCount;
					for(int i = 0; i < matCount; i++)
						((smPAT3D *)AssaRes[index].res)->smMaterialGroup->smMaterial[i].BlendType = blendType;
				}

				return AssaRes[index].res;
			}
			else if(AssaRes[index].type == TYPE_BONE_ANI)
			{
				if(AssaRes[index - 1].LoadFlag == FALSE)
				{


					AssaRes[index - 1].res = (void *)smASE_ReadBone(AssaRes[index - 1].resFullName);
					AssaRes[index - 1].LoadFlag = TRUE;
				}
				return AssaRes[index].res;
			}
			else if(AssaRes[index].type == TYPE_MAT)
			{
				if(AssaRes[index].LoadFlag == FALSE)
				{
					int *matNum = new int;
					(*matNum) = CreateTextureMaterial(AssaRes[index].resFullName, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
					AssaRes[index].res = matNum;
					AssaRes[index].LoadFlag = TRUE;
					smMaterialGroup->ReadTextures();

				}

				int matNum = *((int *)AssaRes[index].res);
				smMaterialGroup->smMaterial[matNum].TwoSide = TRUE;
				smMaterialGroup->smMaterial[matNum].BlendType = blendType;
				return AssaRes[index].res;
			}

		}
	}

	return NULL;
}


#define FLOATS_EM				(FLOATNS+3)
#define SM_DIST_NEARZ			16
#define SMFLOAT_DIST_NEARZ		(SM_DIST_NEARZ<<FLOATNS)

bool AssaGetCameraCoord(POINT3D &world)
{
	int rx, ry, rz;


	world.x -= smRender.CameraPosiX;
	world.y -= smRender.CameraPosiY;
	world.z -= smRender.CameraPosiZ;

	rx = world.x * smRender.mCamera._11 +
		world.y * smRender.mCamera._21 +
		world.z * smRender.mCamera._31;

	ry = world.x * smRender.mCamera._12 +
		world.y * smRender.mCamera._22 +
		world.z * smRender.mCamera._32;

	rz = world.x * smRender.mCamera._13 +
		world.y * smRender.mCamera._23 +
		world.z * smRender.mCamera._33;

	world.x = rx >> FLOATS_EM;
	world.y = ry >> FLOATS_EM;
	world.z = rz >> FLOATS_EM;

	if(world.z < SMFLOAT_DIST_NEARZ)
		return FALSE;
	return TRUE;
}


bool AssaAddFace2D(smFACE2D *face, int ZPosiFlag, int angle)
{
	int x, y, z;
	int rx, ry, rz;
	int width, height;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[SMC_A] = face->Transparency;
	sColor[SMC_R] = face->r;
	sColor[SMC_G] = face->g;
	sColor[SMC_B] = face->b;

	x = face->x;
	y = face->y;
	z = face->z;


	x -= smRender.CameraPosiX;
	y -= smRender.CameraPosiY;
	z -= smRender.CameraPosiZ;

	rx = x * smRender.mCamera._11 +
		y * smRender.mCamera._21 +
		z * smRender.mCamera._31;

	ry = x * smRender.mCamera._12 +
		y * smRender.mCamera._22 +
		z * smRender.mCamera._32;

	rz = x * smRender.mCamera._13 +
		y * smRender.mCamera._23 +
		z * smRender.
		mCamera._33;

	x = rx >> FLOATS_EM;
	y = ry >> FLOATS_EM;
	z = rz >> FLOATS_EM;


	if(ZPosiFlag)
		z -= 24 * fONE;


	if(z < SMFLOAT_DIST_NEARZ) return false;

	width = face->width >> 1;
	height = face->height >> 1;

	if(angle != 0)
	{

		int		ex[4], ey[4];
		int		mx, my;
		int		sin, cos;

		sin = GetSin[angle&ANGCLIP] >> FLOATNS;
		cos = GetCos[angle&ANGCLIP] >> FLOATNS;

		mx = -width;	my = -height;
		ex[0] = (mx * cos - my * sin) >> FLOATNS;
		ey[0] = (mx * sin + my * cos) >> FLOATNS;

		mx = width;	my = -height;
		ex[1] = (mx * cos - my * sin) >> FLOATNS;
		ey[1] = (mx * sin + my * cos) >> FLOATNS;

		mx = -width;	my = +height;
		ex[2] = (mx * cos - my * sin) >> FLOATNS;
		ey[2] = (mx * sin + my * cos) >> FLOATNS;

		mx = width;	my = height;
		ex[3] = (mx * cos - my * sin) >> FLOATNS;
		ey[3] = (mx * sin + my * cos) >> FLOATNS;



		v[0] = smRender.AddRendVertex(x + ex[0], y + ey[0], z, sColor);
		v[1] = smRender.AddRendVertex(x + ex[1], y + ey[1], z, sColor);
		v[2] = smRender.AddRendVertex(x + ex[2], y + ey[2], z, sColor);
		v[3] = smRender.AddRendVertex(x + ex[3], y + ey[3], z, sColor);
	}
	else
	{

		v[0] = smRender.AddRendVertex(x - width, y - height, z, sColor);
		v[1] = smRender.AddRendVertex(x + width, y - height, z, sColor);
		v[2] = smRender.AddRendVertex(x - width, y + height, z, sColor);
		v[3] = smRender.AddRendVertex(x + width, y + height, z, sColor);
	}


	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;
	rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
	rf->lpTexLink = 0;


	smRender.AddRendTempTexLink(rf, 0, face->TexRect.left, face->TexRect.bottom,
								face->TexRect.right, face->TexRect.bottom,
								face->TexRect.left, face->TexRect.top);



	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;
	rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
	rf->lpTexLink = 0;


	smRender.AddRendTempTexLink(rf, 0, face->TexRect.right, face->TexRect.bottom,
								face->TexRect.right, face->TexRect.top,
								face->TexRect.left, face->TexRect.top);


	return true;
}


bool AssaAddFace2DLine(smFACE2D *face, POINT3D *localDestPos, BOOL centerFlag)
{
	int x, y, z;
	int width;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[SMC_A] = face->Transparency;
	sColor[SMC_R] = face->r;
	sColor[SMC_G] = face->g;
	sColor[SMC_B] = face->b;

	x = face->x;
	y = face->y;
	z = face->z;

	POINT3D currentPos;
	POINT3D destPos;
	width = face->width / 2;

	currentPos.x = x;
	currentPos.y = y;
	currentPos.z = z;

	destPos.x = localDestPos->x;
	destPos.y = localDestPos->y;
	destPos.z = localDestPos->z;

	if(centerFlag == FALSE)
	{
		destPos.x = currentPos.x + destPos.x;
		destPos.y = currentPos.y + destPos.y;
		destPos.z = currentPos.z + destPos.z;
	}
	else
	{
		POINT3D centerDestPos;
		memcpy(&centerDestPos, &destPos, sizeof(centerDestPos));
		centerDestPos.x = centerDestPos.x / 2;
		centerDestPos.y = centerDestPos.y / 2;
		centerDestPos.z = centerDestPos.z / 2;

		destPos.x = currentPos.x + centerDestPos.x;
		destPos.y = currentPos.y + centerDestPos.y;
		destPos.z = currentPos.z + centerDestPos.z;

		currentPos.x = currentPos.x - (centerDestPos.x);
		currentPos.y = currentPos.y - (centerDestPos.y);
		currentPos.z = currentPos.z - (centerDestPos.z);
	}



	if(AssaGetCameraCoord(currentPos) == FALSE)
		return FALSE;

	if(AssaGetCameraCoord(destPos) == FALSE)
		return FALSE;




	sColor[SMC_A] = face->Transparency;
	sColor[SMC_R] = face->r;
	sColor[SMC_G] = face->g;
	sColor[SMC_B] = face->b;

	smTEXRECT texRect;
	texRect.left = 0;
	texRect.top = 0;
	texRect.right = 1;
	texRect.bottom = 1;

	float dx = float(destPos.x - currentPos.x);
	float dy = float(destPos.y - currentPos.y);
	float length = (float)sqrt(dx*dx + dy*dy);

	dx = dx / length*width;
	dy = dy / length*width;

	D3DVECTOR persp;
	persp.x = -dy;
	persp.y = +dx;
	persp.z = 0;

	if(abs((int)dx) > 1.0f) currentPos.x -= (int)dx;
	if(abs((int)dy) > 1.0f) currentPos.y -= (int)dy;

	v[0] = smRender.AddRendVertex(int(destPos.x - persp.x), int(destPos.y - persp.y), int(destPos.z), sColor);
	v[1] = smRender.AddRendVertex(int(destPos.x + persp.x), int(destPos.y + persp.y), int(destPos.z), sColor);
	v[2] = smRender.AddRendVertex(int(currentPos.x - persp.x), int(currentPos.y - persp.y), int(currentPos.z), sColor);
	v[3] = smRender.AddRendVertex(int(currentPos.x + persp.x), int(currentPos.y + persp.y), int(currentPos.z), sColor);


	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;
	rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
	rf->lpTexLink = 0;


	smRender.AddRendTempTexLink(rf, 0, texRect.left, texRect.bottom,
								texRect.right, texRect.bottom,
								texRect.left, texRect.top);



	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;
	rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
	rf->lpTexLink = 0;


	smRender.AddRendTempTexLink(rf, 0, texRect.right, texRect.bottom,
								texRect.right, texRect.top,
								texRect.left, texRect.top);
	return true;
}



bool AssaAddFaceWorld(smFACE2D *face, POINT3D *inAngle)
{
	int x, y, z;
	int width, height;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[SMC_A] = face->Transparency;
	sColor[SMC_R] = face->r;
	sColor[SMC_G] = face->g;
	sColor[SMC_B] = face->b;

	x = face->x;
	y = face->y;
	z = face->z;

	POINT3D inVertex[4];
	POINT3D outVertex[4];

	width = face->width / 2;
	height = face->height / 2;

	inVertex[0].x = x - width;
	inVertex[0].y = y;
	inVertex[0].z = z + height;

	inVertex[1].x = x + width;
	inVertex[1].y = y;
	inVertex[1].z = z + height;

	inVertex[2].x = x - width;
	inVertex[2].y = y;
	inVertex[2].z = z - height;

	inVertex[3].x = x + width;
	inVertex[3].y = y;
	inVertex[3].z = z - height;

	int index = 0;
	if(inAngle != NULL)
	{
		inVertex[0].x = -width;
		inVertex[0].y = 0;
		inVertex[0].z = height;

		inVertex[1].x = width;
		inVertex[1].y = 0;
		inVertex[1].z = height;

		inVertex[2].x = -width;
		inVertex[2].y = 9;
		inVertex[2].z = -height;

		inVertex[3].x = width;
		inVertex[3].y = 0;
		inVertex[3].z = -height;

		POINT3D angle;
		angle.x = (int)inAngle->x;
		angle.y = (int)inAngle->y;
		angle.z = (int)inAngle->z;

		angle.x = angle.x & ANGCLIP;
		angle.y = angle.y & ANGCLIP;
		angle.z = angle.z & ANGCLIP;

		smMATRIX inRotXMatrix;
		smMATRIX inRotYMatrix;
		smMATRIX inRotZMatrix;

		smMATRIX outMatrix;
		smIdentityMatrix(outMatrix);
		smIdentityMatrix(inRotXMatrix);
		smIdentityMatrix(inRotYMatrix);
		smIdentityMatrix(inRotZMatrix);

		smRotateXMatrix(inRotXMatrix, angle.x);
		smRotateYMatrix(inRotYMatrix, angle.y);
		smRotateZMatrix(inRotZMatrix, angle.z);

		smMatrixMult(outMatrix, inRotXMatrix, inRotYMatrix);
		smMatrixMult(outMatrix, outMatrix, inRotZMatrix);

		for(index = 0; index < 4; index++)
		{
			outVertex[index].x = inVertex[index].x * outMatrix._11 +
				inVertex[index].y * outMatrix._21 +
				inVertex[index].z * outMatrix._31;


			outVertex[index].y = inVertex[index].x * outMatrix._12 +
				inVertex[index].y * outMatrix._22 +
				inVertex[index].z * outMatrix._32;


			outVertex[index].z = inVertex[index].x * outMatrix._13 +
				inVertex[index].y * outMatrix._23 +
				inVertex[index].z * outMatrix._33;

			outVertex[index].x = outVertex[index].x / fONE + x;
			outVertex[index].y = outVertex[index].y / fONE + y;
			outVertex[index].z = outVertex[index].z / fONE + z;

		}

		memcpy(inVertex, outVertex, sizeof(inVertex));
	}


	for(index = 0; index < 4; index++)
	{
		inVertex[index].x -= smRender.CameraPosiX;
		inVertex[index].y -= smRender.CameraPosiY;
		inVertex[index].z -= smRender.CameraPosiZ;
	}

	for(index = 0; index < 4; index++)
	{
		outVertex[index].x = inVertex[index].x*smRender.mCamera._11 +
			inVertex[index].y*smRender.mCamera._21 +
			inVertex[index].z*smRender.mCamera._31;

		outVertex[index].y = inVertex[index].x*smRender.mCamera._12 +
			inVertex[index].y*smRender.mCamera._22 +
			inVertex[index].z*smRender.mCamera._32;

		outVertex[index].z = inVertex[index].x*smRender.mCamera._13 +
			inVertex[index].y*smRender.mCamera._23 +
			inVertex[index].z*smRender.mCamera._33;

		outVertex[index].x = outVertex[index].x >> FLOATS_EM;
		outVertex[index].y = outVertex[index].y >> FLOATS_EM;
		outVertex[index].z = outVertex[index].z >> FLOATS_EM;

		if(outVertex[index].z < SMFLOAT_DIST_NEARZ)
			return false;
	}



	v[0] = smRender.AddRendVertex(outVertex[0].x, outVertex[0].y, outVertex[0].z, sColor);
	v[1] = smRender.AddRendVertex(outVertex[1].x, outVertex[1].y, outVertex[1].z, sColor);
	v[2] = smRender.AddRendVertex(outVertex[2].x, outVertex[2].y, outVertex[2].z, sColor);
	v[3] = smRender.AddRendVertex(outVertex[3].x, outVertex[3].y, outVertex[3].z, sColor);


	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;
	rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
	rf->lpTexLink = 0;


	smRender.AddRendTempTexLink(rf, 0, face->TexRect.left, face->TexRect.bottom,
								face->TexRect.right, face->TexRect.bottom,
								face->TexRect.left, face->TexRect.top);



	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;
	rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
	rf->lpTexLink = 0;


	smRender.AddRendTempTexLink(rf, 0, face->TexRect.right, face->TexRect.bottom,
								face->TexRect.right, face->TexRect.top,
								face->TexRect.left, face->TexRect.top);
	return true;
}



bool AssaAddFaceTrace(smFACE2D *face, cASSATrace *assaTrace)
{
	if(face == NULL || assaTrace == NULL)
		return false;

	if(assaTrace->TraceList.size() < 2)
		return FALSE;

	POINT3D destPos;
	POINT3D currentPos;

	std::list<POINT3D>::iterator i;
	i = assaTrace->TraceList.begin();
	destPos.x = i->x;
	destPos.y = i->y;
	destPos.z = i->z;

	int texSizeCount = 0;
	int test = assaTrace->TraceList.size();
	float cellSize = 1.f / (assaTrace->TraceList.size() - 1);
	++i;
	POINT3D OldVertex[2];
	memset(OldVertex, 0, sizeof(OldVertex));

	for(; i != assaTrace->TraceList.end(); i++)
	{
		currentPos.x = i->x;
		currentPos.y = i->y;
		currentPos.z = i->z;

		if(AssaGetCameraCoord(currentPos) == FALSE)
			return FALSE;

		if(AssaGetCameraCoord(destPos) == FALSE)
			return FALSE;

		smRENDVERTEX *v[4];
		smRENDFACE	 *rf;

		short		sColor[4];

		sColor[SMC_R] = face->r;
		sColor[SMC_G] = face->g;
		sColor[SMC_B] = face->b;
		sColor[SMC_A] = face->Transparency;

		smTEXRECT texRect;
		texRect.left = 0;
		texRect.top = (float)texSizeCount*cellSize;
		texRect.right = 1;
		texRect.bottom = (float)(texSizeCount + 1)*cellSize;


		int size;
		size = (int)face->width;

		size = size >> 1;

		float dx = float(destPos.x - currentPos.x);
		float dy = float(destPos.y - currentPos.y);
		float length = (float)sqrt(dx*dx + dy*dy);

		if(length == 0)
			length = 1;

		dx = dx / length*size;
		dy = dy / length*size;

		D3DVECTOR persp;
		persp.x = -dy;
		persp.y = +dx;
		persp.z = 0;

		if(texSizeCount == 0)
		{
			v[0] = smRender.AddRendVertex(int(destPos.x - persp.x), int(destPos.y - persp.y), int(destPos.z), sColor);
			v[1] = smRender.AddRendVertex(int(destPos.x + persp.x), int(destPos.y + persp.y), int(destPos.z), sColor);
		}
		else
		{
			v[0] = smRender.AddRendVertex(OldVertex[0].x, OldVertex[0].y, OldVertex[0].z, sColor);
			v[1] = smRender.AddRendVertex(OldVertex[1].x, OldVertex[1].y, OldVertex[1].z, sColor);
		}

		OldVertex[0].x = int(currentPos.x - persp.x);
		OldVertex[0].y = int(currentPos.y - persp.y);
		OldVertex[0].z = int(currentPos.z);

		OldVertex[1].x = int(currentPos.x + persp.x);
		OldVertex[1].y = int(currentPos.y + persp.y);
		OldVertex[1].z = int(currentPos.z);

		destPos.x = int(i->x);
		destPos.y = int(i->y);
		destPos.z = int(i->z);

		v[2] = smRender.AddRendVertex(int(currentPos.x - persp.x), int(currentPos.y - persp.y), int(currentPos.z), sColor);
		v[3] = smRender.AddRendVertex(int(currentPos.x + persp.x), int(currentPos.y + persp.y), int(currentPos.z), sColor);


		rf = &smRender.RendFace[smRender.nRendFace++];
		rf->lpRendVertex[0] = v[0];
		rf->lpRendVertex[1] = v[1];
		rf->lpRendVertex[2] = v[2];
		rf->Matrial = face->MatNum;
		rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
		rf->lpTexLink = 0;


		smRender.AddRendTempTexLink(rf, 0, texRect.left, texRect.top,
									texRect.right, texRect.top,
									texRect.left, texRect.bottom);



		rf = &smRender.RendFace[smRender.nRendFace++];
		rf->lpRendVertex[0] = v[1];
		rf->lpRendVertex[1] = v[3];
		rf->lpRendVertex[2] = v[2];
		rf->Matrial = face->MatNum;
		rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
		rf->lpTexLink = 0;


		smRender.AddRendTempTexLink(rf, 0, texRect.right, texRect.top,
									texRect.right, texRect.bottom,
									texRect.left, texRect.bottom);

		texSizeCount++;
	}
	return true;
}



bool AssaSearchObjPos(smCHAR *character, smOBJ3D *obj, POINT3D *outObjPos)
{
	if(character == NULL ||
	   obj == NULL)
		return false;

	smMATRIX *mWorld;
	mWorld = &obj->mWorld;
	POINT3D angle;
	memcpy(&angle, &character->Angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;
	AnimObjectTree(obj, character->frame, angle.x, angle.y, angle.z);

	outObjPos->x = character->pX + mWorld->_41;
	outObjPos->z = character->pZ + mWorld->_42;
	outObjPos->y = character->pY + mWorld->_43;

	return true;
}


bool AssaSearchObjPos(smCHAR *character, smOBJ3D *obj, POINT3D *outObjPos, int length)
{
	if(character == NULL ||
	   obj == NULL)
		return false;

	smMATRIX *mWorld;
	mWorld = &obj->mWorld;
	POINT3D angle;
	memcpy(&angle, &character->Angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;
	AnimObjectTree(obj, character->frame, angle.x, angle.y, angle.z);

	POINT3D pBot;
	pBot.x = 0;
	pBot.y = 0;
	pBot.z = length;

	int rx, ry, rz;
	rx = pBot.x * mWorld->_11 +
		pBot.y * mWorld->_21 +
		pBot.z * mWorld->_31;

	ry = pBot.x * mWorld->_12 +
		pBot.y * mWorld->_22 +
		pBot.z * mWorld->_32;

	rz = pBot.x * mWorld->_13 +
		pBot.y * mWorld->_23 +
		pBot.z * mWorld->_33;

	outObjPos->x = character->pX + (rx >> FLOATNS) + mWorld->_41;
	outObjPos->z = character->pZ + (ry >> FLOATNS) + mWorld->_42;
	outObjPos->y = character->pY + (rz >> FLOATNS) + mWorld->_43;





	return true;
}


bool AssaSearchWeaponPos(smCHAR *character, POINT3D *outWeaponPos, float u)
{
	if(character == NULL)
		return false;

	smMATRIX *mWorld;
	mWorld = &character->HvRightHand.ObjBip->mWorld;

	POINT3D pBot;
	pBot.x = 0;
	pBot.y = 0;

	if(character->ShootingFlag)
	{
		outWeaponPos->x = character->ShootingPosi.x;
		outWeaponPos->y = character->ShootingPosi.y;
		outWeaponPos->z = character->ShootingPosi.z;
		return true;
	}

	if((character->HvRightHand.dwItemCode & sinITEM_MASK2) == sinWT1)
	{
		pBot.z = -character->HvRightHand.SizeMax + int((float)character->HvRightHand.SizeMax*u);
	}
	else
	{
		pBot.z = character->HvRightHand.SizeMax - int((float)character->HvRightHand.SizeMax*u);
	}

	POINT3D angle;
	memcpy(&angle, &character->Angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

	AnimObjectTree(character->HvRightHand.ObjBip, character->frame, angle.x, angle.y, angle.z);
	int rx, ry, rz;
	rx = pBot.x * mWorld->_11 +
		pBot.y * mWorld->_21 +
		pBot.z * mWorld->_31;

	ry = pBot.x * mWorld->_12 +
		pBot.y * mWorld->_22 +
		pBot.z * mWorld->_32;

	rz = pBot.x * mWorld->_13 +
		pBot.y * mWorld->_23 +
		pBot.z * mWorld->_33;

	outWeaponPos->x = character->pX + (rx >> FLOATNS) + mWorld->_41;
	outWeaponPos->z = character->pZ + (ry >> FLOATNS) + mWorld->_42;
	outWeaponPos->y = character->pY + (rz >> FLOATNS) + mWorld->_43;

	return true;
}



static char sinDecode[512];
static char sinLine[512];
int AssaTestEffectImage()
{

	char *szFilePath = "image\\Sinimage\\AssaEffect\\AssaTest.INI";

	FILE	*fp;
	char strBuff[64];

	char *p;
	int Count = 0;
	int NextFlag = 0;
	int Index = 0;
	int sinMeshCount = 0;

	fp = fopen(szFilePath, "rb");
	if(fp == NULL) return FALSE;


	while(!feof(fp))
	{
		NextFlag = 0;
		if(fgets(sinLine, 255, fp) == NULL)
			break;

		p = GetWord(sinDecode, sinLine);



		if(!NextFlag && lstrcmp(sinDecode, "*파일이름") == 0)
		{
			char boneName2[8];
			char MeshName[32];
			memset(boneName2, 0, sizeof(boneName2));
			memcpy(boneName2, strBuff, 2);
			p = GetWord(strBuff, p);
			if(stricmp(boneName2, "b_") == 0)
			{
				cAssaEffect[Index]->Bone = 1;
				Index = SetAssaEffect(0, strBuff, lpCurPlayer, 0, 0);
				strcpy_s(MeshName, &strBuff[2]);
				Index = SetAssaEffect(0, MeshName, lpCurPlayer, 0, 0);

			}
			else
			{
				Index = SetAssaEffect(0, strBuff, lpCurPlayer, 0, 0);
			}


			cAssaEffect[Index]->Angle.y = (-(lpCurPlayer->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP;
			NextFlag = TRUE;

		}

		if(!NextFlag && lstrcmp(sinDecode, "*프레임") == 0)
		{
			p = GetWord(strBuff, p);
			cAssaEffect[Index]->AniMaxCount = atoi(strBuff);
			NextFlag = TRUE;

		}

		if(!NextFlag && lstrcmp(sinDecode, "*프레임딜레이") == 0)
		{
			p = GetWord(strBuff, p);
			cAssaEffect[Index]->AniDelayTime = atoi(strBuff);
			NextFlag = TRUE;

		}
		if(!NextFlag && lstrcmp(sinDecode, "*높이") == 0)
		{
			p = GetWord(strBuff, p);
			cAssaEffect[Index]->Posi.y += atoi(strBuff);
			NextFlag = TRUE;

		}

	}
	if(fp) fclose(fp);
	return TRUE;

}
