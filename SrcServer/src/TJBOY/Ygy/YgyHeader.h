#pragma once
#ifndef __GLOBALHEADER_H__
#define __GLOBALHEADER_H__




#include <windows.h>


#include ".\\MemMap\\memmap.h"
#include ".\\Packet\\PacketStruct.h"
#include ".\\Packet\\Packet.h"
#include ".\\Process\\Process.h"
#include "util.h"


#ifndef VOICE_CHAT
#define VOICE_CHAT
#endif

#ifndef __YOUDEBUG
#define __YOUDEBUG
#endif

extern BOOL bCheckClan;


#endif