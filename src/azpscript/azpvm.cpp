/*  	Azpazeta - Sandbox strategy game
    	Copyright (C) 2013  Adrián Arroyo Calle
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/* AzpVM - Azpazeta Virtual Machine */
#include "azpvm.hpp"
#include <iostream>
#include "wx/utils.h"
#include "../version.hpp"
#include "azpapi.hpp"

AZPVM::AZPVM(wxString file, AZPVMState state)
{
	//Check files and state DONE
	#if LUA_VERSION_NUM < 502
	#pragma message LUA_VERSION
	#error
	#endif
	//std::cout << azpVersion() << std::endl;
	//wxLogMessage(wxT("AZPVM Running"));	//Debug TODO
	if(!wxFileExists(file))
	{
		wxLogError(wxT("The file (")+file+wxT(") doesn't exist. Reinstall the game can solve the problem"));
		return;
	}else{
		if(state==azpVM_TEST)wxLogVerbose(wxT("[AZPVM] Init AZPVM"));
		//Run Lua 5.2
	 lua_State *azpvm = luaL_newstate();

    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
        {NULL, NULL}
    };
    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        luaL_requiref(azpvm, lib->name, lib->func, 1);
        lua_settop(azpvm, 0);
    }
	lua_pushcfunction(azpvm, azpInit);
	lua_setglobal(azpvm, "azpInit");
	lua_pushcfunction(azpvm,azpConsole);
	lua_setglobal(azpvm,"azpConsole");
	lua_pushcfunction(azpvm, azpLogo);
	lua_setglobal(azpvm,"azpLogo");
	lua_pushcfunction(azpvm,azpWait);
	lua_setglobal(azpvm,"azpWait");
	lua_pushcfunction(azpvm,azpMosaic);
	lua_setglobal(azpvm,"azpMosaic");
	lua_pushcfunction(azpvm,azpExecute);
	lua_setglobal(azpvm,"azpExecute");
	lua_pushcfunction(azpvm,azpGet);
	lua_setglobal(azpvm,"azpGet");
	lua_pushcfunction(azpvm,azpSet);
	lua_setglobal(azpvm,"azpSet");
	lua_pushcfunction(azpvm,azpStartMission);
	lua_setglobal(azpvm,"azpStartMission");
	lua_pushcfunction(azpvm,azpFinishMission);
	lua_setglobal(azpvm,"azpFinishMission");
	lua_pushcfunction(azpvm,azpDialog);
	lua_setglobal(azpvm,"azpDialog");
	lua_pushcfunction(azpvm,azpQuestion);
	lua_setglobal(azpvm,"azpQuestion");
	lua_pushcfunction(azpvm,azpBattle);
	lua_setglobal(azpvm,"azpBattle");

    int status = luaL_loadfile(azpvm, file.mb_str());
    int result = 0;
    if(status == LUA_OK)
    {
        result = lua_pcall(azpvm, 0, LUA_MULTRET, 0);
    }
    else
    {

    }
 
    // close the Lua state
	
	lua_close(azpvm);

	}

}

