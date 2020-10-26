
#include "dxWav.h"
#include <windowsx.h>
#include <mmsystem.h>
#include <conio.h>



HRESULT     rval_g_lpDs;
HRESULT     dsrval_lpDirectSound;

int numSound = 0;

char dataDir[64];


int mouThRead;
BYTE *mouThdataOfs = NULL;

BOOL wav_opt = 1;

LPDIRECTSOUND           g_lpDS = NULL;
BOOL                    g_bSoundPresent = FALSE;
LPDIRECTSOUNDBUFFER     g_lpSounds[NUM_SOUNDS];
BOOL                    g_bSoundPaused = FALSE;


char sangJuWav[NUM_SOUNDS][64];
int  sangJuWav_F[NUM_SOUNDS] = { 1, };





int chk_load_sangJuWav(int wavN)
{
	if(sangJuWav_F[wavN - 1] == 1) return 1;
	sangJuWav_F[wavN - 1] = 1;
	CreateBufferFromWaveFile(sangJuWav[wavN - 1], wavN);

	return 1;
}


char *sangJuWav2[NUM_SOUNDS] = {
"Assets\\Audio\\rain01.wav",
"Assets\\Audio\\thunder1.wav",
"Assets\\Audio\\Button.wav",
"Assets\\Audio\\New.wav",
"Assets\\Audio\\CharacterDelete.wav",
"Assets\\Audio\\ButtonBack.wav",
"Assets\\Audio\\CharacterSelect.wav",

"Assets\\Audio\\NewChar.wav",
"Assets\\Audio\\Fire.wav",
"Assets\\Audio\\Thunder.wav",
"Assets\\Audio\\GameStart.wav",
"Assets\\Audio\\Login.wav",
NULL
};

char *wnameBuf[NUM_SOUNDS] = {
"Assets\\Audio\\bgm0.wav",
"Assets\\Audio\\rain01.wav",
"Assets\\Audio\\thunder1.wav",
"Assets\\Audio\\step01.wav",
"Assets\\Audio\\Effects\\weapon\\one hand swing - small 3.wav",
	NULL
};

int isPlaying(int i);


char *backMusicWav[] = {
"Assets\\Audio\\622s.wav",
NULL,
NULL,
};


int  BackMusic_Load(int stageNumber)
{
	if(g_bSoundPresent == FALSE) return 0;

	char strFilename[128];
	strcpy(strFilename, dataDir);

	strcat(strFilename, backMusicWav[stageNumber]);

	if(!CreateBufferFromWaveFile(strFilename, 0))
	{
		return FALSE;
	}
	return 1;
}

void BackMusicPlay()
{
	PlayWav(0, 1);
}


void BackMusicClr()
{
	StopAllWav();
	sBufferClear(0);
}

void PlayWavEffect(int num)
{
	PlayWav(num);
}

void BackMusic_Stop()
{
	StopWav(0);
}










BOOL InitDX_Wav(HWND g_hwnd)
{
	if(!wav_opt)
	{
		g_bSoundPresent = FALSE;
		return 0;
	}

	int i;









	if(rval_g_lpDs == DS_OK)
		g_bSoundPresent = TRUE;
	else
		g_bSoundPresent = FALSE;


	if(g_bSoundPresent)
	{



		g_lpDS->SetCooperativeLevel(g_hwnd, DSSCL_NORMAL);


		for(i = 0; i < NUM_SOUNDS; i++)
		{
			g_lpSounds[i] = NULL;
		}

		for(i = 0; i < NUM_SOUNDS; i++)
		{
			if(wnameBuf[i] != NULL)
			{
				if(!CreateBufferFromWaveFile(wnameBuf[i], i))

					return FALSE;
				numSound++;
			}
		}
	}

	return TRUE;
}









void TermDX_Wav()
{
	if(!g_bSoundPresent) return;


	for(int i = 0; i < NUM_SOUNDS; i++)
	{
		if(g_lpSounds[i])
		{
			g_lpSounds[i]->Release();
			g_lpSounds[i] = NULL;
		}
	}


	if(g_lpDS)
	{
		g_lpDS->Release();
		g_lpDS = NULL;
	}
}









BOOL CreateSoundBuffer(DWORD dwBuf, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo)
{
	PCMWAVEFORMAT pcmwf;
	DSBUFFERDESC dsbdesc;


	memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT));
	pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.wf.nChannels = bStereo ? 2 : 1;
	pcmwf.wf.nSamplesPerSec = dwFreq;
	pcmwf.wf.nBlockAlign = (WORD)dwBlkAlign;
	pcmwf.wf.nAvgBytesPerSec = pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
	pcmwf.wBitsPerSample = (WORD)dwBitsPerSample;


	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;

	dsbdesc.dwBufferBytes = dwBufSize;
	dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&pcmwf;

	g_lpDS->CreateSoundBuffer(&dsbdesc, &g_lpSounds[dwBuf], NULL);
	return TRUE;
}








BOOL ReadData(LPDIRECTSOUNDBUFFER lpDSB, FILE* pFile, DWORD dwSize, DWORD dwPos)
{

	if(dwPos != 0xffffffff)
	{
		if(fseek(pFile, dwPos, SEEK_SET) != 0)
		{
			return FALSE;
		}
	}


	LPVOID pData1;
	DWORD  dwData1Size;
	LPVOID pData2;
	DWORD  dwData2Size;
	HRESULT rval;
	rval = lpDSB->Lock(0, dwSize, &pData1, &dwData1Size, &pData2, &dwData2Size, DSBLOCK_FROMWRITECURSOR);
	if(rval != DS_OK)
	{
		return FALSE;
	}


	if(dwData1Size > 0)
	{
		if(fread(pData1, dwData1Size, 1, pFile) != 1)
		{
			return FALSE;
		}

		if(mouThRead == 0)
		{
			mouThdataOfs = (BYTE*)pData1;
		}

	}

	if(dwData2Size > 0)
	{
		if(fread(pData2, dwData2Size, 1, pFile) != 1)
		{
			return FALSE;
		}
	}


	rval = lpDSB->Unlock(pData1, dwData1Size, pData2, dwData2Size);
	if(rval != DS_OK)
	{
		return FALSE;
	}


	return TRUE;
}









BOOL CreateBufferFromWaveFile(char* FileName, DWORD dwBuf)
{
	DWORD dwSize;
	BOOL bStereo;

	FILE* pFile = fopen(FileName, "rb");
	if(pFile == NULL) return FALSE;


	WaveHeader1 wavHdr1;
	WaveHeader2 wavHdr2;

	WaveHeader0 wavHdr;
	if(fread(&wavHdr, sizeof(wavHdr), 1, pFile) != 1)
	{
		fclose(pFile);
		return NULL;
	}

	if(wavHdr.DATA[0] == 'd' && wavHdr.DATA[1] == 'a')
	{

		fseek(pFile, 0, SEEK_SET);
		fread(&wavHdr1, sizeof(wavHdr1), 1, pFile);
		dwSize = wavHdr1.dwDSize;

		bStereo = wavHdr1.wChnls > 1 ? TRUE : FALSE;

		if(!CreateSoundBuffer(dwBuf, dwSize, wavHdr1.dwSRate, wavHdr1.BitsPerSample, wavHdr1.wBlkAlign, bStereo))
		{

			fclose(pFile);
			return FALSE;
		}
		if(!g_lpSounds[dwBuf])
		{
			fclose(pFile);
			return FALSE;
		}

		mouThRead = dwBuf;

		if(!ReadData(g_lpSounds[dwBuf], pFile, dwSize, sizeof(wavHdr1)))
		{
			fclose(pFile);
			return FALSE;
		}
	}
	else if(wavHdr.DATA[0] == 'f' && wavHdr.DATA[1] == 'a')
	{

		fseek(pFile, 0, SEEK_SET);
		fread(&wavHdr2, sizeof(wavHdr2), 1, pFile);

		dwSize = wavHdr2.dwDSize;

		bStereo = wavHdr2.wChnls > 1 ? TRUE : FALSE;


		if(!CreateSoundBuffer(dwBuf, dwSize, wavHdr2.dwSRate, wavHdr2.BitsPerSample, wavHdr2.wBlkAlign, bStereo))
		{

			fclose(pFile);
			return FALSE;
		}


		mouThRead = dwBuf;

		if(!ReadData(g_lpSounds[dwBuf], pFile, dwSize, sizeof(wavHdr2)))
		{
			fclose(pFile);
			return FALSE;
		}
	}
	else
	{


		dwSize = wavHdr.dwDSize;

		bStereo = wavHdr.wChnls > 1 ? TRUE : FALSE;


		if(!CreateSoundBuffer(dwBuf, dwSize, wavHdr.dwSRate, wavHdr.BitsPerSample, wavHdr.wBlkAlign, bStereo))
		{

			fclose(pFile);
			return FALSE;
		}


		mouThRead = dwBuf;

		if(!ReadData(g_lpSounds[dwBuf], pFile, dwSize, sizeof(wavHdr)))
		{
			fclose(pFile);
			return FALSE;
		}
	}


	fclose(pFile);

	return TRUE;
}









BOOL ReadDataWavBuf(LPDIRECTSOUNDBUFFER lpDSB, BYTE *wavBUF, DWORD dwSize)
{


	int cnt = 0;

	LPVOID pData1;
	DWORD  dwData1Size;
	LPVOID pData2;
	DWORD  dwData2Size;
	HRESULT rval;

	rval = lpDSB->Lock(0, dwSize, &pData1, &dwData1Size, &pData2, &dwData2Size, DSBLOCK_FROMWRITECURSOR);
	if(rval != DS_OK)
	{
		return FALSE;
	}


	if(dwData1Size > 0)
	{




		memcpy(pData1, &wavBUF[cnt], dwData1Size);
		cnt += dwData1Size;

		if(mouThRead == 0)
		{
			mouThdataOfs = (BYTE*)pData1;
		}

	}


	if(dwData2Size > 0)
	{




		memcpy(pData2, &wavBUF[cnt], dwData2Size);
	}


	rval = lpDSB->Unlock(pData1, dwData1Size, pData2, dwData2Size);
	if(rval != DS_OK)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CreateBufferFromWavBUF(unsigned char* wavBUf, unsigned int dwBuf)
{
	DWORD dwSize;
	BOOL bStereo;
	BYTE cnt = 0;






	WaveHeader1 wavHdr1;
	WaveHeader2 wavHdr2;

	WaveHeader0 wavHdr;






	memcpy(&wavHdr, &wavBUf[cnt], sizeof(wavHdr));
	cnt += sizeof(wavHdr);


	if(wavHdr.DATA[0] == 'd' && wavHdr.DATA[1] == 'a')
	{


		cnt = 0;
		memcpy(&wavHdr1, &wavBUf[cnt], sizeof(wavHdr1));
		cnt += sizeof(wavHdr1);


		dwSize = wavHdr1.dwDSize;

		bStereo = wavHdr1.wChnls > 1 ? TRUE : FALSE;



		if(!CreateSoundBuffer(dwBuf, dwSize, wavHdr1.dwSRate, wavHdr1.BitsPerSample, wavHdr1.wBlkAlign, bStereo))
		{


			return FALSE;
		}



		mouThRead = dwBuf;


		if(!ReadDataWavBuf(g_lpSounds[dwBuf], &wavBUf[cnt], dwSize))
		{

			return FALSE;
		}
	}

	else if(wavHdr.DATA[0] == 'f' && wavHdr.DATA[1] == 'a')
	{


		cnt = 0;
		memcpy(&wavHdr2, &wavBUf[cnt], sizeof(wavHdr2));
		cnt += sizeof(wavHdr2);


		dwSize = wavHdr2.dwDSize;

		bStereo = wavHdr2.wChnls > 1 ? TRUE : FALSE;




		if(!CreateSoundBuffer(dwBuf, dwSize, wavHdr2.dwSRate, wavHdr2.BitsPerSample, wavHdr2.wBlkAlign, bStereo))
		{


			return FALSE;
		}


		mouThRead = dwBuf;


		if(!ReadDataWavBuf(g_lpSounds[dwBuf], &wavBUf[cnt], dwSize))
		{

			return FALSE;
		}
	}
	else
	{

		dwSize = wavHdr.dwDSize;

		bStereo = wavHdr.wChnls > 1 ? TRUE : FALSE;




		if(!CreateSoundBuffer(dwBuf, dwSize, wavHdr.dwSRate, wavHdr.BitsPerSample, wavHdr.wBlkAlign, bStereo))
		{


			return FALSE;
		}


		mouThRead = dwBuf;


		if(!ReadDataWavBuf(g_lpSounds[dwBuf], &wavBUf[cnt], dwSize))
		{

			return FALSE;
		}
	}




	return TRUE;
}

















BOOL StopAllWav()
{
	if(!g_bSoundPresent) return FALSE;


	for(int i = 0; i < NUM_SOUNDS; i++)
	{
		if(g_lpSounds[i])
		{
			DWORD dwStatus;

			g_lpSounds[i]->GetStatus(&dwStatus);

			if((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
			{


				g_lpSounds[i]->Stop();

			}
		}
	}


	return TRUE;
}





#define VOL_SHIFT (-400)
#define VOL_MULT 10

#define PAN_SHIFT (-400)
#define PAN_MULT  10

#define FRQ_MULT  10









BOOL PlayWav(DWORD dwSound, DWORD dwFlags, DWORD dwVol, DWORD dwfreq)
{
	if(g_bSoundPaused) return TRUE;
	if(!g_bSoundPresent) return TRUE;


	if(dwSound >= NUM_SOUNDS) return FALSE;


	chk_load_sangJuWav((int)dwSound);



	if(g_lpSounds[dwSound])
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if((dwStatus & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
		{

			g_lpSounds[dwSound]->SetVolume((dwVol + VOL_SHIFT) * VOL_MULT);
			g_lpSounds[dwSound]->SetFrequency(dwfreq*FRQ_MULT);
			g_lpSounds[dwSound]->Play(0, 0, dwFlags);

		}


		if(dwSound == 0)
			g_lpSounds[dwSound]->SetCurrentPosition(0);

	}


	return TRUE;
}



BOOL PlayWav2(DWORD dwSound, DWORD dwFlags, DWORD dwVol, DWORD dwfreq)
{
	if(g_bSoundPaused) return TRUE;
	if(!g_bSoundPresent) return TRUE;


	if(dwSound >= NUM_SOUNDS) return FALSE;


	chk_load_sangJuWav((int)dwSound);



	if(g_lpSounds[dwSound])
	{

		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)

			g_lpSounds[dwSound]->SetCurrentPosition(0);

		g_lpSounds[dwSound]->SetVolume((dwVol + VOL_SHIFT) * VOL_MULT);
		g_lpSounds[dwSound]->SetFrequency(dwfreq*FRQ_MULT);
		g_lpSounds[dwSound]->Play(0, 0, dwFlags);
	}

	return TRUE;
}


BOOL IsPlayWav(DWORD dwSound)
{
	DWORD dwStatus;

	if(g_bSoundPaused) return FALSE;
	if(!g_bSoundPresent) return FALSE;
	if(dwSound >= NUM_SOUNDS) return FALSE;
	if(!g_lpSounds[dwSound]) return FALSE;

	g_lpSounds[dwSound]->GetStatus(&dwStatus);

	if((dwStatus & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING) return FALSE;

	return TRUE;
}





BOOL PlayWav3(DWORD dwSound, DWORD dwFlags, DWORD dwVol, DWORD dwfreq, DWORD dwPan)
{
	if(g_bSoundPaused) return TRUE;
	if(!g_bSoundPresent) return TRUE;


	if(dwSound >= NUM_SOUNDS) return FALSE;


	chk_load_sangJuWav((int)dwSound);


	if(g_lpSounds[dwSound])
	{

		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)

			g_lpSounds[dwSound]->SetCurrentPosition(0);


		g_lpSounds[dwSound]->SetPan((dwPan + PAN_SHIFT)*PAN_MULT);


		g_lpSounds[dwSound]->SetFrequency(dwfreq*FRQ_MULT);


		g_lpSounds[dwSound]->SetVolume((dwVol + VOL_SHIFT) * VOL_MULT);
		g_lpSounds[dwSound]->Play(0, 0, dwFlags);
	}

	return TRUE;
}




BOOL PlayWav_VolChange(DWORD dwSound, DWORD dwVol)
{
	if(g_bSoundPaused) return TRUE;
	if(!g_bSoundPresent) return TRUE;


	if(dwSound >= NUM_SOUNDS) return FALSE;


	chk_load_sangJuWav((int)dwSound);


	if(g_lpSounds[dwSound])
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
		{

			g_lpSounds[dwSound]->SetVolume((dwVol + VOL_SHIFT) * VOL_MULT);
		}

	}
	return TRUE;
}


BOOL PlayWav_FrequencyChange(DWORD dwSound, DWORD dwfreq)
{
	if(g_bSoundPaused) return TRUE;
	if(!g_bSoundPresent) return TRUE;


	if(dwSound >= NUM_SOUNDS) return FALSE;


	if(g_lpSounds[dwSound])
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)

			g_lpSounds[dwSound]->SetFrequency(dwfreq*FRQ_MULT);
	}
	return TRUE;
}



BOOL PlayWav_PanChange(DWORD dwSound, DWORD dwPan)
{
	if(g_bSoundPaused) return TRUE;
	if(!g_bSoundPresent) return TRUE;


	if(dwSound >= NUM_SOUNDS) return FALSE;


	if(g_lpSounds[dwSound])
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)

			g_lpSounds[dwSound]->SetPan((dwPan + PAN_SHIFT)*PAN_MULT);
	}
	return TRUE;
}



BOOL StopWav(int i);


void check_backMus(int flag)
{
	if(flag == 0)
	{
		StopWav(0);
	}
	else
	{
		StopWav(0);
		PlayWav(0, 1);
	}
}

















void TermDX_Wav2()
{
	if(!g_bSoundPresent) return;

	for(int i = 0; i < NUM_SOUNDS; i++)
	{
		if(g_lpSounds[i])
		{
			PlayWav_VolChange(i, 0);
			g_lpSounds[i]->Release();	g_lpSounds[i] = NULL;
		}
	}
	if(g_lpDS)
	{
		g_lpDS->Release();
		g_lpDS = NULL;
	}

	Uninit_BGM();
}


BOOL CreateBufferFromWaveFile2(char* FileName, int sbufN)
{
	if(!g_bSoundPresent)
	{
		return FALSE;
	}
	StopWav(sbufN);
	sBufferClear(sbufN);

	if(!CreateBufferFromWaveFile(FileName, sbufN))
	{
		sBufferClear(sbufN);
		return FALSE;
	}
	return TRUE;
}


BOOL sBufferClear(int sbufN)
{
	if(!g_bSoundPresent)
	{
		return FALSE;
	}

	if(g_lpSounds[sbufN])
	{
		g_lpSounds[sbufN]->Release();
		g_lpSounds[sbufN] = NULL;
		return TRUE;
	}
	return FALSE;
}


BOOL StopWav(int i)
{
	if(!g_bSoundPresent)
	{
		return FALSE;
	}


	if(g_lpSounds[i])
	{
		DWORD dwStatus;

		g_lpSounds[i]->GetStatus(&dwStatus);

		if((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
		{


			g_lpSounds[i]->Stop();
		}
	}

	return TRUE;
}



void allWAVE_playORstop(int flag)
{
	int i;
	if(flag == 0)
	{
		for(i = 0; i < NUM_SOUNDS; i++)
		{
			if(g_lpSounds[i])
			{
				StopWav(i);
			}
		}
	}
	else
	{

		if(g_lpSounds[0])
		{
			StopWav(0);
			PlayWav(0);
		}
	}
}












DWORD get_pos(DWORD dwSound)
{
	DWORD pos;
	if(g_bSoundPaused) return TRUE;
	if(!g_bSoundPresent) return TRUE;


	if(dwSound >= NUM_SOUNDS) return FALSE;


	if(g_lpSounds[dwSound])
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);

		if((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
		{

			g_lpSounds[dwSound]->GetCurrentPosition(&pos, NULL);



			return pos;
		}
	}


	return 0;
}







BYTE getmouTH()
{
	if(mouThdataOfs == NULL) return 0;

	DWORD pos = get_pos(0);
	BYTE b = mouThdataOfs[pos];
	return b;
}

int isPlaying(int i)
{
	if(!g_bSoundPresent) return FALSE;


	if(g_lpSounds[i])
	{
		DWORD dwStatus;

		g_lpSounds[i]->GetStatus(&dwStatus);

		if((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
		{


			return 1;
		}
		else
		{
			return 0;
		}
	}

	return 0;
}











































































#include "wave.h"
#include "shell.h"
#include "stream.h"




HRESULT SetupStreamBuffer(LPSTR lpszFilename);


LPDIRECTSOUND       lpDirectSound = NULL;

LPDIRECTSOUNDBUFFER lpDSBStreamBuffer = NULL;


HWND    m_hWnd;

LONG  m_lInTimer = FALSE;
BOOL  m_bTimerInit = FALSE;
BOOL  m_bPlaying = FALSE;
BOOL  m_bIsCloseOnRun = FALSE;
BOOL  m_bFileOpen = FALSE;
UINT  m_uTimerID = 0;
DWORD m_SecondBuffFocus = 0;

WAVEINFOCA  m_wiWave;



void LSStopBackground(DWORD dwState);
void LSResetWavePlayer(void);
void LSFillDataBuffer(void);
void CALLBACK LSTimeRunFuncForDSound(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);







void LSStopBackground(DWORD dwState)
{}




void LSResetWavePlayer(void)
{}


void LSFillDataBuffer(void)
{}






void CALLBACK LSTimeRunFuncForDSound(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
}









BOOL OpenBGM(LPSTR lpszFileName)
{

	return TRUE;
}

HRESULT SetupStreamBuffer(LPSTR lpszFilename)
{
	
	return DS_OK;
}


void PlayBGM(void)
{
	
}

void StopBGM(void)
{
}

void SetVolumeBGM(DWORD dwVol)
{
}




BOOL Init_BGM(HWND hwnd)
{
	
	return TRUE;
}


void Uninit_BGM(void)
{
	
}


void InitDirectSound()
{
}




