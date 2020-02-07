@echo off
::Set Environments for X86_64 build
cd %~dp0
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
where cl.exe link.exe

::Set Environment Variables
set NAME=hvtool.exe
set BINDIR=bin
set CFLAGS=/c /O2 /W4 /MD /nologo /Fo%BINDIR%\\
set LFLAGS=/nologo /MACHINE:X64
set LIBS=ole32.lib shell32.lib lib/computecore.lib lib/computenetwork.lib

::Build
@mkdir %BINDIR%

cl.exe %CFLAGS% src\*.c
link.exe %LFLAGS% %LIBS% %BINDIR%\*.obj /OUT:%BINDIR%\%NAME%

:: Get stats
dir /b %BINDIR%\*.exe
pause
exit /b
