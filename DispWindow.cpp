// See LICENSE file for usage restrictions.
#include "DispWindow.h"
#include "resource.h"
#include <Commctrl.h>

//---------------------------------------------------------------------------
HWND DispWindowHWnd=NULL;
static HICON hMainIcon=NULL;
static FARPROC ExecuteProc=NULL;

//---------------------------------------------------------------------------
BOOL CALLBACK DispWindowProc(HWND hwndDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
		case WM_INITDIALOG:
		{
			::SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)hMainIcon);
			::SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (LPARAM)hMainIcon);
			::SendDlgItemMessage(DispWindowHWnd,IDC_LOGONNAME_COMBO,CB_SETMINVISIBLE,(WPARAM)10,0);
		}
		return TRUE;
		case WM_CLOSE:
		::PostQuitMessage(0);
		break;
		case WM_COMMAND:
		{
			if(LOWORD(wParam)==IDC_OK_BUTTON)
			{
				if(ExecuteProc)
				{
					ExecuteProc();
				}
			}
		}
		break;
	}
	return FALSE;
}
//---------------------------------------------------------------------------
void __fastcall CreateDispWindow(HINSTANCE hInstance,HWND hParent)
{
	if(DispWindowHWnd!=NULL)return;
	hMainIcon=::LoadIcon(hInstance,MAKEINTRESOURCE(IDI_MAINICON));
	DispWindowHWnd=::CreateDialog(
		hInstance,
		MAKEINTRESOURCE(IDD_MAIN_DIALOG),
		hParent,
		(DLGPROC)DispWindowProc
	);
}
//---------------------------------------------------------------------------
void __fastcall DestroyDispWindow()
{
	HWND Temp=DispWindowHWnd;
	DispWindowHWnd=NULL;
	::DestroyWindow(Temp);
	::DestroyIcon(hMainIcon);
}
//---------------------------------------------------------------------------
UniString __fastcall GetCtrlTextWithNew(int ID)
{
	UniString res;
	if(!::IsWindow(DispWindowHWnd))return res;
	if(ID==0)return res;
	LRESULT LEN=::SendDlgItemMessage(DispWindowHWnd,ID,WM_GETTEXTLENGTH,0,0);
	if(LEN==0)return res;
	wchar_t *Res=new wchar_t[LEN+2];
	memset(Res,0,sizeof(wchar_t)*(LEN+2));
	::SendDlgItemMessage(DispWindowHWnd,ID,WM_GETTEXT,LEN+1,(LPARAM)Res);
	res=Res;
	delete [] Res;
	return res;
}
//---------------------------------------------------------------------------
void __fastcall DispWindowAddNetUserToCombo(const UniString &user)
{
	if(!::IsWindow(DispWindowHWnd))return;
	if(user==NULL)return;
	::SendDlgItemMessage(DispWindowHWnd,IDC_LOGONNAME_COMBO,CB_ADDSTRING,0,(LPARAM)(user.c_str()));
}
//---------------------------------------------------------------------------
void __fastcall DispWindowSetDomain(const UniString &text)
{
	if(!::IsWindow(DispWindowHWnd))return;
	if(text==NULL)return;
	::SendDlgItemMessage(DispWindowHWnd,IDC_DOMAIN_EDIT,WM_SETTEXT,0,(LPARAM)(text.c_str()));
}
//---------------------------------------------------------------------------
UniString __fastcall DispWindowGetDomain(void)
{
	return GetCtrlTextWithNew(IDC_DOMAIN_EDIT);
}
//---------------------------------------------------------------------------
void __fastcall DispWindowSetUser(const UniString &text)
{
	if(!::IsWindow(DispWindowHWnd))return;
	if(text==NULL)return;
	::SendDlgItemMessage(DispWindowHWnd,IDC_LOGONNAME_COMBO,WM_SETTEXT,0,(LPARAM)(text.c_str()));
}
//---------------------------------------------------------------------------
UniString __fastcall DispWindowGetUser(void)
{
	return GetCtrlTextWithNew(IDC_LOGONNAME_COMBO);
}
//---------------------------------------------------------------------------
void __fastcall DispWindowSetPassword(const UniString &text)
{
	if(!::IsWindow(DispWindowHWnd))return;
	if(text==NULL)return;
	::SendDlgItemMessage(DispWindowHWnd,IDC_PASSWORD_EDIT,WM_SETTEXT,0,(LPARAM)(text.c_str()));
}
//---------------------------------------------------------------------------
UniString __fastcall DispWindowGetPassword(void)
{
	return GetCtrlTextWithNew(IDC_PASSWORD_EDIT);
}
//---------------------------------------------------------------------------
void __fastcall DispWindowSetCommand(const UniString &text)
{
	if(!::IsWindow(DispWindowHWnd))return;
	if(text==NULL)return;
	::SendDlgItemMessage(DispWindowHWnd,IDC_COMMAND_EDIT,WM_SETTEXT,0,(LPARAM)(text.c_str()));
}
//---------------------------------------------------------------------------
UniString __fastcall DispWindowGetCommand(void)
{
	return GetCtrlTextWithNew(IDC_COMMAND_EDIT);
}
//---------------------------------------------------------------------------
void __fastcall DispWindowSetRun(FARPROC aProc)
{
	ExecuteProc=aProc;
}
//---------------------------------------------------------------------------
