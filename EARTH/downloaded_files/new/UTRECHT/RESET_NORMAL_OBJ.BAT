@echo off
setlocal enabledelayedexpansion
if not exist out2 mkdir out2

for /f "tokens=*" %%F in ('dir /s /b "backup_obj_test\*.obj"') do (
	set "l=%%~nF"
	set "result=!l:~0,17!"
	set "result2=!l:~0,14!"

	if exist "!result2!\!result!-21\%%~nF.obj" move "!result2!\!result!-21\%%~nF.obj" out2
	move "backup_obj_test\%%~nF.obj" "!result2!\!result!-21"
)
pause