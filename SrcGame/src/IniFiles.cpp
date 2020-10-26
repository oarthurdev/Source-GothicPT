#include "sinbaram\sinLinkHeader.h"
#include <Strsafe.h>
#include <new>

IniFiles::IniFiles(LPCSTR pszFileName)
{
	ZeroMemory(m_szFileName, MAX_PATH);
	StringCchCopy(m_szFileName, MAX_PATH, pszFileName);
}

IniFiles::~IniFiles()
{
}

INT IniFiles::ReadInt(LPCSTR pszSection, LPCSTR pszKey)
{
	INT iResult = GetPrivateProfileInt(pszSection, pszKey, 0, m_szFileName);

	return iResult;
}

BOOL IniFiles::ReadBool(LPCSTR pszSection, LPCSTR pszKey)
{
	CHAR szResult[255];

	GetPrivateProfileString(pszSection, pszKey, "", szResult, 255, m_szFileName);
	if (lstrcmpi(szResult, "True") == 0)
		return TRUE;

	return FALSE;
}

BOOL IniFiles::ReadOnOff(LPCSTR pszSection, LPCSTR pszKey)
{
	CHAR szResult[255];

	GetPrivateProfileString(pszSection, pszKey, "", szResult, 255, m_szFileName);
	if (lstrcmpi(szResult, "On") == 0)
		return TRUE;

	return FALSE;
}

FLOAT IniFiles::ReadFloat(LPCSTR pszSection, LPCSTR pszKey)
{
	CHAR szResult[255];
	DOUBLE fltResult;

	GetPrivateProfileString(pszSection, pszKey, "", szResult, 255, m_szFileName);
	fltResult = atof(szResult);

	return (FLOAT)fltResult;
}

LPSTR IniFiles::ReadString(LPCSTR pszSection, LPCSTR pszKey)
{
	LPSTR pszResult = new (std::nothrow) CHAR[255];

	if (!pszResult) return NULL;

	ZeroMemory(pszResult, 255);

	GetPrivateProfileString(pszSection, pszKey, "", pszResult, 255, m_szFileName);

	return pszResult;
}

VOID IniFiles::WriteInt(LPCSTR pszSection, LPCSTR pszKey, INT iValue)
{
	CHAR szValue[255];
	wsprintf(szValue, "%d", iValue);

	WritePrivateProfileString(pszSection, pszKey, szValue, m_szFileName);
}

VOID IniFiles::WriteBool(LPCSTR pszSection, LPCSTR pszKey, BOOL bValue)
{
	CHAR szValue[255];
	wsprintf(szValue, "%s", bValue ? "True" : "False");

	WritePrivateProfileString(pszSection, pszKey, szValue, m_szFileName);
}

VOID IniFiles::WriteOnOff(LPCSTR pszSection, LPCSTR pszKey, BOOL bValue)
{
	CHAR szValue[255];
	wsprintf(szValue, "%s", bValue ? "On" : "Off");

	WritePrivateProfileString(pszSection, pszKey, szValue, m_szFileName);
}

VOID IniFiles::WriteFloat(LPCSTR pszSection, LPCSTR pszKey, FLOAT fValue)
{
	CHAR szValue[255];
	wsprintf(szValue, "%f", fValue);

	WritePrivateProfileString(pszSection, pszKey, szValue, m_szFileName);
}

VOID IniFiles::WriteString(LPCSTR pszSection, LPCSTR pszKey, LPCSTR pszValue)
{
	WritePrivateProfileString(pszSection, pszKey, pszValue, m_szFileName);
}
