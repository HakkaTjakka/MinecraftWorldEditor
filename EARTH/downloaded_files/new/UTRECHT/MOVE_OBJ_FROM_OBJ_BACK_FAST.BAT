@echo off
setlocal enabledelayedexpansion
if not exist was_present mkdir was_present


for /f "tokens=*" %%F in ('dir /s /b "obj\*.obj"') do (
	set "l=%%~nF"
	set "result=!l:~0,17!"
	set "result2=!l:~0,14!"

	if exist "!result2!\!result!-21\%%~nF.obj" move "!result2!\!result!-21\%%~nF.obj" was_present
	move "%%F" "!result2!\!result!-21"
)
pause