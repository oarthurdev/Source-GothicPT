


#define SIN_EFFECT_RAGE_OF_SINBARAM			100	


#define SIN_RAND_1000000  (rand()%1000000) 
#define SIN_RAND_100000   (rand()%100000) 
#define SIN_RAND_10000    (rand()%10000) 
#define SIN_RAND_1000     (rand()%1000) 
#define SIN_RAND_100      (rand()%100) 
#define SIN_RAND_10       (rand()%10) 



class cSIN3D
{

public:
	int sinEffect2D_Line;
	int MatParticleRed[4];
	int MatParticleBlue[4];
	int MatParticleGreen[4];
	int	MatParticleGold[4];
	int	MatEffectLine;

	int MatParticle1;



	int	MatWideCircle;



	smPAT3D     *Rage_Of_SinBaRam;


public:

	cSIN3D();
	~cSIN3D();

	void Init();
	void Load();
	void Release();
	void Draw(int x, int y, int z, int ax, int ay, int az);
	void DrawText();
	void Close();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();



	int sinDrawTexture(int x, int y, int z, int AngleX, int AngleY, int AngleZ, smFACE2D *lpFace, int sinAngle);

};

extern cSIN3D cSin3D;
