





#pragma once


#define MAX_ZIP_BUFF_SIZE			((1024*1024) * 5)
#define MAX_FILE_NAME				64
#define ZIP_LIB_VER					"100"


enum eZIP_ERROR
{
	ZIP_OK = 1,
	ZIP_ERROR = -1,
	ZIP_UN_ERROR = -2,
	ZIP_BUFF_SIZE_ERROR = -3,
	ZIP_TYPE_ERROR = -4,
	ZIP_FILE_ERROR = -5,
	ZIP_NAME_ERROR = -6,
};


struct SZIP_HEADER
{
	DWORD Type;
	DWORD TotalFileSize;
	DWORD TotalOrgSize;
	DWORD ZipSize;
	char  OrgFileName[MAX_FILE_NAME];
	DWORD Reserved;
};


extern "C" __declspec(dllexport) int SetExtChangeZip(char *szDest);


extern "C" __declspec(dllexport) int ZipData(BYTE *lpDestBuff, DWORD *lpDestBuffSize, BYTE *lpSrcBuff, DWORD SrcBuffSize);
extern "C" __declspec(dllexport) int UnZipData(BYTE *lpDestBuff, DWORD *lpDestBuffSize, BYTE *lpSrcBuff);


extern "C" __declspec(dllexport) int ZipFile(char *lpSrcFileName);

extern "C" __declspec(dllexport) int UnZipFile(char *lpSrcFileName);


extern "C" __declspec(dllexport) int UnZipDataToFile(BYTE *lpSrcBuff);


extern "C" __declspec(dllexport) int UnZipDataToDirectory(char *Directory, BYTE *lpSrcBuff);
