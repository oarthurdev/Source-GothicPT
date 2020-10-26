








#ifndef _LUA_COMMAND_
#define _LUA_COMMAND_

int luaCommand_Begin                ( lua_State *pLuaState);
int luaCommand_End                  ( lua_State *pLuaState);
int luaCommand_InitColor            ( lua_State *pLuaState);
int luaCommand_InitSize             ( lua_State *pLuaState);

int luaCommand_InitPos              ( lua_State *pLuaState);
int luaCommand_InitStartDelayTime   ( lua_State *pLuaState);

int luaCommand_InitTextureName      ( lua_State *pLuaState);
int luaCommand_InitAniTextureName   ( lua_State *pLuaState);
int luaCommand_InitEndTime          ( lua_State *pLuaState);

int luaCommand_InitMeshName         ( lua_State *pLuaState);
int luaCommand_InitMaxFrame         ( lua_State *pLuaState);
int luaCommand_InitLoop             ( lua_State *pLuaState);

int luaCommand_InitAxialPos         ( lua_State *pLuaState);

int luaCommand_InitSpawnBoundingBox      ( lua_State *pLuaState);
int luaCommand_InitSpawnBoundingSphere   ( lua_State *pLuaState);
int luaCommand_InitSpawnBoundingDoughnut ( lua_State *pLuaState);

int luaCommand_InitParticleType     ( lua_State *pLuaState);
int luaCommand_InitVelocityType     ( lua_State *pLuaState);

int luaCommand_InitVelocity         ( lua_State *pLuaState);
int luaCommand_InitParticleNum      ( lua_State *pLuaState);
int luaCommand_InitEmitRate         ( lua_State *pLuaState);
int luaCommand_InitBlendType        ( lua_State *pLuaState);

int luaCommand_EventColor           ( lua_State *pLuaState);
int luaCommand_EventSize            ( lua_State *pLuaState);
int luaCommand_EventFadeColor       ( lua_State *pLuaState);
int luaCommand_EventFadeSize        ( lua_State *pLuaState);
#endif
