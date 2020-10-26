#ifndef _HO_NEW_PARTICLE_MGR_
#define _H0_NEW_PARTICLE_MGR_

#include <vector>
#include <string>


using namespace std;

struct HoNewParticleMatRes
{
	int     matNum;
	string  matName;
};

#define MAX_TOKEN_VECTORS   500
#define MAX_MATERIAL        300
#define MAX_EMITTER         300

class HoNewParticleScriptRes
{
public:
	string name;

	HoNewParticleEmitterTokenizer emitterTokenizer;
};


class HoNewParticleResMgr
{
public:
	HoNewParticleResMgr()
	{
		init();
	}

	~HoNewParticleResMgr()
	{

	}

private:

	int NumScriptRes;
	std::vector<HoNewParticleScriptRes> ScriptRes;

	int NumMaterial;
	std::vector<HoNewParticleMatRes > MatRes;

public:
	void init();

	bool LoadScript(char *scr);
	HoNewParticleScriptRes *AddScript(char *scr, char *indexName = "test");
	HoNewParticleScriptRes *FindScript(char *find);

	int AddTexture(const char *mat);
	int SearchingAddTexture(const char *directory);
};

class HoNewParticleMgr
{
public:
	HoNewParticleMgr()
	{
		NumEmitters = 0;
		Emitters.clear();
		Emitters.reserve(MAX_EMITTER);
		Running = false;

	}

	~HoNewParticleMgr()
	{
		NumEmitters = 0;
		Destroy();
	}

private:
	int     NumEmitters;
	std::vector<HoNewParticleEmitter> Emitters;

public:
	void	Init();
	bool    Running;
	void    Clear();

	void    Destroy();



	void    Main(float elapsedTime, float timeDelta);
	void    Draw(int x, int y, int z, int ax, int ay, int az);
	bool    IsRunning()
	{
		return Running;
	}

	int     Start(HoNewParticleScriptRes *scriptRes, POINT3D pos, float startDelay = 0.f);
	int     Start(char *fileName, POINT3D pos, float startDelay = 0.f);

	void    SetPos(int partID, D3DXVECTOR3 pos);
	void    SetAttachPos(int partID, D3DXVECTOR3 pos);
	void    SetStop(int partID);
	void    SetFastStop(int partID);
	void	SetAngle(int partID, POINT3D angle);

	bool	GetRunning(int partID);
	void    SetRendering(int partID, BOOL flag);



};



extern HoNewParticleResMgr  g_NewParticleResMgr;
extern HoNewParticleMgr     g_NewParticleMgr;

#endif
