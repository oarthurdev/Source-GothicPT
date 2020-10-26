#include <windows.h>
#include <Tlhelp32.h>

class checkbuf
{
public:
	DWORD	filename;
	DWORD	filechecksum;
	DWORD	allchecksum;
	char	name[512];
};
int arrange(checkbuf* data, int size);
POINT GetProcessModule();




POINT GetProcessModule()
{
	MODULEENTRY32	me32 = { 0 };
	HANDLE			hModuleSnap = NULL;
	DWORD			nBytesRead;
	DWORD			checksum = 0;
	int				len;
	int				filecount = 0;

	checkbuf		sumdata[200];
	POINT			allChecksum;

	ZeroMemory(&allChecksum, sizeof(POINT));

	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if(hModuleSnap == INVALID_HANDLE_VALUE) return allChecksum;
	me32.dwSize = sizeof(MODULEENTRY32);

	if(Module32First(hModuleSnap, &me32))
	{
		do
		{
			if(strstr(me32.szExePath, "game.exe") != NULL) continue;
			if(strstr(me32.szExePath, "ime") != NULL) continue;
			if(strstr(me32.szExePath, "IME") != NULL) continue;

			HANDLE hFindFile;
			WIN32_FIND_DATA FindFileData;
			ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATA));

			if((hFindFile = FindFirstFile(me32.szExePath, &FindFileData)) != INVALID_HANDLE_VALUE)
			{
				HANDLE	hSaveFile;
				int		loopcount;
				int		i;

				hSaveFile = CreateFile(me32.szExePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if(hSaveFile != INVALID_HANDLE_VALUE)
				{
					DWORD *mbuf = new DWORD[FindFileData.nFileSizeLow / sizeof(DWORD)];
					ReadFile(hSaveFile, mbuf, sizeof(DWORD)*(FindFileData.nFileSizeLow / sizeof(DWORD)), &nBytesRead, NULL);

					loopcount = FindFileData.nFileSizeLow / sizeof(DWORD);
					for(i = 1; i < (int)loopcount; i += 2) checksum += mbuf[i] * i;
					sumdata[filecount].filechecksum = checksum;

					CloseHandle(hSaveFile);
					delete mbuf;

					checksum = 0;
					strcpy(sumdata[filecount].name, strupr(me32.szModule));

					len = (int)strlen(sumdata[filecount].name);
					for(i = 0; i < len; i++) checksum += me32.szModule[i] * i;
					sumdata[filecount].filename = checksum;

					sumdata[filecount].allchecksum = sumdata[filecount].filechecksum + sumdata[filecount].filename;
					filecount++;
				}
				else
				{
					CloseHandle(hModuleSnap);
					ZeroMemory(&allChecksum, sizeof(POINT));
					return	allChecksum;
				}
			}
		} while(Module32Next(hModuleSnap, &me32));
	}
	CloseHandle(hModuleSnap);

	arrange(sumdata, filecount);
	for(int i = 0; i < filecount; i++) allChecksum.x += sumdata[i].allchecksum*i;
	allChecksum.y = filecount;
	return allChecksum;
}
int arrange(checkbuf* data, int size)
{
	DWORD	val;
	BOOL	test = TRUE;
	DWORD	allchecksum;

	for(;;)
	{
		test = FALSE;
		int check = 0;
		for(int x = 0; x < size; x++)
		{
			val = data[x].allchecksum;
			for(int y = (x + 1); y < size; y++)
			{
				if(val < data[y].allchecksum)
				{


					allchecksum = data[x].allchecksum;




					data[x].allchecksum = data[y].allchecksum;




					data[y].allchecksum = allchecksum;

					test = TRUE;
					break;
				}
			}
			if(!test) check++;
			if(check == size) return 1;
		}
	}
	return 1;
}
