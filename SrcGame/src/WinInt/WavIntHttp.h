





#pragma once



struct SWavDownUrl
{

	char szRemainderUrl[128];
};



extern int  CreateWavIntHttp(char *lpWavUrlBasis);
extern void DestroyWavIntHttp(void);

extern int WavIntHttpPush(char *lpRemainderUrl);


extern void MainWavIntHttp(void);
