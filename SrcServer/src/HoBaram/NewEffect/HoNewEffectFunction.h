#ifndef _HO_NEW_EFFECT_FUNCTION_H_
#define _HO_NEW_EFFECT_FUNCTION_H_

#include "smlib3d\\smd3d.h"
#include "smwsock.h"
#include "character.h"

void SkillMetalionImpulsionHit(smCHAR **pChar, int charCount);
void SkillMetalionCompulsion(smCHAR *pChar);
void SkillMetalionSphere(smCHAR *pChar, float time, float attackTime);
void SkillMetalionSphereDefence(POINT3D *curPos, POINT3D *desPos, bool flag = true);
void SkillMetalionGolem(smCHAR *pChar);

void SkillWarriorDestroyerBlade(smCHAR *pChar, float time);
void SkillWarriorDestroyerHit(POINT3D *pos);
void SkillWarriorBetserker(smCHAR *pChar, float time);
void SkillWarriorCycloneStrikeBlade(smCHAR *pChar, float time);

void SkillLancelotAssassinEye(smCHAR *pChar, float time);
void SkillLancelotChargingStrike(smCHAR *pChar);
void SkillLancelotVague(smCHAR *pChar);

void SkillSagittarionPhoneixShot(smCHAR *pChar, POINT3D *curPos, POINT3D *desPos);
void SkillSagittarionForceOfNature1(smCHAR *pChar, float time); 
void SkillSagittarionForceOfNature2(smCHAR *pChar, float time); 

void SkillSaintDivinePiercing(smCHAR *pChar);
void SkillSaintGodBless(smCHAR *pChar, float time);
void SkillSwordOfUstice(smCHAR *pChar);

void SkillValhallaHallOfValhalla1(smCHAR *pChar);
void SkillValhallaXRage(POINT3D *curPos, POINT3D *desPos);
void SkillFrostJavelin(POINT3D *curPos, POINT3D *desPos);
void SkillForstJavelinAttach(smCHAR *pChar, float time);
void SkillVengeance(POINT3D *curPos, POINT3D *desPos);

void SkillCelestialGlacialSpike(smCHAR *pChar);
void SkillCelestialRegnerationField(smCHAR *pChar, float time);
void SkillCelestialMusPel(smCHAR* pChar, float time, float attackTime);
void CelestialChainLighting(smCHAR **pChar, int count);
void SkillArchMageMeteo(POINT3D *desPos);
void SkillArchMageFireElementalHand(smCHAR *pChar);
void SkillArchMageFireElementalShot(POINT3D *curPos, POINT3D *desPos);

BOOL GetAssaCodeEffect(smCHAR *pChar, int code);


void Valento_PowerUp(smCHAR *pChar);
void Valento_Justice(smCHAR *pChar);

void ParkIncubusSummonerSkill(smCHAR *pChar);
void DevilBird_Skill(smCHAR *pChar);
#endif