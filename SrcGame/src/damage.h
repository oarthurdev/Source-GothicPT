

DWORD	dm_GetRangeDamgeChkSum(TRANS_SKIL_ATTACKDATA2 *lpTransSkilAttackData2);

DWORD	dm_GetDamgeChkSum(TRANS_ATTACKDATA2 *lpTransAttackData2);

DWORD	dm_GetDamgeChkSum_S2V(TRANS_ATTACKDATA *lpTransAttackData);

DWORD	dm_GetCommandChkSum(smTRANS_COMMAND *lpTransCommand, DWORD dwObjectSerial);


int dm_SendTransDamage(smCHAR *lpChar, int PowParam1, int PowParam2, int AttackState, int Resistance, DWORD dwSkillCode, int UseAccuracy, smWINSOCK *lpsmSock);

int dm_SendTransDamage(smCHAR *lpChar, int PowParam1, int PowParam2, int AttackState, int Resistance, DWORD dwSkillCode, int UseAccuracy);



int dm_SelectRange(int x, int y, int z, int range, int UseAttackRating, int SelCount);

int dm_SelectRange(int x, int y, int z, int range, int UseAttackRating);

int dm_SelectRangeBox(smCHAR *lpCurChar, RECT *lpRect, int UseAttackRating);

int dm_SelectDamageCount(smCHAR *lpCurChar, int SelCount, int Size);

int dm_SelectDamageCount(smCHAR *lpCurChar, smCHAR *lpTragetChar, int SelCount, int Size);

int dm_SelectDamageChainCount(smCHAR *lpCurChar, smCHAR *lpTragetChar, int SelCount, int Size);


int dm_AddRangeDamage(smCHAR *lpChar);


int dm_SendRangeDamage(int x, int y, int z, smCHAR *lpMainTraget, int PowParam1, int PowParam2, int AttackState, int Registance, DWORD dwSkillCode);


int RecvDamagePacketModule(TRANS_FUNC_MEMORY *lpTransFuncModule);
int RecvDamagePacketModule2(TRANS_FUNC_MEMORY *lpTransFuncModule);

int RecvDynPacketModule(TRANS_FUNC_MEMORY *lpTransFuncModule);

typedef DWORD(*LPFN_EncodeDamagePacket)(void *lpPacket);
typedef DWORD(*LPFN_DecodeDamagePacket)(rsPLAYINFO *lpPlayInfo, void *lpPacket);
extern LPFN_EncodeDamagePacket	fnEncodeDamagePacket;
extern LPFN_DecodeDamagePacket	fnDecodeDamagePacket;
extern DWORD	dmAttackCount;

extern smCHAR	*lpSelected_Char[SKIL_ATTACK_CHAR_MAX];
extern int	dmSelected_CharCnt;

int	dm_EncodePacket(void *lpPacket);
int	dm_DecodePacket(DWORD dwObjectSerial, void *lpPacket);

int CheckMaxDamage();


int	LockSpeedProtect(smCHAR *lpChar);

int UnlockSpeedProtect(smCHAR *lpChar);
