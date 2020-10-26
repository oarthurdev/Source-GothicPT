







#ifndef _PI_SCRIPT_
#define _PI_SCRIPT_
#pragma once

#include "..\\HoNewEffectHeader.h"
#ifndef _HO_NEW_WIN32_
extern "C"
{
#include "Lua\\src\\lua.h"
#include "Lua\\src\\lauxlib.h"
#include "Lua\\src\\lualib.h"
}
#endif

#ifdef  _HO_NEW_WIN32_
extern "C"
{
#include "Lua\\lua.h"
#include "Lua\\lauxlib.h"
#include "Lua\\lualib.h"
}
#endif

class PiScript
{
public:
	PiScript(void);
	~PiScript(void);

private:
	lua_State *m_pLuaState;
private:
	void RegisterCommand(lua_State *state);
	void RegisterFunction(lua_CFunction fn, const char* name);

public:
	bool RunScriptFile(const char *fileName);
	bool RunScriptBuffer(const char *buffer);
};

#endif
