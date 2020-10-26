void c_GetFilePath(char *szName, char *szFileName)
{
	if(szName[4] == 0 && szName[3] >= '0' && szName[3] <= '9' && (
		((szName[0] == 'c' || szName[0] == 'C') && (szName[1] == 'o' || szName[1] == 'O') && (szName[2] == 'm' || szName[2] == 'M')) ||
		((szName[0] == 'l' || szName[0] == 'L') && (szName[1] == 'p' || szName[1] == 'P') && (szName[2] == 't' || szName[2] == 'T')))
		)
	{
		wsprintf(szFileName, "££%s.dat", szName);
		return;
	}

	if(szName[3] == 0 &&
		((szName[0] == 'p' || szName[0] == 'P') && (szName[1] == 'r' || szName[1] == 'R') && (szName[2] == 'n' || szName[2] == 'N')) ||
	   ((szName[0] == 'c' || szName[0] == 'C') && (szName[1] == 'o' || szName[1] == 'O') && (szName[2] == 'n' || szName[2] == 'N'))
	   )
	{
		wsprintf(szFileName, "££%s.dat", szName);
		return;
	}
	wsprintf(szFileName, "%s.dat", szName);
}
int c_GetUserCode(char *szName)
{
	int cnt, len;
	BYTE ch;
	BYTE *lpData = (BYTE *)szName;
	len = lstrlen(szName);
	ch = 0;
	for(cnt = 0; cnt < len; cnt++)
	{
		if(lpData[cnt] >= 'a' && lpData[cnt] <= 'z')
			ch += (lpData[cnt] - 0x20);
		else
			ch += lpData[cnt];
	}
	return ch;
}
int c_CheckName(char* filepath, char* data)
{
	int			num = 0;
	char		charname[48];
	char		checkname[48];
	char		fullpath[2048];
	char*		charlist;
	int			findsize = 0;
	HANDLE      hFind = NULL;
	DWORD       lowsize = 0, highsize = 0;

	ZeroMemory(charname, sizeof(char) * 48);
	ZeroMemory(fullpath, sizeof(char) * 2048);

	num = GetUserCode(data);
	c_GetFilePath(data, charname);

	wsprintf(fullpath, "%s\\%d.txt", filepath, num);

	hFind = CreateFile(fullpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		return 1;
	}
	else
	{
		lowsize = GetFileSize(hFind, &highsize);
		if(lowsize == 0) return 0;
		charlist = new char[lowsize + 1];
		ZeroMemory(charlist, sizeof(char)*(lowsize + 1));
		ReadFile(hFind, charlist, sizeof(char)*lowsize, &highsize, NULL);
		CloseHandle(hFind);
	}
	findsize = lowsize / 48;
	for(num = 0; num < findsize; num++)
	{
		memcpy(checkname, charlist + (48 * num), sizeof(char) * 48);
		if(strcmp(checkname, charname) == 0)
		{
			delete[] charlist;
			return 0;
		}
	}
	delete[] charlist;
	return 1;
}
