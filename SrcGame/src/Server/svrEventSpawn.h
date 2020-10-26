

class	rsEVENT_SPAWN
{

public:
	DWORD		dwOpenTime;
	DWORD		dwEventPlayTime;
	DWORD		dwSpawnTime;
	DWORD		dwBossTime;
	int			EventFlag;
	int			EventCondition;
	STG_AREA	*lpStageArea;
	int			FieldCode;


	int Main();
	int	Order(rsPLAYINFO *lpPlayInfo, char *szText);
	int	Event_KillMonster(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar);
	int FindEnemyCount();
	int FindBossCount();
	int KillMonstersAll();
	int InitCoreMonster(sHCORE_MONSTER *hCoreMonster);
	int	OpenCoreMonster(smCHAR_INFO *lpCharInfo, int x, int z);
	int	OpenCoreMonsters(sHCORE_MONSTER *hCoreMonster, int x, int z, int range);
	int	OpenUserEffect(int FontEffectType, int x, int z, int range);

};



#define	rsEVENT_CODE_SPAWN_FLAG		0x200

extern rsEVENT_SPAWN	rsEventSpawn[STAGE_AREA_MAX];



int rsEventSpawn_KillMonster(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar);
int rsEventSpawn_Order(rsPLAYINFO *lpPlayInfo, char *szText);
int rsEventSpawn_Main(STG_AREA *lpStgArea);
