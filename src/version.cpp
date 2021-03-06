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

//Add Version frame DONE
#include "url.hpp"

#include "wx/aboutdlg.h"
#include "version.hpp"
#include "wx/wxhtml.h"
#include "wx/utils.h"
void Version::Display::About()
{
	wxAboutDialogInfo info;
	info.AddArtist(wxT("Adrián Arroyo Calle"));
	info.AddArtist(wxT("Raúl Izquierdo Buznego"));
	info.AddArtist(wxT("Pablo Izquierdo Buznego"));
	info.AddDeveloper(wxT("Adrián Arroyo Calle"));
	info.AddDocWriter(wxT("Adrián Arroyo Calle"));
	info.AddDocWriter(wxT("Raúl Izquierdo Buznego"));
	info.AddTranslator(wxT("Adrián Arroyo Calle->Spanish"));
	info.AddTranslator(wxT("Google Translate->French"));
	info.SetDescription(_("Azpazeta is a strategy-economic game about Vadrix and the region of Azpazeta. Explore the world in a sandbox game"));
#ifdef WIN32
	info.SetLicense(wxT("Azpazeta The strategy-economic game\nCopyright (C) 2013  Adrián Arroyo Calle\n\n"
L"This program is free software; you can redistribute it and/or\n"
L"modify it under the terms of the GNU General Public License\n"
L"as published by the Free Software Foundation; either version 2\n"
L"of the License, or (at your option) any later version.\n"

L"This program is distributed in the hope that it will be useful,\n\n"
L"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
L"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
L"GNU General Public License for more details.\n\n"

L"You should have received a copy of the GNU General Public License\n"
L"along with this program; if not, write to the Free Software\n"
L"Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA."));
#else
	info.SetLicense(wxT("Azpazeta The strategy-economic game\nCopyright (C) 2013  Adrián Arroyo Calle\n\n"
"This program is free software; you can redistribute it and/or\n"
"modify it under the terms of the GNU General Public License\n"
"as published by the Free Software Foundation; either version 2\n"
"of the License, or (at your option) any later version.\n"

"This program is distributed in the hope that it will be useful,\n\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n\n"

"You should have received a copy of the GNU General Public License\n"
"along with this program; if not, write to the Free Software\n"
"Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA."));
#endif
	info.SetName(wxT("Azpazeta"));
	info.SetVersion(wxString::FromUTF8(AZPAZETA_VERSION_STR));
	info.SetWebSite(wxString::FromUTF8(URL_HOMEPAGE));
	wxAboutBox(info);
}
void Version::Display::All()
{
	//wxHTML, create class VersionHTML and put all the data in this file DONE
	HTMLVersion* version=new HTMLVersion();
	version->ShowModal();
	
}
HTMLVersion::HTMLVersion() : wxDialog(NULL,wxID_ANY,_("Version information"))
{
	//#pragma message "Existen mensajes"
	//#pragma message OS_WX
	//Put the data DONE
	SetSize(500,500);
	html=new wxHtmlWindow(this);
	wxString htmlPageVersion=wxString::Format(wxT("<h1>Azpazeta Version Information</h1><h2>Version</h2><p>Major version: %d<br>Minor version: %d<br>Patch version: %d<br>Version name: %s<br>AZPScript Version: %d</p>"),AZPAZETA_VERSION_MAJOR,AZPAZETA_VERSION_MINOR,AZPAZETA_VERSION_PATCH,AZPAZETA_WX_NAME,AZPSCRIPT_VERSION);
	html->SetPage(htmlPageVersion);
	//Compiling options
        wxString htmlPageCompile=wxT("<h2>Compile configuration</h2><p>Compiler: ");
	htmlPageCompile.Append(wxString::FromUTF8("Unknow")); //AZP_COMPILER
	htmlPageCompile.Append(wxT("<br>CMake Version: "));
	htmlPageCompile.Append(wxString::FromUTF8("Unknow")); //AZP_CMAKE_VERSION
	htmlPageCompile.Append(wxT("<br>Operating System: "));
	htmlPageCompile.Append(wxString::FromUTF8("Unknow")); //AZP_SYSTEM
	htmlPageCompile.Append(wxT("<br>Processor: "));
	htmlPageCompile.Append(wxString::FromUTF8("Unknow")); //AZP_PROCESSOR
	htmlPageCompile.Append(wxT("<br>wxWidgets Version String: "));
	htmlPageCompile.Append(wxVERSION_STRING);
//	htmlPageCompile.Append(wxT("<br>wxWidgets Minor Version: "));
//	htmlPageCompile.Append(wxMINOR_VERSION);
	htmlPageCompile.Append(wxT("<br></p>"));//COMPILER_WX,CMAKE_WX_VERSION,OS_WX,PROCESSOR_WX,wxMAJOR_VERSION,wxMINOR_VERSION);
	html->AppendToPage(htmlPageCompile);
	//Runtime Values
	wxString htmlPageRunning=wxT("<h2>Runtime values</h2><p>Host name: ");
	htmlPageRunning.Append(wxGetHostName());
	htmlPageRunning.Append(wxT("<br>Operating System: "));
	htmlPageRunning.Append(wxGetOsDescription());
	htmlPageRunning.Append(wxT("<br>Little endian: "));
	htmlPageRunning.Append(wxIsPlatformLittleEndian() ? wxT("Yes") : wxT("No"));
	htmlPageRunning.Append(wxT("<br>Native 64 bits: "));
	htmlPageRunning.Append(wxIsPlatform64Bit() ? wxT("Yes") : wxT("No"));
	html->AppendToPage(htmlPageRunning);

	
	


}
