

int sinPublicEffectTestKey();


void sinInitPublicEffect();
void sinPublicEffectMove(cSINEFFECT2 *pEffect);


int sinEffect_WideLine(POINT3D *pPosi, int Mat, int Lenght, int Num);
int sinEffect_WideParticle_Bone(POINT3D *pPosi, int Mat, int Size, int Time, int Num, int Speed);
int sinEffect_WideParticle(POINT3D *pPosi, int Mat, int Size);
int sinEffect_BombParticle(POINT3D *pPosi, int Mat, int Size, int Num);
int sinEffect_Light5(POINT3D *pPosi, int Size);
int sinEffect_SpoutParticle(POINT3D *pPosi, int Mat, int Num, int Size, int Time, int Gravity);
int sinEffect_GatherLine(smCHAR *pChar, int Mat, int Time);
int sinEffect_GatherLine2(smCHAR *pChar, int Mat);
int sinEffect_WideContinueLine(smCHAR *pChar, int Mat, int Time, int Height);
int sinEffect_WideContinueLine2(POINT3D *pPosi, int Mat);
int sinEffect_GatherCircleParticle(POINT3D *pPosi, int Mat);
int sinEffect_Hit2(POINT3D *pPosi, int Mat);



int sinEffect_Sen(POINT3D *pPosi);
int sinEffect_Sen_Particle(POINT3D *pPosi);
int sinEffect_MutentTree_Smoke(POINT3D *pPosi);
int sinEffect_MutentTree_Smoke_Particle(POINT3D *pPosi);
int sinEffect_MutentTree_Attack(smCHAR *pChar, smCHAR *desChar);
int sinEffect_MutentTree_Attack_Particle(POINT3D *pPosi);
int sinEffect_MutentTree_Attack_Particle2(POINT3D *pPosi);
int sinEffect_MutentTree_Hit_Particle(POINT3D *pPosi);
int sinEffect_MutentTree_Fire(POINT3D *pPosi);
int sinEffect_MutentTree_Fire_Particle(POINT3D *pPosi);
int sinEffect_Ratoo(smCHAR *pChar);
int sinEffect_Ratoo_Vigor(smCHAR *pChar);
int sinEffect_Ratoo_Vigor_Partilce(POINT3D *pPosi);