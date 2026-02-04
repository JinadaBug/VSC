@echo off
setlocal

:: ======= SETUP ENVIRONMENT =======
echo Initializing MSVC environment...
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul

:: ====== CLEAN OBJ ======
if exist obj\*.obj del /q obj\*.obj

:: ====== CLEAN EXE ======
if exist bin\desktop\windows\*.exe del /q bin\desktop\windows\*.exe

:: ===== CREATE PATH =====
lua bat\track.lua

:: ======= COMPILE =======
cl ^
    /std:c++20 ^
    /EHsc ^
    /nologo ^
    /c ^
    /Fo"obj\\" ^
    /D "_WIN32_WINNT=0x0A00" ^
    /I add\inc ^
    /I src ^
    @bat\files.txt

:: ==== CHECK ERROR ====
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Compilation failed.
    exit /b %ERRORLEVEL%
)

:: ======= LINK =======
link ^
    obj\*.obj ^
    /LIBPATH:add\lib SDL3.lib vulkan-1.lib ^
    /OUT:bin\desktop\windows\client.exe ^
    /SUBSYSTEM:WINDOWS ^
    /MACHINE:X64

:: ==== CHECK ERROR ====
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Linking failed.
    exit /b %ERRORLEVEL%
)

:: ======= SUCCESS =======
echo [SUCCESS] Build complete.
endlocal