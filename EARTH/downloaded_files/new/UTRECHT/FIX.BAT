@echo off
setlocal enabledelayedexpansion
REM if not exist out2 mkdir out2
MKDIR \TRASH
for /f "tokens=*" %%F in (FIX.TXT) do (
	set "l=%%~nF"
	set "result=!l:~0,17!"
	set "result2=!l:~0,14!"

	CALL :TEST "!result2!\!result!-21"

	REM if exist "!result2!\!result!-21\%%~nF.obj" move "!result2!\!result!-21\%%~nF.obj" out2
	REM move "backup_obj_test\%%~nF.obj" "!result2!\!result!-21"
)

:TEST
	if exist "%1" (
		ECHO EXIST:     %1 %~t1 
		REM RMDIR %1\ /S /Q
		MOVE %1 \TRASH
	) else (
		ECHO NOT EXIST: %1 %~t1 
	)

	exit /b

pause