// See LICENSE file for usage restrictions.
//---------------------------------------------------------------------------
#include <windows.h>
#pragma hdrstop

#include "TansGLEM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
UniString TransGLEM(DWORD value)
{
	LPVOID lpMsgBuf;
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,NULL,value,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),/* Default language*/(LPTSTR) &lpMsgBuf,0,NULL);
	UniString EM=((TCHAR *)lpMsgBuf);
	LocalFree(lpMsgBuf);
	return EM;
};
//---------------------------------------------------------------------------
