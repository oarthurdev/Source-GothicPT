#define	CHAR_LEVEL_MAX	149  // LEVEL MAX SERVIDOR


#define sinNPC_SHOP				0x00000001	
#define sinNPC_MIX				0x00000002	
#define sinNPC_AGING			0x00000004	
#define sinNPC_WARE				0x00000008	
#define sinNPC_SKILL			0x00000010	
#define sinNPC_FORCE			0x00000020	
#define sinNPC_SMELTING			0x00000030	
#define sinNPC_MANUFACTURE		0x00000040	
#define sinNPC_MIXTURE_RESET	0x00000080	






extern DWORD	dwFuncChkTime;

DWORD Check_CodeSafe(DWORD dwStartFunc);
DWORD Check_CodeSafe2();
DWORD	GetSafeCode();
DWORD	GetSafeCode2();
int Code_VRamBuffOpen();
int	Mix_CodeVram();

extern char	szLastWhisperName[32];
extern int	LastWhisperLen;
extern int	PlayerArmor;

extern int	PlayUsed_Resurrection;


int SetPlayerArmor(int armor);

char *GetFaceHairSkin(smCHAR *lpChar);






int GetInvenPotionCount(sCHK_POTION_COUNT *ChkPotion);

int	ResetPotion();

int	ResetPotion2();

int	ComparePotion();

int	XorCheckPotion(sCHK_POTION_COUNT *ChkPotion);



int	WhisperPartyPlayer(char *szName);

int	SetClanChatting();

int IsClanChatting();


int AddExp(int Exp);

INT64 GetNextExp(int Level);

int	CheckLevelExp(int Level, INT64 Exp);

int	GetLevelFromExp(INT64 Exp);

int	SetExp64(smCHAR_INFO *smCharInfo, INT64 Exp64);

INT64 GetExp64(smCHAR_INFO *smCharInfo);

INT64 GetXorExp64(smCHAR_INFO *smCharInfo);

INT64 CodeXorCharInfo_Exp();


int CheckFieldContExp();



int	ActionEtherCore(sITEM	*lpItem);


int DeadPlayerExp(smCHAR *lpChar);

int ContGameExp(smCHAR *lpChar);

int GetPlayDefence(smCHAR_INFO *lpAttackCharInfo, smCHAR_INFO *lpDefenceCharInfo);


int DrawWeather(int ax);
int InitWeatherSystem();

int AddRemoveDynPattern(smDPAT *lpDinaPattern);


int LoadOftenModels();


int	LoadOftenMeshPattern(char *szFileName);

int LoadOftenArmor();

int LoadOftenItem();

int LoadOftenNpc();

int LoadOftenFace();

int CheckOftenMeshTextureSwap();

int	ChangeModelSkin(smCHAR *lpChar, int ComicArmor, int ComicHeadNum, char *szArmor, char *szHead);

int ChangeHairModel(int HairCode);



int InitFieldMap();


int MainFieldMap();

int DrawFieldMap();

int GetFieldMapCursor();

int psSetDefaultRenderState();



int EecodeCompress(BYTE *lpSrcData, BYTE *lpDestData, int size);

int DecodeCompress(BYTE *lpSrcData, BYTE *lpDestData);

int DecodeCompress(BYTE *lpSrcData, BYTE *lpDestData, int dCount);

int EecodeCompress(BYTE *lpSrcData, BYTE *lpDestData, int size, int DestSize);


int DecodeCompress_ItemPotion(rsPLAYINFO *lpPlayInfo, BYTE *lpSrcData, BYTE *lpDestData, int deCount, void *lpTransRecdata);



smCHAR *CheckOtherPlayPosi(int x, int y, int z);


int ReformItem(sITEMINFO *lpItemInfo);

int ReformItem_AdjustTime(sITEMINFO *lpItemInfo, int TimeAdjust);


int CheckItemForm(sITEMINFO *lpItemInfo);

int CompareItems(sITEMINFO *lpItemInfo1, sITEMINFO *lpItemInfo2);

int	rsReformItem_Server(sITEMINFO *lpItemInfo);


int CheckCharForm();

int ReformCharForm();

int ReformCharForm(smCHAR_INFO *lpCharInfo);

int CheckCharForm(smCHAR_INFO *lpCharInfo);

int ReformTrade(void *lpTrade);

int CheckTrade(void *lpTrade);


int ReformMixItem(sITEMINFO *lpItemInfo);

int CheckMixItem(sITEMINFO *lpItemInfo);


float GetItemAbsorb(sITEMINFO *lpItemInfo);


int	RequestPartyPlayers(smCHAR	*lpChar);

int psSetDefaultRenderState();


smTRNAS_PLAYERINFO	*GetCharInfoCache(char *lpData);

int SaveCharInfoCache(smTRNAS_PLAYERINFO *lpTransPlayInfo);

extern smCHAR	chrPartyPlayer;

int OpenPartyPlayer(char *szName, char *szModelFile1, char *szModelFile2);



int	CheckPlayAttackCount();

int AttackMotionCountUp();

int	AttackRecvCountUp();

int	CheckCopyItem(sITEMINFO *lpItem);

int ChangeJobFace();



int InitTimeEffect();

int AddTimeEffect(DWORD EffectCode, DWORD dwTime, int x, int y, int z);
int AddTimeEffect(DWORD EffectCode, DWORD dwTime, int x, int y, int z, smCHAR *lpChar);

int TimeEffectMain();



smCHAR *SelectRotPlayer(smCHAR *lpCurrentChar);

int	CloseRotPlayer();

smCHAR *InitRotPlayer();


int Check_PlaySubReleaseFunc();


int SetJobFace(char *szModelName);

int	CheckUserModel(smCHAR_INFO *lpCharInfo);


int	ResetInvenItemCode();

int SubInvenItemCode(sITEMINFO *lpItem);

int	CheckInvenItemCode();


void CheckPlaySubFunc2();




int	ResetEnergyGraph(int Num);

int CheckEnergyGraphError();

int CheckEnergyGraph();


sITEMINFO *FindInvenItem(DWORD dwItemCode, DWORD dwHead, DWORD dwChkSum);

int SendInvenItemError(DWORD dwKind, DWORD dwItemCode, DWORD dwHead, DWORD dwChkSum);

int SendUsingItemListToServer();

int SendUsingItemListToServer2();



int	ResetInvenMoney();

int	AddInvenMoney(int Money);

int	CheckInvenMoney();



int GetAttackSpeedMainFrame(int AttackSpeed);
int	GetAttackSpeedFrame(int AttackSpeed, int AddSpeed);
int	GetAttackSpeedFrame(int AttackSpeed);


extern int DispLoading;
extern int MessageLoading;


#define POTION_ETHERCORE		0x40

extern int	CodeXorExp;
extern int	CodeXorExp_High;
extern int	CodeXorLife;
extern int	CodeXorMana;
extern int	CodeXorStamina;
extern int	CodeXorMoney;



int GetItemKindFromBliankColor(smCHARTOOL	*lpCharTool);


extern char	szSOD_String[64];
extern BYTE	bSOD_StringColor[4];
extern int	SOD_StringCount;

extern sSOD_SCORE	sSodScore;
extern int		SoDGateFlag;

int	DisplaySodScore();
int	SodScoreMain();
int	Sod_SodEffect(int Round);


