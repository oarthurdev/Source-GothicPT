#ifndef _HO_ASSA_PARTICLE_EFFECT_
#define _HO_ASSA_PARTICLE_EFFECT_





int		GetAssaEffect();
int		StopAssaCodeEffect(smCHAR *pChar, int code, int setTime = 0);

bool	AddAssaCodeEffectTime(smCHAR *pChar, int code, int time);

BOOL	GetAssaUseEffect(smCHAR *pChar, int code);
bool	GetAssaContinueSkill(int skillCode);

extern int AssaParticle_LineIn(POINT3D *pPosi, char *texName = NULL, int continueTime = 15, int speed = 0);
extern int AssaParticle_LineOut(POINT3D *pPosi, char *texName = NULL, int continueTime = 10, int speed = 0);
extern int AssaParticle_Star(POINT3D *pPosi);


extern int AssaParticle_HolyValor_Jang(smCHAR *pChar, int maxTime = 0);
extern int AssaParticle_HolyValor_Member(smCHAR *pChar, int maxTime = 0);


extern int AssaParticle_DrasticSpirit_Jang(smCHAR *pChar, int maxTime = 0);
extern int AssaParticle_DrasticSpirit_Member(smCHAR *pChar, int maxTime = 0);


extern int AssaParticle_Windy(smCHAR *pChar, int maxTime = 0);
extern int AssaParticle_TwistJavelinShot(POINT3D *pPosi, POINT3D *pDesti);
extern int AssaParticle_FireJavelin(POINT3D *pPosi, POINT3D *pDesti);
extern int AssaParticle_FireJavelin(smCHAR *pChar, POINT3D *pDesti);




extern int AssaParticle_DivineLighting(smCHAR *pChar);
extern int AssaParticle_Sprak(POINT3D *pPosi);


extern int AssaParticle_ColumnOfWater(POINT3D *pPosi, POINT3D *pDesti, int level = 1);
extern int AssaParticle_ColumnOfWaterHit(POINT3D *pPosi);

extern int AssaParticle_EnchantWeaponIceJang(smCHAR *pChar, int maxTime = 0);
extern int AssaParticle_EnchantWeaponFireJang(smCHAR *pChar, int maxTime = 0);
extern int AssaParticle_EnchantWeaponLightJang(smCHAR *pChar, int maxTime = 0);


extern int AssaParticle_EnchantWeaponJinMember(smCHAR *pChar);
extern int AssaParticle_EnchantWeaponIceMember(smCHAR *pChar, int maxTime = 0);
extern int AssaParticle_EnchantWeaponFireMember(smCHAR *pChar, int maxTime = 0);
extern int AssaParticle_EnchantWeaponLightMember(smCHAR *pChar, int maxTime = 0);

extern int AssaParticle_LightShot(POINT3D *pPosi, POINT3D *pDesti);
extern int AssaParticle_FireShot(POINT3D *pPosi, POINT3D *pDesti);
extern int AssaParticle_IceShot(POINT3D *pPosi, POINT3D *pDesti);

extern int AssaParticle_LightHit1(POINT3D *pPosi);
extern int AssaParticle_IceHit1(POINT3D *pPosi);
extern int AssaParticle_FireHit1(POINT3D *pPosi);
extern int AssaParticle_FireHit2(POINT3D *pPosi);

extern int AssaParticle_BigFireHit1(POINT3D *pPosi);

extern int AssaParticle_DeadLay(POINT3D *pPosi, POINT3D *pDesti);
extern int AssaParticle_ShootingEffect2(POINT3D *pPosi, POINT3D *pDesti);
extern int AssaParticle_HolyMind_Attack(smCHAR *pChar, int liveCount);



extern int StartEffect_Serqbus_Skill1(smCHAR *pChar, int liveCount);
extern int StartEffect_Serqbus_Skill2(smCHAR *pChar, int liveCount);
extern int StartEffect_Serqbus_Skill3(smCHAR *pChar, int liveCount);


int AssaParticle_Fury_Eye(smCHAR *pChar);
int AssaParticle_Fury_ShotFire(smCHAR *pChar, POINT3D *destPos);

int AssaParticle_Fury_RespawnMonster(POINT3D *pPosi);
int AssaParticle_Fury_RespawnBody(smCHAR *pChar);
int AssaParticle_Fury_Skill1(smCHAR *pChar);

int AssaParticle_Fury_Skill1(POINT3D *pPosi, POINT3D *pAngle);


int AssaParticle_EvilMapleShot(smCHAR *pChar);


int AssaParticle_EvilPlantShot(smCHAR *pChar);


int AssaParticle_ThornCrawlerShot(smCHAR *pChar, POINT3D *destPos);


int AssaParticle_StoneGolemShot(smCHAR *pChar);



int AssaParticle_HeavyGoblinHit1(smCHAR *pChar);
int AssaParticle_HeavyGoblinHit2(smCHAR *pChar);


int AssaParticle_DoomGuardHit1(smCHAR *pChar);
int AssaParticle_DoomGuardHit2(smCHAR *pChar);


int AssaParticle_SnailShot(smCHAR *pChar, POINT3D *destPos);


int AssaParticle_NightMare(smCHAR *pChar);


int AssaParticle_RatooHit1(smCHAR *pChar);


int AssaParticle_Hit1(POINT3D *destPos);



int AssaParticleSpiderSkill1(smCHAR *pChar);


void AssaParticle_CastleRed(smCHAR *pChar);
void AssaParticle_CastleGreen(smCHAR *pChar);
void AssaParticle_CastleBlue(smCHAR *pChar);

void AssaParticle_KeepSkillEffect(char *FileName, smCHAR *pChar, int liveCount, unsigned int dwSkillCode);
void AssaParticle_ShootingEffect(smCHAR *pCurChar, smCHAR *pDestChar, unsigned int dwSkillCode);

int AssaParticleClanMonster(smCHAR *pChar);
int AssaParticleClanMonsterHit1(smCHAR *pChar);
int AssaParticleClanMonsterHit2(smCHAR *pChar);
int AssaParticle_Sprak1(POINT3D *pPosi);



void AssaParticle_Concentration(smCHAR *pChar, int liveCount);
void AssaParticle_SwiftAxe(smCHAR *pChar, int liveCount);
void AssaParticle_AvangingCrash(smCHAR* pChar);
void AssaParticle_BoneSmash1(smCHAR* pChar);
void AssaParticle_BoneSmash2(smCHAR* pChar);


void AssaParticle_VeonmSpear(smCHAR *pDest);
void AssaParticle_VeonmSpearPike(smCHAR *pChar);
void AssaParticle_Vanish(smCHAR *pChar);
void AssaParticle_ChainLance(POINT3D *pPosi);



void AssaParticle_ElementalShotFire(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_ElementalShotLighting(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_GoldenFalcon(smCHAR *pChar, int liveCount);
void AssaParticle_BombHit1(POINT3D *pPosi);
void AssaParticle_BombShot(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_Perforation(POINT3D* pCur, POINT3D* Dest);
void AssaParticle_PerforationHit(smCHAR* monster, smCHAR* character, float delay = 0.f);



void AssaParticle_MetalArmor(smCHAR *pChar, int liveCount);

void AssaParticle_GrandSmash(smCHAR *pChar);
void AssaParticle_SparkShieldStart(smCHAR* pChar, int liveCount);
void AssaParticle_SparkShieldDefence(POINT3D *pPosi, POINT3D *pDesti);



void AssaParticle_EnergyShield(smCHAR *pChar, int liveCount);
void AssaParticle_EnergyShieldDefence(smCHAR *pChar);
void AssaParticle_Diastrophism(smCHAR *pChar);
void AssaParticle_DiastrophismPart(smCHAR *pChar);
void AssaParticle_SpiritElemental(smCHAR *pChar, int liveCount);

void AssaParticle_DancingSwordFire(smCHAR *pChar, int liveCount, int level);
void AssaParticle_DancingSwordIce(smCHAR *pChar, int liveCount, int level);


void AssaParticle_FlameBrandish(smCHAR *pChar);
void AssaParticle_FlameBrandishHit1(smCHAR *pChar);
void AssaParticle_HolyIncantationShot(smCHAR* pDestChar);
void AssaParticle_HolyIncantationPart(smCHAR* pDestChar, int liveCount);
void AssaParticle_HolyIncantationHand(smCHAR* pDestChar);

void AssaParticle_GrandCrossHorz(POINT3D* pPosi, int angleY);
void AssaParticle_GrandCrossVert(POINT3D* pPosi, int angleY);
void AssaParticle_DivineInhalationStart(smCHAR* pChar, int liveCount);
void AssaParticle_DivineInhalationPart(smCHAR* pChar, int liveCount);
void AssaParticle_DivineInhalationDefence(POINT3D *pDest);
void AssaParticle_SoulBreaker(POINT3D* pPosi, int angleY);



void AssaParticle_SplitJavelin(POINT3D* pCur, POINT3D* pDest, int count = 2);
void AssaParticle_TriumphOfValhalla(smCHAR *pDestChar, int liveCount);
void AssaParticle_TriumphOfValhallaMember(smCHAR *pCurChar, smCHAR *pDestChar, int liveCount);
void AssaParticle_LightingJavelin(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_StormJavelin(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_StormJavelinHit(smCHAR* monster, smCHAR* character, float delay = 0.f);



void AssaParticle_VigorBall(smCHAR* pCurChar, smCHAR* pDestChar);
void AssaParticle_ResurrectionShot(smCHAR* pDestChar);
void AssaParticle_ResurrectionPart(smCHAR* pDestChar);
void AssaParticle_Extinction(smCHAR* pDestChar);
void AssaParticle_VirtualLife(smCHAR* pDestChar, int liveCount);




void AssaParticle_MonsterPigonHand(smCHAR* pChar);


void AssaParticle_ClassUpWeapon(smCHAR* pChar);
void AssaParticle_StopClassUpWeapon(smCHAR* pChar);
void AssaParticle_AgingBody(smCHAR* pChar, int num);


void AssaParticle_MonsterExplision(POINT3D *pPosi);
void AssaParticle_MonsterIronSadNessHit1(smCHAR *pChar);
void AssaParticle_MonsterIronSadNessSkill1(smCHAR *pChar);
void AssaParticle_MonsterIronHyperHit1(smCHAR *pChar, POINT3D *pDest);
void AssaParticle_MonsterIronHyperSkill1(smCHAR *pChar, POINT3D *pDest);

void AssaParticle_MonsterIronChainGolem(smCHAR *pChar);
void AssaParticle_MonsterIronRunicGuardian(smCHAR *pChar, smCHAR *pDestChar);
void AssaParticle_MonsterIronMountainHit1(smCHAR *pChar);
void AssaParticle_MonsterIronMountainSkill1(smCHAR *pChar);
void AssaParticle_MonsterIronTowerGolemHit1(smCHAR *pChar);
void AssaParticle_MonsterIronTowerGolemSkill1(smCHAR *pChar);
void AssaParticle_MonsterIronHit1(POINT3D *pPosi);

void AssaParticle_MonsterIronOmuHit1(smCHAR *pChar);
void AssaParticle_MonsterIronFist(smCHAR *pChar);
void AssaParticle_MonsterIronMorgonHit(smCHAR *pChar);
void AssaParticle_MonsterAvelArcher(smCHAR *pChar, smCHAR *pDestChar);
void AssaParticle_MonsterAvelQueen(smCHAR *pChar, smCHAR *pDestChar);
void AssaParticle_MonsterDeadZoneDead(smCHAR *pChar);
void AssaParticle_MonsterHyperDead(smCHAR *pChar);

void AssaParticle_MonsterRunicGuardianHand(smCHAR *pChar);
void AssaParticle_MonsterRunicGuardianShot(smCHAR *pChar, smCHAR *pDestChar);
void AssaParticle_MonsterRunicGuardianBossLightShot(smCHAR **pCharList, int charCount);

void AssaParticle_MonsterRunicGuardianBossShot(smCHAR *pChar, int blendType = SMMAT_BLEND_INVSHADOW);
void AssaParticle_MonsterRunicGrardianBossSkill(smCHAR *pChar);
void AssaParticle_MonsterRunicGuardianBossSkillHit(POINT3D *pDest);
void AssaParticle_MonsterRunicGuardianBossWeapon(smCHAR *pChar);
void AssaParticle_MonsterRunicGuardianBossHit(smCHAR *pCurChar, smCHAR *pDestChar, smCHAR **charList = 0, int charCount = 0);

void AssaParticle_ShelltomShot(POINT3D *pPosi, POINT3D *pDest, int type = 0);
void AssaParticle_BamShot(POINT3D *pPosi, POINT3D *pDest);

void AssaParticle_ShelltomWeapon(smCHAR *pChar, int time, int code);
void AssaParticle_ShelltomWeaponHit(POINT3D *pPosi);


void AssaParticle_TerrainShowStart();
void AssaParticle_TerrainFire(POINT3D *pCur, POINT3D *pDest, int delay = 0);
void AssaParticle_TerrainFireHit(POINT3D *pCur);

void AssaMonsterHitTest(smCHAR *pChar);


void SkillSaintGodlyShield(smCHAR *pChar, float time);
void SkillArchMageFlameWave(smCHAR *pChar);
void SkillCelestialChainLighting(smCHAR **pCharList, int charCount);
void SkillValhallaHallOfValhallaHandEffect(smCHAR *pChar, float time);
void SkillImpulsionLight(smCHAR *pChar, float time);
void SkillImpulsionLightHit(POINT3D *pos);
void SkillShadowMasterHit(POINT3D *pos);
void SkillPhoenixShotFlame(smCHAR *pChar, POINT3D *curPos);
void SkillGodBless(smCHAR *pChar);
void SkillParticle_FrostJavelin(smCHAR *pChar, float time);

void AssaMotionBlur(smCHAR *pChar, char *meshName1, char *meshName2, int timeCount);





int ParkAssaParticle_ColdEye(POINT3D *pPosi, POINT3D *pDesti);

int ParkParticle_ColdEyeSkill(smCHAR *pChar);

int ParkAssaParticle_MisticSpinel(smCHAR *pChar);

int ParkAssaParticle_AcientDia(smCHAR *pChar);

int ParksinSkillEffect_AcientPiercing(smCHAR *pChar);
int ParksinSkillEffect_AcientPiercingAtt(smCHAR *pChar);


int ParkAssaParticle_IceGolemShot(smCHAR *pChar);

int ParkAssaParticle_MistIceBolt(smCHAR* pCurChar, smCHAR* pDestChar);

int ParkAssaParticle_MistIceBall(smCHAR* pCurChar, smCHAR* pDestChar);


int ParkAssaParticle_IceGoblinHit1(smCHAR *pChar);


int ParkAssaParticle_Valento1(smCHAR* pValento);
int ParkAssaParticle_Valento2_1(smCHAR* pValento);
int ParkAssaParticle_Valento2_2(smCHAR* pValento);
int ParkAssaParticle_Valento3_1(smCHAR* pValento);
void ParkAssaParticle_MonsterIceValentoBody(smCHAR *pValento);
void ParkValentSwordShow(smCHAR* pValento, int nTime);

int ParkAssaParticle_ChaosKara1(smCHAR* pChar);
int ParkAssaParticle_ChaosKara2(smCHAR* pChar);
int ParkAssaParticle_ChaosKaraSkill_Monster(smCHAR* pMonster);
int ParkAssaParticle_ChaosKaraSkill_User(smCHAR* pUser);
void ParkAssaParticle_MonsterIceChaosKara(smCHAR *pChar);




void ParkAssaParticle_SpiderTrooperHit1(smCHAR *pChar);

void ParkAssaParticle_StingRay(smCHAR *pChar);
int ParkDivineLight_Effect(smCHAR *lpChar);
int ParkAssaParticle_DivineLighting(smCHAR *pChar);
int ParkAssaParticle_Sprak1(POINT3D *pPosi);
int ParkAssaParticle_Posion(smCHAR *pChar, int liveCount);
void ParkAssaParticle_MummyShot(smCHAR *pChar, smCHAR *pDestChar);
#define STINGRAY_POSION_TIME	5

void ParkBlizzardGiantSkillToTarget(smCHAR *pTarget);

void ParkDevilBirdAttackBlur(smCHAR* pDevilBird);
void ParkDevilBirdAttackNormal(smCHAR *pTarget);
void ParkDevilBirdSkillToTarget(smCHAR *pTarget);

void ParkAssaParticle_MonsterTurtleCanonNormal(smCHAR *pTCanon, smCHAR* pTarget);

void ParkAssaParticle_FireCracker(smCHAR *pChar, int nFireCracker);



DWORD GetTableNum(int n);


DWORD Park_VarEncode(int a, int b, int c, int d);


void Park_VarDecode(DWORD dwData, int &nData1, int &nData2, int &nData3, int &nData4);


void ParkKelvezuHit(smCHAR *pChar);
void ParkKelvezuSkillHit(smCHAR *pChar);
void ParkKelvezuNormal1(smCHAR *pChar);
void ParkKelvezuNormal2(smCHAR *pKelvezu);
void ParkKelvezuSkill1(smCHAR *pKelvezu);
void ParkKelvezuSkill2(smCHAR *pKelvezu);
void ParkKelvezuJin(smCHAR *pKelvezu);


void ParkKelvezuFingerShow(smCHAR* pKelvezu, int nTime);


void ParkKelvezuWingShow(smCHAR* pKelvezu, int nTime);


void ParkKelvezuTaleShow(smCHAR* pKelvezu, int nTime);


void ParkAssaParticle_WorldCupMonsterAttack(smCHAR* pMonster, smCHAR *pChar);

void ParkWorldCupMonsterHit(smCHAR *pChar);




void ParkAssaParticle_DarkPhalanx(smCHAR *pDarkPhalanx);


void ParkAssaParticle_TerrainFireHit(POINT3D *pCur, int nType);
void ParkAssaParticle_TerrainFire(POINT3D *pCur, POINT3D *pDest, int delay = 0, int nType = 0);
void ParkAssaParticle_FireWorm(smCHAR* pTarget, BOOL bSkill = FALSE);


void ParkAssaParticle_ChimeraNormal(smCHAR *pChimera);


void ParkAssaParticle_ChimeraSkill(smCHAR *pChar);


void ParkAssaParticle_BloodySkill(smCHAR *pBloodKnight);


void ParkAssaParticle_BloodySkillStun(smCHAR *pChar);


void ParkAssaParticle_HellHoundNormal(smCHAR *pChar);


void ParkAssaParticle_HellHoundSkillAttack(smCHAR *pHellHound);


void ParkAssaParticle_HellHoundSkillTaget(smCHAR *pChar);


void ParkAssaParticle_DarkGuardTaget(smCHAR *pChar);


void ParkAssaParticle_DarkGuardSkill(smCHAR *pDarkGuard, smCHAR *pChar);


void ParkAssaParticle_DarkMageNormal(smCHAR *pDarkMage, smCHAR *pChar);


void ParkAssaParticle_DarkMageSkill(smCHAR *pChar);


void ParkAssaParticle_DarkMageDead(smCHAR *pDarkMage);




void AssaParticle_AttackSkillEffect(char *FileName, smCHAR *pChar, DWORD dwSkillCode);

#endif
