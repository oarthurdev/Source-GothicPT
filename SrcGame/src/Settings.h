class cSettings
{
public:
	static cSettings * GetInstance() { static cSettings instance; return &instance; };
	BOOL   IsOpen() { return cOpen; }
	bool   IsWideScreen() { return ((smScreenWidth / 4) != (smScreenHeight / 3)); }
	bool   MouseAction(int x, int y, int w, int h);
	int    cImages[45];
	void   Init();
	void   Open();
	void   Close();
	void   Draw();
	void   Button();
	void   Load();
	void   Save();
	void   Reset();
	void   Set(int Windowed, int Width, int Height);
	int    bWindowed, cWindowed;
	int    bTraje, cTraje;
	int    bAutoAdjust, cAutoAdjust;
	int    bRatio, cRatio;
	int    bResolution, cResolution;
	int    bTexture, cTexture;
	int    bBPP, cBPP;
	int    bEffects, cEffects;
	int    bLights, cLights;
	int    bShadows, cShadows;
	int    bMusic, cMusic;
	int    bMVol, cMVol;
	int    bSound, cSound;
	int    bAmbient, cAmbient;
	int    bSVol, cSVol;
	int    bCamView, cCamView;
	int    bCamRange, cCamRange;
	int    bCamShake, cCamShake;
	int    bCamInv, cCamInv;
	int    bFilter, cFilter;
	int    bFilterSpec, cFilterSpec;
	int    bHP, cHP;
	int    bMP, cMP;
	int    bSP, cSP;
	int    bGold, cGold;
	int    bAmulets, cAmulets;
	int    bRings, cRings;
	int    bSheltoms, cSheltoms;
	int    bForce, cForce;
	int    bPremiums, cPremiums;
	int    bCrystal, cCrystal;
	int    bDefItem, cDefItem;
	int    bOffItem, cOffItem;
	int    bElse, cElse;
	int    bMS, cMS;
	int    bFS, cFS;
	int    bPS, cPS;
	int    bAS, cAS;
	int    bKS, cKS;
	int    bATS, cATS;
	int    bPRS, cPRS;
	int    bMGS, cMGS;
	int    bASS, cASS;
	int    bSH, cSH;
	int    bNaked, cNaked;
	int    bPort, cPort;
	int    bMotionBlur, cMotionBlur;
	int    bWeather, cWeather;
	int    bNetwork, cNetwork;
	char  Server1[32], Server2[32],  Server3[32];
	

private:
	bool   cOpen;
	int    Tab;
};
