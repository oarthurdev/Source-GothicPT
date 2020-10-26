
#define SIN_MAX_EFFECT2			1000

#define SIN_EFFECT_STUN			1
#define SIN_EFFECT_ICEVIGO		2
#define SIN_EFFECT_BOSSAURA		3
#define SIN_EFFECT_BOSSAURA2	4


#define SIN_EFFECT_NO_TIME		0xFFFF0000

#define SIN_EFFECT_FACE			1
#define SIN_EFFECT_MESH			2


class cSINEFFECT2
{

public:

	DWORD CODE;
	int   Time;
	int   Max_Time;
	int   Index;

public:


	POINT3D		Posi;
	POINT3D		Angle;
	POINT3D		AngleTemp;
	POINT3D		RanderAngle;
	POINT3D		SortPosi;
	int			FaceAngleY;
	POINT3D		DesPosi;
	int			AddHeight;


	int			Flag;
	smFACE2D	sinFace;
	smPAT3D     *sinPatMesh;
	smOBJ3D		*sinObj;
	int			ObjMat;


	int			AniCount;
	int			AniTime;
	int			AniMax;
	int			AniReverseNum;

	int			*lpMatAni;


	int			MoveKind;
	POINT3D		MoveSpeed;
	int			Gravity;
	int			DesSpeed;
	POINT3D		MoveAngle;
	int			MoveStartTime;


	POINT3D		RotateDistance;
	int			RotateSpeed;
	int			RotateSpeedCnt;
	POINT3D		RotatePosi;
	POINT3D		CharDistance;
	int			RotateAngle;


	POINT		Size;
	int			SizeIncreTime;
	int			SizeDecreTime;
	int			SizeAmount;
	int			ReSizingNum;
	int			ReSizingAmount;


	smCHAR		*pChar;
	smCHAR		*DesChar;
	POINT3D		CharPosi;
	POINT3D		DesCharPosi;


	int			Color_A;
	int			Color_R;
	int			Color_G;
	int			Color_B;

	int			AlphaCount;
	int			AlphaTime;
	int			AlphaAmount;

	int			AlphaReverse_A;
	int			AlphaReverseNum;

	int			AlphaFadeInFlag;


	int			ProcessCount;


	int			CopyFlag;

	int			ActionTime[10];
	int			BoneFlag;

	int			CrashCheckCount[3];
public:


};
extern POINT3D	sinPosi2;
extern POINT3D	sinAngle2;




int setBossMonsterEffect(smCHAR *pChar, int ProcessCount);


int setBossMonsterEffect2(POINT3D Posi);


int sinSetEffect_Stun(smCHAR *pChar, int Time);


int sinSetEffect_IceVigo(smCHAR *pChar, int Time);

int sinSetParticleRound(POINT3D Posi);

int sinSetParticleTail(POINT3D Posi);

int ParticleTestKey();

int sinHitParticle(int Mat, POINT3D Posi);

int sinTornadoParticle(int Mat, POINT3D Posi);

int sinSparkParticle(int Mat, POINT3D Posi);

int sinParticleLine(int Mat, POINT3D Posi, int R, int G, int B);

int sinGetMoveLocation2(cSINEFFECT2 *pEffect);

int sinSetLightEffect(int R, int G, int B, int A, POINT3D Posi);

int sinSongPyeunEffect(POINT3D Posi);




int InitEffect2();


int sinSearchEmptyIndex();


int sinDrawEffect2(int x, int y, int z, int ax, int ay, int az);


int sinDrawTexture2(cSINEFFECT2 *pSinEffect2);


int sinCreateObject(cSINEFFECT2 *pEffect);


int sinMoveEffect2(cSINEFFECT2 *pEffect);


int sinActiveEffect2();


int sinBubbleSort2(cSINEFFECT2 *list, int num);


int EffectTestDrawText2();


int sinCheckCharState(cSINEFFECT2 *pEffect);


int sinReleaseEffect();


int sinReSetObjPosi(cSINEFFECT2 *pEffect);


int sinEffectDefaultSet(int Index, int Kind, smCHAR *pChar = 0, POINT3D *pPosi = 0, int Y = 0);


int sinSetRotatePosiReSet(cSINEFFECT2 *pEffect);

int CheeseTestEffectImage();


extern cSINEFFECT2 cSinEffect2[SIN_MAX_EFFECT2];
extern sinEFFECT_ZDEPTH sinEffect_Zdepth2[SIN_MAX_EFFECT2];


int SetDynLight(int x, int y, int z, int r, int g, int b, int a, int power, int DecPower);


extern int Matstun;