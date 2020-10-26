
#define		SIN_MAX_EFFECT				1000	
#define		SIN_MAX_PROCESS				100		


#define		SIN_EFFECT_PARTICLE			0x01000000
#define		SIN_EFFECT_FACE2D			0x02000000
#define		SIN_EFFECT_OBJECT			0x03000000
#define		SIN_EFFECT_PATMESH			0x04000000


#define SIN_EFFECT_1					0x00000001
#define SIN_EFFECT_2					0x00000002
#define SIN_EFFECT_3					0x00000003
#define SIN_EFFECT_4					0x00000004
#define SIN_EFFECT_5					0x00000005
#define SIN_EFFECT_6					0x00000006
#define SIN_EFFECT_7					0x00000007
#define SIN_EFFECT_8					0x00000008
#define SIN_EFFECT_9					0x00000009
#define SIN_EFFECT_10					0x00000010



#define	sinEFFECT_MASK1	0xFF000000
#define	sinEFFECT_MASK2	0xFFFF0000
#define	sinEFFECT_MASK3	0x0000FFFF




#define		SIN_PARTICLE_SPOUT			(SIN_EFFECT_PARTICLE | SIN_EFFECT_1)		
#define		SIN_PARTICLE_GATHER			(SIN_EFFECT_PARTICLE | SIN_EFFECT_2)		
#define		SIN_PARTICLE_ROTATE_RISE	(SIN_EFFECT_PARTICLE | SIN_EFFECT_3)		
#define		SIN_PARTICLE_WIDE			(SIN_EFFECT_PARTICLE | SIN_EFFECT_4)		

#define		SIN_EFFECT_WIDE_LINE		(SIN_EFFECT_OBJECT | SIN_EFFECT_1)			
#define		SIN_EFFECT_RISE_LINE		(SIN_EFFECT_OBJECT | SIN_EFFECT_2)			


#define		SIN_PARTICLE_COLOR_GOLD		1		
#define		SIN_PARTICLE_COLOR_BLUE		2		
#define		SIN_PARTICLE_COLOR_RED		3		
#define		SIN_PARTICLE_COLOR_GREEN	4		


#define		SIN_EFFECT_TYPE_NORMAL		1		
#define		SIN_EFFECT_TYPE_FADEON		2		
#define		SIN_EFFECT_TYPE_EXPAND		3		
#define		SIN_EFFECT_TYPE_DECREASE	4		
#define		SIN_EFFECT_TYPE_FLICKER		5		
#define		SIN_EFFECT_TYPE_FADEOUT		6		


#define		SIN_EFFECT_DEAD				0		
#define		SIN_EFFECT_ALIVE			1		



struct sinEFFECT
{
	int			CODE;
	int			Color;
	int			State;

	smFACE2D	sinFace;

	POINT3D		MoveSpeed;
	POINT3D		MoveAngle;
	int			MoveGravity;

	POINT3D		ObjectPosi;
	int			ObjectMat;
	POINT3D		ObjectSize;


	int			FaceAngle;

	int			LifeTime;
	int			LifeTime_MAX;

	int			AniCount;
	int			ChangeSize;

	int			RotateRadian;
	int			RotateDistance;

	int			TypeSize;
	int			TypeFade;
	smPAT3D     *sinPatMesh;
	smOBJ3D		*sinObj;

	int			MeshFlag;

};

struct sinEFFECT_PROCESS
{
	int Kind;
	int Time;
	POINT3D	Posi;
	int Index[100];

};


struct sinEFFECT_ZDEPTH
{
	int		Index;
	int		ZDepth;

};


smFACE2D sinSetFace(int Mat, int x, int y, int z, int w, int h, int R, int G, int B, int A);


int sinStartEffect(int Name, int x, int y, int z);


int sinSetEffect(int CODE, int x, int y, int z, int Size, int Color = 0, int AngleY = 0);


int sinActiveEffect();


int sinEffectAni(sinEFFECT *pEffect);


int sinMoveEffect(sinEFFECT *pEffect);


int sinDrawEffect(int x, int y, int z, int ax, int ay, int az);


int sinBubbleSort(sinEFFECT_ZDEPTH *list, int num);


int sinEffectProcess();


int sinSetEffectProcess(int Kind, int x, int y, int z);


int sinCreateEffectObject(sinEFFECT *pEffect);


int sinGetMoveLocation(sinEFFECT *pEffect);


int EffectTestDrawText();


int TestObjectDraw(int x, int y, int z, int ax, int ay, int az);

int TestCreateEffectObject();

extern smTEXRECT sinTexRect;
extern sinEFFECT sinEffect[SIN_MAX_EFFECT];
extern sinEFFECT_ZDEPTH	sinEffect_ZDepth[SIN_MAX_EFFECT];
