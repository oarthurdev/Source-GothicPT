
int	rsAddClientFuncPos(TRANS_CLIENT_FUNPOS	*lpClentFuncPos);

int	rsRecvClientFuncPos(TRANS_CLIENT_FUNPOS	*lpClentFuncPos);

TRANS_CLIENT_FUNPOS *rsGetClientPos(int Version);

int	rsResetClientFuncPos();


int rsSendFuncMemToClient(rsPLAYINFO *lpPlayInfo, DWORD dwFuncMem, DWORD	dwLen);

int	rsCompClientFuncMem(rsPLAYINFO *lpPlayInfo, DWORD	dwFunc, DWORD dwChkSum);

int	rsCompClientFuncMem2(rsPLAYINFO *lpPlayInfo, DWORD dwFuncCode);

int	rsCheckClientFuncMem(rsPLAYINFO *lpPlayInfo);
