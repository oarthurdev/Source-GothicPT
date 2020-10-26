

#define SIN_MAX_INTER_EFFECT		300

#define SIN_INTER_EFFECT_AGING				1		
#define SIN_INTER_EFFECT_AGING2				2		
#define SIN_INTER_EFFECT_AGING_SUCCESS		3		

struct sINTER_EFFECT
{
	smFACE2D Face;
	int Time;
	int Max_Time;
	POINT Speed;
	POINT Speed2;
	int Direction;
	int AniCount;
	int AniKeyFlag;
	int AniKeyFlag2;
	int FadeType;
	int Kind;
	int Gravity;



};

struct sINTER_EFFECT3
{
	DIRECTDRAWSURFACE lpSuccessEffectAging;
	int Flag;
	int x;
	int y;

	int w;
	int h;

	int MoveX;
	int MoveY;

	int MoveX2;
	int MoveY2;

	int Speed;


};



int sinSetParticle(int Kind, int Color, int x, int y, int z);




int InitInterEffect();


int SetInterEffectAging();


int SetInterEffectAging2();


int sinActiveInterEffect();


int sinDrawInterEffect();


int InterEffectAging2Process();


int sinSuccessCraftEffect();


int sinSuccessCraftEffect2();


int MoveSuccessCraftEffect2();


int DrawSuccessCraftEffect2();


int SetPuzzleEffect(int x, int y);


int SetInterEffectSmelting();


int SetInterEffectManufacture();

int SetInterEffectMixtureReset();


extern int   StartInterEffectAging2;
extern int   sinCraftItemStartFlag;
extern int   sinCraftItemStartFlag2;


extern int  sinAgingSuccessFlag2;
extern DWORD InitCancelMixTime;