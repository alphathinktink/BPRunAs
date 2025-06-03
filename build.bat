@ECHO OFF
@REM call notepad++ -openSession .\BPRunAs.sess
SET MINGW32_BIN=C:\msys64\mingw32\bin
IF NOT EXIST bin mkdir bin


:TestMinGW
IF EXIST "%MINGW32_BIN%\g++.exe" GOTO CleanFiles
@ECHO MinGW compiler not found.
PAUSE
EXIT

:CleanFiles
@ECHO CleanFiles...
IF EXIST bin\BPRunAs.exe (
	del bin\BPRunAs.exe >NUL 2>&1
	IF EXIST bin\BPRunAs.exe (
		@ECHO Failed to delete BPRunAs.exe -- is it still running?
		powershell -c "(New-Object Media.SoundPlayer 'C:\Windows\Media\Windows Exclamation.wav').PlaySync()"
		PAUSE
		EXIT
	)
)
IF EXIST bin\resource.o del bin\resource.o

SET PATH=%PATH%;%MINGW32_BIN%

:CompileRes
@ECHO CompileRes...
windres resource.rc bin\resource.o
IF %ERRORLEVEL% EQU 0 GOTO CompileEXE
ECHO There was an error during resource compile operation.
PAUSE
EXIT

:CompileEXE
@ECHO CompileProject...
g++ -m32 -DUNICODE -D_UNICODE -DNOVTABLE= -mwindows -static -Wattributes -o bin\BPRunAs.exe BPRunAs.cpp DispWindow.cpp TansGLEM.cpp bin\resource.o -lnetapi32
IF %ERRORLEVEL% EQU 0 GOTO CleanupCompile
ECHO There was an error during exe compile/build operation.
PAUSE
EXIT

:CleanupCompile
@ECHO CleanupCompile...
IF EXIST bin\resource.o del bin\resource.o

:Complete
@ECHO Compile/build completed.
