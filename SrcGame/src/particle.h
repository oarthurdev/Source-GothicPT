#define PARTICLE_MAX	500


#define SMPARTICLETYPE_SHINE1		0x0001
#define SMPARTICLETYPE_BLOOD1		0x0010
#define SMPARTICLETYPE_BLOOD2		0x0011


int InitParticle();

int SetParticle(int x, int y, int z, int MatNum, int Type, int Param = 0);

int PlayParticle();

int DrawParticle(int x, int y, int z, int ax, int ay, int az);



int InitDynLight();

int CloseDynLight();

int SetDynLight(int x, int y, int z, int r, int g, int b, int a, int power, int DecPower = 10);

int DynLightApply();

int DynLightMain();
