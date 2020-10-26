
#pragma once
#ifndef __PACKET_H__
#define __PACKET_H__

#include "../Memmap/memmap.h"




class CPacket
{
public:
	CPacket();
	~CPacket();
public:
	VOID Init();
	VOID Clear();
	VOID Parsing();

	char* GetData()
	{
		return memMapReadData;
	}
	VOID SetSelectCha(char *id, char *chaname, char *clanname, DWORD clannum);


	VOID SetClanChat(char *msg);


public:


private:
	INDEX			*m_Index;
	USERINFO		m_userInfo;

	CLANCHAT            m_sClanChat;


	char				memMapReadData[MEMORYMAP_MAX];
};
#endif
