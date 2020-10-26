
int rsRecvAttackData_Old(rsPLAYINFO *lpPlayInfo, TRANS_ATTACKDATA *lpTransAttackData, smCHAR *lpTargetChar, int Type);

int rsRecvRangeAttackData_Old(rsPLAYINFO *lpPlayInfo, TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData, int Type);

int rsRecvRangeAttackUserData_Old(rsPLAYINFO *lpPlayInfo, TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData);



int rsRecvAttackData(rsPLAYINFO *lpPlayInfo, TRANS_ATTACKDATA2 *lpTransAttackData);

int rsRecvRangeAttackData(rsPLAYINFO *lpPlayInfo, TRANS_SKIL_ATTACKDATA2 *lpTransRangeAttackData);;


DWORD	dm_GetRangeDamgeChkSum(TRANS_SKIL_ATTACKDATA2 *lpTransSkilAttackData2);

DWORD	dm_GetDamgeChkSum(TRANS_ATTACKDATA2 *lpTransAttackData2);

DWORD	dm_GetCommandChkSum(smTRANS_COMMAND *lpTransCommand, DWORD dwObjectSerial);


int rsCheckSkillLevel(rsPLAYINFO *lpPlayInfo, DWORD dwSkillCode);


int	rsDecodeDamagePacket(rsPLAYINFO *lpPlayInfo, void *lpPacket);

int	rsEncodeDamagePacket(rsPLAYINFO *lpPlayInfo, void *lpPacket);

int rsSendDamageFuncToClient(rsPLAYINFO *lpPlayInfo);

int rsSendDamageFuncToClient2(rsPLAYINFO *lpPlayInfo);

int rsSetDamagePacketKey(rsPLAYINFO *lpPlayInfo);

int	rsProcessSafePacket(rsPLAYINFO *lpPlayInfo);

int	rsCompareSafePacket(rsPLAYINFO *lpPlayInfo, DWORD dwRcvPacketCode);


int rsRecordDamageError(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
