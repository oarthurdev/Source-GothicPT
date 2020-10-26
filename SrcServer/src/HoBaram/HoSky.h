#ifndef _HO_SKY_H_
#define _HO_SKY_H_

#include <vector>
#include <list>
#include <string>

#define		USER_SKY_ADD_CODE		10000						



struct skyResInfo
{
	std::string		resName;
	int				fadeSlowFlag;
	smPAT3D			*stageSky;

	int colorR, colorG, colorB, colorA;

	skyResInfo()
	{
		fadeSlowFlag = 0;
		stageSky = NULL;
		colorR = 255;
		colorG = 255;
		colorB = 255;
		colorA = 255;
	}
};



class HoSkyDrawInfo
{
public:
	int LightColorR;
	int LightColorG;
	int LightColorB;
	int	LightDark;
	int	LightDelay;

	bool	FogFlag;
	int		FogColorR;
	int		FogColorG;
	int		FogColorB;
	int		FogColorA;

	int		FogStartPos;
	int		FogEndPos;

	int		ChangeSkyNum;
	int		ChangeSkyTime;
	BOOL	ChangeNextSkyEnd;

	BOOL	ClippingFlag;
	std::vector<skyResInfo> SkyResInfoList;

	HoSkyDrawInfo()
	{
		LightColorR = 0;
		LightColorG = 0;
		LightColorB = 0;
		LightDark = 0;
		LightDelay = 300;

		FogFlag = false;
		FogColorR = 0;
		FogColorG = 0;
		FogColorB = 0;
		FogColorA = 0;

		FogStartPos = 50;
		FogEndPos = 5000;

		ClippingFlag = TRUE;
	}

	void	LoadRes();
	void	DestroyRes();

};

#define FIELD_BACKIMAGE_AURORA	0x200

class HoSky
{
private:
	std::vector <HoSkyDrawInfo>		    SkyDrawInfoList;

	int							CodeID;
	int							DrawIndex;
	int							DrawOldIndex;


	int							DrawAlphaCount;
	int							DrawOldAlphaCount;

	int							DrawNextAlphaCount;
	int							DrawNextOldAlphaCount;


	BOOL						DrawNextFlag;
	int							TimeCount;

	int							FogStartColorR;
	int							FogStartColorG;
	int							FogStartColorB;
	int							FogStartColorA;

	int							FogEndColorR;
	int							FogEndColorG;
	int							FogEndColorB;
	int							FogEndColorA;

	int							FogStartPos1;
	int							FogStartPos2;

	int							FogEndPos1;
	int							FogEndPos2;
	int							FieldStartColorDelay;


	int							BlinkTime;
	int							BlinkColor;
	BOOL						BlinkFlag;
	BOOL						BlinkDrawFlag;
	int							BlinkCount;
	int							ParticleCount;
	int							SnowParticleNum;
	BOOL						StartSnowFlag;
public:
	int							FieldColorR, FieldColorG, FieldColorB;
	BOOL						FirstSkyLoadFlag;
	BOOL						TestModeFlag;

private:
	void		ParticleEffectSpawn();

public:
	HoSky();
	~HoSky();

	int			Main();
	int			Draw(int x, int y, int z, int ax, int ay, int az);
	int			Draw(int x, int y, int z, int ax, int ay, int az, unsigned int index, int alphaCount = 100, int alphaNextCount = 100);

	void		Destroy();
	void		Create();

	void		LoadRes();


	void		DestroyRes();

	unsigned int	SetDrawIndex(unsigned int ID, int codeID);
	int				GetCodeID()
	{
		return CodeID;
	}
	void			SetCodeID(int code)
	{
		CodeID = code;
	}

	unsigned int	SetNextDrawIndex();
	void			Init();

	void			SetFieldColor(int r, int g, int b, int startDelay = 0)
	{
		FieldColorR = r;
		FieldColorG = g;
		FieldColorB = b;

		FieldStartColorDelay = startDelay;
	}

	int			GetDarkLight()
	{
		if(DrawIndex == -1)
			return 0;

		return SkyDrawInfoList[DrawIndex].LightDark;
	}
};


extern int InitSky();
extern int CreateSky();
extern int ReCreateSky();

extern int DrawOpeningSky(int x, int y, int z, int ax, int ay, int az);
extern int DrawSky(int x, int y, int z, int ax, int ay, int az);
extern int MainSky();
extern int ChangeSky(int id);
extern int SetNextSky();
extern int DestroySky();


#endif