
extern CRITICAL_SECTION	cSection_Main;
extern smWINSOCK	*lpWSockServer_Area[2];
extern smWINSOCK	*lpWSockServer_DispArea[2];
extern int	AreaServerMode;

int RecvAreaServerMap(TRANS_SEVER_MAP *lpTransServerMap);

extern DWORD	dwDebugAreaIP[4];
extern DWORD	dwDebugAreaCount;
extern DWORD	dwDebugAreaConnCount;
extern DWORD	dwDebugAreaStep;
