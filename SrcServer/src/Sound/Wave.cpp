



#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include "wave.h"


BOOL LSEnable = FALSE;






int WaveOpenFile(char *pszFileName, HMMIO *phmmioIn, WAVEFORMATEX **ppwfxInfo, MMCKINFO *pckInRIFF)
{
	HMMIO         hmmioIn;
	MMCKINFO      ckIn;
	PCMWAVEFORMAT pcmWaveFormat;
	WORD          cbExtraAlloc;
	int           nError;


	*ppwfxInfo = NULL;
	nError = 0;
	hmmioIn = NULL;

	if((hmmioIn = mmioOpen(pszFileName, NULL, MMIO_ALLOCBUF | MMIO_READ)) == NULL)
	{
		nError = ER_CANNOTOPEN;
		goto ERROR_READING_WAVE;
	}

	if((nError = (int)mmioDescend(hmmioIn, pckInRIFF, NULL, 0)) != 0)
	{
		goto ERROR_READING_WAVE;
	}

	if((pckInRIFF->ckid != FOURCC_RIFF) || (pckInRIFF->fccType != mmioFOURCC('W', 'A', 'V', 'E')))
	{
		nError = ER_NOTWAVEFILE;
		goto ERROR_READING_WAVE;
	}


	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if((nError = (int)mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK)) != 0)
	{
		goto ERROR_READING_WAVE;
	}




	if(ckIn.cksize < (long) sizeof(PCMWAVEFORMAT))
	{
		nError = ER_NOTWAVEFILE;
		goto ERROR_READING_WAVE;
	}


	if(mmioRead(hmmioIn, (HPSTR)&pcmWaveFormat, (long) sizeof(pcmWaveFormat)) != (long) sizeof(pcmWaveFormat))
	{
		nError = ER_CANNOTREAD;
		goto ERROR_READING_WAVE;
	}




	if(pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		cbExtraAlloc = 0;
	}
	else
	{

		if(mmioRead(hmmioIn, (LPSTR)&cbExtraAlloc, (long)sizeof(cbExtraAlloc)) != (long) sizeof(cbExtraAlloc))
		{
			nError = ER_CANNOTREAD;
			goto ERROR_READING_WAVE;
		}
	}


	if((*ppwfxInfo = (WAVEFORMATEX*)GlobalAlloc(GMEM_FIXED, sizeof(WAVEFORMATEX) + cbExtraAlloc)) == NULL)
	{
		nError = ER_MEM;
		goto ERROR_READING_WAVE;
	}


	memcpy(*ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
	(*ppwfxInfo)->cbSize = cbExtraAlloc;


	if(cbExtraAlloc != 0)
	{
		if(mmioRead(hmmioIn, (LPSTR)(((BYTE*)&((*ppwfxInfo)->cbSize)) + sizeof(cbExtraAlloc)), (long)(cbExtraAlloc)) != (long)(cbExtraAlloc))
		{
			nError = ER_NOTWAVEFILE;
			goto ERROR_READING_WAVE;
		}
	}


	if((nError = mmioAscend(hmmioIn, &ckIn, 0)) != 0)
	{
		goto ERROR_READING_WAVE;
	}
	goto TEMPCLEANUP;

ERROR_READING_WAVE:
	if(*ppwfxInfo != NULL)
	{
		GlobalFree(*ppwfxInfo);
		*ppwfxInfo = NULL;
	}

	if(hmmioIn != NULL)
	{
		mmioClose(hmmioIn, 0);
		hmmioIn = NULL;
	}

TEMPCLEANUP:
	*phmmioIn = hmmioIn;

	return nError;
}



int WaveStartDataRead(HMMIO *phmmioIn, MMCKINFO *pckIn, MMCKINFO *pckInRIFF)
{
	int nError;

	nError = 0;


	if((nError = mmioSeek(*phmmioIn, pckInRIFF->dwDataOffset + sizeof(FOURCC), SEEK_SET)) == -1)
	{
		LSEnable = FALSE;
	}

	nError = 0;

	pckIn->ckid = mmioFOURCC('d', 'a', 't', 'a');
	if((nError = mmioDescend(*phmmioIn, pckIn, pckInRIFF, MMIO_FINDCHUNK)) != 0)
	{
		goto ERROR_READING_WAVE;
	}

	goto CLEANUP;

ERROR_READING_WAVE:

CLEANUP:
	return nError;
}



int WaveReadFile(HMMIO hmmioIn, UINT cbRead, BYTE *pbDest, MMCKINFO *pckIn, UINT *cbActualRead)
{
	UINT i;
	MMIOINFO mmioinfoIn;
	int      nError;
	UINT     cbDataIn;

	nError = 0;

	if((nError = mmioGetInfo(hmmioIn, &mmioinfoIn, 0)) != 0)
	{
		goto ERROR_CANNOT_READ;
	}

	cbDataIn = cbRead;
	if(cbDataIn > pckIn->cksize)
		cbDataIn = pckIn->cksize;

	pckIn->cksize -= cbDataIn;

	for(i = 0; i < cbDataIn; i++)
	{

		if(mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			if((nError = mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ)) != 0)
			{
				goto ERROR_CANNOT_READ;
			}
			if(mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
			{
				nError = ER_CORRUPTWAVEFILE;
				goto ERROR_CANNOT_READ;
			}
		}


		*((BYTE*)pbDest + i) =
			*((BYTE*)mmioinfoIn.pchNext);


		*mmioinfoIn.pchNext++;

	}

	if((nError = mmioSetInfo(hmmioIn, &mmioinfoIn, 0)) != 0)
	{
		goto ERROR_CANNOT_READ;
	}

	*cbActualRead = cbDataIn;
	goto FINISHED_READING;

ERROR_CANNOT_READ:
	*cbActualRead = 0;

FINISHED_READING:
	return nError;
}


int WaveCloseReadFile(HMMIO *phmmio, WAVEFORMATEX **ppwfxSrc)
{
	if(*ppwfxSrc != NULL)
	{
		GlobalFree(*ppwfxSrc);
		*ppwfxSrc = NULL;
	}

	if(*phmmio != NULL)
	{
		mmioClose(*phmmio, 0);
		*phmmio = NULL;
	}

	return 0;
}


int WaveCreateFile(char *pszFileName, HMMIO *phmmioOut, WAVEFORMATEX *pwfxDest, MMCKINFO *pckOut, MMCKINFO *pckOutRIFF)
{
	int      nError;
	DWORD    dwFactChunk;
	MMCKINFO ckOut1;

	dwFactChunk = (DWORD)-1;
	nError = 0;

	*phmmioOut = mmioOpen(pszFileName, NULL, MMIO_ALLOCBUF | MMIO_READWRITE | MMIO_CREATE);

	if(*phmmioOut == NULL)
	{
		nError = ER_CANNOTWRITE;
		goto ERROR_CANNOT_WRITE;
	}


	pckOutRIFF->fccType = mmioFOURCC('W', 'A', 'V', 'E');
	pckOutRIFF->cksize = 0;
	if((nError = mmioCreateChunk(*phmmioOut, pckOutRIFF, MMIO_CREATERIFF)) != 0)
	{
		goto ERROR_CANNOT_WRITE;
	}





	pckOut->ckid = mmioFOURCC('f', 'm', 't', ' ');
	pckOut->cksize = sizeof(PCMWAVEFORMAT);
	if((nError = mmioCreateChunk(*phmmioOut, pckOut, 0)) != 0)
	{
		goto ERROR_CANNOT_WRITE;
	}


	if(pwfxDest->wFormatTag == WAVE_FORMAT_PCM)
	{
		if((UINT)(mmioWrite(*phmmioOut, (HPSTR)pwfxDest, sizeof(PCMWAVEFORMAT))) != sizeof(PCMWAVEFORMAT))
		{
			nError = ER_CANNOTWRITE;
			goto ERROR_CANNOT_WRITE;
		}
	}
	else
	{

		if((UINT)mmioWrite(*phmmioOut, (HPSTR)pwfxDest, sizeof(*pwfxDest) + pwfxDest->cbSize) != (sizeof(*pwfxDest) + pwfxDest->cbSize))
		{
			nError = ER_CANNOTWRITE;
			goto ERROR_CANNOT_WRITE;
		}
	}


	if((nError = mmioAscend(*phmmioOut, pckOut, 0)) != 0)
	{
		goto ERROR_CANNOT_WRITE;
	}



	ckOut1.ckid = mmioFOURCC('f', 'a', 'c', 't');
	ckOut1.cksize = 0;
	if((nError = mmioCreateChunk(*phmmioOut, &ckOut1, 0)) != 0)
	{
		goto ERROR_CANNOT_WRITE;
	}

	if((UINT)mmioWrite(*phmmioOut, (HPSTR)&dwFactChunk, sizeof(dwFactChunk)) != sizeof(dwFactChunk))
	{
		nError = ER_CANNOTWRITE;
		goto ERROR_CANNOT_WRITE;
	}


	if((nError = mmioAscend(*phmmioOut, &ckOut1, 0)) != 0)
	{
		nError = ER_CANNOTWRITE;
		goto ERROR_CANNOT_WRITE;
	}

	goto DONE_CREATE;

ERROR_CANNOT_WRITE:



DONE_CREATE:
	return nError;

}


int WaveStartDataWrite(HMMIO *phmmioOut, MMCKINFO *pckOut, MMIOINFO *pmmioinfoOut)
{
	int nError;

	nError = 0;

	pckOut->ckid = mmioFOURCC('d', 'a', 't', 'a');
	pckOut->cksize = 0;
	if((nError = mmioCreateChunk(*phmmioOut, pckOut, 0)) != 0)
	{
		goto ERROR_CANNOT_WRITE;
	}

	if((nError = mmioGetInfo(*phmmioOut, pmmioinfoOut, 0)) != 0)
	{
		goto ERROR_CANNOT_WRITE;
	}

	goto CLEANUP;
ERROR_CANNOT_WRITE:

CLEANUP:
	return nError;
}


int WaveWriteFile(HMMIO hmmioOut, UINT cbWrite, BYTE *pbSrc, MMCKINFO *pckOut, UINT *cbActualWrite, MMIOINFO *pmmioinfoOut)
{
	int  nError;

	nError = 0;

	*cbActualWrite = 0;

	for(UINT i = 0; i < cbWrite; i++)
	{
		if(pmmioinfoOut->pchNext == pmmioinfoOut->pchEndWrite)
		{
			pmmioinfoOut->dwFlags |= MMIO_DIRTY;
			if((nError = mmioAdvance(hmmioOut, pmmioinfoOut, MMIO_WRITE)) != 0)
			{
				goto ERROR_CANNOT_WRITE;
			}
		}


		*((BYTE*)pmmioinfoOut->pchNext) = *((BYTE*)pbSrc + i);

		*pmmioinfoOut->pchNext++;

		(*cbActualWrite)++;
	}

ERROR_CANNOT_WRITE:



	return nError;
}




int WaveCloseWriteFile(HMMIO *phmmioOut, MMCKINFO *pckOut, MMCKINFO *pckOutRIFF, MMIOINFO *pmmioinfoOut, DWORD cSamples)
{
	int nError;

	nError = 0;

	if(*phmmioOut == NULL) return 0;

	pmmioinfoOut->dwFlags |= MMIO_DIRTY;
	if((nError = mmioSetInfo(*phmmioOut, pmmioinfoOut, 0)) != 0)
	{

		goto ERROR_CANNOT_WRITE;
	}



	if((nError = mmioAscend(*phmmioOut, pckOut, 0)) != 0)
		goto ERROR_CANNOT_WRITE;


	if((nError = mmioAscend(*phmmioOut, pckOutRIFF, 0)) != 0)
		goto ERROR_CANNOT_WRITE;

	nError = mmioSeek(*phmmioOut, 0, SEEK_SET);
	if((nError = (int)mmioDescend(*phmmioOut, pckOutRIFF, NULL, 0)) != 0)
	{
		goto ERROR_CANNOT_WRITE;
	}

	nError = 0;
	pckOut->ckid = mmioFOURCC('f', 'a', 'c', 't');
	if((nError = mmioDescend(*phmmioOut, pckOut, pckOutRIFF, MMIO_FINDCHUNK)) == 0)
	{


		nError = mmioWrite(*phmmioOut, (HPSTR)&cSamples, sizeof(DWORD));
		nError = mmioAscend(*phmmioOut, pckOut, 0);
		nError = 0;
	}
	else
	{
		nError = 0;
		LSEnable = FALSE;

	}





	if((nError = mmioAscend(*phmmioOut, pckOutRIFF, 0)) != 0)
		goto ERROR_CANNOT_WRITE;

ERROR_CANNOT_WRITE:
	if(*phmmioOut != NULL)
	{
		mmioClose(*phmmioOut, 0);
		*phmmioOut = NULL;
	}

	return nError;
}



int WaveCopyUselessChunks(HMMIO *phmmioIn, MMCKINFO *pckIn, MMCKINFO *pckInRiff, HMMIO *phmmioOut, MMCKINFO *pckOut, MMCKINFO *pckOutRiff)
{
	int nError;

	nError = 0;

	if((nError = mmioSeek(*phmmioIn, pckInRiff->dwDataOffset + sizeof(FOURCC), SEEK_SET)) == -1)
	{
		nError = ER_CANNOTREAD;
		goto ERROR_IN_PROC;
	}

	nError = 0;

	while(mmioDescend(*phmmioIn, pckIn, pckInRiff, 0) == 0)
	{


		if((pckIn->dwDataOffset + pckIn->cksize) > (pckInRiff->dwDataOffset + pckInRiff->cksize))
			goto ERROR_IN_PROC;

		switch(pckIn->ckid)
		{

			case mmioFOURCC('f', 'm', 't', ' '):
			break;
			case mmioFOURCC('d', 'a', 't', 'a'):
			break;
			case mmioFOURCC('f', 'a', 'c', 't'):
			break;
			case mmioFOURCC('J', 'U', 'N', 'K'):
			break;
			case mmioFOURCC('P', 'A', 'D', ' '):
			break;
			case mmioFOURCC('c', 'u', 'e', ' '):
			break;

			case mmioFOURCC('p', 'l', 's', 't'):

			riffCopyChunk(*phmmioIn, *phmmioOut, pckIn);
			break;
			case mmioFOURCC('D', 'I', 'S', 'P'):
			riffCopyChunk(*phmmioIn, *phmmioOut, pckIn);
			break;

			default:
			break;
		}

		mmioAscend(*phmmioIn, pckIn, 0);
	}

ERROR_IN_PROC:
	{

		mmioSeek(*phmmioIn, pckInRiff->dwDataOffset + sizeof(FOURCC), SEEK_SET);
	}

	return nError;
}



BOOL riffCopyChunk(HMMIO hmmioSrc, HMMIO hmmioDst, const LPMMCKINFO lpck)
{
	MMCKINFO    ck;
	HPSTR       hpBuf;

	hpBuf = (HPSTR)GlobalAllocPtr(GHND, lpck->cksize);
	if(!hpBuf) return FALSE;

	ck.ckid = lpck->ckid;
	ck.cksize = lpck->cksize;
	if(mmioCreateChunk(hmmioDst, &ck, 0))
		goto rscc_Error;

	if(mmioRead(hmmioSrc, hpBuf, lpck->cksize) != (LONG)lpck->cksize)
		goto rscc_Error;

	if(mmioWrite(hmmioDst, hpBuf, lpck->cksize) != (LONG)lpck->cksize)
		goto rscc_Error;

	if(mmioAscend(hmmioDst, &ck, 0))
		goto rscc_Error;

	if(hpBuf) GlobalFreePtr(hpBuf);

	return TRUE;

rscc_Error:

	if(hpBuf) GlobalFreePtr(hpBuf);

	return FALSE;
}





int WaveLoadFile(char *pszFileName, UINT *cbSize, DWORD *pcSamples, WAVEFORMATEX **ppwfxInfo, BYTE **ppbData)
{
	HMMIO    hmmioIn;
	MMCKINFO ckInRiff;
	MMCKINFO ckIn;
	int      nError;
	UINT     cbActualRead;

	*ppbData = NULL;
	*ppwfxInfo = NULL;
	*cbSize = 0;

	if((nError = WaveOpenFile(pszFileName, &hmmioIn, ppwfxInfo, &ckInRiff)) != 0)
	{
		goto ERROR_LOADING;
	}

	if((nError = WaveStartDataRead(&hmmioIn, &ckIn, &ckInRiff)) != 0)
	{
		goto ERROR_LOADING;
	}


	if((*ppbData = (BYTE *)GlobalAlloc(GMEM_FIXED, ckIn.cksize)) == NULL)
	{
		nError = ER_MEM;
		goto ERROR_LOADING;
	}

	if((nError = WaveReadFile(hmmioIn, ckIn.cksize, *ppbData, &ckIn, &cbActualRead)) != 0)
	{
		goto ERROR_LOADING;
	}

	*cbSize = cbActualRead;
	goto DONE_LOADING;

ERROR_LOADING:
	if(*ppbData != NULL)
	{
		GlobalFree(*ppbData);
		*ppbData = NULL;
	}
	if(*ppwfxInfo != NULL)
	{
		GlobalFree(*ppwfxInfo);
		*ppwfxInfo = NULL;
	}

DONE_LOADING:

	if(hmmioIn != NULL)
	{
		mmioClose(hmmioIn, 0);
		hmmioIn = NULL;
	}

	return nError;
}


int WaveSaveFile(char *pszFileName, UINT cbSize, DWORD cSamples, WAVEFORMATEX *pwfxDest, BYTE *pbData)
{
	HMMIO     hmmioOut;
	MMCKINFO  ckOut;
	MMCKINFO  ckOutRIFF;
	MMIOINFO  mmioinfoOut;
	UINT      cbActualWrite;
	int       nError;

	if((nError = WaveCreateFile(pszFileName, &hmmioOut, pwfxDest, &ckOut, &ckOutRIFF)) != 0)
	{
		goto ERROR_SAVING;
	}

	if((nError = WaveStartDataWrite(&hmmioOut, &ckOut, &mmioinfoOut)) != 0)
	{
		goto ERROR_SAVING;
	}

	if((nError = WaveWriteFile(hmmioOut, cbSize, pbData, &ckOut, &cbActualWrite, &mmioinfoOut)) != 0)
	{
		goto ERROR_SAVING;
	}

	if((nError = WaveCloseWriteFile(&hmmioOut, &ckOut, &ckOutRIFF, &mmioinfoOut, cSamples)) != 0)
	{
		goto ERROR_SAVING;
	}

ERROR_SAVING:

	return nError;
}
