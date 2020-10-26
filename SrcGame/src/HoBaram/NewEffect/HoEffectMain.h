#ifndef _HO_EFFECT_MAIN_H_
#define _HO_EFFECT_MAIN_H_


#include "HoNewEffectHeader.h"
#include "HoEffectResMgr.h"
#include "Script\\PiScript.h"

#ifdef  _HO_NEW_WIN32_
extern "C"
{
   #include "Script\\Lua\\win32\\lua.h"
   #include "Script\\Lua\\win32\\lauxlib.h"
   #include "Script\\Lua\\win32\\lualib.h"
}
#endif

#include "HoEffectModel.h"
#include "HoEffectController.h"

class HoEffectMain
{
private:
	HoEffectGroup                    *m_EffectGroup;
    HoEffectModelControllerInterface *m_ModelController;
	int                               m_WorkTypeName;
	int								  m_SpecificWorkTypeName;
	
    PiScript						  m_PiScript;


public:
	HoEffectMain(); 
	~HoEffectMain(); 
	
	
	
    void    LuaBegin(const char *typeName, const char *parentMeshName = NULL);
    void    LuaEnd();
    void    LuaInitPos(float x, float y, float z);
    void    LuaInitColor(float r, float g, float b, float a);
    void    LuaInitMeshName(const char *meshName, const char *boneName);
    void    LuaInitTextureName(const char *textureName);
    void    LuaInitAniTextureName(const char *textureName, int textureCount, float aniDelayTime);

    void    LuaInitMaxFrame(float frame);
    void    LuaInitLoop(int loop);
    void    LuaInitStartDelayTime(float delayTime);
    void    LuaInitEndTime(float time);
    void    LuaInitEndTime(float x1, float x2);
    void    LuaInitSize(float x, float y);
    void    LuaInitSize(float x1, float x2, float y1, float y2);
    void    LuaInitBlendType(const char *type);

    void    LuaInitParticleNum(float particleNum);
    void    LuaInitEmitRate(float emitRate);
    void    LuaInitVelocity(float x1, float x2, float y1, float y2, float z1, float z2);

    void    LuaEventColor(float time, float r, float g, float b, float a);
    void    LuaEventSize(float time, float x, float y, float z);
    void    LuaEventFadeColor(float time, float r, float g, float b, float a);
    void    LuaEventFadeSize(float time, float x, float y, float z);

    void    LuaInitSpawnBoundingBox(float x1, float x2, float y1, float y2, float z1, float z2);
    void    LuaInitSpawnBoundingSphere(float x1, float x2);
    void    LuaInitSpawnBoundingDoughnut(float x1, float x2, float y1, float y2);

    void    LuaInitVelocityType(const char *typeName);
    void    LuaInitParticleType(const char *typeName);

    void    LuaInitAxialPos(float x1, float y1, float z1, float x2, float y2, float z2);

	void	Update(int x, int y, int z, int ax, int ay, int az);
	void	Main(float elapsed);
	HoEffectGroup *LoadScript(const char *str);
	HoEffectBillboardAxialController *LoadScriptAxial(const char *str);
};

extern HoEffectMain	MainWindow;
#endif
