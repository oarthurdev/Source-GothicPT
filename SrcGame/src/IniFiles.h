#pragma once
#include <Windows.h>


class IniFiles
{
public:
					IniFiles(LPCTSTR pszFileName);
	virtual			~IniFiles();

	INT				ReadInt(LPCSTR pszSection, LPCSTR pszKey);
	BOOL			ReadBool(LPCSTR pszSection, LPCSTR pszKey);
	BOOL			ReadOnOff(LPCSTR pszSection, LPCSTR pszKey);
	FLOAT			ReadFloat(LPCSTR pszSection, LPCSTR pszKey);
	LPSTR			ReadString(LPCSTR pszSection, LPCSTR pszKey);

	VOID			WriteInt(LPCSTR pszSection, LPCSTR pszKey, INT iValue);
	VOID			WriteBool(LPCSTR pszSection, LPCSTR pszKey, BOOL bValue);
	VOID			WriteOnOff(LPCSTR pszSection, LPCSTR pszKey, BOOL bValue);
	VOID			WriteFloat(LPCSTR pszSection, LPCSTR pszKey, FLOAT fValue);
	VOID			WriteString(LPCSTR pszSection, LPCSTR pszKey, LPCSTR pszValue);

private:
	CHAR			m_szFileName[MAX_PATH];

};

