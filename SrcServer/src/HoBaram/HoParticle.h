#ifndef _HO_PARTICLE_H_
#define _HO_PARTICLE_H_

#ifndef D3D_OVERLOADS
#define D3D_OVERLOADS
#endif



#define MAX_PARTICLES	200
#define RANDOM_NUM	(((FLOAT)rand()-(FLOAT)rand())/RAND_MAX)

#define MIN_SPEED		0.0f	
#define MIN_LIFETIME	0.1f	
#define MIN_SIZE		2.0f	

#define MIN_SPREAD		0.01f	
#define MIN_EMISSION	1.0f	
#define MIN_GRAVITY		-3.0f	
#define MIN_ALPHA		0.0f	

#define MAX_SPEED		500.0f	
#define MAX_LIFETIME	10.0f	
#define MAX_SIZE		20.0f	

#define MAX_SPREAD		180.0f	
#define MAX_EMISSION    1000.0f	
#define MAX_GRAVITY		3.0f	
#define MAX_ALPHA		255.0f	



#define Clamp(x, min, max)  x = (x<min  ? min : x<max ? x : max);

enum ParticleSystemType
{
	PS_FIRE,
	PS_DUST,
	PS_BLOOD
};

class HoParticleSystem;
class HoParticle
{
public:
	HoParticle();
	~HoParticle();
public:
	D3DVECTOR		PrevLocation;
	D3DVECTOR		Location;

	D3DVECTOR		Velocity;

	D3DCOLORVALUE	Color;
	D3DCOLORVALUE	ColorDelta;

	float			Age;
	float			LifeTime;

	float			Size;
	float			SizeDelta;

	float			Alpha;
	float			AlphaDelta;

	float			Gravity;
	float			GravityDelta;

	float			TimeCount;

	HoParticleSystem*	Parent;
	void			SetParent(HoParticleSystem* parent)
	{
		Parent = parent;
	}

public:
	bool Main();
};


class HoParticleSystem : public HoEffectObject
{
public:
	HoParticleSystem();
	virtual ~HoParticleSystem();

	void SetState(BOOL startFlag)
	{
		Age = -1.0f;
	}

	virtual int	  Main();
	virtual int	  Draw(int x, int y, int z, int ax, int ay, int az);
	virtual void  Init();
	int	  Start(int x, int y, int z, int matNum, int particleCode = 0);
	void		  GetLocation(D3DVECTOR& vLocation);
	void		  TranslateWorld(int x, int y, int z);




	int make_pSu;
	int ParticleCode;

public:



	BOOL		 AutoDieFlag;
	int			 MaterialNum;

	unsigned int ParticlesAlive;
	unsigned int ParticlesPerSec;

	D3DVECTOR	 PrevLocation;
	D3DVECTOR	 Location;

	D3DVECTOR	 Velocity;
	D3DVECTOR    Direction;


	float	GravityStart;
	float	GravityEnd;

	float	SizeStart;
	float	SizeEnd;

	float   AlphaStart;
	float	AlphaEnd;

	D3DCOLORVALUE	ColorStart;
	D3DCOLORVALUE	ColorEnd;


	float	Theta;
	float	Speed;
	float	Life;

	float	EmissionResidue;
	float	Age;

	float	TimeCount;
	HoParticle Particles[MAX_PARTICLES];
	smFACE2D			Face2d;
};


class HoParticleBow : public HoParticleSystem
{
public:
	HoParticleBow();
	~HoParticleBow();

	int Main();
	int Start(int x, int y, int z, int r, int g, int b, int a, int matNum);
	int StartFire(int x, int y, int z, int r, int g, int b, int a, int matNum);

};


class HoParticleTornado : public HoParticleSystem
{
public:
	int LocalAngle;
	HoParticleTornado();
	~HoParticleTornado();

	int Main();
	int Start(int originX, int originY, int originZ, int localX, int localY, int localZ, int matNum);
};




class HoParticleDest : public HoParticleSystem
{
public:
	int DestX, DestY, DestZ;
	int LocalAngle;
	BOOL EndWaveFlag;
	HoParticleDest();
	~HoParticleDest();

	int Main();
	void SetAge(float age)
	{
		Age = age;
	}
	int Start(int worldX, int worldY, int worldZ, int destX, int destY, int destZ, int matNum, int type);

};

class HoParticleSpark : public HoParticleSystem
{
public:
	HoParticleSpark();
	~HoParticleSpark();
	void  Init();

	int   Draw(int x, int y, int z, int ax, int ay, int az);

	bool AddFace2D(smFACE2D *face, int particleIndex);


	void Start(int x, int y, int z, int matNum, int type);

};



#endif