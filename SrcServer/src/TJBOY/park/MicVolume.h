#pragma once
#ifndef __MICVOL_H__
#define __MICVOL_H__

#include <Mmsystem.h>

typedef struct MixerControlStruct
{
	short nIndex;
	short nDeviceNum;
	unsigned int nLineID;
	int nMax;
	char DeviceName[64];
	MIXERCONTROL m_ctlMixerSpeaker;
	MIXERCONTROL m_ctlMixerMute;
} MCS;

class CMicVolume
{
public:
	HMIXER h_mix;
	MCS m_WavOut, m_WavIn, m_MicIn, m_MicOut;
	float nVolStep;
public:
	CMicVolume(void);
	~CMicVolume(void);

	BOOL Init();
	HMIXER MixDevice(HMIXER current_mix, unsigned int mix_id);
	void GetMicDevice();
	BOOL GetDevice();
	float VolDevice(MCS *pData);
	void GetDeviceCtrl(MCS *pData);
	void SetDeviceCtrl(MCS *pData, float vol);
};

#endif


#ifdef MICVOL_CPP

class CMicVolume cmicvol;

#else

extern class CMicVolume cmicvol;

#endif
