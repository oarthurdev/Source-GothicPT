
#pragma once
#ifndef __MEMMAP_H__
#define __MEMMAP_H__






#define MEMORYMAP_MAX		4096


#define MEMORYMAP_NAME		"PTE_CALL_VOICECHAT"   
class CMemMap
{
public:
	CMemMap();
	~CMemMap();
public:
	VOID	Clear();
	VOID	SetName(char* name);
	BOOL	InitMemoryMap();
	VOID	WriteMemoryMap(char *data);


	VOID	WriteMemoryMap(char *data, int size);


	VOID    ReadMemoryMap(char* data);
	VOID    SetMemMapSize(int size);

public:

	char    m_szMemMapName[64];
	HANDLE  m_hMemMap;

	char   *m_cMemMapPtr;
	int     m_nMemMapSize;

	BOOL    m_bIsMemMap;
};
#endif
