







#include ".\PiScript.h"
#include ".\PiScriptLuaCommand.h"

#include "..\\HoNewEffectHeader.h"
#ifndef _HO_NEW_WIN32_
#include "..\\..\\MainWnd.h"
#endif

#ifdef _HO_NEW_WIN32_
#include "..\\HoEffectMain.h"
#endif




int luaCommand_Begin(lua_State *pLuaState)
{
	return TRUE;
}

int luaCommand_End(lua_State *pLuaState)
{
	return TRUE;
}

int luaCommand_InitPos(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitMeshName(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitMaxFrame(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitStartDelayTime(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitLoop(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitTextureName(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitAniTextureName(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitColor(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_EventColor(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_EventSize(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_EventFadeColor(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_EventFadeSize(lua_State *pLuaState){
	return TRUE;
}


int luaCommand_InitEndTime(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitSize(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitBlendType(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitSpawnBoundingBox(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitSpawnBoundingSphere(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitSpawnBoundingDoughnut(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitParticleNum(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitEmitRate(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitAxialPos(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitVelocity(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitParticleType(lua_State *pLuaState){
	return TRUE;
}

int luaCommand_InitVelocityType(lua_State *pLuaState){
	return TRUE;
}



