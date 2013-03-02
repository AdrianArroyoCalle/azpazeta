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

#include "lua.hpp"
#include "wx/wx.h"

typedef enum{ 	//States of AzpVM
azpVM_FULL,	//All the options (not recomended)
azpVM_SECURE,	//Secure AzpVM (default)
azpVM_INSTALLATION, //Install files for AZPP (only INSTALL.LUA, UPGRADE.LUA and UNINSTALL.LUA)
azpVM_TEST,	//Test script for developers (verbose output)
azpVM_INTERNET	//Allow Internet in azpVM_SECURE

}AZPVMState;

class AZPVM
{
	public:
		AZPVM(wxString file,AZPVMState state);
};
static int azpInit(lua_State*);