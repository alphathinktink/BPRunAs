// See LICENSE file for usage restrictions.
#ifndef DispWindowH
#define DispWindowH
#include <windows.h>
#include "UniString.h"

extern HWND DispWindowHWnd;

void __fastcall CreateDispWindow(HINSTANCE hInstance,HWND hParent);
void __fastcall DestroyDispWindow();
void __fastcall DispWindowAddNetUserToCombo(const UniString &user);
void __fastcall DispWindowSetDomain(const UniString &text);
UniString __fastcall DispWindowGetDomain(void);
void __fastcall DispWindowSetUser(const UniString &text);
UniString __fastcall DispWindowGetUser(void);
void __fastcall DispWindowSetPassword(const UniString &text);
UniString __fastcall DispWindowGetPassword(void);
void __fastcall DispWindowSetCommand(const UniString &text);
UniString __fastcall DispWindowGetCommand(void);
void __fastcall DispWindowSetRun(FARPROC aProc);

#endif//DispWindowH