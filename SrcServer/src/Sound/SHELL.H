/*==========================================================================
 *
 *  Copyright (C) 1995-1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       shell.h
 *  Content:    DirectSound shell header
 *
 ***************************************************************************/

#define MAXCONTROLS             80
#define MAXPAN_TB               800
#define MINPAN_TB               0
#define MINVOL_TB               0
#define MAXVOL_TB               400
#define SHIFTVOL_TB             (-400)
#define SHIFTPAN_TB             (-400)
#define MULTPAN_TB              (10L)
#define MULTVOL_TB              (10L)
#define MINVOL_VAL              -400
#define MAXVOL_VAL              0
#define MIDPAN_VAL              0


// To check for stopping of sounds, a timer is set...use this for the rate.
#define TIMERPERIOD     500 // In milliseconds



/*  This is the main head of the linked list, but its only used for the
	pNext which will point to the first FILEINFO structure, or NULL if there
	are no files loaded  */

/*
int NewDirectSoundBuffer(LSFILEINFO *pFileInfo );
int ChangeOutputVol(LSFILEINFO *pFileInfo );
int ChangeOutputFreq(LSFILEINFO *pFileInfo );
int ChangeOutputPan(LSFILEINFO *pFileInfo );
int ReleaseDirectSoundBuffer(LSFILEINFO *pFileInfo );
BOOL IsValidWave(LPSTR);

int StreamBufferSetup( LPSTR lpszBkFilename );
void ResetWavePlayer( void );
void FillDataBuffer( void );
void CloseBackground();
void CALLBACK TimeFunc( UINT uTimerID, UINT uMsg,
						DWORD dwUser, DWORD dw1, DWORD dw2 );
*/
