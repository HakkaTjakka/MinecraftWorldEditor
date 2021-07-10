@echo off
setlocal enabledelayedexpansion
REM if not exist backup_obj_test mkdir backup_obj_test
if not exist backup_obj_test2 mkdir backup_obj_test2


for /f "tokens=*" %%F in ('dir /s /b "out\*.obj"') do (
	set "l=%%~nF"
	set "result=!l:~0,17!"
	set "result2=!l:~0,14!"

	if exist "!result2!\!result!-21\%%~nF.obj" move "!result2!\!result!-21\%%~nF.obj" backup_obj_test2
	move "out\%%~nF.obj" "!result2!\!result!-21"
)
pause