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
#include "azpmarket.hpp"
#include "wx/sstream.h"
#include "wx/protocol/http.h"
#include "wx/progdlg.h"
#include "../app.hpp"

extern wxString azppath;

HTMLMarket::HTMLMarket() : wxDialog(NULL,wxID_ANY,_("Azpazeta Market"))
{
	SetSize(800,600);

	wxPanel* toolbar=new wxPanel(this,wxID_ANY,wxPoint(0,0),wxSize(800,80));
	wxPanel* main=new wxPanel(this,wxID_ANY,wxPoint(0,80),wxSize(800,520));
	
	

	wxImage azpazetaimg(azppath+wxT("/media/azpazeta.png"),wxBITMAP_TYPE_PNG);
	wxBitmap azpscale=wxBitmap(azpazetaimg.Scale(64,64));
	wxBitmapButton* back=new wxBitmapButton(toolbar,wxID_ANY,azpscale,wxPoint(1,1));
	back->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(HTMLMarket::AzpHome),NULL,this);
	
	html=new HTMLBrowser(main);
	AZPOptions options=LoadOptions();
	StartPage(options.azpscript.azpazetaMarketURL);




	



}
void HTMLMarket::StartPage(wxString url)
{
	wxProgressDialog progress(_("Azpazeta Market"),_("Reading user options"));
	
	progress.Pulse(_("Getting server data"));
	wxString server=url.AfterFirst('/').AfterFirst('/').BeforeFirst('/');
	wxString subpage=url.AfterFirst('/').AfterFirst('/').AfterFirst('/').Prepend(_("/"));

	wxHTTP get;
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	get.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

 	progress.Pulse(_("Connecting to server: ")+server);
	// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
	while (!get.Connect(server))  // only the server, no pages here yet ...
	    wxSleep(5);
 
	wxApp::IsMainLoopRunning(); // should return true
 	progress.Pulse(_("Accessing files"));
	// use _T("/") for index.html, index.php, default.asp, etc.
	wxInputStream *httpStream = get.GetInputStream(subpage);

if (get.GetError() == wxPROTO_NOERR)
{
    progress.Pulse(_("Reading page"));
    wxString res;
    wxStringOutputStream out_stream(&res);
    httpStream->Read(out_stream);
	html->SetPage(res);
	title=html->GetOpenedPageTitle();
	mainpage=url;

}
else
{
	progress.Update(100,_("Fail to connect"));
    html->SetPage(_("<h1>Error</h1>Unable to connect to the server"));
	mainpage=url;
	title=wxT("NOTEXIST");
	
}
 
wxDELETE(httpStream);
get.Close();
}
void HTMLMarket::AzpHome(wxCommandEvent& event)
{
	if(title.Cmp(html->GetOpenedPageTitle())==0)
	{
		this->Destroy();
	}else
	{
		StartPage(mainpage);
	}
}
HTMLBrowser::HTMLBrowser(wxWindow* panel) : wxHtmlWindow(panel,wxID_ANY,wxPoint(1,1),wxSize(800,520))
{



}
void HTMLBrowser::OnLinkClicked(const wxHtmlLinkInfo & link)
{
	wxProgressDialog progress(_("Azpazeta Market"),_("Reading user options"));
	wxString webpage=link.GetHref();
	progress.Pulse(_("Getting server data"));
	wxString server=webpage.AfterFirst('/').AfterFirst('/').BeforeFirst('/');
	wxString subpage=webpage.AfterFirst('/').AfterFirst('/').AfterFirst('/').Prepend(_("/"));

	wxHTTP get;
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	get.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

 	progress.Pulse(_("Connecting to server: ")+server);
	// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
	while (!get.Connect(server))  // only the server, no pages here yet ...
	    wxSleep(5);
 
	wxApp::IsMainLoopRunning(); // should return true
 	progress.Pulse(_("Accessing files"));
	// use _T("/") for index.html, index.php, default.asp, etc.
	wxInputStream *httpStream = get.GetInputStream(subpage);

if (get.GetError() == wxPROTO_NOERR)
{
    progress.Pulse(_("Reading page"));
    wxString res;
    wxStringOutputStream out_stream(&res);
    httpStream->Read(out_stream);
	SetPage(res);

}
else
{
	progress.Update(100,_("Fail to connect"));
    SetPage(_("<h1>Error</h1>Unable to connect to the server"));
	
}
 
wxDELETE(httpStream);
get.Close();
	
}