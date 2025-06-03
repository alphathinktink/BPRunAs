// See LICENSE file for usage restrictions.
#include <windows.h>
#include <string>
#include <objidl.h>
#include <winerror.h>
#include <lm.h>
#include <sddl.h>
#include "DispWindow.h"
#include "TansGLEM.h"
#include "resource.h"
#pragma comment(lib, netapi32.lib)
#define NERR_Success 0 /* Success */
using namespace std;

HINSTANCE hGlobalInstance=NULL;


int CALLBACK ToExecute();

//---------------------------------------------------------------------------
void __fastcall RunAsUser(void);
void PopulateLocalAdmins(void);
//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hGlobalInstance=hInstance;
	wchar_t Domain[MAX_PATH+1];
	DWORD DomainBuffSize=MAX_PATH;
	memset(Domain,0,sizeof(Domain));
	BOOL bRES=::GetComputerNameEx(
		ComputerNameDnsFullyQualified,
		Domain,
		&DomainBuffSize
	);
	if(!bRES)
	{
		DWORD LE=::GetLastError();
		std::wstring t=to_wstring(LE);
		t=L"Failed to get domain name: LE="+t;
		MessageBoxW(NULL,t.c_str(),L"Test",MB_OK);
		return 0;
	}

	CreateDispWindow(hInstance,HWND_DESKTOP);
	PopulateLocalAdmins();
	SendDlgItemMessage(DispWindowHWnd, IDC_LOGONNAME_COMBO, CB_SETCURSEL, 0, 0);
	DispWindowSetDomain(Domain);
	DispWindowSetCommand(L"C:\\Windows\\System32\\cmd.exe");
	FARPROC TEMPTORUN=ToExecute;
	DispWindowSetRun(TEMPTORUN);
	MSG msg;
	while(::GetMessage(&msg, NULL, 0, 0))
	{
		if(DispWindowHWnd==NULL || !::IsDialogMessage(DispWindowHWnd,&msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
	DestroyDispWindow();
	return 1;
}
//---------------------------------------------------------------------------
int CALLBACK ToExecute()
{
	RunAsUser();
	return 0;
}
//---------------------------------------------------------------------------
void __fastcall RunAsUser(void)
{
	UniString Domain=DispWindowGetDomain();
	UniString User=DispWindowGetUser();
	UniString Password=DispWindowGetPassword();
	UniString Command=DispWindowGetCommand();
	if(Command==NULL || Command==L"")
	{
		Command=L"C:\\Windows\\System32\\cmd.exe";
	}
	PROCESS_INFORMATION pi;
	memset(&pi,0,sizeof(PROCESS_INFORMATION));
	BOOL bRES=::CreateProcessWithLogonW(
		User.c_str(),
		Domain.c_str(),
		Password.c_str(),
		LOGON_WITH_PROFILE,
		Command.c_str(),
		NULL,
		CREATE_DEFAULT_ERROR_MODE,
		NULL,
		NULL,
		NULL,
		&pi
	);	
	if(!bRES)
	{
		DWORD LE=::GetLastError();
		UniString LEText=TransGLEM(LE);
		UniString t=L"Failed to create process: "+LEText+" ("+UniString((int)LE)+")";;
		MessageBoxW(DispWindowHWnd,t.c_str(),L"Test",MB_OK);
	}
	::CloseHandle(pi.hProcess);
	::CloseHandle(pi.hThread);
}
//---------------------------------------------------------------------------
void PopulateLocalAdmins(void)
{
	LPLOCALGROUP_MEMBERS_INFO_2 pBuf=NULL;
	DWORD dwEntriesRead=0,dwTotalEntries=0,dwResumeHandle=0;

	if(NetLocalGroupGetMembers(
		NULL,
		L"Administrators",
		2,
		(LPBYTE *)&pBuf,
		MAX_PREFERRED_LENGTH,
		&dwEntriesRead,
		&dwTotalEntries,
		&dwResumeHandle
	)==NERR_Success && pBuf!=NULL)
	{
		for(DWORD i=0;i<dwEntriesRead;++i)
		{
			if(pBuf[i].lgrmi2_sidusage==SidTypeUser && pBuf[i].lgrmi2_sid!=NULL)
			{
				DWORD nameSize=0;
				DWORD domainSize=0;
				SID_NAME_USE sidType;

				// Probe buffer sizes
				LookupAccountSidW(
					NULL,
					pBuf[i].lgrmi2_sid,
					NULL,
					&nameSize,
					NULL,
					&domainSize,
					&sidType
				);

				if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
				{
					WCHAR *name=new WCHAR[nameSize];
					WCHAR *domain=new WCHAR[domainSize];

					if(LookupAccountSidW(
						NULL,
						pBuf[i].lgrmi2_sid,
						name,
						&nameSize,
						domain,
						&domainSize,
						&sidType
					))
					{
						LPUSER_INFO_1 pUserInfo=NULL;
						NET_API_STATUS ures=NetUserGetInfo(NULL,name,1,(LPBYTE *)&pUserInfo);
						if(ures==NERR_Success && pUserInfo!=NULL)
						{
							if((pUserInfo->usri1_flags & UF_ACCOUNTDISABLE)==0)
							{
								DispWindowAddNetUserToCombo(name);
							}
							NetApiBufferFree(pUserInfo);
						}
					}

					delete [] name;
					delete [] domain;
				}
			}
		}
		NetApiBufferFree(pBuf);
	}
}
//---------------------------------------------------------------------------
