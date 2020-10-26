#define MICVOL_CPP

#include <windows.h>
#include "micvolume.h"

CMicVolume::CMicVolume(void)
{
}

CMicVolume::~CMicVolume(void)
{
}

BOOL CMicVolume::Init()
{
	h_mix = MixDevice(NULL, 0);
	if(NULL == h_mix)
	{
		return FALSE;
	}

	if(GetDevice() == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

HMIXER CMicVolume::MixDevice(HMIXER current_mix, unsigned int mix_id)
{
	HMIXER h_mixer;
	MIXERCAPS mixer_caps;

	if(mixerGetDevCaps(mix_id, &mixer_caps, sizeof(mixer_caps)) != MMSYSERR_NOERROR)
		return NULL;

	if(mixerOpen(&h_mixer, mix_id, DWORD(NULL), 0L, CALLBACK_WINDOW) != MMSYSERR_NOERROR)
		return NULL;

	if(current_mix != NULL)
	{
		if(mixerClose(current_mix) != MMSYSERR_NOERROR)
		{
		#ifdef _DEBUG
			MessageBox(NULL, "Mixer 장치가 사용중입니다.", "Mixer 열기실패", MB_ICONSTOP);
		#endif
			current_mix = NULL;
		}
	}






	return h_mixer;
}

void CMicVolume::GetMicDevice()
{
	MIXERCAPS mixer_caps;
	MIXERLINE mixer_line;
	mixerGetDevCaps((unsigned int)h_mix, &mixer_caps, sizeof(mixer_caps));

	for(int i = 0; i < m_WavIn.nDeviceNum; i++)
	{
		mixer_line.cbStruct = sizeof(mixer_line);
		mixer_line.dwDestination = m_WavIn.nIndex;
		mixer_line.dwSource = i;

		if(mixerGetLineInfo((HMIXEROBJ)h_mix, &mixer_line, MIXER_GETLINEINFOF_SOURCE) != MMSYSERR_NOERROR)
			continue;

		if(mixer_line.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE)
		{
			m_MicIn.nIndex = (short)i;
			m_MicIn.nLineID = mixer_line.dwLineID;
			GetDeviceCtrl(&m_MicIn);
			break;
		}
	}
}

BOOL CMicVolume::GetDevice()
{
	MIXERCAPS mixer_caps;
	MIXERLINE mixer_line;
	if(mixerGetDevCaps((unsigned int)h_mix, &mixer_caps, sizeof(mixer_caps)) != MMSYSERR_NOERROR)
	{
	#ifdef _DEBUG
		MessageBox(NULL, "등록된 장치의 정보를 읽을 수 없습니다.", "시스템 정보 오류", MB_ICONSTOP);
	#endif
		mixer_caps.cDestinations = 0;
		return FALSE;
	}

	for(unsigned int i = 0; i < mixer_caps.cDestinations; i++)
	{
		mixer_line.cbStruct = sizeof(mixer_line);
		mixer_line.dwDestination = i;
		if(mixerGetLineInfo((HMIXEROBJ)h_mix, &mixer_line, MIXER_GETLINEINFOF_DESTINATION) != MMSYSERR_NOERROR)
			continue;

		if(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS == mixer_line.dwComponentType)
		{
			m_WavOut.nDeviceNum = (short)mixer_line.cConnections;
			m_WavOut.nIndex = (short)i;
			m_WavOut.nLineID = mixer_line.dwLineID;
			strcpy(m_WavOut.DeviceName, mixer_line.szName);

		}
		else if(MIXERLINE_COMPONENTTYPE_DST_WAVEIN == mixer_line.dwComponentType)
		{
			m_WavIn.nDeviceNum = (short)mixer_line.cConnections;
			m_WavIn.nIndex = (short)i;
			m_WavIn.nLineID = mixer_line.dwLineID;
			strcpy(m_WavIn.DeviceName, mixer_line.szName);
		}
	}

	GetMicDevice();

	if(VolDevice(&m_MicIn) < 0)
	{
		return FALSE;
	}
	return TRUE;
}

float CMicVolume::VolDevice(MCS *pData)
{
	int nCnt = 1;
	float temp = 0;

	if(MIXERCONTROL_CONTROLF_MULTIPLE & pData->m_ctlMixerSpeaker.fdwControl) nCnt = pData->m_ctlMixerSpeaker.cMultipleItems;

	MIXERCONTROLDETAILS_UNSIGNED mixer_control_details_unsigned[10];
	MIXERCONTROLDETAILS mixer_control_details;
	mixer_control_details.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mixer_control_details.dwControlID = pData->m_ctlMixerSpeaker.dwControlID;
	mixer_control_details.cChannels = 1;
	mixer_control_details.cMultipleItems = pData->m_ctlMixerSpeaker.cMultipleItems;
	mixer_control_details.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mixer_control_details.paDetails = mixer_control_details_unsigned;

	if(mixerGetControlDetails((HMIXEROBJ)h_mix, &mixer_control_details, MIXER_GETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
	{
	#ifdef _DEBUG
		MessageBox(NULL, "내부함수 오류(mixerGetControlDetails)", "내부 함수 오류", MB_ICONSTOP);
	#endif
		return -1;
	}

	for(int i = 0; i < nCnt; i++)
	{
		temp = ((float)mixer_control_details_unsigned[i].dwValue * (float)pData->nMax + 65535 / 2) / 65535;
	}
	return temp;
}








void CMicVolume::GetDeviceCtrl(MCS *pData)
{
	MIXERLINE mixer_line;

	mixer_line.cbStruct = sizeof(MIXERLINE);
	mixer_line.dwLineID = pData->nLineID;

	if(mixerGetLineInfo((HMIXEROBJ)h_mix, &mixer_line, MIXER_GETLINEINFOF_LINEID) != MMSYSERR_NOERROR)
	{
	#ifdef _DEBUG
		MessageBox(NULL, "내부함수 수행중 오류(MixerGetLineInfo)", "장치 정보 오류", MB_ICONSTOP);
	#endif
		return;
	}
	else if(!mixer_line.cControls)
	{
	#ifdef _DEBUG
		MessageBox(NULL, "사용 가능한 기능 부재", "장치 오류", MB_ICONSTOP);
	#endif
		return;
	}

	MIXERLINECONTROLS mixer_line_controls;
	MIXERCONTROL *mixer_control = (MIXERCONTROL *)LocalAlloc(LPTR, sizeof(MIXERCONTROL)*(unsigned int)mixer_line.cControls);
	mixer_line_controls.cbStruct = sizeof(MIXERLINECONTROLS);
	mixer_line_controls.dwLineID = pData->nLineID;
	mixer_line_controls.cControls = mixer_line.cControls;
	mixer_line_controls.cbmxctrl = sizeof(MIXERCONTROL);
	mixer_line_controls.pamxctrl = mixer_control;

	if(mixerGetLineControls((HMIXEROBJ)h_mix, &mixer_line_controls, MIXER_GETLINECONTROLSF_ALL) != MMSYSERR_NOERROR)
	{
	#ifdef _DEBUG
		MessageBox(NULL, "내부함수 수행중 오류(mixerGetLineControls)", "장치 정보 오류", MB_ICONSTOP);
	#endif
	}
	else
	{
		for(unsigned int i = 0; i < mixer_line_controls.cControls; i++)
		{
			if(mixer_control[i].dwControlType == MIXERCONTROL_CONTROLTYPE_VOLUME)
			{
				pData->nMax = (int)min(32767, mixer_control[i].Metrics.cSteps - 1);
				int nPageIncrement = pData->nMax / 10;
				if(nPageIncrement <= 0) nPageIncrement = 1;
				nVolStep = (float)(pData->nMax / 9);




				pData->m_ctlMixerSpeaker = mixer_control[i];
			}
			else if(mixer_control[i].dwControlType == MIXERCONTROL_CONTROLTYPE_MUTE)
			{
				pData->m_ctlMixerMute = mixer_control[i];
			}
		}
	}

	LocalFree((HLOCAL)mixer_control);
}

void CMicVolume::SetDeviceCtrl(MCS *pData, float vol)
{
	int nCnt = 1;

	MIXERCONTROLDETAILS_UNSIGNED mixer_control_details_unsigned[10];
	MIXERCONTROLDETAILS mixer_control_details;
	mixer_control_details.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mixer_control_details.dwControlID = pData->m_ctlMixerSpeaker.dwControlID;
	mixer_control_details.cChannels = 1;
	mixer_control_details.cMultipleItems = pData->m_ctlMixerSpeaker.cMultipleItems;
	mixer_control_details.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mixer_control_details.paDetails = mixer_control_details_unsigned;

	if(MIXERCONTROL_CONTROLF_MULTIPLE & pData->m_ctlMixerSpeaker.fdwControl) nCnt = pData->m_ctlMixerSpeaker.cMultipleItems;

	for(int i = 0; i < nCnt; i++)
	{
		mixer_control_details_unsigned[i].dwValue = (int)((vol * 65535 + pData->nMax / 2) / pData->nMax);
	}
	if(mixerSetControlDetails((HMIXEROBJ)h_mix, &mixer_control_details, 0))
	{
	#ifdef _DEBUG
		MessageBox(NULL, "내부 함수 오류(mixerSetControlDetails)", "내부 함수 오류", MB_ICONSTOP);
	#endif
	}
	return;
}
